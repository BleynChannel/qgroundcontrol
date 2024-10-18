/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QGroundControl
import QGroundControl.Palette
import QGroundControl.FactSystem
import QGroundControl.FactControls
import QGroundControl.Controls
import QGroundControl.ScreenTools

SettingsPage {
    property var    _settingsManager:            QGroundControl.settingsManager
    property var    _videoManager:              QGroundControl.videoManager
    property var    _videoSettings:             _settingsManager.videoSettings
    property string _videoSource:               _videoSettings.videoSource.rawValue
    property bool   _isGST:                     _videoManager.gstreamerEnabled
    property bool   _isStreamSource:            _videoManager.isStreamSource
    property bool   _isUDP264:                  _isStreamSource && (_videoSource === _videoSettings.udp264VideoSource)
    property bool   _isUDP265:                  _isStreamSource && (_videoSource === _videoSettings.udp265VideoSource)
    property bool   _isRTSP:                    _isStreamSource && (_videoSource === _videoSettings.rtspVideoSource)
    property bool   _isTCP:                     _isStreamSource && (_videoSource === _videoSettings.tcpVideoSource)
    property bool   _isMPEGTS:                  _isStreamSource && (_videoSource === _videoSettings.mpegtsVideoSource)
    property bool   _videoAutoStreamConfig:     _videoManager.autoStreamConfigured
    property real   _urlFieldWidth:             ScreenTools.defaultFontPixelWidth * 25
    property bool   _requiresUDPPort:           _isUDP264 || _isUDP265 || _isMPEGTS

    SettingsGroupLayout {
        Layout.fillWidth:   true
        heading:            qsTr("Video Source")
        headingDescription: _videoAutoStreamConfig ? qsTr("Mavlink camera stream is automatically configured") : ""
        enabled:            !_videoAutoStreamConfig

		LabelledFactComboBox {
            Layout.fillWidth:   true
            label:              qsTr("Source")
            indexModel:         false
            fact:               _videoSettings.videoSource
            visible:            fact.visible
        }
    }

    SettingsGroupLayout {
		id: connectionGroup
        Layout.fillWidth:   true
        heading:            qsTr("Connection")
        visible:            !_videoAutoStreamConfig && (_isTCP || _isRTSP | _requiresUDPPort)

		property list<string> rtspUrls //TODO: Remove this and use _videoReceiver.uris

		onRtspUrlsChanged: {
			_videoSettings.rtspUrl.value = rtspUrls.length > 0 ? rtspUrls.join(';') : ""
		}

		Component.onCompleted: {
			var url = _videoSettings.rtspUrl.valueString
			connectionGroup.rtspUrls = url.length > 0 ? url.split(';') : []
		}

		function changeRtspUrl(index, value) {
			if (index >= rtspUrls.length) {
				rtspUrls.push(value)
			} else {
				rtspUrls[index] = value
			}
		}

		function removeRtspUrl(index) {
			rtspUrls.splice(index, 1)
		}

		Repeater {
            model: connectionGroup.rtspUrls
            
            delegate: RowLayout {
				required property int index
				required property string modelData

                Layout.fillWidth:   true

                QGCLabel {
                    Layout.fillWidth:   true
                    text:               modelData
                }
                QGCColoredImage {
                    height:                 ScreenTools.minTouchPixels
                    width:                  height
                    sourceSize.height:      height
                    fillMode:               Image.PreserveAspectFit
                    smooth:                 true
                    color:                  qgcPalEdit.text
                    source:                 "/res/pencil.svg"

                    QGCPalette {
                        id: qgcPalEdit
                        colorGroupEnabled: parent.enabled
                    }

                    QGCMouseArea {
                        fillItem: parent
                        onClicked: {
                            sourceDialogComponent.createObject(mainWindow, {
								changeRtspUrl: connectionGroup.changeRtspUrl,
								index: index,
								editing: true,
								editingUrl: modelData
							}).open()
                        }
                    }
                }
                QGCColoredImage {
                    height:                 ScreenTools.minTouchPixels
                    width:                  height
                    sourceSize.height:      height
                    fillMode:               Image.PreserveAspectFit
                    mipmap:                 true
                    smooth:                 true
                    color:                  qgcPalDelete.text
                    source:                 "/res/TrashDelete.svg"

                    QGCPalette {
                        id: qgcPalDelete
                        colorGroupEnabled: parent.enabled
                    }

                    QGCMouseArea {
                        fillItem:   parent
                        onClicked:  mainWindow.showMessageDialog(
                                        "Delete Source", 
                                        qsTr("Are you sure you want to delete '%1'?").arg(modelData), 
                                        Dialog.Ok | Dialog.Cancel, 
                                        function () {
											connectionGroup.removeRtspUrl(index)
                                        })
                    }
                }
            }
        }

		LabelledButton {
            label:      		"Add new RTSP URL" //! qsTr
            buttonText: 		qsTr("Add")
            Layout.fillWidth:   true
			visible:            _isRTSP && _videoSettings.rtspUrl.visible

            onClicked: {
				sourceDialogComponent.createObject(mainWindow, {
					changeRtspUrl: connectionGroup.changeRtspUrl,
					index: connectionGroup.rtspUrls.length,
					editing: false,
					editingUrl: ""
				}).open()
            }
        }

        LabelledFactTextField {
            Layout.fillWidth:           true
            label:                      qsTr("TCP URL")
            textFieldPreferredWidth:    _urlFieldWidth
            fact:                       _videoSettings.tcpUrl
            visible:                    _isTCP && _videoSettings.tcpUrl.visible
        }

        LabelledFactTextField {
            Layout.fillWidth:   true
            label:              qsTr("UDP Port")
            fact:               _videoSettings.udpPort
            visible:            _requiresUDPPort && _videoSettings.udpPort.visible
        }
    }

	Component {
        id: sourceDialogComponent

        QGCPopupDialog {
            title:          editing ? "Edit Video Source" : "Add New Video Source" //! qsTr
            buttons:        Dialog.Save | Dialog.Cancel
            acceptAllowed:  sourceField.text !== ""

            property var 	changeRtspUrl
			property int	index
			property bool	editing
			property string	editingUrl

            onAccepted: {
                if (changeRtspUrl) {
					changeRtspUrl(index, sourceField.text)
				}
            }

            ColumnLayout {
                spacing: ScreenTools.defaultFontPixelHeight / 2

                RowLayout {
                    Layout.fillWidth:   true
                    spacing:            ScreenTools.defaultFontPixelWidth

                    QGCLabel { text: qsTr("RTSP URL") }
					QGCTextField {
                        id:                 		sourceField
                        Layout.fillWidth:   		true
						Layout.preferredWidth:    	_urlFieldWidth
                        text:               		editingUrl
                        placeholderText:    		"Enter url" //! qsTr
                    }
                }
            }
        }
    }

    SettingsGroupLayout {
        Layout.fillWidth:   true
        heading:            qsTr("Settings")

        LabelledFactTextField {
            Layout.fillWidth:   true
            label:              qsTr("Aspect Ratio")
            fact:               _videoSettings.aspectRatio
            visible:            !_videoAutoStreamConfig && _isStreamSource && _videoSettings.aspectRatio.visible
        }

        FactCheckBoxSlider {
            Layout.fillWidth:   true
            text:               qsTr("Stop recording when disarmed")
            fact:               _videoSettings.disableWhenDisarmed
            visible:            !_videoAutoStreamConfig && _isStreamSource && fact.visible
        }

        FactCheckBoxSlider {
            Layout.fillWidth:   true
            text:               qsTr("Low Latency Mode")
            fact:               _videoSettings.lowLatencyMode
            visible:            !_videoAutoStreamConfig && _isStreamSource && fact.visible && _isGST
        }

        LabelledFactComboBox {
            Layout.fillWidth:   true
            label:              qsTr("Video decode priority")
            fact:               _videoSettings.forceVideoDecoder
            visible:            fact.visible
            indexModel:         false
        }
    }

    SettingsGroupLayout {
        Layout.fillWidth: true
        heading:            qsTr("Local Video Storage")

        LabelledFactComboBox {
            Layout.fillWidth:   true
            label:              qsTr("Record File Format")
            fact:               _videoSettings.recordingFormat
            visible:            _videoSettings.recordingFormat.visible
        }

        FactCheckBoxSlider {
            Layout.fillWidth:   true
            text:               qsTr("Auto-Delete Saved Recordings")
            fact:               _videoSettings.enableStorageLimit
            visible:            fact.visible
        }

        LabelledFactTextField {
            Layout.fillWidth:   true
            label:              qsTr("Max Storage Usage")
            fact:               _videoSettings.maxVideoSize
            visible:            fact.visible
            enabled:            _videoSettings.enableStorageLimit.rawValue
        }
    }
}
