/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "APMAutoPilotPlugin.h"
#include "UAS.h"
#include "FirmwarePlugin/APM/APMParameterMetaData.h"  // FIXME: Hack
#include "FirmwarePlugin/APM/APMFirmwarePlugin.h"  // FIXME: Hack
#include "FirmwarePlugin/APM/ArduCopterFirmwarePlugin.h"
#include "VehicleComponent.h"
#include "APMAirframeComponent.h"
#include "APMAirframeComponentAirframes.h"
#include "APMAirframeLoader.h"
#include "APMFlightModesComponent.h"
#include "APMRadioComponent.h"
#include "APMSafetyComponent.h"
#include "APMTuningComponent.h"
#include "APMSensorsComponent.h"
#include "APMPowerComponent.h"
#include "APMMotorComponent.h"
#include "APMCameraComponent.h"
#include "APMLightsComponent.h"
#include "APMSubFrameComponent.h"
#include "ESP8266Component.h"
#include "APMHeliComponent.h"
#include "QGCApplication.h"

#include <QSerialPortInfo>

/// This is the AutoPilotPlugin implementatin for the MAV_AUTOPILOT_ARDUPILOT type.
APMAutoPilotPlugin::APMAutoPilotPlugin(Vehicle* vehicle, QObject* parent)
    : AutoPilotPlugin           (vehicle, parent)
    , _incorrectParameterVersion(false)
    , _airframeComponent        (NULL)
    , _cameraComponent          (NULL)
    , _lightsComponent          (NULL)
    , _subFrameComponent        (NULL)
    , _flightModesComponent     (NULL)
    , _powerComponent           (NULL)
    , _motorComponent           (NULL)
    , _radioComponent           (NULL)
    , _safetyComponent          (NULL)
    , _sensorsComponent         (NULL)
    , _tuningComponent          (NULL)
    , _airframeFacts            (new APMAirframeLoader(this, vehicle->uas(), this))
    , _esp8266Component         (NULL)
    , _heliComponent            (NULL)
{
    APMAirframeLoader::loadAirframeFactMetaData();

#if !defined(NO_SERIAL_LINK) && !defined(__android__)
    connect(vehicle->parameterManager(), &ParameterManager::parametersReadyChanged, this, &APMAutoPilotPlugin::_checkForBadCubeBlack);
#endif
}

APMAutoPilotPlugin::~APMAutoPilotPlugin()
{

}

const QVariantList& APMAutoPilotPlugin::vehicleComponents(void)
{
    if (_components.count() == 0 && !_incorrectParameterVersion) {
        if (_vehicle->parameterManager()->parametersReady()) {
            _airframeComponent = new APMAirframeComponent(_vehicle, this);
            _airframeComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_airframeComponent));

            if ( _vehicle->supportsRadio() ) {
                _radioComponent = new APMRadioComponent(_vehicle, this);
                _radioComponent->setupTriggerSignals();
                _components.append(QVariant::fromValue((VehicleComponent*)_radioComponent));
            }

            // No flight modes component for Sub versions 3.5 and up
            if (!_vehicle->sub() || (_vehicle->versionCompare(3, 5, 0) < 0)) {
                _flightModesComponent = new APMFlightModesComponent(_vehicle, this);
                _flightModesComponent->setupTriggerSignals();
                _components.append(QVariant::fromValue((VehicleComponent*)_flightModesComponent));
            }

            _sensorsComponent = new APMSensorsComponent(_vehicle, this);
            _sensorsComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_sensorsComponent));

            _powerComponent = new APMPowerComponent(_vehicle, this);
            _powerComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_powerComponent));

            if (_vehicle->sub() && _vehicle->versionCompare(3, 5, 3) >= 0) {
                _motorComponent = new APMMotorComponent(_vehicle, this);
                _motorComponent->setupTriggerSignals();
                _components.append(QVariant::fromValue((VehicleComponent*)_motorComponent));
            }

            _safetyComponent = new APMSafetyComponent(_vehicle, this);
            _safetyComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_safetyComponent));

            if (_vehicle->vehicleType() == MAV_TYPE_HELICOPTER) {
                _heliComponent = new APMHeliComponent(_vehicle, this);
                _heliComponent->setupTriggerSignals();
                _components.append(QVariant::fromValue((VehicleComponent*)_heliComponent));
            }

            _tuningComponent = new APMTuningComponent(_vehicle, this);
            _tuningComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_tuningComponent));

            _cameraComponent = new APMCameraComponent(_vehicle, this);
            _cameraComponent->setupTriggerSignals();
            _components.append(QVariant::fromValue((VehicleComponent*)_cameraComponent));

            if (_vehicle->sub()) {
                _lightsComponent = new APMLightsComponent(_vehicle, this);
                _lightsComponent->setupTriggerSignals();
                _components.append(QVariant::fromValue((VehicleComponent*)_lightsComponent));

                if(_vehicle->versionCompare(3, 5, 0) >= 0) {
                    _subFrameComponent = new APMSubFrameComponent(_vehicle, this);
                    _subFrameComponent->setupTriggerSignals();
                    _components.append(QVariant::fromValue((VehicleComponent*)_subFrameComponent));
                }
            }

            //-- Is there an ESP8266 Connected?
            if(_vehicle->parameterManager()->parameterExists(MAV_COMP_ID_UDP_BRIDGE, "SW_VER")) {
                _esp8266Component = new ESP8266Component(_vehicle, this);
                _esp8266Component->setupTriggerSignals();
                _components.append(QVariant::fromValue((VehicleComponent*)_esp8266Component));
            }
        } else {
            qWarning() << "Call to vehicleCompenents prior to parametersReady";
        }
    }

    return _components;
}

