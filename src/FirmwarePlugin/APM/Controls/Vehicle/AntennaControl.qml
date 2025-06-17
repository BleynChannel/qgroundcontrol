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
	dataColor:		qgcPal.buttonText
	titleText: 		"Поворот антенны" //! qsTr
	dataText: 		_telemetry.vehicleAntennaPosition + "°"

	property var	_telemetry:	QGroundControl.vehicleTelemetry

	onClicked:      mainWindow.showIndicatorDrawer(antennaControlPage, control)

    Component {
        id: antennaControlPage

        AntennaControlPage { }
    }
}