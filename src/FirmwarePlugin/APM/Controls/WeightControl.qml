import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.VehicleTelemetry
import QGroundControl.Palette

APMIconButton {
	id: 			weightButton
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	iconSource: 	"/qmlimages/Weight.svg"
	iconColor: 		_telemetry.vehicleWeight ? qgcPal.colorGreen : qgcPal.colorRed
	border.color:	qgcPal.button
	labelText:		"Weight" //! qsTr

	property var	_telemetry:	QGroundControl.vehicleTelemetry

	function onWeightButton() {
		_telemetry.vehicleWeight = !_telemetry.vehicleWeight
		console.log("Weight status: ", _telemetry.vehicleWeight)
	}

	onClicked: onWeightButton()
}