import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0
import QtQuick.Dialogs 1.2
import QtMultimedia 5.9
import FaceService 1.0
import QtQuick.Layouts 1.3

Window {
    id:camerawWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    RowLayout{
        anchors.fill: parent

        FaceListPanel{
            id: faceListPanel
            Layout.fillHeight: true
            Layout.minimumWidth: 60
            Layout.preferredWidth: 120
        }

        FaceInfoPanel{
            id: faceInfoPanel
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
