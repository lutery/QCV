import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQml 2.2
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    id: resizePanel
    anchors.fill: parent

    signal imgProcessParam(QtObject param)

    ImageOperaParam {
        id: operaParams
    }

    ColumnLayout{
        anchors.fill: parent

        spacing: 4

        Label {
            text: "指定尺寸"
            font.pointSize: 18
        }

        RowLayout {
            Layout.topMargin: 8

            Label {
                text: "长："
                font.pointSize: 16
            }

            TextField {
                id: widthParam
            }
        }

        RowLayout {
            Layout.topMargin: 8

            Label {
                text: "宽："
                font.pointSize: 16
            }

            TextField {
                id: heightParam
            }
        }

        Rectangle {
            Layout.fillHeight: true
        }
    }

    Button {
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        text: "开始处理"
        onClicked: {
            var width = parseInt(widthParam.text)
            var height = parseInt(heightParam.text)
            if (width > 0 &&
                    height > 0){
                console.log("width: " + width + ", height: " + height)
                operaParams.setWidthParam(width)
                operaParams.setHeightParam(height)

                resizePanel.imgProcessParam(operaParams)
            }
        }
    }
}
