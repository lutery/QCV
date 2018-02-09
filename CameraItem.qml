import QtQuick 2.0
import QtMultimedia 5.8

VideoOutput {
    id: root
    height: width
    source: camera

    signal fatalError
    signal sizeChanged

    onHeightChanged: root.sizeChanged()

    Camera {
        id: camera
//        deviceId: QtMultimedia.availableCameras[1].deviceId

        onError: {
            if (Camera.NoError != error) {
                console.log("[qmlvideo] CameraItem.onError error " + error + " errorString " + errorString)
                root.fatalError()
            }
        }

//        imageCapture.onImageCaptured: {
//            preview
//        }
    }

    function start() { camera.start() }
    function stop() { camera.stop() }
}
