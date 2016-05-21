import QtQuick 2.5

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
    radius: root.width/30
    smooth: true
    border.color: "#e4e4e4"
    border.width: 1
    Rectangle{
        id:mainForm
        radius: root.width/30
        anchors.fill: parent
        color: "lightgray"
        Rectangle{
            id:header
            anchors.top: parent.top
            anchors.topMargin: 5
            width: parent.width-30
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height/6
            color:"transparent"
            Text{
                anchors.centerIn: parent
                color:"black"
                font.pixelSize: 19
                text: root.title
            }
        }
        Rectangle{
            id:body
            anchors.top: header.bottom
            width: parent.width-30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            color:"transparent"
            Rectangle{
                id:imageContainer
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                Image{
                    anchors.fill: parent
                    source: srcImg
                }
            }
            Rectangle{
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left:imageContainer.right
                anchors.right: parent.right
                Rectangle{
                    id:bodyFooter
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: parent.height/6
                    color:"transparent"
                    Rectangle{
                        id:authorN
                        height: parent.height
                        width: parent.width/4
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            color:"black"
                            font.pixelSize: 13
                            text: root.authorName
                        }
                    }
                    Rectangle{
                        id:likesN
                        height: parent.height
                        anchors.left: authorN.right
                        width: parent.width/4
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            color:"black"
                            font.pixelSize: 13
                            text: root.likes
                        }
                    }
                    Rectangle{
                        id:viewsN
                        height: parent.height
                        anchors.left: likesN.right
                        width: parent.width/4
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            color:"black"
                            font.pixelSize: 13
                            text: root.views
                        }
                    }
                    Rectangle{
                        height: parent.height
                        anchors.left: viewsN.right
                        width: parent.width/4
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            color:"black"
                            font.pixelSize: 13
                            text: root.votes
                        }
                    }
                }
                Rectangle{
                    anchors.top: parent.top
                    anchors.bottom:bodyFooter.top
                    width: parent.width
                    color:"gray"
                    Text{
                        width: parent.width
                        color:"black"
                        wrapMode: Text.WordWrap
                        font.pixelSize: 15
                        maximumLineCount: 7
                        elide: Text.ElideRight
                        text: root.recipeDesc
                    }
                }
            }
        }
    }

    //Mouse area to react on click events
    MouseArea {
        anchors.fill: menuit
        onClicked: root.clicked();
    }
}