QString APMAutoPilotPlugin::prerequisiteSetup(VehicleComponent* component) const
{
    bool requiresAirframeCheck = false;

    if (qobject_cast<const APMFlightModesComponent*>(component)) {
        if (_airframeComponent && !_airframeComponent->setupComplete()) {
            return _airframeComponent->name();
        }
        if (_radioComponent && !_radioComponent->setupComplete()) {
            return _radioComponent->name();
        }
        requiresAirframeCheck = true;
    } else if (qobject_cast<const APMRadioComponent*>(component)) {
        requiresAirframeCheck = true;
    } else if (qobject_cast<const APMCameraComponent*>(component)) {
        requiresAirframeCheck = true;
    } else if (qobject_cast<const APMPowerComponent*>(component)) {
        requiresAirframeCheck = true;
    } else if (qobject_cast<const APMSafetyComponent*>(component)) {
        requiresAirframeCheck = true;
    } else if (qobject_cast<const APMTuningComponent*>(component)) {
        requiresAirframeCheck = true;
    } else if (qobject_cast<const APMSensorsComponent*>(component)) {
        requiresAirframeCheck = true;
    }

    if (requiresAirframeCheck) {
        if (_airframeComponent && !_airframeComponent->setupComplete()) {
            return _airframeComponent->name();
        }
    }

    return QString();
}

#if !defined(NO_SERIAL_LINK) && !defined(__android__)
/// The following code is executed when the Vehicle is parameter ready. It checks for the service bulletin against Cube Blacks.
void APMAutoPilotPlugin::_checkForBadCubeBlack(void)
{
    bool cubeBlackFound = false;
    for (const QVariant& varLink: _vehicle->links()) {
        SerialLink* serialLink = varLink.value<SerialLink*>();
        if (serialLink && QSerialPortInfo(*serialLink->_hackAccessToPort()).description().contains(QStringLiteral("CubeBlack"))) {
            cubeBlackFound = true;
        }

    }
    if (!cubeBlackFound) {
        return;
    }

    ParameterManager* paramMgr = _vehicle->parameterManager();

    QString paramAcc3("INS_ACC3_ID");
    QString paramGyr3("INS_GYR3_ID");
    QString paramEnableMask("INS_ENABLE_MASK");

    if (paramMgr->parameterExists(-1, paramAcc3) && paramMgr->getParameter(-1, paramAcc3)->rawValue().toInt() == 0 &&
            paramMgr->parameterExists(-1, paramGyr3) && paramMgr->getParameter(-1, paramGyr3)->rawValue().toInt() == 0 &&
            paramMgr->parameterExists(-1, paramEnableMask) && paramMgr->getParameter(-1, paramEnableMask)->rawValue().toInt() >= 7) {
        qgcApp()->showMessage(tr("WARNING: The flight board you are using has a critical service bulletin against ti which advise against flying. https://discuss.cubepilot.org/t/sb-0000002-critical-service-bulletin-for-cubes-purchased-between-january-2019-to-present-do-not-fly/406"));

    }
}
#endif
