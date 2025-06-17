import QtQuick
import QtQuick.Controls

import QGroundControl
import QGroundControl.Controls
import QGroundControl.ScreenTools

APMTextBlock {
	id: 	control

	signal clicked(var event)

	MouseArea {
		anchors.fill: 	parent
		onClicked:     	(event) => control.clicked(event)
	}
}