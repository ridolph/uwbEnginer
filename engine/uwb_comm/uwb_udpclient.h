#ifndef UWB_UDPCLIENT_H
#define UWB_UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QString>

class UWB_UdpClient :public QObject
{
        Q_OBJECT
public:
    explicit UWB_UdpClient(int aid, QString server,QUdpSocket **pp_socket);
    ~UWB_UdpClient();
    void setServer(QString server);
    void startUpdate();
    void startRecover();
    void startGetVer();
    //void startSyn();
private:
   void readSetting();
   void sendMsg(const QByteArray &data);
    QUdpSocket **_pp_udpSocket;
    QString  _addr;
    int _port;
    QString _upgradeServer;
    QString _filePath;
    QString _ancVer;

};

#endif // UWB_UDPCLIENT_H
