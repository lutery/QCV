import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    id: transformPanel
    anchors.fill: parent

    signal imgProcess(real type, QtObject param)

    ImageOperaParam {

    }

    RowLayout{
        anchors.fill: parent
        Layout.margins: 4
        spacing: 4

        ColumnLayout{
            id: transformLayout
//            width: 120
            Layout.minimumWidth: 64
            Layout.maximumWidth: 64
//            Layout.fillWidth: true
            Layout.fillHeight: true
            anchors.left: parent.left

            ListView {
                id: transformType
                anchors.fill: parent
                delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")
                //ToDo 这里看是否可以使用其他的方式动态加载独立的模型文件
                model: transformTypeModel.item
                clip: true
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                signal listItemChanged(string dstPanel)
                onListItemChanged: {
                    console.log("transformType onTransformChange " + dstPanel)

                    settingPanel.source = dstPanel
                    settingPanel.item.imgProcessParam.connect(onImgProcessParam)
                }
//                function onListItemChanged(dstPanel) {
//                    console.log("transformType onTransformChange")

//                    settingPanel.source = dstPanel
//                }
            }
        }

        Rectangle {
            id: blank_rt
            Layout.maximumWidth: 8
            Layout.minimumWidth: 8
            Layout.fillHeight: true
//            color: "red"
            anchors.left: transformLayout.right
        }

        ColumnLayout{
            Layout.minimumWidth: 64
            Layout.maximumWidth: 64
            Layout.fillHeight: true
            anchors.left: blank_rt.right

            ListView {
                id: methodType
//                anchors.fill: parent
                Layout.fillWidth: true
                Layout.fillHeight: true
                delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")
                model: methodTypeModel.item
                clip: true
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                signal listItemChanged(string dstPanel)
            }

            ListView {
                id: resizeType
//                anchors.fill: parent
                Layout.fillHeight: true
                Layout.fillWidth: true
                delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")
                model: resizeTypeModel.item
                clip: true
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                signal listItemChanged(string dstPanel)
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Loader {
                id: settingPanel
                anchors.fill: parent
            }
        }
    }

    Loader{
        id: transformTypeModel
        source: "qrc:/listview/model/TransformModel.qml"
    }

    Loader {
        id: methodTypeModel
        source: "qrc:/listview/model/MethodModel.qml"
    }

    Loader{
        id: resizeTypeModel
        source: "qrc:/listview/model/ResizeTypeModel.qml"
    }

    function onImgProcessParam(param){
        console.log("transformPanel onImgParam exec")

        var method = SImageService.Resize_NEAREST_OpenCV
        var methodItem = methodType.model.get(methodType.currentIndex)
        var resizeItem = resizeType.model.get(resizeType.currentIndex)
        console.log("methodType.currentItem.methodId : " + methodItem.methodId)
        console.log("resizeType.currentItem.methodId : " + resizeItem.methodId)
        if (methodItem.methodId == 1){

            if (resizeItem.methodId == 1){
                method = SImageService.Resize_NEAREST_OpenCV
            }
            else if (resizeItem.methodId == 2){
                method = SImageService.Resize_LINEAR_OpenCV
            }
            else if (resizeItem.methodId == 3){
                method = SImageService.Resize_CUBIC_OpenCV
            }

        }
        else if (methodItem.methodId == 2){

            if (resizeItem.methodId == 1){
                method = SImageService.Resize_NEAREST_Third
            }
            else if (resizeItem.methodId == 2){
                method = SImageService.Resize_LINEAR_Third
            }
            else if (resizeItem.methodId == 3){
                method = SImageService.Resize_CUBIC_Third
            }
        }

        console.log("method is " + method)
        param.setTransformType(method)
        transformPanel.imgProcess(SImageService.TransformImg, param)
    }
}
