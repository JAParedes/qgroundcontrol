/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "AirMapFlightPlanManager.h"
#include "AirMapManager.h"
#include "AirMapRulesetsManager.h"
#include "AirMapAdvisoryManager.h"
#include "QGCApplication.h"

#include "MissionController.h"
#include "QGCMAVLink.h"

#include "airmap/pilots.h"
#include "airmap/flights.h"
#include "airmap/date_time.h"
#include "airmap/flight_plans.h"
#include "airmap/geometry.h"

using namespace airmap;

//-----------------------------------------------------------------------------
AirMapFlightPlanManager::AirMapFlightPlanManager(AirMapSharedState& shared, QObject *parent)
    : AirspaceFlightPlanProvider(parent)
    , _shared(shared)
{
    connect(&_pollTimer, &QTimer::timeout, this, &AirMapFlightPlanManager::_pollBriefing);
    //-- Set some valid, initial start/end time
    _flightStartTime = QDateTime::currentDateTime().addSecs(10 * 60);
    _flightEndTime   = _flightStartTime.addSecs(30 * 60);
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::setFlightStartTime(QDateTime start)
{
    if(_flightStartTime != start) {
        //-- Can't start in the past
        if(start < QDateTime::currentDateTime()) {
            start = QDateTime::currentDateTime().addSecs(5 * 60);
        }
        _flightStartTime = start;
        emit flightStartTimeChanged();
    }
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::setFlightEndTime(QDateTime end)
{
    if(_flightEndTime != end) {
        //-- End has to be after start
        if(end < _flightStartTime) {
            end = _flightStartTime.addSecs(30 * 60);
        }
        _flightEndTime = end;
        emit flightEndTimeChanged();
    }
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::createFlightPlan(MissionController* missionController)
{
    if (!_shared.client()) {
        qCDebug(AirMapManagerLog) << "No AirMap client instance. Will not create a flight";
        return;
    }

    if (_state != State::Idle) {
        qCWarning(AirMapManagerLog) << "AirMapFlightPlanManager::createFlight: State not idle";
        return;
    }

    //-- TODO: Check if there is an ongoing flight plan and do something about it (Delete it?)
    _createPlan = true;
    if(!_controller) {
        _controller = missionController;
        //-- Get notified of mission changes
        connect(missionController, &MissionController::missionBoundingCubeChanged, this, &AirMapFlightPlanManager::_missionChanged);
    }
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::_createFlightPlan()
{
    _flight.reset();

    //-- Get flight bounding cube and prepare (box) polygon

    //-- TODO: If single point, we need to set a point and a radius instead

    QGCGeoBoundingCube bc = _controller->travelBoundingCube();
    _flight.maxAltitude   = fmax(bc.pointNW.altitude(), bc.pointSE.altitude());
    _flight.takeoffCoord  = _controller->takeoffCoordinate();
    _flight.coords.append(QGeoCoordinate(bc.pointNW.latitude(), bc.pointNW.longitude(), _flight.maxAltitude));
    _flight.coords.append(QGeoCoordinate(bc.pointNW.latitude(), bc.pointSE.longitude(), _flight.maxAltitude));
    _flight.coords.append(QGeoCoordinate(bc.pointSE.latitude(), bc.pointSE.longitude(), _flight.maxAltitude));
    _flight.coords.append(QGeoCoordinate(bc.pointSE.latitude(), bc.pointNW.longitude(), _flight.maxAltitude));
    _flight.coords.append(QGeoCoordinate(bc.pointNW.latitude(), bc.pointNW.longitude(), _flight.maxAltitude));

    if(_flightStartTime.isNull() || _flightStartTime < QDateTime::currentDateTime()) {
        _flightStartTime = QDateTime::currentDateTime().addSecs(5 * 60);
        emit flightStartTimeChanged();
    }

    if(_flightEndTime.isNull() || _flightEndTime < _flightStartTime) {
        _flightEndTime = _flightStartTime.addSecs(30 * 60);
        emit flightEndTimeChanged();
    }

    qCDebug(AirMapManagerLog) << "About to create flight plan";
    qCDebug(AirMapManagerLog) << "Takeoff:     " << _flight.takeoffCoord;
    qCDebug(AirMapManagerLog) << "Bounding box:" << bc.pointNW << bc.pointSE;
    qCDebug(AirMapManagerLog) << "Flight Start:" << _flightStartTime;
    qCDebug(AirMapManagerLog) << "Flight End:  " << _flightEndTime;

    //-- Not Yet
    return;

    if (_pilotID == "") {
        //-- Need to get the pilot id before uploading the flight plan
        qCDebug(AirMapManagerLog) << "Getting pilot ID";
        _state = State::GetPilotID;
        std::weak_ptr<LifetimeChecker> isAlive(_instance);
        _shared.doRequestWithLogin([this, isAlive](const QString& login_token) {
            if (!isAlive.lock()) return;
            Pilots::Authenticated::Parameters params;
            params.authorization = login_token.toStdString();
            _shared.client()->pilots().authenticated(params, [this, isAlive](const Pilots::Authenticated::Result& result) {
                if (!isAlive.lock()) return;
                if (_state != State::GetPilotID) return;
                if (result) {
                    _pilotID = QString::fromStdString(result.value().id);
                    qCDebug(AirMapManagerLog) << "Got Pilot ID:"<<_pilotID;
                    _uploadFlightPlan();
                } else {
                    _flightPermitStatus = AirspaceFlightPlanProvider::PermitUnknown;
                    emit flightPermitStatusChanged();
                    _state = State::Idle;
                    QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
                    emit error("Failed to create Flight Plan", QString::fromStdString(result.error().message()), description);
                    return;
                }
            });
        });
    } else {
        _uploadFlightPlan();
    }

    _flightPermitStatus = AirspaceFlightPlanProvider::PermitPending;
    emit flightPermitStatusChanged();
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::_uploadFlightPlan()
{
    qCDebug(AirMapManagerLog) << "Uploading flight plan";
    _state = State::FlightUpload;
    std::weak_ptr<LifetimeChecker> isAlive(_instance);
    _shared.doRequestWithLogin([this, isAlive](const QString& login_token) {
        if (!isAlive.lock()) return;
        if (_state != State::FlightUpload) return;
        FlightPlans::Create::Parameters params;
        params.max_altitude = _flight.maxAltitude;
        params.buffer       = 2.f;
        params.latitude     = _flight.takeoffCoord.latitude();
        params.longitude    = _flight.takeoffCoord.longitude();
        params.pilot.id     = _pilotID.toStdString();
        /*

        TODO: Convert this to fucking boost

        quint64 start = _flightStartTime.toUTC().toMSecsSinceEpoch();
        quint64 end   = _flightEndTime.toUTC().toMSecsSinceEpoch();

        */
        params.start_time   = Clock::universal_time() + Minutes{5};
        params.end_time     = Clock::universal_time() + Hours{2};
        //-- Rules
        AirMapRulesetsManager* pRulesMgr = dynamic_cast<AirMapRulesetsManager*>(qgcApp()->toolbox()->airspaceManager()->ruleSets());
        if(pRulesMgr) {
            foreach(QString ruleset, pRulesMgr->rulesetsIDs()) {
                params.rulesets.push_back(ruleset.toStdString());
            }
        }
        //-- Geometry: LineString
        Geometry::LineString lineString;
        for (const auto& qcoord : _flight.coords) {
            Geometry::Coordinate coord;
            coord.latitude  = qcoord.latitude();
            coord.longitude = qcoord.longitude();
            lineString.coordinates.push_back(coord);
        }
        params.geometry = Geometry(lineString);
        params.authorization = login_token.toStdString();
        //-- Create flight plan
        _shared.client()->flight_plans().create_by_polygon(params, [this, isAlive](const FlightPlans::Create::Result& result) {
            if (!isAlive.lock()) return;
            if (_state != State::FlightUpload) return;
            if (result) {
                _flightPlan = QString::fromStdString(result.value().id);
                qCDebug(AirMapManagerLog) << "Flight plan created:" << _flightPlan;
                _state = State::FlightPolling;
                _pollBriefing();
            } else {
                QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
                emit error("Flight Plan creation failed", QString::fromStdString(result.error().message()), description);
            }
        });
    });
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::_updateFlightPlan()
{
    //-- TODO: This is broken as the parameters for updating the plan have
    //   little to do with those used when creating it.

    qCDebug(AirMapManagerLog) << "Updating flight plan";
    _state = State::FlightUpdate;
    std::weak_ptr<LifetimeChecker> isAlive(_instance);
    _shared.doRequestWithLogin([this, isAlive](const QString& login_token) {
        if (!isAlive.lock()) return;
        if (_state != State::FlightUpdate) return;
        FlightPlans::Update::Parameters params;
        params.authorization  = login_token.toStdString();
        params.flight_plan.id = _flightPlan.toStdString();
        params.flight_plan.pilot.id = _pilotID.toStdString();
        params.flight_plan.altitude_agl.max = _flight.maxAltitude;
        params.flight_plan.buffer = 2.f;
        params.flight_plan.takeoff.latitude  = _flight.takeoffCoord.latitude();
        params.flight_plan.takeoff.longitude = _flight.takeoffCoord.longitude();
        /*

        TODO: Convert this to fucking boost

        quint64 start = _flightStartTime.toUTC().toMSecsSinceEpoch();
        quint64 end   = _flightEndTime.toUTC().toMSecsSinceEpoch();

        */
        params.flight_plan.start_time   = Clock::universal_time() + Minutes{5};
        params.flight_plan.end_time     = Clock::universal_time() + Hours{2};
        //-- Rules
        /*
        AirMapRulesetsManager* pRulesMgr = dynamic_cast<AirMapRulesetsManager*>(qgcApp()->toolbox()->airspaceManager()->ruleSets());
        if(pRulesMgr) {
            foreach(QString ruleset, pRulesMgr->rulesetsIDs()) {
                params.flight_plan.rulesets.push_back(ruleset.toStdString());
            }
        }
        */
        //-- Geometry: LineString
        Geometry::LineString lineString;
        for (const auto& qcoord : _flight.coords) {
            Geometry::Coordinate coord;
            coord.latitude  = qcoord.latitude();
            coord.longitude = qcoord.longitude();
            lineString.coordinates.push_back(coord);
        }
        params.flight_plan.geometry = Geometry(lineString);
        //-- Update flight plan
        _shared.client()->flight_plans().update(params, [this, isAlive](const FlightPlans::Update::Result& result) {
            if (!isAlive.lock()) return;
            if (_state != State::FlightUpdate) return;
            if (result) {
                qCDebug(AirMapManagerLog) << "Flight plan updated:" << _flightPlan;
                _state = State::FlightPolling;
                _pollBriefing();
            } else {
                QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
                emit error("Flight Plan creation failed", QString::fromStdString(result.error().message()), description);
            }
        });
    });
}

//-----------------------------------------------------------------------------
static bool
adv_sort(QObject* a, QObject* b)
{
    AirMapAdvisory* aa = qobject_cast<AirMapAdvisory*>(a);
    AirMapAdvisory* bb = qobject_cast<AirMapAdvisory*>(b);
    if(!aa || !bb) return false;
    return (int)aa->color() > (int)bb->color();
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::_pollBriefing()
{
    if (_state != State::FlightPolling) {
        qCWarning(AirMapManagerLog) << "AirMapFlightPlanManager::_pollBriefing: not in polling state";
        return;
    }
    FlightPlans::RenderBriefing::Parameters params;
    params.authorization = _shared.loginToken().toStdString();
    params.id = _flightPlan.toStdString();
    std::weak_ptr<LifetimeChecker> isAlive(_instance);
    _shared.client()->flight_plans().render_briefing(params, [this, isAlive](const FlightPlans::RenderBriefing::Result& result) {
        if (!isAlive.lock()) return;
        if (_state != State::FlightPolling) return;
        if (result) {
            const FlightPlan::Briefing& briefing = result.value();
            qCDebug(AirMapManagerLog) << "Flight polling/briefing response";
            //-- Collect advisories
            _valid = false;
            _advisories.clearAndDeleteContents();
            const std::vector<Status::Advisory> advisories = briefing.airspace.advisories;
            _airspaceColor = (AirspaceAdvisoryProvider::AdvisoryColor)(int)briefing.airspace.color;
            for (const auto& advisory : advisories) {
                AirMapAdvisory* pAdvisory = new AirMapAdvisory(this);
                pAdvisory->_id          = QString::fromStdString(advisory.airspace.id());
                pAdvisory->_name        = QString::fromStdString(advisory.airspace.name());
                pAdvisory->_type        = (AirspaceAdvisory::AdvisoryType)(int)advisory.airspace.type();
                pAdvisory->_color       = (AirspaceAdvisoryProvider::AdvisoryColor)(int)advisory.color;
                _advisories.append(pAdvisory);
                qCDebug(AirMapManagerLog) << "Adding briefing advisory" << pAdvisory->name();
            }
            //-- Sort in order of color (priority)
            _advisories.beginReset();
            std::sort(_advisories.objectList()->begin(), _advisories.objectList()->end(), adv_sort);
            _advisories.endReset();
            _valid = true;
            emit advisoryChanged();
            //-- Evaluate briefing status
            bool rejected = false;
            bool accepted = false;
            bool pending  = false;
            for (const auto& authorization : briefing.evaluation.authorizations) {
                switch (authorization.status) {
                case Evaluation::Authorization::Status::accepted:
                case Evaluation::Authorization::Status::accepted_upon_submission:
                    accepted = true;
                    break;
                case Evaluation::Authorization::Status::rejected:
                case Evaluation::Authorization::Status::rejected_upon_submission:
                    rejected = true;
                    break;
                case Evaluation::Authorization::Status::pending:
                    pending = true;
                    break;
                }
            }
            if (briefing.evaluation.authorizations.size() == 0) {
                // If we don't get any authorizations, we assume it's accepted
                accepted = true;
            }
            qCDebug(AirMapManagerLog) << "Flight approval: accepted=" << accepted << "rejected" << rejected << "pending" << pending;
            if ((rejected || accepted) && !pending) {
                if (rejected) { // rejected has priority
                    _flightPermitStatus = AirspaceFlightPlanProvider::PermitRejected;
                } else {
                    _flightPermitStatus = AirspaceFlightPlanProvider::PermitAccepted;
                }
                emit flightPermitStatusChanged();
                _state = State::Idle;
            } else if(pending) {
                //-- Wait until we send the next polling request
                _pollTimer.setSingleShot(true);
                _pollTimer.start(2000);
            }
        } else {
            QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
            emit error("Brief Request failed",
                    QString::fromStdString(result.error().message()), description);
            _state = State::Idle;
        }
    });
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::_deleteFlightPlan()
{
    if(_flightPlan.isEmpty()) {
        qCDebug(AirMapManagerLog) << "Delete non existing flight plan";
        return;
    }
    qCDebug(AirMapManagerLog) << "Deleting flight plan";
    _state = State::FlightDelete;
    std::weak_ptr<LifetimeChecker> isAlive(_instance);
    FlightPlans::Delete::Parameters params;
    params.authorization = _shared.loginToken().toStdString();
    params.id = _flightPlan.toStdString();
    //-- Delete flight plan
    _shared.client()->flight_plans().delete_(params, [this, isAlive](const FlightPlans::Delete::Result& result) {
        if (!isAlive.lock()) return;
        if (_state != State::FlightDelete) return;
        if (result) {
            _flightPlan.clear();
            qCDebug(AirMapManagerLog) << "Flight plan deleted";
            _state = State::Idle;
        } else {
            QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
            emit error("Flight Plan deletion failed", QString::fromStdString(result.error().message()), description);
        }
    });
}

//-----------------------------------------------------------------------------
void
AirMapFlightPlanManager::_missionChanged()
{
    //-- Creating a new flight plan?
    if(_createPlan) {
        _createPlan = false;
        _createFlightPlan();
    }
    //-- Plan is being modified
    // _updateFlightPlan();
}
