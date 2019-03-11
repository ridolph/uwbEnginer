// -------------------------------------------------------------------------------------------------------------------
//
//  File: MainWindow.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "connectionwidget.h"
#include "serialconnection.h"
#include "RTLSDisplayApplication.h"
#include "ViewSettings.h"
#include "set"

#include <QShortcut>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QDomDocument>
#include <QFile>
#include "setserverwidget.h"
#include "uwb_comm/UWB_TcpClient.h"


int g_udp_port;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _setServerW = new setServerWidget;
    _setScanConfigW = new setScanConfigWidget;
    _tagManageW = new AncManageWidget;

    _showMainToolBar = false;
    _notConnected = true;

    QFont ft;
    ft.setPointSize(22);
    ui->statusBar->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->statusBar->setPalette(pa);

    {
        QWidget *empty = new QWidget(this);
        empty->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        ui->mainToolBar->addWidget(empty);
    }

    _anchorConfigAction = new QAction(tr("&Connection Configuration"), this);
    //ui->menuBar->addAction(anchorConfigAction);
    //connect(anchorConfigAction, SIGNAL(triggered()), SLOT(onAnchorConfigAction()));

    createPopupMenu(ui->viewMenu);

    //add connection widget to the main window
    _cWidget = new ConnectionWidget(this);
    ui->mainToolBar->addWidget(_cWidget);

    QObject::connect(RTLSDisplayApplication::instance(), SIGNAL(aboutToQuit()), SLOT(saveSettings()));

    //ui->helpMenu->addAction(ui->actionAbout);
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(onAboutAction()));
    connect(ui->actionConfigServer, SIGNAL(triggered(bool)),this, SLOT(onConfigServerAction()));
    connect(ui->actionScanConfig, SIGNAL(triggered(bool)),this, SLOT(onScanConfigAction()));
    connect(ui->actionTagManage, SIGNAL(triggered(bool)), this, SLOT(onTagManageAction()));

    _infoLabel = new QLabel(parent);

    ui->viewSettings_dw->close();
    ui->minimap_dw->close();

    connect(ui->minimap_dw->toggleViewAction(), SIGNAL(triggered()), SLOT(onMiniMapView()));

    QObject::connect(RTLSDisplayApplication::serialConnection(), SIGNAL(connectionStateChanged(SerialConnection::ConnectionState)),
                     this, SLOT(connectionStateChanged(SerialConnection::ConnectionState)));

    RTLSDisplayApplication::connectReady(this, "onReady()");

    _tcpServer = new QTcpServer();
    connect(_tcpServer, &QTcpServer::newConnection, this, &MainWindow::tcpNewConnection);

    //qDebug() << "tcp Listen Port 5000";
    _tcpServer->listen(QHostAddress::Any, 5000);

    _udpSocket = new QUdpSocket(this);
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("udpport");
    g_udp_port = configfile->value("port").toInt();
    configfile->endGroup();
    delete configfile;

    _udpSocket->bind(g_udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    RTLSDisplayApplication::client()->_udpSocket = _udpSocket;
    _tagManageW->_udpSocket = _udpSocket;
    //qDebug() << "udp Listen Port 5006";
    QObject::connect(_udpSocket, &QUdpSocket::readyRead, RTLSDisplayApplication::client(), &RTLSClient::newUdpData);
    QObject::connect(RTLSDisplayApplication::client(), &RTLSClient::updateAncAddr, _tagManageW, &AncManageWidget::updateAncAddr);

}



