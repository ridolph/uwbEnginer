#ifndef UWB_TCPCLIENT_H
#define UWB_TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QString>
//#include "ScanThread.h"
//#include "../location/location.h"

#define CMD_TYPE  "cmd_type"
#define CMD_DIR   "cmd_dir"
#define UPGRADE   "upgrade"
#define CHECK_VER "check_ver"
#define SERVER    "server"
#define FILE_PATH "file_path"
#define CUR_FILE  "cur_file"
#define ANC_VER   "anc_ver"
#define TAG_VER  "tag_ver"
#define ANC_UP_TIME   "anc_up_time"
#define TAG_UP_TIME   "tag_up_time"
#define DIR_QUERY "query"
#define DIR_RESP  "resp"
#define UP_STATUS "up_status"
#define UP_RESULT "up_result"

typedef enum {
    UP_SUCCESS = 0, //全部成功
    UP_DOING = 1,//升级中
    UP_HALF_FAILED = 2,//部分升级失败，版本回退中
    UP_ALL_FAILED = 3,//全部升级失败
    UP_REPEAT//版本重复
}_UP_STATUS;



class UWB_TcpClient: public QObject
{
    Q_OBJECT

public:
    explicit  UWB_TcpClient(QString addr, int port);
    ~UWB_TcpClient();
    void sendTagOnlineStatus(int tagId, int status);
    void sendTagAlarm(int tagId, int alarm, int op, QString areaCode);
    void sendPositon(int tagId, double x, double y, double z, QString areaCode);
	void sendPositonOutServer(int tagId, double x, double y, double z, QString areaCode);
    void sendTagHeartRate(int tagId, int heartRate, int power,int state);
    void setServer(QString addr, int port);


 signals:
    void startUpdate(QString ver);

public slots:
    void sendUpResp(int status, int *failBuf,int failCount, int *succBuf, int succCount);

    /*  发送标签状态    lwq 20190311    */
    void sendTagStatus(int tag_id, int tag_status, int tag_area);


private slots:
    void connectOk();
    void readMessage();
    void msgHandle(QString msg);
    void disconnected();
    void printError(QAbstractSocket::SocketError);
    void pingTimeout();
    void connTimeout();
    void pingRspTimeout();



private:
    void sendCkVerResp();
    //void sendUpResp(int status);

    void backupSetting();
    void writeSetting(QString server , QString file_path,  QString ver);
    void sendMsg(const QByteArray &data);
    QTcpSocket *_tcpClient;
    QTimer *_pingTimer;
    QTimer *_connTimer;
    QTimer *_pingRspTimer;
    bool _connectFlag;
    QString _serverAddr;
    int _serverPort;
};

#endif // UWB_TCPCLIENT_H
