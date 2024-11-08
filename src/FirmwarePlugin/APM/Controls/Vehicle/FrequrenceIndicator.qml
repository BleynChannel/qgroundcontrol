import QtQuick

import QGroundControl
import QGroundControl.VehicleTelemetry
import QGroundControl.Controls
import QGroundControl.Palette
import QGroundControl.ScreenTools

Row {
	id:				control
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	spacing: 		ScreenTools.defaultFontPixelWidth / 2

	property var	_telemetry:	QGroundControl.vehicleTelemetry

	APMTextBlock {
		anchors.top:    parent.top
		anchors.bottom: parent.bottom
		border.color:	qgcPal.button
		titleColor:		qgcPal.buttonText
		dataColor:		qgcPal.buttonText
		titleText: 		"Частота левого двигателя" //! qsTr
		dataText: 		_telemetry.vehicleLeftFrequrence + " Hz"
	}

	APMTextBlock {
		anchors.top:    parent.top
		anchors.bottom: parent.bottom
		border.color:	qgcPal.button
		titleColor:		qgcPal.buttonText
		dataColor:		qgcPal.buttonText
		titleText: 		"Частота правого двигателя" //! qsTr
		dataText: 		_telemetry.vehicleRightFrequrence + " Hz"
	}
}