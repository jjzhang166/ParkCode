#-------------------------------------------------
#
# Project created by QtCreator 2012-08-13T16:53:27
#
#-------------------------------------------------

QT       += core gui network

TARGET = WineTest
TEMPLATE = app
LIBS += "../lib/libws2_32.a"

SOURCES += main.cpp\
        mainwindow.cpp \
    qlistener.cpp \
    qmytcpserver.cpp \
    qprocessresponsethread.cpp \
    qresponseevent.cpp

HEADERS  += mainwindow.h \
    qlistener.h \
    qmytcpserver.h \
    qprocessresponsethread.h \
    qresponseevent.h

FORMS    += mainwindow.ui
