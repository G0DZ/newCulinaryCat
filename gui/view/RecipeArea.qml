import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import io.app 1.0
import "."

Item {
    id:root
    signal back
    property bool loading:true
    property QObjectListModel recipeModel
    property int headerHeight: Styles.recipeHeaderHeight
    Rectangle{
        anchors.fill: parent
        AnimatedImage{
            id: animation;
            visible:loading
            source: "images/BusyIndicator.gif"
        }
        ListView {
            id: list
            visible: !loading
            interactive: false
            anchors.fill: parent
            header: RecipeHeader {
                id: recipeHeaderItem
                width: parent.width
                height: headerHeight
                onClicked: {
                    root.back();
                }
            }
            model: recipeModel
            delegate: Component{
                id:componentModel
                RecipeItem{
                    width: list.width
                    height: list.height-headerHeight
                    title: display.title
                    srcImg: display.imgLink
                    views: display.views
                    authorName: display.authorName
                    recipeDesc: display.recipeDesc
                    likes: display.likes
                    votes: display.votes
                    recipeUrl: display.recipeUrl
                    color:"transparent"
                }
            }
        } //end ListView
    }
}
