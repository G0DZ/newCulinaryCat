import QtQuick 2.0
import QtQuick.Window 2.1

//! [splash-properties]
Window {
    id: splash
    color: "transparent"
    title: "Splash Window"
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen
    property int timeoutInterval: 2500
    signal timeout
//! [splash-properties]
//! [screen-properties]
    x: (Screen.width - splashImage.width) / 2
    y: (Screen.height - splashImage.height) / 2
//! [screen-properties]
    width: splashImage.width
    height: splashImage.height

    AnimatedImage {
        id: splashImage
        source: "../images/KK.gif"
        MouseArea {
            anchors.fill: parent
            //onClicked: splash.//Qt.quit()
        }
    }
    //! [timer]
    Timer {
        interval: timeoutInterval; running: true; repeat: false
        onTriggered: {
            visible = false
            splash.timeout()
        }
    }
    //! [timer]
    Component.onCompleted: visible = true
}
