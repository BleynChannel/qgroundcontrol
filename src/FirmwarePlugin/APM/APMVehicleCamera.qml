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
	visible: 		QGroundControl.videoManager.videoReceiverUris.length > 0

    property var    _activeVehicle: QGroundControl.multiVehicleManager.activeVehicle

	Rectangle {
		anchors.fill: controlsRow
		color: "transparent"
		border.color: qgcPal.button
		border.width: 1
		radius: ScreenTools.defaultFontPixelWidth / 2
	}

	Row {
		id: controlsRow
		anchors.top:    parent.top
        anchors.bottom: parent.bottom
		leftPadding:    ScreenTools.defaultFontPixelWidth * 2
		rightPadding:   ScreenTools.defaultFontPixelWidth * 2
        spacing:        ScreenTools.defaultFontPixelWidth

		property int _activeCamera: 0

		function setActiveCamera(index) {
			_activeCamera = index
			QGroundControl.videoManager.changeCurrentUri(index)
		}

		Repeater {
			model: QGroundControl.videoManager.videoReceiverUris.map((uri, index) => { return index })

			APMIconButton {
				required property int index

				anchors.top:    parent.top
				anchors.bottom: parent.bottom
				iconSource: 	"/qmlimages/CameraIcon.svg"
				iconColor: 		controlsRow._activeCamera === index ? qgcPal.colorGreen : qgcPal.button

				onClicked: controlsRow.setActiveCamera(index)
			}
		}
	}
}