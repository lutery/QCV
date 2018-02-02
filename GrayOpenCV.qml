import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "通常算法"
        method: SImageService.GeneralGrayOpenCV
    }
}
