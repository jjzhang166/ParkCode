#-------------------------------------------------
#
# Project created by QtCreator 2012-06-13T14:55:25
#
#-------------------------------------------------
DEFINES += StartupDebug

QT       += core gui network

MYTARGET = $$quote( PlatformCentralServer%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ThreadLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonWidgetLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyNetwork", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyDatabase", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "PlatformGlobal", "Debug" )

    ##Debug
    contains( DEFINES, StartupDebug ) {
        DESTDIR = "./Debug"
        TARGET = $$sprintf( $$MYTARGET, "" )
        system( copy ..\\LibExeFiles\\Debug\\CommonLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\ThreadLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\ManipulateFileDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\CommonWidgetLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\MyNetworkDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\MyDatabaseDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\ManipulateFileDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\PlatformGlobalDebug.dll .\\Debug )
    }
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ThreadLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonWidgetLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyNetwork", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyDatabase", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "PlatformGlobal", "" )
}

TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
