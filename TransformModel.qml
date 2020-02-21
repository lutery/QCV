import QtQuick 2.0
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "缩放"
        method: "qrc:/transform/view/resizeTransformPanel.qml"
        methodId: 1
    }

    ListElement {
        name: "平移"
        method: ""
        methodId: 2
    }
}
