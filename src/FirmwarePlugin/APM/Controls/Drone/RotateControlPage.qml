import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QGroundControl
import QGroundControl.VehicleTelemetry
import QGroundControl.Controls
import QGroundControl.MultiVehicleManager
import QGroundControl.ScreenTools
import QGroundControl.Palette

ToolIndicatorPage {
	showExpand:         false
	contentComponent:   rotateContentComponent

	Component {
		id: 		rotateContentComponent

		RowLayout {
			id: 		rowLayout
			spacing: 	2

			property alias	_rotate:		rotateSlider.value

			property var	_telemetry:		QGroundControl.vehicleTelemetry

			Component.onCompleted: _rotate = _telemetry.droneRotate
			
			Column {
				width:		ScreenTools.defaultFontPixelWidth * 20
				spacing: 	2

				QGCTextField {
					id: 			rotateTextField
					anchors.left: 	parent.left
					anchors.right: 	parent.right
					validator: 		IntValidator {bottom: 0; top: 360;}
					text:			_rotate.toString()
					
					onTextEdited: _rotate = parseInt(text)
				}

				Slider {
					id:				rotateSlider
					anchors.left:	parent.left
					anchors.right:	parent.right
					from: 			0
					to:				360
					stepSize:		1
				}

				QGCButton {
					id:				rotateButton
					anchors.right:	parent.right
					text:			"Отправить" //! qsTr
					enabled:		globals.guidedControllerFlyView.showROI
					onClicked: {
						// _activeVehicle.setPointROI(_activeVehicle.calcRotateLocation(_rotate, _activeVehicle.coordinate))
						globals.guidedControllerFlyView.executeAction(globals.guidedControllerFlyView.actionROI, _activeVehicle.calcRotateLocation(_rotate, _activeVehicle.coordinate), 0, false)
						// _telemetry.droneRotate = _rotate
						mainWindow.closeIndicatorDrawer()
					}
				}
			}
		}
	}
}