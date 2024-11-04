import QtQuick
import QtQuick.Layouts

import QGroundControl
import QGroundControl.Controls
import QGroundControl.MultiVehicleManager
import QGroundControl.ScreenTools

Item {
    id:             _root
	visible:        _activeVehicle && _activeVehicle.isROIEnabled
	width:          uploadButton.width
    anchors.top:    parent.top
    anchors.bottom: parent.bottom

    property var    _activeVehicle:          QGroundControl.multiVehicleManager.activeVehicle

	QGCButton {
		id:             uploadButton
		anchors.top:    parent.top
		anchors.bottom: parent.bottom
		width:          height * 1.5
		text:           "Upload ROI" //! qsTr
		onClicked: {
			// globals.guidedControllerFlyView.confirmAction(globals.guidedControllerFlyView.actionROI, _activeVehicle.roiCoord)
			_activeVehicle.guidedModeROI(_activeVehicle.roiCoord)
		}
	}
}