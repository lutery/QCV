import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "自定义阈值"
        method: SImageService.CustomBinaryOpenCV
    }

    ListElement {
        name: "OSTU(大律法)"
        method: SImageService.OSTUOpenCV
    }

    ListElement {
        name: "TRIANGLE(三角函数)"
        method: SImageService.TriangleOpenCV
    }
}
