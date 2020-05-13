import QtQuick 2.0
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "KMeans"
        method: "qrc:/view/imagesplit/ImageSplitView.qml"
        methodId: 1
    }

    ListElement {
        name: "高斯混合模型"
        method: "qrc:/view/imagesplit/ImageSplitView.qml"
        methodId: 2
    }

    ListElement {
        name: "分水岭"
        method: "qrc:/view/imagesplit/ImageSplitView.qml"
        methodId: 3
    }

    ListElement {
        name: "Grabcut"
        method: "qrc:/view/imagesplit/ImageSplitView.qml"
        methodId: 4
    }

    ListElement {
        name: "简单颜色检测"
        method: "qrc:/view/imagesplit/ColorDectedView.qml"
        methodId: 5
    }
}
