#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T10:48:05
#
#-------------------------------------------------

QT       -= gui

MYTARGET = $$quote( ControllerCmd%1 )
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

DEFINES += CONTROLLERCMD_LIBRARY

SOURCES += qcontrollercmd.cpp \
    qcmdparser.cpp \
    qcmdgenerator.cpp

HEADERS += qcontrollercmd.h\
        ControllerCmd_global.h \
    qcmdparser.h \
    qcmdgenerator.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE1EA7F16
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ControllerCmd.dll
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
