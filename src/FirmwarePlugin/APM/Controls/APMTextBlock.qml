import QtQuick
import QtQuick.Controls

import QGroundControl
import QGroundControl.Controls
import QGroundControl.ScreenTools
// import QGroundControl.Palette

Rectangle {
	id: 			control
	width:			height
	border.width: 	ScreenTools.defaultFontPointSize / 3
	color:			"transparent"
	radius:			ScreenTools.defaultFontPixelWidth / 2

	property alias titleText:	title.text
	property alias titleColor:	title.color
	property alias dataText:	data.text
	property alias dataColor:	data.color

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
			font.pointSize: 		ScreenTools.defaultFontPointSize
			// color: 					titleColor
			elide:					Text.ElideRight
			horizontalAlignment:	Text.AlignHCenter
		}

		QGCLabel {
			id: 					data
			visible:				text !== ""
			anchors.left: 			parent.left
			anchors.right: 			parent.right
			font.pointSize: 		ScreenTools.defaultFontPointSize * 0.85
			// color: 					dataColor
			elide:					Text.ElideRight
			horizontalAlignment:	Text.AlignHCenter
		}
	}
}