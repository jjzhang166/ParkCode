#-------------------------------------------------
#
# Project created by QtCreator 2013-01-14T14:57:28
#
#-------------------------------------------------

DEFINES += StartupDebug

QT       += core gui network
MYTARGET = $$quote( Administrator%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "DatabaseLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ThreadLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "IniConfigFile", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "NetworkLibrary", "Debug" )

    ##Debug
    contains( DEFINES, StartupDebug ) {
        DESTDIR = "./Debug"
        TARGET = $$sprintf( $$MYTARGET, "" )
        system( copy ..\\LibExeFiles\\Debug\\CommonLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\DatabaseLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\IniConfigFileDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\NetworkLibraryDebug.dll .\\Debug )
        system( copy ..\\LibExeFiles\\Debug\\ThreadLibraryDebug.dll .\\Debug )
    }
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "DatabaseLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ThreadLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "IniConfigFile", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "NetworkLibrary", "" )
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
