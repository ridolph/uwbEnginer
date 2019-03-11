#include "UWB_UdpClient.h"
#include <QDebug>
#include "cJSON.h"
#include <QDataStream>
#include <QSettings>
UWB_UdpClient::UWB_UdpClient(int aid, QString server, QUdpSocket **pp_socket)
{
    setServer(server);
    _pp_udpSocket = pp_socket;
}

UWB_UdpClient::~UWB_UdpClient()
{

}

void UWB_UdpClient::setServer(QString server)
{
    _addr = server.section(":", 0, 0);
    _port = server.section(":", 1, 1).toInt();
    readSetting();
    qDebug()<<"udp set server:"<<_addr<<_port;
}

void UWB_UdpClient::startUpdate()
{
    readSetting();

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
}

void UWB_UdpClient::startRecover()
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
}

void UWB_UdpClient::startGetVer()
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

}

void UWB_UdpClient::readSetting()
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

void UWB_UdpClient::sendMsg(const QByteArray &data)
{
    qDebug()<<"msg:_addr:"<< _addr<<"_port"<<_port;
    (*_pp_udpSocket)->writeDatagram(data, QHostAddress(_addr), _port);
}
