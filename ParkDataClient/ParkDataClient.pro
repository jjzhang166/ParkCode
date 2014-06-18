#-------------------------------------------------
#
# Project created by QtCreator 2011-11-02T10:02:13
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = ParkDataClient
TEMPLATE = app
DEFINES += PARKDATACLIENT_APP

INCLUDEPATH += "../Mysql/include"

LIBS += "../lib/libmysqlclient.a"
LIBS += "../lib/libmysql.a"

SOURCES += main.cpp\
        mainwindow.cpp \
    ../Network/tcpclient.cpp \
    ../Network/http.cpp \
    ../Network/udpclient.cpp \
    ../Common/ommonfunction.cpp \
    ../Network/manipulatemessage.cpp \
    ../Network/netcommfunction.cpp \
    ../Network/httpserver.cpp \
    ../Network/httpevent.cpp \
    ../Network/netclient.cpp \
    ../Network/ftp.cpp \
    ../Common/logicinterface.cpp \
    ../Database/mysqldatabase.cpp

HEADERS  += mainwindow.h \
    ../Network/tcpclient.h \
    ../Network/http.h \
    ../Network/CommonData.h \
    ../Network/udpclient.h \
    ../Common/commonfunction.h \
    ../Network/manipulatemessage.h \
    ../Network/netcommfunction.h \
    ../Network/httpserver.h \
    ../Network/httpevent.h \
    ../Network/netclient.h \
    ../Network/ftp.h \
    ../Common/logicinterface.h \
    ../Database/mysqldatabase.h

FORMS    += mainwindow.ui
