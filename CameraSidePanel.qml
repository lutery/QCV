import QtQuick 2.1
import QtQuick.Controls 2.2

Rectangle {
    id: root
    color: "#151515"

    signal switchCamera(string cameraId)

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
                    lvbg.visible = !lvbg.visible
//                    listCamera.visible = !listCamera.visible
                }

                onExited: {
                    lvbg.visible = !lvbg.visible
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
        width: itemWidth * 2
        opacity: 0.8
        visible: false
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
                        listCamera.visible = false
                        lvbg.visible = false

                        root.switchCamera(deviceId)
                    }
                }
            }
        }
    }

    Loader{
        id: listCameraModel
        source: "qrc:/listview/model/CameraSelectionList.qml"
    }
}
