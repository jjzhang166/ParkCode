#-------------------------------------------------
#
# Project created by QtCreator 2013-04-26T16:24:47
#
#-------------------------------------------------

QT       += core gui
LIBS += ./lib/libtmControlClient.a

TARGET = JWSIPC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qjwsipcevent.cpp \
    qjwsipcthread.cpp

HEADERS  += mainwindow.h \
    qjwsipcevent.h \
    qjwsipcthread.h

FORMS    += mainwindow.ui
