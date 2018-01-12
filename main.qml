import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0

Window {
    id:mainWin
    visible: true
    width: 240
    height: 480
    title: qsTr("Tool Windows")

    PreviewWindow{
        id: previewWin
        x: mainWin.x + mainWin.width
        y: mainWin.y
    }

    Flow{
        anchors.fill: parent
        anchors.margins: 4
        spacing: 10

        Button{
            text: "打开预览"

            onClicked: {
                if (!previewWin.visible) {
                    previewWin.show()
                }
            }
        }

        Button{
            text: "自动纠偏"

            onClicked: {
                console.log("click auto")
                previewWin.imageOperation(SImageService.AutoRectifying)
            }
        }
    }
}
