#-------------------------------------------------
#
# Project created by QtCreator 2012-06-13T16:31:24
#
#-------------------------------------------------

QT       += sql network

QT       -= gui

MYTARGET = $$quote( MyDatabase%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
}

TEMPLATE = lib

DEFINES += MYDATABASE_LIBRARY

SOURCES += qmydatabase.cpp \
    qsqlserver.cpp \
    qdatabasegenerator.cpp \
    qmysql.cpp

HEADERS += qmydatabase.h\
        MyDatabase_global.h \
    qsqlserver.h \
    qdatabasegenerator.h \
    qmysql.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4CF5EE1
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = MyDatabase.dll
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
