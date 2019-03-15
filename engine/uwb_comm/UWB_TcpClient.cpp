#include "UWB_TcpClient.h"
#include <QDataStream>
#include "cJSON.h"
#include<QThread>
#include<QDateTime>
#include<QTime>
#include "tagInfo/tagInfo.h"
#include <QSettings>

#define pi 3.14159265358979
#define iPI  0.0174532925199433
#define  a 6378140.0 // 地球半径
#define  f  1.0 / 298.257 // 第一扁率


UWB_TcpClient::UWB_TcpClient(QString addr, int port):_serverAddr(addr),_serverPort(port)
{
    _tcpClient = new QTcpSocket(this);
    _pingTimer = new QTimer;
    _connTimer = new QTimer;
    _pingRspTimer = new QTimer;
    _connectFlag = false;


    connect(_tcpClient,SIGNAL(connected()),this,SLOT(connectOk()));
    connect(_tcpClient,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(_tcpClient,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(_tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(printError(QAbstractSocket::SocketError)));
    connect(_pingTimer,SIGNAL(timeout()),this, SLOT(pingTimeout()));
    connect(_connTimer,SIGNAL(timeout()),this, SLOT(connTimeout()));
    connect(_pingRspTimer, SIGNAL(timeout()), this, SLOT(pingRspTimeout()));

    _pingTimer->setInterval(60000);
    _pingTimer->start();
    _connTimer->setInterval(1000);
    _connTimer->start();
    _pingRspTimer->setInterval(3000);

    _tcpClient->connectToHost(_serverAddr,_serverPort);
}

UWB_TcpClient::~UWB_TcpClient()
{
    _tcpClient->close();
    delete _tcpClient;
    delete _pingTimer;
    delete _connTimer;
    delete _pingRspTimer;
}

//?l??
void UWB_TcpClient::connTimeout()
{
    _connTimer->start();
    if(false == _connectFlag)
    {
        _tcpClient->abort();
        _tcpClient->connectToHost(_serverAddr,_serverPort);
    }
}

void UWB_TcpClient::pingRspTimeout()
{
    qDebug()<<"ping rsp time out";
    _connectFlag = false;
    _pingRspTimer->stop();
}

//??????,?А????ф????????П
void UWB_TcpClient::sendMsg(const QByteArray &data)
{
    _tcpClient->write(data);
    _pingTimer->start();
}

void UWB_TcpClient::connectOk()
{
    _connectFlag = true;
    qDebug()<<"tcpclient connect ok";

}

void UWB_TcpClient::setServer(QString addr, int port)
{
    if((_serverAddr == addr)&&(_serverPort == port))
    {
        return;
    }

    _serverAddr = addr;
    _serverPort = port;
    _connectFlag = false;
    _connTimer->start();
    _tcpClient->abort();
    _tcpClient->connectToHost(_serverAddr,_serverPort);
}


void UWB_TcpClient::readMessage()
{
    _pingRspTimer->stop();//????Ь?ì??_pingRspTimer

    QDataStream readIn(_tcpClient);
    readIn.setVersion(QDataStream::Qt_5_7);
    QByteArray readBuf = _tcpClient->readAll();
    QString readStr = QString::fromLocal8Bit(readBuf);
    qDebug()<<"readStr"<<readStr;

    msgHandle(readStr);
}


void UWB_TcpClient::disconnected()
{
    _connectFlag = false;
    qDebug()<<"tcpclient disconnect";
}

void UWB_TcpClient::printError(QAbstractSocket::SocketError)
{
    qDebug()<< "tcpclient err:"<<_tcpClient->errorString();
    _tcpClient->abort();
    _connectFlag = false;
}

void UWB_TcpClient::pingTimeout()
{
    _pingTimer->start();
    _pingRspTimer->start();//?????????Ь?

    if(false == _connectFlag)
        return;
    int msgType = MSG_TYPE_PING;
    cJSON *posJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(posJson, "ping", 1);
    cJSON_AddNumberToObject(posJson, "type", msgType);

    char *strPosData = cJSON_Print(posJson);
    qDebug() << "ping str:"<< strPosData;
    QString s(strPosData);
    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(posJson);
    free(strPosData);
}

void UWB_TcpClient::sendTagOnlineStatus(int tagId, int status)
{
    if(false == _connectFlag)
        return;

    int msgType = MSG_TYPE_ONLINE_STATUS;
    cJSON *posJson = cJSON_CreateObject();
    if (posJson == NULL)
    {
        return;
    }

    QDateTime time = QDateTime::currentDateTime();
    int tim_t = time.toTime_t();
    cJSON_AddNumberToObject(posJson, "tag_id", tagId);
    cJSON_AddNumberToObject(posJson, "status", status);
    cJSON_AddNumberToObject(posJson, "type", msgType);
    cJSON_AddNumberToObject(posJson, "timestamp",tim_t);

    char *strPosData = cJSON_Print(posJson);
    qDebug() << "send online status:"<< strPosData;
    QString s(strPosData);

    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(posJson);
    free(strPosData);
}

void UWB_TcpClient::sendTagAlarm(int tagId, int alarm, int op, QString areaCode)
{
    if(false == _connectFlag)
        return;
    QString alarmTypeStr;
    QString alarmLvStr;
    int msgType = MSG_TYPE_ALARM;

    switch(alarm)
    {
        case ALARM_OTHER_CELL:
            alarmTypeStr = ALARM_OTHER_CELL_STR;
            alarmLvStr = ALARM_LEVEL_BAD;
            break;
        case ALARM_OUT_RANGE:
            alarmTypeStr = ALARM_OUT_RANGE_STR;
             alarmLvStr = ALARM_LEVEL_BAD;
            break;
        case ALARM_STAY_LONG:
            alarmTypeStr = ALARM_STAY_TIMOUT_STR;
            alarmLvStr = ALARM_LEVEL_COMMON;
            break;
        case ALARM_NO_SIGNAL:
            alarmTypeStr = ALARM_NO_SIGNAL_STR;
            alarmLvStr = ALARM_LEVEL_COMMON;
            break;
        default:
            My_Debug()<<"UNKOWN ALARM TYPE";
            return;
    }
    cJSON *posJson = cJSON_CreateObject();
    if (posJson == NULL)
    {
        return;
    }

    QDateTime time = QDateTime::currentDateTime();
    int tim_t = time.toTime_t();
    cJSON_AddNumberToObject(posJson, "tag_id", tagId);
    cJSON_AddStringToObject(posJson, "warning_code", alarmTypeStr.toLatin1().data());
    cJSON_AddStringToObject(posJson, "level", alarmLvStr.toLatin1().data());
    cJSON_AddNumberToObject(posJson, "type", msgType);
    cJSON_AddNumberToObject(posJson, "op", op);
    cJSON_AddNumberToObject(posJson, "timestamp",tim_t);
    cJSON_AddStringToObject(posJson, "pos_code", areaCode.toLatin1().data());

    char *strPosData = cJSON_Print(posJson);
    My_Debug() << "send alarm11111:"<< strPosData;
    QString s(strPosData);

    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(posJson);
    free(strPosData);
}

/**********************************/
/*经纬度转高斯*/
void Geo2Gauss(double Lat, double Lon, short IsSix, double *y, double *x, double *Gammar)
{
	int ProjNo, ZoneWide;
	double Lon1, Lat1, Lon0, X0, Y0, tmpx, tmpy;
	double e2, ee, NN, T, C, A, M;
	double e, n, l ,t;

	ProjNo = 0;

	//// 计算中心子午线经度
	if (IsSix == 1 )// 6度带
	{
		ZoneWide = 6; // 带宽
		ProjNo = (int)(Lon / ZoneWide);
		Lon0 = ProjNo * ZoneWide + ZoneWide / 2;
		Lon0 = Lon0 * iPI;
	}
	//else // 3度带
	//{
	//	ZoneWide = 3; // 带宽 
	//	ProjNo = round(Lon / ZoneWide);
	//	Lon0 = ProjNo * ZoneWide;
	//	Lon0 = Lon0 * iPI;    
	//}

	// 经纬度转换为弧度
	Lon1 = Lon * iPI;
	Lat1 = Lat * iPI;

	e2 = 2 * f - f * f;
	ee = e2 * (1.0 - e2);
	NN = a /  sqrt(1.0 - e2 *  sin(Lat1) *  sin(Lat1));
	T =  tan(Lat1) *  tan(Lat1);
	C = ee *  cos(Lat1) *  cos(Lat1);
	A = (Lon1 - Lon0) *  cos(Lat1);
	M = a * ((1 - e2 / 4 - 3 * pow(e2,2 )/ 64 - 5 * pow(e2,3) / 256) * Lat1 - (3 * e2 / 8 + 3 * pow(e2,2) / 32 + 45 * pow(e2,3) / 1024) *  sin(2 * Lat1) + (15 * pow(e2,2 )/ 256 + 45 * pow(e2,3) / 1024) *  sin(4 * Lat1) - (35 * pow(e2,3) / 3072) *  sin(6 * Lat1));
	tmpy = NN * (A + (1 - T + C) * pow(A,3) / 6 + (5 - 18 * T + T * T + 72 * C - 58 * ee) *pow( A,5) / 120);
	tmpx = M + NN *  tan(Lat1) * (A * A / 2 + (5 - T + 9 * C + 4 * C * C) * pow(A,4) / 24 + (61 - 58 * T + T * T + 600 * C - 330 * ee) *pow( A,6) / 720);
	Y0 = 1000000 * (ProjNo + 1) + 500000;
	X0 = 0;
	*x = tmpx + X0; 
	*y = tmpy + Y0;



	//// 计算测量点的子午线收敛角

	e = 1.0/pow((1-f),2) - 1;
	e = sqrt(e); // 第二扁心率
	
	n = e * pow(cos(Lat1),2);

	l = (Lon1 - Lon0 )/ iPI; // 测量点经度与中心子午线的经度差（゜）

	t = tan(Lat1);

	*Gammar = l * sin(Lat1) * (1 +pow( l,2) * pow(cos(Lat1),2) * (1 + 3*pow(n,2) + 2*pow(n,4)) / 3 + pow(l,4 )* pow(cos(Lat1),4) *(2-pow(t,2)) / 15.0);


}

/*高斯转经纬度*/
void Gauss2Geo(double y, double x, short IsSix,  double *Lat, double *Lon)
{
	double D, K;
	double L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
	double Jd, Wd;

// 带号
D = (int)(y/1000000); // 取整

// 中央经线
K = 0;
if (IsSix == 1)
{
    K = D * 6 - 3; // 6度带计算
}
else
{
    K = D * 3;  // 3度带计算
}

// 计算
L = x / (6378245 * (1-0.006693421623) * 1.0050517739);
M = L +(0.00506237764 * sin(2*L)/2-0.00001062451 * sin(4*L)/4+0.0000002081*sin(6*L)/6)/1.0050517739;
N = L +(0.00506237764 * sin(2*M)/2-0.00001062451 * sin(4*M)/4+0.0000002081*sin(6*M)/6)/1.0050517739;
O = L +(0.00506237764 * sin(2*N)/2-0.00001062451 * sin(4*N)/4+0.0000002081*sin(6*N)/6)/1.0050517739;
P = L +(0.00506237764 * sin(2*O)/2-0.00001062451 * sin(4*O)/4+0.0000002081*sin(6*O)/6)/1.0050517739;
Q = L +(0.00506237764 * sin(2*P)/2-0.00001062451 * sin(4*P)/4+0.0000002081*sin(6*P)/6)/1.0050517739;
R = L +(0.00506237764 * sin(2*Q)/2-0.00001062451 * sin(4*Q)/4+0.0000002081*sin(6*Q)/6)/1.0050517739;
S = tan(R);
T = 0.006738525415 * pow(cos(R),2.0);
U = 6378245.0 / sqrt(1-0.006693421623*pow(sin(R),2.0));
V = 6378245.0*(1-0.006693421623)/pow((sqrt((1-0.006693421623*pow(sin(R),2)))),3.0);
W = 5+3*pow(S,2.0)+T-9*T*pow(S,2.0);
X = 61+90*pow(S,2.0)+45*pow(S,4.0);
Y = 1+2*pow(S,2.0)+pow(T,2.0);
Z = 5+28*pow(S,2.0)+24*pow(S,4.0)+6*T+8*T*pow(S,2.0);
Wd = (180/pi)*(R-pow((y-D*1000000-500000),2.0)*S/(2*V*U)+pow((y-D*1000000-500000),4.0)*W/(24*pow(U,3.0)*V)-pow((y-D*1000000-500000),6.0)*X/(7200*pow(U,5.0)*V));
Jd = (180.0/pi)*(y-D*1000000-500000)*(1-pow((y-D*1000000-500000),2.0)*Y/(6*pow(U,2.0))+pow((y-D*1000000-500000),4.0)*Z/(120*pow(U,4.0)))/(U*cos(P));

// 输出
*Lat = Wd; // 纬度
*Lon = K + Jd; // 经度

}

/******************************************************/

double jw[2]={112.98586,22.99594};
static double  mm [5]={0.00001,0.00002,0.00003,0.00004,0.00005};
static int my =0;


void UWB_TcpClient::sendPositon(int tagId, double x, double y, double z, QString areaCode)
{

        # if 1
    if(false == _connectFlag)
        return;
	#endif

     int msgType = MSG_TYPE_POSITION;

    cJSON *posJson = cJSON_CreateObject();
    if (posJson == NULL)
    {
        return;
    }

    QDateTime time = QDateTime::currentDateTime();
    int tim_t = time.toTime_t();
    x = x * 1000;
    y = y * 1000;
    z = z * 1000;
    int pos_x = (int)x;
    int pos_y = (int)y;
    int pos_z = (int)z;
    pos_x = pos_x ^ 9527;
    pos_y = pos_y ^ 9527;
    pos_z = pos_z ^ 9527;
    cJSON_AddNumberToObject(posJson, "tag_id", tagId);
    cJSON_AddNumberToObject(posJson, "pos_x", pos_x);
    cJSON_AddNumberToObject(posJson, "pos_y", pos_y);
    cJSON_AddNumberToObject(posJson, "pos_z", pos_z);
    cJSON_AddNumberToObject(posJson, "type", msgType);
    cJSON_AddStringToObject(posJson, "pos_code", areaCode.toLatin1().data());
    cJSON_AddNumberToObject(posJson, "timestamp",tim_t);



    /*坐标转换*/
	#if 0
	double Theta = 30; // 室内坐标系的x轴方位（相对真北，单位゜）
	double x1=0,y1=0;//原点的高斯坐标
	short IsSix = 1;  // 是否6度带
	double Lat =22.995919 , Lon =112.985859, Gammar = 0; // 输出纬度、经度
	double Xp, Yp; //p点在高斯坐标系中的位置
	double xp =x, yp =y; //p点在室内坐标系中的位置
	double delt; // 室内坐标系与原点所在高斯坐标系的方位角差
	Geo2Gauss(Lat, Lon, IsSix, &y1, &x1, &Gammar);
	
	delt = Theta - Gammar;
	delt = delt * pi / 180.0;

	Xp = xp * cos(delt) + yp * sin(delt) +x1;
	Yp = yp * cos(delt) - xp * sin(delt) +y1;
	Gauss2Geo(Yp, Xp, IsSix, &Lat, &Lon);


	/*对外部发送临时处理*/

	double lat = Lat;
	double lng = Lon;
	double altitude =1.0 ;
	cJSON_AddNumberToObject(posJson, "lat",lat);
	cJSON_AddNumberToObject(posJson, "lng",lng);
	cJSON_AddNumberToObject(posJson, "altitude",altitude);
#endif 

    char *strPosData = cJSON_Print(posJson);
	qDebug() << "send pos:"<< strPosData;
   // My_Debug() << "send pos:"<< strPosData;
    QString s(strPosData);

    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(posJson);
    free(strPosData);
}

void UWB_TcpClient::sendPositonOutServer(int tagId, double x, double y, double z, QString areaCode)
{

        # if 1
    if(false == _connectFlag)
        return;
	#endif

     int msgType = MSG_TYPE_POSITION;

    cJSON *posJson = cJSON_CreateObject();
    if (posJson == NULL)
    {
        return;
    }

    QDateTime time = QDateTime::currentDateTime();
    int tim_t = time.toTime_t();
    x = x * 1000;
    y = y * 1000;
    z = z * 1000;
    int pos_x = (int)x;
    int pos_y = (int)y;
    int pos_z = (int)z;
    pos_x = pos_x ^ 9527;
    pos_y = pos_y ^ 9527;
    pos_z = pos_z ^ 9527;
    cJSON_AddNumberToObject(posJson, "tag_id", tagId);
    cJSON_AddNumberToObject(posJson, "pos_x", pos_x);
    cJSON_AddNumberToObject(posJson, "pos_y", pos_y);
    cJSON_AddNumberToObject(posJson, "pos_z", pos_z);
    cJSON_AddNumberToObject(posJson, "type", msgType);
    cJSON_AddStringToObject(posJson, "pos_code", areaCode.toLatin1().data());
    cJSON_AddNumberToObject(posJson, "timestamp",tim_t);



    /*坐标转换*/
	#if 0
	double Theta = 30; // 室内坐标系的x轴方位（相对真北，单位゜）
	double x1=0,y1=0;//原点的高斯坐标
	short IsSix = 1;  // 是否6度带
	double Lat =22.995919 , Lon =112.985859, Gammar = 0; // 输出纬度、经度
	double Xp, Yp; //p点在高斯坐标系中的位置
	double xp =x, yp =y; //p点在室内坐标系中的位置
	double delt; // 室内坐标系与原点所在高斯坐标系的方位角差
	Geo2Gauss(Lat, Lon, IsSix, &y1, &x1, &Gammar);
	
	delt = Theta - Gammar;
	delt = delt * pi / 180.0;

	Xp = xp * cos(delt) + yp * sin(delt) +x1;
	Yp = yp * cos(delt) - xp * sin(delt) +y1;
	Gauss2Geo(Yp, Xp, IsSix, &Lat, &Lon);


	/*对外部发送临时处理*/

	double lat = Lat;
	double lng = Lon;
	double altitude =1.0 ;
	cJSON_AddNumberToObject(posJson, "lat",lat);
	cJSON_AddNumberToObject(posJson, "lng",lng);
	cJSON_AddNumberToObject(posJson, "altitude",altitude);
#endif 

    char *strPosData = cJSON_Print(posJson);
	qDebug() << "send pos:"<< strPosData;
   // My_Debug() << "send pos:"<< strPosData;
    QString s(strPosData);

    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(posJson);
    free(strPosData);
}

void UWB_TcpClient::sendTagHeartRate(int tagId, int heartRate, int power, int state)
{
    if(false == _connectFlag)
        return;

    int msgType = MSG_TYPE_HEART;
    int sos = 0, wristlet = 0, move = 0;


    cJSON *posJson = cJSON_CreateObject();
    if (posJson == NULL)
    {
        return;
    }

    if(0xff == state)
    {
        sos = 0xff ;
        wristlet = 0xff;
        move = 0xff;
    }
    else
    {   
        move = state & 0x01;
        wristlet = state & 0x02;
        sos = state & 0x04;
                  /*
		sos = state & 0x01;
        wristlet = state & 0x02;
        move = state & 0x04;*/
    }
    printf("state=%d  sos[i]=%d\n",state,sos);
    
    QDateTime time = QDateTime::currentDateTime();
    int tim_t = time.toTime_t();
    cJSON_AddNumberToObject(posJson, "tag_id", tagId);
    cJSON_AddNumberToObject(posJson, "power", power);
    cJSON_AddNumberToObject(posJson, "heart", heartRate);
    cJSON_AddNumberToObject(posJson, "sos", sos);
    cJSON_AddNumberToObject(posJson, "wristlet", wristlet);
    cJSON_AddNumberToObject(posJson, "move", move);
    cJSON_AddNumberToObject(posJson, "type", msgType);
    cJSON_AddNumberToObject(posJson, "timestamp",tim_t);

    char *strPosData = cJSON_Print(posJson);
    QString s(strPosData);

    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(posJson);
    free(strPosData);
}


void UWB_TcpClient::msgHandle(QString msg)
{
    cJSON *json = NULL, *cmdTypeJson = NULL;

    json = cJSON_Parse(msg.toLatin1().data());
    if(json == NULL)
    {
        qDebug()<<"uwb_tcpclient msg prase json err";
        return;
    }
    cmdTypeJson = cJSON_GetObjectItem(json, CMD_TYPE);

    if(cmdTypeJson == NULL || cmdTypeJson->type != cJSON_String)
    {
        qDebug()<<"uwb_tcpclient msg prase cmd_type err";

        cJSON_Delete(json);
        return ;
    }
    QString cmdType = QString(cmdTypeJson->valuestring);

    if(CHECK_VER== cmdType)
    {
        sendCkVerResp();
    }
    else if(UPGRADE == cmdType)
    {

        cJSON *serverJson = NULL;
        cJSON *filePathJson = NULL;
        cJSON *ancVerJson = NULL;

        QSettings * configfile;
        configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
        configfile->beginGroup("upgradeserver");
        QString recent_ver = configfile->value("anc_ver").toString();
        configfile->endGroup();
        delete configfile;

        ancVerJson = cJSON_GetObjectItem(json, ANC_VER);
        if(NULL == ancVerJson  || ancVerJson->type != cJSON_String)
        {
            qDebug()<<"uwb_tcpclient msg parse anc_ver err";
            cJSON_Delete(json);
            return;
        }
        QString ancVer = QString(ancVerJson->valuestring);

        if(ancVer == recent_ver)
        {
             cJSON_Delete(json);
             int fail_buf[1]; int succ_buf[1];
             sendUpResp(UP_REPEAT,fail_buf,0,succ_buf,0);
             return;
        }

        serverJson = cJSON_GetObjectItem(json, SERVER);
        if(NULL == serverJson || serverJson->type != cJSON_String)
        {
            qDebug()<<"uwb_tcpclient msg prase server err";
            cJSON_Delete(json);
            return ;
        }
        QString server = QString(serverJson->valuestring);

        filePathJson = cJSON_GetObjectItem(json, FILE_PATH);
        if(NULL == serverJson || filePathJson->type != cJSON_String)
        {
            qDebug()<<"uwb_tcpclient msg prase file_path err";
            cJSON_Delete(json);
            return ;
        }
        QString file_path = QString(filePathJson->valuestring);
   		//QString file_path = "/" + ancVer;

        qDebug()<<"recv cmd upgrade server:"<<server <<"file_path:"<< file_path \
                  <<"anc_ver:"<< ancVer;

		printf("recv cmd upgrade server: %s file_path:%s anc_ver:%s ",server.toStdString().data(), file_path.toStdString().data(), \
			ancVer.toStdString().data());
        backupSetting();
        writeSetting(server, file_path, ancVer);
        sendUpResp(UP_DOING, NULL, 0, NULL, 0);

        emit startUpdate(ancVer);
    }

    cJSON_Delete(json);
    return ;
}



void UWB_TcpClient::sendCkVerResp()
{
    QString file;
    int up_time;

    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("upgradeserver");
    //QString filePath = configfile->value("file_path").toString();
    QString anc_ver = configfile->value("anc_ver").toString();
    up_time = configfile->value("up_time").toInt();
    configfile->endGroup();
    delete configfile;

    if(anc_ver.isEmpty())
    {
        anc_ver = QString("default.bin");
    }

    cJSON *verJson = cJSON_CreateObject();
    if (verJson == NULL)
    {
        return;
    }

    cJSON_AddStringToObject(verJson, CMD_TYPE, CHECK_VER);
    cJSON_AddStringToObject(verJson, CMD_DIR, DIR_RESP);
    cJSON_AddStringToObject(verJson, ANC_VER, anc_ver.toLatin1().data());
    cJSON_AddStringToObject(verJson, TAG_VER, "TAG_V10001.bin");
    cJSON_AddNumberToObject(verJson, ANC_UP_TIME, up_time);
    cJSON_AddNumberToObject(verJson, TAG_UP_TIME, up_time);
    cJSON_AddNumberToObject(verJson, "type", 5);

    char *data = cJSON_Print(verJson);
    QString s(data);

    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(verJson);
    free(data);
}



/*
void UWB_TcpClient::sendUpResp(int status)
{

    if(status == UP_HALF_FAILED)
    {
        qDebug()<<"arg status:2 err";
        return;
    }

    cJSON *upJson = cJSON_CreateObject();
    if (upJson == NULL)
    {
        return;
    }

    cJSON_AddStringToObject(upJson, CMD_TYPE, UPGRADE);
    cJSON_AddStringToObject(upJson, CMD_DIR, DIR_RESP);
    cJSON_AddNumberToObject(upJson, UP_STATUS, status);

    cJSON_AddNumberToObject(upJson, "type", 6);
    char *data = cJSON_Print(upJson);

    QString s(data);
    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(upJson);
    free(data);
}*/

void UWB_TcpClient::sendUpResp(int status,  int *succBuf, int succCount, int *failBuf, int failCount)
{
    cJSON *upJson = cJSON_CreateObject();
    if (upJson == NULL)
    {
        return;
    }

    cJSON_AddStringToObject(upJson, CMD_TYPE, UPGRADE);
    cJSON_AddStringToObject(upJson, CMD_DIR, DIR_RESP);
    cJSON_AddNumberToObject(upJson, UP_STATUS, status);

    //if(status == 2)
    {
        cJSON * failJson = NULL, *succJson = NULL;

        failJson = cJSON_CreateObject();
        succJson = cJSON_CreateObject();
        cJSON_AddItemToObject(failJson, "failed", cJSON_CreateIntArray(failBuf, failCount));
        cJSON_AddItemToObject(succJson, "succ", cJSON_CreateIntArray(succBuf, succCount));
        cJSON * resultArray = NULL;
        resultArray = cJSON_CreateArray();
        cJSON_AddItemToArray(resultArray, failJson);
        cJSON_AddItemToArray(resultArray, succJson);

        cJSON_AddItemToObject(upJson, "up_result", resultArray);

    }
    cJSON_AddNumberToObject(upJson, "type", 6);
    char *data = cJSON_Print(upJson);

    QString s(data);
    QByteArray outBlock ;
    outBlock = outBlock.append(s);
    outBlock = outBlock.append("*");

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    sendMsg(outBlock);

    cJSON_Delete(upJson);
    free(data);
}

void UWB_TcpClient::writeSetting(QString server, QString file_path, QString ver)
{
    QString addr;
    int port;
    int up_time;
    addr = server.section(":",0,0);
    port = server.section(":",1,1).toInt();

    QDateTime time = QDateTime::currentDateTime();
    up_time = time.toTime_t();;

    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->setValue("/upgradeserver/addr", addr);
    configfile->setValue("/upgradeserver/port", port);
    configfile->setValue("/upgradeserver/file_path", file_path);
    configfile->setValue("/upgradeserver/up_time", up_time);
    configfile->setValue("/upgradeserver/anc_ver", ver);
    delete configfile;
}



void UWB_TcpClient::backupSetting()
{

    QString addr;
    QString port;
    QString file_path;
    QString anc_ver;
    QString up_time;
    QSettings * configfile;
    configfile = new QSettings("uwbconfig.ini", QSettings::IniFormat);

    configfile->beginGroup("upgradeserver");
    addr = configfile->value("addr").toString();
    port = configfile->value("port").toString();
    file_path = configfile->value("file_path").toString();
    anc_ver = configfile->value("anc_ver").toString();
    up_time = configfile->value("up_time").toString();
    configfile->endGroup();

    configfile->setValue("/upgradeserver_back/addr", addr);
    configfile->setValue("/upgradeserver_back/port", port);
    configfile->setValue("/upgradeserver_back/file_path", file_path);
    configfile->setValue("/upgradeserver_back/anc_ver", anc_ver);
    configfile->setValue("/upgradeserver_back/up_time", up_time);


    delete configfile;

}



/*************************************************************
*	Name:		sendTagStatus
*	Func:		发送标签状态
*	Input:		tag_id: 标签ID tag_status: 标签状态
				tag_area: 标签所处区域
*	Output:		void
*	Return:		void
**************************************************************/
void UWB_TcpClient::sendTagStatus(int tag_id, int tag_status, QString tag_area)
{
	int msgType = MSG_TYPE_POSITION;

	cJSON *posJson = cJSON_CreateObject();
	
	if (posJson == NULL)
	{
		return;
	}

	QDateTime time = QDateTime::currentDateTime();
	int tim_t = time.toTime_t();

	cJSON_AddNumberToObject(posJson, "type", 9);
	cJSON_AddNumberToObject(posJson, "tag_id", tag_id);
	cJSON_AddNumberToObject(posJson, "tag_status", tag_status);
	cJSON_AddStringToObject(posJson, "pos_code", tag_area.toLatin1().data());
	cJSON_AddNumberToObject(posJson, "timestamp",tim_t);

	char *strPosData = cJSON_Print(posJson);
	qDebug() << "send pos:"<< strPosData;
   // My_Debug() << "send pos:"<< strPosData;
	QString s(strPosData);

	QByteArray outBlock ;
	outBlock = outBlock.append(s);
	outBlock = outBlock.append("*");

	QDataStream out(&outBlock, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_7);
	sendMsg(outBlock);

	cJSON_Delete(posJson);
	free(strPosData);
	printf("sendTagStatus\n");
}


/*************************************************************
*	Name:		sendAncStatus
*	Func:		发送基站状态
*	Input:		anc_id: 基站ID anc_status: 基站状态
				tag_num: 基站标签总数
*	Output:		void
*	Return:		void
**************************************************************/
void UWB_TcpClient::sendAncStatus(int tag_id, int tag_status, int tag_num)
{
	 int msgType = MSG_TYPE_POSITION;

	 cJSON *posJson = cJSON_CreateObject();
	 
	 if (posJson == NULL)
	 {
		 return;
	 }

	 QDateTime time = QDateTime::currentDateTime();
	 int tim_t = time.toTime_t();

	 cJSON_AddNumberToObject(posJson, "type", 8);
	 cJSON_AddNumberToObject(posJson, "anchor_id", tag_id);
	 cJSON_AddNumberToObject(posJson, "anchor_status", tag_status);
	 cJSON_AddNumberToObject(posJson, "online_tag_number", tag_num);
	 cJSON_AddNumberToObject(posJson, "timestamp",tim_t);

	 char *strPosData = cJSON_Print(posJson);
	 qDebug() << "send pos:"<< strPosData;
	// My_Debug() << "send pos:"<< strPosData;
	 QString s(strPosData);

	 QByteArray outBlock ;
	 outBlock = outBlock.append(s);
	 outBlock = outBlock.append("*");

	 QDataStream out(&outBlock, QIODevice::WriteOnly);
	 out.setVersion(QDataStream::Qt_5_7);
	 sendMsg(outBlock);

	 cJSON_Delete(posJson);
	 free(strPosData);
	 printf("sendAncStatus\n");
}



