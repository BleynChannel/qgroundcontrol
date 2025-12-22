import QtQuick
import QtQuick.Layouts

import QGroundControl
import QGroundControl.Controls
import QGroundControl.MultiVehicleManager
import QGroundControl.ScreenTools

Item {
    id:             control
    width:          controlsRow.width
    anchors.top:    parent.top
    anchors.bottom: parent.bottom
	visible: 		QGroundControl.videoManager.uris.length > 0

    property var    _activeVehicle: QGroundControl.multiVehicleManager.activeVehicle
	property var 	_telemetry:	QGroundControl.vehicleTelemetry

	Rectangle {
		anchors.fill: 	controlsRow
		color: 			"transparent"
		border.color: 	qgcPal.button
		border.width: 	ScreenTools.defaultFontPointSize / 3
		radius: 		ScreenTools.defaultFontPixelWidth / 2
	}

	Row {
		id: controlsRow
		anchors.top:    parent.top
        anchors.bottom: parent.bottom
		leftPadding:    ScreenTools.defaultFontPixelWidth * 2
		rightPadding:   ScreenTools.defaultFontPixelWidth * 2
        spacing:        ScreenTools.defaultFontPixelWidth

		Repeater {
			model: QGroundControl.videoManager.uris.map((uri, index) => { return index })

			APMIconButton {
				required property int index

				anchors.top:    parent.top
				anchors.bottom: parent.bottom
				iconSource: 	"/qmlimages/CameraIcon.svg"
				iconColor: 		QGroundControl.videoManager.activeUri === index ? qgcPal.colorGreen : qgcPal.button
				border.width:	0

				onClicked: _telemetry.vehicleCameraSelect = index
			}
		}
	}
}