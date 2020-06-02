import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: root

    property int itemHeight: 50
    property int itemWidth: 100
    property string sceneSource: ""

    signal sceneChange(string scene)

    ListModel {
        id: functionList
        ListElement { name: "打开预览"; source: "Preview.qml" }
        ListElement { name: "灰度二值化"; source: "GrayBinaryPanel.qml" }
        ListElement { name: "图像分割"; source: "ImageSplitPanel.qml" }
        ListElement { name: "切边"; source: "TrimmingPanel.qml" }
        ListElement { name: "自动纠偏"; source: "RotatePanel.qml" }
        ListElement { name: "保存"; source: "SaveImage.qml" }
        ListElement { name: "打开"; source: "OpenImage.qml" }
        ListElement { name: "相机"; source: "qrc:/camera/CameraPanel.qml" }
        ListElement { name: "人脸识别"; source: "qrc:/camera/FaceRecognition.qml" }
        ListElement { name: "图像变换"; source: "TransformPanel.qml" }
        ListElement { name: "机器学习"; source: "MachineLearning.qml" }
        ListElement { name: "图像重映射/形态学"; source: "RemapImage.qml" }
//        ListElement { name: "Rotate"; source: "CameraRotate.qml" }
//        ListElement { name: "Spin"; source: "CameraSpin.qml" }
    }

    Component {
        id: funcDelegate
        Item {
            width: root.itemWidth
            height: 0.8 * itemHeight

            Button {
                anchors.fill: parent
                anchors.margins: 5
                anchors.rightMargin: 2.5
                anchors.bottomMargin: 0
                text: name
                onClicked: {
                    root.sceneSource = source
                    root.sceneChange(root.sceneSource)
                }
            }
        }
    }

    Flickable {
        anchors.fill: parent
        contentHeight: (itemHeight * (functionList.count + 1))
        clip: true

        Row {
            id: layout
            anchors {
                fill: parent
                topMargin: 5
                bottomMargin: 5
            }

            Column {
                Repeater {
                    model: functionList
                    delegate: funcDelegate
                }
            }
        }
    }

}
