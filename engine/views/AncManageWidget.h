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

/*	����ͷ�ļ�	*/
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
    //QPushButton * btn;//����
    UWB_UdpClient *cli;//��Ӧ�����Ŀͻ���
    int lastSec;   //�ϴθ�������ʱ��
    int isChecked; //�Ƿ�ѡ
    int up_flag;//�Ƿ�����������־
    int query_ver_ack;//�Ƿ��յ���ѯ�汾�ŵ���Ӧ

    /*  ������ʾ��վ������Ϣ    lwq 20190313    */
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
        UP_SUCCESS = 0, //ȫ���ɹ�
        UP_DOING = 1,//������
        UP_HALF_FAILED = 2,//��������ʧ�ܣ��汾������
        UP_ALL_FAILED = 3,//ȫ������ʧ��
        UP_BACKED//�汾�������
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

    /*  ������ʱ��  */
    QTimer *_sendDataTimer;
    QUdpSocket * _udpSocket;

    /*  ���������Ͳ�������    lwq 20190314    */
    ViewAncGroupWidget *_viewAncGroupWidget;

    /*  ��ȡ��վ������Ϣ    lwq 20190313    */
    void getAncConfigInfo(int aid,int *group, float *x, float *y, float *z);
    
signals:
    void sendUpResp(int status, int *succBuf, int succCount, int *failBuf, int failCount);

    /*  ���ͻ�վ���ߴ���    */
    void sendDownLineInfo(int aid);

public slots:
    void startUpdate(QString ver);
    //void updateBtnClicked();
    void sendUpCmdRsut(int aid, bool ok);//��������ָ��������
    void sendRecoverCmdRsut(int aid, bool ok);//���Ͱ汾���˽������
    void sendGetVerRsut(int aid, QString ver);//���ͻ�ȡ�汾�Ž������
    void updateAncAddr(int aid, QString addr, int port);//���»�վ��ַ��Ϣ
    void periodProcess();
    void startUpTimeout();
    void reportStaTimeout();
    void cellClicked(int r, int c);
    void showUpSrvW(void);

    /*������վ������ط��� lwq 20190313 */
    void initAncInfoManage(int ancId, int group, double x, double y, double z);

private slots:
    void verChanged(QString ver);

    /*  ��ѯ�����豸У׼ʱ�䶨ʱ�� */
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

    /*  ��վ����    */
    QAction *_setAncGroupParmAction;

    
    AncUpSrvConfigWidget* _ancUpSrvConfigW;


    int _start_upgrade_flag;
    QString _ver;


};

#endif // TAGMANAGEWIDGET_H
