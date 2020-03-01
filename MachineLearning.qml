import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    id: machineLearning
    anchors.fill: parent

    signal imgProcess(real type, QtObject param)

    ImageOperaParam {

    }

    RowLayout {
        anchors.fill: parent
        Layout.margins: 4
        spacing: 4

        ColumnLayout {
            id: mllayout
            Layout.minimumWidth: 64
            Layout.maximumWidth: 64
            Layout.fillHeight: true
            anchors.left: parent.left

            ListView {
                id: mlType
                anchors.fill: parent
                delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")
                model: Qt.createComponent("qrc:/listview/model/MLTypeModel.qml")
                clip: true
                highlight: Rectangle {
                    color: "lightsteelblue"
                    radius: 5
                }
            }
        }
    }
}
