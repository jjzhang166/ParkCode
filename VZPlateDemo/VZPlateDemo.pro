#-------------------------------------------------
#
# Project created by QtCreator 2012-12-17T15:54:13
#
#-------------------------------------------------

QT       += core gui phonon

INCLUDEPATH += ../VehicleLicense/WinTone
INCLUDEPATH += ../Multimedia/HikSDK
INCLUDEPATH += ../Multimedia/TmSDK
INCLUDEPATH += ../HKIPC/inc
INCLUDEPATH += ../JWSIPC/inc
INCLUDEPATH += ../JbIPC

LIBS += ../lib/libLPKernelEx.a
LIBS += ../lib/libDs40xxSDK.a
LIBS += ../HKIPC/lib/libHCNetSDK.a
LIBS += ../JWSIPC/lib/libtmControlClient.a
LIBS += ../lib/libgdi32.a
LIBS += ../lib/libole32.a
LIBS += ../lib/libUsbCameraDll.a

DEFINES += _WIN32_WINNT=0x0500

TARGET = VZPlateDemo
TEMPLATE = app


SOURCES += main.cpp\
        VZMainWindow.cpp \
    Thread/qplatethread.cpp \
    Thread/qplateevent.cpp \
    Thread/qanalogcamerathread.cpp \
    Thread/qdigitalcamerathread.cpp \
    Thread/qcameraevent.cpp \
    Thread/qfilecamerathread.cpp \
    Thread/qdirectorythread.cpp \
    qcommon.cpp \
    Thread/qdirectoryevent.cpp \
    Thread/qhkcapturecardthread.cpp \
    Thread/qtmcapturecardthread.cpp \
    Thread/qdhkipcthread.cpp \
    Thread/qjvsipcthread.cpp \
    Thread/qonvifthread.cpp \
    blacklistmainwindow.cpp \
    cconfigurator.cpp \
    cdlgblacklist.cpp \
    cdlgconfig.cpp \
    qtransparentframe.cpp \
    Thread/quv200thread.cpp \
    Thread/cusbcamerathread.cpp \
    qdlgdevice.cpp \
    Thread/quv200timerthread.cpp \
    Thread/qjbipc.cpp

HEADERS  += VZMainWindow.h \
    Thread/qplatethread.h \
    Thread/qplateevent.h \
    Thread/qanalogcamerathread.h \
    Thread/qdigitalcamerathread.h \
    Thread/qcameraevent.h \
    Thread/qfilecamerathread.h \
    Thread/qdirectorythread.h \
    qcommon.h \
    Thread/qdirectoryevent.h \
    Thread/qhkcapturecardthread.h \
    Thread/qtmcapturecardthread.h \
    Thread/qdhkipcthread.h \
    Thread/qjvsipcthread.h \
    Thread/qonvifthread.h \
    blacklistmainwindow.h \
    cconfigurator.h \
    cdlgblacklist.h \
    cdlgconfig.h \
    qtransparentframe.h \
    Thread/quv200thread.h \
    Thread/cusbcamerathread.h \
    qdlgdevice.h \
    Thread/quv200timerthread.h \
    Thread/qjbipc.h

FORMS    += vzmainwindow.ui \
    blacklistmainwindow.ui \
    cdlgblacklist.ui \
    cdlgconfig.ui \
    qtransparentframe.ui \
    qdlgdevice.ui

RESOURCES +=
