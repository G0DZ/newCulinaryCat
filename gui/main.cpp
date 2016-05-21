#include <QApplication>
#include <QQmlApplicationEngine>

#include "controller/coremanager.h"
#include "model/prevrecipemodel.h"
#include "model/qobjectlistmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<PrevRecipeModel>("io.app", 1, 0, "PrevRecipe");
    qmlRegisterType<PrevRecipeModel>("io.app", 1, 0, "Recipe");
    qmlRegisterType<QObjectListModel>("io.app", 1, 0, "QObjectListModel");
    CoreManager * core = new CoreManager();
    engine.rootContext()->setContextProperty("coreManager", core);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
