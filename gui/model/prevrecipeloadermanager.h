#ifndef PREVRECIPELOADERMANAGER_H
#define PREVRECIPELOADERMANAGER_H

#include <QThread>
#include "prevrecipeloader.h"

class PrevRecipeLoaderManager : public QThread
{
    Q_OBJECT
public:
    PrevRecipeLoaderManager();
    void startLoad(QString searchName);
    PrevRecipeLoader *pLoaderImpl;
private:
    void run();
signals:
    void loadFinished(); //external
    void onStuffImpl(QString); //internal
};

#endif // PREVRECIPELOADERMANAGER_H
