#ifndef PREVRECIPELOADER_H
#define PREVRECIPELOADER_H

#include <QObject>
#include "qquicklist.h"
#include "prevrecipemodel.h"
#include "httpconnect.h"

#define ITEMS_ON_PAGE 10

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
signals:
    void previewsFinished(); //external
    void pageFinished(); //internal
private:
    int currentPage;
    int maxPageCount;
    HttpConnect *newConnect;
    QString urlPrefix;
    QString urlPostfix;
    QList<PrevRecipeModel *> *m_prevRecipeList;
private slots:
    void getPage();
};

#endif // PREVRECIPELOADER_H
