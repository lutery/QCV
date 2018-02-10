import QtQuick 2.7
import QtQuick.Controls 2.2

Rectangle {
    id: root
    color: "#151515"

    signal switchCamera(string cameraId)

    property int cameraSelHover: 0x00

    Rectangle {
        id: menuField
        height: itemHeight
        width: itemHeight
        color: "transparent"
        anchors.right: parent.right
        Image {
            id: menu
            source: "qrc:/image/resource/icon/icon_menu.png"
            anchors {
                right: parent.right
                top: parent.top
                margins: scaledMargin
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: cameraSidePanel.state == "expanded" ? cameraSidePanel.state = "collapsed" : cameraSidePanel.state = "expanded"
        }
    }

    Column {
        id: funcSelect

        anchors {
            top: menuField.bottom
            right: parent.right
            left: parent.left
            bottom: parent.bottom
            topMargin: 10
        }

        spacing: 10
        visible: cameraSidePanel.state == "expanded"

        Rectangle {
            width: 0.9 * parent.width
            height: 1
            color: "#353535"
            anchors.left: parent.left
        }
        Button {
            id: cameraListBtn
            text: "Camera List"
            height: itemHeight
            width: parent.width
            onClicked: {

            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true

                onEntered: {
                    lvbg.width = itemWidth * 2
                    cameraSelHover |= 0xf0
//                    lvbg.visible = !lvbg.visible
//                    listCamera.visible = !listCamera.visible
                }

                onExited: {
                    camera_sel_timer.restart()
//                    lvbg.width = 0
                    cameraSelHover &= 0x0f
//                    lvbg.visible = !lvbg.visible
//                    listCamera.visible = !listCamera.visible
                }
            }
        }
//        Rectangle {
//            width: 0.9 * parent.width
//            height: 1
//            color: "#353535"
//            anchors.left: parent.left
//        }
//        Button {
//            text: "Open image"
//            height: itemHeight
//            width: parent.width
//            onClicked: {
//                cameraSidePanel.state = "collapsed"
//                root.openImage()
//            }
//        }
//        Rectangle {
//            width: 0.9 * parent.width
//            height: 1
//            color: "#353535"
//            anchors.left: parent.left
//        }
//        Button {
//            text: "Open video"
//            height: itemHeight
//            width: parent.width
//            onClicked: {
//                cameraSidePanel.state = "collapsed"
//                root.openVideo()
//            }
//        }
//        Rectangle {
//            width: 0.9 * parent.width
//            height: 1
//            color: "#353535"
//            anchors.left: parent.left
//        }
//        Button {
//            text: "Reset"
//            height: itemHeight
//            width: parent.width
//            onClicked: {
//                cameraSidePanel.state = "collapsed"
//                root.close()
//            }
//        }
//        Rectangle {
//            width: 0.9 * parent.width
//            height: 1
//            color: "#353535"
//            anchors.left: parent.left
//        }
    }

    Rectangle{
        id: lvbg
        width: 0 //itemWidth * 2
        opacity: 0.8
//        visible: false
        color: "black"

        anchors {
            left: funcSelect.right
            top: funcSelect.top
            bottom: funcSelect.bottom
        }

        ListView{
            id: listCamera
            width: itemWidth * 2
            anchors.fill: parent
            visible: true

            model: listCameraModel.item
            delegate: listCameraDelegate

            clip: true
            focus: true

            Component {
                id: listCameraDelegate
                Button {
                    text: name
                    width: itemWidth * 2
                    onClicked: {
                        console.log("camera name" + name)
                        console.log("camera id " + deviceId)
//                        listCamera.visible = false
//                        lvbg.visible = false
                        lvbg.width = 0

                        root.switchCamera(deviceId)
                    }
                }
            }
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton

            onEntered: {
                camera_sel_timer.restart()
//                lvbg.width = itemWidth * 2
                cameraSelHover |= 0x0f
            }

            onExited: {
                camera_sel_timer.restart()
//                lvbg.width = 0
                cameraSelHover &= 0xf0
            }
        }
    }

    Loader{
        id: listCameraModel
        source: "qrc:/listview/model/CameraSelectionList.qml"
    }

    Timer{
        id: camera_sel_timer
        interval: 500
        onTriggered: {
            if (cameraSelHover == 0x00){
                lvbg.width = 0
            }
            else{
                lvbg.width = itemWidth * 2
            }
        }
    }
}
