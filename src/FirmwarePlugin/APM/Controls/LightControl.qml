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
	iconColor: 		_telemetry.vehicleFlashlight ? qgcPal.colorGreen : qgcPal.colorRed
	border.color:	qgcPal.button
	labelText:		"Light" //! qsTr

	property var	_telemetry:		QGroundControl.vehicleTelemetry

	function onLightButton() {
		_telemetry.vehicleFlashlight = !_telemetry.vehicleFlashlight
		console.log("Light status: ", _telemetry.vehicleFlashlight)
	}

	onClicked: onLightButton()
}