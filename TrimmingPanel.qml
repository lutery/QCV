import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import SImageServiceQML 1.0

Rectangle {
    id: trimPanel
    anchors.fill: parent

    signal trimBorder(real method, real border,color background)

    RowLayout{
        anchors.fill: parent
        Layout.margins: 4
        spacing: 4

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
//            Layout.alignment: Qt.AlignCenter

//            Rectangle{
//                anchors.fill: parent
//                color: "red"
//            }

            ListView {
                id: methodType
                anchors.fill: parent
                delegate: Qt.createComponent("qrc:/listview/delegate/LVDelegate.qml")
                model: methodTypeModel.item
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            CheckBox{
                id: leftBorder
                text: "左边"
                checked: true
            }

            CheckBox{
                id: rightBorder
                text:"右边"
                checked: true
            }

            CheckBox{
                id: topBorder
                text:"顶边"
                checked: true
            }

            CheckBox{
                id: bottomBorder
                text:"底边"
                checked: true
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
                    console.log("开始裁边");
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

//                    if (simpleTrim.checked){
//                        borderParam |= SImageService.Simple;
//                    }
//                    else if (countTrim.checked){
//                        borderParam |= SImageService.Count;
//                    }
//                    else if (mapTrim.checked){
//                        borderParam |= SImageService.Map;
//                    }

                    if (methodType.currentIndex >= 0){
                        console.log(methodType.currentIndex);
                        var method = methodType.model.get(methodType.currentIndex).method;

                        console.log(method)
                        trimPanel.trimBorder(method, borderParam, "#" + bgColor.text);
                    }

//                    trimPanel.trimBorder(borderParam, "#" + bgColor.text)
                }
            }
        }
    }

    Loader{
        id: methodTypeModel
        source: "qrc:/qml/TrimBorderModel.qml"
    }
}
