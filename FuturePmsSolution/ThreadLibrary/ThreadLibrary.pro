QT       += core gui network

DEFINES += _WIN32_WINDOWS=0x0490

MYTARGET = $$quote( ThreadLibrary%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )
MYDESTLIB = $$quote( %1/lib%2%3.a )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyNetwork", "Debug" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyDatabase", "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "CommonLibrary", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "ManipulateFile", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyNetwork", "" )
    LIBS += $$sprintf( $$MYDESTLIB, $$DESTDIR, "MyDatabase", "" )
}

TEMPLATE = lib

DEFINES += THREADLIBRARY_LIBRARY

SOURCES += qthreadgenerator.cpp \
    qloggerthread.cpp \
    qlistenerthread.cpp \
    qtcppeersocketthread.cpp \
    qudpreceiversocketthread.cpp \
    qtcpclientsocketthread.cpp \
    qdatabasethread.cpp \
    qmybasethread.cpp \
    Event/qloggerevent.cpp \
    Event/qmythreadevent.cpp \
    Event/qlistenerthreadevent.cpp \
    Event/qtcppeerthreadevent.cpp \
    Event/qtcpclientthreadevent.cpp \
    Event/qdatabasethreadevent.cpp \
    qthreadpooltask.cpp \
    Event/qudpreceiverthreadevent.cpp \
    Event/qudpsenderthreadevent.cpp \
    qudpsenderthread.cpp \
    qudpfeedbackthread.cpp \
    qfreetcppeersocketthread.cpp \
    Event/qfreetcppeersocketthreadevent.cpp \
    qfreedatabaseobjectthread.cpp \
    Event/qfreedatabaseobjectthreadevent.cpp

HEADERS += ThreadLibrary_global.h \
    qthreadgenerator.h \
    qloggerthread.h \
    qlistenerthread.h \
    qtcppeersocketthread.h \
    qudpreceiversocketthread.h \
    qtcpclientsocketthread.h \
    qdatabasethread.h \
    qmybasethread.h \
    Event/qloggerevent.h \
    ThreadModule.h \
    Event/qmythreadevent.h \
    Event/qlistenerthreadevent.h \
    Event/qtcppeerthreadevent.h \
    Event/qtcpclientthreadevent.h \
    Event/qdatabasethreadevent.h \
    qthreadpooltask.h \
    Event/qudpreceiverthreadevent.h \
    Event/qudpsenderthreadevent.h \
    qudpsenderthread.h \
    qudpfeedbackthread.h \
    qfreetcppeersocketthread.h \
    Event/qfreetcppeersocketthreadevent.h \
    qfreedatabaseobjectthread.h \
    Event/qfreedatabaseobjectthreadevent.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0F78417
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ThreadLibrary.dll
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
