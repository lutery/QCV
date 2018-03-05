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
        name: "DLIB OpenCV结合算法"
        deviceId: FaceService.Dlib
        type: 2
    }
}

