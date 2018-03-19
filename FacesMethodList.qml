import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import FaceService 1.0

ListModel {
    ListElement {
        name: "OpenCV HARR 特征默认算法"
        deviceId: FaceService.OpencvHaarcascade
        type: 2
    }

    ListElement {
        name: "OpenCV FrontalFace"
        deviceId: FaceService.CVFrontalFace
        type: 2
    }

    ListElement {
        name: "OpenCV FrontalFaceAlt"
        deviceId: FaceService.CVFrontalFaceAlt
        type: 2
    }

    ListElement {
        name: "OpenCV FrontalFaceAlt2"
        deviceId: FaceService.CVFrontalFaceAlt2
        type: 2
    }

    ListElement {
        name: "OpenCV FrontalFaceAltTree"
        deviceId: FaceService.CVFrontalFaceAltTree
        type: 2
    }

    ListElement {
        name: "OpenCV FrontalFaceExtended"
        deviceId: FaceService.CVFrontalFaceExtended
        type: 2
    }

    ListElement {
        name: "DLIB OpenCV结合算法"
        deviceId: FaceService.Dlib
        type: 2
    }
}

