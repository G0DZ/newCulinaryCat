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
    m_prevRecipelist = (*pLoader->pLoaderImpl->prevRecipeList());
    emit modelChanged(model());
}
