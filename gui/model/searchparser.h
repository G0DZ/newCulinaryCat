#ifndef SEARCHPARSER_H
#define SEARCHPARSER_H

#include <qgumbonode.h>
#include <qgumbodocument.h>
#include <QString>
#include "prevrecipemodel.h"

class SearchParser
{
public:
    SearchParser();
    bool parse(QString content);               //парсим страницу, основная функция
    QList<PrevRecipeModel *> getRecipesList() const;
    void setRecipesList(const QList<PrevRecipeModel *> &value);

private:
    bool getListPart();         //пытаемся получить часть страницы с списком рецептов
    int parsePrevCount();       //получаем количество рецептов
    QList<PrevRecipeModel*> parsePrevRecipes(); //получаем рецепты с данной страницы

    //переменные
    int elementsCount;          //количество рецептов ВСЕГО
    QList<PrevRecipeModel *> recipesList;
    QString htmlPage;
    QGumboDocument *doc;
    QGumboNode *listPart;
};

#endif // SEARCHPARSER_H
