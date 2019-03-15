// -------------------------------------------------------------------------------------------------------------------
//
//  File: RTLSClient.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef RTLSCLIENT_H
#define RTLSCLIENT_H

#include <QObject>

#include "SerialConnection.h"
#include "trilateration.h"
#include <stdint.h>
#include <QSettings>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTimer>
#include "../uwb_comm/UWB_WebSocket.h"
#include "../uwb_comm/UWB_HTTP.h"
#include "../uwb_comm/UWB_TcpClient.h"
#include "../uwb_comm/tagInfo/tagInfo.h"
#include <QMap>
#include "KlmanFilter.h"



class QFile;
class DataAnchor;
class DataTag;

//#include <armadillo>
//using namespace arma;

#define PI (3.141592653589793)

#define MAX_NUM_ANCS_RNG 3 //A0-A1, A0-A2, A1-A2
#define ANC_RANGE_HIST 25
#define HIS_LENGTH 50
#define FILTER_SIZE 10  //NOTE: filter size needs to be > 2
#define FILTER_SIZE_SHORT 6

#define MAX_NUM_TAGS MAX_TAG_NUM
#define MAX_NUM_ANCS (200)   //扩容

typedef struct
{
    int aid;
    int range;
}ANC_RANGE;

typedef QList<ANC_RANGE> QARList;

typedef struct
{
    double x_arr[HIS_LENGTH];
    double y_arr[HIS_LENGTH];
    double z_arr[HIS_LENGTH];
    double av_x, av_y, av_z; //average
    double fx, fy, fz; //filter average
    double sqx_arr[HIS_LENGTH]; //square x
    double sqy_arr[HIS_LENGTH];
    double sqz_arr[HIS_LENGTH];
    double avsq_x, avsq_y, avsq_z; //average of squares
    double errx_arr[HIS_LENGTH]; //error x (x-av_x)
    double erry_arr[HIS_LENGTH];
    double errz_arr[HIS_LENGTH];
    double averr_x, averr_y, averr_z; //avearge error
    double variancex, variancey, variancez;
    double std_x, std_y, std_z;
    double r95;
    int id;
    int arr_idx;
    int count;
	int msec;
	int packetlossrate;
    int numberOfLEs;
    int filterReady;
    bool ready;
    int rangeSeq;//current handle seq
    int newestSeq;
    int startMsec;//time of start handle seq
    int newestRecvMsec;//newest data seq
    int seqDelayCount;
    int rangeCount[256];
    int rangeValue[256][MAX_NUM_ANCS]; //(mm) each tag ranges to 4 anchors - it has a range number which is modulo 256
    KlmanFilter *xKlman;
    KlmanFilter *yKlman;
    int lstEftSec;
    int heartRate;//default 0xff
    int power;//default 0xff
    int state;//default 0xff

    /*  20190311 新增   lwq*/
    int workState;  //标签工作状态 0：离线 1：在线 2：休眠 3：异常
    QDateTime upTime;   //上线时间
    QDateTime downTime; //下线时间
    //QString area;   //区域范围
} tag_reports_t;



typedef struct
{
    double x, y, z;
    uint64_t id;
    QString label;
    int tagRangeCorection[MAX_NUM_TAGS];
    bool show;

    /*  20190311 新增   lwq*/
    int workState;  //基站工作状态 0：离线 1：在线 2：异常
    int group;  //基站所属组
    QList<int> tagId;    //标签ID
    int tagSum; //标签总数
} anc_struct_t;


typedef struct 
{
    double x, y, z;
    uint64_t id;
    QString label;
    int tagRangeCorection[MAX_NUM_TAGS];
    bool show;

    /*  20190311 新增   lwq*/
    QString addr;
    int port;
    int workState;  //基站工作状态 0：离线 1：在线 2：异常
    int group;  //基站所属组
    QList<int> tagId;    //标签ID
    int tagSum; //标签总数

    int klmanFlag;  
    KlmanFilter *xKlman;
    KlmanFilter *yKlman;
}anc_reports_t;

typedef struct
{
    int group;
    int klmanFlag;  
    KlmanFilter *xKlman;
    KlmanFilter *yKlman;
   

}filter_config_t;

typedef struct
{
    double x, y, z;
    uint64_t id;
} pos_report_t;

typedef struct
{
  double x;
  double y;
} vec2d;

class RTLSClient : public QObject
{
    Q_OBJECT
public:
    explicit RTLSClient(QObject *parent = 0);

    void test();
    int calcVec1Loc(vec3d *report, int *ranges);
    int calculateTagLocation(vec3d *report, int count, int mask,int *ranges);
	int getareaid(double x,double y,int labelid);
    void updateTagStatistics(int i, double x, double y, double z);
    void initialiseTagList(int id);
    double process_ma(double *array, int idx);
    double process_me(double *array, int idx);
    double process_avg(int idx);
    void setGWReady(bool set);
    void setUseAutoPos(bool useAutoPos);
    QStringList getLocationFilters(void);
    void setLocationFilter(int filter);
    void saveConfigFile(QString filename);
    void loadConfigFile(QString filename);

