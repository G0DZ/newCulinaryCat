#include "searchparser.h"
#include <QDebug>

SearchParser::SearchParser()
{

}

bool SearchParser::parse(QString content)
{
    //получаем страницу
    htmlPage = content;
    //парсим ее
    doc = new QGumboDocument(QGumboDocument::parse(htmlPage));
    if(!getListPart())
        return false;
    parsePrevCount();
    parsePrevRecipes();
    return true;
}

bool SearchParser::getListPart()
{
    QGumboNode root = doc->rootNode();
    QGumboNode contentPart = root.getElementById("content").front();
    listPart = new QGumboNode(contentPart);
    if(listPart == NULL)
        return false;
    return true;
}

int SearchParser::parsePrevCount()
{
    QGumboNode h1 = listPart->getElementsByTagName(HtmlTag::H1).at(1);
    QGumboNode span = h1.getElementsByTagName(HtmlTag::SPAN).front();
    if(span.innerText() == "ничего не найдено")
        elementsCount = 0;
    else{
        int x = span.innerText().remove(QRegExp("[^\\d]")).toInt();
        //qDebug() << span.innerText().remove(QRegExp("[^\\d]"));
        elementsCount = x;
    }
    //qDebug() << elementsCount;
    return elementsCount;
}

QList<PrevRecipeModel*> SearchParser::parsePrevRecipes()
{
    QList<PrevRecipeModel*> recipes;
    //парсим из root
    QGumboNodes nodes = listPart->getElementsByClassName("uno_recipie");
    if(!nodes.empty()){
        for (const QGumboNode node : nodes){
            PrevRecipeModel *pr = new PrevRecipeModel();
            QGumboNode td = node.getElementsByTagName(HtmlTag::TD).front();
            //тперь парсим h1
            QGumboNode tdH1 = td.getElementsByTagName(HtmlTag::H1).front(); //h1
            QGumboNode h1A = tdH1.getElementsByTagName(HtmlTag::A).front(); //a
            pr->setRecipeUrl(h1A.getAttribute("href"));
            pr->setTitle(h1A.innerText());
            //qDebug() << pr->getTitle() << "   " << pr->getRecipeUrl();
            //парсим описание
            QGumboNode tdtd = td.getElementsByTagName(HtmlTag::TD).at(1); //td
            QGumboNode tdImg = tdtd.getElementsByTagName(HtmlTag::IMG).front(); //a
            pr->setImgLink(tdImg.getAttribute("src"));
            //qDebug() << pr->getImgLink();
            //get tr
            QGumboNode tdtr = td.getElementsByTagName(HtmlTag::TR).front(); //td2
            QGumboNode td2 = tdtr.children().back();
            QGumboNode td2desc = td2.childNodes().front();
            if(td2desc.isText())
                pr->setRecipeDesc(td2desc.getText().simplified());
            //qDebug() << pr->getRecipeDesc();
            //
            QGumboNode userPlace = node.getElementsByClassName("recipie_username").front();
            pr->setAuthorName(userPlace.innerText());
            QGumboNode viewPlace = node.getElementsByClassName("recipie_view").front();
            pr->setViews(viewPlace.innerText());
            QGumboNode likesPlace = node.getElementsByClassName("recipie_favor").back();
            //второй с таким именем
            pr->setLikes(likesPlace.innerText());
            QGumboNode votesPlace = node.getElementsByClassName("recipie_vote").front();
            QGumboNode votesB = votesPlace.getElementsByTagName(HtmlTag::B).front();
            pr->setVotes(votesB.innerText());
            //qDebug() << pr->getAuthorName() << pr->getViews() << pr->getLikes() << pr->getVotes() << "\n";
            recipes.append(pr);
        }
    }
    recipesList = recipes;
    return recipes;
}

int SearchParser::getElementsCount() const
{
    return elementsCount;
}

QList<PrevRecipeModel *> SearchParser::getRecipesList() const
{
    return recipesList;
}

void SearchParser::setRecipesList(const QList<PrevRecipeModel *> &value)
{
    recipesList = value;
}

