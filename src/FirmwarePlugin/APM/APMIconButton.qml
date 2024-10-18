import QtQuick

import QGroundControl
import QGroundControl.Controls
import QGroundControl.MultiVehicleManager

// Used as the base class control for nboth VehicleGPSIndicator and RTKGPSIndicator

Item {
    id:             control
    width:          iconImage.width

	property alias iconSource: iconImage.source
	property alias iconColor:  iconImage.color
	
	signal clicked(var event)

	QGCColoredImage {
		id: iconImage
		fillMode:			Image.PreserveAspectFit
		anchors.top: 		parent.top
		anchors.bottom: 	parent.bottom
		width: 				height
		sourceSize.height:  height
	}

	MouseArea {
		id:          	mouseArea
		anchors.fill: 	parent
		onClicked:     	(event) => control.clicked(event)
	}
}