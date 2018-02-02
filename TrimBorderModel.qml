import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "外接矩形"
        method: SImageService.BoundMat
    }

    ListElement{
        name: "简单切边"
        method: SImageService.Simple
    }

    ListElement{
        name: "统计切边"
        method: SImageService.Count
    }

    ListElement{
        name: "映射切边"
        method: SImageService.Map
    }

    ListElement {
        name: "Canny简单切边"
        method: SImageService.SimpleCanny
    }

    ListElement {
        name: "腐蚀Canny简单切边"
        method: SImageService.SCannyErode
    }

    ListElement {
        name: "腐蚀膨胀Canny简单切边"
        method: SImageService.SCannyEroDil
    }
}
