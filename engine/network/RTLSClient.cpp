// -------------------------------------------------------------------------------------------------------------------
//
//  File: RTLSClient.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "RTLSClient.h"

#include "RTLSDisplayApplication.h"
#include "SerialConnection.h"
#include "mainwindow.h"
#include "trilateration.h"

#include <QTextStream>
#include <QDateTime>
#include <QThread>
#include <QFile>
#include <QDebug>
#include <math.h>
#include <QMessageBox>

#include <QDomDocument>
#include <QFile>
#include <time.h>
#include <QJsonObject>
#include "../uwb_comm/cJSON.h"
#include "../uwb_comm/ScanThread.h"
#include "../tools/vec1.h"
#include <QtCore>
#include "uwb_comm/cJSON.h"

//extern "C"_declspec(dllimport)   void  LSQR (double *E, double *b, double *r, int nLtrace, int Nref, double e)
//extern "C"_declspec(dllimport)   void  location_4P (double *CtrPoints, double *d, double *P)

#include <locdll.h>

#include "LinkList.h"


//#define MAX((x),(y)) ((x) > (y)? (x): (y))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define DEBUG_FILE 0

#define LOG_FILE_MAX_SIZE  209715200 //200*1024*1024

//#define TOF_REPORT_LEN  (65)
//#define TOF_REPORT_ARGS (12)


extern int g_locCorrectEnable;
extern int g_klmanEnable;
extern int g_vec;

#define PING_REPORT_LEN  (5)
#define TOF_REPORT_LEN  (184)
#define TOF_REPORT_ARGS (27)//参数个数

#define TOF_REPORT_TYPE_DC  (1)
#define TOF_REPORT_LEN_DC  (184)
#define TOF_REPORT_TYPE_ND  (2)
#define TOF_REPORT_LEN_ND  (135)

using namespace std;

#define nDim (2)


#define KLMAN_Q  0.1//卡尔曼系统噪声,经验值0.1
#define KLMAN_R  0.1//卡尔曼测量噪声,经验值0.1

/*	用于判断是否超出区域范围	*/
#define AREA_X			10.599999
#define AREA_Y			5.499999	
#define ZEROPLUS		0.000001	//0值	
#define MODIFYVALUE	0.040001		//修正值



void testpos(void)
{
    double CtrPoints[12] = {18.22, 4.79, 2.70, 10.08, 4.79, 2.70,  10.00, 11.24, 2.70, 17.99, 8.87, 2.70};
    double d[4] = {3.064, 5.997, 7.466, 3.271};
    double P[3] = {0};
    //新算法基站位置赋值

    location_4P(CtrPoints,d, P);
    qDebug()<<"TEST POS:";
    qDebug()<<"Ctr:"<<CtrPoints[0]<<CtrPoints[1]<<CtrPoints[2]<<CtrPoints[3]<<CtrPoints[4]<<CtrPoints[5]<<CtrPoints[6]<<
             CtrPoints[7]<<CtrPoints[8]<<CtrPoints[9]<<CtrPoints[10]<<CtrPoints[11];
    qDebug()<<"rang4:"<<d[0]<<d[1]<<d[2]<<d[3];
    qDebug()<<"pos:"<<P[0]<<P[1]<<P[2];
}

void testpos2(void)
{
    double CtrPoints[12] = {17.99, 8.87, 2.70, 10.08, 4.79, 2.70,  10.00, 11.24, 2.70, 17.99, 8.87, 2.70};
    double d[4] = {3.271, 5.997, 7.466, 3.271};
    double P[3] = {0};
    //新算法基站位置赋值

    location_4P(CtrPoints,d, P);
    qDebug()<<"TEST POS:";
    qDebug()<<"Ctr:"<<CtrPoints[0]<<CtrPoints[1]<<CtrPoints[2]<<CtrPoints[3]<<CtrPoints[4]<<CtrPoints[5]<<CtrPoints[6]<<
             CtrPoints[7]<<CtrPoints[8]<<CtrPoints[9]<<CtrPoints[10]<<CtrPoints[11];
    qDebug()<<"rang4:"<<d[0]<<d[1]<<d[2]<<d[3];
    qDebug()<<"pos:"<<P[0]<<P[1]<<P[2];
}


void testpos3(void)
{
    double CtrPoints[12] = {18.22, 4.79, 2.70, 17.99, 8.87, 2.70,  10.00, 11.24, 2.70, 17.99, 8.87, 2.70};
    double d[4] = {3.064, 3.271, 7.466, 3.271};
    double P[3] = {0};
    //新算法基站位置赋值

    location_4P(CtrPoints,d, P);
    qDebug()<<"TEST POS:";
    qDebug()<<"Ctr:"<<CtrPoints[0]<<CtrPoints[1]<<CtrPoints[2]<<CtrPoints[3]<<CtrPoints[4]<<CtrPoints[5]<<CtrPoints[6]<<
             CtrPoints[7]<<CtrPoints[8]<<CtrPoints[9]<<CtrPoints[10]<<CtrPoints[11];
    qDebug()<<"rang4:"<<d[0]<<d[1]<<d[2]<<d[3];
    qDebug()<<"pos:"<<P[0]<<P[1]<<P[2];
}

void testpos4(void)
{
    double CtrPoints[12] = {18.22, 4.79, 2.70, 10.08, 4.79, 2.70,  17.99, 8.87, 2.70, 17.99, 8.87, 2.70};
    double d[4] = {3.064, 5.997, 3.271, 3.271};
     double P[3] = {0};
    //新算法基站位置赋值

    location_4P(CtrPoints,d, P);
    qDebug()<<"TEST POS:";
    qDebug()<<"Ctr:"<<CtrPoints[0]<<CtrPoints[1]<<CtrPoints[2]<<CtrPoints[3]<<CtrPoints[4]<<CtrPoints[5]<<CtrPoints[6]<<
             CtrPoints[7]<<CtrPoints[8]<<CtrPoints[9]<<CtrPoints[10]<<CtrPoints[11];
    qDebug()<<"rang4:"<<d[0]<<d[1]<<d[2]<<d[3];
    qDebug()<<"pos:"<<P[0]<<P[1]<<P[2];
}


void testpos5(void)
{
    double CtrPoints[12] = {18.22, 4.79, 2.70, 10.08, 4.79, 2.70,  10.00, 11.24, 2.70, 18.22, 4.79, 2.70};
    double d[4] = {3.064, 5.997, 7.466, 3.064};
    double P[3] = {0};
    //新算法基站位置赋值

    location_4P(CtrPoints,d, P);
    qDebug()<<"TEST POS:";
    qDebug()<<"Ctr:"<<CtrPoints[0]<<CtrPoints[1]<<CtrPoints[2]<<CtrPoints[3]<<CtrPoints[4]<<CtrPoints[5]<<CtrPoints[6]<<
             CtrPoints[7]<<CtrPoints[8]<<CtrPoints[9]<<CtrPoints[10]<<CtrPoints[11];
    qDebug()<<"rang4:"<<d[0]<<d[1]<<d[2]<<d[3];
    qDebug()<<"pos:"<<P[0]<<P[1]<<P[2];
}



/**
* @brief RTLSDisplayApplication
*        Constructor, it consumes the data received over the COM port connection and sends the
*        processed data to the graphical display
* */
RTLSClient::RTLSClient(QObject *parent) :
    QObject(parent),
    _first(true),
    _useAutoPos (false),
    _file(NULL),
    _fileDbg(NULL)
{

    /*
    Filter Types
    0 - No Filtering
    1 - Moving Average
    2 - Moving Average excluding max and min
    */
    _locationFilterTypes << "None" << "Moving Average" << "Moving Avg. Ex";
    _usingFilter = 0;

    _graphicsWidgetReady = false ;
    _tagList.clear();

    //memset(&_ancArray, 0, MAX_NUM_ANCS*sizeof(anc_struct_t));
    _serial = NULL;

    _filterSize = FILTER_SIZE_SHORT ;

    for(int a0 = 0; a0 < MAX_NUM_ANCS; a0++)
    {
        for(int b0 = 0; b0 < MAX_NUM_ANCS; b0++)
        {
            _ancRangeValues[a0][b0] = 0;
            _ancRangeValuesAvg[a0][b0] = 0;
        }
    }

	LinkList anc_info;
	LinkList tag_info;


    _ancRangeLastSeq = 0x0;
    _ancRangeCount = 0;

    RTLSDisplayApplication::connectReady(this, "onReady()");

}






void RTLSClient::onReady()
{
    initAllArea();//里面一些参数需要allready之后加载
    tagInfoInit();

    //createDataLog();

    //_WebSocketServer = new UWB_WebSocketServer(1234);
    //_HttpClient = new UWB_HTTP(HTTP_3D_URL);

    readdiscountSettings();
    readJavaServerSettings();
    _tcpClient = new UWB_TcpClient(_javaServerAddr, _javaServerPort);
    _tcpClientOutServer = new UWB_TcpClient(_OutServerAddr, _OutServerPort);

    //start scan thread
    ScanThread *scanThread = new ScanThread;
    connect(scanThread,SIGNAL(SendCellOnlineStatus(int,uint8_t)),this,SLOT(SendCellOnlineStatus(int,uint8_t)), Qt::BlockingQueuedConnection);
    connect(scanThread,SIGNAL(SendAlarm(int, ALARM_TYPE, uint8_t)),this, SLOT(SendAlarm(int, ALARM_TYPE, uint8_t)), Qt::BlockingQueuedConnection);
    scanThread->start();

    _periodCalcTimer = new QTimer;
    connect(_periodCalcTimer, SIGNAL(timeout()), this, SLOT(periodCalcProcess()));
    _periodCalcTimer->setInterval(200);
    _periodCalcTimer->start();

    QObject::connect(RTLSDisplayApplication::serialConnection(), SIGNAL(serialOpened(QString, QString)),
                         this, SLOT(onConnected(QString, QString)));

}


void tmpFunc()
{
#if 0
    double CtrPoints[12] ={0,0,2,-1,0,2,0,-1,2,-1,-1,2};
    double d[4] ={20,15,10,15};
    double P[3] ={0};

    location_4P( CtrPoints,d, P);
    printf(" x=%0.2f y=%0.2f z=%0.2f",P[0],P[1],P[2]);
#endif
}

