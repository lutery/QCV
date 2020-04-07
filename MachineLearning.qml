import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0
import "./listview/model"

Rectangle {
    id: machineLearning
    anchors.fill: parent

    signal imgProcess(real type, QtObject param)

    ImageOperaParam {

    }

    RowLayout {
        anchors.fill: parent

        //ToDo 研究如何将其间隔开
        RowLayout {
            Layout.margins: 4
            spacing: 6
    //        arrayWidthSpacing:[0, 0]

            ColumnLayout {
                id: mllayout
                Layout.minimumWidth: 64
                Layout.maximumWidth: 64
                Layout.fillHeight: true
                anchors.left: parent.left

//                Rectangle {
//                    anchors.fill: parent
//                    color: 'blue'
//                }

                ListView {
                    id: mlType
                    anchors.fill: parent
                    delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")
                    model: mlTypeModel
                    clip: true
                    highlight: Rectangle {
                        color: "lightsteelblue"
                        radius: 5
                    }
                }
            }

            ColumnLayout {
                id:methodlayout
                Layout.minimumWidth: 64
                Layout.maximumWidth: 64
                Layout.fillHeight: true
                anchors.left: mllayout.right

//                Rectangle {
//                    anchors.fill: parent
//                    color: 'red'
//                }

                ListView {
                    id: methodType
                    anchors.fill: parent
                    delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")
                    model: mlTypeModel
                    clip: true
                    highlight: Rectangle {
                        color: "lightsteelblue"
                        radius: 5
                    }
                }
            }
        }
    }

    MLTypeModel {
        id: mlTypeModel
    }
}
