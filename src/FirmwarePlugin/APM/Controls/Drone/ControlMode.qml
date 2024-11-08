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
	dataColor:		_telemetry.droneControlMode === 0 ? qgcPal.colorGreen : qgcPal.colorRed
	titleText: 		"Режим управления" //! qsTr
	dataText: 		_telemetry.droneControlMode === 0 ? "Ручной" : "Авто"

	property var	_telemetry:	QGroundControl.vehicleTelemetry

	onClicked: {
		_telemetry.droneControlMode = _telemetry.droneControlMode === 0 ? 1 : 0
	}
}