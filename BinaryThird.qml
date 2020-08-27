import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "自定义阈值"
        method: SImageService.CustomBinaryThird
        param: "{\"name\":\"threshold\", \"value\":128}"
    }

    ListElement {
        name: "bayer表"
        method: SImageService.BayerDither
        param:"{\"name\":\"bayerRatio\", \"value\":3}"
    }
}
