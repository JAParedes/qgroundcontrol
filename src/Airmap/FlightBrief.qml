import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtQuick.Controls.Styles  1.4
import QtQuick.Dialogs          1.2
import QtQml                    2.2

import QGroundControl                   1.0
import QGroundControl.Airmap            1.0
import QGroundControl.Airspace          1.0
import QGroundControl.Controls          1.0
import QGroundControl.Palette           1.0
import QGroundControl.ScreenTools       1.0
import QGroundControl.SettingsManager   1.0

Item {
    id:                 _root
    implicitHeight:     briefRootCol.height
    implicitWidth:      briefRootCol.width
    property real baseHeight:  ScreenTools.defaultFontPixelHeight * 22
    property real baseWidth:   ScreenTools.defaultFontPixelWidth  * 40
    Column {
        id:             briefRootCol
        spacing:        ScreenTools.defaultFontPixelHeight * 0.25
        Rectangle {
            color:          qgcPal.windowShade
            anchors.right:  parent.right
            anchors.left:   parent.left
            height:         briefLabel.height + ScreenTools.defaultFontPixelHeight
            QGCLabel {
                id:             briefLabel
                text:           qsTr("Flight Brief")
                font.pointSize: ScreenTools.mediumFontPointSize
                font.family:    ScreenTools.demiboldFontFamily
                anchors.centerIn: parent
            }
        }
        Item { width: 1; height: ScreenTools.defaultFontPixelHeight * 0.5; }
        Flickable {
            clip:           true
            width:          baseWidth
            height:         baseHeight - buttonRow.height - ScreenTools.defaultFontPixelHeight
            contentHeight:  briefCol.height
            flickableDirection: Flickable.VerticalFlick
            Column {
                id:                 briefCol
                spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                anchors.right:      parent.right
                anchors.left:       parent.left
                QGCLabel {
                    text:           qsTr("Authorizations")
                }
                Rectangle {
                    color:          qgcPal.windowShade
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    height:         authCol.height + ScreenTools.defaultFontPixelHeight
                    Column {
                        id:                 authCol
                        spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                        anchors.margins:    ScreenTools.defaultFontPixelWidth
                        anchors.right:      parent.right
                        anchors.left:       parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        QGCLabel {
                            text:           qsTr("Federal Aviation Administration")
                            visible:        _flightPermit !== AirspaceFlightPlanProvider.PermitNone
                        }
                        QGCLabel {
                            text:           qsTr("Automatic authorization to fly in controlled airspace")
                            visible:        _flightPermit !== AirspaceFlightPlanProvider.PermitNone
                            font.pointSize: ScreenTools.smallFontPointSize
                        }
                        Rectangle {
                            anchors.right:      parent.right
                            anchors.left:       parent.left
                            height:             label.height + (ScreenTools.defaultFontPixelHeight * 0.5)
                            color: {
                                if(_flightPermit == AirspaceFlightPlanProvider.PermitPending)
                                    return _colorOrange
                                if(_flightPermit == AirspaceFlightPlanProvider.PermitAccepted)
                                    return _colorGreen
                                if(_flightPermit == AirspaceFlightPlanProvider.PermitRejected)
                                    return _colorRed
                                return _colorGray
                            }
                            QGCLabel {
                                id:     label
                                color:  _colorWhite
                                text: {
                                    if(_flightPermit === AirspaceFlightPlanProvider.PermitPending)
                                        return qsTr("Authorization Pending")
                                    if(_flightPermit === AirspaceFlightPlanProvider.PermitAccepted)
                                        return qsTr("Authorization Accepted")
                                    if(_flightPermit === AirspaceFlightPlanProvider.PermitRejected)
                                        return qsTr("Authorization Rejected")
                                    return qsTr("Authorization Unknown")
                                }
                                anchors.centerIn: parent
                            }
                        }
                    }
                }
                Item { width: 1; height: ScreenTools.defaultFontPixelHeight * 0.25; }
                QGCLabel {
                    text:           qsTr("Rules & Compliance")
                    visible:        hasBriefRules()
                }
                ExclusiveGroup { id: ruleGroup }
                ComplianceRules {
                    text:           qsTr("Rules you may be violating")
                    rules:          violationRules
                    visible:        violationRules && violationRules.count
                    color:          _colorRed
                    exclusiveGroup: ruleGroup
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    property var violationRules: QGroundControl.airspaceManager.flightPlan.rulesViolation
                }
                ComplianceRules {
                    text:           qsTr("Rules needing more information")
                    rules:          infoRules
                    color:          _colorOrange
                    visible:        infoRules && infoRules.count
                    exclusiveGroup: ruleGroup
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    property var infoRules: QGroundControl.airspaceManager.flightPlan.rulesInfo
                }
                ComplianceRules {
                    text:           qsTr("Rules you should review")
                    rules:          reviewRules
                    color:          _colorYellow
                    visible:        reviewRules && reviewRules.count
                    exclusiveGroup: ruleGroup
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    property var reviewRules: QGroundControl.airspaceManager.flightPlan.rulesReview
                }
                ComplianceRules {
                    text:           qsTr("Rules you are following")
                    rules:          followRules
                    color:          _colorGreen
                    visible:        followRules && followRules.count
                    exclusiveGroup: ruleGroup
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    property var followRules: QGroundControl.airspaceManager.flightPlan.rulesFollowing
                }
            }
        }
        //-------------------------------------------------------------
        //-- File Flight Plan or Close
        Item { width: 1; height: ScreenTools.defaultFontPixelHeight; }
        Row {
            id:         buttonRow
            spacing: ScreenTools.defaultFontPixelWidth
            anchors.horizontalCenter: parent.horizontalCenter
            QGCButton {
                text:           qsTr("Update Plan")
                backRadius:     4
                heightFactor:   0.3333
                showBorder:     true
                enabled:        _flightPermit !== AirspaceFlightPlanProvider.PermitNone && _dirty
                visible:        planView
                width:          ScreenTools.defaultFontPixelWidth * 12
                onClicked: {
                    //-- TODO: Update Plan
                    mainWindow.enableToolbar()
                    rootLoader.sourceComponent = null
                }
            }
            QGCButton {
                text:           qsTr("Submit Plan")
                backRadius:     4
                heightFactor:   0.3333
                showBorder:     true
                enabled:        _flightPermit !== AirspaceFlightPlanProvider.PermitNone
                width:          ScreenTools.defaultFontPixelWidth * 12
                visible:        planView
                onClicked: {
                    //-- TODO: File Plan
                    mainWindow.enableToolbar()
                    rootLoader.sourceComponent = null
                }
            }
            QGCButton {
                text:           qsTr("Close")
                backRadius:     4
                heightFactor:   0.3333
                showBorder:     true
                width:          ScreenTools.defaultFontPixelWidth * 12
                onClicked: {
                    mainWindow.enableToolbar()
                    rootLoader.sourceComponent = null
                }
            }
        }
    }
}
