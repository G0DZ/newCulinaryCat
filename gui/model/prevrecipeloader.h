#ifndef PREVRECIPELOADER_H
#define PREVRECIPELOADER_H

#include <QObject>
#include "qquicklist.h"
#include "prevrecipemodel.h"
#include "httpconnect.h"

class PrevRecipeLoader : public QObject
{
    Q_OBJECT
public:
    PrevRecipeLoader();
    QList<PrevRecipeModel *> *prevRecipeList() const;
    void setPrevRecipeList(QList<PrevRecipeModel *> *prevRecipeList);

public slots:
    void loadAllPreviews(QString searchName);
    void parsePage(QString content);
    //void getPage();
signals:
    void previewsFinished();
private:
    QList<PrevRecipeModel *> *m_prevRecipeList;
};

#endif // PREVRECIPELOADER_H
