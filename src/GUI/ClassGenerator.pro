QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../ClassGenerator/sources/ClassGenerator.cpp \
    ../ClassGenerator/sources/FormattableString.cpp \
    ../ClassGenerator/sources/literals.cpp \
    ../UserClassGenerator/user_literals.cpp \
    ../XMLClassGenerator/sources/XMLClassGenerator.cpp \
    ../XMLClassGenerator/sources/xml_literals.cpp \
    ../JSONClassGenerator/sources/JSONClassGenerator.cpp \
    ../JSONClassGenerator/sources/json_literals.cpp \
    ../INIClassGenerator/sources/INIClassGenerator.cpp \
    ../INIClassGenerator/sources/ini_literals.cpp \
    ../controller/controller.cpp \
    main.cpp \
    sources/Config.cpp \
    sources/IntermediateFormatHandler.cpp \
    sources/MainWindow.cpp \
    sources/TreeEditor.cpp \
    sources/TreeParser.cpp \
    sources/rootconfig.cpp \
    sources/StateHandler.cpp

HEADERS += \
    ../../lib/json.hpp \
    ../ClassGenerator/headers/ClassGenerator.h \
    ../ClassGenerator/headers/FormattableString.h \
    ../ClassGenerator/headers/literals.h \
    ../UserClassGenerator/user_literals.h \
    ../XMLClassGenerator/headers/XMLClassGenerator.h \
    ../XMLClassGenerator/headers/xml_literals.h \
    ../JSONClassGenerator/headers/JSONClassGenerator.h \
    ../JSONClassGenerator/headers/json_literals.h \
    ../INIClassGenerator/headers/INIClassGenerator.h \
    ../INIClassGenerator/headers/ini_literals.h \
    ../controller/controller.h \
    headers/Config.h \
    headers/IntermediateFormatHandler.h \
    headers/MainWindow.h \
    headers/TreeEditor.h \
    headers/TreeParser.h \
    headers/rootconfig.h \
    headers/StateHandler.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/resources.qrc
