#include "recipeloader.h"
#include "recipeparser.h"

RecipeLoader::RecipeLoader()
{

}

void RecipeLoader::loadRecipeByURL(QString url)
{
    //qDebug() << "Loader get URL: "+url;
    HttpConnect *newConnect = new HttpConnect();
    newConnect->downloadContent(url,CBT_BUFFER,CSM_LOUD);
    connect(newConnect,SIGNAL(contentFinished(QString)),this,SLOT(parseRecipe(QString)));
}

void RecipeLoader::parseRecipe(QString content)
{
    //обработка страницы рецепта
    //qDebug() << "Recipe parser get page!";
    RecipeParser rp;
    if(rp.parse(content)){
        //qDebug() << "Get recipe wia parser!";
        m_recipeModel = rp.getTempRecipe();
        qDebug() << "RecipeName: "+ m_recipeModel->getTitle();
        emit recipeFinished();
    }
}

RecipeModel *RecipeLoader::recipeModel() const
{
    return m_recipeModel;
}

void RecipeLoader::setRecipeModel(RecipeModel *recipeModel)
{
    m_recipeModel = recipeModel;
}
