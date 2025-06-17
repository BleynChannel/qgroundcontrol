import QtQuick

import QGroundControl
import QGroundControl.Controls
import org.freedesktop.gstreamer.Qt6GLVideoItem

Window {
	id: subVehicleView
	visible: true

	property bool   _showGrid:          QGroundControl.settingsManager.videoSettings.gridLines.rawValue

	Component {
		id: videoBackgroundComponent

		GstGLQt6VideoItem {
			id:             videoContent
			objectName:     "anotherVideo"

			Connections {
				target: QGroundControl.videoManager
				function onImageFileChanged() {
					videoContent.grabToImage(function(result) {
						if (!result.saveToFile(QGroundControl.videoManager.imageFile)) {
							console.error('Error capturing video frame');
						}
					});
				}
			}
			Rectangle {
				color:  Qt.rgba(1,1,1,0.5)
				height: parent.height
				width:  1
				x:      parent.width * 0.33
				visible: _showGrid && !QGroundControl.videoManager.fullScreen
			}
			Rectangle {
				color:  Qt.rgba(1,1,1,0.5)
				height: parent.height
				width:  1
				x:      parent.width * 0.66
				visible: _showGrid && !QGroundControl.videoManager.fullScreen
			}
			Rectangle {
				color:  Qt.rgba(1,1,1,0.5)
				width:  parent.width
				height: 1
				y:      parent.height * 0.33
				visible: _showGrid && !QGroundControl.videoManager.fullScreen
			}
			Rectangle {
				color:  Qt.rgba(1,1,1,0.5)
				width:  parent.width
				height: 1
				y:      parent.height * 0.66
				visible: _showGrid && !QGroundControl.videoManager.fullScreen
			}
		}
	}

	Loader {
		// GStreamer is causing crashes on Lenovo laptop OpenGL Intel drivers. In order to workaround this
		// we don't load a QGCVideoBackground object when video is disabled. This prevents any video rendering
		// code from running. Hence the Loader to completely remove it.
		height:             parent.height
		width:              parent.width
		anchors.centerIn:   parent
		visible:            QGroundControl.videoManager.decoding
		sourceComponent:    videoBackgroundComponent

		property bool videoDisabled: QGroundControl.settingsManager.videoSettings.videoSource.rawValue === QGroundControl.settingsManager.videoSettings.disabledVideoSource
	}

	Item {
		id: 			videoOverlay
		anchors.fill: 	parent
	}
}