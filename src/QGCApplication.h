/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QApplication>
#include <QTimer>
#include <QElapsedTimer>
#include <QMap>
#include <QSet>
#include <QMetaMethod>
#include <QMetaObject>

// These private headers are require to implement the signal compress support below
#include <private/qthread_p.h>
#include <private/qobject_p.h>

#include "LinkConfiguration.h"
#include "LinkManager.h"
#include "MAVLinkProtocol.h"
#include "FlightMapSettings.h"
#include "FirmwarePluginManager.h"
#include "MultiVehicleManager.h"
#include "JoystickManager.h"
#include "AudioOutput.h"
#include "UASMessageHandler.h"
#include "FactSystem.h"
#include "GPSRTKFactGroup.h"

#ifdef QGC_RTLAB_ENABLED
#include "OpalLink.h"
#endif

// Work around circular header includes
class QQmlApplicationEngine;
class QGCSingleton;
class QGCToolbox;
class QGCFileDownload;

/**
 * @brief The main application and management class.
 *
 * This class is started by the main method and provides
 * the central management unit of the groundstation application.
 *
 * Needs QApplication base to support QtCharts module. This way
 * we avoid application crashing on 5.12 when using the module.
 *
 * Note: `lastWindowClosed` will be sent by MessageBox popups and other
 * dialogs, that are spawned in QML, when they are closed
**/
class QGCApplication : public QApplication
{
    Q_OBJECT
public:
    QGCApplication(int &argc, char* argv[], bool unitTesting);
    ~QGCApplication();

    /// @brief Sets the persistent flag to delete all settings the next time QGroundControl is started.
    void deleteAllSettingsNextBoot(void);

    /// @brief Clears the persistent flag to delete all settings the next time QGroundControl is started.
    void clearDeleteAllSettingsNextBoot(void);

    /// @brief Returns true if unit tests are being run
    bool runningUnitTests(void) { return _runningUnitTests; }

    /// @brief Returns true if Qt debug output should be logged to a file
    bool logOutput(void) { return _logOutput; }

    /// Used to report a missing Parameter. Warning will be displayed to user. Method may be called
    /// multiple times.
    void reportMissingParameter(int componentId, const QString& name);

    /// Show non-modal vehicle message to the user
    Q_SLOT void showVehicleMessage(const QString& message);

    /// Show modal application message to the user
    Q_SLOT void showAppMessage(const QString& message, const QString& title = QString());

    /// @return true: Fake ui into showing mobile interface
    bool fakeMobile(void) const { return _fakeMobile; }

    // Still working on getting rid of this and using dependency injection instead for everything
    QGCToolbox* toolbox(void) { return _toolbox; }

    /// Do we have Bluetooth Support?
    bool isBluetoothAvailable() { return _bluetoothAvailable; }

    /// Is Internet available?
    bool isInternetAvailable();

    FactGroup* gpsRtkFactGroup(void)  { return _gpsRtkFactGroup; }

    QTranslator& qgcJSONTranslator(void) { return _qgcTranslatorJSON; }

    static QString cachedParameterMetaDataFile(void);
    static QString cachedAirframeMetaDataFile(void);

    void            setLanguage();
    QQuickItem*     mainRootWindow();

    uint64_t        msecsSinceBoot(void) { return _msecsElapsedTime.elapsed(); }

public slots:
    /// You can connect to this slot to show an information message box from a different thread.
    void informationMessageBoxOnMainThread(const QString& title, const QString& msg);

    /// You can connect to this slot to show a warning message box from a different thread.
    void warningMessageBoxOnMainThread(const QString& title, const QString& msg);

    /// You can connect to this slot to show a critical message box from a different thread.
    void criticalMessageBoxOnMainThread(const QString& title, const QString& msg);

    void showSetupView();

    void qmlAttemptWindowClose();

    /// Save the specified telemetry Log
    void saveTelemetryLogOnMainThread(QString tempLogfile);

    /// Check that the telemetry save path is set correctly
    void checkTelemetrySavePathOnMainThread();

    /// Get current language
    const QLocale getCurrentLanguage() { return _locale; }

signals:
    /// This is connected to MAVLinkProtocol::checkForLostLogFiles. We signal this to ourselves to call the slot
    /// on the MAVLinkProtocol thread;
    void checkForLostLogFiles   ();

    void languageChanged        (const QLocale locale);

public:
    // Although public, these methods are internal and should only be called by UnitTest code

    /// @brief Perform initialize which is common to both normal application running and unit tests.
    ///         Although public should only be called by main.
    void _initCommon();

    /// @brief Initialize the application for normal application boot. Or in other words we are not going to run
    ///         unit tests. Although public should only be called by main.
    bool _initForNormalAppBoot();

    /// @brief Initialize the application for normal application boot. Or in other words we are not going to run
    ///         unit tests. Although public should only be called by main.
    bool _initForUnitTests();

    static QGCApplication*  _app;   ///< Our own singleton. Should be reference directly by qgcApp

    bool    isErrorState()  { return _error; }

public:
    // Although public, these methods are internal and should only be called by UnitTest code

    /// Shutdown the application object
    void _shutdown();

    bool _checkTelemetrySavePath(bool useMessageBox);

private slots:
    void _missingParamsDisplay          (void);
    void _currentVersionDownloadFinished(QString remoteFile, QString localFile);
    void _currentVersionDownloadError   (QString errorMsg);
    bool _parseVersionText              (const QString& versionString, int& majorVersion, int& minorVersion, int& buildVersion);
    void _onGPSConnect                  (void);
    void _onGPSDisconnect               (void);
    void _gpsSurveyInStatus             (float duration, float accuracyMM,  double latitude, double longitude, float altitude, bool valid, bool active);
    void _gpsNumSatellites              (int numSatellites);
    void _showDelayedAppMessages        (void);

private:
    QObject*    _rootQmlObject          ();
    void        _checkForNewVersion     ();
    void        _exitWithError          (QString errorMessage);


