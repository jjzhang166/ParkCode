#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T11:02:31
#
#-------------------------------------------------

#QT       -= gui

MYTARGET = $$quote( ControllerCommon%1 )
MYDESTDIR = $$quote( ../ControllerUI/%1 )

#message( $$MYDESTDIR )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
}

TEMPLATE = lib

DEFINES += CONTROLLERCOMMON_LIBRARY

SOURCES += qcontrollercommon.cpp \
    qctrlevent.cpp

HEADERS += qcontrollercommon.h\
        ControllerCommon_global.h \
    CommonHead.h \
    qctrlevent.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0187F7C
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ControllerCommon.dll
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
