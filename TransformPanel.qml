import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    id: transformPanel
    anchors.fill: parent

    signal imgProcess(real type, QtObject param)

    ImageOperaParam {

    }

    RowLayout{
        anchors.fill: parent
        Layout.margins: 4
        spacing: 4

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: methodType
                anchors.fill: parent

            }
        }
    }
}
