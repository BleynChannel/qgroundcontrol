import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import QGroundControl
import QGroundControl.Calibration
import QGroundControl.Controls
import QGroundControl.Palette
import QGroundControl.ScreenTools

APMTextButton {
	id: 			control
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	border.color:	qgcPal.button
	titleColor:		qgcPal.buttonText
	titleText: 		"Калибровка" //! qsTr
	enabled:		_calibration.connected

	property var	_calibration:	QGroundControl.сalibration

	Timer {
		interval:			5000
		repeat:				true
		running:			!_calibration.connected
		triggeredOnStart:	true
		
		onTriggered:		_calibration.reconnect()
	}

	onClicked: {
		mainWindow.showMessageDialog(
			"Начало калибровки", //! qsTr 
			"Начать процесс калибровки?", //! qsTr 
			Dialog.Ok | Dialog.Cancel, 
			calibrate)
	}

	function calibrate()
	{
		// var handler = _calibration.execReadThread("rosrun calcu calcu.py");
		var handler = _calibration.execReadThread("echo 'Hello, World!'");

		calibrationDialogComponent.createObject(mainWindow, { handler: handler }).open()
	}

	Component {
        id: calibrationDialogComponent

        QGCPopupDialog {
			id:				calibrationDialog
            title:          "Калибровка" //! qsTr
            buttons:        Dialog.Apply | Dialog.Cancel
			// acceptAllowed:	false

			property var	handler
            
			onAccepted: {
				console.log("Apply")
				calibrationDialog.close()
			}

            onRejected: {
				console.log("Cancel")
				handler.stop()
			}

			Connections {
				target: handler
				
				function onRead(buffer) {
					console.log(buffer.toString())
				}

				function onFinished() {
					console.log("Finished!")
					handler = null
					calibrationDialog.acceptAllowed = true
				}
			}

            ColumnLayout {
                spacing: 		ScreenTools.defaultFontPixelHeight / 2
				width:			ScreenTools.screenWidth / 2
				height:			ScreenTools.screenHeight / 2.5

				QGCLabel {
					id: 					description
					font.pointSize: 		ScreenTools.defaultFontPointSize * 1.8
					color: 					qgcPal.buttonText
					elide:					Text.ElideRight
					wrapMode:               Text.WordWrap
					text:					"Information"
					width:					parent.width - 20
				}

				// QGCLabel {
				// 	id: 					description
				// 	font.pointSize: 		ScreenTools.defaultFontPointSize * 1.8
				// 	color: 					qgcPal.buttonText
				// 	elide:					Text.ElideRight
				// 	text:					"Information"
				// 	Layout.alignment: 		Qt.AlignHCenter | Qt.AlignVCenter
				// }

				// QGCLabel {
				// 	id: 					status
				// 	font.pointSize: 		ScreenTools.defaultFontPointSize * 2.2
				// 	color: 					qgcPal.buttonText
				// 	elide:					Text.ElideRight
				// 	text:					"Done"
				// 	Layout.alignment: 		Qt.AlignHCenter | Qt.AlignVCenter
				// }
            }
        }
    }
}