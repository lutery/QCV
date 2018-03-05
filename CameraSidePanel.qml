import QtQuick 2.7
import QtQuick.Controls 2.2

Rectangle {
    id: root
    color: "#151515"

    signal switchCamera(string cameraId)
    signal switchMethod(real methodId)

    property int cameraSelHover: 0x00

    // 侧板的点击按钮
    Rectangle {
        id: menuField
//        可以读取父类属性
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

    // 功能选择面板
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
                    cameraSelHover |= 0x80
                    listCameraModel.source = "qrc:/listview/model/CameraSelectionList.qml"
//                    lvbg.visible = !lvbg.visible
//                    listCamera.visible = !listCamera.visible
                }

                onExited: {
                    camera_sel_timer.restart()
//                    lvbg.width = 0
                    cameraSelHover &= 0x7f
//                    lvbg.visible = !lvbg.visible
//                    listCamera.visible = !listCamera.visible
                }
            }
        }
        Rectangle {
            width: 0.9 * parent.width
            height: 1
            color: "#353535"
            anchors.left: parent.left
        }
        Button {
            id: faceListBtn
            text: "人脸识别算法"
            height: itemHeight
            width: parent.width
            onClicked: {

            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true

                onEntered: {
                    lvbg.width = itemWidth * 2
                    listCameraModel.source = "qrc:/listview/model/FacesMethodList.qml"
                    cameraSelHover |= 0x80
                }

                onExited: {
                    camera_sel_timer.restart()
                    cameraSelHover &= 0x7f
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

//    选择列表代理
//    Component {
//        id: listSelDelegate
//        Button {
//            text: name
//            width: itemWidth * 2
//            onClicked: {
//                console.log("face method name" + name)
//                console.log("face method id " + deviceId)
//                facesMethod.width = 0
//            }
//        }
//    }

    // 相机设备选择
    Rectangle{
        id: lvbg
        // 隐藏采用宽度置零的方式进行
        width: 0 //itemWidth * 2
        opacity: 0.8
//        visible: false
        color: "black"

        // 利用锚点进行定位
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
                        console.log("type " + type)
//                        listCamera.visible = false
//                        lvbg.visible = false

                        if (type == 1){
                            lvbg.width = 0
                            root.switchCamera(deviceId)
                        }
                        else if (type == 2){
                            root.switchMethod(deviceId);
                        }
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

//    Rectangle{
//        id: facesMethod
//        // 隐藏采用宽度置零的方式进行
//        width: 0 //itemWidth * 2
//        opacity: 0.8
////        visible: false
//        color: "black"

//        // 利用锚点进行定位
//        anchors {
//            left: funcSelect.right
//            top: funcSelect.top
//            bottom: funcSelect.bottom
//        }

//        ListView{
//            id: listFaces
//            width: itemWidth * 2
//            anchors.fill: parent
//            visible: true

//            model: listCameraModel.item
//            delegate: listSelDelegate

//            clip: true
//            focus: true
//        }

//        MouseArea{
//            anchors.fill: parent
//            hoverEnabled: true
//            acceptedButtons: Qt.NoButton

//            onEntered: {
//                camera_sel_timer.restart()
//                cameraSelHover |= 0x0f
//            }

//            onExited: {
//                camera_sel_timer.restart()
//                cameraSelHover &= 0xf0
//            }
//        }
//    }

    Loader{
        id: listCameraModel
        source: "qrc:/listview/model/CameraSelectionList.qml"
    }

    // 定时器用于判断是否该把子菜单进行隐藏
    Timer{
        id: camera_sel_timer
        interval: 500
        onTriggered: {
            if (cameraSelHover == 0x00){
                lvbg.width = 0
                facesMethod.width = 0
            }
            else if (cameraSelHover & 0x80 != 0x00){
                lvbg.width = itemWidth * 2
            }
            else if (cameraSelHover & 0x40 != 0x00){
                facesMethod.width = itemWidth * 2
            }
        }
    }
}
