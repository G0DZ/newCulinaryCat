#ifndef RECIPELOADER_H
#define RECIPELOADER_H

#include <QObject>
#include "qquicklist.h"
#include "recipemodel.h"
#include "httpconnect.h"

class RecipeLoader : public QObject
{
    Q_OBJECT
public:
    RecipeLoader();
public slots:
    void loadRecipeByURL(QString url);
    void parseRecipe(QString content);
signals:
    void recipeFinished();
private:
    RecipeModel m_recipeModel;
};

#endif // RECIPELOADER_H
