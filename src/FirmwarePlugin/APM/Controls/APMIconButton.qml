import QtQuick
import QtQuick.Layouts

import QGroundControl
import QGroundControl.Controls
import QGroundControl.ScreenTools

// Used as the base class control for nboth VehicleGPSIndicator and RTKGPSIndicator

Rectangle {
    id:             control
    width:          height
	anchors.top:    parent.top
	anchors.bottom:	parent.bottom
	border.width: 	ScreenTools.defaultFontPointSize / 3
	color:			"transparent"
	radius:			ScreenTools.defaultFontPixelWidth / 2

	property alias labelText:		label.text
	property alias iconSource: 		iconImage.source
	property alias iconColor:  		iconImage.color
	
	property real  _opacity:		mouseArea.pressed ? .5 : enabled && hoverArea.hovered ? .7 : 1
	
	signal clicked(var event)

	Column {
		id: 				column
		anchors.fill:		parent
		anchors.margins: 	parent.border.width + ScreenTools.defaultFontPixelWidth / 1.1
		spacing: 			4

		QGCColoredImage {
			id: 						iconImage
			fillMode:					Image.PreserveAspectFit
			anchors.horizontalCenter: 	parent.horizontalCenter
			height: 					parent.height - (label.visible ? label.height + parent.spacing : 0)
			sourceSize.height:  		height
			width:						height
			opacity:					_opacity
		}

		Item {
			anchors.left:				parent.left
			anchors.right:				parent.right
			height:						label.height

			QGCLabel {
				id:							label
				horizontalAlignment:		Text.AlignHCenter
				anchors.left:				parent.left
				anchors.right:				parent.right
				elide:						Text.ElideRight
				font.pointSize: 			ScreenTools.defaultFontPointSize * 0.85
				visible: 					label.text !== ""
				enabled: 					label.visible
				opacity:					_opacity
			}
		}
	}

	MouseArea {
		id:          	mouseArea
		anchors.fill: 	parent
		onClicked:     	(event) => control.clicked(event)
	}

	HoverHandler {
		id:				hoverArea
	}
}