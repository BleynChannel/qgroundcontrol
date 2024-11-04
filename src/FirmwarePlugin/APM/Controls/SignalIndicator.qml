import QtQuick

import QGroundControl
import QGroundControl.VehicleTelemetry
import QGroundControl.Controls
import QGroundControl.Palette

APMTextBlock {
	id: 			control
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	border.color:	qgcPal.button
	titleColor:		qgcPal.buttonText
	dataColor:		qgcPal.buttonText
	titleText: 		"Signal" //! qsTr
	dataText: 		_telemetry.vehicleSignal

	property var	_telemetry:	QGroundControl.vehicleTelemetry
}