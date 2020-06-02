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

        ColumnLayout {
            Layout.fillHeight: true
        }

        Button {
            text: "开始"
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
}
