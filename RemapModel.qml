import QtQuick 2.0
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "水纹重采样"
        methodId: SImageService.Remap_wave
        method: "qrc:/remap/WaterWave.qml"
    }

    ListElement {
        name: "膨胀"
        methodId: SImageService.Remap_dilate
        method: "qrc:/remap/DilateErode.qml"
    }

    ListElement {
        name: "腐蚀"
        methodId: SImageService.Remap_erode
        method: "qrc:/remap/DilateErode.qml"
    }
}
