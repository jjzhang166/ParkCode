##              operator
## name = value and name += value name -= value
## This operator only adds a value to the list of values in a variable if it doesn't already exist. It is used like this:
## DEFINES *= QT_DLL
## QT_DLL will only be added to the list of pre-processor defines if it is not already defined.
## The '~=' operator
## This operator replaces any values that match the regexp with the specified value. It is used like this:
## DEFINES ~= s/QT_[DT].+/QT
## This removes any values in the list that start with QT_D or QT_T with QT.

## Scopes. A scope are similar to 'if' statements, if a certain condition is true, the settings inside the scope are processed. A scope is written like this:
## win32 { // Block
##	DEFINES += QT_DLL
## }
## win32:DEFINES += QT_DLL // line
## !win32 { // except win32
##	DEFINES += QT_DLL
## }
##Any entry on the CONFIG line is also a scope. For example, if you write this:
##    CONFIG += warn_on
## warn_on {
## Self Define scope
## }
##win32 {
##	thread {
##	    DEFINES += QT_THREAD_SUPPORT
##	}
## }
## win32:thread { // To save writing many nested scopes
##	DEFINES += QT_THREAD_SUPPORT
## }
## win32:thread { //Once a test has been performed you may also do else/elseif operations.
##  DEFINES += QT_THREAD_SUPPORT
## } else:debug {
##  DEFINES += QT_NOTHREAD_DEBUG
## } else {
##  warning("Unknown configuration")
## }
## Myown variable MY_VARIABLE = value
## MY_DEFINES = $$DEFINES MY_DEFINES = $${DEFINES}

QT       += core gui network## system variables
DEFINES += _WIN32_WINNT=0x0501

MYTARGET = $$quote( CommonLibrary%1 )
MYDESTDIR = $$quote( ../LibExeFiles/%1 )

#message( $$MYDESTDIR )

Debug {
    TARGET = $$sprintf( $$MYTARGET, "Debug" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Debug" )
}

Release {
    TARGET = $$sprintf( $$MYTARGET, "" )
    DESTDIR = $$sprintf( $$MYDESTDIR, "Release" )
}

##OBJECTS_DIR
##MOC_DIR
##INCLUDEPATH
##DLLDESTDIR
TEMPLATE = lib

DEFINES += QCOMMONFUNCTION_LIBRARY

SOURCES += qcommonfunction.cpp \
    qmyapplication.cpp \
    qmanipulatemessage.cpp \
    qnetdataprocess.cpp

HEADERS += qcommonfunction.h\
        QCommonFunction_global.h \
    CommonMacro.h \
    qmyapplication.h \
    CommonEnum.h \
    CommonDataStruct.h \
    qmanipulatemessage.h \
    qnetdataprocess.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0F78417
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = CommonLibrary.dll
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
