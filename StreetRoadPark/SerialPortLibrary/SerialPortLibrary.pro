#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T00:15:13
#
#-------------------------------------------------

QT       += network xml

DEFINES += _WIN32_WINDOWS=0x0501
INCLUDEPATH += ../DatabaseLibrary/Mysql/include

MYTARGET = $$quote( SerialPortLibrary%1 )
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

DEFINES += SERIALPORTLIBRARY_LIBRARY

SOURCES += serialportcontroller.cpp \
    qextserialport/win_qextserialport.cpp \
    qextserialport/qextserialport.cpp \
    qextserialport/qextserialbase.cpp \
    creceiverthread.cpp \
    csenderthread.cpp \
    cparserthread.cpp \
    ccomconfigurator.cpp \
    ccomthreadevent.cpp

HEADERS += serialportcontroller.h\
        SerialPortLibrary_global.h \
    qextserialport/win_qextserialport.h \
    qextserialport/qextserialport.h \
    qextserialport/qextserialbase.h \
    creceiverthread.h \
    csenderthread.h \
    cparserthread.h \
    ccomconfigurator.h \
    ccomthreadevent.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
