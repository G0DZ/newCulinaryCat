#include "loadermanager.h"

LoaderManager::LoaderManager()
{
    pLoaderImpl = new PrevRecipeLoader();
    //signal to thread
    connect(this,
           SIGNAL(pStuffImpl(QString)),
           pLoaderImpl,
           SLOT(loadAllPreviews(QString)));
    // signal from thread
    connect(pLoaderImpl,
            SIGNAL(previewsFinished()),
            this,
            SIGNAL(previewsFinished()));
    //
    rLoaderImpl = new RecipeLoader();
    //signal to thread
    connect(this,
           SIGNAL(rStuffImpl(QString)),
           rLoaderImpl,
           SLOT(loadRecipeByURL(QString)));
    // signal from thread
    connect(rLoaderImpl,
            SIGNAL(recipeFinished()),
            this,
            SIGNAL(recipeFinished()));
}

void LoaderManager::loadRecipe(QString recipeURL)
{
    if(rLoaderImpl!=NULL){
        delete rLoaderImpl;
        rLoaderImpl = NULL;
    }
    rLoaderImpl = new RecipeLoader();
    emit rStuffImpl(recipeURL);
}

void LoaderManager::loadPreviews(QString searchName)
{
    if(pLoaderImpl!=NULL){
        delete pLoaderImpl;
        pLoaderImpl = NULL;
    }
    pLoaderImpl = new PrevRecipeLoader();
    emit pStuffImpl(searchName);
}

void LoaderManager::run()
{
    exec();
}