void RTLSClient::onConnected(QString ver, QString conf)
{
    bool ok = true;
    int anchor = 0, chan = 2, mode = 0, addr = 0, addr1 = 0, m = 0;
    //tag or anchor, chan 2 or 5,

    _first = true;
    _version = ver ;
    _configuration = conf.toLocal8Bit().at(0);



    qDebug() << "configuration " << "0x"+QString::number(_configuration, 16);
    if(ok)
    {
        m = (_configuration & 6) >> 1;

        if(m & 0x1)
        {
            _filterSize = FILTER_SIZE ;
        }
        else
        {
            _filterSize = FILTER_SIZE_SHORT ;
        }

        if(_configuration & 0x8)
        {
            anchor = 1;
        }

        mode = (_configuration & 0x2) >> 1;

        if(_configuration & 0x4)
        {
            chan = 5 ;
        }

        addr1 = (_configuration & 0x70) >> 4;

        addr = ((addr1 >> 2) & 0x1) + (((addr1 >> 1) & 0x1) << 1) + ((addr1 & 0x1) << 2);
    }

    //write the header
    if(anchor)
    {
        _config = QString(":Conf:Anchor%1:%2:Chan%3\n").arg(addr).arg(mode).arg(chan);
        emit statusBarMessage(QString("DecaRangeRTLS Anchor ID%1 Mode %2").arg(addr).arg(m));
        qDebug() << QString("DecaRangeRTLS Anchor ID%1 Mode %2").arg(addr).arg(m);
#if 0
        if(addr & 0x3) //anchors 1, 2, and 3 don't support RTLS (only geo fencing)
        {
            QMessageBox::about(NULL, tr("COM"), QString("Connected to Anchor %1.\nRTLS is not supported, only Geo-fencing mode.").arg(addr));
        }
        else if (addr == 0x4)
        {
            QMessageBox::about(NULL, tr("COM"), QString("Connected to Listener.\nBoth RTLS and Geo-fencing modes are supported."));
        }
        else
        {
            QMessageBox::about(NULL, tr("COM"), QString("Connected to Anchor %1.\nBoth RTLS and Geo-fencing modes are supported.").arg(addr));
        }
#endif
    }
    else
    {
        _config = QString(":Conf:Tag%1:%2:Chan%3\n").arg(addr).arg(mode).arg(chan);
        emit statusBarMessage(QString("DecaRangeRTLS Tag ID%1 Mode %2").arg(addr).arg(m));
        qDebug() << QString("DecaRangeRTLS Tag ID%1 Mode %2").arg(addr).arg(m);
#if 0
        QMessageBox::about(NULL, tr("COM"), QString("Connected to Tag %1.").arg(addr));
#endif
    }
    //get pointer to Serial connection serial port pointer
    is_socket_connected = false;
    _serial = RTLSDisplayApplication::serialConnection()->serialPort();
    connect(_serial, SIGNAL(readyRead()), this, SLOT(newTcpOrSerialData()));
}


void RTLSClient::openLogFile(QString userfilename)
{
    QDateTime now = QDateTime::currentDateTime();

    _logFilePath = "./Logs/"+now.toString("yyyyMMdd_hhmmss")+"RTLS_log.txt";

    _first = true;

    _file = new QFile(_logFilePath);
#if (DEBUG_FILE==1)
    QString filenameDbg("./Logs/"+now.toString("yyyyMMdd_hhmmss")+"RTLS_log_dbg.txt");
    _fileDbg = new QFile(filenameDbg);
    if (!_fileDbg->open(QFile::ReadWrite | QFile::Text))
    {
        qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg(filename).arg(_file->errorString())));
        //QMessageBox::critical(NULL, tr("Logfile Error"), QString("Cannot create file %1 %2\nPlease make sure ./Logs/ folder exists.").arg(filename).arg(_file->errorString()));
    }
#endif
    if (!_file->open(QFile::ReadWrite | QFile::Text))
    {
        qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg(_logFilePath).arg(_file->errorString())));
        QMessageBox::critical(NULL, tr("Logfile Error"), QString("Cannot create file %1 %2\nPlease make sure ./Logs/ folder exists.").arg(_logFilePath).arg(_file->errorString()));
    }
    else
    {
        QString nowstr = now.toString("T:hhmmsszzz:");
        QString s = nowstr + QString("DecaRangeRTLS:LogFile:") + _version + _config;
        QTextStream ts( _file );
        ts << s;
    }
}

void RTLSClient::closeLogFile(void)
{
    if(_file)
    {
        _file->flush();
        _file->close();

        _file = NULL ;
    }

#if (DEBUG_FILE==1)
    if(_fileDbg)
    {
        _fileDbg->flush();
        _fileDbg->close();

        _fileDbg = NULL ;
    }
#endif
}


void RTLSClient::createDataLog()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timeStr = time.toString("yyyyMMdd-hhmmss"); //设置显示格式

    QString logDir = QString("LOG/");
    QDir t_writeDir(logDir);
    if(t_writeDir.exists())
    {
       // qDebug()<<"dir log is exist";
    }
    else
    {
        qDebug()<<"dir log is not exist";
        QDir tDir;

        tDir.mkpath(logDir);
        qDebug()<<"create logDir"<<logDir;
    }

    QString baseDatalogFile =  logDir + timeStr + QString("_base.log");
    QString handleDatalogFile =  logDir + timeStr + QString("_handle.log");

    //_baseDataFile = new QFile(baseDatalogFile);
    _handleDataFile = new QFile(handleDatalogFile);

    //_baseDataFile->open(QIODevice::Append|QIODevice::Text);
    _handleDataFile->open(QIODevice::Append|QIODevice::Text);

    //打开文件是否成功
    //if((!_baseDataFile->isOpen()) || (!_handleDataFile->isOpen()))
    if(!_handleDataFile->isOpen())
    {
        qDebug() << "open file : " << "data file" << "failed!";
        return;
    }

    _handleDataFile->close();
    //_baseDataFile->close();
}
//记录处理过的数据日志
void RTLSClient::writeHandleDataLog(QString writeStr)
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timeStr = time.toString("[yyyyMMdd-hh:mm:ss]"); //设置显示格式
    unsigned int pos = 0;

    if(NULL == _handleDataFile)
    {
        return;
    }
    _handleDataFile->open(QIODevice::Append|QIODevice::Text);

    //声明一个文本流对象,与文件绑定
    QTextStream t_textStream(_handleDataFile);
    t_textStream <<timeStr<<" "<<writeStr<<"\n";
    pos = _handleDataFile->pos();

    _handleDataFile->flush();
    _handleDataFile->close();


    if(pos > LOG_FILE_MAX_SIZE)
    {
        delete _handleDataFile;
        //delete _baseDataFile;
        createDataLog();
    }
}

UWB_TcpClient* RTLSClient::uwbTcpClient()
{
    return _tcpClient;
}

//记录原始数据日志
void RTLSClient::writeBaseDataLog(QString writeStr)
{
    if(NULL == _baseDataFile)
    {
        return;
    }
    _baseDataFile->open(QIODevice::Append|QIODevice::Text);
    //声明一个文本流对象,与文件绑定
    QTextStream t_textStream(_baseDataFile);
    t_textStream <<writeStr<<"\n";
    _baseDataFile->flush();
    _baseDataFile->close();
}


const QString &RTLSClient::getLogFilePath()
{
    return _logFilePath;
}
void RTLSClient::readdiscountSettings()
{
    _configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    _configfile->beginGroup("discount");
    _min = _configfile->value("min").toInt();
    _count =  _configfile->value("count").toInt();
    if(_min == 0)
    {
        _min = 1;
        _count =154;
    }
    _configfile->endGroup();
    delete _configfile;
}


void RTLSClient::readJavaServerSettings()
{
    _configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    _configfile->beginGroup("javatcpserver");
    _javaServerAddr = _configfile->value("inaddr").toString();
    if(_javaServerAddr.isEmpty())
    {
        qDebug()<<"uwbconfig.ini inserver impty";
    }

    _OutServerAddr = _configfile->value("outaddr").toString();
    if(_OutServerAddr.isEmpty())
    {
        qDebug()<<"uwbconfig.ini outserver impty";
    }
    _javaServerPort = _configfile->value("inport").toInt();
    _OutServerPort = _configfile->value("outport").toInt();
    delete _configfile;
}
void RTLSClient::writeJavaServerSettings()
{
    _configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    _configfile->setValue("/javatcpserver/inaddr", _javaServerAddr);
    _configfile->setValue("/javatcpserver/inport", _javaServerPort);
    delete _configfile;
}

void RTLSClient::writeOutServerSettings()
{
    _configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    _configfile->setValue("/javatcpserver/outaddr", _OutServerAddr);
    _configfile->setValue("/javatcpserver/outport", _OutServerPort);
    delete _configfile;
}


//initialise the tag reports strusture and add to the list
void RTLSClient::initialiseTagList(int id)
{
    tag_reports_t r;
    memset(&r, 0, sizeof(tag_reports_t));
    r.id = id;
    r.ready = false;
    r.filterReady = 0;
    r.rangeSeq = -1;
    r.startMsec = 0;
    r.seqDelayCount = 0;
    memset(&r.rangeValue[0][0], -1, sizeof(r.rangeValue));
    r.xKlman = new KlmanFilter(KLMAN_Q,KLMAN_R);
    r.yKlman = new KlmanFilter(KLMAN_Q,KLMAN_R);
    r.lstEftSec = 0;
    r.heartRate = 0xff;
    r.power = 0xff;
    r.state = 0xff;
    _tagList.append(r);
}

//calculate average of last 10
double RTLSClient::process_ma(double *array, int idx)
{
    double sum = 0;
    int i, j;

    for(j=0, i=idx; j<_filterSize; i--, j++)
    {
        if(i < 0)
        {
            i = (HIS_LENGTH - 1);
        }
        sum += array[i];
    }
    return (sum / _filterSize);
}

//calculate average (of last 10) excluding min and max
double RTLSClient::process_me(double *array, int idx)
{
    double max, min, sum;
    int i, j;

    sum = max = min = array[idx];

    i=(idx--);

    if(i < 0)
    {
        i = (HIS_LENGTH - 1);
    }

    for(j=0; j<(_filterSize-1); i--, j++)
    {
        if(i < 0)
        {
            i = (HIS_LENGTH - 1);
        }
        if (array[i] > max)
        {
            max = array[i];
        }
        if (array[i] < min)
        {
            min = array[i];
        }
        sum += array[i];
    }

    sum = sum - max - min;

    return (sum / (_filterSize - 2));
}

void RTLSClient::updateTagStatistics(int i, double x, double y, double z)
//update the history array and the average
{
    QDateTime now = QDateTime::currentDateTime();
    QString nowstr = now.toString("T:hhmmsszzz:");
    int j = 0;
    int idx = _tagList.at(i).arr_idx;
    uint64_t id = _tagList.at(i).id;
    tag_reports_t rp = _tagList.at(i);
    double avDistanceXY = 0;
    double sum_std = 0;
    double DistanceXY[HIS_LENGTH];
    double DstCentreXY[HIS_LENGTH];
    double stdevXY = 0;

    rp.av_x = 0;
    rp.av_y = 0;
    rp.av_z = 0;


    for(j=0; j<HIS_LENGTH; j++)
    {
       rp.av_x += rp.x_arr[j];
       rp.av_y += rp.y_arr[j];
       rp.av_z += rp.z_arr[j];
    }

    rp.av_x /= HIS_LENGTH;
    rp.av_y /= HIS_LENGTH;
    rp.av_z /= HIS_LENGTH;

    for(j=0; j<HIS_LENGTH; j++)
    {
        DistanceXY[j] = sqrt((rp.x_arr[j] - rp.av_x)*(rp.x_arr[j] - rp.av_x) + (rp.y_arr[j] - rp.av_y)*(rp.y_arr[j] - rp.av_y));
    }

    for (j=0; j<HIS_LENGTH; j++)
    {
        avDistanceXY += DistanceXY[j]/HIS_LENGTH;
    }

    for(j=0; j<HIS_LENGTH; j++)
    {
        sum_std += (DistanceXY[j]-avDistanceXY)*(DistanceXY[j]-avDistanceXY);

    }

    stdevXY = sqrt(sum_std/HIS_LENGTH);

    vec2d sum_tempXY = {0, 0};
    vec2d CentrerXY = {0, 0};

    int counterXY = 0;

    for(j=0; j<HIS_LENGTH; j++)
    {
        if (DistanceXY[j] < stdevXY*2)
        {
            sum_tempXY.x += rp.x_arr[j];
            sum_tempXY.y += rp.y_arr[j];
            counterXY++;
        }

    }

    CentrerXY.x  = sum_tempXY.x/counterXY;
    CentrerXY.y  = sum_tempXY.y/counterXY;

    for(j=0; j<HIS_LENGTH; j++)
    {
        DstCentreXY[j] = sqrt((rp.x_arr[j] - CentrerXY.x)*(rp.x_arr[j] - CentrerXY.x) + (rp.y_arr[j] - CentrerXY.y)*(rp.y_arr[j] - CentrerXY.y));
    }

    r95Sort(DstCentreXY,0,HIS_LENGTH-1);

    rp.r95 = DstCentreXY[int(0.95*HIS_LENGTH)];

    //R95 = SQRT(meanErrx*meanErrx + meanErry*meanErry) + 2*SQRT(stdx*stdx+stdy*stdy)
    //rp.r95 = sqrt((rp.averr_x*rp.averr_x) + (rp.averr_y*rp.averr_y)) +
    //        2.0 * sqrt((rp.std_x*rp.std_x) + (rp.std_y*rp.std_y)) ;


    //update the value in the array
    rp.x_arr[idx] = x;
    rp.y_arr[idx] = y;
    rp.z_arr[idx] = z;

    rp.arr_idx++;
    //wrap the index
    if(rp.arr_idx >= HIS_LENGTH)
    {
        rp.arr_idx = 0;
        rp.ready = true;
        rp.filterReady = 1;
    }

    rp.count++;


    if(rp.filterReady > 0)
    {
        if((_usingFilter == 2) ||(_usingFilter == 0) )
        {
            rp.fx = process_me(rp.x_arr, idx);
            rp.fy = process_me(rp.y_arr, idx);
            rp.fz = process_me(rp.z_arr, idx);
        }
        else if (_usingFilter == 1)
        {
            rp.fx = process_ma(rp.x_arr, idx);
            rp.fy = process_ma(rp.y_arr, idx);
            rp.fz = process_ma(rp.z_arr, idx);
        }

        //qDebug() << rp.fx << rp.fy << rp.fz ;

        if(rp.filterReady == 1)
        {
            emit enableFiltering();
            rp.filterReady++;
        }
    }

    //update the list entry
    _tagList.replace(i, rp);

    if(rp.ready)
    {
        if(_graphicsWidgetReady)
        {
            emit tagStats(id, CentrerXY.x, CentrerXY.y, rp.av_z, rp.r95);
        }

        if(_file)
        {
            //log data to file
            QString s = nowstr + QString("TS:%1 avx:%2 avy:%3 avz:%4 r95:%5\n").arg(id).arg(rp.av_x).arg(rp.av_y).arg(rp.av_z).arg(rp.r95);
            QTextStream ts( _file );
            ts << s;
        }
        rp.ready = false;
    }
}

