#include "prevrecipeloader.h"
#include "searchparser.h"

PrevRecipeLoader::PrevRecipeLoader()
{

}

void PrevRecipeLoader::loadAllPreviews(QString searchName)
{
    //переводим имя в строке поиска в понятный для парсера вид
    QByteArray result = QTextCodec::codecForName("Windows-1251")->fromUnicode(searchName.toLower())
            .toPercentEncoding();
    //формируем строку выдачи
    QString urlString = "http://www.povarenok.ru/recipes/search/?name=" + result;
    qDebug() << urlString;
    //получаем первую страницу выдачи.
    HttpConnect *newConnect = new HttpConnect();
    newConnect->downloadContent(urlString,CBT_BUFFER,CSM_LOUD);
    connect(newConnect,SIGNAL(contentFinished(QString)),this,SLOT(parsePage(QString)));
}

void PrevRecipeLoader::parsePage(QString content)
{
    //обработка страницы выдачи
    qDebug() << "обработал, запускаю парсер!";
    SearchParser sp;
    if(sp.parse(content)){
        qDebug() << "что-то пропарсили, пробуем на вкус:";
         m_prevRecipeList = new QList<PrevRecipeModel*>(sp.getRecipesList());
         //QDEBUG
//         for(PrevRecipe recipe : allPreview){
//             qDebug() << "\n"+recipe.getTitle()+"   "+recipe.getRecipeUrl()+"\n"
//                                           +recipe.getImgLink()+"\n"+recipe.getRecipeDesc()+"\n"
//                                           +recipe.getAuthorName()+"   "+recipe.getViews()+"   "
//                                           +recipe.getLikes()+"    "+recipe.getVotes()+"\n\n";
//         }
         emit previewsFinished();
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
