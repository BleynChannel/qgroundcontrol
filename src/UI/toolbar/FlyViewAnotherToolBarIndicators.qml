/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick

import QGroundControl
import QGroundControl.ScreenTools

//-------------------------------------------------------------------------
//-- Toolbar Indicators
Flow {
    id:                 indicatorFlow
	anchors.left:		parent.left
	anchors.right:		parent.right
    padding:    		_toolIndicatorMargins
    spacing:            ScreenTools.defaultFontPixelWidth * 1.75

    property var  _activeVehicle:           QGroundControl.multiVehicleManager.activeVehicle
    property real _toolIndicatorMargins:    ScreenTools.defaultFontPixelHeight * 0.66

    function dropMessageIndicatorTool() {
        toolIndicatorsRepeater.dropMessageIndicatorTool();
    }

    Repeater {
        id:     toolIndicatorsRepeater
        model:  _activeVehicle ? _activeVehicle.anotherToolIndicators : []

        function dropMessageIndicatorTool() {
            for (var i=0; i<count; i++) {
                var thisTool = itemAt(i);
                if (thisTool.item.dropMessageIndicator) {
                    thisTool.item.dropMessageIndicator();
                }
            }
        }

        Loader {
			height:				ScreenTools.toolbarHeight - indicatorFlow._toolIndicatorMargins * 2
            source:             modelData
            visible:            item.showIndicator
        }
    }
}
