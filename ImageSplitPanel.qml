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

            ButtonGroup{
                id: splitType
            }

            RadioButton{
                id: kmeansRadio
                text: "KMeans"
                ButtonGroup.group: splitType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: gmmRadio
                text: "高斯混合模型"
                ButtonGroup.group: splitType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: watershedRadio
                text: "分水岭"
                ButtonGroup.group: splitType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: grabcutRadio
                text: "Grabcut"
                ButtonGroup.group: splitType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
//            Layout.alignment: Qt.AlignCenter

            ButtonGroup{
                id: trainType
            }

            RadioButton{
                id: trainRadio
                text: "KMeans"
                ButtonGroup.group: trainType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: splitRadio
                text: "高斯混合模型"
                ButtonGroup.group: trainType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout{
                Text{
                    text: "分割块"
                    height: 60
                }

                TextField{
                    id: cluserCount
                    width: 30
                    height: 60
                    placeholderText: "2"
                }
            }

            Button{
                id: trimBorder
                text: "图片分割"
                onClicked: {
                    console.log("开始分割")

                    var splitType = 0x00;

                    if (kmeansRadio.checked){
                        splitType = SImageService.KMeans
                    }else if (gmmRadio.checked){
                        splitType = SImageService.GMM
                    }else if (watershedRadio.checked){
                        splitType = SImageService.Watershed
                    }else if (grabcutRadio.checked){
                        splitType = SImageService.GrabCut
                    }

                    operaParams.setClusterCount(cluserCount)
                    operaParams.setImageSplitType(splitType)

//                    splitPanel.imgSplit(splitType, cluserCount.text)
                    splitPanel.imgProcess(SImageService.ImageSplit, operaParams)
                }
            }
        }
    }
}

