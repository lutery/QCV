/**
  * 灰度二值化qml面板
  */
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import Qt.labs.settings 1.1
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    id: gbPanel
    anchors.fill: parent

//    signal gbProcess(real type, real param)
    // 信号 发送二值化类型以及相关的处理参数
    signal imgProcess(real type, QtObject param)

    property var selectLib: 1
    property var selectType: 1
    property var selectMethod: 1

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
//                model: Qt.createComponent("qrc:/listview/model/GrayOpenCV.qml").createObject(methodType)
                model: methodTypeModel.item

                signal listItemChanged(int index)

                onListItemChanged: {
                    console.log(index)

                    gbparam.text = methodType.model.get(index).param
                }
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
            id: paramLayout

            Layout.fillWidth: true
            Layout.fillHeight: true

            Text{
                id: paramTxt
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                text: "参数"
                height: 60
            }

            Rectangle {

                Layout.fillHeight: true
//                Layout.fillWidth: true
                width:gbPanel.width / 4

                border.color: "black"
                border.width: 2
                smooth: true
                radius: 5

                TextArea{
                    id: gbparam

                    anchors.fill: parent
//                    Layout.fillWidth: true
//                    Layout.fillHeight: true
//                    width: Layout.fillWidth
//                    height: Layout.fillHeight
//                    Layout.alignment: Qt.AlignLeft |  Qt.AlignRight | Qt.AlignTop | Qt.AlignBottom

    //                    placeholderText: "128"
                    text: "128\n128\n128\n128\n128\n128\n128\n128\n128\n128\n128\n128"

                    wrapMode: Text.WordWrap
                }
            }

            Button{
                id: trimBorder
                text: "开始处理"

                Layout.alignment: Qt.AlignBottom | Qt.AlignRight

                onClicked: {
                    console.log("开始处理")

//                    var paramsJson = "{\"name\":\"ceshi\", \"list\":[1, 2, 3, 4]}";
//                    var jsonObj = JSON.parse(paramsJson)
//                    console.log(jsonObj)

                    if (methodType.currentIndex >= 0){

                        console.log(methodType.currentIndex);
                        var method = methodType.model.get(methodType.currentIndex).method;
                        var param = gbparam.text;

                        console.log(method)
                        console.log(param)

                        operaParams.setGBMethod(method)
                        operaParams.setJsonParam(param)
//                        if (method == SImageService.BayerDither)
//                        {
//                            if (param > 4)
//                            {
//                                param = 4
//                            }
//                            else if (param < 1)
//                            {
//                                param = 1
//                            }

//                            operaParams.setBayerParam(param)
//                        }
//                        else
//                        {
//                            operaParams.setGBParam(param)
//                        }

//                        gbPanel.gbProcess(method, param);
                        gbPanel.imgProcess(SImageService.GrayBinary, operaParams);
                    }
                }
            }
        }
    }

    Loader{
        id: methodTypeModel
        source: "qrc:/listview/model/GrayOpenCV.qml"
    }

    function switchMethod(){
        console.log("switchMethod")
        if (selectLib == 1 && selectType == 1){
            console.log("selectLib == 1 && selectType == 1")
            methodTypeModel.source = "qrc:/listview/model/GrayOpenCV.qml"
        }
        else if (selectLib == 1 && selectType == 2){
            console.log("selectLib == 1 && selectType == 2")
            methodTypeModel.source = "qrc:/listview/model/BinaryOpenCV.qml"
        }
        else if (selectLib == 2 && selectType == 1){
            console.log("selectLib == 2 && selectType == 1")
            methodTypeModel.source = "qrc:/listview/model/GrayThird.qml"
        }
        else if (selectLib == 2 && selectType == 2){
            console.log("selectLib == 2 && selectType == 2")
            methodTypeModel.source = "qrc:/listview/model/BinaryThird.qml"
        }
    }
}

