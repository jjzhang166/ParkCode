#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T09:32:40
#
#-------------------------------------------------

QT       += core gui network sql

DEFINES += _WIN32_WINDOWS=0x0490

MYTARGET = $$quote( DataProtocol%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
}

TEMPLATE = lib

DEFINES += DATAPROTOCOL_LIBRARY

SOURCES += qdataprotocol.cpp

HEADERS += qdataprotocol.h\
        DataProtocol_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