void RTLSClient::setUseAutoPos(bool useAutoPos)
{
    _useAutoPos = useAutoPos;

    return;
}

QStringList RTLSClient::getLocationFilters(void)
{
    return _locationFilterTypes;
}

/*
Filter Types
0 - No Filtering
1 - Moving Average
2 - Moving Average excluding max and min
3 - Kalman Filter
*/
void RTLSClient::setLocationFilter(int filter)
{
    _usingFilter = filter ;
}


void RTLSClient::handleMsg(QByteArray &data)
{
   cJSON *json = NULL, *msgJson = NULL;
   json = cJSON_Parse(data.data());
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

   msgJson = cJSON_GetObjectItem(json, "aid");
   if(msgJson == NULL)
   {
       qDebug()<<"updateClient msg prase aid err";
       return;
   }
   int aid = msgJson->valueint;


   qDebug()<<"recv msg"<<str;

   if(str == QString("upgrade"))
   {
        emit sendUpCmdRsut(aid, true);
   }
   else if(str == QString("recover"))
   {
        emit sendRecoverCmdRsut(aid, true);
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
       QString ver = QString(verJson->valuestring);//.section("/", -1, -1);
       emit sendGetVerRsut(aid, ver);
   }

   cJSON_Delete(json);
}

void RTLSClient::newUdpData()
{
    QByteArray data;
    QHostAddress cliAddr;
    quint16  port;

#if 0	

    QDateTime now = QDateTime::currentDateTime();
    QString nowstr = now.toString("yyyyMMdd_hhmmss");

	/*	用于压力测试记录 */
	QFile file("log.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Append);	  
	QTextStream text_stream(&file);	 
	text_stream << nowstr << "\r\n";	  
	file.flush();    
	file.close();
#endif

	
    data.resize(_udpSocket->pendingDatagramSize());
    _udpSocket->readDatagram(data.data(), data.size(), &cliAddr, &port);
    quint32 ipv4 = cliAddr.toIPv4Address();
    quint8 ip1,ip2,ip3,ip4;
    ip1 = (ipv4&0xff000000)>>24;
    ip2 = (ipv4&0xff0000)>>16;
    ip3 = (ipv4&0xff00)>>8;
    ip4 = ipv4&0xff;
    QString addr;
    addr.sprintf("%d.%d.%d.%d",ip1, ip2, ip3, ip4);
    //qDebug()<<"addr::"<<addr << ipv4 << ip1<<ip2<<ip3<<ip4<<"port:"<<port;
    printf("UDP================newData %d\n", port);
    newData(data, addr, port);
}

void RTLSClient::newTcpOrSerialData()
{
    QString addr;
    QByteArray data;
    quint32 ipv4;
    quint64 port;

    if (is_socket_connected)
    {
        data = _tcpSocket->readAll();
        ipv4 = _tcpSocket->peerAddress().toIPv4Address();
        port = _tcpSocket->peerPort();
        quint8 ip1,ip2,ip3,ip4;
        ip1 = (ipv4&0xff000000)>>24;
        ip2 = (ipv4&0xff0000)>>16;
        ip3 = (ipv4&0xff00)>>8;
        ip4 = ipv4&0xff;
        addr.sprintf("%d.%d.%d.%d",ip1, ip2, ip3, ip4);
        //qDebug()<<"tcp addr:"<<addr << "port"<< port;
    }
    else
    {
        data = _serial->readAll();
    }
    //qDebug() << data;
    printf("TCP================newData\n");
    newData(data, addr, port);
}

//处理udp/tcp/serial 数据
static int lastsec = 0;
void RTLSClient::newData(QByteArray &data, QString addr, qint64 port)
{
    QDateTime now = QDateTime::currentDateTime();
    QString nowstr = now.toString("T:hhmmsszzz:");
    int length = data.length();
    int offset = 0;
    QString statusMsg;
    int ping_flag = 0;
    int rsp_flag = 0;
    QByteArray tofReport;

    int aid, tid, range[16], lnum, seq, mask, heartRate, power, state;
    int move =0;
    unsigned int rangetime;
    char c, type;
    int tof_report_type = 0;
    int tof_report_len = 0;
    int ancid[8] = {0};
    int anctof[8]={0};
    int i = 0;
    int n = 0;

    while(length >= PING_REPORT_LEN) //we have received a range report from an anchor or a tag
    {
        while(length >= PING_REPORT_LEN)
        {
            QByteArray header = data.mid(offset, 2);

            //"ma" contains the bias corrected anchor to anchor ranges
            if(header.contains("da")) //loop here until we reach header ("ma")
            {
                break;
            }
            //"mc" contains the bias corrected ranges
            if(header.contains("dc")) //loop here until we reach header ("dc")
            {
                tof_report_type = TOF_REPORT_TYPE_DC;
                tof_report_len = TOF_REPORT_LEN_DC;
                break;
            }
            if(header.contains("nd")) //loop here until we reach header ("nd")
            {
                printf("nd\n\r");
                tof_report_type = TOF_REPORT_TYPE_ND;
                tof_report_len = TOF_REPORT_LEN_ND;
                break;
            }
            if(header.contains("dp"))
            {
                ping_flag = 1;
                break;
            }
            if(header.contains("{\""))
            {
                rsp_flag = 1;
                break;
            }

            offset += 2;
            length -= 2;
        }

        if(ping_flag)
        {
            if(length < PING_REPORT_LEN)
            {
                return;
            }

            tofReport = data.mid(offset, PING_REPORT_LEN);
            qDebug()<<tofReport;

            n = sscanf(tofReport.constData(),"dp %02x", &aid);

            if(!addr.isEmpty())
            {
                //qDebug()<<"recv " << aid <<"ping";
				emit updateAncAddr(aid, addr, port);
            }

            offset += PING_REPORT_LEN;
            length -= PING_REPORT_LEN;
            ping_flag = 0;
            continue;
        }
        if(rsp_flag)
        {
           int start;
           int end;
           start = offset;
           end = data.indexOf("}") + 1;

           tofReport = data.mid(start,end-start);
           qDebug()<<"recv rsp:"<<tofReport;
           handleMsg(tofReport);
           offset = end;
           length -= (end- start);
           rsp_flag = 0;
           continue;
        }


        if(length < tof_report_len)
        {
            return;
        }

        tofReport = data.mid(offset, tof_report_len);

        //e.g.
        //mr 0f 000005a4 000004c8 00000436 000003f9 0958 c0 40424042 a0:0
        //ma 07 00000000 0000085c 00000659 000006b7 095b 26 00024bed a0:0
        //mc 0f 00000663 000005a3 00000512 000004cb 095f c1 00024c24 a0:0
#if 0
        int aid, tid, range[4], lnum, seq, mask;
        int rangetime;
        char c, type;
        int n = sscanf(tofReport.constData(),"m%c %x %x %x %x %x %x %x %x %c%d:%d", &type, &mask, &range[0], &range[1], &range[2], &range[3], &lnum, &seq, &rangetime, &c, &tid, &aid);
#else
        //dc c889 000001a2 00000000 00000000 000012df 00000000 00000000 00000000 00001478 00000000 00000000 00000000 000017e2 00000000 00000000 00000b37 0000106b 018c 05 0000d306 a0:0
        //dc 0009 00001765 00000000 00000000 00001e83 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 7b9a 1d 033b1e6d a03:0

        if(tof_report_type == TOF_REPORT_TYPE_DC)
        {
            n = sscanf(tofReport.constData(),"d%c %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %c%02x:%02x %02x %02x %02x",
                       &type, &mask,
                       &range[0], &range[1], &range[2], &range[3],
                       &range[4], &range[5], &range[6], &range[7],
                       &range[8], &range[9], &range[10], &range[11],
                       &range[12], &range[13], &range[14], &range[15],
                       &lnum, &seq, &rangetime, &c, &tid, &aid, &heartRate, &power, &state);

        }
        else if(tof_report_type == TOF_REPORT_TYPE_ND)
        {
            //nd a 0000:0074 0001 0000:0125f 0000:00000 0000:00000 0000:00000 0000:00000 0000:00000 0000:00000 0000:00000 000a 01 0001e535 00 3c 03
            n = sscanf(tofReport.constData(),"%cd %c %x:%x %x %x:%x %x:%x %x:%x %x:%x %x:%x %x:%x %x:%x %x:%x %x %x %x %02x %02x %02x",
                       &type, &c, &aid, &tid,  &mask,
                       &ancid[0],&anctof[0],
                       &ancid[1],&anctof[1],
                       &ancid[2],&anctof[2],
                       &ancid[3],&anctof[3],
                       &ancid[4],&anctof[4],
                       &ancid[5],&anctof[5],
                       &ancid[6],&anctof[6],
                       &ancid[7],&anctof[7],
                       &lnum, &seq,&rangetime, &heartRate, &power, &state);
            //mask = 1;
            memset(range,0,sizeof(range));

            range[aid%16] = anctof[0];
            mask = 0x1<<aid;

            //for(i = 0;i<8;i++)
            //{
                //range[ancid[i]%16] = anctof[i];
                //if(anctof[i])
                //{
                    //mask |= 0x1<<(ancid[i]%16);
                //}
            //}

            {
            printf("seq  = %d,tid = %d aid = %d power =%d\n",seq,tid,aid,power);
            for(i =0;i<16;i++)
                printf("range[%d] = %d\n",i,range[i]);
            }

            if(_file)
            {
                QString s =  nowstr +  QString("nd:[%1-%2]:%3:%4:%5:%6:%7:%8:%9:%10 rang9:%11:%12:%13:%14:%15:%16:%17:%18\n").arg(aid).arg(tid).arg(range[0]).arg(range[1]).arg(range[2]).arg(range[3]).arg(range[4]).arg(range[5]).arg(range[6]).arg(range[7]).arg(range[8]).arg(range[9]).arg(range[10]).arg(range[11]).arg(range[12]).arg(range[13]).arg(range[14]).arg(range[15])+
                    QString("num %1 seq:%2 rt:%3 hr:%4 pw:%5 mask:%6\n").arg(lnum).arg(seq).arg(rangetime).arg(heartRate).arg(power).arg(mask)+
                    QString("raw ancid %1:%2:%3:%4:%5:%6:%7:%8\n").arg(ancid[0]).arg(ancid[1]).arg(ancid[2]).arg(ancid[3]).arg(ancid[4]).arg(ancid[5]).arg(ancid[6]).arg(ancid[7])+
                    QString("raw tof %1:%2:%3:%4:%5:%6:%7:%8\n").arg(anctof[0]).arg(anctof[1]).arg(anctof[2]).arg(anctof[3]).arg(anctof[4]).arg(anctof[5]).arg(anctof[6]).arg(anctof[7]);
                QTextStream ts( _file );
                ts << s;
            }

        }
#endif
        printf("seq  = %d,tid = %d aid = %d power =%d\n",seq,tid,aid,power);
        aid &= 0x0F;
        move = state&0x01;
        //qDebug()<<"herat;"<<heartRate<<"pw:"<<power<<"sta"<<state;
        if(rangetime == 0xffffffff)
        {
           // QMessageBox::critical(NULL, "critical", "Trail period is expired.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            qDebug()<<"0xffffffff";
          //  emit closeApp();
        }

        QString baseDataStr = QString(tofReport);
       // writeHandleDataLog(baseDataStr);
        //writeBaseDataLog(baseDataStr);
        qDebug()<<baseDataStr;

        if(!addr.isEmpty())
        {
            emit updateAncAddr(aid, addr, port);
        }

       // qDebug() << tofReport.constData();

        if (tid > MAX_TAG_NUM)
            return;
                  /*
        if(tid == 5)
            {
        printf("seq = %d clock=%d\n", seq,clock());
            }
            */

        //qDebug() << "anc"<< aid << "tag" << tid << "range(mm)" << range ;
        //qDebug() << "number"<< lnum << "seq" << seq << c << i ;

        //qDebug() << n << QString::fromLocal8Bit(tofReport, TOF_REPORT_LEN);

        offset += tof_report_len;
        length -= tof_report_len;

        if(n != TOF_REPORT_ARGS)
        {
            QString string1 = QString::fromLocal8Bit(tofReport, tof_report_len);
            //qDebug() << n << string1;
            continue;
        }

        //qDebug() << tofReport.constData();

        //notify the user if connected to a tag or an anchor
        if(_first)
        {
            if(c == 'a') //we are connected to an anchor id = i
            {
                //statusMsg = "Connected to Anchor ID" + QString(" %1.").arg(aid);

                //emit statusBarMessage(statusMsg);
            }
            else
            if(c == 't') //we are connected to a tag id = i
            {
                statusMsg = "Connected to Tag ID" + QString(" %1.").arg(tid);

                emit statusBarMessage(statusMsg);
            }
            else
            if(c == 'l') //we are connected to a listener id = i
            {
                statusMsg = "Connected to Listener ID" + QString(" %1.").arg(aid);

                emit statusBarMessage(statusMsg);
            }
            //log the anchor co-ordinates to the file
            for(int j = 0; j < MAX_NUM_ANCS; j++)
            {
                if(_file)
                {
                    QString s =  nowstr + QString("AP:%1:%2:%3:%4\n").arg(j).arg(_ancArray[j].x).arg(_ancArray[j].y).arg(_ancArray[j].z);
                    QTextStream ts( _file );
                    ts << s;
                }
            }
            _first = false;
        }
        printf("mask=%d\n",mask);

        if((type == 'c')||(type == 'n')) //if 'c' these reports relate to tag <-> anchor ranges
        {
            //check the mask and process the tag - anchor ranges
            for(int k=0; k<MAX_NUM_ANCS; k++)
            {
                if((0x1 << k) & mask) //we have a valid range
                {
                    processTagRangeReport(k, tid, range[k], lnum, seq, addr); //this is received when tags range to anchors
                }
            }

            processHeartRateReport(tid, heartRate, power, state);

           // trilaterateTag(tid, seq, mask);
        }
#if 0
        if(type == 'a') //if 'a' these reports relate to anchor <-> anchor ranges
        {
            int ai = 0, aj = 0;
            if(_useAutoPos) //if Anchor auto positioning is enabled then process Anchor-Anchor TWR data
            {
                for(int k=1; k<MAX_NUM_ANCS; k++)
                {
                    if((0x1 << k) & mask) //we have a valid range
                    {
                        switch(k)
                        {
                            case 1: //range A0 to A1
                                ai = 0;
                                aj = 1;
                                break;
                            case 2: //range A0 to A2
                                ai = 0;
                                aj = 2;
                                break;
                            case 3: //range A1 to A2
                                ai = 1;
                                aj = 2;
                                break;
                        }

                        processAnchRangeReport(ai, aj, range[k], lnum, seq); //this is received when achors range to each other
                    }
                }
            }
        }
#endif
    }

}


//calculate average (of last 50) excluding min and max
double RTLSClient::process_avg(int idx)
{
    double max, min, sum;
    int i;

    sum = max = min = _ancRangeArray[idx][0];

    for(i=0; i<ANC_RANGE_HIST; i++)
    {
        if (_ancRangeArray[idx][i] > max) max = _ancRangeArray[idx][i];
        if (_ancRangeArray[idx][i] < min) min = _ancRangeArray[idx][i];
        sum += _ancRangeArray[idx][i];
    }

    sum = sum - max - min;

    return sum / (ANC_RANGE_HIST - 2);
}

#if 0
void RTLSClient::processAnchRangeReport(int aid, int tid, int range, int lnum, int seq)
{
    QDateTime now = QDateTime::currentDateTime();
    QString nowstr = now.toString("T:hhmmsszzz:");
    //qDebug() << "a and t " << aid << tid << "correction = " << (_ancArray[aid].tagRangeCorection[tid] * 0.01);

    //log data to file
    if(_file)
    {
        QString s =  nowstr + QString("RA:%1:%2:%3:%4:%5:%6\n").arg(tid).arg(aid).arg(range).arg(0).arg(seq).arg(lnum);
        QTextStream ts( _file );
        ts << s;
    }

    //find the anchor in the list (A0 to A1, is the same as A1 to A0)
    _ancRangeValues[aid][tid] = ((double)range) / 1000;
    _ancRangeValues[tid][aid] = _ancRangeValues[aid][tid];

    if(seq != _ancRangeLastSeq) //new ranges - send signal to GUI
    {
        //first we store the 50 ranges and find and average range, then we calculate position
        if(_ancRangeCount < ANC_RANGE_HIST)
        {
            _ancRangeArray[0][_ancRangeCount] = _ancRangeValues[0][1]; //range A0-A1
            _ancRangeArray[1][_ancRangeCount] = _ancRangeValues[0][2]; //range A0-A2
            _ancRangeArray[2][_ancRangeCount] = _ancRangeValues[1][2]; //rnage A1-A2
            _ancRangeCount++;
        }
        else //calculate average and then location
        {
            _ancRangeCount = 0;

            if(_useAutoPos) //if Anchor auto positioning is enabled then process Anchor-Anchor TWR data
            {
                //we have 3 ranges (A0 to A1, A0 to A2 and A1 to A2)
                //calculate A0, A1 and A2 coordinates (x, y) based on A0 = 0,0 and assume A2 is to the right of A1

                int nNodes = 3;
                int viewNode = 0;
                mat twrdistance = zeros<mat>(nNodes,nNodes);
                mat transCoord = zeros<mat>(nNodes,nDim);
                mat estCoord = zeros<mat>(nNodes,nDim);

                //calculate average (exclude min, max)
                _ancRangeValuesAvg[0][1] = _ancRangeValuesAvg[1][0] = process_avg(0);
                _ancRangeValuesAvg[0][2] = _ancRangeValuesAvg[2][0] = process_avg(1);
                _ancRangeValuesAvg[1][2] = _ancRangeValuesAvg[2][1] = process_avg(2);

                for (int i = 0; i<nNodes; i++)                  // change the array to mat format
                {
                    for (int j = 0; j<nNodes; j++)
                    {
                       twrdistance(i,j) =  _ancRangeValuesAvg[i][j];
                    }
                }

                mds(twrdistance, nNodes, viewNode, &transCoord); // Using multi-dimension scaling to estimation the shape

                angleRotation(transCoord, nNodes, &estCoord); // estCoord is the coordinates with a1 on the x axis and a2 in the first quadrant

                //emit ancRanges(_ancRangeValues[0][1], _ancRangeValues[0][2], _ancRangeValues[1][2]); //send the update to graphic
                for(int i=0; i<(MAX_NUM_ANCS-1); i++) // Only update positions of A0, A1 and A2
                {
                    _ancArray[i].x = estCoord.at(i,0);
                    _ancArray[i].y = estCoord.at(i,1);

                    emit anchPos(i, _ancArray[i].x, _ancArray[i].y, _ancArray[i].z, false, true); // Update table entry
                }

                //if()
                //{
                   // emit centerOnAnchors(); - don't auto center ...
                //}
            }
        }
    }

    _ancRangeLastSeq = seq;
}

void RTLSClient::mds(mat twrdistance, int nNodes, int viewNode, mat* transCoord)
{
    mat         distSquared = zeros<mat>(nNodes,nNodes);
    mat         u = zeros<mat>(nNodes,nNodes);
    mat         v = zeros<mat>(nNodes,nNodes);
    colvec      s = zeros<vec>(nNodes);
    mat         estGeom = zeros<mat>(nNodes,nDim);

    distSquared = square(twrdistance);

    mat centeringOperator = eye<mat>(nNodes,nNodes)-(ones<mat>(nNodes,nNodes)/nNodes);

    mat centeredDistSquared = -0.5 * centeringOperator * distSquared * centeringOperator;

    svd(u,s,v,centeredDistSquared);

    for (int i = 0; i<nDim; i++)
    {
        estGeom.col(i) = u.col(i)*sqrt(s(i));
    }

    for (int i = 0; i<nNodes; i++)
    {
        transCoord->row(i) = estGeom.row(i)-estGeom.row(viewNode);
    }


}

void RTLSClient::angleRotation(mat transCoord, int nNodes, mat* estCoord)
{
    mat rotationMatrix = -ones<mat>(2,2);
    colvec transdistance = zeros(nNodes,1);
    mat Coord = zeros<mat>(nNodes,nDim);


    for (int i = 0; i<nNodes; i++)
    {
        transdistance.at(i) = sqrt(transCoord(i,0)*transCoord(i,0) + transCoord(i,1)*transCoord(i,1));

    }


    colvec currentAngle = acos(transCoord.col(0)/transdistance);

    for (int i = 0; i<nNodes; i++)
    {
        if (transCoord(i,1)<0)
        {
            currentAngle(i) = -currentAngle(i);
        }
    }

    double rotateAngle = currentAngle(1);

    rotationMatrix << cos(rotateAngle) << (-sin(rotateAngle)) << endr
                   << sin(rotateAngle) << cos(rotateAngle) <<endr;

    Coord = transCoord*rotationMatrix;

    if (Coord.at(2,1)<0)
    {
        Coord.at(2,1) = -Coord.at(2,1);
    }

    *estCoord = Coord;

}
#endif
void RTLSClient::processHeartRateReport(int tid, int heartRate, int power, int state)
{
    int idx = 0;
    //find the tag in the list
    for(idx=0; idx<_tagList.size(); idx++)
    {
        //find this tag in the list
        if(_tagList.at(idx).id == tid)
            break;
    }

    //if we don't have this tag in the list add it
    if(idx == _tagList.size())
    {
        initialiseTagList(tid);
    }
    tag_reports_t rp = _tagList.at(idx);
    //if(rp.heartRate == 0xff)
    {
        rp.heartRate = heartRate;
    }

    //if(rp.power == 0xff)
    {
        rp.power = power;
    }

    //if(rp.state == 0xff)
    {
        rp.state = state;
    }

    //update the list entry
    _tagList.replace(idx, rp);
}

void RTLSClient::processTagRangeReport(int aid, int tid, int range, int lnum, int seq, QString addr)
{
    int range_corrected;
    range_corrected = (0 == range)?0:(range + (_ancArray[aid].tagRangeCorection[tid] * 10)); //range correction is in cm (range is in mm)

    int idx = 0;
    //find the tag in the list
    for(idx=0; idx<_tagList.size(); idx++)
    {
        //find this tag in the list
        if(_tagList.at(idx).id == tid)
        {
			break;
		}
            
    }

    //if we don't have this tag in the list add it
    if(idx == _tagList.size())
    {
    	/*	新标签上线 发送消息给后台*/
		_tcpClient->sendTagStatus(1, 2, 3);
        initialiseTagList(tid);
    }
    tag_reports_t rp = _tagList.at(idx);

    int minus = (rp.rangeSeq > seq) ? (rp.rangeSeq - seq) : (seq-rp.rangeSeq);
    if(minus >= 2)//seq maybe incontinuity
    {
        memset(&rp.rangeValue[rp.rangeSeq][0], -1, MAX_NUM_ANCS*sizeof(int));
        rp.startMsec = 0;
        if(seq>0)
        {
            rp.rangeSeq = seq-1;
        }
        else
        {
            rp.rangeSeq = 0xff;
        }
    }
    printf("tid = %d range = %d seq=%d rp.rangeSeq =%d\n",tid,range,seq,rp.rangeSeq);
    if((seq < rp.rangeSeq) || ((seq == 0xff) && (rp.rangeSeq == 0)))//if seq has already process then return
    {
        rp.newestRecvMsec = clock();
        //update the list entry
        _tagList.replace(idx, rp);
        return;
    }

    rp.newestSeq = seq;

    if(-1 == rp.rangeSeq)
    {
        rp.rangeSeq = seq;
    }

    if(range_corrected != 0)//valid data
    {
        rp.rangeValue[seq][aid & 0xf] = range_corrected;
    }
    else
    {
        rp.rangeValue[seq][aid & 0xf] = 0;
    }

    rp.newestRecvMsec = clock();
                 /* if(tid == 5)
        printf("rp.rangeSeq = %d\n",rp.rangeSeq);*/
    //update the list entry
    _tagList.replace(idx, rp);
}

#if 0
void RTLSClient::processTagRangeReport(int aid, int tid, int range, int lnum, int seq)
{
    int range_corrected = range + (_ancArray[aid].tagRangeCorection[tid] * 10); //range correction is in cm (range is in mm)
    int idx = 0;

    QDateTime now = QDateTime::currentDateTime();
    QString nowstr = now.toString("T:hhmmsszzz:");
    //qDebug() << "a and t " << aid << tid << "correction = " << (_ancArray[aid].tagRangeCorection[tid] * 0.01);

    //log data to file
    if(_file)
    {
        QString s =  nowstr + QString("RR:%1:%2:%3:%4:%5:%6\n").arg(tid).arg(aid).arg(range).arg(range_corrected).arg(seq).arg(lnum);
        QTextStream ts( _file );
        ts << s;
    }

    //find the tag in the list
    for(idx=0; idx<_tagList.size(); idx++)
    {
        //find this tag in the list
        if(_tagList.at(idx).id == tid)
            break;
    }

    //if we don't have this tag in the list add it
    if(idx == _tagList.size())
    {
        initialiseTagList(tid);
    }

    tag_reports_t rp = _tagList.at(idx);

    emit tagRange(tid, aid, (range_corrected * 0.001)); //convert to meters

    if(rp.rangeSeq == seq) // we have already received range from one or more anchors with this seq
    {
        rp.rangeCount[seq & 0xFF]++;
        rp.rangeSeq = seq & 0xFF;
        rp.rangeValue[seq][aid & 0xf] = range_corrected;
        //printf("wwj:range_corrected = %d\r\n", range_corrected);
    }
    else //this is the 1st range from this range sequence
    {
        rp.rangeCount[seq & 0xFF] = 1;
        rp.rangeSeq = seq & 0xFF;
        rp.rangeValue[seq][aid & 0xf] = range_corrected;
        //printf("wwj:range_corrected = %d\r\n", range_corrected);
    }

    //update the list entry
    _tagList.replace(idx, rp);
}
#endif


/*	标签位置处理	*/
void RTLSClient::trilaterateTag(int tid, int seq, int mask)
{
    int idx = 0, count = 0;
    //bool trilaterate = false;
    vec3d report,lastloc;
    bool newposition = false;
    int nolocation = 0;
    int lastSeq = 0;
    QDateTime now = QDateTime::currentDateTime();
    QString nowstr = now.toString("T:hhmmsszzz:");
    static uint8_t s_cnt = 0;
    TAG tmpNode;
    AREA_TYPE areaType;
    int sysTime;
    int lastidx,move =0 ;
    double distance = 0;
    //static int lstEftSec = 0;


	printf("trilaterateTag\n");
    //find the tag in the list
    for(idx=0; idx<_tagList.size(); idx++)
    {
        //find this tag in the list
        if(_tagList.at(idx).id == tid)
            break;
    }

    tag_reports_t rp = _tagList.at(idx);

    lastSeq = (seq) & 0xFF ;
    count = rp.rangeCount[lastSeq];
    if(rp.state != 0xff)
    {
        move = rp.state&0x01;
    }
    lastidx = rp.arr_idx;
    if(lastidx ==0)
    {
        if(rp.filterReady ==0)
        {
            move = 1;
        }
        else
        {
            lastidx = HIS_LENGTH-1;
        }
    }
    else
    {
        lastidx-=1;
    }
    lastloc.x = rp.x_arr[lastidx];
    lastloc.y = rp.y_arr[lastidx];
    lastloc.z = rp.z_arr[lastidx];

    if(tid == 5 )
    {
        printf("filterReady  =%d,seq = %d  rp.arr_idx = %d rp.state =%d  move=%d count=%d\r\n",rp.filterReady, seq,rp.arr_idx,rp.state,move,rp.count);
        //printf("x= %0.2f,y=%0.2f,z=%0.2f\r\n",lastloc.x ,lastloc.y ,lastloc.z );
        //printf("rp x= %0.2f,y=%0.2f,z=%0.2f\r\n",rp.fx,rp.fy,rp.fz);

    }

    int tm;
    if(lastSeq >= 230)
    {
        tm = 1;
    }

   sysTime = clock()/CLOCKS_PER_SEC;
   int ret = -1;

    //we got next range seq. lets try and trilaterate the previous
    //if(count >= 3)
    {
        //qDebug() << "try to get location" ;

        if(1 == g_vec)//vec1
        {
             ret = calcVec1Loc(&report, &rp.rangeValue[lastSeq][0]);
        }
        else//vec3
        {
            //if((tid == 7) &&(rp.state != 0xff))
            //if(tid == 7)
            if(rp.state != 0xff)
            ret = calculateTagLocation(&report, count, mask,&rp.rangeValue[lastSeq][0]);
        }

        if(ret != -1)
        {
            qDebug()<<"X:"<<report.x<<"Y:"<<report.y<<"Z:"<<report.z;//原始坐标

            if((sysTime - rp.lstEftSec) >= 5)
            {
                rp.xKlman->clear();
                rp.yKlman->clear();
            }

            rp.lstEftSec = sysTime;

            if(1 == g_klmanEnable)//卡尔曼滤波算法
            {
                report.x = rp.xKlman->update(report.x);
                report.y = rp.yKlman->update(report.y);
            }

            if(1 == g_locCorrectEnable)//漂移纠正算法
            {
                //记录TagID加入告警判断
                 getTagLastInfo(tid,&tmpNode);
                 tmpNode.current_node.x = report.x;
                 tmpNode.current_node.y = report.y;
                 tmpNode.current_node.z = report.z;
                 //校正漂移坐标
                 areaType = confirmNodeArea(&tmpNode);
                 qDebug()<<"amend areatype :"<<areaType;
                 tmpNode.last_area_type = areaType;
                 if(areaType != AREA_OUT_RANGE)
                 {
                    tmpNode.last_effect_area_type = areaType;
                 }
                 //修正后的坐标
                report.x = tmpNode.current_node.x;
                report.y = tmpNode.current_node.y;
                report.z = tmpNode.current_node.z;
            }
            else
            {
                tmpNode.current_node.x = report.x;
                tmpNode.current_node.y = report.y;
                tmpNode.current_node.z = report.z;
                areaType = findNodeArea(&tmpNode);
                tmpNode.last_area_type = areaType;//不能去掉,否则动态设置会出问题。
                if(areaType != AREA_OUT_RANGE)
                {
                   tmpNode.last_effect_area_type = areaType;
                }
            }

            qDebug()<<"X:"<<report.x<<"Y:"<<report.y<<"Z:"<<report.z;

            #if 0
            if((move == 0) &&( tid == 7)&&(rp.filterReady >0))
            {
                distance = sqrt((rp.fx-report.x)*(rp.fx-report.x)+ (rp.fy-report.y)*(rp.fy-report.y));
                printf("distance =%0.2f\r\n",distance);
            }
            #endif

            QString areaCode;
            getAreaCode(areaType,areaCode);
            if((((move == 0)&&(rp.filterReady > 0))||(_usingFilter != 0))&&(ret != TRIL_1SPHERES))
            {
                qDebug()<<"fx:"<<rp.fx<<"fy:"<<rp.fy<<"fz:"<<rp.fz;

				/*	位置边界处理	*/
				printf("location1 fx = %f, fy = %f\n", rp.fx, rp.fy);
				tagPositionCorrect(&rp.fx, &rp.fy, 0, 0);
				printf("location2 fx = %f, fy = %f\n", rp.fx, rp.fy);
				
                _tcpClient->sendPositon(tid,rp.fx,rp.fy,rp.fz,areaCode);	//向后台发送位置信息
                _tcpClientOutServer ->sendPositonOutServer(tid,rp.fx,rp.fy,rp.fz,areaCode);	//向第三方后台发送消息
            }
            else
            {
                _tcpClient->sendPositon(tid,report.x,report.y,report.z,areaCode);
                _tcpClientOutServer ->sendPositonOutServer(tid,report.x,report.y,report.z,areaCode);

            }
           // _HttpClient->SendTagPosition(tid,report.x,report.y,report.z);

            //记录收到数据时间
            setTagLastInfo(tid, tmpNode);
            setTagLoctTime(tid, sysTime);

            QString postr;
            postr.sprintf("TAG:%02d 所在区域:%d",tid, (int)areaType);
            QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
            QString timeStr = time.toString("[MMdd-hh:mm:ss]"); //设置显示格式
            QString dspStr = timeStr + postr + QString("\n");
            emit dsptcpLog(dspStr);
           //_WebSocketServer->m_uwb_sql->SavePrisonerPosition(tid, report.x, report.y, report.z);
           // _WebSocketServer->SendTagPosition(tid, report.x, report.y, report.z);

            newposition = true;
            rp.numberOfLEs++;

            _tagList.replace(idx, rp);

            //log data to file
            if(_file)
            {
                QString s = nowstr + QString("LE:%1:%2:%3:[%4,%5,%6]:").arg(tid).arg(rp.numberOfLEs).arg(lastSeq).arg(report.x).arg(report.y).arg(report.z) +
                        QString("%1:%2:%3:%4\n").arg(rp.rangeValue[lastSeq][0]).arg(rp.rangeValue[lastSeq][1]).arg(rp.rangeValue[lastSeq][2]).arg(rp.rangeValue[lastSeq][3]);
                QTextStream ts( _file );
                ts << s;
            }

            //qDebug() << "emit tagPos" << rp.numberOfLEs;
            printf("report x=%0.2f y=%0.2f z=%0.2f\r\n",report.x, report.y, report.z);
            if(_usingFilter == 0)
            {
                if(((move == 0) &&(rp.filterReady >0))&&(ret != TRIL_1SPHERES))
                {
                    printf("rp x=%0.2f y=%0.2f z=%0.2f\r\n",rp.fx, rp.fy, rp.fz);
                    emit tagPos(tid, rp.fx, rp.fy, rp.fz); //send the update to graphic
                }
                else
                {
                    emit tagPos(tid, report.x, report.y, report.z);
                }
            }
            if(nolocation)
            {
                emit statusBarMessage("");
            }

            nolocation = 0;
        }
        else //no solution
        {
            qDebug()<<"no solution";
            nolocation++;

            //log data to file
            if(_file)
            {
                QString s = nowstr + QString("NL:%1:%2:%3:[nan,nan,nan]:").arg(tid).arg(rp.numberOfLEs).arg(lastSeq) +
                        QString("%1:%2:%3:%4\n").arg(rp.rangeValue[lastSeq][0]).arg(rp.rangeValue[lastSeq][1]).arg(rp.rangeValue[lastSeq][2]).arg(rp.rangeValue[lastSeq][3]);
                QTextStream ts( _file );
                ts << s;
            }

            if( nolocation >= 5)
            {
                emit statusBarMessage("No location solution.");
            }
        }

    }
    //clear the count
    //rp.rangeCount[lastSeq] = 0;
    //update statistics if new position has been calculated
    if(newposition)
    {
        updateTagStatistics(idx, report.x, report.y, report.z);

        if((_usingFilter != 0)&&(ret != TRIL_1SPHERES))
        {
            emit tagPos(tid, rp.fx, rp.fy, rp.fz); //send the update to graphic
        }
    }

    //qDebug() << "newposition" << newposition << idx << lastSeq << seq;
}
#if 0
int RTLSClient::getareaid(double x,double y,int labelid)
{
    int areaid=0;
    int cellid = 0;
    QString id;

    _configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    _configfile->beginGroup("labelarea");
    id = QString::number(labelid,16);
    cellid= _configfile->value(id).toInt()-2;

    if(x>= allx[0] && x<= allx[1] && y>= ally[0] && y<= ally[1])
    {
        //走廊区域
        if(x>= lobbyx[0] && x<= lobbyx[1] && y>= lobbyy[0] && y<= lobbyy[1])
        {
            if(x>=doorx[cellid]&&x<=doorx[cellid+1]&&y>=doory[cellid]&&y<=doory[cellid+1])
            {
                areaid = 2;
            }
            else
            {
                areaid = 3;
            }

        }
        else
        {
            if(x>=cellx[cellid]&&x<=cellx[cellid+1]&&y>=celly[cellid]&&y<=celly[cellid+1])
            {
                if((x>=toiletx[cellid]&&x<=toiletx[cellid+1]&&y>=toiletx[cellid]&&y<=toiletx[cellid+1]))
                {
                    areaid = 1;
                }
                else
                {
                    areaid = 0;
                }
            }
            else
            {
                areaid = 4;
            }
        }
    }
    else
    {
        areaid =5;
    }
    return areaid;
}
#endif

#define  M    4  // 控制点（基站）数


bool compareAncRange(const ANC_RANGE &ar1, const ANC_RANGE &ar2)
{
    if(ar1.range < ar2.range)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void  sortAncRange(QARList* arList)
{
    qSort(arList->begin(), arList->end(), compareAncRange);
}




int RTLSClient::calculateTagLocation(vec3d *report, int count, int mask,int *ranges)
{
    QDateTime now = QDateTime::currentDateTime();
    QString nowstr = now.toString("T:hhmmsszzz:");
    //读取配置文件
    int i=0, keep2id1=0,keep2id2 =0,keep0id = -1;
    double keep2ranges1=9999.0,keep2ranges2 =9999.0,keep0ranges=9999.0;
    int baseid[10] ={0};
    memset(baseid, -1, 10);

    int dimension;
    int Base3 =0;
    double x1,x2,y1,y2;
    int k=0;
    int dis1 =0,dis2=0;
    QString id,id2;
    int distance;

    QStringList list;

    //新算法变量初始化
    double CtrPoints[M*3] ={0};
    double d[M] ={0};
    double P[3] ={0};

    _configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    _configfile->beginGroup("distance");
    distance = _configfile->value("distance").toInt();
    _configfile->endGroup();
    if(_file)
    {
        QString s =  nowstr + QString("distance:%1\n").arg(distance);
        QTextStream ts( _file );
        ts << s;
    }
    _configfile->beginGroup("dimension");
    printf("******start********\n");
    for(i=0;i<16;i++)
    {
        /*if(((0x1 << i) & mask) == 0)
        {
            ranges[i] = 0;
            continue;
        }*/
        if(ranges[i] <= 0 )
        {
            ranges[i] = 0;
            continue;
        }
        //qDebug("ranges[%d=%d\n",i,ranges[i]);
        printf("ranges[%d]=%d\n",i,ranges[i]);
        id = QString::number(i,10);
        dimension = _configfile->value(id).toInt();
        //printf("dimension=%d  ranges[i]=%d\n",dimension,ranges[i]);
        //二维和三维
        if(dimension >0)
        {    //printf("keep2ranges=%0.2f\n",keep2ranges);
            k++;
            if(k == 1)
            {
                keep2ranges1 = (double)ranges[i]/1000.0;
                keep2id1 = i;
            }
            else
            {
                if(keep2ranges1 >((double)ranges[i]/1000.0))
                {
                    keep2ranges2 = keep2ranges1;
                    keep2id2 = keep2id1;
                    keep2ranges1 = (double)ranges[i]/1000.0;
                    keep2id1 = i;
                }
                else
                {
                    if(keep2ranges2 > ((double)ranges[i]/1000.0))
                    {
                        keep2ranges2 = (double)ranges[i]/1000.0;
                        keep2id2 = i;
                    }
                }
            }
        }
        else
        {
            if(keep0ranges >((double)ranges[i]/1000.0))
            {
                keep0ranges =(double)ranges[i]/1000.0;
                keep0id = i;
            }
        }

    }
    //qDebug("keep2id1=%d,keep2id2 =%d,keep0id=%d\n",keep2id1,keep2id2,keep0id);
    if(-1 != keep0id)
    {
        if(ranges[keep0id] <= distance)
        {
            report->x = _ancArray[keep0id].x;
            report->y = _ancArray[keep0id].y;
            report->z = _ancArray[keep0id].z;
            //report->x = 6.320;
            //report->y = 4.980;
            //report->z = 3.000;
            return TRIL_1SPHERES;
        }
        else
        {
            return -1;
        }
    }


#if 0
    //判断前两个最近距离基站的邻居关系
    dis1 = ranges[keep2id1];
     id = QString::number(keep2id1,10);
     _configfile->beginGroup("neighbour");
    id2 = _configfile->value(id).toString();
    list =id2.split(",");
    for(i=0;i<list.size();i++)
    {
        dis1 += ranges[list[i].toInt()];
        if(ranges[list[i].toInt()] == 0)
        {
            printf("return");
            return -1;
        }
    }

    dis2 = ranges[keep2id2];
    id = QString::number(keep2id2,10);
    id2 = _configfile->value(id).toString();
    list =id2.split(",");
    for(i=0;i<list.size();i++)
    {
       dis2 += ranges[list[i].toInt()];
       if(ranges[list[i].toInt()] == 0)
       {
          dis2 = 9999;
          break;
       }
    }

    if(dis1 > dis2)
    {
        keep2id1 = keep2id2;
    }
#endif
    _configfile->endGroup();
    baseid[0] = keep2id1;
    //qDebug("baseid=%d\n",baseid[0]);
    printf("baseid=%d\n",baseid[0]);
    id = QString::number(keep2id1,10);
    _configfile->beginGroup("neighbour");
    //_configfile->setValue(id,"34,35");
    id2 = _configfile->value(id).toString();
    _configfile->endGroup();

    if(id2 == "")
    {
        return -1;
    }

    list =id2.split(",");

    //anc-rang 链表 排序
    QARList arList;
    ANC_RANGE tmpAr;
    tmpAr.aid = baseid[0];
    tmpAr.range = ranges[baseid[0]];
    arList<<tmpAr;
    for(i=0;i<list.size();i++)
    {
        baseid[i+1] = list[i].toInt();
        tmpAr.aid = baseid[i+1];
        if(ranges[baseid[i+1]] == 0)
        {
            tmpAr.range = 0xffff;//升序排列过滤 range 0

            Base3++;
            ranges[baseid[i+1]] =0;
            qDebug()<<"list.size:"<<list.size();
            if(Base3 >(list.size()-2))
                return -1;
        }
        else
        {
            tmpAr.range = ranges[baseid[i+1]];
        }

        arList<<tmpAr;
    }

    //按照aid对应的rang升序排列，range为0排后面
    sortAncRange(&arList);
    i = 0;
    QARList::Iterator iter;
    for(iter=arList.begin();iter!=arList.end();iter++)
    {
        baseid[i] = iter->aid;
        i++;
    }

#if 1
    //新算法基站位置赋值
    for(i=0;i<M;i++)
    {
        printf("ranges[%d]=%d,baseid = %d,\r\n",i,ranges[baseid[i]] ,baseid[i]);
        if(ranges[baseid[i]] == 0)
        {
            if((i+1) == M)
            {
                d[i] = (double) ranges[baseid[i-1]] / 1000.0;
                CtrPoints[i*3] = _ancArray[baseid[i-1]].x;
                CtrPoints[i*3+1] = _ancArray[baseid[i-1]].y;
                CtrPoints[i*3+2] = _ancArray[baseid[i-1]].z;
            }
            else
            {
                d[i] = (double) ranges[baseid[i+1]] / 1000.0;
                CtrPoints[i*3] = _ancArray[baseid[i+1]].x;
                CtrPoints[i*3+1] = _ancArray[baseid[i+1]].y;
                CtrPoints[i*3+2] = _ancArray[baseid[i+1]].z;
            }
        }
        else
        {
            d[i] = (double) ranges[baseid[i]] / 1000.0;
            CtrPoints[i*3] = _ancArray[baseid[i]].x;
            CtrPoints[i*3+1] = _ancArray[baseid[i]].y;
            CtrPoints[i*3+2] = _ancArray[baseid[i]].z;
        }
    }
#endif

    //qDebug()<<d[0]<<d[1]<<d[2]<<d[3]<<CtrPoints[0]<<CtrPoints[1]<<CtrPoints[2]<<CtrPoints[3]
     //       <<CtrPoints[4]<<CtrPoints[5]<<CtrPoints[6]<<CtrPoints[7]<<CtrPoints[8]<<CtrPoints[9]
      //      <<CtrPoints[10]<<CtrPoints[11];


    location_4P( CtrPoints,d, P);
    printf("x=%0.2f y=%0.2f z=%0.2f\r\n",P[0],P[1],P[2]);
    printf("******end********\n");

    //判断是否在区域内
#if 1
    _configfile->beginGroup("area");
    id = QString::number(baseid[0],10);
    id2 = _configfile->value(id).toString();
    list =id2.split(",");
    //qDebug() << baseid[0] << id2 << list.size();
    x1 = list[0].toDouble();
    x2 = list[1].toDouble();
    y1 = list[2].toDouble();
    y2 = list[3].toDouble();

    _configfile->endGroup();
#endif
    if((P[0] >= x1)&&(P[0] <= x2)&&(P[1] >= y1) &&(P[1] <=y2))
    {
        report->x = P[0];
        report->y = P[1];
        report->z = P[2];
    }
    else
    {
        //printf("keep0id = %d,%0.2f\n",keep0id,_ancArray[keep0id].x);
        report->x = _ancArray[keep0id].x;
        report->y = _ancArray[keep0id].y;
        report->z = _ancArray[keep0id].z;
    }

    delete _configfile;

    return TRIL_3SPHERES;

}

void RTLSClient::test()
{
    int range[16] = {-1, -1, -1, -1,
                     5452, -1, -1, -1,
                     255, 114, -1, 1201,
                     754, -1, 1786, 400
                    };

    vec3d report;

    calcVec1Loc(&report, &range[0]);

}

int RTLSClient::calcVec1Loc(vec3d *report, int *ranges)
{
    double anc[4];
    double dst[2];
    double pos[2];
    int baseid0 = -1;
    int baseid1 = -1;
    int efcCount = 0;
    int tmpid;

    int i = 0, j = 0;

    for(i=0;i<16;i++)
    {
        if((ranges[i] == -1) || (ranges[i] == 0))
        {
            ranges[i] = 0;
            continue;
        }
        qDebug("range[%d]:, %d", i, ranges[i]);

        if((-1 == baseid0) && (-1 == baseid1))//basid0 baseid1 均为空，优先填充baseid0
        {
            baseid0 = i;
            efcCount++;
            continue;
        }
        else if((-1 != baseid0) && (-1 == baseid1))//baseid1 为空
        {
            baseid1 = i;
            efcCount++;
            continue;
        }
        else //baseid0 baseid1 均不为空
        {
            tmpid = baseid0;
            if(ranges[i] < ranges[baseid0])
            {
                baseid0 = i;
                if(ranges[tmpid] < ranges[baseid1])
                {
                    baseid1 = tmpid;
                }
            }
            else
            {
                if(ranges[i] < ranges[baseid1])
                {
                    baseid1 = i;
                }
            }
        }
    }

    if(efcCount < 2)
    {
        qDebug()<<"effect range < 2 ";
        return -1;
    }

    if(ranges[baseid0] > ranges[baseid1])// be sure of  range[base0] < range[baseid1]
    {
        tmpid = baseid0;
        baseid0 = baseid1;
        baseid1 = tmpid;
    }

    qDebug()<<"base0"<<baseid0<<"base1"<<baseid1;

    double dstAB = sqrt(pow(_ancArray[baseid0].x - _ancArray[baseid1].x, 2) + pow(_ancArray[baseid0].y - _ancArray[baseid1].y, 2));

    anc[0] = _ancArray[baseid0].x;
    anc[1] = _ancArray[baseid0].y;
    anc[2] = _ancArray[baseid1].x;
    anc[3] = _ancArray[baseid1].y;
    dst[0] = (double)ranges[baseid0]/1000.0;
    dst[1] = (double)ranges[baseid1]/1000.0;

    if(dst[1] > dstAB)
    {
        dst[0] = 0 - dst[0];//反方向
    }

    qDebug("anc[0]:%f, anc[1]:%f, anc[2]:%f, anc[3]:%f, dst0:%f, dst1:%f", anc[0], anc[1], anc[2], anc[3],dst[0], dst[1]);

    location_2P(anc, dst, pos);

    report->x = pos[0];
    report->y = pos[1];
    report->z = _ancArray[baseid0].z;

    return 0;
}












#if 0
int RTLSClient::calculateTagLocation(vec3d *report, int count, int *ranges)
{
    int result = 0;
    vec3d anchorArray[4];


    anchorArray[0].x = _ancArray[0].x;
    anchorArray[0].y = _ancArray[0].y;
    anchorArray[0].z = _ancArray[0].z;

    anchorArray[1].x = _ancArray[1].x;
    anchorArray[1].y = _ancArray[1].y;
    anchorArray[1].z = _ancArray[1].z;

    anchorArray[2].x = _ancArray[2].x;
    anchorArray[2].y = _ancArray[2].y;
    anchorArray[2].z = _ancArray[2].z;

    anchorArray[3].x = _ancArray[3].x;
    anchorArray[3].y = _ancArray[3].y;
    anchorArray[3].z = _ancArray[3].z;
    printf("%d 12here\r\n",_configfile);

    result = GetLocation(report, ((count==4) ? 1 : 0), &anchorArray[0], ranges);

    return result;
}
#endif
void RTLSClient::setGWReady(bool set)
{
    _graphicsWidgetReady = set;
}

void r95Sort (double s[], int l, int r)
{
    int i,j;
    double x;
    if(l<r)
    {
        i = l;
        j = r;
        x = s[i];
        while(i<j)
        {
            while (i<j&&s[j]>x) j--;
            if (i<j) s[i++] = s[j];
            while (i<j&&s[i]<x) i++;
            if (i < j) s[j--] = s[i];
        }
        s[i] = x;
        r95Sort(s, l, i-1);
        r95Sort(s, i+1, r);
    }

}

void RTLSClient::connectionStateChanged(SerialConnection::ConnectionState state)
{
    qDebug() << "RTLSClient::connectionStateChanged " << state;

    if(state == SerialConnection::Disconnected) //disconnect from Serial Port
    {
        if(_serial != NULL)
        {
            disconnect(_serial, SIGNAL(readyRead()), this, SLOT(newTcpOrSerialData()));
            _serial = NULL;
        }
        if(_file)
        {
            _file->close(); //close the Log file
        }
    }

}


void RTLSClient::addMissingAnchors(void)
{
    int i;

    //check how many anchors were added and add placeholders for any missing ones
    for(i=0; i<MAX_NUM_ANCS; i++)
    {
        if(_ancArray[i].id == 0xff)
        {
            _ancArray[i].id = i;
            emit anchPos(i, _ancArray[i].x, _ancArray[i].y, _ancArray[i].z, false, false);
        }
    }

    emit centerOnAnchors();
}

void RTLSClient::loadConfigFile(QString filename)
{
    QFile file(filename);

    double x[MAX_NUM_ANCS] = {0.0};
    double y[MAX_NUM_ANCS] = {0.0};

    _ancMaxShowCount = 0;

    for(int i=0; i<MAX_NUM_ANCS; i++)
    {
        _ancArray[i].id = 0xff;
        _ancArray[i].label = "";
        _ancArray[i].x = x[i];  //default x
        _ancArray[i].y = y[i];  //default y
        _ancArray[i].z = 3.00;  //default z

        for(int j = 0; j<MAX_NUM_TAGS; j++)
        {
            _ancArray[i].tagRangeCorection[j] =  0;
        }
    }

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg(filename).arg(file.errorString())));
        addMissingAnchors();
        return;
    }

    QDomDocument doc;
    QString error;
    int errorLine;
    int errorColumn;

    if(doc.setContent(&file, false, &error, &errorLine, &errorColumn))
    {
     //   qDebug() << "file error !!!" << error << errorLine << errorColumn;
    }

    QDomElement config = doc.documentElement();

    if( config.tagName() == "config" )
    {
        QDomNode n = config.firstChild();
        while( !n.isNull() )
        {
            QDomElement e = n.toElement();
            if( !e.isNull() )
            {
                if( e.tagName() == "anc" )
                {
                    bool ok;
                    int id = (e.attribute( "ID", "" )).toInt(&ok);

                    id &= 0x0F;

                    if(ok)
                    {
                        _ancArray[id].id = id & 0xf;
                        _ancArray[id].label = (e.attribute( "label", "" ));
                        _ancArray[id].x = (e.attribute("x", "0.0")).toDouble(&ok);
                        _ancArray[id].y = (e.attribute("y", "0.0")).toDouble(&ok);
                        _ancArray[id].z = (e.attribute("z", "0.0")).toDouble(&ok);

                        //tag distance correction (in cm)
                        _ancArray[id].tagRangeCorection[0] = (e.attribute("t0", "0")).toDouble(&ok);
                        _ancArray[id].tagRangeCorection[1] = (e.attribute("t1", "0")).toDouble(&ok);
                        _ancArray[id].tagRangeCorection[2] = (e.attribute("t2", "0")).toDouble(&ok);
                        _ancArray[id].tagRangeCorection[3] = (e.attribute("t3", "0")).toDouble(&ok);
                        _ancArray[id].tagRangeCorection[4] = (e.attribute("t4", "0")).toDouble(&ok);
                        _ancArray[id].tagRangeCorection[5] = (e.attribute("t5", "0")).toDouble(&ok);
                        _ancArray[id].tagRangeCorection[6] = (e.attribute("t6", "0")).toDouble(&ok);
                        _ancArray[id].tagRangeCorection[7] = (e.attribute("t7", "0")).toDouble(&ok);
                        _ancArray[id].show = (e.attribute("show","0")).toInt();
                        if(true == _ancArray[id].show)
                        {
                        	printf("++++++++++++++++++++++%d\n", _ancMaxShowCount);
                            _ancMaxShowCount++;
                        }

                       emit anchPos(id, _ancArray[id].x, _ancArray[id].y, _ancArray[id].z, _ancArray[id].show, false);

                    }
                }
            }

            n = n.nextSibling();
        }

    }

    file.close();

    addMissingAnchors();
}

