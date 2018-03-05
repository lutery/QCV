import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle{
    color: "#501B5E20"

    GridLayout{
        columns:2

        Text{
            text:"帧数："
            font.pointSize: 16
            color: "white"
        }

        Text{
            id: fps
            text: curFPS
            font.pointSize: 16
            color: "white"
        }

        Text{
            text:"像素格式："
            font.pointSize: 16
            color: "white"
        }

        Text{
            id: pixelFormat
            font.pointSize: 16
            color: "white"
            text: curPixelFormat
        }
    }
}