void MainWindow::onReady()
{

    QObject::connect(graphicsWidget(), SIGNAL(setTagHistory(int)), viewSettingsWidget(), SLOT(setTagHistory(int)));
    QObject::connect(viewSettingsWidget(), SIGNAL(udpPortChanged(void)), this, SLOT(udpPortChanged(void)));
    QObject::connect(viewSettingsWidget(), SIGNAL(saveViewSettings(void)), this, SLOT(saveViewConfigSettings(void)));
    QObject::connect(RTLSDisplayApplication::client()->uwbTcpClient(), &UWB_TcpClient::startUpdate, _tagManageW, &AncManageWidget::startUpdate);
    QObject::connect( _tagManageW, &AncManageWidget::sendUpResp, RTLSDisplayApplication::client()->uwbTcpClient(), &UWB_TcpClient::sendUpResp);
    QObject::connect(RTLSDisplayApplication::client(), &RTLSClient::sendUpCmdRsut, _tagManageW, &AncManageWidget::sendUpCmdRsut);
    QObject::connect(RTLSDisplayApplication::client(), &RTLSClient::sendRecoverCmdRsut, _tagManageW, &AncManageWidget::sendRecoverCmdRsut);
    QObject::connect(RTLSDisplayApplication::client(), &RTLSClient::sendGetVerRsut, _tagManageW, &AncManageWidget::sendGetVerRsut);


    loadSettings();

    if(_showMainToolBar)
    {
        ui->mainToolBar->show();
    }
    else
    {
        ui->mainToolBar->hide();
    }

    ui->viewSettings_dw->show();

#ifdef QT_DEBUG
    ui->mainToolBar->show();
#else
    /*while(_notConnected)
    {
        if(_notConnected)
        {
            //QMessageBox::critical(NULL, tr("COM Error"), QString("Cannot open/connect to COM port.\nPlease make sure TREK device is connected to PC."));

            QMessageBox::StandardButton reply;

            //RTLSDisplayApplication::beep();

            reply = QMessageBox::warning(this, tr("COM Error"), "Cannot open/connect to COM port.\n"
                                          "Please make sure TREK device is connected to PC.\n\n "
                                          "Press Close to exit or Retry to retry.",
                                          QMessageBox::Close|QMessageBox::Retry);

            if(reply == QMessageBox::Close)
            {

                //exit application
                //RTLSDisplayApplication::closeAllWindows();
                //exit(-1);
                _notConnected = false;
                break;
            }

            //else it will re-try...

        }

        if(_cWidget->updateDeviceList() > 0)
        {
            _notConnected = false;
            break;
        }
    }*/
#endif
}

void MainWindow::tcpNewConnection()
{
    _tcpSocket = _tcpServer->nextPendingConnection();
    qDebug() << "A new TCP connection connected";

	//_tcpSocket->write("11111111111111");
	printf(" _tcpSocket = _tcpServer->nextPendingConnection()\n");
    //连接QTcpSocket的信号槽，以读取新数据
    //QObject::connect(_tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);

    RTLSDisplayApplication::client()->is_socket_connected = true;
    RTLSDisplayApplication::client()->_tcpSocket = _tcpSocket;
    QObject::connect(_tcpSocket, &QTcpSocket::readyRead, RTLSDisplayApplication::client(), &RTLSClient::newTcpOrSerialData);
    QObject::connect(_tcpSocket, &QTcpSocket::disconnected, this, &MainWindow::socket_Disconnected);
}

void MainWindow::socket_Read_Data()
{
    qDebug() << "Socket read data";

    QByteArray buffer;
    //读取缓冲区数据
    buffer = _tcpSocket->readAll();
    if(!buffer.isEmpty())
    {
        qDebug() << tr(buffer);
    }
}

void MainWindow::socket_Disconnected()
{
    qDebug() << "Socket disconnected";
}

MainWindow::~MainWindow()
{
    _tcpServer->close();
    _tcpServer->deleteLater();
    delete ui;
}

GraphicsWidget *MainWindow::graphicsWidget()
{
    return ui->graphicsWidget;
}

ViewSettingsWidget *MainWindow::viewSettingsWidget()
{
    return ui->viewSettings_w;
}


setServerWidget *MainWindow::serverConfigWidget()
{
    return _setServerW;
}

QMenu *MainWindow::createPopupMenu()
{
    return createPopupMenu(new QMenu());
}

QMenu *MainWindow::createPopupMenu(QMenu *menu)
{
    menu->addAction(ui->viewSettings_dw->toggleViewAction());
    menu->addAction(ui->minimap_dw->toggleViewAction());

    return menu;
}

void MainWindow::onAnchorConfigAction()
{
    ui->mainToolBar->show();
}

