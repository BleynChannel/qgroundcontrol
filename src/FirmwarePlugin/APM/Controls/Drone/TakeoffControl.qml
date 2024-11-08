import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.Palette

APMIconButton {
	id: 			takeoffButton
	anchors.top:    parent.top
	anchors.bottom: parent.bottom
	iconSource: 	"/res/takeoff.svg"
    enabled:    	_guidedController.showTakeoff || !_guidedController.showLand
	border.color:	qgcPal.button
	labelText:		"Взлёт" //! qsTr

	property var _guidedController: globals.guidedControllerFlyView

	function onTakeoffButton() {
		_guidedController.closeAll()
        _guidedController.confirmAction(_guidedController.actionTakeoff)
	}

	onClicked: onTakeoffButton()
}