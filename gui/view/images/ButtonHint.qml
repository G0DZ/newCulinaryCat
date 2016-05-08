import QtQuick 2.0

Item {
    id: button
    width: 30
    height: 25
    property string urlImage: ""
    property string urlImageHover: ""
    property color color: "white"
    property color hoverColor: "#E0DDD7"
    property color pressColor: "#5E63E4"
    property double scaleCoef: 2
    property double typeCoef: 1
    onEnabledChanged: state = ""
    signal clicked

    //Rectangle to draw the button
    Rectangle {
        id: rectangleButton
        anchors.fill: parent
        Image{
            source: (button.state == "") ? urlImage : urlImageHover
            width: parent.width/scaleCoef
            height: width/typeCoef
            anchors.centerIn: parent
        }
    }

    //change the color of the button in differen button states
    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: rectangleButton
                color: hoverColor
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: rectangleButton
                color: pressColor
            }
        }
    ]

    //define transmission for the states
    transitions: [
        Transition {
            from: ""; to: "Hovering"
            ColorAnimation { duration: 200 }
        },
        Transition {
            from: "*"; to: "Pressed"
            ColorAnimation { duration: 10 }
        }
    ]

    //Mouse area to react on click events
    MouseArea {
        hoverEnabled: true
        anchors.fill: button
        onEntered: { button.state='Hovering'}
        onExited: { button.state=''}
        onClicked: { button.clicked();}
        onPressed: { button.state="Pressed" }
        onReleased: {
            if (containsMouse)
              button.state="Hovering";
            else
              button.state="";
        }
    }
}