void MainWindow::onMiniMapView()
{
    //check if we have loaded floorplan before we open mini map
    //if no floor plan close minimap
    QString path = RTLSDisplayApplication::viewSettings()->getFloorplanPath();

    if(path == "") //no floorplan loaded
    {
        ui->minimap_dw->close();
        //qDebug() << "close minimap" ;
        QMessageBox::warning(NULL, tr("Error"), "No floorplan loaded. Please upload floorplan to use mini-map.");
    }
}

void MainWindow::connectionStateChanged(SerialConnection::ConnectionState state)
{
 /*   switch(state)
    {
        case SerialConnection::Connecting:
        {
            statusBar()->showMessage(QString("Connecting to Tag/Anchor..."));
            _showMainToolBar = false;
            _notConnected = false;
            break;
        }
        case SerialConnection::Connected:
        {
            statusBar()->showMessage("Connection successful.");
            loadSettings();
            _showMainToolBar = false;
            _notConnected = false;
            break;
        }
        case SerialConnection::ConnectionFailed:
        {
            statusBar()->showMessage("Connection failed.");
            loadSettings();
            _showMainToolBar = true;
            _notConnected = true;
            break;
        }
        case SerialConnection::Disconnected:
        {
            statusBar()->showMessage("Connection disconnected.");
            _showMainToolBar = true;
            _notConnected = true;
            break;
        }
    }

    if(state != SerialConnection::Connecting)
    {
        RTLSDisplayApplication::client()->setGWReady(true);
    }
*/
#ifdef QT_DEBUG
    ui->mainToolBar->show();
#endif
}


void MainWindow::loadSettings()
{
    QSettings s;
    s.beginGroup("MainWindow");
    QVariant state = s.value("window-state");
    if (state.convert(QVariant::ByteArray))
    {
        this->restoreState(state.toByteArray());
    }

    QVariant geometry = s.value("window-geometry");
    if (geometry.convert(QVariant::ByteArray))
    {
        this->restoreGeometry(geometry.toByteArray());
    }
    else
    {
        this->showMaximized();
    }
    s.endGroup();

    //load view settings
    loadConfigFile("./TREKview_config.xml");
    graphicsWidget()->loadConfigFile("./TREKtag_config.xml");
    RTLSDisplayApplication::instance()->client()->loadConfigFile("./TREKanc_config.xml");
}

void MainWindow::saveViewConfigSettings(void)
{
    saveConfigFile("./TREKview_config.xml", "view_cfg");
}

void MainWindow::udpPortChanged()
{
    _udpSocket->disconnectFromHost();
    _udpSocket->bind(g_udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
}

void MainWindow::saveSettings()
{
    QSettings s;
    s.beginGroup("MainWindow");
    s.setValue("window-state",    this->saveState());
    s.setValue("window-geometry", this->saveGeometry());
    s.endGroup();

    //save view settings
    saveConfigFile("./TREKview_config.xml", "view_cfg");
    graphicsWidget()->saveConfigFile("./TREKtag_config.xml");
    RTLSDisplayApplication::instance()->client()->saveConfigFile("./TREKanc_config.xml");
}

void MainWindow::setServer(QString addr , int port)
{
    qDebug()<<"slot set server"<<addr<<port;
}

void MainWindow::onTagManageAction()
{
    _tagManageW->show();
}

void MainWindow::onConfigServerAction()
{
    _setServerW->readSetting();
    _setServerW->show();
}

void MainWindow::onScanConfigAction()
{
    _setScanConfigW->readSetting();
    _setScanConfigW->show();
}

void MainWindow::onAboutAction()
{
    _infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About"),
            tr("<b>QianKunLE</b>"
               "<br>version 1.0 (" __DATE__
               ") <br>Copyright (C) 2018, qiankuniot Ltd.\n"
               "<br>www.qiankuniot.com"));
}

