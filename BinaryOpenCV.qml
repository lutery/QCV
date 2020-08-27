import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import SImageServiceQML 1.0

ListModel {
    ListElement {
        name: "自定义阈值"
        method: SImageService.CustomBinaryOpenCV
        param: "{\"name\":\"threshold\", \"value\":128}"
    }

    ListElement {
        name: "OSTU(大律法)"
        method: SImageService.OSTUOpenCV
        param:""
    }

    ListElement {
        name: "TRIANGLE(三角函数)"
        method: SImageService.TriangleOpenCV
        param:""
    }

    ListElement {
        name: "Adaptive(局部阈值法)"
        method: SImageService.AdapOpenCV
        param:"{\"maxValue\":255, \"method\":0, \"type\":0, \"blockSize\":3, \"delta\":30}"
    }
}
