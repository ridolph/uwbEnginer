#ifndef TAGMANAGEWIDGET_H
#define TAGMANAGEWIDGET_H

#include <QWidget>
#include <QMap>
#include <QPushButton>
#include <QTableWidgetItem>
#include <uwb_comm/UpdateClient.h>
#include <QTimer>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QLabel>
#include "AncUpSrvConfigWidget.h"
#include "uwb_comm/uwb_udpclient.h"
#include <QUdpSocket>
#include "RTLSClient.h"

/*	新增头文件	*/
#include "viewancgroupwidget.h"
#include "network/RTLSClient.h"

namespace Ui {
class AncManageWidget;
}

typedef struct {
    int ridx;
    QString addr;
    int port;
    QString ver;
    int online;
    //QPushButton * btn;//按键
    UWB_UdpClient *cli;//对应建立的客户端
    int lastSec;   //上次更新数据时间
    int isChecked; //是否勾选
    int up_flag;//是否正在升级标志
    int query_ver_ack;//是否收到查询版本号的响应

    /*  新增显示基站基本信息    lwq 20190313    */
    int group;
    double x;
    double y;
    double z;
}AncItem;

typedef QMap<int, AncItem>   AncTableMap;

class AncManageWidget : public QWidget
{
    Q_OBJECT

public:

    enum {
        UP_SUCCESS = 0, //全部成功
        UP_DOING = 1,//升级中
        UP_HALF_FAILED = 2,//部分升级失败，版本回退中
        UP_ALL_FAILED = 3,//全部升级失败
        UP_BACKED//版本回退完成
    }_UP_STATUS;

    enum {
        ColumnGroup = 0,
        ColumnID,
        ColumnX,
        ColumnY,
        ColumnZ,
        ColumnAddr,
        ColumnVer,
        ColumnOlStatus,
        ColumnCount
        /*
        ColumnID = 0,
        ColumnAddr,
        ColumnVer,
        ColumnOlStatus,
        ColumnCount
        */
    }Column;

    explicit AncManageWidget(QWidget *parent = 0);
    ~AncManageWidget();
    void init();

    /*  新增定时器  */
    QTimer *_sendDataTimer;
    QUdpSocket * _udpSocket;

    /*  新增组管理和参数设置    lwq 20190314    */
    ViewAncGroupWidget *_viewAncGroupWidget;

    /*  获取基站基本信息    lwq 20190313    */
    void getAncConfigInfo(int aid,int *group, float *x, float *y, float *z);
    
signals:
    void sendUpResp(int status, int *succBuf, int succCount, int *failBuf, int failCount);

    /*  发送基站掉线处理    */
    void sendDownLineInfo(int aid);

public slots:
    void startUpdate(QString ver);
    //void updateBtnClicked();
    void sendUpCmdRsut(int aid, bool ok);//发送升级指令结果返回
    void sendRecoverCmdRsut(int aid, bool ok);//发送版本回退结果返回
    void sendGetVerRsut(int aid, QString ver);//发送获取版本号结果返回
    void updateAncAddr(int aid, QString addr, int port);//更新基站地址信息
    void periodProcess();
    void startUpTimeout();
    void reportStaTimeout();
    void cellClicked(int r, int c);
    void showUpSrvW(void);

    /*新增基站管理相关方法 lwq 20190313 */
    void initAncInfoManage(int ancId, int group, double x, double y, double z);

private slots:
    void verChanged(QString ver);

    /*  轮询发送设备校准时间定时器 */
    void senDataTimeout(void);

private:
    void loadAncItem(int aid, int isChecked, QString ver);
    void addNewAncItem(int aid, QString addr, int port);
    int setAncItem(int aid, AncItem item);
    int getAncItem(int aid, AncItem* pItem);
    void writeManageConfig(int aid, int checkState, QString ver);
    void initManageConfig();
    void readNewVer();
    void checkOnline();
    void checkVerUpdate();
    void recoverSetting();
    void startVerBack();


    Ui::AncManageWidget *ui;
    AncTableMap _ancS;
    QTimer * _periodTimer;
    QTimer * _startUpTimer;
    QTimer * _reportStaTimer;
    //QTimer * _
    QMenuBar* _menuBar;
    QMenu *_settingMenu ;
    QAction *_setAncTcpPortAction;
    QAction *_setUpgradeServerAction;

    /*  基站管理    */
    QAction *_setAncGroupParmAction;

    
    AncUpSrvConfigWidget* _ancUpSrvConfigW;


    int _start_upgrade_flag;
    QString _ver;


};

#endif // TAGMANAGEWIDGET_H
