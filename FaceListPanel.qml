import QtQuick 2.7
import QtQuick.Controls 2.2

Rectangle {
    id: root



    ListView{
        anchors.fill: parent
        delegate: Qt.createComponent("qrc:/listview/delegate/LVDelegate.qml")
        model: fileInfoModel.item
    }

    Loader{
        id: fileInfoModel
        source: "qrc:/listview/model/FaceInfoModel.qml"
    }
}
