import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import QGroundControl
import QGroundControl.Calibration
import QGroundControl.Controls
import QGroundControl.Palette
import QGroundControl.ScreenTools

APMTextButton {
    id: control
    titleText: "Запустить калибровку"
    enabled: _calibration.connected

    	property var	_calibration:	QGroundControl.сalibration

    onClicked: {
        _calibration.launchCalibrationApp()
    }
}