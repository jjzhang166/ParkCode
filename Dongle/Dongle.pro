#-------------------------------------------------
#
# Project created by QtCreator 2012-02-21T09:54:09
#
#-------------------------------------------------

QT       -= gui

TARGET = Dongle
TEMPLATE = lib

DEFINES += DONGLE_LIBRARY

SOURCES += dongle.cpp \
    ETDongle/etdongle.cpp

HEADERS += dongle.h\
        Dongle_global.h \
    ETDongle/etdongle.h
