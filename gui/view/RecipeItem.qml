import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle{
    id:root
    signal clicked
    property string title: ""
    property string srcImg: ""
    property string views: ""
    property string authorName: ""
    property string recipeDesc: ""
    property string likes: ""
    property string votes: ""
    property string recipeUrl: ""
    //radius: root.width/30
    //smooth: true
    //border.color: "#e4e4e4"
    //border.width: 1
    color:"transparent"
    ScrollView{
        anchors.fill: parent
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn
        //horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        //color:"transparent"
        Rectangle{
            id:mainArea
            width: root.width-20
            height: 1500
            color:"black"
            Rectangle{
                id: titleContent
                anchors.top: parent.top
                width: parent.width
                height: parent.width*0.15
                color:"yellow"
                Rectangle{
                    color:"transparent"
                    anchors.centerIn: parent
                    width: parent.width/2
                    height: parent.height/2
                    Text{
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.centerIn: parent
                        font.pointSize: 16
                        //color: "#b2b0b1"
                        text: title
                    }
                }
            }
            Rectangle{
                id: imageContent
                anchors.top: titleContent.bottom
                width: parent.width
                height: parent.height*0.20
                color: "red"
                Image{
                    anchors.centerIn: parent
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    height: parent.height
                    //width: parent.width
                    source: srcImg
                }
            }
            Rectangle{

            }
        }
    }
}
