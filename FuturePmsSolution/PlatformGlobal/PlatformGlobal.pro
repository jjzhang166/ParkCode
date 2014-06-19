#-------------------------------------------------
#
# Project created by QtCreator 2012-06-26T10:16:03
#
#-------------------------------------------------

QT       += network

DEFINES += PLATFORMGLOBAL_LIBRARY

MYTARGET = $$quote( PlatformGlobal%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyNetwork", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyDatabase", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonWidgetLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ThreadLibrary", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyNetwork", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyDatabase", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonWidgetLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ThreadLibrary", "" )
}

TEMPLATE = lib

SOURCES += qplatformglobal.cpp

HEADERS += qplatformglobal.h\
        PlatformGlobal_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE6E916BC
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PlatformGlobal.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
