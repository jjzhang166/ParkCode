#-------------------------------------------------
#
# Project created by QtCreator 2014-08-08T11:04:36
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
