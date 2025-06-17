import QtQuick

import QGroundControl
import QGroundControl.VehicleTelemetry
import QGroundControl.Controls
import QGroundControl.Palette

APMTextButton {
	id: 			control
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	border.color:	qgcPal.button
	titleColor:		qgcPal.buttonText
	dataColor:		_telemetry.droneWinding ? qgcPal.colorGreen : qgcPal.colorRed
	titleText: 		"Смотка" //! qsTr
	dataText: 		_telemetry.droneWinding ? "ВКЛ" : "ВЫКЛ"

	property var	_telemetry:	QGroundControl.vehicleTelemetry

	onClicked: {
		_telemetry.droneWinding = !_telemetry.droneWinding
	}
}