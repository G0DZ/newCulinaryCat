import QtQuick 2.0
import "."
Rectangle {
    id:root
    Rectangle{
        id:mainArea
        color: "gray"//Styles.backgroundColor
        anchors.fill: parent
        Rectangle{
            id: imagesArea
            height: parent.height
            width: parent.width/2
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.centerIn: parent
            color: "yellow"//"transparent"//"yellow"//
            Image{
                id:toFirst
                anchors.left: parent.left
                height: parent.height
                width: parent.height
                source: "../images/chevronFirst.png"
                //anchors.horizontalCenter: parent.horizontalCenter
            }
            Image{
                id:toLeft
                anchors.left: toFirst.right
                height: parent.height
                width: parent.height
                source: "../images/chevronLeft.png"
                //anchors.horizontalCenter: parent.horizontalCenter
            }
            Image{
                id:toRight
                anchors.right: toEnd.left
                height: parent.height
                width: parent.height
                source: "../images/chevronRight.png"
                //anchors.horizontalCenter: parent.horizontalCenter
            }
            Image{
                id:toEnd
                anchors.right: parent.right
                height: parent.height
                width: parent.height
                source: "../images/chevronLast.png"
                //anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
