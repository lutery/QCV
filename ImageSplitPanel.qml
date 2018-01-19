import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2

Rectangle {
    id: splitPanel
    anchors.fill: parent

    signal imgSplit(real cluserCount)

    RowLayout{
        anchors.fill: parent
        Layout.margins: 4
        spacing: 4

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
//            Layout.alignment: Qt.AlignCenter

            ButtonGroup{
                id: trimType
            }

            RadioButton{
                id: kmeansRadio
                text: "KMeans"
                ButtonGroup.group: trimType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: gmmRadio
                text: "高斯混合模型"
                ButtonGroup.group: trimType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: watershedRadio
                text: "分水岭"
                ButtonGroup.group: trimType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: grabcutRadio
                text: "Grabcut"
                ButtonGroup.group: trimType
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

                    splitPanel.imgSplit(cluserCount.text)
                }
            }
        }
    }
}

