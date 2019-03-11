#include "UpdateClient.h"
#include <QDebug>
#include <uwb_comm/cJSON.h>
#include <QDataStream>
#include <QSettings>

UpdateClient::UpdateClient(int aid, QString tcpServer)
{
    _aid = aid;
    if(!tcpServer.isEmpty())
    {
        _tcpServerAddr = tcpServer.section(":",0,0);
        _tcpServerPort = tcpServer.section(":",1,1).toInt();
    }

    _connectTimeLimit = 5;
    _connectCount = 0;
    _startGetVerFlag = 0;
    _startRecoverFlag = 0;
    _startUpdateFlag = 0;

    qDebug()<<"create update client,aid:"<<aid<<_tcpServerAddr<<_tcpServerPort;

    _tcpClient = new QTcpSocket(this);
    _connTimer = new QTimer;
    _rspTimer = new QTimer;
    _connectFlag = false;


    connect(_tcpClient,SIGNAL(connected()),this,SLOT(connectOk()));
    connect(_tcpClient,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(_tcpClient,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(_tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(printError(QAbstractSocket::SocketError)));
    connect(_connTimer,SIGNAL(timeout()),this, SLOT(connTimeout()));
    connect(_rspTimer, SIGNAL(timeout()), this, SLOT(rspTimeout()));

    _connTimer->setInterval(1000);
    _rspTimer->setInterval(10000);
}

UpdateClient::~UpdateClient()
{

}

void UpdateClient::setServer(QString tcpServer)
{
    _tcpServerAddr = tcpServer.section(":",0,0);
    _tcpServerPort = tcpServer.section(":",1,1).toInt();
    qDebug()<<"tcpserver set addr:"<<_tcpServerAddr<< "port"<<_tcpServerPort;
}

void UpdateClient::startConn()
{
    readSetting();
    _tcpClient->connectToHost(_tcpServerAddr, _tcpServerPort);
    _connTimer->start();
    _connectCount = 0;

}

void UpdateClient::connectOk()
{
    _connectFlag = true;
    _connTimer->stop();
    _connectCount = 0;
    qDebug()<<"updateClient connect ok";

    if(_startUpdateFlag)
    {
        sendUpdateCmd();
    }

    if(_startRecoverFlag)
    {
        sendRecoverCmd();
    }

    if(_startGetVerFlag)
    {
        sendGetVerCmd();
    }
}

//重连机制
void UpdateClient::connTimeout()
{
    if(_connectCount >= _connectTimeLimit)
    {
        emit sendUpCmdRsut(_aid, false);
        _connTimer->stop();
        _connectCount = 0;
        _startGetVerFlag = 0;
        _startRecoverFlag = 0;
        _startUpdateFlag = 0;
        return;
    }

    if(false == _connectFlag)
    {
        _tcpClient->abort();
        _connTimer->start();
        _tcpClient->connectToHost(_tcpServerAddr,_tcpServerPort);
        _connectCount++;
    }
}


void UpdateClient::startUpdate()
{
    if(_connectFlag == false)
    {
        _startUpdateFlag = 1;
        startConn();
    }
    else
    {
        sendUpdateCmd();
    }
}

void UpdateClient::startRecover()
{
    if(_connectFlag == false)
    {
        _startRecoverFlag = 1;
        startConn();
    }
    else
    {
        sendRecoverCmd();
    }
}

void UpdateClient::startGetVer()
{
    qDebug()<<"up client start get ver"<< "_cnflag"<<_connectFlag;
    if(_connectFlag == false)
    {
        _startGetVerFlag = 1;
        startConn();
    }
    else
    {
        sendGetVerCmd();
    }
}

void UpdateClient::rspTimeout()
{
    _tcpClient->abort();
    _connectFlag = false;
    _rspTimer->stop();
    _connTimer->stop();
}

void UpdateClient::readSetting()
{
    QSettings * configfile;
    QString addr, port;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("upgradeserver");
    addr = configfile->value("addr").toString();
    port = configfile->value("port").toString();
    _upgradeServer = addr + ":" + port;
    _filePath = configfile->value("file_path").toString();
    _ancVer = configfile->value("anc_ver").toString();
    configfile->endGroup();
    delete configfile;
}

//发送数据接口
void UpdateClient::sendMsg(const QByteArray &data)
{
    _tcpClient->write(data);
}

void UpdateClient::sendUpdateCmd()
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "cmd_type", "upgrade");
    cJSON_AddStringToObject(json, "upgrade_server", _upgradeServer.toLatin1().data());
    cJSON_AddStringToObject(json, "file_path", _filePath.toLatin1().data());
    cJSON_AddStringToObject(json, "anc_ver", _ancVer.toLatin1().data());

    char *strData = cJSON_Print(json);
    qDebug() << "cmd json str:"<< strData;
    QString s(strData);
    QByteArray outBlock ;
    outBlock = outBlock.append(s);

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(json);
    free(strData);

    _startUpdateFlag = 0;
    _rspTimer->start();//wait cmd rsp;

}

