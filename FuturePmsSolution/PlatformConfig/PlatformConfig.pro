#-------------------------------------------------
#
# Project created by QtCreator 2012-07-02T17:08:36
#
#-------------------------------------------------

DEFINES += StartupDebug

QT       += core gui

MYTARGET = $$quote( PlatformConfig%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "Debug" )

    ##Debug
    contains( DEFINES, StartupDebug ) {
        DESTDIR = "./Debug"
        TARGET = $$sprintf( $$MYTARGET, "" )
        system( copy ..\\LibExeFiles\\Debug\\CommonLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\ManipulateFileDebug.dll .\\Debug )
    }
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "" )
}

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
