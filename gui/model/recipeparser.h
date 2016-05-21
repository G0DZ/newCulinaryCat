#ifndef RECIPEPARSER_H
#define RECIPEPARSER_H

#include <qgumbonode.h>
#include <qgumbodocument.h>
#include <QString>
#include "recipemodel.h"

class RecipeParser
{
public:
    RecipeParser();
    ~RecipeParser();
    bool parse(QString content);               //парсим страницу
    bool checkPage();           //проверка мета информации о сайте по html;
    bool getRecipePart();       //получаем часть страницы с рецептом
    QString parseName();        //имя рецепта
    QString parseImage();       //главная картина рецепта
    QString parseViews();       //количество просмотров
    QString parseTimePeaces();        //время приготовления и количество порций
    QString parsePublishDate(); //дата публикации
    QString parseAuthorName();  //имя автора рецепта
    QString parseDesc();        //краткое описание рецепта
    //std::vector<IngredientsGroup> parseIng(); //ингредиенты
    //std::vector<RecipeStep> parseSteps(); //пошаговое приготовление
    //std::vector<RecipeTextElement> parseText(); //текстовое описание рецепта
    //рекурсивный парсинг текстового поля
    //void getTextElement(QGumboNodes nodes, std::vector<RecipeTextElement> *text);
    RecipeModel *getTempRecipe() const;
    void setTempRecipe(RecipeModel *value);
private:
    QString htmlPage;
    QGumboDocument *doc;
    QGumboNode *recipePart;
    RecipeModel* tempRecipe;
};

#endif // RECIPEPARSER_H
