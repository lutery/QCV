import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import SImageServiceQML 1.0

Rectangle {
    id: gbPanel
    anchors.fill: parent

    signal gbProcess(real type, real param)

    property var selectLib: 1
    property var selectType: 1
    property var selectMethod: 1

    RowLayout{
        anchors.fill: parent
        Layout.margins: 4
        spacing: 4

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            ButtonGroup{
                id: processMethod
            }

            RadioButton{
                id: kmeansRadio
                text: "OpenCV"
                ButtonGroup.group: processMethod
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
                onClicked: {
                    console.log("OpenCV")
                    selectLib = 1
                    gbPanel.switchMethod()
                }
            }

            RadioButton{
                id: gmmRadio
                text: "Third Part"
                ButtonGroup.group: processMethod
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
                onClicked: {
                    console.log("Third Part")
                    selectLib = 2
                    gbPanel.switchMethod()
                }
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
//            Layout.alignment: Qt.AlignCenter

            ButtonGroup{
                id: processType
            }

            RadioButton{
                id: trainRadio
                text: "灰度"
                ButtonGroup.group: processType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
                onClicked: {
                    console.log("灰度")
                    selectType = 1
                    gbPanel.switchMethod()
                }
            }

            RadioButton{
                id: splitRadio
                text: "二值化"
                ButtonGroup.group: processType
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.topMargin: 4
                checked: true
                focus: true
                onClicked: {
                    console.log("二值化")
                    selectType = 2
                    gbPanel.switchMethod()
                }
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
//            Layout.alignment: Qt.AlignCenter

            ListView {
                id: methodType
                anchors.fill: parent
//                delegate: methodDelegate
                delegate: Qt.createComponent("qrc:/listview/delegate/LVDelegate.qml")
//                model: Qt.createComponent("qrc:/qml/GrayOpenCV.qml").createObject(methodType)
                model: methodTypeModel.item
            }

//            Component{
//                id: methodDelegate
//                Item{
//                    width: parent.width
//                    height: 30

//                    RowLayout{
//                        anchors.fill: parent

//                        ButtonGroup{
//                            id: methodTypeGroup
//                        }

//                        RadioButton{
//                            id: selMethodType
//                            text: name
//                            ButtonGroup.group: methodTypeGroup
//                        }
//                    }
//                }
//            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout{
                Text{
                    text: "参数"
                    height: 60
                }

                TextField{
                    id: gbparam
                    width: 30
                    height: 60
//                    placeholderText: "128"
                    text: "128"
                }
            }

            Button{
                id: trimBorder
                text: "开始处理"
                onClicked: {
                    console.log("开始处理")

                    if (methodType.currentIndex >= 0){
                        console.log(methodType.currentIndex);
                        var method = methodType.model.get(methodType.currentIndex).method;
                        var param = gbparam.text;

                        console.log(method)
                        console.log(param)
                        gbPanel.gbProcess(method, param);
                    }
                }
            }
        }
    }

    Loader{
        id: methodTypeModel
        source: "qrc:/qml/GrayOpenCV.qml"
    }

    function switchMethod(){
        console.log("switchMethod")
        if (selectLib == 1 && selectType == 1){
            console.log("selectLib == 1 && selectType == 1")
            methodTypeModel.source = "qrc:/qml/GrayOpenCV.qml"
        }
        else if (selectLib == 1 && selectType == 2){
            console.log("selectLib == 1 && selectType == 2")
            methodTypeModel.source = "qrc:/qml/BinaryOpenCV.qml"
        }
        else if (selectLib == 2 && selectType == 1){
            console.log("selectLib == 2 && selectType == 1")
            methodTypeModel.source = "qrc:/qml/GrayThird.qml"
        }
        else if (selectLib == 2 && selectType == 2){
            console.log("selectLib == 2 && selectType == 2")
            methodTypeModel.source = "qrc:/qml/BinaryThird.qml"
        }
    }
}

