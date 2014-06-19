#-------------------------------------------------
#
# Project created by QtCreator 2013-01-14T15:01:15
#
#-------------------------------------------------

QT       += core gui network sql

DEFINES += _WIN32_WINDOWS=0x0490
MYTARGET = $$quote( ThreadLibrary%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "NetworkLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "IniConfigFile", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "DataProtocol", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "NetworkLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "IniConfigFile", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "DataProtocol", "" )
}

TEMPLATE = lib
DEFINES += THREADLIBRARY_LIBRARY

SOURCES += qthreadlibrary.cpp \
    qmythread.cpp \
    qlistenerthread.cpp \
    qsocketdispatcherthread.cpp \
    qsocketthread.cpp \
    qlogthread.cpp \
    qdataparserthread.cpp \
    qdatabasethread.cpp \
    qthreadevent.cpp

HEADERS += qthreadlibrary.h\
        ThreadLibrary_global.h \
    qmythread.h \
    qlistenerthread.h \
    qsocketdispatcherthread.h \
    qsocketthread.h \
    qlogthread.h \
    qdataparserthread.h \
    qdatabasethread.h \
    qthreadevent.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
