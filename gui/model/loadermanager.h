#ifndef LOADERMANAGER_H
#define LOADERMANAGER_H

#include <QThread>
#include "prevrecipeloader.h"
#include "recipeloader.h"

class LoaderManager : public QThread
{
    Q_OBJECT
public:
    LoaderManager();
    void loadRecipe(QString recipeURL);
    void loadPreviews(QString searchName);
    PrevRecipeLoader *pLoaderImpl;
    RecipeLoader *rLoaderImpl;
private:
    void run();
signals:
    void recipeFinished(); //external
    void rStuffImpl(QString); //internal
    //
    void previewsFinished(); //external
    void pStuffImpl(QString); //internal
};

#endif // LOADERMANAGER_H
