import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    id: headerIt
    signal clicked
    Rectangle {
        id: rectangleBack
        color: "#333333"
        anchors.fill: parent
        Rectangle{
            color:"transparent"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 5
            width: parent.width/2
            //height: parent.height/2
            ButtonHint{
                anchors.left: parent.left
                anchors.leftMargin: 10
                height: parent.height
                width: height
                hoverColor: "#E32636"
                pressColor: "#A5260A"
                scaleCoef: 1
                urlImageHover: "images/arrow_back.png"
                urlImage: "images/arrow_back.png"
                onClicked: {
                    //findstr = textA.text
                    //menuit.clicked();
                }
            }
        }
    }

}
