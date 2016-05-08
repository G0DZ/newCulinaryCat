import QtQuick 2.5

Item {
    id: menuti
    width:  Styles.menuWidth-1
    height: Styles.menuContentHeight
    property string menuText: ""

    //Rectangle to draw the button
    Rectangle {
        id: rectangleButton
        anchors.fill: parent
        Rectangle{
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            Text {
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 11
                color: "#b2b0b1"
                text: menuti.menuText
            }
        }
    }
}
