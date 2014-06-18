#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T00:20:06
#
#-------------------------------------------------

QT       += sql network xml

DEFINES += _WIN32_WINDOWS=0x0501

MYTARGET = $$quote( DatabaseLibrary%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

INCLUDEPATH += ./Mysql/include
LIBS += ./Mysql/lib/liblibmysql.a

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )

    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "NetworkLibrary", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )

    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "NetworkLibrary", "" )
}

TEMPLATE = lib

DEFINES += DATABASELIBRARY_LIBRARY

SOURCES += databasecontroller.cpp \
    Database/mysqldatabase.cpp \
    cdbconfigurator.cpp \
    qdbthreadevent.cpp \
    qdatadispactherthread.cpp \
    qdatabaseprocessor.cpp \
    qthreadpooltask.cpp \
    qdbdataprocess.cpp \
    qjson2sqlparser.cpp \
    Constant.cpp \
    qdatauploadthread.cpp \
    qdatadownloadthread.cpp \
    qdatauploadevent.cpp

HEADERS += databasecontroller.h\
        DatabaseLibrary_global.h \
    Database/mysqldatabase.h \
    cdbconfigurator.h \
    qdbthreadevent.h \
    qdatadispactherthread.h \
    qdatabaseprocessor.h \
    qthreadpooltask.h \
    qdbdataprocess.h \
    qjson2sqlparser.h \
    qdbcommon.h \
    qjsonstruct.h \
    Constant.h \
    qdatauploadthread.h \
    qdatadownloadthread.h \
    qdatauploadevent.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
