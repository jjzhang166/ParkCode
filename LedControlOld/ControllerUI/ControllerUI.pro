#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T09:49:55
#
#-------------------------------------------------

QT       += core gui

MYDESTDIR = $$quote( %1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "Controller", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCommon", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCmd", "Debug" )
}

Release {
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "Controller", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCommon", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ControllerCmd", "" )
}

TARGET = ControllerUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qdlgconfig.cpp \

HEADERS  += mainwindow.h \
    qdlgconfig.h \

FORMS    += mainwindow.ui \
    qdlgconfig.ui

RESOURCES += \
    Image.qrc
