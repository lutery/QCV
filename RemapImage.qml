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

            ListView {
                id: methodType
                anchors.fill: parent
                delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")
                model: remapModel.item
                clip: true
                highlight: Rectangle {
                    color: "lightsteelblue"
                    radius: 5
                }

                signal listItemChanged(string panelUrl)
                onListItemChanged: {
                    console.log("remap panel item change")
                    settingPanel.source = panelUrl
                }
            }
        }

        Loader{
            id: settingPanel
            Layout.fillWidth: true
            Layout.fillHeight: true

        }

//        ColumnLayout{

//        }

//        ColumnLayout {

//            Button {
//                text: "水纹"
//                onClicked: {
//                    console.log("开始水纹重采样")
//                    if (methodType.currentIndex >= 0){
//                        var method = methodType.model.get(methodType.currentIndex).method

//                        operaParam.setWaveRange(10)
//                        operaParam.setWaveFreq(2.0)
//                        operaParam.setRemapType(method)

//                        remapPanel.imgProcess(SImageService.Remap, operaParam)
//                    }
//                }
//            }
//        }
    }

    Loader {
        id: remapModel
        source: "qrc:/listview/model/RemapModel.qml"
    }
}
