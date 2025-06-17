import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.VehicleTelemetry
import QGroundControl.Palette

APMIconButton {
	id: 			engineButton
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	iconSource: 	"/qmlimages/Start.svg"
	iconColor: 		_telemetry.vehicleEngine ? qgcPal.colorGreen : qgcPal.colorRed
	border.color:	qgcPal.button
	labelText:		"Engine" //! qsTr

	property var 	_telemetry:	QGroundControl.vehicleTelemetry

	function onEngineButton() {
		_telemetry.vehicleEngine = !_telemetry.vehicleEngine
		console.log("Engine status: ", _telemetry.vehicleEngine)
	}

	onClicked: onEngineButton()
}