QDomElement AnchorToNode( QDomDocument &d, anc_struct_t * anc )
{
    QDomElement cn = d.createElement( "anc" );
    cn.setAttribute("ID", QString::number(anc->id));
    cn.setAttribute("label", anc->label);
    cn.setAttribute("x", anc->x);
    cn.setAttribute("y", anc->y);
    cn.setAttribute("z", anc->z);
    cn.setAttribute("t0", anc->tagRangeCorection[0]);
    cn.setAttribute("t1", anc->tagRangeCorection[1]);
    cn.setAttribute("t2", anc->tagRangeCorection[2]);
    cn.setAttribute("t3", anc->tagRangeCorection[3]);
    cn.setAttribute("t4", anc->tagRangeCorection[4]);
    cn.setAttribute("t5", anc->tagRangeCorection[5]);
    cn.setAttribute("t6", anc->tagRangeCorection[6]);
    cn.setAttribute("t7", anc->tagRangeCorection[7]);
    cn.setAttribute("show", anc->show);

    return cn;
}

void RTLSClient::saveConfigFile(QString filename)
{
    QFile file( filename );
    int i = 0;

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg(filename).arg(file.errorString())));
        return;
    }

    QDomDocument doc;

    // Adding tag config root
    QDomElement config = doc.createElement("config");
    doc.appendChild(config);

    while (i < MAX_NUM_ANCS)
    {
        config.appendChild( AnchorToNode(doc, &_ancArray[i]) );

        i++;
    }

    QTextStream ts( &file );
    ts << doc.toString();

    file.close();

    if(_file)
    {
        _file->flush();
    }

    qDebug() << doc.toString();
}


