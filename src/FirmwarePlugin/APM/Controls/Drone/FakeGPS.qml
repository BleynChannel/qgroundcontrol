import QtQuick

import QGroundControl
import QGroundControl.VehicleTelemetry
import QGroundControl.Controls
import QGroundControl.Palette

APMTextButton {
  id:       control
  anchors.top:    parent.top
  anchors.bottom: parent.bottom
  border.color:  qgcPal.button
  titleColor:    qgcPal.buttonText
  dataColor:    _telemetry.fakeGPS ? qgcPal.colorGreen : qgcPal.colorRed
  titleText:     "FakeGPS" //! qsTr
  dataText:     _telemetry.fakeGPS ? "ВКЛ" : "ВЫКЛ"

  property var  _telemetry:  QGroundControl.vehicleTelemetry

  onClicked: {
    _telemetry.fakeGPS = !_telemetry.fakeGPS
  }
}
