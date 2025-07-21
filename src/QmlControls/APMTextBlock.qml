import QtQuick
import QtQuick.Controls

import QGroundControl
import QGroundControl.Controls
import QGroundControl.ScreenTools
import QGroundControl.Palette

Rectangle {
	id: 			control
	width:			height
	border.width: 	ScreenTools.defaultFontPointSize / 3
	border.color:	qgcPal.button
	color:			"transparent"
	radius:			ScreenTools.defaultFontPixelWidth / 2

	property alias titleText:		title.text
	property alias titleColor:		title.color
	property alias titleOpacity:	title.opacity
	property alias dataText:		data.text
	property alias dataColor:		data.color
	property alias dataOpacity:		data.opacity

	QGCPalette {
        id:                 qgcPal
        colorGroupEnabled:  true
    }

	Column {
		anchors.left:			parent.left
		anchors.right:			parent.right
		anchors.margins: 		control.border.width + ScreenTools.defaultFontPixelWidth / 1.5
		anchors.verticalCenter: parent.verticalCenter
		spacing: 				2

		QGCLabel {
			id: 					title
			anchors.left: 			parent.left
			anchors.right: 			parent.right
			font.pointSize: 		ScreenTools.defaultFontPointSize * 0.9
			color: 					qgcPal.buttonText
			elide:					Text.ElideRight
			wrapMode:				Text.WordWrap
			horizontalAlignment:	Text.AlignHCenter
		}

		QGCLabel {
			id: 					data
			visible:				text !== ""
			anchors.left: 			parent.left
			anchors.right: 			parent.right
			font.pointSize: 		ScreenTools.defaultFontPointSize * 0.85
			opacity:				0.75
			color: 					qgcPal.buttonText
			elide:					Text.ElideRight
			horizontalAlignment:	Text.AlignHCenter
		}
	}
}