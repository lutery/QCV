import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0

Window {
    id:previewWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ImageShowItem{
        id: imageShow
        anchors.fill: parent
    }
}
