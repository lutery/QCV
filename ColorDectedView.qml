import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    anchors.fill: parent

    ColorDialog {
          id: colorDialog
          title: "Please choose a color"

          onAccepted: {
              console.log("You chose: " + colorDialog.color)
              selectColor.color = colorDialog.color
//              Qt.quit()
          }
          onRejected: {
              console.log("Canceled")
//              Qt.quit()
          }
      }

//    Button {
//        id: colorSelectBtn
//        text: "选择颜色"

//        anchors.baseline: trimBorder
//        anchors.right: trimBorder.left
//        anchors.rightMargin: 8

//        onClicked: {

//        }
//    }

    Text {
        id: colorTitle

        anchors.left: colorSelectBtn.left
        anchors.top: colorSelectBtn.bottom
        anchors.topMargin: 8

        text: qsTr("当前选择的颜色是：")
    }

    Rectangle {
        id: selectColor

        anchors.left: colorTitle.left
        anchors.top: colorTitle.bottom
        anchors.topMargin: 8

        width: 100
        height: 80

        color: "#000000"

        MouseArea {
            anchors.fill: parent

            onClicked: {
                colorDialog.open()
            }
        }
    }

    Button{
        id: trimBorder
        text: "颜色检测"

        anchors.bottom: parent.bottom
        anchors.right: parent.right

        onClicked: {
            console.log("开始检测")

            operaParams.setDetectColor(selectColor.color)
            operaParams.setDetectType(SImageService.DetectType_Simple)

            splitPanel.imgProcess(SImageService.ColorDetect, operaParams)
        }
    }
}
