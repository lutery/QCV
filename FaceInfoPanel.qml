import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import FaceService 1.0

Rectangle {
    id: root
//    color: "green"

    Rectangle{
        id: previewRc
        anchors.centerIn: parent
        width: 360
        height: 360
//        color: "red"

        Loader{
            id: cameraLoader
        }
    }

    Rectangle{
        id: btnRc
        anchors.top: previewRc.bottom
        anchors.topMargin: 20
        width: root.width

        RowLayout{
            anchors.centerIn: parent
            spacing: 6

            Button{
                width: 120
                height: 32
                text: "识别"
//                color: "blue"
                onClicked: {

                }
            }

            Button{
                width: 120
                height: 32
                text: "添加"
//                color: "yellow"
                onClicked: {

                }
            }

            Button{
                width: 120
                height: 32
                text: "保存"
//                color: "yellow"
                onClicked: {
                    FaceService.save()
                }
            }
        }
    }

    Rectangle{
        anchors.top: btnRc.bottom
        anchors.topMargin: 30
        width: 30

        TextEdit{
            id: faceid
            anchors.fill: parent
        }
    }

    Component.onCompleted: {
        cameraLoader.source = "CameraItem.qml"

        if (cameraLoader.Error == Loader.Error){
            console.log("load camera item error")
            return
        }

        if (cameraLoader.item){
            cameraLoader.item.sizeChanged.connect(updateRootSize)
//            cameraLoader.item.parent = camerawWin
            cameraLoader.item.width = previewRc.width
            cameraLoader.item.height = previewRc.height

            if (camerawWin.autoStart)
                camerawWin.start()
        }
    }

    function start() {
        if (cameraLoader.item) {
            cameraLoader.item.start()
            camerawWin.started = true
        }
    }

    function stop() {
        if (cameraLoader.item) {
            cameraLoader.item.stop()
            camerawWin.started = false
        }
    }

    function contentItem() { return cameraLoader.item }
    function updateRootSize() { previewRc.height = contentItem().height }
}
