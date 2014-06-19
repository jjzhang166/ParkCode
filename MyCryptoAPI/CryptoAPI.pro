#-------------------------------------------------
#
# Project created by QtCreator 2012-02-23T22:19:41
#
#-------------------------------------------------

QT       -= gui

TARGET = CryptoAPI
TEMPLATE = lib

DEFINES += CRYPTOAPI_LIBRARY

SOURCES += cryptoapi.cpp

HEADERS += cryptoapi.h\
        CryptoAPI_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE43E47E6
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = CryptoAPI.dll
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
