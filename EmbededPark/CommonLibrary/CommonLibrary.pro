#-------------------------------------------------
#
# Project created by QtCreator 2013-01-14T15:03:08
#
#-------------------------------------------------

QT       += core gui network sql

DEFINES += _WIN32_WINDOWS=0x0490

MYTARGET = $$quote( CommonLibrary%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
}

TEMPLATE = lib

DEFINES += COMMONLIBRARY_LIBRARY

SOURCES += qcommonlibrary.cpp

HEADERS += qcommonlibrary.h\
        CommonLibrary_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
