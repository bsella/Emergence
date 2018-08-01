#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T20:37:55
#
#-------------------------------------------------

    #check Qt version
    QT_VERSION = $$[QT_VERSION]
    QT_VERSION = $$split(QT_VERSION, ".")
    QT_VER_MAJ = $$member(QT_VERSION, 0)
    QT_VER_MIN = $$member(QT_VERSION, 1)

    lessThan(QT_VER_MAJ, 5) | lessThan(QT_VER_MIN, 7) {
        error(Emergence requires Qt 5.7 or newer but Qt $$[QT_VERSION] was detected.)
    }

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Emergence
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QMAKE_CXXFLAGS += -std=c++17

SOURCES +=\
	src/main.cpp \
	src/mainwindow.cpp \
    src/nodes/CompNode.cpp \
    src/nodes/IfNode.cpp \
    src/nodes/LogicNode.cpp \
    src/nodes/PaletteNode.cpp \
	src/Palette.cpp \
    src/nodes/PixelNode.cpp \
    src/nodes/Node.cpp \
    src/nodes/ConstNode.cpp \
    src/nodes/RenderNode.cpp \
    src/Workspace.cpp \
    src/nodes/MathNode.cpp \
    src/nodes/BitmapNode.cpp \
    src/ExportImageDialog.cpp \
    src/nodes/ColorNode.cpp \
    src/data_t.cpp \
    src/nodes/ComplexNode.cpp \
    src/NodeBox.cpp \
    src/commands.cpp \
    src/nodes/FunctionNode.cpp \
    src/FunctionManager.cpp \
    src/Function.cpp

HEADERS  +=\
    headers/mainwindow.h \
    headers/nodes/Node.h \
    headers/nodes/IfNode.h \
    headers/nodes/LogicNode.h \
    headers/Palette.h \
    headers/nodes/PaletteNode.h \
    headers/nodes/CompNode.h \
    headers/nodes/ConstNode.h \
    headers/nodes/PixelNode.h \
    headers/data_t.h \
    headers/nodes/RenderNode.h \
    headers/Workspace.h \
    headers/nodes/MathNode.h \
    headers/nodes/BitmapNode.h \
    headers/ExportImageDialog.h \
    headers/nodes/ColorNode.h \
    headers/nodes/ComplexNode.h \
    headers/NodeBox.h \
    headers/commands.h \
    headers/signalManager.h \
    headers/nodes/FunctionNode.h \
    headers/FunctionManager.h \
    headers/Function.h

FORMS += forms/mainwindow.ui \
    forms/exportimagedialog.ui \
    forms/functionmanager.ui

INCLUDEPATH+= headers

RESOURCES += \
    application.qrc