void RTLSClient::updateAnchorXYZ(int id, int x, double value)
{
    QDateTime now = QDateTime::currentDateTime();
    QString nowstr = now.toString("T:hhmmsszzz:");

    if(x == 1)
    {
        _ancArray[id].x = value;
    }
    else if (x == 2)
    {
        _ancArray[id].y = value;
    }
    else if (x == 3)
    {
        _ancArray[id].z = value;
    }

    if(_file)
    {
        QString s =  nowstr + QString("AP:%1:%2:%3:%4\n").arg(id).arg(_ancArray[id].x).arg(_ancArray[id].y).arg(_ancArray[id].z);
        QTextStream ts( _file );
        ts << s;
    }
}


void RTLSClient::updateTagCorrection(int aid, int tid, int value)
{
    tid &= 0xf;

    _ancArray[aid].tagRangeCorection[tid] = value;

}

void RTLSClient::updateAnchorShow(int id, bool show)
{
    if(_ancArray[id].show == show)
        return;

    if(true == show)
    {
        _ancMaxShowCount++;
    }
    else
    {
        _ancMaxShowCount--;
    }


    _ancArray[id].show = show;
    qDebug()<<"id:"<<id << "show"<<show;
}

int* RTLSClient::getTagCorrections(int anchID)
{
    return &_ancArray[anchID].tagRangeCorection[0];
}


