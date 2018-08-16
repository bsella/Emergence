include(../Emergence.pri)

QT += core gui widgets

TARGET = Emergence
TEMPLATE = app

FORMS += mainwindow.ui
HEADERS += mainwindow.h\
           data_t.h\
           Node.h\
           Workspace.h\
           NodeInterface.h\
           NodeBox.h
SOURCES += mainwindow.cpp\
           main.cpp\
           data_t.cpp\
           Node.cpp\
           Workspace.cpp\
           NodeBox.cpp

RESOURCES += src.qrc

INCLUDEPATH += ../src\
               ../plugins

target.path= ..
INSTALLS += target
