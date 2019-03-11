#-------------------------------------------------
#
# Project created by QtCreator 2014-05-28T11:50:00
#
#-------------------------------------------------
cache()

QT       += core gui network xml serialport websockets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QianKunLE
TEMPLATE = app
QMAKE_INFO_PLIST = Info.plist

INCLUDEPATH += models network views util tools

LIBS += -L$$PWD/uwb_dll/ -llocdll

LIBS += -L$$PWD/uwb_dll/ -lKlmanFilter

SOURCES += main.cpp\
    RTLSDisplayApplication.cpp \
    views/mainwindow.cpp \
    network/RTLSClient.cpp \
    views/GraphicsView.cpp \
    views/GraphicsWidget.cpp \
    views/ViewSettingsWidget.cpp \
        views/MinimapView.cpp \
    views/connectionwidget.cpp \
    models/ViewSettings.cpp \
    tools/OriginTool.cpp \
    tools/RubberBandTool.cpp \
    tools/ScaleTool.cpp \
    util/QPropertyModel.cpp \
    network/SerialConnection.cpp \
    tools/trilateration.cpp \
    uwb_comm/UWB_SQL.cpp \
    uwb_comm/UWB_WebSocket.cpp \
    uwb_comm/cJSON.c \
    uwb_comm/scanthread.cpp \
    uwb_comm/location/location.cpp \
    uwb_comm/tagInfo/tagInfo.cpp \
    uwb_comm/UWB_TcpClient.cpp \
    uwb_comm/uwb_http.cpp \
    views/setserverwidget.cpp \
    views/setScanConfigWidget.cpp \
    uwb_comm/UpdateClient.cpp \
    views/AncManageWidget.cpp \
    views/AncUpSrvConfigWidget.cpp \
    verify/aes.cpp \
    verify/verify.cpp \
    tools/vec1.cpp \
    uwb_comm/UWB_UdpClient.cpp \
    mylog/Mylog.cpp \
    tools/linklist.cpp

HEADERS  += \
    RTLSDisplayApplication.h \
        views/mainwindow.h \
    network/RTLSClient.h \
    views/GraphicsView.h \
    views/GraphicsWidget.h \
    views/ViewSettingsWidget.h \
    views/MinimapView.h \
    views/connectionwidget.h \
    models/ViewSettings.h \
    tools/AbstractTool.h \
    tools/OriginTool.h \
    tools/RubberBandTool.h \
    tools/ScaleTool.h \
    util/QPropertyModel.h \
    network/SerialConnection.h \
    tools/trilateration.h \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/ui_connectionwidget.h \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/ui_GraphicsWidget.h \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/ui_mainwindow.h \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/ui_ViewSettingsWidget.h \
    uwb_comm/cJSON.h \
    uwb_comm/UWB_SQL.h \
    uwb_comm/UWB_WebSocket.h \
    locdll.h \
    uwb_comm/ScanThread.h \
    uwb_comm/location/location.h \
    uwb_comm/tagInfo/tagInfo.h \
    uwb_comm/UWB_TcpClient.h \
    uwb_comm/UWB_HTTP.h \
    views/setserverwidget.h \
    views/setScanConfigWidget.h \
    uwb_comm/UpdateClient.h \
    views/AncManageWidget.h \
    views/AncUpSrvConfigWidget.h \
    verify/aes.h \
    verify/verify.h \
    tools/vec1.h \
    uwb_comm/UWB_UdpClient.h \
    mylog/Mylog.h \
    KlmanFilter.h \
    tools/linklist.h

FORMS    += \
    views/mainwindow.ui \
    views/GraphicsWidget.ui \
    views/ViewSettingsWidget.ui \
    views/connectionwidget.ui \
    views/setserverwidget.ui \
    views/setScanConfigWidget.ui \
    views/AncManageWidget.ui \
    views/AncUpSrvConfigWidget.ui \
    views/AncTcpSrvPortConfigWidget.ui

#CONFIG += console

RC_FILE = images/myapp.rc

DISTFILES += \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/.qmake.cache \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/.qmake.cache \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/.qmake.stash \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/.qmake.stash \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/DecaRangeRTLS.exe \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/libgcc_s_dw2-1.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/libstdc++-6.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/libwinpthread-1.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5Cored.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5Guid.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5Network.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5Networkd.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5SerialPortd.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5Sqld.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5WebSocketsd.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5Widgetsd.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Qt5Xmld.dll \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/release/DecaRangeRTLS.exe \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/TREKanc_config.xml \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/TREKtag_config.xml \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Debug/TREKview_config.xml \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/TREKanc_config.xml \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/TREKtag_config.xml \
    build-TREKdisplay-Desktop_Qt_5_7_0_MinGW_32bit-Release/TREKview_config.xml \
    TREKanc_config.xml \
    uwb_dll/KlmanFilter.dll \
    uwb_dll/Locdll.dll
