import QtQuick 2.14

Rectangle {
    anchors.fill: parent

    Row{
       anchors.fill: parent

       ListView {
           id: one_lv
           delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")

           signal listItemChanged(int index)
           Component.onCompleted: {
                one_lv.listItemChanged.connect(one_lv_itemChange)
           }
       }

       ListView {
           id: two_lv
           delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")

           signal listItemChanged(int index)
           Component.onCompleted: {
               two_lv.listItemChanged.connect(two_lv_itemChange)
           }
       }

       ListView {
           id: three_lv
           delegate: Qt.createComponent("qrc:/listview/delegate/RadioDelegate.qml")

           signal listItemChanged(int index)
           Component.onCompleted: {
               three_lv.listItemChanged.connect(three_lv_itemChange)
           }
       }
    }

    function one_lv_itemChange(index){
        console.log("index is " + index)
    }

    function tow_lv_itemChange(index){
        console.log("index is " + index)
    }

    function three_lv_itemChange(index){
        console.log("index is " + index)
    }
}
