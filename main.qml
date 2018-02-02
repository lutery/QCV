import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0
import QtQuick.Layouts 1.3
import SImageOperaParamQML 1.0
import QtQuick.Dialogs 1.2

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

    FileDialog{
        id: saveDialog
        title: "保存图片"
        folder: shortcuts.home
        selectFolder: false
        selectExisting: false
        nameFilters: ["Image files (*.jpg)", "Image files (*.png)", "Image files (*.bmp)"]
        onAccepted: {
            console.log("You choose: " + saveDialog.fileUrls);

            var filePath = fileUrls[0].substr(8)

            operaParams.setSelectPath(filePath)

            previewWin.imageOperation(SImageService.Save, operaParams)

            console.log(filePath)

//            Qt.quit()
        }

        onRejected: {
            console.log("Canceled")
//            Qt.quic()
        }
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

            Button {
                text: "图像分割"

                onClicked: {
                    console.log("click image split")

                    if (settingPanel.state != settingPanel.Null){
                        settingPanel.source = ""
                    }

                    settingPanel.source = "ImageSplitPanel.qml"
                    settingPanel.item.imgSplit.connect(onImgSplit)
                }
            }

            Button {
                text: "灰度/二值化"

                onClicked: {
                    console.log("click image split")

                    if (settingPanel.state != settingPanel.Null){
                        settingPanel.source = ""
                    }

                    settingPanel.source = "GrayBinaryPanel.qml"
                    settingPanel.item.gbProcess.connect(onGBProcess)
                }
            }

            Button {
                text: "保存"

                onClicked: {
                    saveDialog.visible = true
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

    function onTrimborder(method, border, background){
        console.log("onTrimborder")
        console.log(method)
        console.log(border)
        console.log(background)
        console.log("onTrimborder")

        operaParams.setTrimType(method);
        operaParams.setTrimBorder(border);
        operaParams.setBgColor(background);

        previewWin.imageOperation(SImageService.TrimBorder, operaParams)
    }

    function onImgSplit(splitType, cluserCount){
        console.log("splitType")
        console.log(splitType)
        console.log("cluserCount")
        console.log(cluserCount)

        operaParams.setClusterCount(cluserCount)
        operaParams.setImageSplitType(splitType)

        previewWin.imageOperation(SImageService.ImageSplit, operaParams);
    }

    function onGBProcess(type, param){
        console.log(type)
        console.log(param)

        operaParams.setGBMethod(type)
        operaParams.setGBParam(param)

        previewWin.imageOperation(SImageService.GrayBinary, operaParams)
    }
}
