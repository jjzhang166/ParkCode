#-------------------------------------------------
#
# Project created by QtCreator 2011-12-29T09:13:01
#
#-------------------------------------------------

QT       += core gui network

TARGET = PlatformClient
TEMPLATE = app
DEFINES += PLATFORM_CLIENT

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../Common/ommonfunction.cpp

HEADERS  += mainwindow.h \
    ../../Common/commonfunction.h

FORMS    += mainwindow.ui
