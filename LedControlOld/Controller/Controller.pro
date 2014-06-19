#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T10:05:46
#
#-------------------------------------------------

#QT       -= gui

MYTARGET = $$quote( Controller%1 )
MYDESTDIR = $$quote( ../ControllerUI/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCommon", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerSP", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCommon", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerSP", "" )
}

TEMPLATE = lib

DEFINES += CONTROLLER_LIBRARY

SOURCES += qcontroller.cpp

HEADERS += qcontroller.h\
        Controller_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4D1B20B
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Controller.dll
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
