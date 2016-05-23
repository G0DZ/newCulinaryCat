#include "prevrecipeloader.h"
#include "searchparser.h"

PrevRecipeLoader::PrevRecipeLoader()
{
    newConnect = new HttpConnect();
    connect(newConnect,SIGNAL(contentFinished(QString)),this,SLOT(parsePage(QString)));
    connect(this,SIGNAL(pageFinished()),this,SLOT(getPage()));
    currentPage = 0;
    maxPageCount = 100;
    urlPrefix = "http://www.povarenok.ru/recipes/search/~";
}

void PrevRecipeLoader::loadAllPreviews(QString searchName)
{
    //переводим имя в строке поиска в понятный для парсера вид
    QByteArray result = QTextCodec::codecForName("Windows-1251")->fromUnicode(searchName.toLower())
            .toPercentEncoding();
    //формируем постфикс выдачи
    urlPostfix = "/?name=" + result;
    //проходим по страницам выдачи

    getPage();
    //newConnect->downloadContent(urlString,CBT_BUFFER,CSM_LOUD);
    //connect(newConnect,SIGNAL(contentFinished(QString)),this,SLOT(parsePage(QString)));
}

void PrevRecipeLoader::parsePage(QString content)
{
    //обработка страницы выдачи
    //qDebug() << "обработал, запускаю парсер!";
    SearchParser sp;
    if(sp.parse(content)){
        //
        if(currentPage == 1){
            qDebug() << "ElementsCount:" << sp.getElementsCount();
            int elementsCount = sp.getElementsCount();
            maxPageCount = (elementsCount+(ITEMS_ON_PAGE-(elementsCount%ITEMS_ON_PAGE)))/ITEMS_ON_PAGE;
        }
        //qDebug() << "что-то пропарсили, пробуем на вкус:";
         m_prevRecipeList = new QList<PrevRecipeModel*>(sp.getRecipesList());

         emit previewsFinished();
         emit pageFinished();
    }
}
void PrevRecipeLoader::getPage()
{
    if(currentPage<maxPageCount){
        currentPage++;
        qDebug() << "Trying to load page...";
        QString urlString = urlPrefix+QString::number(currentPage)+urlPostfix;
        qDebug() << urlString;
        newConnect->downloadContent(urlString,CBT_BUFFER,CSM_LOUD);
    }
}



QList<PrevRecipeModel *> *PrevRecipeLoader::prevRecipeList() const
{
    return m_prevRecipeList;
}

void PrevRecipeLoader::setPrevRecipeList(QList<PrevRecipeModel *> *prevRecipeList)
{
    m_prevRecipeList = prevRecipeList;
}
