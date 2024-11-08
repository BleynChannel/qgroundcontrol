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
	titleText: 		"Питание" //! qsTr
	dataText: 		_telemetry.droneLinkPower ? "Подведено" : "Отведено"

	property var	_telemetry:	QGroundControl.vehicleTelemetry
}