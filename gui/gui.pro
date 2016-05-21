TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    controller/coremanager.cpp \
    model/prevrecipemodel.cpp \
    model/qobjectlistmodel.cpp \
    model/prevrecipeloader.cpp \
    model/prevrecipeloadermanager.cpp \
    model/httpconnect.cpp \
    model/searchparser.cpp \
    model/recipemodel.cpp \
    model/recipeloader.cpp

RESOURCES += view/qml.qrc \
    view/images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    controller/coremanager.h \
    model/prevrecipemodel.h \
    model/qquicklist.h \
    model/qobjectlistmodel.h \
    model/prevrecipeloader.h \
    model/prevrecipeloadermanager.h \
    model/httpconnect.h \
    model/recipemodel.h \
    model/searchparser.h \
    model/recipeloader.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/QGumboParser/release/ -lQGumboParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/QGumboParser/debug/ -lQGumboParser
else:unix: LIBS += -L$$OUT_PWD/../libs/QGumboParser/ -lQGumboParser

INCLUDEPATH += $$PWD/../libs/QGumboParser
DEPENDPATH += $$PWD/../libs/QGumboParser

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/release/libQGumboParser.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/debug/libQGumboParser.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/release/QGumboParser.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/debug/QGumboParser.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/libQGumboParser.a
