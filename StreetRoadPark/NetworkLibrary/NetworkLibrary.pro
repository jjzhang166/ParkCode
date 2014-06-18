#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T00:23:00
#
#-------------------------------------------------

QT       += network xml
INCLUDEPATH += ../DatabaseLibrary
INCLUDEPATH += ../DatabaseLibrary/Mysql/include

DEFINES += _WIN32_WINDOWS=0x0501

MYTARGET = $$quote( NetworkLibrary%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )

    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "DatabaseLibrary", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )

    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "DatabaseLibrary", "" )
}

TEMPLATE = lib

DEFINES += NETWORKLIBRARY_LIBRARY

SOURCES += networkcontroller.cpp \
    qsocketthread.cpp \
    qsocketdispatcherthread.cpp \
    qlistenerthread.cpp \
    qdataparserthread.cpp \
    qthreadevent.cpp \
    qmytcpserver.cpp \
    cnetconfigurator.cpp \
    qudpmulticast.cpp \
    qmulticastthread.cpp \
    qlikebroadcastthread.cpp

HEADERS += networkcontroller.h\
        NetworkLibrary_global.h \
    qsocketthread.h \
    qsocketdispatcherthread.h \
    qlistenerthread.h \
    qdataparserthread.h \
    qthreadevent.h \
    qmytcpserver.h \
    cnetconfigurator.h \
    qudpmulticast.h \
    qmulticastthread.h \
    qlikebroadcastthread.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
