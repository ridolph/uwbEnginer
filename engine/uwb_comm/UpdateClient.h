#ifndef UPDATECLIENT_H
#define UPDATECLIENT_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>

class UpdateClient: public QObject
{
   Q_OBJECT
public:
   explicit UpdateClient(int aid, QString tcpServer);
   ~UpdateClient();
    void setServer(QString tcpServer);
    void startConn();
    void startUpdate();
    void startRecover();
    void startGetVer();
private slots:
    void connectOk();
    void readMessage();
    void handleMsg(QString msg);
    void disconnected();
    void printError(QAbstractSocket::SocketError);
    void connTimeout();
    void rspTimeout();

signals:
    void sendUpCmdRsut(int aid, bool ok);
    void sendRecoverCmdRsut(int aid, bool ok);
    void sendGetVerRsut(int aid, QString ver);

private:
    void readSetting();

    int _aid;
    QString _tcpServerAddr;
    int _tcpServerPort;
    QString _upgradeServer;
    QString _filePath;
    QString _ancVer;
    QTcpSocket *_tcpClient;
    QTimer *_connTimer;
    QTimer *_rspTimer;
    bool _connectFlag;
    bool _startUpdateFlag;
    bool _startRecoverFlag;
    bool _startGetVerFlag;
    int _connectTimeLimit;
    int _connectCount;

   void sendMsg(const QByteArray &data);
   void sendUpdateCmd(void);
   void sendRecoverCmd(void);
   void sendGetVerCmd(void);
};

#endif // UPDATECLIENT_H
