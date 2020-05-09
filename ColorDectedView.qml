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
              Qt.quit()
          }
          onRejected: {
              console.log("Canceled")
              Qt.quit()
          }
          Component.onCompleted: visible = true
      }

    Button {
        id: colorSelectBtn
        text: "选择颜色"

        anchors.baseline: trimBorder
        anchors.right: trimBorder.left
        anchors.rightMargin: 8

        onClicked: {

        }
    }

    Button{
        id: trimBorder
        text: "颜色检测"

        anchors.bottom: parent.bottom
        anchors.right: parent.right

        onClicked: {
            console.log("开始检测")
        }
    }
}
