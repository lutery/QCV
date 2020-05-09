import QtQuick 2.0
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "水纹重采样"
        methodId: SImageService.Remap_wave
        method: "qrc:/transform/view/resizeTransformPanel.qml"
    }
}
