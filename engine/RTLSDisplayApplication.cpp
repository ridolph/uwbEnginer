// -------------------------------------------------------------------------------------------------------------------
//
//  File: RTLSDisplayApplication.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "RTLSDisplayApplication.h"

#include "mainwindow.h"
#include "SerialConnection.h"
#include "RTLSClient.h"
#include "ViewSettings.h"
#include "GraphicsWidget.h"

#include <QMetaProperty>
#include <QDesktopWidget>
#include "views/ViewSettingsWidget.h"
#include "verify/verify.h"
#include <QMessageBox>
/**
* @brief RTLSDisplayApplication
*        Constructor, it initialises the application and its parts
*        the _serialConnection is used for managing the COM port connection
*        the _client consumes the data received over the COM port connection and sends the
* processed data to the graphical display
*        the _mainWindow holds the various GUI parts
*        the _viewSettings is used for configuration of the graphical display
*/



RTLSDisplayApplication::RTLSDisplayApplication(int &argc, char **argv, int remainTime) : QApplication(argc, argv)
{
    QDesktopWidget desktop;
    int desktopHeight=desktop.geometry().height();
    int desktopWidth=desktop.geometry().width();

    _remainTime =  remainTime;
    qDebug()<<"remain:"<<_remainTime;
    _ready = false;

    this->setOrganizationName("Decawave");
    this->setOrganizationDomain("decawave.com");
    this->setApplicationName("TREKDisplay");

    _viewSettings = new ViewSettings(this);

    _serialConnection = new SerialConnection(this);

    _client = new RTLSClient(this);

	_ancMangeWidget = new AncManageWidget;

    _mainWindow = new MainWindow();
    _mainWindow->resize(desktopWidth/2,desktopHeight/2);

    _ready = true;

    _timer = new QTimer;
    _timer->setInterval(60000);//period : 1 minute
    //_timer->setInterval(5000);//period : 5 sec
    _timer->start();
    QObject::connect(_timer,SIGNAL(timeout()), this, SLOT(updateTime()));

    //Connect the various signals and corresponding slots
    QObject::connect(_client, SIGNAL(tagHeartRate(quint64, quint64, quint64,quint64)), graphicsWidget(), SLOT(tagHeartRate(quint64,quint64,quint64,quint64)));
    QObject::connect(_client, SIGNAL(anchPos(quint64,double,double,double,bool,bool)), graphicsWidget(), SLOT(anchPos(quint64,double,double,double,bool, bool)));
    QObject::connect(_client, SIGNAL(tagPos(quint64,double,double,double)), graphicsWidget(), SLOT(tagPos(quint64,double,double,double)));
    QObject::connect(_client, SIGNAL(tagStats(quint64,double,double,double,double)), graphicsWidget(), SLOT(tagStats(quint64,double,double,double,double)));
    QObject::connect(_client, SIGNAL(tagRange(quint64,quint64,double)), graphicsWidget(), SLOT(tagRange(quint64,quint64,double)));
    QObject::connect(_client, SIGNAL(statusBarMessage(QString)), _mainWindow, SLOT(statusBarMessage(QString)));

    QObject::connect(_client, SIGNAL(centerOnAnchors(void)), graphicsWidget(), SLOT(centerOnAnchors(void)));

    QObject::connect(_serialConnection, SIGNAL(clearTags()), graphicsWidget(), SLOT(clearTags()));

    QObject::connect(_serialConnection, SIGNAL(statusBarMessage(QString)), _mainWindow, SLOT(statusBarMessage(QString)));
    QObject::connect(_serialConnection, SIGNAL(connectionStateChanged(SerialConnection::ConnectionState)), _client, SLOT(connectionStateChanged(SerialConnection::ConnectionState)));

    QObject::connect(graphicsWidget(), SIGNAL(updateAnchorXYZ(int, int, double)), _client, SLOT(updateAnchorXYZ(int, int, double)));
    QObject::connect(graphicsWidget(), SIGNAL(updateTagCorrection(int, int, int)), _client, SLOT(updateTagCorrection(int, int, int)));
    QObject::connect(graphicsWidget(), SIGNAL(updateAnchorShow(int,bool)),_client, SLOT(updateAnchorShow(int,bool)));
    QObject::connect(_client, SIGNAL(ancRanges(int, int, int)), graphicsWidget(), SLOT(ancRanges(int, int, int)));
    QObject::connect(_client, SIGNAL(dsptcpLog(QString)), mainWindow()->viewSettingsWidget(), SLOT(dsptcpLog(QString)));
    QObject::connect(serverConfigWidget(),SIGNAL(setServer(QString,int)), _client,SLOT(setServer(QString,int)));
    QObject::connect(serverConfigWidget(),SIGNAL(setOutServer(QString,int)), _client,SLOT(setOutServer(QString,int)));

    QObject::connect(_client, SIGNAL(closeApp()), this, SLOT(closeApp()));


	/*	关联基站配置文件相关数据	*/
	QObject::connect(_client, SIGNAL(anchInfo(int, int, double, double, double)), _ancMangeWidget, SLOT(initAncInfoManage(int, int , double , double , double )));
	
    //emit ready signal so other components can finish initialisation
    emit ready();
}

RTLSDisplayApplication::~RTLSDisplayApplication()
{
    // Delete the objects manually, because we want to control the order
    delete _mainWindow;

    delete _client;

    delete _serialConnection;

	delete _viewSettings;

	delete _ancMangeWidget;
}

RTLSDisplayApplication *RTLSDisplayApplication::instance()
{
    return qobject_cast<RTLSDisplayApplication *>(QCoreApplication::instance());
}

ViewSettings *RTLSDisplayApplication::viewSettings()
{
    return instance()->_viewSettings;
}

RTLSClient *RTLSDisplayApplication::client()
{
    return instance()->_client;
}


SerialConnection *RTLSDisplayApplication::serialConnection()
{
    return instance()->_serialConnection;
}

MainWindow *RTLSDisplayApplication::mainWindow()
{
    return instance()->_mainWindow;
}

GraphicsWidget *RTLSDisplayApplication::graphicsWidget()
{
    return mainWindow()->graphicsWidget();
}

GraphicsView *RTLSDisplayApplication::graphicsView()
{
    return mainWindow()->graphicsWidget()->graphicsView();
}


setServerWidget *RTLSDisplayApplication::serverConfigWidget()
{
   return mainWindow()->serverConfigWidget();
}

void RTLSDisplayApplication::connectReady(QObject *receiver, const char *member, Qt::ConnectionType type)
{
    QMetaMethod method = receiver->metaObject()->method(receiver->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(member)));
    // Either call the method or connect it to the ready signal

    if (instance()->_ready && method.isValid())
        method.invoke(receiver, type);
    else
        QObject::connect(instance(), QMetaMethod::fromSignal(&RTLSDisplayApplication::ready), receiver, method, type);
}


void RTLSDisplayApplication::updateTime()
{
   //_remainTime--;
    printf("_remainTime = %d",_remainTime);
   if(_remainTime <= 0)
   {
      closeApp();
   }
   else
   {
      updateRemainTime(_remainTime);
   }
}

void RTLSDisplayApplication::closeApp()
{
    QMessageBox::critical(NULL, "critical", "Trail period is expired.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    this->exit(0);
}

