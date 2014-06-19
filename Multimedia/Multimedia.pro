#-------------------------------------------------
#
# Project created by QtCreator 2011-05-17T15:23:28
#
#-------------------------------------------------

QT       += core network phonon multimedia

TARGET = Multimedia
TEMPLATE = lib
#DESTDIR +=
INCLUDEPATH += "../Mysql/include"

LIBS += "../lib/libDs40xxSDK.a"
LIBS += "../lib/libJVSDK.a"
LIBS += "../lib/libGdi32.a"

DEFINES += MULTIMEDIA_LIBRARY

SOURCES += multimedia.cpp \
    HikSDK/hikvision.cpp \
    ../Common/ommonfunction.cpp \
    TmSDK/tm.cpp \
    JvsSDK/jvssdk.cpp

HEADERS += multimedia.h\
        Multimedia_global.h \
    HikSDK/hikvision.h \
    ../Common/commonfunction.h \
    TmSDK/tm.h \
    JvsSDK/jvssdk.h
