import QtQuick 2.0

Item {
    id: menuit
    width:  Styles.menuWidth-1
    height: Styles.menuContentHeight
    property string menuText: ""
    property string urlImage: ""
    property string urlImageHover: ""
    property string urlImagePressed: ""
    onEnabledChanged: state = ""
    signal clicked

    //Rectangle to draw the button
    Rectangle {
        id: rectangleButton
        color: "transparent" //иначе подсветку не будет видно
        anchors.fill: parent
        Image{
            id: menuImage
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: 25
            height: 25
            function getHandColor()
            {
                if(menuit.state == "")
                    return urlImage
                if(menuit.state == "Hovering")
                    return urlImageHover
                if(menuit.state == "Pressed")
                    return urlImagePressed
            }
            source: getHandColor()
        }
        Rectangle{
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: menuImage.right
            anchors.leftMargin: 10
            Text {
                anchors.verticalCenter: parent.verticalCenter
                function getTextColor()
                {
                    if(menuit.state == "")
                        return "black"
                    if(menuit.state == "Hovering")
                        return "black"
                    if(menuit.state == "Pressed")
                        return "white"
                }
                color: getTextColor()
                font.pointSize: 12
                text: menuit.menuText
            }
        }
    }
    //change the color of the button in differen button states
    states: [
        State {
            name: "Hovering"
        },
        State {
            name: "Pressed"
        }
    ]

    //define transmission for the states
    transitions: [
        Transition {
            from: ""; to: "Hovering"
            ColorAnimation { duration: 300 }
        },
        Transition {
            from: "*"; to: "Pressed"
            ColorAnimation { duration: 300 }
        }
    ]

    //Mouse area to react on click events
    MouseArea {
        hoverEnabled: true
        anchors.fill: menuit
        onEntered: { menuit.state='Hovering'}
        onExited: { menuit.state=''}
        onClicked: { menuit.clicked(); menuit.state="Pressed"}
        onReleased: {
            if (containsMouse)
              menuit.state="Hovering";
            else
              menuit.state="";
        }
    }
}
