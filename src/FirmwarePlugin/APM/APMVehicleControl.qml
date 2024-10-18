import QtQuick
import QtQuick.Layouts

import QGroundControl
import QGroundControl.Controls
import QGroundControl.MultiVehicleManager
import QGroundControl.ScreenTools
import QGroundControl.Palette

Item {
    id:             control
    width:          controlsRow.width
    anchors.top:    parent.top
    anchors.bottom: parent.bottom

    property var    _activeVehicle: QGroundControl.multiVehicleManager.activeVehicle

	Row {
		id: 			controlsRow
		anchors.top:    parent.top
        anchors.bottom: parent.bottom
        spacing:        ScreenTools.defaultFontPixelWidth / 1.5

        APMIconButton {
			id: 			engineButton
			anchors.top:    parent.top
    		anchors.bottom: parent.bottom
			iconSource: 	"/qmlimages/Start.svg"
			iconColor: 		_startEngine ? qgcPal.colorGreen : qgcPal.colorRed

            property bool _startEngine: false

			function onEngineButton() {
				_startEngine = !_startEngine
				console.log("Engine status: ", _startEngine)
			}

			onClicked: onEngineButton()
		}
	}
}
