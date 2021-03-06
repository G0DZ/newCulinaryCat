import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import QtGraphicalEffects 1.0
import io.app 1.0
import "."

ApplicationWindow {
    //основные настройки
    id: root;
    //properties
    property bool menuShown: true
    property bool startShown: true
    property bool recipeShown: false
    property bool previewLoading: false
    property int cellSize: 2
    //
    visible: false
    width: 1002
    height: 602
    style: ApplicationWindowStyle {
            background: Rectangle {
                color: "transparent"
                z:10
                border.color: "#d9e1e3"
                border.width: 1
            }
        }
    flags: Qt.FramelessWindowHint |
           Qt.WindowMinimizeButtonHint |
           Qt.Window
    x: (Screen.width - width) / 2
    y: (Screen.height - height) / 2
    //двигаем окно
    MouseArea {
        id: mouseRegion
        anchors.fill: parent;
        property variant clickPos: "1,1"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            root.x += delta.x;
            root.y += delta.y;
        }
    }
    Rectangle{
        id:core
        width: 1000
        height: 600
        anchors.centerIn: parent
        //head
        Rectangle {
            id: head
            width: parent.width
            height: Styles.headerHeight
            color: Styles.backgroundColor//"black"//
            ButtonHint{
                anchors.right: parent.right
                anchors.top: parent.top
                hoverColor: "#E32636"
                pressColor: "#A5260A"
                urlImageHover: "../images/close2.png"
                urlImage: "../images/close1.png"
                onClicked: {
                    Qt.quit();
                }
            }
            ButtonHint{
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.top: parent.top
                hoverColor: "#8d8d8d"
                pressColor: "#6495ED"
                urlImageHover: "../images/hide-white.png"
                urlImage: "../images/hide-gray.png"
                onClicked: {
                    root.visibility = Window.Minimized
                }
            }
        }

        Rectangle{
            id: menu
            color: "white"
            x: 0
            y: Styles.headerHeight
            width: root.menuShown ? Styles.menuWidth : 0
            height: parent.height-Styles.headerHeight
            Behavior on width { NumberAnimation { duration: 100 } }
            BorderImage {
                id: menuShadow
                anchors.top: parent.top
                anchors.right: parent.right
                height: parent.height-15
                //z: -1 /* this will place it below normal_view_ */
                visible: root.menuShown
                source: "../images/shadow.png"
                //verticalTileMode: BorderImage.R
                border { left: 1; }
            }
            Rectangle{
                id:menuHead
                anchors.top: parent.top
                anchors.left: parent.left
                height: 50
                width: parent.width-1
                ButtonHint{
                    width: 50
                    scaleCoef: 1
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    hoverColor: "white"
                    pressColor: "white"
                    visible: root.menuShown ? true : false
                    urlImageHover: "../images/switchOn.png"
                    urlImage: "../images/switchOn.png"
                    onClicked: {
                        root.menuShown = !root.menuShown;
                    }
                }
            }
            Rectangle{
                id:menuBody
                anchors.top: menuHead.bottom
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: parent.width-1
                MenuTitle{
                    id: menuBodyTitle
                    anchors.top: parent.top
                    width: parent.width
                    height: Styles.menuContentHeight
                    menuText: "Поиск рецептов:"
                }
                ListModel {
                   id: menuContent
                   ListElement {
                       myTitle:'По названию'
                       myUrlImage: "../images/File-gray.png"
                       myUrlImageHover: "../images/File-lightblue.png"
                       myUrlImagePressed: "../images/book-lightblue.png"
                   }
                   ListElement {
                       myTitle:'По ингредиентам'
                       myUrlImage: "../images/File-gray.png"
                       myUrlImageHover: "../images/File-lightblue.png"
                       myUrlImagePressed: "../images/book-lightblue.png"
                   }
                   ListElement {
                       myTitle:'По категориям'
                       myUrlImage: "../images/book-gray.png"
                       myUrlImageHover: "../images/book-lightblue.png"
                       myUrlImagePressed: "../images/book-white.png"
                   }
                }
                ListView {
                    id: list
                    interactive: false
                    anchors.top: menuBodyTitle.bottom
                    anchors.bottom: parent.bottom
                    width: parent.width
                    model: menuContent
                    delegate: Component{
                        id:componentModel
                        MenuItem{
                            width: parent.width
                            height: Styles.menuContentHeight
                            urlImage: model.myUrlImage
                            urlImageHover: model.myUrlImageHover
                            urlImagePressed: model.myUrlImagePressed
                            menuText: model.myTitle
                            onClicked: {
                                list.currentIndex = index
                                root.startShown = false;
                            }
                        }
                    }
                    highlight: Rectangle {
                       color: 'blue'
                       visible: !root.startShown
                    }
                    focus: true
                    onCurrentItemChanged: {
                        //console.log(model.get(list.currentIndex).myTitle + ' selected')
                        bodyTabs.currentIndex = list.currentIndex
                    }
                }
            }
        }
        Rectangle{
            id:body
            x: root.menuShown ? Styles.menuWidth : 0
            y: Styles.headerHeight
            width: parent.width-x
            height: parent.height-Styles.headerHeight
            Behavior on x { NumberAnimation { duration: 100 } }
            Rectangle{
                id:bodyHead
                anchors.top: parent.top
                anchors.left: parent.left
                height: 40
                width: parent.width-1
                ButtonHint{
                    width: 50
                    scaleCoef: 1
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    hoverColor: "white"
                    pressColor: "white"
                    visible: root.menuShown ? false : true
                    urlImageHover: "../images/switchOff.png"
                    urlImage: "../images/switchOff.png"
                    onClicked: {
                        root.menuShown = !root.menuShown;
                    }
                }
                BorderImage {
                    id: bodyShadow
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.left: parent.left
                    source: "../images/shadow.png"
                    border { bottom: 1; }
                }
            }
            Rectangle{
                id:bodyContent
                anchors.top: bodyHead.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                StartArea{
                    id: startingPoint
                    anchors.fill: parent
                    contentText: Styles.contentText
                    description: Styles.description
                    visible: root.startShown
                    Component.onCompleted: {
                        list.currentIndex = -1
                    }
                }
                TabView {
                    id: bodyTabs
                    visible: !root.startShown
                    anchors.fill: parent
                    tabsVisible: false
                    frameVisible: false
                    Tab {
                        title: "Red"
                        Rectangle{
                            anchors.fill: parent
                            color:"transparent"
                            RecipeArea{
                                id: tempRecipeArea
                                anchors.fill: parent
                                recipeModel: coreManager.recipe
                                visible: root.recipeShown
                                onBack: {
                                    recipeShown = !recipeShown
                                    tempRecipeArea.loading = !tempRecipeArea.loading
                                }
                                Connections{
                                    target: coreManager
                                    onRecipeChanged: {
                                        tempRecipeArea.loading = false
                                    }
                                }
                            }
                            Rectangle {
                                id: searchArea
                                anchors.fill: parent
                                color: "white"
                                visible: !root.recipeShown
                                FindNameTitle{
                                    id:fnt
                                    height: 50
                                    width: parent.width
                                    onClicked: {
                                        coreManager.updateByName(fnt.findstr)
                                    }
                                }
                                Rectangle{
                                    id:workplace
                                    anchors.top:fnt.bottom
                                    anchors.bottom: parent.bottom
                                    width: parent.width
                                    FooterHint{
                                        id:footer
                                        function incIndex(x) {
                                            if(x < recipesList.count+1-root.cellSize)
                                                return x+root.cellSize
                                            else return x
                                        }
                                        function decIndex(x) {
                                            if(x > -1+root.cellSize)
                                                return x-root.cellSize
                                            else return x
                                        }
                                        anchors.bottom: parent.bottom
                                        width: parent.width
                                        height: 50
                                        color: "orange"
                                        onToHome: {
                                            recipesList.currentIndex = 0
                                            recipesList.positionViewAtBeginning();
                                        }
                                        onToEnd: {
                                            recipesList.currentIndex = recipesList.count
                                            recipesList.positionViewAtEnd();
                                            coreManager.uploadPreview();
                                            root.previewLoading = true;
                                        }
                                        onToNextPage: {
                                            recipesList.currentIndex = incIndex(recipesList.currentIndex)
                                            recipesList.positionViewAtIndex(recipesList.currentIndex,
                                                                            GridView.Contain)
                                            if(recipesList.currentIndex+4 >= recipesList.count){
                                                coreManager.uploadPreview();
                                                root.previewLoading = true
                                            }
                                        }
                                        onToPrevPage: {
                                            recipesList.currentIndex = decIndex(recipesList.currentIndex)
                                            recipesList.positionViewAtIndex(recipesList.currentIndex,
                                                                            GridView.Contain)
                                        }
                                    }
                                    GridView {
                                        id: recipesList
                                        interactive: false
                                        anchors.top: parent.top
                                        anchors.bottom: footer.top
                                        width: parent.width-uploadIndicator.width
                                        cellWidth: (recipesList.width)*0.5;
                                        cellHeight: (parent.height-footer.height)*0.5
                                        flow: GridView.TopToBottom
                                        clip: true
                                        highlightFollowsCurrentItem: false
                                        snapMode: GridView.SnapOneRow
                                        model: coreManager.model
                                        delegate: Item{
                                            id:itemNameModel
                                            width: recipesList.cellWidth;
                                            height: recipesList.cellHeight
                                            Preview{
                                                width: itemNameModel.width-10
                                                height: itemNameModel.height-10
                                                anchors.centerIn: parent
                                                title: display.title
                                                srcImg: display.imgLink
                                                views: display.views
                                                authorName: display.authorName
                                                recipeDesc: display.recipeDesc
                                                likes: display.likes
                                                votes: display.votes
                                                recipeUrl: display.recipeUrl
                                                onClicked: {
                                                    coreManager.getRecipeByURL(recipeUrl)
                                                    //tempRecipeArea.visible = true
                                                    recipeShown = !recipeShown
                                                }
                                            }
                                        }
                                        focus: true
                                        onCurrentItemChanged: {
                                            //console.log(model.get(list.currentIndex).myTitle + ' selected')
                                            //bodyTabs.currentIndex = list.currentIndex
                                        }
                                    }
                                    UploadIndicator{
                                        id: uploadIndicator
                                        height: parent.height-footer.height
                                        width: root.previewLoading ? Styles.busyInd : 0
                                        anchors.top: parent.top
                                        anchors.left: recipesList.right
                                    }
                                    Connections {
                                        target: coreManager
                                        onModelChanged: {
                                            root.previewLoading = false
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Tab {
                        title: "Blue"
                        RecipeArea{
                            anchors.fill: parent
                            recipeModel: coreManager.recipe
                            //contentText: Styles.contentText
                            //description: Styles.description
                            //Component.onCompleted: {
                            //}
                        }

                        //Rectangle { anchors.fill: parent
                        //    color: "blue" }
                    }
                    Tab {
                        title: "Green"
                        Rectangle { anchors.fill: parent
                            color: "green" }
                    }
                }
            }
        }
    }

    property var splashWindow: Splash {
        onTimeout: root.visible = true
    }
}