void RTLSClient::periodCalcProcess()
{
    _periodCalcTimer->start();

    int i = 0, j = 0;
    int idx = 0, count;
    int range;
    int msec;

    msec = clock();
    tag_reports_t rp;

    for(idx=0; idx<_tagList.size(); idx++)
    {
        rp = _tagList.at(idx);
        count = 0;
        /*if((msec - rp.newestRecvMsec) >= 3000)
        {
            continue;
        }*/

        for(i=0; i<MAX_NUM_ANCS; i++)
        {
            if(true == _ancArray[i].show)
            {
                printf("rp.rangeSeq=%d count = %d range=%d\n",rp.rangeSeq,count,rp.rangeValue[rp.rangeSeq][i]);
                if(rp.rangeValue[rp.rangeSeq][i] > 0)
                {
                    count++;
                }
            }
        }

        QString dcStr;
        dcStr += QString::asprintf("%02d ", rp.id);
        //recv over or timeout
        if(rp.id == 7)
        printf("count = %d _ancMaxShowCount =%d msec =%d rp.startMsec=%d\n",count,_ancMaxShowCount,msec,rp.startMsec);
        if((count > 0) || ((msec - rp.startMsec) >= 10000))
        {

            for(i=0; i<MAX_NUM_ANCS; i++)
            {
                if(true == _ancArray[i].show)
                {
                   range = rp.rangeValue[rp.rangeSeq][i];
                   int range_corrected = range + (_ancArray[i].tagRangeCorection[idx] * 10); //range correction is in cm (range is in mm)
                   emit tagRange(rp.id, _ancArray[i].id, (range_corrected * 0.001)); //convert to meters
                }

                if(rp.rangeValue[rp.rangeSeq][i] > 0)
                dcStr += QString::asprintf("%d:%08x ", i, rp.rangeValue[rp.rangeSeq][i]);
            }

            QString seqStr = QString::number(rp.rangeSeq, 16);
            QString newseqStr = QString::number(rp.newestSeq, 16);
            QString tmpStr = dcStr + QString::asprintf("new:%02x, now:%02x", rp.newestSeq, rp.rangeSeq);
            //writeHandleDataLog(tmpStr);
            qDebug()<<tmpStr;

            //calc tag location
            printf("rp.id = %d\n",rp.id);
            trilaterateTag(rp.id, rp.rangeSeq, 0);
            rp = _tagList.at(idx);//reload rp;

            //if(rp.id == 5)
            {
                printf("receive rp.rangeSeq = %d clock=%d\n",rp.rangeSeq,clock());
                if(clock() -rp.msec >_min*60000)
                {
                    rp.packetlossrate =int(100*double(_count -rp.count)/double(_count));

                    printf("here rp.msec= %d,count =%d packetlossrate =%d\n",rp.msec,rp.count,rp.packetlossrate);
                    if(rp.packetlossrate < 0) rp.packetlossrate=0;
                    rp.msec =clock();
                    rp.count = 0;
                }



            }

            if(rp.power != 0xff)
            {
                _tcpClient->sendTagHeartRate(rp.id, rp.heartRate, rp.power, rp.state);
                emit tagHeartRate(rp.id, rp.heartRate, rp.power, rp.packetlossrate );
            }

            //reset info of tag;
            memset(&rp.rangeValue[rp.rangeSeq][0], -1, MAX_NUM_ANCS*sizeof(int));
           /* rp.heartRate = 0xff;
            rp.power= 0xff;//rp.state =0xff;
            rp.state = 0xff;*/

            bool correctSeqFlag = false;//收包过程中有数据包卡住的情况导致序列号异常，校正回来。
            printf("rp.newestSeq=%d \r\n", rp.newestSeq);
            if((rp.rangeSeq > rp.newestSeq) || ((rp.rangeSeq == 0) && (rp.newestSeq == 0xff)))
            {
                rp.seqDelayCount++;
                printf("rp.seqDelayCount=%d \r\n", rp.seqDelayCount);
                if(rp.seqDelayCount >= 2)
                {
                    rp.seqDelayCount = 0;
                    correctSeqFlag = true;
                }
            }
            else
            {
               rp.seqDelayCount = 0;
            }
            printf("correctSeqFlag=%d \r\n", correctSeqFlag);
            if(true != correctSeqFlag)
            {
                rp.rangeSeq++;
                printf("rp.rangeSeq123456=%d \r\n", rp.rangeSeq);
                if(rp.rangeSeq > 0xff)
                {
                    rp.rangeSeq = 0;
                }
            }
            printf("rp.rangeSeq789=%d \r\n", rp.rangeSeq);

            rp.startMsec = msec;
            //update the list entry

            _tagList.replace(idx, rp);
        }
                /*if(rp.id == 5)
    printf("end rp.rangeSeq = %d clock = %d\n",rp.rangeSeq,clock());*/

    }




    //int range_corrected = range + (_ancArray[aid].tagRangeCorection[tid] * 10); //range correction is in cm (range is in mm)
    //emit tagRange(tid, aid, (range_corrected * 0.001)); //convert to meters

}

