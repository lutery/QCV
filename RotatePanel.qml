import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    id: trimPanel
    anchors.fill: parent

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
                id: methodType
                anchors.fill: parent
                delegate: Qt.createComponent("qrc:/listview/delegate/LVDelegate.qml")
                model: methodTypeModel.item
                clip: true
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Dial{
                id: angleDial
                Layout.alignment: Qt.AlignCenter
            }
        }

        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Button{
                id: trimBorder
                text: "旋转"
                onClicked: {
                    console.log("开始裁边");
                    if (methodType.currentIndex >= 0){
                        console.log(methodType.currentIndex);
                        var method = methodType.model.get(methodType.currentIndex).method;

                        console.log(method)

                        operaParams.setRotateMethod(method);
                        operaParams.setRotateParam(angleDial.angle);
                        trimPanel.imgProcess(SImageService.Rotate, operaParams);
                    }
                }
            }
        }
    }

    Loader{
        id: methodTypeModel
        source: "qrc:/qml/RotateModel.qml"
    }
}