    int* getTagCorrections(int anchID);

    void addMissingAnchors(void);

    void trilaterateTag(int tid, int seq, int mask);
    void processTagRangeReport(int aid, int tid, int range, int lnum, int seq, QString addr);
    void processAnchRangeReport(int aid, int tid, int range, int lnum, int seq);
    void processHeartRateReport(int tid, int heartRate, int power, int state);

    //void mds(mat twrdistance, int nNodes, int viewNode, mat* transCoord);
    //void angleRotation(mat transCoord, int nNodes, mat* estCoord);
    void getAreaCode(AREA_TYPE type, QString &code);

    void openLogFile(QString userfilename);
    void closeLogFile(void);
    const QString &getLogFilePath();
	void readdiscountSettings(void);
    void readJavaServerSettings(void);
    void writeJavaServerSettings(void);
	void writeOutServerSettings(void);
    void createDataLog();
    void writeBaseDataLog(QString writeStr);
    void writeHandleDataLog(QString writeStr);
    UWB_TcpClient* uwbTcpClient();
    void handleMsg(QByteArray &data);

    void tagPositionCorrect(double *fx, double *fy, double fx_j, double fy_j);


signals:
    void tagHeartRate(quint64 tagId, quint64 rate, quint64 power,quint64 plossRate);
    void anchPos(quint64 anchorId, double x, double y, double z,bool, bool);
    void tagPos(quint64 tagId, double x, double y, double z);
    void tagStats(quint64 tagId, double x, double y, double z, double r95);
    void tagRange(quint64 tagId, quint64 aId, double x);
    void statusBarMessage(QString status);

    void centerOnAnchors();
    void enableFiltering(void);
    void ancRanges(int a01, int a02, int a12);
    void dsptcpLog(QString str);
    void updateAncAddr(int aid, QString addr, int port);
    void closeApp();

    void sendUpCmdRsut(int aid, bool ok);
    void sendRecoverCmdRsut(int aid, bool ok);
    void sendGetVerRsut(int aid, QString ver);

    void anchInfo(int, int, double, double, double);


public slots:
    void newUdpData();
    void newTcpOrSerialData();
    void newData(QByteArray &data, QString addr, qint64 port);
    void SendCellOnlineStatus(int tagId, uint8_t status);
    void SendAlarm(int tagId, ALARM_TYPE alarmType, uint8_t op);
    void setServer(QString addr, int port);
    void setOutServer(QString addr, int port);

    /*  新增 lwq 20190315   */
    void sendAncStatus(int aid, QString addr, int port);
    void sendAncStatusDown(int aid);
    void addNewAncTagSum(int ancID, int tagID);
    
protected slots:
    void onReady();
    void onConnected(QString ver, QString conf);

    void updateAnchorXYZ(int id, int x, double value);
    void updateTagCorrection(int aid, int tid, int value);
    void updateAnchorShow(int id, bool show);

    /*  定时发送基站状态    lwq 20190315    */
    void sendAncStatusTimeOut(void);

private slots:
    void connectionStateChanged(SerialConnection::ConnectionState);
    void periodCalcProcess();

public:
    bool is_socket_connected;

    QTcpSocket *_tcpSocket;
    QUdpSocket *_udpSocket;
    UWB_WebSocketServer *_WebSocketServer;
    UWB_HTTP *_HttpClient;
    UWB_TcpClient *_tcpClient;
	UWB_TcpClient *_tcpClientOutServer;
  

    /*  定时上报状态信息    */
    QTimer *_sendStatusOntimeTimer;

private:
    bool _graphicsWidgetReady;
    bool _first;
    bool _useAutoPos;

    QList <tag_reports_t> _tagList;
    QList <anc_reports_t> _ancList;

    anc_struct_t _ancArray[MAX_NUM_ANCS];
    int _ancMaxShowCount;
    int _ancRangeCount;
    double _ancRangeArray[MAX_NUM_ANCS_RNG][ANC_RANGE_HIST]; //contains the last 50 ranges so we can calculate average

    double _ancRangeValues[MAX_NUM_ANCS][MAX_NUM_ANCS];
    double _ancRangeValuesAvg[MAX_NUM_ANCS][MAX_NUM_ANCS];

    QFile *_file;
    QFile *_fileDbg;

    QFile *_baseDataFile;
    QFile *_handleDataFile;

	QSettings *_configfile;

    QSerialPort *_serial;
    QStringList _locationFilterTypes ;
    int _usingFilter;
    uint8_t _ancRangeLastSeq;
    uint8_t _configuration;
    QString _version;
    QString _config;
    QString _logFilePath;
    QString _javaServerAddr;
	QString _OutServerAddr;
    int     _javaServerPort;
	int     _OutServerPort;
    QTimer *_periodCalcTimer;

	int _min;
	int _count;
    int _filterSize;
};

void r95Sort(double s[], int l, int r);

#endif // RTLSCLIENT_H
