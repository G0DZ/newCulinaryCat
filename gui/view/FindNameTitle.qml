import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    id: menuit
    height: 60
    signal clicked
    property string findstr: ""
    Rectangle {
        id: rectangleBack
        color: "#333333"
        anchors.fill: parent
        Rectangle{
            color:"transparent"
            anchors.centerIn: parent
            width: parent.width/2
            height: parent.height/2
            TextField {
                id:textA
                placeholderText: "Введите название блюда"
                anchors.left: parent.left
                width: parent.width-40
                height: parent.height
                font.pointSize: 13
                focus: true
                text: "микс"
//                Keys.onPressed: {
//                    if (event.key == Qt.Key_Return ||
//                            event.key == Qt.Key_Enter) {
//                        if(event.isAutoRepeat) return
//                        findstr = textA.text
//                        menuit.clicked();
//                        console.log("pressed!")
//                    }
//                }
            }
            ButtonHint{
                anchors.left: textA.right
                anchors.leftMargin: 10
                height: parent.height
                hoverColor: "#E32636"
                pressColor: "#A5260A"
                urlImageHover: "images/close2.png"
                urlImage: "images/close1.png"
                onClicked: {
                    findstr = textA.text
                    menuit.clicked();
                }
            }
        }
    }
}
