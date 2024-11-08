import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.Palette

APMIconButton {
	id: 			landButton
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	iconSource: 	"/res/land.svg"
	// iconColor: 		_telemetry.vehicleEngine ? qgcPal.colorGreen : qgcPal.colorRed
    enabled:    	!_guidedController.showTakeoff || _guidedController.showLand
	border.color:	qgcPal.button
	labelText:		"Спуск" //! qsTr

	property var _guidedController: globals.guidedControllerFlyView

	function onLandButton() {
		_guidedController.closeAll()
        _guidedController.confirmAction(_guidedController.actionLand)
	}

	onClicked: onLandButton()
}