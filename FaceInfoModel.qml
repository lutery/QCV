import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import FaceService 1.0

ListModel {
    id: rootModel

    Component.onCompleted: {
        var facePaths = FaceService.scanFaceInfos();

        console.log(facePaths.length)

        for (var i = 0; i < facePaths.length; ++i){
            rootModel.append({
                             name: facePaths[i]
                             });
        }
    }
}

