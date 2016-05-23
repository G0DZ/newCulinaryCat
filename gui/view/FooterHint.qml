import QtQuick 2.0
import "."
Rectangle {
    id:root
    signal toHome
    signal toEnd
    signal toNextPage
    signal toPrevPage
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
            ButtonHint{
                id:toFirst
                anchors.left: parent.left
                height: parent.height
                width: parent.height
                urlImage: "../images/chevronFirst.png"
                scaleCoef: 1;
                onClicked: {
                    root.toHome()
                }
                //anchors.horizontalCenter: parent.horizontalCenter
            }
            ButtonHint{
                id:toLeft
                anchors.left: toFirst.right
                height: parent.height
                width: parent.height
                urlImage: "../images/chevronLeft.png"
                scaleCoef: 1;
                onClicked: {
                    root.toPrevPage()
                }
                //anchors.horizontalCenter: parent.horizontalCenter
            }
            ButtonHint{
                id:toRight
                anchors.right: toEnd.left
                height: parent.height
                width: parent.height
                urlImage: "../images/chevronRight.png"
                scaleCoef: 1;
                onClicked: {
                    root.toNextPage()
                }
                //anchors.horizontalCenter: parent.horizontalCenter
            }
            ButtonHint{
                id:toEnd
                anchors.right: parent.right
                height: parent.height
                width: parent.height
                urlImage: "../images/chevronLast.png"
                scaleCoef: 1;
                onClicked: {
                    root.toEnd()
                }
                //anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
