import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
    id: radioDelegate
    width: parent.width
    height: 30

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("radio delegate clicked index is " + index)
            radioDelegate.ListView.view.currentIndex = index
            radioDelegate.ListView.view.listItemChanged(index, )
        }
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 8
        Text {
            id: id_radio
            text: name
            font.pixelSize: 18
            Layout.fillWidth: true
        }
    }
}
