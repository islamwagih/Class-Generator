QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    sources/Config.cpp \
    sources/IntermediateFormatHandler.cpp \
    sources/MainWindow.cpp \
    sources/TreeEditor.cpp \
    sources/TreeParser.cpp \
    sources/rootconfig.cpp

HEADERS += \
    ../../lib/json.hpp \
    headers/Config.h \
    headers/IntermediateFormatHandler.h \
    headers/MainWindow.h \
    headers/TreeEditor.h \
    headers/TreeParser.h \
    headers/rootconfig.h \
    headers/rootconfig.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/resources.qrc
