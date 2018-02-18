import QtQuick 2.9
import QtMultimedia 5.8

ListModel {
    id: rootModel

    Component.onCompleted: {
//        QtMultimedia.availableCameras[1].deviceId

        for (var i = 0; i < QtMultimedia.availableCameras.length; ++i){
            rootModel.append({
                              name: QtMultimedia.availableCameras[i].displayName,
                              deviceId: QtMultimedia.availableCameras[i].deviceId
                             });
        }
    }
}
