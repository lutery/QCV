import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
    id: radioDelegate
    width: parent.width
    height: 30

    MouseArea {
        anchors.fill: parent
        onClicked: radioDelegate.ListView.view.currentIndex = index
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 8
        Text {
            id: id_radio
            text: qsTr("text")
        }
    }
}
