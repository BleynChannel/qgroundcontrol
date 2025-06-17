import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.VehicleTelemetry
import QGroundControl.Palette

APMIconButton {
	id: 			lightButton
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	iconSource: 	"/qmlimages/Flashlight.svg"
    iconColor: 		_telemetry.vehicleFlashlight === 1 ? qgcPal.colorGreen : qgcPal.colorRed
	border.color:	qgcPal.button
	labelText:		"Свет" //! qsTr

	property var	_telemetry:		QGroundControl.vehicleTelemetry

	function onLightButton() {
		_telemetry.vehicleFlashlight = !_telemetry.vehicleFlashlight
	}

	onClicked: onLightButton()
}
