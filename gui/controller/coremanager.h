#ifndef COREMANAGER_H
#define COREMANAGER_H

#include <QObject>
#include "model/qquicklist.h"
#include "model/prevrecipemodel.h"

class CoreManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObjectListModel * model READ model NOTIFY modelChanged)
    Q_PROPERTY(QQmlListProperty<PrevRecipeModel> listProperty READ listProperty NOTIFY modelChanged)
public:
    explicit CoreManager(QObject *parent = 0);
    QObjectListModel * model() { return m_personlist.getModel(); }
    QQmlListProperty<PrevRecipeModel> listProperty() { return QQmlListProperty<PrevRecipeModel>(this,m_personlist); }
signals:
    void modelChanged(QObjectListModel *);
private:
    QQuickList<PrevRecipeModel> m_personlist;
};

#endif // COREMANAGER_H
