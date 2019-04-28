/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @author Pritam Ghanghas <pritam.ghanghas@gmail.com>

#ifndef ArduRoverFirmwarePlugin_H
#define ArduRoverFirmwarePlugin_H

#include "APMFirmwarePlugin.h"

class APMRoverMode : public APMCustomMode
{
public:
    enum Mode {
        MANUAL          = 0,
        ACRO            = 1,
        STEERING        = 3,
        HOLD            = 4,
        LOITER          = 5,
        FOLLOW          = 6,
        SIMPLE          = 7,
        AUTO            = 10,
        RTL             = 11,
        SMART_RTL       = 12,
        GUIDED          = 15,
        INITIALIZING    = 16,
    };
    static const int modeCount = 17;

    APMRoverMode(uint32_t mode, bool settable);
};

class ArduRoverFirmwarePlugin : public APMFirmwarePlugin
{
    Q_OBJECT
    
public:
    ArduRoverFirmwarePlugin(void);

    // Overrides from FirmwarePlugin
    QString pauseFlightMode                         (void) const override { return QString("Hold"); }
    void    guidedModeChangeAltitude                (Vehicle* vehicle, double altitudeChange) override;
    int     remapParamNameHigestMinorVersionNumber  (int majorVersionNumber) const override;
    const   FirmwarePlugin::remapParamNameMajorVersionMap_t& paramNameRemapMajorVersionMap(void) const override { return _remapParamName; }
    bool    supportsNegativeThrust                  (void) override;
    QString offlineEditingParamFile                 (Vehicle* vehicle) override { Q_UNUSED(vehicle); return QStringLiteral(":/FirmwarePlugin/APM/Rover.OfflineEditing.params"); }

private:
    static bool _remapParamNameIntialized;
    static FirmwarePlugin::remapParamNameMajorVersionMap_t  _remapParamName;
};

#endif
