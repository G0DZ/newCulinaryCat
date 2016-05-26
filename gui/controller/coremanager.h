#ifndef COREMANAGER_H
#define COREMANAGER_H

#include <QObject>
#include "model/qquicklist.h"
#include "model/prevrecipemodel.h"
//#include "model/prevrecipeloadermanager.h"
#include "model/recipemodel.h"
#include "model/loadermanager.h"

class CoreManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObjectListModel * model READ model NOTIFY modelChanged)
    Q_PROPERTY(QQmlListProperty<PrevRecipeModel> listProperty READ listProperty NOTIFY modelChanged)
    Q_PROPERTY(QObjectListModel * recipe READ recipe NOTIFY recipeChanged)
    Q_PROPERTY(QQmlListProperty<RecipeModel> recipeProperty READ recipeProperty NOTIFY recipeChanged)
public:
    explicit CoreManager(QObject *parent = 0);
    QObjectListModel * model() { return m_prevRecipelist.getModel(); }
    QObjectListModel * recipe() { return m_recipeList.getModel(); }
    QQmlListProperty<PrevRecipeModel> listProperty() { return QQmlListProperty<PrevRecipeModel>(this,m_prevRecipelist); }
    QQmlListProperty<RecipeModel> recipeProperty() { return QQmlListProperty<RecipeModel>(this,m_recipeList); }
    //получаем рецепт по указанному URL
    Q_INVOKABLE void getRecipeByURL(QString URL);
    //обновляет модель в соответствии с указанным названием рецепта
    Q_INVOKABLE void updateByName(QString recipeName);
public slots:
    //обновление модели из загрузчика
    Q_INVOKABLE void updateModel();
    //обновление рецепта
    Q_INVOKABLE void updateRecipe();
    //подгрузка страниц
    Q_INVOKABLE void uploadPreview();
signals:
    void loadRecipe(QString);
    void startLoad(QString);
    void modelChanged(QObjectListModel *);
    void recipeChanged(QObjectListModel *);
    void previewUpload();
private:
    LoaderManager *loader;
    QQuickList<PrevRecipeModel> m_prevRecipelist;
    QQuickList<RecipeModel> m_recipeList;
};

#endif // COREMANAGER_H