void MainWindow::loadConfigFile(QString filename)
{
    QFile file(filename);

    if (!file.open(QFile::ReadWrite | QFile::Text))
    {
        qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg(filename).arg(file.errorString())));
        return;
    }

    QDomDocument doc;

    doc.setContent(&file, false);

    QDomElement root = doc.documentElement();

    qDebug() << root.tagName() ;


    if( root.tagName() == "config" )
    {
        //there are acnhors saved in the config file
        //populate the _model anchor list

        QDomNode n = root.firstChild();
        while( !n.isNull() )
        {
            QDomElement e = n.toElement();
            if( !e.isNull() )
            {
                if( e.tagName() == "view_cfg" )
                {

                    RTLSDisplayApplication::viewSettings()->setGridWidth((e.attribute( "gridW", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setGridHeight((e.attribute( "gridH", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setShowGrid(((e.attribute( "gridS", "" )).toInt() == 1) ? true : false);
                    RTLSDisplayApplication::viewSettings()->setShowOrigin(((e.attribute( "originS", "" )).toInt() == 1) ? true : false);
                    RTLSDisplayApplication::viewSettings()->setFloorplanPath(e.attribute( "fplan", "" ));
                    RTLSDisplayApplication::viewSettings()->setFloorplanXOffset((e.attribute( "offsetX", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setFloorplanYOffset((e.attribute( "offsetY", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setFloorplanXScale((e.attribute( "scaleX", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->setFloorplanYScale((e.attribute( "scaleY", "" )).toDouble());
                    RTLSDisplayApplication::viewSettings()->floorplanFlipX((e.attribute( "flipX", "" )).toInt());
                    RTLSDisplayApplication::viewSettings()->floorplanFlipY((e.attribute( "flipY", "" )).toInt());

                    RTLSDisplayApplication::viewSettings()->setFloorplanPathN();
                    RTLSDisplayApplication::viewSettings()->setSaveFP(((e.attribute( "saveFP", "" )).toInt() == 1) ? true : false);

                }
            }

            n = n.nextSibling();
        }

    }

    file.close(); //close the file
}

void MainWindow::saveConfigFile(QString filename, QString cfg)
{
    QFile file(filename);

    /*if (!file.open(QFile::ReadWrite | QFile::Text))
    {
        qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg(filename).arg(file.errorString())));
        return;
    }*/

    QDomDocument doc;
    //doc.setContent(&file, false);

    //save the graphical information
    QDomElement info = doc.createElement("config");
    doc.appendChild(info);

    qDebug() << info.tagName() ;

    if(cfg == "view_cfg")
    {
        QDomElement cn = doc.createElement( "view_cfg" );

        cn.setAttribute("gridW",  QString::number(RTLSDisplayApplication::viewSettings()->gridWidth(), 'g', 3));
        cn.setAttribute("gridH",  QString::number(RTLSDisplayApplication::viewSettings()->gridHeight(), 'g', 3));
        cn.setAttribute("gridS",  QString::number((RTLSDisplayApplication::viewSettings()->gridShow() == true) ? 1 : 0));
        cn.setAttribute("originS",  QString::number((RTLSDisplayApplication::viewSettings()->originShow() == true) ? 1 : 0));
        cn.setAttribute("saveFP",  QString::number((RTLSDisplayApplication::viewSettings()->floorplanSave() == true) ? 1 : 0));

        if(RTLSDisplayApplication::viewSettings()->floorplanSave()) //we want to save the floor plan...
        {
            cn.setAttribute("flipX",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanFlipX(), 10));
            cn.setAttribute("flipY",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanFlipY(), 10));
            cn.setAttribute("scaleX",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanXScale(),'g', 3));
            cn.setAttribute("scaleY",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanYScale(), 'g', 3));
            cn.setAttribute("offsetX",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanXOffset(), 'g', 3));
            cn.setAttribute("offsetY",  QString::number(RTLSDisplayApplication::viewSettings()->floorplanYOffset(), 'g', 3));
            cn.setAttribute("fplan", RTLSDisplayApplication::viewSettings()->getFloorplanPath());
        }
        else
        {

        }
        info.appendChild( cn );

    }

    //file.close(); //close the file and overwrite with new info

    file.open(QIODevice::WriteOnly | QIODevice::Text);


    QTextStream ts( &file );
    ts << doc.toString();

    qDebug() << doc.toString();

    file.close();
}


void MainWindow::statusBarMessage(QString status)
{
    ui->statusBar->showMessage(status);
}
