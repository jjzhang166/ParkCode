#-------------------------------------------------
#
# Project created by QtCreator 2013-03-21T16:22:37
#
#-------------------------------------------------

QT       += core

QT       -= gui
INCLUDEPATH += ../DatabaseLibrary/Mysql/include
LIBS += ../DatabaseLibrary/Mysql/lib/liblibmysql.a
DEFINES += _WIN32_WINDOWS=0x0501
TARGET = Test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