void UpdateClient::sendGetVerCmd()
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "cmd_type", "get_ver");

    char *strData = cJSON_Print(json);
    qDebug() << "cmd json str:"<< strData;
    QString s(strData);
    QByteArray outBlock ;
    outBlock = outBlock.append(s);

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(json);
    free(strData);

    _startGetVerFlag = 0;
    _rspTimer->start();//wait cmd rsp;

}

void UpdateClient::sendRecoverCmd()
{

    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "cmd_type", "recover");

    char *strData = cJSON_Print(json);
    qDebug() << "cmd json str:"<< strData;
    QString s(strData);
    QByteArray outBlock ;
    outBlock = outBlock.append(s);

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(json);
    free(strData);

    _startRecoverFlag = 0;
    _rspTimer->start();//wait cmd rsp;
}

void UpdateClient::readMessage()
{
    QDataStream readIn(_tcpClient);
    readIn.setVersion(QDataStream::Qt_5_7);

    QByteArray readBuf = _tcpClient->readAll();
    QString readStr = QString::fromLocal8Bit(readBuf);
    qDebug()<<"readStr"<<readStr;

    handleMsg(readStr);

}

void UpdateClient::handleMsg(QString msg)
{
   cJSON *json, *msgJson = NULL;
   json = cJSON_Parse(msg.toLatin1().data());
   if(json == NULL)
   {
       qDebug()<<"updateClient msg prase  err";
       return;
   }
   msgJson = cJSON_GetObjectItem(json, "resp");
   if(msgJson == NULL)
   {
       qDebug()<<"updateClient msg prase resp err";
       return;
   }

   QString str = QString(msgJson->valuestring);

   qDebug()<<"recv msg"<<str;

   if(str == QString("upgrade"))
   {
       _rspTimer->stop();
       _tcpClient->abort();
        emit sendUpCmdRsut(_aid, true);
   }
   else if(str == QString("recover"))
   {
       _rspTimer->stop();
       _tcpClient->abort();
        emit sendRecoverCmdRsut(_aid, true);
   }
   else if(str == QString("get_ver"))
   {
       cJSON * verJson = NULL;
       verJson = cJSON_GetObjectItem(json, "ver");
       if(verJson == NULL)
       {
           qDebug()<<"updateClient msg prase ver err";
           cJSON_Delete(json);
           return;
       }
       QString ver = QString(verJson->valuestring).section("/", -1, -1);
       _rspTimer->stop();
       _tcpClient->abort();
       emit sendGetVerRsut(_aid, ver);
   }

   cJSON_Delete(json);
}

void UpdateClient::disconnected()
{
    _connectFlag = false;
    qDebug()<<"updateClient disconnect";
}

void UpdateClient::printError(QAbstractSocket::SocketError)
{
    qDebug()<< "updateClient err:"<<_tcpClient->errorString();
    _tcpClient->abort();
    _connectFlag = false;
}

