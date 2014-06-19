#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T10:25:15
#
#-------------------------------------------------

QT       -= gui

MYTARGET = $$quote( ControllerNet%1 )
MYDESTDIR = $$quote( ../ControllerUI/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCommon", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCommon", "" )
}

TEMPLATE = lib

DEFINES += CONTROLLERNET_LIBRARY

SOURCES += qcontrollernet.cpp

HEADERS += qcontrollernet.h\
        ControllerNet_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE172F81B
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ControllerNet.dll
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
