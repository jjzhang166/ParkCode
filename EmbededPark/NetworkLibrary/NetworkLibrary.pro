#-------------------------------------------------
#
# Project created by QtCreator 2013-01-14T15:02:10
#
#-------------------------------------------------

QT       += core network sql

MYTARGET = $$quote( NetworkLibrary%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "IniConfigFile", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "IniConfigFile", "" )
}

TEMPLATE = lib

DEFINES += NETWORKLIBRARY_LIBRARY

SOURCES += qnetworklibrary.cpp \
    qmytcpserver.cpp \
    qmytcpsocket.cpp \
    qtcpclientsocket.cpp \
    qtcppeersocket.cpp

HEADERS += qnetworklibrary.h\
        NetworkLibrary_global.h \
    qmytcpserver.h \
    qmytcpsocket.h \
    qtcpclientsocket.h \
    qtcppeersocket.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
