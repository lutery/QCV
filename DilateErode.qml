import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    anchors.fill: parent

    property var type: SImageService.Remap_dilate

    signal imgProcessParam(ImageOperaParam param)

    ColumnLayout {
        anchors.fill: parent

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            ComboBox {
                id: morphShape
                model: morphShapeModel.item
                textRole: "name"
                valueRole: "shapeId"

                Layout.fillWidth: true
            }

            RowLayout {
                Layout.fillWidth: true

                Text {
                    id: widthTitle
                    text: qsTr("宽")
                }

                TextEdit {
                    id: widthEdit
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                Layout.fillWidth: true

                Text {
                    id: heightTitle
                    text: qsTr("高")
                }

                TextEdit {
                    id: heightEdit
                    Layout.fillWidth: true
                }
            }
        }

        Button {
            text: "膨胀"
            onClicked: {
                console.log("开始进行形态学操作")
                if (methodType.currentIndex >= 0){
                    var method = methodType.model.get(methodType.currentIndex).method

                    operaParam.setWaveRange(10)
                    operaParam.setWaveFreq(2.0)
                    operaParam.setRemapType(method)

                    remapPanel.imgProcess(SImageService.Remap, operaParam)
                }
            }
        }
    }

    Loader {
        id: morphShapeModel
        source: "qrc:/combox/model/MorphShapeModel.qml"
    }
}
