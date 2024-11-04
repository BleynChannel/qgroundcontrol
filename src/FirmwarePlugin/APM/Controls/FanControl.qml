import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.VehicleTelemetry
import QGroundControl.Palette

APMIconButton {
	id: 			fanButton
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	iconSource: 	"/qmlimages/Fan.svg"
	iconColor: 		_telemetry.vehicleFan ? qgcPal.colorGreen : qgcPal.colorRed
	border.color:	qgcPal.button
	labelText:		"Fan" //! qsTr

	property var	_telemetry:	QGroundControl.vehicleTelemetry

	function onFanButton() {
		_telemetry.vehicleFan = !_telemetry.vehicleFan
		console.log("Fan status: ", _telemetry.vehicleFan)
	}

	onClicked: onFanButton()
}