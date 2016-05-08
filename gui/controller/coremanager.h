#ifndef COREMANAGER_H
#define COREMANAGER_H

#include <QObject>
#include "model/qquicklist.h"
#include "model/prevrecipemodel.h"
#include "model/prevrecipeloadermanager.h"

class CoreManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObjectListModel * model READ model NOTIFY modelChanged)
    Q_PROPERTY(QQmlListProperty<PrevRecipeModel> listProperty READ listProperty NOTIFY modelChanged)
public:
    explicit CoreManager(QObject *parent = 0);
    QObjectListModel * model() { return m_prevRecipelist.getModel(); }
    QQmlListProperty<PrevRecipeModel> listProperty() { return QQmlListProperty<PrevRecipeModel>(this,m_prevRecipelist); }

    //обновляет модель в соответствии с указанным названием рецепта
    Q_INVOKABLE void updateByName(QString recipeName);
public slots:
    //обновление модели из загрузчика
    Q_INVOKABLE void updateModel();
signals:
    void startLoad(QString);
    void modelChanged(QObjectListModel *);
private:
    PrevRecipeLoaderManager *pLoader;
    QQuickList<PrevRecipeModel> m_prevRecipelist;
};

#endif // COREMANAGER_H
