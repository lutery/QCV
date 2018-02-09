import QtQuick 2.0
import QtMultimedia 5.8
import CameraFilter 1.0

VideoOutput {
    id: root
//    height: width
    source: camera
    filters: [cameraFilter]

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

    CameraFilter{
        id: "cameraFilter"
    }

    function start() { camera.start() }
    function stop() { camera.stop() }
    function switchCamera(deviceid){
        for (var i = 0; i < QtMultimedia.availableCameras.length; ++i){
            if (deviceid == QtMultimedia.availableCameras[i].deviceId){
                camera.deviceId = deviceid
            }
        }
    }
}
