import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import SImageServiceQML 1.0

Rectangle {
    id: trimPanel
    anchors.fill: parent

    signal trimBorder(real border,color background)

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
                id: simpleTrim
                text: "简单切边"
                ButtonGroup.group: trimType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: countTrim
                text: "统计切边"
                ButtonGroup.group: trimType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
            }

            RadioButton{
                id: mapTrim
                text: "映射切边"
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

            CheckBox{
                id: leftBorder
                text: "左边"
            }

            CheckBox{
                id: rightBorder
                text:"右边"
            }

            CheckBox{
                id: topBorder
                text:"顶边"
            }

            CheckBox{
                id: bottomBorder
                text:"底边"
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout{
                Text{
                    text: "切边颜色"
                    height: 60
                }

                TextField{
                    id: bgColor
                    width: 30
                    height: 60
                    placeholderText: "000000"
                }
            }

            Button{
                id: trimBorder
                text: "开始裁边"
                onClicked: {
                    console.log("开始裁边")
                    var borderParam = 0

                    if (leftBorder.checked){
                        borderParam |= SImageService.Left;
                    }

                    if (rightBorder.checked){
                        borderParam |= SImageService.Right;
                    }

                    if (topBorder.checked) {
                        borderParam |= SImageService.Top;
                    }

                    if (bottomBorder.checked){
                        borderParam |= SImageService.Bottom;
                    }

                    if (simpleTrim.checked){
                        borderParam |= SImageService.Simple;
                    }
                    else if (countTrim.checked){
                        borderParam |= SImageService.Count;
                    }
                    else if (mapTrim.checked){
                        borderParam |= SImageService.Map;
                    }

                    trimPanel.trimBorder(borderParam, "#" + bgColor.text)
                }
            }
        }
    }
}
