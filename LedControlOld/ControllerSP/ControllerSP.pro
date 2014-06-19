#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T10:23:55
#
#-------------------------------------------------

#QT       -= gui

MYTARGET = $$quote( ControllerSP%1 )
MYDESTDIR = $$quote( ../ControllerUI/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCommon", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCmd", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCommon", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCmd", "" )
}

TEMPLATE = lib

DEFINES += CONTROLLERSP_LIBRARY

SOURCES += qcontrollersp.cpp \
    qextserialport/win_qextserialport.cpp \
    qextserialport/qextserialbase.cpp \
    qextserialport/qextserialport.cpp \
    qthreadsp.cpp \
    qthreadspwriter.cpp \
    qthreadspparser.cpp

HEADERS += qcontrollersp.h\
        ControllerSP_global.h \
    qextserialport/qextserialbase.h \
    qextserialport/win_qextserialport.h \
    qextserialport/qextserialport.h \
    qthreadsp.h \
    qthreadspwriter.h \
    qthreadspparser.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE69BCEC0
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ControllerSP.dll
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
