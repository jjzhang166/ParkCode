#-------------------------------------------------
#
# Project created by QtCreator 2013-02-23T23:38:52
#
#-------------------------------------------------
DEFINES += StartupDebug
#DEFINES += StartupRelease
QT += network xml

INCLUDEPATH += ../DatabaseLibrary
INCLUDEPATH += ../NetworkLibrary
INCLUDEPATH += ../SerialPortLibrary
INCLUDEPATH += ../DatabaseLibrary/Mysql/include

MYTARGET = $$quote( StreetRoadParkServer%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "DatabaseLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "NetworkLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "SerialPortLibrary", "Debug" )

    ##Debug
    contains( DEFINES, StartupDebug ) {
        DESTDIR = "./Debug"
        TARGET = $$sprintf( $$MYTARGET, "" )
        system( copy ..\\LibExeFiles\\Debug\\DatabaseLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\NetworkLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\SerialPortLibraryDebug.dll .\\Debug )
    }
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "DatabaseLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "NetworkLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "SerialPortLibrary", "" )

    contains( DEFINES, StartupRelease ) {
        DESTDIR = "./Release"
        TARGET = $$sprintf( $$MYTARGET, "" )
        system( copy ..\\LibExeFiles\\Release\\DatabaseLibrary.dll .\\Release )
        system( copy ..\\LibExeFiles\\Release\\NetworkLibrary.dll .\\Release )
        system( copy ..\\LibExeFiles\\Release\\SerialPortLibrary.dll .\\Release )
    }
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cmainconfigurator.cpp

HEADERS  += mainwindow.h \
    cmainconfigurator.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images.qrc
