/**
  * 预览窗口面板，实际进行图像处理的地方
  */
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

    /**
      * 图像处理函数
      * param 0: 处理类型
      * param param: 处理参数
      */
    function imageOperation(o, param){
        console.log(o)

        switch (o){
        case SImageService.AutoRectifying:
            console.log("click auto rotate")
            imageService.operaParam = param
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

        // 图像二值化
        case SImageService.GrayBinary:
            imageService.operaParam = param;
            imageService.sltImageOpera(o, imageShow.copyImage())
            break

        case SImageService.TransformImg:
            imageService.operaParam = param;
            imageService.sltImageOpera(o, imageShow.copyImage())
            break

        case SImageService.Remap:
            imageService.operaParam = param
            imageService.sltImageOpera(o, imageShow.copyImage())
            break
        }
    }

    ImageShowItem{
        id: imageShow
        anchors.fill: parent
    }

    // 图像处理服务
    SImageService{
        id: imageService;

        // 处理完成更新图像信号
        onUpdateImg: {
            imageShow.sltQImage(image)
        }
    }

    // 文件拖动控件
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
