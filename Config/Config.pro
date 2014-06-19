#-------------------------------------------------
#
# Project created by QtCreator 2011-09-08T10:01:29
#
#-------------------------------------------------

QT       += core gui network phonon

TARGET = Config
TEMPLATE = app
DEFINES += PARAM_CFG_H #RAW_API

INCLUDEPATH += "../Mysql/include"

SOURCES += main.cpp\
        mainwindow.cpp \
    ../Common/ommonfunction.cpp

HEADERS  += mainwindow.h \
    ../Common/commonfunction.h

FORMS    += mainwindow.ui
