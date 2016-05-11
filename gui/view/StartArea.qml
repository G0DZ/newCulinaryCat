import QtQuick 2.0
import "."
Rectangle {
    id:root
    property string description: "Добро пожаловать!"
    property string contentText: "Продолжите работу с программой, выбрав соответсвующий пункт меню"
    Rectangle{
        id:mainArea
        //color: Styles.backgroundColor
        anchors.fill: parent
        Rectangle{
            id:textArea
            height: parent.height/2
            width: parent.height/1.5
            color: "transparent"//"yellow"
            anchors.centerIn: parent
            Image{
                anchors.top: parent.top
                source: "../images/startArea.png"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text{
                id:descriptionText
                anchors.centerIn: parent
                color:"black"
                font.pixelSize: 19
                text: root.description
            }
            Text{
                anchors.top: descriptionText.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                color:"gray"
                font.pixelSize: 14
                text: root.contentText
            }
        }
    }
}
