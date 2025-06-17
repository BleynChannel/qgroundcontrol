import QtQuick
import QtQuick.Controls

import QGroundControl
import QGroundControl.Controls
import QGroundControl.ScreenTools

APMTextBlock {
	id: 				control
	titleOpacity:		_opacity
	dataOpacity:		_opacity

	property bool   _showHighlight:     enabled && (mouseArea.pressed || hoverArea.hovered)
	property real	_opacity:			mouseArea.pressed ? .5 : enabled && hoverArea.hovered ? .7 : 1

	signal clicked(var event)

	MouseArea {
		id:				mouseArea
		anchors.fill: 	parent
		onClicked:     	(event) => control.clicked(event)
	}

	HoverHandler {
		id:				hoverArea
	}
}