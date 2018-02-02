import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0

Window {
    id:previewWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    function imageOperation(o, param){
        console.log(o)

        switch (o){
        case SImageService.AutoRectifying:
            console.log("click auto rotate")
            imageService.sltImageOpera(o, imageShow.copyImage())
            break

        case SImageService.TrimBorder:
            imageService.operaParam = param;
            imageService.sltImageOpera(o, imageShow.copyImage())
            break

        case SImageService.ImageSplit:
            imageService.operaParam = param;
            imageService.sltImageOpera(o, imageShow.copyImage())
            break

        case SImageService.Save:
            imageService.operaParam = param;
            imageService.sltImageOpera(o, imageShow.copyImage())
            break;

        case SImageService.GrayBinary:
            imageService.operaParam = param;
            imageService.sltImageOpera(o, imageShow.copyImage())
        }
    }

    ImageShowItem{
        id: imageShow
        anchors.fill: parent
    }

    SImageService{
        id: imageService;

        onUpdateImg: {
            imageShow.sltQImage(image)
        }
    }

    DropArea {
        anchors.fill: parent
        onDropped: {
            if (drop.hasUrls){
                for (var i = 0; i < drop.urls.length; ++i){
                    var fileurl = drop.urls[i].substr(8).replace(/\//g, "\\")
                    console.log(fileurl)
                    imageShow.sltQImage(fileurl)
                }
            }
        }
    }

    Button{
        text: "撤销"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10

        onClicked: {
            imageService.undo()
        }
    }

    Button{
        text: "恢复"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10

        onClicked: {
            imageService.redo()
        }
    }
}
