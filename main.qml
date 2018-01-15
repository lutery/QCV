import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0
import QtQuick.Layouts 1.3
import SImageOperaParamQML 1.0

Window {
    id:mainWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Tool Windows")

    PreviewWindow{
        id: previewWin
//        窗口跟随
        x: mainWin.x + mainWin.width
        y: mainWin.y
    }

    ColumnLayout{
        spacing: 10

        RowLayout{
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
                    previewWin.imageOperation(SImageService.AutoRectifying, undefined)
                }
            }

            Button {
                text: "切边"

                onClicked: {
                    console.log(settingPanel.status)

                    if (settingPanel.status != settingPanel.Null){
                        settingPanel.source = ""
                    }

                    settingPanel.source = "TrimmingPanel.qml"
                    settingPanel.item.trimBorder.connect(onTrimborder)

                }
            }
        }

        RowLayout{
            Layout.fillHeight: true

            Loader{
                id: settingPanel
                anchors.fill: parent

            }
        }
    }

    ImageOperaParam {
        id: operaParams
    }

    function onTrimborder(border, background){
        console.log("onTrimborder")
        console.log(border)
        console.log(background)

        operaParams.setTrimBorder(border);
        operaParams.setBgColor(background);

        previewWin.imageOperation(SImageService.TrimBorder, operaParams)
    }
}
