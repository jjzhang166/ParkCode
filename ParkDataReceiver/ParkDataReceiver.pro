#-------------------------------------------------
#
# Project created by QtCreator 2011-10-26T09:28:02
#
#-------------------------------------------------

QT       += core gui sql network phonon
# QT_NO_DEBUG QT_NO_DEBUG_OUTPUT
TARGET = ParkDataReceiver
TEMPLATE = app
DEFINES += PARKDATARECEIVER_APP _WIN32_WINNT=0x0501

INCLUDEPATH += "../Mysql/include"

LIBS += "../lib/libws2_32.a"
LIBS += "../lib/libpsapi.a"
LIBS += "../lib/libiphlpapi.a"
LIBS += "../lib/libmysqlclient.a"
LIBS += "../lib/libmysql.a"

SOURCES += main.cpp\
        mainwindow.cpp \
    ../Database/mssqlserver.cpp \
    ../Network/udpdispatcher.cpp \
    ../Network/tcpdispatcher.cpp \
    ../Network/tcpclient.cpp \
    ../Network/svrthread.cpp \
    ../Network/NetProcessData.cpp \
    ../Network/mytcpserver.cpp \
    ../Network/http.cpp \
    ../Common/ommonfunction.cpp \
    ../Database/bulkinsert.cpp \
    ../Network/udpclient.cpp \
    ../Network/manipulatemessage.cpp \
    ../Network/netcommfunction.cpp \
    ../Network/parkintranet.cpp \
    ../Network/netclient.cpp \
    ../Network/httpevent.cpp \
    ../Network/httpserver.cpp \
    ../Network/peersocket.cpp \
    ../Heartbeat/heartbeatthread.cpp \
    ../Heartbeat/hbevent.cpp \
    ../Network/localsvrcommunication.cpp \
    ../Network/localcltcommunication.cpp \
    ../Network/ftp.cpp \
    ../Common/logicinterface.cpp \
    ../Database/mysqldatabase.cpp \
    ../Network/ftpevent.cpp \
    ../Network/ping.cpp \
    ../Network/dataparserthread.cpp \
    ../Network/parserevent.cpp \
    ../Database/dbheartbeat.cpp \
    ../Database/dbheartbeatevent.cpp

HEADERS  += mainwindow.h \
    ../Database/mssqlserver.h \
    ../Network/udpdispatcher.h \
    ../Network/tcpdispatcher.h \
    ../Network/tcpclient.h \
    ../Network/svrthread.h \
    ../Network/NetProcessData.h \
    ../Network/mytcpserver.h \
    ../Network/http.h \
    ../Network/CommonData.h \
    ../Common/commonfunction.h \
    ../Database/bulkinsert.h \
    ../Network/udpclient.h \
    ../Network/manipulatemessage.h \
    ../Network/netcommfunction.h \
    ../Network/parkintranet.h \
    ../Network/netclient.h \
    ../Network/httpserver.h \
    ../Network/httpevent.h \
    ../Network/peersocket.h \
    ../Heartbeat/heartbeatthread.h \
    ../Heartbeat/hbevent.h \
    ../Network/localcltcommunication.h \
    ../Network/localsvrcommunication.h \
    ../Network/ftp.h \
    ../Common/logicinterface.h \
    ../Database/mysqldatabase.h \
    ../Network/ftpevent.h \
    ../Network/ping.h \
    ../Network/dataparserthread.h \
    ../Network/parserevent.h \
    ../Database/dbheartbeat.h \
    ../Database/dbheartbeatevent.h

FORMS    += mainwindow.ui
