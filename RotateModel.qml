import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "手动旋转"
        method: SImageService.ManualRotate
    }

    ListElement {
        name: "自动纠偏"
        method: SImageService.AutoRectifying
    }
}
