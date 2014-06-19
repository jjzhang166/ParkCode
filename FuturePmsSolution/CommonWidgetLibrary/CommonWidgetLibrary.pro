#-------------------------------------------------
#
# Project created by QtCreator 2012-06-15T11:03:39
#
#-------------------------------------------------

QT       += gui

MYTARGET = $$quote( CommonWidgetLibrary%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "" )
}

TEMPLATE = lib

DEFINES += COMMONWIDGETLIBRARY_LIBRARY

SOURCES += commonwidgetlibrary.cpp \
    Dialog/qdlglogbrowser.cpp \
    MyWidget/qmysplitter.cpp

HEADERS += commonwidgetlibrary.h\
        CommonWidgetLibrary_global.h \
    Dialog/qdlglogbrowser.h \
    MyWidget/qmysplitter.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE3C07814
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = CommonWidgetLibrary.dll
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

FORMS += \
    Dialog/qdlglogbrowser.ui
