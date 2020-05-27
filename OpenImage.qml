import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0
import QtQuick.Dialogs 1.2

Window {
    id:previewWin
    visible: false
    width: 640
    height: 480
    title: qsTr("Hello World")

    FileDialog{
        id: saveDialog
        title: "打开图片"
        folder: shortcuts.home
        selectFolder: false
        selectExisting: true
        nameFilters: ["Image files (*.jpg)", "Image files (*.png)", "Image files (*.bmp)"]
        visible: true
        onAccepted: {
            console.log("You choose: " + saveDialog.fileUrls);

            var filePath = fileUrls[0].substr(8)

            operaParams.setSelectPath(filePath)

            previewWin.imageOperation(SImageService.Open, operaParams)

            console.log(filePath)

            previewWin.close()
//            Qt.quit()
        }

        onRejected: {
            console.log("Canceled")
//            Qt.quic()
            previewWin.close()
        }
    }
}
