import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    id: splitPanel
    anchors.fill: parent

//    signal imgSplit(real splitType, real cluserCount)
    signal imgProcess(real type, QtObject param)

    ImageOperaParam {
        id: operaParams
    }

    RowLayout{
        anchors.fill: parent
        Layout.margins: 4
        spacing: 4

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
//            Layout.alignment: Qt.AlignCenter

            ListView {
                id: splitType
                anchors.fill: parent

                delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")
                model: splitTypeModel.item
                clip: true
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                signal listItemChanged(string dstPanel)
                onListItemChanged: {
                    console.log("image split panel dstpanel is " + dstPanel)

                    settingPanel.source = dstPanel
                }
            }
        }

        Loader {
            id: settingPanel

            Layout.fillWidth: true
            Layout.fillHeight: true

            source: "qrc:/view/imagesplit/ImageSplitView.qml"
        }
    }

    Loader {
        id: splitTypeModel
        source: "qrc:/listview/model/ImageSplit.qml"
    }
}

