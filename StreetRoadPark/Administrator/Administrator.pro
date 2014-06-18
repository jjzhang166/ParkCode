#-------------------------------------------------
#
# Project created by QtCreator 2013-03-28T10:26:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Administrator
TEMPLATE = app

INCLUDEPATH += "./Mysql/include"

LIBS += "./Mysql/lib/liblibmysql.a"

SOURCES += main.cpp\
        mainwindow.cpp \
    Implement/logindialog.cpp \
    Database/mysqldatabase.cpp \
    ItemInfos/iteminfoadmin.cpp \
    ItemInfos/iteminfounit.cpp \
    ItemInfos/iteminfopark.cpp \
    ItemInfos/iteminforeceiver.cpp \
    ItemInfos/iteminfodetector.cpp \
    Implement/addadmindialog.cpp \
    Implement/addunitdialog.cpp \
    Implement/addparkdialog.cpp \
    Implement/iterfacetomysql.cpp \
    Implement/addreceiverdialog.cpp \
    Implement/adddetectordialog.cpp \
    Comm/commfunction.cpp \
    Implement/modadmindialog.cpp \
    Implement/modunitdialog.cpp \
    Implement/modparkdialog.cpp \
    Implement/modreceiverdialog.cpp \
    Implement/moddetectordialog.cpp \
    Implement/changecreaterpassworddialog.cpp \
    ItemInfos/iteminfogroup.cpp \
    ItemInfos/iteminfouser.cpp \
    Implement/addgroupdialog.cpp \
    Implement/adduserdialog.cpp \
    Implement/modgroupdialog.cpp \
    Implement/moduserdialog.cpp \
    Batch/batchadmindialog.cpp \
    Batch/batchunitdialog.cpp \
    Batch/batchparkdialog.cpp \
    Batch/batchreceiverdialog.cpp \
    Batch/batchdetectordialog.cpp \
    Batch/batchgroupdialog.cpp \
    Batch/batchuserdialog.cpp

HEADERS  += mainwindow.h \
    Implement/logindialog.h \
    Database/mysqldatabase.h \
    ItemInfos/iteminfoadmin.h \
    ItemInfos/iteminfounit.h \
    ItemInfos/iteminfopark.h \
    ItemInfos/iteminforeceiver.h \
    ItemInfos/iteminfodetector.h \
    ItemInfos/ItemType.h \
    Implement/addadmindialog.h \
    Implement/addunitdialog.h \
    Implement/addparkdialog.h \
    Implement/iterfacetomysql.h \
    Implement/addreceiverdialog.h \
    Implement/adddetectordialog.h \
    Comm/commfunction.h \
    Implement/modadmindialog.h \
    Implement/modunitdialog.h \
    Implement/modparkdialog.h \
    Implement/modreceiverdialog.h \
    Implement/moddetectordialog.h \
    Implement/changecreaterpassworddialog.h \
    ItemInfos/iteminfogroup.h \
    ItemInfos/iteminfouser.h \
    Implement/addgroupdialog.h \
    Implement/adduserdialog.h \
    Implement/modgroupdialog.h \
    Implement/moduserdialog.h \
    Batch/batchadmindialog.h \
    Batch/batchunitdialog.h \
    Batch/batchparkdialog.h \
    Batch/batchreceiverdialog.h \
    Batch/batchdetectordialog.h \
    Batch/batchgroupdialog.h \
    Batch/batchuserdialog.h

FORMS    += mainwindow.ui \
    Implement/clogindialog.ui \
    Implement/addadmindialog.ui \
    Implement/addunitdialog.ui \
    Implement/addparkdialog.ui \
    Implement/addreceiverdialog.ui \
    Implement/adddetectordialog.ui \
    Implement/modadmindialog.ui \
    Implement/modunitdialog.ui \
    Implement/modparkdialog.ui \
    Implement/modreceiverdialog.ui \
    Implement/moddetectordialog.ui \
    Implement/changecreaterpassworddialog.ui \
    Implement/addgroupdialog.ui \
    Implement/adduserdialog.ui \
    Implement/modgroupdialog.ui \
    Implement/moduserdialog.ui \
    Batch/batchadmindialog.ui \
    Batch/batchunitdialog.ui \
    Batch/batchparkdialog.ui \
    Batch/batchreceiverdialog.ui \
    Batch/batchdetectordialog.ui \
    Batch/batchgroupdialog.ui \
    Batch/batchuserdialog.ui
