import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    id: remapPanel

    anchors.fill: parent

    signal imgProcess(real type, QtObject param)

    ImageOperaParam {
        id: operaParam
    }

    RowLayout {
        anchors.fill: parent
        Layout.margins: 4
        spacing: 4

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: methodType
                anchors.fill: parent
                delegate: Qt.createComponent("qrc:/listview/delegate/LVDelegate.qml")
            }
        }
    }
}
