import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

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

    Button{
        text: 打开预览

        onClicked: {
            if (!previewWin.visible) {
                previewWin.show()
            }
        }
    }
}
