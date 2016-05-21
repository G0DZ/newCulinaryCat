import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import io.app 1.0
import "."

Item {
    id:root
    property QObjectListModel recipeModel
    property int headerHeight: 50
    Rectangle{
        anchors.fill: parent
        ListView {
            id: list
            interactive: false
            anchors.fill: parent
            model: recipeModel
            delegate: Component{
                id:componentModel
                Text {
                    text: display.title+display.authorName
                }
            }
            header: RecipeHeader {
                id: recipeHeaderItem
                width: parent.width
                height: headerHeight
            }

            //focus: true
            //onCurrentItemChanged: {
                //console.log(model.get(list.currentIndex).myTitle + ' selected')
            //    bodyTabs.currentIndex = list.currentIndex
            //}
        } //end ListView
    }
}