void RTLSClient::SendCellOnlineStatus(int tagId, uint8_t status)
{
   //_WebSocketServer->SendCellOnlineStatus(tagId, status);
   _tcpClient->sendTagOnlineStatus(tagId, status);
   QString idStr;
   idStr.sprintf("TAG:%02d",tagId);
   QString statusStr;
   QString dspStr;
   if(status == ON_LINE)
   {
       statusStr = QString(" 上线");
   }
   else
   {
      statusStr = QString(" 下线");
   }
   QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
   QString timeStr = time.toString("[MMdd-hh:mm:ss]"); //设置显示格式
   dspStr = timeStr + idStr + statusStr + QString("\n");
   qDebug()<<dspStr;
   emit dsptcpLog(dspStr);

}

void RTLSClient::SendAlarm(int tagId, ALARM_TYPE alarmType, uint8_t op)
{
    QString statusMsg;
    QString areaCode;
    TAG tmpNode;
    getTagLastInfo(tagId,&tmpNode);
    getAreaCode(tmpNode.last_effect_area_type,areaCode);
    _tcpClient->sendTagAlarm(tagId, (int)alarmType, op, areaCode);

    QString opStr;
    if(op == ALARM_SET)
    {
        opStr = QString(" 设置 ");
    }
    else
    {
        opStr = QString(" 取消 ");
    }
    QString idStr;
    idStr.sprintf("TAG:%02d",tagId);
    QString alarmStr;

    switch(alarmType)
    {
        case ALARM_NONE:
            alarmStr = QString("取消所有告警");
            break;
        case ALARM_OTHER_CELL:
            alarmStr = QString("串监告警");
            break;
        case ALARM_OUT_RANGE:
           alarmStr = QString("越界告警");
            break;
        case ALARM_STAY_LONG:
            alarmStr = QString("卫生间滞留告警");
            break;
        case ALARM_NO_SIGNAL:
            alarmStr = QString("信号消失告警");
            break;
        default:
            alarmStr.sprintf("无法识别的告警类型%d",alarmType);
            emit dsptcpLog(alarmStr);
            return;
    }


    if( (op == ALARM_SET) && (alarmType == ALARM_OUT_RANGE) )
    {
        statusMsg = "标签" + QString(" %1 ").arg(tagId) + QString("越界！");

        emit statusBarMessage(statusMsg);
    }
    else if( (op == ALARM_CANCEL) && (alarmType == ALARM_OUT_RANGE) )
    {
        statusMsg = "";

        emit statusBarMessage(statusMsg);
    }

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timeStr = time.toString("[MMdd-hh:mm:ss]"); //设置显示格式

    QString dspStr = timeStr + idStr + opStr + alarmStr + QString("\n");
    qDebug()<<dspStr;
    emit dsptcpLog(dspStr);
}

