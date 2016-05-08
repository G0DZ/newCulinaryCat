TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    controller/coremanager.cpp \
    model/prevrecipemodel.cpp \
    model/qobjectlistmodel.cpp \
    model/prevrecipeloader.cpp \
    model/prevrecipeloadermanager.cpp

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
    model/prevrecipeloadermanager.h
