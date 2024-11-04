import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.VehicleTelemetry
import QGroundControl.Palette

APMIconButton {
	id: 			resetButton
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	iconSource: 	"/qmlimages/Reset.svg"
	iconColor: 		_telemetry.vehicleReset ? qgcPal.colorGreen : qgcPal.colorRed
	border.color:	qgcPal.button
	labelText:		"Reset" //! qsTr

	property var	_telemetry:	QGroundControl.vehicleTelemetry

	function onResetButton() {
		_telemetry.vehicleReset = !_telemetry.vehicleReset
		console.log("Reset status: ", _telemetry.vehicleReset)
	}

	onClicked: onResetButton()
}