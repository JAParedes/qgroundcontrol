/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QObject>

#include "MissionController.h"
#include "GeoFenceController.h"
#include "RallyPointController.h"
#include "Vehicle.h"
#include "MultiVehicleManager.h"
#include "QGCLoggingCategory.h"

Q_DECLARE_LOGGING_CATEGORY(PlanMasterControllerLog)

/// Master controller for mission, fence, rally
class PlanMasterController : public QObject
{
    Q_OBJECT
    
public:
    PlanMasterController(QObject* parent = NULL);
    ~PlanMasterController();
    
    Q_PROPERTY(MissionController*       missionController       READ missionController      CONSTANT)
    Q_PROPERTY(GeoFenceController*      geoFenceController      READ geoFenceController     CONSTANT)
    Q_PROPERTY(RallyPointController*    rallyPointController    READ rallyPointController   CONSTANT)

    Q_PROPERTY(Vehicle*     controllerVehicle   MEMBER _controllerVehicle               CONSTANT)
    Q_PROPERTY(bool         offline             READ offline                            NOTIFY offlineEditingChanged)   ///< true: controller is not connected to an active vehicle
    Q_PROPERTY(bool         containsItems       READ containsItems                      NOTIFY containsItemsChanged)    ///< true: Elemement is non-empty
    Q_PROPERTY(bool         syncInProgress      READ syncInProgress                     NOTIFY syncInProgressChanged)   ///< true: Information is currently being saved/sent, false: no active save/send in progress
    Q_PROPERTY(bool         dirty               READ dirty              WRITE setDirty  NOTIFY dirtyChanged)            ///< true: Unsaved/sent changes are present, false: no changes since last save/send
    Q_PROPERTY(QString      fileExtension       READ fileExtension                      CONSTANT)                       ///< File extension for missions
    Q_PROPERTY(QString      kmlFileExtension    READ kmlFileExtension                   CONSTANT)
    ///< kml file extension for missions
    Q_PROPERTY(QStringList  loadNameFilters     READ loadNameFilters                    CONSTANT)                       ///< File filter list loading plan files
    Q_PROPERTY(QStringList  saveNameFilters     READ saveNameFilters                    CONSTANT)                       ///< File filter list saving plan files
    Q_PROPERTY(QStringList  saveKmlFilters      READ saveKmlFilters                     CONSTANT)                       ///< File filter list saving KML files

    /// Should be called immediately upon Component.onCompleted.
    ///     @param editMode true: controller being used in Plan view, false: controller being used in Fly view
    Q_INVOKABLE virtual void start(bool editMode);

    /// Starts the controller using a single static active vehicle. Will not track global active vehicle changes.
    Q_INVOKABLE virtual void startStaticActiveVehicle(Vehicle* vehicle);

    /// Sends a plan to the specified file
    ///     @param[in] vehicle Vehicle we are sending a plan to
    ///     @param[in] filename Plan file to load
    static void sendPlanToVehicle(Vehicle* vehicle, const QString& filename);

    Q_INVOKABLE void loadFromVehicle(void);
    Q_INVOKABLE void sendToVehicle(void);
    Q_INVOKABLE void loadFromFile(const QString& filename);
    Q_INVOKABLE void saveToFile(const QString& filename);
    Q_INVOKABLE void saveToKml(const QString& filename);
    Q_INVOKABLE void removeAll(void);                       ///< Removes all from controller only, synce required to remove from vehicle
    Q_INVOKABLE void removeAllFromVehicle(void);            ///< Removes all from vehicle and controller

    MissionController*      missionController(void)     { return &_missionController; }
    GeoFenceController*     geoFenceController(void)    { return &_geoFenceController; }
    RallyPointController*   rallyPointController(void)  { return &_rallyPointController; }

    bool        offline         (void) const { return _offline; }
    bool        containsItems   (void) const;
    bool        syncInProgress  (void) const { return _syncInProgress; }
    bool        dirty           (void) const;
    void        setDirty        (bool dirty);
    QString     fileExtension   (void) const;
    QString     kmlFileExtension(void) const;
    QStringList loadNameFilters (void) const;
    QStringList saveNameFilters (void) const;
    QStringList saveKmlFilters  (void) const;

    QJsonDocument saveToJson    ();

    Vehicle* controllerVehicle(void) { return _controllerVehicle; }
    Vehicle* managerVehicle(void) { return _managerVehicle; }

signals:
    void containsItemsChanged   (bool containsItems);
    void syncInProgressChanged  (bool syncInProgress);
    void dirtyChanged           (bool dirty);
    void vehicleChanged         (Vehicle* vehicle);
    void offlineEditingChanged  (bool offlineEditing);

private slots:
    void _activeVehicleChanged(Vehicle* activeVehicle);
    void _loadMissionComplete(void);
    void _loadGeoFenceComplete(void);
    void _loadRallyPointsComplete(void);
    void _sendMissionComplete(void);
    void _sendGeoFenceComplete(void);
    void _sendRallyPointsComplete(void);

private:
    void _showPlanFromManagerVehicle(void);

    MultiVehicleManager*    _multiVehicleMgr;
    Vehicle*                _controllerVehicle;
    Vehicle*                _managerVehicle;
    bool                    _editMode;
    bool                    _offline;
    MissionController       _missionController;
    GeoFenceController      _geoFenceController;
    RallyPointController    _rallyPointController;
    bool                    _loadGeoFence;
    bool                    _loadRallyPoints;
    bool                    _sendGeoFence;
    bool                    _sendRallyPoints;
    bool                    _syncInProgress;

    static const int    _planFileVersion;
    static const char*  _planFileType;
    static const char*  _jsonMissionObjectKey;
    static const char*  _jsonGeoFenceObjectKey;
    static const char*  _jsonRallyPointsObjectKey;
};
