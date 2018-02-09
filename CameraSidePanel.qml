import QtQuick 2.1
import QtQuick.Controls 2.2

Rectangle {
    id: root
    color: "#151515"

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
            onClicked: fileOpen.state == "expanded" ? fileOpen.state = "collapsed" : fileOpen.state = "expanded"
        }
    }

    Column {
        anchors {
            top: menuField.bottom
            right: parent.right
            left: parent.left
            bottom: parent.bottom
            topMargin: 10
        }

        spacing: 10
        visible: fileOpen.state == "expanded"

        Rectangle {
            width: 0.9 * parent.width
            height: 1
            color: "#353535"
            anchors.left: parent.left
        }
        Button {
            text: "Start camera"
            height: itemHeight
            width: parent.width
            onClicked: {
                fileOpen.state = "collapsed"
                root.openCamera()
            }
        }
        Rectangle {
            width: 0.9 * parent.width
            height: 1
            color: "#353535"
            anchors.left: parent.left
        }
        Button {
            text: "Open image"
            height: itemHeight
            width: parent.width
            onClicked: {
                fileOpen.state = "collapsed"
                root.openImage()
            }
        }
        Rectangle {
            width: 0.9 * parent.width
            height: 1
            color: "#353535"
            anchors.left: parent.left
        }
        Button {
            text: "Open video"
            height: itemHeight
            width: parent.width
            onClicked: {
                fileOpen.state = "collapsed"
                root.openVideo()
            }
        }
        Rectangle {
            width: 0.9 * parent.width
            height: 1
            color: "#353535"
            anchors.left: parent.left
        }
        Button {
            text: "Reset"
            height: itemHeight
            width: parent.width
            onClicked: {
                fileOpen.state = "collapsed"
                root.close()
            }
        }
        Rectangle {
            width: 0.9 * parent.width
            height: 1
            color: "#353535"
            anchors.left: parent.left
        }
    }
}
