import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import ImageShowItemQML 1.0
import SImageServiceQML 1.0
import SImageOperaParamQML 1.0
import QtQuick.Dialogs 1.2

Window {
    id:saveWin
    visible: false
    width: 640
    height: 480
    title: qsTr("Hello World")

    signal imgProcess(real type, QtObject param)

    FileDialog{
        id: saveDialog
        title: "保存图片"
        folder: shortcuts.home
        selectFolder: false
        selectExisting: false
        nameFilters: ["Image files (*.jpg)", "Image files (*.png)", "Image files (*.bmp)"]
        visible: true
        onAccepted: {
            console.log("You choose: " + saveDialog.fileUrls);

            var filePath = fileUrls[0].substr(8)

            operaParams.setSelectPath(filePath)

            saveWin.imgProcess(SImageService.Save, operaParams)

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
