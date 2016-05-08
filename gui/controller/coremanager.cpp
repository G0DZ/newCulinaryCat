#include "coremanager.h"

CoreManager::CoreManager(QObject *parent) : QObject(parent)
{
    pLoader = new PrevRecipeLoaderManager();
    pLoader->start();
    connect(this, SIGNAL (startLoad(QString)),pLoader,SIGNAL(onStuffImpl(QString)));
    connect(pLoader, SIGNAL(loadFinished()),this,SLOT(updateModel()));
}

void CoreManager::updateByName(QString recipeName)
{
    emit startLoad(recipeName);
}

void CoreManager::updateModel()
{
//    PrevRecipeModel *A = new PrevRecipeModel();
//    A->setAuthorName("authorName");
//    A->setImgLink("http://www.povarenok.ru/data/cache/2015may/13/03/1141247_46241-150x150x.jpg");
//    A->setLikes("500");
//    A->setRecipeDesc("Это рецепт поистине королевской ватрушки. Нежнейшая сливочно-творожная начинка просто тает в орту, шоколадное тесто приятно хрустит, а аромат смородины добавляет ему свежесть и кислинку. Это мой любимый рецепт королевской ватрушки. ");
//    A->setRecipeUrl("http://www.povarenok.ru/recipes/show/107907/");
//    A->setTitle("Королевская шоколадно-сливочная ватрушка с черной смородиной");
//    A->setViews("999999");
//    A->setVotes("9999999");
//    PrevRecipeModel *F = new PrevRecipeModel();
//    F->setAuthorName("authorName");
//    F->setImgLink("http://www.povarenok.ru/data/cache/2015may/13/03/1141247_46241-150x150x.jpg");
//    F->setLikes("500");
//    F->setRecipeDesc("Это рецепт поистине королевской ватрушки. Нежнейшая сливочно-творожная начинка просто тает в орту, шоколадное тесто приятно хрустит, а аромат смородины добавляет ему свежесть и кислинку. Это мой любимый рецепт королевской ватрушки. ");
//    F->setRecipeUrl("http://www.povarenok.ru/recipes/show/107907/");
//    F->setTitle("ЧО?");
//    F->setViews("999999");
//    F->setVotes("9999999");
//    QQuickList<PrevRecipeModel> B;
//    B.append(A);
//    B.append(F);
//    //B.emplace_back(A);
//    qDebug() << "hello";
//    //updateReadyFlag = true;
    m_prevRecipelist = (*pLoader->pLoaderImpl->prevRecipeList());

    emit modelChanged(model());
}