    bool                        _runningUnitTests;                                  ///< true: running unit tests, false: normal app
    static const int            _missingParamsDelayedDisplayTimerTimeout = 1000;    ///< Timeout to wait for next missing fact to come in before display
    QTimer                      _missingParamsDelayedDisplayTimer;                  ///< Timer use to delay missing fact display
    QList<QPair<int,QString>>   _missingParams;                                     ///< List of missing parameter component id:name

    QQmlApplicationEngine* _qmlAppEngine        = nullptr;
    bool                _logOutput              = false;    ///< true: Log Qt debug output to file
    bool				_fakeMobile             = false;    ///< true: Fake ui into displaying mobile interface
    bool                _settingsUpgraded       = false;    ///< true: Settings format has been upgrade to new version
    int                 _majorVersion           = 0;
    int                 _minorVersion           = 0;
    int                 _buildVersion           = 0;
    QGCFileDownload*    _currentVersionDownload = nullptr;
    GPSRTKFactGroup*    _gpsRtkFactGroup        = nullptr;
    QGCToolbox*         _toolbox                = nullptr;
    QQuickItem*         _mainRootWindow         = nullptr;
    bool                _bluetoothAvailable     = false;
    QTranslator         _qgcTranslatorSourceCode;           ///< translations for source code C++/Qml
    QTranslator         _qgcTranslatorJSON;                 ///< translations for json files
    QTranslator         _qgcTranslatorQtLibs;               ///< tranlsations for Qt libraries
    QLocale             _locale;
    bool                _error                  = false;
    QElapsedTimer       _msecsElapsedTime;

    QList<QPair<QString /* title */, QString /* message */>> _delayedAppMessages;

    static const char* _settingsVersionKey;             ///< Settings key which hold settings version
    static const char* _deleteAllSettingsKey;           ///< If this settings key is set on boot, all settings will be deleted

    /// Unit Test have access to creating and destroying singletons
    friend class UnitTest;

private:
    /*! Keeps a list of singal indices for one or more meatobject classes.
     * The indices are signal indices as given by QMetaCallEvent.signalId.
     * On Qt 5, those do *not* match QMetaObject::methodIndex since they
     * exclude non-signal methods. */
    class SignalList {
        Q_DISABLE_COPY(SignalList)
        typedef QMap<const QMetaObject *, QSet<int> > T;
        T m_data;
        /*! Returns a signal index that is can be compared to QMetaCallEvent.signalId. */
        static int signalIndex(const QMetaMethod & method) {
            Q_ASSERT(method.methodType() == QMetaMethod::Signal);
    #if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
            int index = -1;
            const QMetaObject * mobj = method.enclosingMetaObject();
            for (int i = 0; i <= method.methodIndex(); ++i) {
                if (mobj->method(i).methodType() != QMetaMethod::Signal) continue;
                ++ index;
            }
            return index;
    #else
            return method.methodIndex();
    #endif
        }
    public:
        SignalList() {}
        void add(const QMetaMethod & method) {
            m_data[method.enclosingMetaObject()].insert(signalIndex(method));
        }
        void remove(const QMetaMethod & method) {
            T::iterator it = m_data.find(method.enclosingMetaObject());
            if (it != m_data.end()) {
                it->remove(signalIndex(method));
                if (it->empty()) m_data.erase(it);
            }
        }
        bool contains(const QMetaObject * metaObject, int signalId) {
            T::const_iterator it = m_data.find(metaObject);
            return it != m_data.end() && it.value().contains(signalId);
        }
    };

    SignalList m_compressedSignals;

public:
    void addCompressedSignal(const QMetaMethod & method) { m_compressedSignals.add(method); }
    void removeCompressedSignal(const QMetaMethod & method) { m_compressedSignals.remove(method); }

private:
    struct EventHelper : private QEvent {
        static void clearPostedFlag(QEvent * ev) {
            (&static_cast<EventHelper*>(ev)->t)[1] &= ~0x8001; // Hack to clear QEvent::posted
        }
    };

    bool compressEvent(QEvent *event, QObject *receiver, QPostEventList *postedEvents) {
        if (event->type() != QEvent::MetaCall)
            return QApplication::compressEvent(event, receiver, postedEvents);

        QMetaCallEvent *mce = static_cast<QMetaCallEvent*>(event);

        if (mce->sender() && !m_compressedSignals.contains(mce->sender()->metaObject(), mce->signalId())) {
            return false;
        }

        for (QPostEventList::iterator it = postedEvents->begin(); it != postedEvents->end(); ++it) {
            QPostEvent &cur = *it;
            if (cur.receiver != receiver || cur.event == 0 || cur.event->type() != event->type())
                continue;
            QMetaCallEvent *cur_mce = static_cast<QMetaCallEvent*>(cur.event);
            if (cur_mce->sender() != mce->sender() || cur_mce->signalId() != mce->signalId() ||
                    cur_mce->id() != mce->id())
                continue;
            if (true) {
              /* Keep The Newest Call */
              // We can't merely qSwap the existing posted event with the new one, since QEvent
              // keeps track of whether it has been posted. Deletion of a formerly posted event
              // takes the posted event list mutex and does a useless search of the posted event
              // list upon deletion. We thus clear the QEvent::posted flag before deletion.
              EventHelper::clearPostedFlag(cur.event);
              delete cur.event;
              cur.event = event;
            } else {
              /* Keep the Oldest Call */
              delete event;
            }
            return true;
        }
        return false;
    }



};

/// @brief Returns the QGCApplication object singleton.
QGCApplication* qgcApp(void);
