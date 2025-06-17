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

	property alias labelText:	label.text
	property alias iconSource: 	iconImage.source
	property alias iconColor:  	iconImage.color
	
	signal clicked(var event)

	Column {
		id: 				column
		anchors.fill:		parent
		anchors.margins: 	parent.border.width + ScreenTools.defaultFontPixelWidth / 1.5
		spacing: 			4

		QGCColoredImage {
			id: 						iconImage
			fillMode:					Image.PreserveAspectFit
			anchors.horizontalCenter: 	parent.horizontalCenter
			height: 					parent.height - (label.visible ? label.height + parent.anchors.margins + parent.spacing : 0)
			sourceSize.height:  		height
			width:						height
		}

		Item {
			width: 						iconImage.height
			height:						label.height
			anchors.horizontalCenter: 	parent.horizontalCenter

			QGCLabel {
				id:							label
				// horizontalAlignment:		Text.AlignHCenter //! WIP
				anchors.horizontalCenter:	parent.horizontalCenter
				elide:						Text.ElideRight
				visible: 					label.text !== ""
				enabled: 					label.visible
			}
		}
	}

	MouseArea {
		id:          	mouseArea
		anchors.fill: 	parent
		onClicked:     	(event) => control.clicked(event)
	}
}