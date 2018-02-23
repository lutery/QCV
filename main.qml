import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0
import QtQuick.Layouts 1.3
import SImageOperaParamQML 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3

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

    Loader{
       id: cameraWin
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

    RowLayout{
        anchors.margins: 4
        spacing: 10
        anchors.fill: parent

        SceneSelectionPanel{
            id: sceneSelectionPanel
            Layout.fillHeight: true
            Layout.maximumWidth: sceneSelectionPanel.itemWidth + 10
            Layout.minimumWidth: sceneSelectionPanel.itemWidth + 10
//            onSceneSourceChanged: {

//                console.log("sceneSource = " + sceneSource)

//                if (sceneSource == "Preview.qml"){
//                    if (!previewWin.visible) {
//                        previewWin.show()
//                    }
//                }
//                else if (sceneSource == "qrc:/control/CameraPanel.qml"){
////                    if (cameraWin.status != cameraWin.Null){
////                        cameraWin.source = ""
////                        console.log("Null")
////                    }
////                    else {
//                        cameraWin.source = sceneSource
////                        console.log(sceneSource);
////                    }
//                }
//                else{
//                    settingPanel.source = sceneSource
//                    settingPanel.item.imgProcess.connect(onImgProcess)
//                }
//            }

            onSceneChange: {
                console.log("sceneSource = " + sceneSource)

                if (sceneSource == "Preview.qml"){
                    if (!previewWin.visible) {
                        previewWin.show()
                    }
                }
                else if (sceneSource == "qrc:/camera/CameraPanel.qml"){
                    cameraWin.source = ""
                    cameraWin.source = sceneSource
                }
                else{
                    settingPanel.source = sceneSource
                    settingPanel.item.imgProcess.connect(onImgProcess)
                }
            }
        }
//    ColumnLayout{
//        spacing: 10
//        anchors.fill: parent

//        RowLayout{
//            anchors.margins: 4
//            spacing: 10
//            Layout.fillWidth: true

//            SceneSelectionPanel{
//                anchors.fill: parent
//            }

//            Button{
//                text: "打开预览"

//                onClicked: {
//                    if (!previewWin.visible) {
//                        previewWin.show()
//                    }
//                }
//            }

//            Button{
//                text: "自动纠偏"

//                onClicked: {
//                    console.log("click auto")
//                    previewWin.imageOperation(SImageService.AutoRectifying, undefined)
//                }
//            }

//            Button {
//                text: "切边"

//                onClicked: {
//                    console.log(settingPanel.status)

//                    if (settingPanel.status != settingPanel.Null){
//                        settingPanel.source = ""
//                    }

//                    settingPanel.source = "TrimmingPanel.qml"
//                    settingPanel.item.trimBorder.connect(onTrimborder)

//                }
//            }

//            Button {
//                text: "图像分割"

//                onClicked: {
//                    console.log("click image split")

//                    if (settingPanel.state != settingPanel.Null){
//                        settingPanel.source = ""
//                    }

//                    settingPanel.source = "ImageSplitPanel.qml"
//                    settingPanel.item.imgSplit.connect(onImgSplit)
//                }
//            }

//            Button {
//                text: "灰度/二值化"

//                onClicked: {
//                    console.log("click image split")

//                    if (settingPanel.state != settingPanel.Null){
//                        settingPanel.source = ""
//                    }

//                    settingPanel.source = "GrayBinaryPanel.qml"
//                    settingPanel.item.gbProcess.connect(onGBProcess)
//                }
//            }

//            Button {
//                text: "保存"

//                onClicked: {
//                    saveDialog.visible = true
//                }
//            }
//        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
//            color: "red"

            Loader{
                id: settingPanel
                anchors.fill: parent

            }
        }
    }

//    ImageOperaParam {
//        id: operaParams
//    }

//    function onTrimborder(method, border, background){
//        console.log("onTrimborder")
//        console.log(method)
//        console.log(border)
//        console.log(background)
//        console.log("onTrimborder")

//        operaParams.setTrimType(method);
//        operaParams.setTrimBorder(border);
//        operaParams.setBgColor(background);

//        previewWin.imageOperation(SImageService.TrimBorder, operaParams)
//    }

//    function onImgSplit(splitType, cluserCount){
//        console.log("splitType")
//        console.log(splitType)
//        console.log("cluserCount")
//        console.log(cluserCount)

//        operaParams.setClusterCount(cluserCount)
//        operaParams.setImageSplitType(splitType)

//        previewWin.imageOperation(SImageService.ImageSplit, operaParams);
//    }

//    function onGBProcess(type, param){
//        console.log(type)
//        console.log(param)

//        operaParams.setGBMethod(type)
//        operaParams.setGBParam(param)

//        previewWin.imageOperation(SImageService.GrayBinary, operaParams)
//    }

    function onImgProcess(type, param){
        console.log("ongImgProcess" + type)

        previewWin.imageOperation(type, param)
    }

//    function onWinClosing(){
//        console.log("onWinClosing");
//        cameraWin.source = "";
//    }
}
