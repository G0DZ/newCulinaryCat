import QtQuick 2.0

Item {
    Rectangle{
        width: parent.width
        height: parent.height
        AnimatedImage{
            anchors.verticalCenter: parent.verticalCenter
            id: animation;
            width: parent.width
            height: animation.width
            source: "images/BusyIndicator.gif"
        }
    }
}