void RTLSClient::setServer(QString addr, int port)
{
    if((_javaServerAddr == addr) && (_javaServerPort == port))
    {
        qDebug()<<"addr  port none changed";
        return;
    }

    _javaServerAddr = addr;
    _javaServerPort = port;
    writeJavaServerSettings();
    _tcpClient->setServer(addr, port);
}

void RTLSClient::setOutServer(QString addr, int port)
{
    if((_OutServerAddr == addr) && (_OutServerPort == port))
    {
        qDebug()<<"addr  port none changed";
        return;
    }

    _OutServerAddr = addr;
    _OutServerPort = port;
    writeOutServerSettings();
    _tcpClientOutServer->setServer(addr, port);
}

void RTLSClient::getAreaCode(AREA_TYPE type, QString &code)
{
    QString buildTypeStr = QString("01");//监房;
    QString buildNumStr = QString("01");//1栋
    QString buildFloorStr = QString("03");//2层
    QString zoneTypeStr;

    switch(type)
    {
    case CELL_1:
        zoneTypeStr = "0900";
        break;
    /* case CELL_2:
        zoneTypeStr = "1000";
        break;
    case TOLIET_1:
        zoneTypeStr = "0901";
        break;
    case TOLIET_2:
        zoneTypeStr = "1001";
        break;*/
    case AREA_OUT_RANGE:
         code = QString("0000000000");
         return;
    }

    code = buildTypeStr + buildNumStr + buildFloorStr + zoneTypeStr;

}


/*************************************************************
*	Name:		positionCorrect
*	Func:		标签位置区域纠正，防止超出区域后后台显示出错
*	Input:		fx: 标签坐标X值 fy:标签坐标Y值 
				fx_j,fy_j: 若有校正值则进行偏移矫正
*	Output:		纠正后的X,Y坐标值
*	Return:		void
**************************************************************/
void RTLSClient::tagPositionCorrect(double *fx, double *fy, double fx_j = 0, double fy_j = 0)
{
	if(((*fx) < ZEROPLUS))
	{
		printf("1x======================\n");
		*fx = MODIFYVALUE;
	}else if(((*fx) > AREA_X))
	{
		printf("2x======================\n");
		*fx = (AREA_X - MODIFYVALUE);
	}

	if(((*fy) < ZEROPLUS))
	{
		printf("3y======================\n");
		*fy = MODIFYVALUE;
	}else if(((*fy) > AREA_Y))
	{
		printf("4y======================\n");
		*fy = (AREA_Y - MODIFYVALUE);
	}	
}



