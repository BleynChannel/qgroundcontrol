import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.VehicleTelemetry
import QGroundControl.Palette

APMIconButton {
	id: 			valveButton
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	iconSource: 	"/qmlimages/Valve.svg"
	iconColor: 		_telemetry.vehicleValve ? qgcPal.colorGreen : qgcPal.colorRed
	border.color:	qgcPal.button
	enabled:		false //! WIP
	labelText:		"Клапан (WIP)" //! qsTr

	property var	_telemetry:	QGroundControl.vehicleTelemetry

	function onValveButton() {
		_telemetry.vehicleValve = !_telemetry.vehicleValve
	}

	onClicked: onValveButton()
}