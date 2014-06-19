#-------------------------------------------------
#
# Project created by QtCreator 2011-12-29T09:12:16
#
#-------------------------------------------------

QT       += core gui network

TARGET = PlatformServer
TEMPLATE = app
DEFINES += PLATFORM_SERVER

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../Common/ommonfunction.cpp

HEADERS  += mainwindow.h \
    ../../Common/commonfunction.h

FORMS    += mainwindow.ui
