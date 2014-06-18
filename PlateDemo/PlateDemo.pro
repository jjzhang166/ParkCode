#-------------------------------------------------
#
# Project created by QtCreator 2011-06-30T11:20:48
#
#-------------------------------------------------

QT       += core gui network phonon

INCLUDEPATH += "../Multimedia"
INCLUDEPATH += "../VehicleLicense"
INCLUDEPATH += "../Mysql/include"

LIBS += "../lib/libMultimedia.a"
LIBS += "../lib/libVehicleLicense.a"

TARGET = PlateDemo
TEMPLATE = app

DEFINES += PLATEDEMO_H #RAW_API


SOURCES += main.cpp\
        mainwindow.cpp \
    mythread.cpp \
    ../Common/ommonfunction.cpp

HEADERS  += mainwindow.h \
    mythread.h \
    ../Common/commonfunction.h

FORMS    += mainwindow.ui
