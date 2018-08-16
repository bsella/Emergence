TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../../src
HEADERS         = LogicPlugin.h
SOURCES         = LogicPlugin.cpp
TARGET          = $$qtLibraryTarget(logicplugin)
DESTDIR         = ../libs
