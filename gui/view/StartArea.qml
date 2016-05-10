import QtQuick 2.0
import "."
Rectangle {
    id:root
    property string description: "HELLO"
    Rectangle{
        id:mainArea
        color: "grey"
        anchors.fill: parent
        Rectangle{
            id:textArea
            height: parent.height/6
            width: parent.height/2
            color:"yellow"
            anchors.centerIn: parent
            Text{
                color:"black"
                font.pixelSize: 19
                text: root.description
            }
        }
    }
}
