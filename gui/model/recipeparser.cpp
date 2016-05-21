#include "recipeparser.h"

RecipeParser::RecipeParser()
{
    tempRecipe = new RecipeModel();
}

RecipeParser::~RecipeParser()
{
    tempRecipe = NULL;
}


RecipeModel *RecipeParser::getTempRecipe() const
{
    return tempRecipe;
}

void RecipeParser::setTempRecipe(RecipeModel *value)
{
    tempRecipe = value;
}

bool RecipeParser::parse(QString content)
{
    //получаем страницу
    htmlPage = content;
    //парсим ее
    doc = new QGumboDocument(QGumboDocument::parse(htmlPage));
    if(!checkPage() || !getRecipePart())
        return false;
    parseName();
    parseImage();
    parseViews();
    parsePublishDate();
    //parseTimePeaces();
    parseAuthorName();
    parseDesc();
    //parseIng();
    //parseSteps();
    //parseText();
    return true;
}


bool RecipeParser::checkPage()
{
    if(doc == NULL)
        return false;
    QGumboNode root = doc->rootNode();
    QGumboNodes nodes = root.getElementsByTagName(HtmlTag::META);
    for (const QGumboNode node : nodes){
        if(node.hasAttribute("property")){
            if(!QString::compare(node.getAttribute("property"),"og:site_name",Qt::CaseInsensitive)){
                if(!QString::compare(node.getAttribute("content"),"Поварёнок",Qt::CaseInsensitive)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool RecipeParser::getRecipePart()
{
    QGumboNode root = doc->rootNode();
    recipePart = new QGumboNode(root.getElementById("print_body").front());
    if(recipePart == NULL)
        return false;
    return true;
}

QString RecipeParser::parseName()
{
    QGumboNode h1 = recipePart->getElementsByTagName(HtmlTag::H1).front();
    QGumboNode a = h1.getElementsByTagName(HtmlTag::A).front();
    tempRecipe->setTitle(a.innerText());
    return a.innerText();
}

QString RecipeParser::parseImage()
{
    QGumboNode recImg = recipePart->getElementsByClassName("recipe-img").front();
    QGumboNode img = recImg.getElementsByTagName(HtmlTag::IMG).front();
    tempRecipe->setImgLink(img.getAttribute("src"));
    return img.getAttribute("src");
}

QString RecipeParser::parseViews()
{
    //парсим из дива recipe-date-views
    QGumboNode recViews = recipePart->getElementsByClassName("recipe-date-views").front();
    tempRecipe->setViews(recViews.innerText().simplified());
    return tempRecipe->getViews();
}

QString RecipeParser::parseTimePeaces()
{
    ///собстна, менять время и порции будем только тогда, когда поля не пусты
    //парсим из дива recipe-time-peaces
    QGumboNode recTime = recipePart->getElementsByClassName("recipe-time-peaces").front();
    //смотрим детей
    QGumboNodes nodes = recTime.children();
    for (const QGumboNode node : nodes){
        QGumboNodes nodeNodes = node.children();
        if(nodeNodes.size() == 2){ //если время
            QGumboNode time = nodeNodes.back();
            tempRecipe->setTime(time.innerText().simplified());
        }
        if(nodeNodes.size() == 1){ //если порции
            tempRecipe->setPeaces(node.innerText().simplified());
        }
    }
    return "";
}

QString RecipeParser::parsePublishDate()
{
    //парсим из дива recipe-date
    QGumboNode recDateViews = recipePart->getElementsByClassName("recipe-date-views").front();
    //нужен первый потомок иъ этого тега
    QGumboNode recDate = recDateViews.children().front();
    tempRecipe->setPublishDate(recDate.innerText());
    return tempRecipe->publishDate();
}

QString RecipeParser::parseAuthorName()
{
    //парсим из дива author-name
    QGumboNode recAuthorName = recipePart->getElementsByClassName("author-name").front();
    //нужен первый потомок <a> из этого тега
    QGumboNode recAuthorA = recAuthorName.getElementsByTagName(HtmlTag::A).front();
    //в нем только один span
    QGumboNode name = recAuthorA.children().front();
    tempRecipe->setAuthorName(name.innerText());
    return tempRecipe->getAuthorName();
}

QString RecipeParser::parseDesc()
{
    //парсим из дива recipe-short
    QGumboNode recShort = recipePart->getElementsByClassName("recipe-short").front();
    //нужен первый потомок <span> из этого тега
    QGumboNode recDesc = recShort.getElementsByTagName(HtmlTag::SPAN).front();
    //в нем только один span
    tempRecipe->setRecipeDesc(recDesc.innerText());
    return tempRecipe->getRecipeDesc();
}

/*
std::vector<IngredientsGroup> RecipeParser::parseIng()
{
    std::vector<IngredientsGroup> ing;
    //парсим из дива recipe-short
    QGumboNode recIng = recipePart->getElementsByClassName("recipe-ing").front();
    QGumboNodes nodes = recIng.children();
    bool openStructFlag = false;
    for (const QGumboNode node : nodes){
        if(!openStructFlag){
            IngredientsGroup A;
            ing.emplace_back(A);
            openStructFlag = true;
        }
        //ВООБЩЕ-ТО ТУТ ТЕГ <DIV>, но с парсером спорить не стал
        if(node.tag() == HtmlTag::B){
            IngredientsGroup *B = &ing.back();
            B->groupName = node.innerText();
        }
        if(node.tag() == HtmlTag::UL){
            QGumboNodes liNodes = node.children();
            std::vector<QString> innerContent;
            for(const QGumboNode liNode : liNodes){
                //все содержится в span
                QGumboNode innerLi = liNode.getElementsByTagName(HtmlTag::SPAN).front();
                QGumboNode liA = innerLi.getElementsByTagName(HtmlTag::A).front();
                QGumboNode liASpan = liA.getElementsByTagName(HtmlTag::SPAN).front();
                QGumboNode liSpan = innerLi.getElementsByTagName(HtmlTag::SPAN).back();
                QString str;
                if(liASpan.innerText() == liSpan.innerText())
                    str = liASpan.innerText()+" "+innerLi.innerText().simplified();
                else
                    str = liASpan.innerText()+" "+innerLi.innerText().simplified()+" "+liSpan.innerText();
                innerContent.emplace_back(str);
            }
            IngredientsGroup *B = &ing.back();
            B->content = innerContent;
            openStructFlag = false;
        }
    }
    tempRecipe.setIng(ing);
    return ing;
}
*/
//std::vector<RecipeStep> RecipeParser::parseSteps()
//{
//    std::vector<RecipeStep> steps;
//    QGumboNodes recipeStepsPlace = recipePart->getElementsByClassName("recipe-steps");
//    if(recipeStepsPlace.empty())
//        return steps;
//    QGumboNode recipeSteps = recipeStepsPlace.front();
//    //каждый шаг - своя табличка, поэтому
//    QGumboNodes nodes = recipeSteps.getElementsByTagName(HtmlTag::TABLE);
//    RecipeStep singleStep;
//    for (const QGumboNode node : nodes){
//        QGumboNodes tds = node.getElementsByTagName(HtmlTag::TD);
//        QGumboNode td1 = tds.front();
//        QGumboNode td1A = td1.getElementsByTagName(HtmlTag::A).front();
//        singleStep.highImageLink = td1A.getAttribute("href");
//        QGumboNode td1AImg = td1A.getElementsByTagName(HtmlTag::IMG).front();
//        singleStep.lowImageLink = td1AImg.getAttribute("src");
//        QGumboNode td2 = tds.back();
//        singleStep.text = td2.innerText();
//        steps.emplace_back(singleStep);
//    }
//    //поехали
//    tempRecipe.setSteps(steps);
//    return steps;
//}

//std::vector<RecipeTextElement> RecipeParser::parseText()
//{
//    std::vector<RecipeTextElement> text;
//    QGumboNode recipeTextPlace = recipePart->getElementsByClassName("recipe-text").front();
//    QGumboNodes nodes = recipeTextPlace.childNodes();
//    if(nodes.empty())
//        return text;
//    getTextElement(nodes,&text);
//    tempRecipe.setText(text);
//    return text;
//}

//void RecipeParser::getTextElement(QGumboNodes nodes, std::vector<RecipeTextElement> *text)
//{
//    for (const QGumboNode node : nodes){
//        if(node.isText()){
//            RecipeTextElement textElement;
//            textElement.type = RecipeTextType::TEXT;
//            textElement.text = node.getText().simplified();
//            text->emplace_back(textElement);
//        }
//        else{
//            if(node.isElement()){
//                    if(node.tag() == HtmlTag::BR){
//                        ///чушь.
//                        /// эти четыре строки сейчас будут повторяться, а я не знаю, как это изменить
//                        RecipeTextElement textElement;
//                        textElement.type = RecipeTextType::TEXT;
//                        textElement.text = "\n";
//                        text->emplace_back(textElement);
//                    } else
//                        if(node.tag() == HtmlTag::A && node.childNodes().empty()){
//                            RecipeTextElement textElement;
//                            textElement.type = RecipeTextType::HREF;
//                            textElement.text = node.getAttribute("href");
//                            text->emplace_back(textElement);
//                        } else
//                            if(node.tag() == HtmlTag::IMG){
//                                if(node.getAttribute("class")!="smile"){
//                                    RecipeTextElement textElement;
//                                    textElement.type = RecipeTextType::IMAGE;
//                                    QString temp = node.getAttribute("src");
//                                    if(temp.left(12) == "/data/cache/")
//                                        textElement.text = "http://www.povarenok.ru"+temp;
//                                    else
//                                        textElement.text = temp;
//                                    text->emplace_back(textElement);
//                                }
//                            } else
//                                if(node.tag() ==HtmlTag::BLOCKQUOTE ||
//                                   node.tag() ==HtmlTag::STRONG ||
//                                   node.tag() ==HtmlTag::I ||
//                                   (node.tag() == HtmlTag::A && !node.childNodes().empty())){
//                                    getTextElement(node.childNodes(),text);
//                                }

//            }
//        }
//    }
//}
