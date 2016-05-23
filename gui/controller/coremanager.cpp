#include "coremanager.h"

CoreManager::CoreManager(QObject *parent) : QObject(parent)
{
    loader = new LoaderManager();
    loader->start();
    connect(this, SIGNAL (startLoad(QString)),loader,SIGNAL(pStuffImpl(QString)));
    connect(loader, SIGNAL(previewsFinished()),this,SLOT(updateModel()));
    connect(this, SIGNAL (loadRecipe(QString)),loader,SIGNAL(rStuffImpl(QString)));
    connect(loader, SIGNAL(recipeFinished()),this,SLOT(updateRecipe()));
}

void CoreManager::getRecipeByURL(QString URL)
{
    emit loadRecipe(URL);
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
    m_prevRecipelist.append(*loader->pLoaderImpl->prevRecipeList());
    //m_prevRecipelist = (*loader->pLoaderImpl->prevRecipeList());

    emit modelChanged(model());
}

void CoreManager::updateRecipe()
{
    m_recipeList.clear();
    m_recipeList.append(loader->rLoaderImpl->recipeModel());

    emit recipeChanged(recipe());
}
