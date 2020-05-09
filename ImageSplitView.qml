import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Rectangle {
    anchors.fill: parent

    RowLayout{
        anchors.centerIn: parent.Center

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

        anchors.bottom: parent.bottom
        anchors.right: parent.right

        onClicked: {
            console.log("开始分割")
            console.log(cluserCount.text)

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

            operaParams.setClusterCount(cluserCount.text)
            operaParams.setImageSplitType(splitType)

//                    splitPanel.imgSplit(splitType, cluserCount.text)
            splitPanel.imgProcess(SImageService.ImageSplit, operaParams)
        }
    }
}
