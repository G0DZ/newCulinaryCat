#include "prevrecipeloadermanager.h"

PrevRecipeLoaderManager::PrevRecipeLoaderManager()
{
    pLoaderImpl = new PrevRecipeLoader();
    //signal to thread
    connect(this,
           SIGNAL(onStuffImpl(QString)),
           pLoaderImpl,
           SLOT(loadAllPreviews(QString)));
    // signal from thread
    connect(pLoaderImpl,
            SIGNAL(previewsFinished()),
            this,
            SIGNAL(loadFinished()));
}

void PrevRecipeLoaderManager::startLoad(QString searchUrl)
{
    if(pLoaderImpl!=NULL){
        delete pLoaderImpl;
        pLoaderImpl = NULL;
    }
    pLoaderImpl = new PrevRecipeLoader();
    emit onStuffImpl(searchUrl);
}

void PrevRecipeLoaderManager::run()
{
    exec();
}

