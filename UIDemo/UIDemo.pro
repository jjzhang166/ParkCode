#-------------------------------------------------
#
# Project created by QtCreator 2011-07-29T11:29:36
#
#-------------------------------------------------

QT       += core gui network phonon

TARGET = UIDemo
TEMPLATE = app

INCLUDEPATH += "../."
INCLUDEPATH += "../Mysql/include"

LIBS += "../lib/libmysqlclient.a"
LIBS += "../lib/libmysql.a"

LIBS += "E:\QtSDK\mingw\lib\libgdi32.a"

DEFINES += PLATEDEMO_H

SOURCES += main.cpp\
        mainwindow.cpp \
    monitor.cpp \
    frame.cpp \
    ../Common/ommonfunction.cpp \
    mytask.cpp \
    ../Common/logicinterface.cpp \
    ../Database/mysqldatabase.cpp

HEADERS  += mainwindow.h \
    monitor.h \
    frame.h \
    ../Common/commonfunction.h \
    mytask.h \
    ../Common/logicinterface.h \
    ../Database/mysqldatabase.h

FORMS    += mainwindow.ui \
    monitor.ui \
    frame.ui
