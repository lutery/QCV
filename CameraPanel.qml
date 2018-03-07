import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0
import QtQuick.Dialogs 1.2
import QtMultimedia 5.9
import FaceService 1.0
import QtQuick.Layouts 1.3

Window {
    id:camerawWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property bool autoStart: true
    property bool started: false
    property bool perfMonitorsLogging: false
    property bool perfMonitorsVisible: false
    property int pixDens: Math.ceil(Screen.pixelDensity)
    property int itemWidth: 25 * pixDens
    property int itemHeight: 10 * pixDens
    property int windowWidth: Screen.desktopAvailableWidth
    property int windowHeight: Screen.desktopAvailableHeight
    property int scaledMargin: 2 * pixDens
    property int fontSize: 5 * pixDens

    property string curFPS: "-1"
    property string curPixelFormat: "unknown"
    property int curFaceCount: 0

//    signal winClosing()

    // 侧板
    CameraSidePanel {
        id: cameraSidePanel
        state: "collapsed"
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width: itemHeight + scaledMargin
        z: 2
        opacity: 0.9

        states: [
            State {
                name: "expanded"
                PropertyChanges {
                    target: cameraSidePanel
                    width: itemWidth * 1.5
                    opacity: 0.8
                }
            },
            State {
                name: "collapsed"
                PropertyChanges {
                    target: cameraSidePanel
                    width: itemHeight + scaledMargin
                    opacity: 0.9
                }
            }
        ]

        transitions: [
            Transition {
                NumberAnimation { target: cameraSidePanel; property: "width"; duration: 100 }
                NumberAnimation { target: cameraSidePanel; property: "opacity"; duration: 100 }
            }
        ]

        onSwitchCamera: {
            console.log("cameraId = " + cameraId)
            cameraLoader.item.switchCamera(cameraId)
        }

        onSwitchMethod: {
            console.log("methodId = " + methodId)
            faceService.switchFaceDectedMethod(methodId)
        }
    }

    FaceService{
        id: faceService

        onSigFps: {
            curFPS = curFps
        }

        onSigPixelFormat: {
            curPixelFormat = curPF
        }

        onSigFaceCount: {
            curFaceCount = curCount;
        }
    }

    Loader{
        id: cameraLoader
    }

    Button {
        id: captureBtn
        anchors{
            bottom: parent.bottom
            right: parent.right
            bottomMargin: 10
            rightMargin: 10
        }

        enabled: cameraLoader.item.captureReady
        text: "拍照"
        onClicked: {
            cameraLoader.item.captureCamera()
        }
    }


    CameraInfoPanel{
        anchors{
            left: cameraSidePanel.right
            leftMargin: 16
            right: parent.right
            rightMargin: 16
            top: parent.top
            topMargin: 16
            bottom: captureBtn.top
            bottomMargin: 16
        }
    }

//    Rectangle{
//                anchors{
//                    left: parent.left + 10
//                    right: parent.right - 10
//                    top: parent.top + 10
//                    bottom: parent.bottom - 10
//                }

//        GridLayout{
//            columns:2

//            Text{
//                text:"帧数："
//            }

//            Text{
//                id: fps
//                text: "0"
//            }

//            Text{
//                text:"图片格式："
//            }
//        }
//    }

    Component.onDestruction: {
        console.log("CameraPanel onDestruction")
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
            cameraLoader.item.width = camerawWin.width
            cameraLoader.item.height = camerawWin.height

            if (camerawWin.autoStart)
                camerawWin.start()
        }
    }

    onWidthChanged: {
        if (contentItem())
            contentItem().width = width
    }

    onHeightChanged: {
        if (contentItem())
            contentItem().height = height
    }

    onClosing:{
        console.log("onclosing")
//        camerawWin.winClosing();
        cameraLoader.source = ""
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
    function updateRootSize() { camerawWin.height = contentItem().height }
}
