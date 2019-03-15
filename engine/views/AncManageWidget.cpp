#include "AncManageWidget.h"
#include "ui_AncManageWidget.h"
#include <QPushButton>
#include <QRect>
#include <QDebug>
#include <time.h>
#include <QSettings>
#include <QDateTime>
#include <QTextCodec>
#include <QFile>
#include <QDomDocument>




//#define TCPSERVER_PORT 51000

static QTextCodec *gbkCode;	/*  定义转换编码格式的全局变量   */

#define Mtr(s) (gbkCode->toUnicode(s))

#define SEND_TIME_VALUE	5000	/*	定时发送系统时间值	*/

AncManageWidget::AncManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AncManageWidget)
{	
	
    /* 新增 防止有时候出现显示中文乱码 */
    gbkCode = QTextCodec::codecForName("GB2312");//你完全可以改成GB18080等编码
    ui->setupUi(this);

	/*	建立组界面控件	*/
	_viewAncGroupWidget = new ViewAncGroupWidget;
	
	/*	界面初始化	*/
    init();

	/*	建立定时发送时间定时器	*/
	_sendDataTimer = new QTimer;
	connect(_sendDataTimer, SIGNAL(timeout()), this, SLOT(senDataTimeout()));

	/*	设置定时器时间	*/
	_sendDataTimer->setInterval(SEND_TIME_VALUE);

	_sendDataTimer->start();
	
	printf("AncManageWidget=====\n");
}

AncManageWidget::~AncManageWidget()
{
    delete ui;
}

void AncManageWidget::init()
{
    //menu
    this->setFixedSize(760, 660);
    _menuBar = new QMenuBar(this);
    QRect rect =  this->geometry();
    _menuBar->setGeometry(QRect(0, 0, rect.width(), 30));
    ui->ancManageTab->setGeometry(0,30, rect.width(), rect.height()-30);
    _settingMenu= new QMenu(Mtr("设置"), _menuBar);
    _menuBar->addMenu(_settingMenu);
    _setUpgradeServerAction = new QAction(Mtr("设置升级服务器地址"), this);
    _settingMenu->addAction(_setUpgradeServerAction);
    _ancUpSrvConfigW = new AncUpSrvConfigWidget;
    connect(_setUpgradeServerAction,SIGNAL(triggered(bool)), _ancUpSrvConfigW, SLOT(readSetting()));
    connect(_setUpgradeServerAction,SIGNAL(triggered(bool)), this, SLOT(showUpSrvW()));
    connect(_ancUpSrvConfigW, SIGNAL(verChanged(QString)), this, SLOT(verChanged(QString)));

    readNewVer();

	/*	层组管理	*/
	_setAncGroupParmAction = new QAction(Mtr("层组管理"), this);
	_settingMenu->addAction(_setAncGroupParmAction);

	connect(_setAncGroupParmAction, SIGNAL(triggered(bool)), _viewAncGroupWidget, SLOT(show()));
	

    //table
    this->setWindowTitle(Mtr("基站管理"));
    ui->ancManageTab->setColumnCount(ColumnCount);
    QStringList header;
    header<< "Group" << "AncId" << "X\n(m)" << "Y\n(m)" << "Z\n(m)" << "Addr" << Mtr("版本") << Mtr("状态");
    ui->ancManageTab->setHorizontalHeaderLabels(header);
    ui->ancManageTab->verticalHeader()->setVisible(false);

	ui->ancManageTab->setColumnWidth(ColumnGroup,50);
	ui->ancManageTab->setColumnWidth(ColumnID,100);
	ui->ancManageTab->setColumnWidth(ColumnX,50);
	ui->ancManageTab->setColumnWidth(ColumnY,50);
    ui->ancManageTab->setColumnWidth(ColumnZ,50);
    ui->ancManageTab->setColumnWidth(ColumnAddr,140);
    ui->ancManageTab->setColumnWidth(ColumnVer,200);
    ui->ancManageTab->setColumnWidth(ColumnOlStatus,100);

    initManageConfig();//load ini anc list

    //other
    _periodTimer = new QTimer;
    _periodTimer->setInterval(60000);//每1000ms检测一次在线状态。一分钟
    _periodTimer->start();
    connect(_periodTimer, SIGNAL(timeout()), this, SLOT(periodProcess()));

    _startUpTimer = new QTimer;
    _startUpTimer->setInterval(90*1000);
    connect(_startUpTimer, SIGNAL(timeout()), this, SLOT(startUpTimeout()));

    _reportStaTimer = new QTimer;
    _reportStaTimer->setInterval(10*1000);
    connect(_reportStaTimer, SIGNAL(timeout()), this, SLOT(reportStaTimeout()));
    _start_upgrade_flag = 0;

    connect(ui->ancManageTab, SIGNAL(cellClicked(int, int)), this, SLOT(cellClicked(int,int)));


}


/*
void AncManageWidget::readSetting()
{
    _ancTcpSrvPort = TCPSERVER_PORT;

    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("upgradeserver");
    _upgradeSrvAddr = configfile->value("addr").toString();
    _upgradeSrvPort = configfile->value("port").toInt();
    _upgradeFilePath = configfile->value("file_path").toString();

    //qDebug()<<_ancTcpSrvPort<<_upgradeSrvAddr<<_upgradeSrvPort<<_upgradeFilePath;
    configfile->endGroup();

    delete configfile;
}
*/



/*更新基站地址*/
void AncManageWidget::updateAncAddr(int aid, QString addr, int port)
{
    AncItem item;
    int ret = false;

	printf("==============updateAncAddr=================%s\n", addr.toStdString().data());
	//_udpSocket->writeDatagram(QByteArray("Hello\n"),QHostAddress("192.168.100.199"),5000);
    ret = getAncItem(aid, &item);
    if(ret == false)
    {
        addNewAncItem(aid, addr, port);
    }
    else
    {
        if(addr != item.addr || port != item.port)
        {
            item.addr = addr;
            item.port = port;
            ui->ancManageTab->item(item.ridx, ColumnAddr)->setText(addr + ":" + QString::number(port));
            QString server = addr + QString(":") + QString::number(port);
            item.cli->setServer(server);
        }

        item.lastSec = clock()/1000;
        setAncItem(aid, item);
        ui->ancManageTab->item(item.ridx, ColumnOlStatus)->setText(Mtr("工作中"));

        //qDebug()<<"online:"<<item.online;
        if(item.online == 0)
        {
            item.query_ver_ack = 0;
            item.ver.clear();
            item.cli->startGetVer();
        }
        item.online = 1;
        setAncItem(aid, item);
    }

}

//检测基站在线状态，10s没有数据判断离线
void AncManageWidget::checkOnline()
{
    int sec = clock()/1000;
    AncTableMap::Iterator iter;
    for(iter = _ancS.begin(); iter!=_ancS.end(); ++iter)
    {
        int last =  iter.value().lastSec;
        int row = iter.value().ridx;
        if((sec - last) > 10)
        {

            QString status = ui->ancManageTab->item(row, ColumnOlStatus)->text();
            if(status == QString(("工作中")))
            {
                ui->ancManageTab->item(row, ColumnOlStatus)->setText(Mtr("离线"));
            }
            iter.value().online = 0;
			emit sendDownLineInfo(iter.value().ridx);
        }
    }

}

//检测版本状态
void AncManageWidget::checkVerUpdate()
{
    AncTableMap::Iterator iter;

    for(iter = _ancS.begin(); iter!=_ancS.end(); ++iter)
    {
        if((1 == iter.value().online) && (1 == iter.value().isChecked))//在线
        {
            if(iter.value().ver.isEmpty())//online and ver is empty
            {
                 iter.value().cli->startGetVer();
                 continue;
            }

            if(1 ==  iter.value().up_flag)
            {
               //qDebug()<<"aid:"<< iter.key()<<"iter_ver111111:"<<iter.value().ver << "_ver:"<< _ver;
                if(iter.value().ver != _ver)//online and ver is not empty
                {
                   qDebug()<<"aid:"<<iter.key()<<"start recover";
                   iter.value().cli->startRecover();
                   iter.value().online = 0;
                   iter.value().up_flag = 0;
                }
            }
            else
            {
               //qDebug()<<"aid:"<< iter.key()<<"iter_ver22222:"<<iter.value().ver << "_ver:"<< _ver;
               if(iter.value().ver != _ver)//online and ver is not empty
               {
                   qDebug()<<"aid:"<<iter.key()<<"start update";
                   iter.value().cli->startUpdate();
                   iter.value().online = 0;
               }
            }
        }

    }

}

//1s 周期循环检测在线状态与版本状态
void AncManageWidget::periodProcess()
{
    _periodTimer->start();
    checkOnline();
    checkVerUpdate();
}

//更新anc map
int AncManageWidget::setAncItem(int aid, AncItem item)
{
    AncTableMap ::Iterator iter;
    iter = _ancS.find(aid);
    if(iter != _ancS.end())
    {
        iter.value() = item;
        return true;
    }
    return false;
}

//根据基站获取基站信息
int AncManageWidget::getAncItem(int aid, AncItem* pItem)
{
    AncTableMap::Iterator iter;
    iter = _ancS.find(aid);
    if(iter != _ancS.end())
    {
        *pItem = iter.value();
        return true;
    }
    return false;
}


void AncManageWidget::getAncConfigInfo(int aid, int *group, float *x, float *y, float *z)
{
	QFile file("./TREKanc_config.xml");

	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug(qPrintable(QString("Error: Cannot read file %1 %2").arg("./TREKview_config.xml").arg(file.errorString())));
		return;
	}
	printf("a=================\n");
	QDomDocument doc;
	QString error;
	int errorLine;
	int errorColumn;
	AncItem item;
	getAncItem(aid, &item);

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
						if(aid == (id & 0xf))
						{
							*group = item.group = (e.attribute("Group", "")).toInt(&ok);
							*x = item.x = (e.attribute("x", "0.0")).toDouble(&ok);
							*y = item.y = (e.attribute("y", "0.0")).toDouble(&ok);
							*z = item.z = (e.attribute("z", "0.0")).toDouble(&ok);
					
							//setAncItem(aid, item);
							printf("aaaid = %d item.group = %d item.x = %f item.y = %f item.z = %f\n", aid, item.group, item.x,item.y, item.z);
							return;
						}
					}
				}
			}
			n = n.nextSibling();
		}
	}
	file.close();
}

//添加新基站信息，更新table界面
void AncManageWidget::loadAncItem(int aid, int isChecked, QString ver)
{
    AncItem t_item;
	int _group;
	float _x, _y, _z;
	
    if(getAncItem(aid, &t_item) == true)
    {
        return;
    }


    int newIndex = ui->ancManageTab->rowCount();
    int rowCount = newIndex + 1;
    ui->ancManageTab->setRowCount(rowCount);

#if 1	//20190313 增加标签信息显示

#if 0
	 t_item.group = 0;
	 t_item.x = 0.00;
	 t_item.y = 0.00;
	 t_item.z = 0.00;
#endif
#if 1
	 getAncConfigInfo(aid, &_group, &_x, &_y, &_z);

	 printf("t_item.group = %d, t_item.x = %f, t_item.y = %f, t_item.z = %f\n", _group, _x, _y, _z);
	
	 QTableWidgetItem* itemg = new QTableWidgetItem;
	 itemg->setText(QString::number(_group, 'd', 0));	
	 itemg->setFlags(itemg->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
	 ui->ancManageTab->setItem(newIndex, ColumnGroup, itemg);

	 QTableWidgetItem* itemx = new QTableWidgetItem;
	 itemx->setText(QString::number(_x, 'f', 2)); 
	 itemx->setFlags(itemx->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
	 ui->ancManageTab->setItem(newIndex, ColumnX, itemx);

	 QTableWidgetItem* itemy = new QTableWidgetItem;
	 itemy->setText(QString::number(_y, 'f', 2)); 
	 itemy->setFlags(itemy->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
	 ui->ancManageTab->setItem(newIndex, ColumnY, itemy);

	 QTableWidgetItem* itemz = new QTableWidgetItem;
	 itemz->setText(QString::number(_z, 'f', 2)); 
	 itemz->setFlags(itemz->flags() | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
	 ui->ancManageTab->setItem(newIndex, ColumnZ, itemz);
	 #endif
#endif

    //set aid checked
    QTableWidgetItem* item1 = new QTableWidgetItem;
    if(isChecked)
    {
        item1->setCheckState(Qt::Checked);
    }
    else
    {
        item1->setCheckState(Qt::Unchecked);
    }
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setText(QString::number(aid));
    item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
    ui->ancManageTab->setItem(newIndex, ColumnID, item1);

    //set addr clear
    QString addr;
    addr.clear();
    QTableWidgetItem* item2 = new QTableWidgetItem;
    item2->setText(addr);
    item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
    ui->ancManageTab->setItem(newIndex, ColumnAddr, item2);

    //set ver text
    QTableWidgetItem* item3 = new QTableWidgetItem;
    item3->setText(ver);
    item3->setFlags(item3->flags() & ~Qt::ItemIsEditable);
    ui->ancManageTab->setItem(newIndex, ColumnVer, item3);

    //set online status 0
    QTableWidgetItem* item4 = new QTableWidgetItem;
    item4->setText(Mtr("离线"));
    item4->setFlags(item4->flags() & ~Qt::ItemIsEditable);
    ui->ancManageTab->setItem(newIndex, ColumnOlStatus, item4);

    //set server clear
    QString server;
    server.clear();
    UWB_UdpClient * cli = new UWB_UdpClient(aid, server, &_udpSocket);
    //connect(cli, SIGNAL(sendUpCmdRsut(int, bool)), this, SLOT(sendUpCmdRsut(int, bool)));
    //connect(cli, SIGNAL(sendRecoverCmdRsut(int, bool)), this, SLOT(sendRecoverCmdRsut(int, bool)));
    //connect(cli, SIGNAL(sendGetVerRsut(int,QString)), this, SLOT(sendGetVerRsut(int,QString)));

    //add anc set
    AncItem tmpAnc;
    tmpAnc.ridx = newIndex;
    tmpAnc.addr = addr;
   // tmpAnc.btn = btn;
    tmpAnc.online = 0;
    tmpAnc.cli = cli;
    tmpAnc.lastSec = 0;
    tmpAnc.isChecked = isChecked;
    tmpAnc.query_ver_ack = 0;
    tmpAnc.ver = ver;
	tmpAnc.group = _group;
	tmpAnc.x = _x;
	tmpAnc.x = _y;
	tmpAnc.x = _z;
    _ancS.insert(aid, tmpAnc);
}



//添加新基站信息，更新table界面
void AncManageWidget::addNewAncItem(int aid, QString addr,int port)
{
    int newIndex = ui->ancManageTab->rowCount();
    int rowCount = newIndex + 1;
    ui->ancManageTab->setRowCount(rowCount);

    QTableWidgetItem* item1 = new QTableWidgetItem;
    item1->setCheckState(Qt::Checked);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setText(QString::number(aid));
    item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
    ui->ancManageTab->setItem(newIndex, ColumnID, item1);

    QTableWidgetItem* item2 = new QTableWidgetItem;
    item2->setText(addr + ":" + QString::number(port));
    item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
    ui->ancManageTab->setItem(newIndex, ColumnAddr, item2);

    QTableWidgetItem* item3 = new QTableWidgetItem;
    item3->setText("");
    item3->setFlags(item3->flags() & ~Qt::ItemIsEditable);
    ui->ancManageTab->setItem(newIndex, ColumnVer, item3);

    QTableWidgetItem* item4 = new QTableWidgetItem;
    item4->setText(Mtr("工作中"));
    item4->setFlags(item4->flags() & ~Qt::ItemIsEditable);
    ui->ancManageTab->setItem(newIndex, ColumnOlStatus, item4);

    QString server = addr + QString(":") + QString::number(port);

    UWB_UdpClient * cli = new UWB_UdpClient(aid, server, &_udpSocket);
    //connect(cli, SIGNAL(sendUpCmdRsut(int, bool)), this, SLOT(sendUpCmdRsut(int, bool)));
   // connect(cli, SIGNAL(sendRecoverCmdRsut(int, bool)), this, SLOT(sendRecoverCmdRsut(int, bool)));
    //connect(cli, SIGNAL(sendGetVerRsut(int,QString)), this, SLOT(sendGetVerRsut(int,QString)));

    AncItem tmpAnc;
    tmpAnc.ridx = newIndex;
    tmpAnc.addr = addr;
    tmpAnc.port = port;
    tmpAnc.online = 1;
    tmpAnc.cli = cli;
    tmpAnc.lastSec = clock()/1000;
    tmpAnc.isChecked = 1;
    tmpAnc.ver.clear();
    tmpAnc.query_ver_ack = 0;
    _ancS.insert(aid, tmpAnc);
    tmpAnc.cli->startGetVer();
}


/*
//点击升级
void AncManageWidget::updateBtnClicked()
{
    QPushButton *senderObj=qobject_cast<QPushButton*>(sender());
    if(senderObj == NULL)
    {
        return;
    }
    QModelIndex idx = ui->ancManageTab->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row=idx.row();
    int column = idx.column();

    QString addr  = ui->ancManageTab->item(row, ColumnAddr)->text();
    qDebug()<<"btn"<<row<<column<<addr;
    int aid = ui->ancManageTab->item(row, ColumnID)->text().toInt();
    AncItem item;
    getAncItem(aid, &item);
    if(item.online)
    {
        item.cli->startUpdate();
        item.online = 0;
        setAncItem(aid, item);
    }
}
*/

void AncManageWidget::sendUpCmdRsut(int aid, bool ok)
{
    qDebug()<<"aid:"<<aid <<"result:"<<ok;

    int rowCount = ui->ancManageTab->rowCount();
    int index = 0;
    for(index=0; index<rowCount; index++)
    {
        if(aid == ui->ancManageTab->item(index,ColumnID)->text().toInt())
        {
           break;
        }

    }

    if(index == rowCount)
    {
        qDebug()<<"cmd result err";
        return;
    }

    AncItem item;
    getAncItem(aid, &item);

    if(ok == true)
    {
        ui->ancManageTab->item(index, ColumnOlStatus)->setText(Mtr("升级中..."));
        item.online = 0;

        setAncItem(aid, item);
    }

}

void AncManageWidget::sendRecoverCmdRsut(int aid, bool ok)
{
   //get index
   //qDebug()<<"aid:"<<aid <<"result:"<<ok;

    int rowCount = ui->ancManageTab->rowCount();
    int index = 0;
    for(index=0; index<rowCount; index++)
    {
        if(aid == ui->ancManageTab->item(index,ColumnID)->text().toInt())
        {
             break;
        }
    }

    if(index == rowCount)
    {
        qDebug()<<"cmd result err";
        return;
    }

    AncItem item;
    getAncItem(aid, &item);


    if(ok == true)
    {
        ui->ancManageTab->item(index, ColumnOlStatus)->setText(Mtr("版本回退中..."));
        item.online = 0;
        setAncItem(aid, item);
    }

}


void AncManageWidget::sendGetVerRsut(int aid, QString ver)
{
    AncItem item;
    getAncItem(aid, &item);
    item.ver = ver;
    item.query_ver_ack = 1;
    setAncItem(aid, item);
    ui->ancManageTab->item(item.ridx, ColumnVer)->setText(ver);
    writeManageConfig(aid,item.isChecked, ver);
}

//60s timeout
void AncManageWidget::startUpTimeout()
{


    int succBuf[64] = {0};
    int failBuf[64] = {0};

    int succCnt = 0, failCnt = 0, sum = 0;

    _startUpTimer->stop();
    _reportStaTimer->stop();
    _start_upgrade_flag = 0;

    int status = 0;

    qDebug()<<"start up time out";

    AncTableMap::Iterator iter;
    for(iter = _ancS.begin(); iter!=_ancS.end(); ++iter)
    {
        if(0 == iter.value().isChecked)
            continue;

        if(1 == iter.value().up_flag)
        {
            sum++;

            if((1 == iter.value().online) && (!iter.value().ver.isEmpty()))
            {
                if(iter.value().ver != _ver)//up successed anc
                {
                    qDebug()<<"up failed aid: "<< iter.key();
                    failBuf[failCnt] = iter.key();
                    failCnt++;
                }
                else
                {
                    qDebug()<<"up succed aid: "<< iter.key();
                    succBuf[succCnt] = iter.key();
                    succCnt++;
                }

            }
            else
            {
                qDebug()<<"up failed aid: "<< iter.key();
                failBuf[failCnt] = iter.key();
                failCnt++;
            }

        }
    }


    if(succCnt == sum)
    {
        status = UP_SUCCESS;
    }
    else if(failCnt == sum)
    {
        status = UP_ALL_FAILED;
        startVerBack();
    }
    else
    {
        status = UP_HALF_FAILED;
        startVerBack();
    }

    emit sendUpResp(status, succBuf, succCnt, failBuf, failCnt);



}

//every 10s report upgrade status
void AncManageWidget::reportStaTimeout()
{
	
    if(_start_upgrade_flag)
    {
        _reportStaTimer->start();
    }
    else
    {
        _reportStaTimer->stop();
    }


    int succBuf[64] = {0};
    int failBuf[64] = {0};

    int succCnt = 0, failCnt = 0;
    int sum = 0, status = 0;

    AncTableMap::Iterator iter;
    for(iter = _ancS.begin(); iter!=_ancS.end(); ++iter)
    {

        if(0 == iter.value().isChecked)
            continue;

        if(1 == iter.value().up_flag)
        {
            sum++;

            if((1 == iter.value().online) && (!iter.value().ver.isEmpty()))
            {
                if(iter.value().ver != _ver)//up successed anc
                {
                    qDebug()<<"up failed aid: "<< iter.key();
                    failBuf[failCnt] = iter.key();
                    failCnt++;
                }
                else
                {
                    qDebug()<<"up succed aid: "<< iter.key();
                    succBuf[succCnt] = iter.key();
                    succCnt++;
                }
            }

        }
    }


    if(succCnt == sum)
    {
        status = UP_SUCCESS;
        _startUpTimer->stop();
        _reportStaTimer->stop();
        _start_upgrade_flag = 0;
    }
    else if(failCnt == sum)
    {
        status = UP_ALL_FAILED;
        startVerBack();
        _startUpTimer->stop();
        _reportStaTimer->stop();
        _start_upgrade_flag = 0;
    }
    else if(failCnt > 0)
    {
        status = UP_HALF_FAILED;
        _startUpTimer->stop();
        _reportStaTimer->stop();
        _start_upgrade_flag = 0;
        startVerBack();
    }
    else
    {
        status = UP_DOING;
    }

    emit sendUpResp(status, succBuf, succCnt, failBuf, failCnt);

}

void AncManageWidget::readNewVer()
{
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("upgradeserver");

    QString anc_ver = configfile->value("anc_ver").toString();
    configfile->endGroup();
    delete configfile;

    _ver = anc_ver;
}

//ver go back
void AncManageWidget::startVerBack()
{
    recoverSetting();

    QSettings * configfile;
    configfile = new QSettings("uwbconfig.ini", QSettings::IniFormat);

    configfile->beginGroup("upgradeserver");
    QString anc_ver = configfile->value("anc_ver").toString();
    configfile->endGroup();
    delete configfile;

    _ver = anc_ver;

}

void AncManageWidget::startUpdate(QString ver)
{
    _start_upgrade_flag = 1;
    qDebug()<<"anc manage widget start update";
    _startUpTimer->start();
    _reportStaTimer->start();

    _ver = ver;
    qDebug()<<"ver:"<<_ver;


    AncTableMap::Iterator iter;
    for(iter = _ancS.begin(); iter!=_ancS.end(); ++iter)
    {
        int row = iter.value().ridx;
        qDebug()<<"row1:"<<row;
        if(1 == iter.value().online && 1 == iter.value().isChecked )
        {
            iter.value().up_flag = 1;
            qDebug()<<"row2:"<<row;
            iter.value().online = 0;

            iter.value().cli->startUpdate();
        }
        else
        {
            iter.value().up_flag = 0;
        }
    }

}


void AncManageWidget::recoverSetting()
{

    QString addr;
    QString port;
    QString file_path;
    QString up_time;
    QString anc_ver;
    QSettings * configfile;
    configfile = new QSettings("uwbconfig.ini", QSettings::IniFormat);

    configfile->beginGroup("upgradeserver_back");
    addr = configfile->value("addr").toString();
    port = configfile->value("port").toString();
    file_path = configfile->value("file_path").toString();
    anc_ver = configfile->value("anc_ver").toString();
    up_time = configfile->value("up_time").toString();
    configfile->endGroup();

    configfile->setValue("/upgradeserver/addr", addr);
    configfile->setValue("/upgradeserver/port", port);
    configfile->setValue("/upgradeserver/file_path", file_path);
    configfile->setValue("/upgradeserver/anc_ver", anc_ver);
    configfile->setValue("/upgradeserver/up_time", up_time);


    delete configfile;
}


void AncManageWidget::cellClicked(int r, int c)
{
    //qDebug()<<"r:"<<r<<"c:"<<c;

    if(c == ColumnID) //toggle label
    {
        QTableWidgetItem *pItem = ui->ancManageTab->item(r, c);
        int aid = pItem->text().toInt();
        AncItem item;
        if(getAncItem(aid, &item) == false)
            return;

        item.isChecked = (pItem->checkState() == Qt::Checked) ? 1 : 0;
        setAncItem(aid, item);
        writeManageConfig(aid, item.isChecked, item.ver);


    }
}

void AncManageWidget::showUpSrvW()
{
    _ancUpSrvConfigW->show();
}

void AncManageWidget::verChanged(QString ver)
{
    _ver = ver;
}

void AncManageWidget::writeManageConfig(int aid, int checkState, QString ver)
{
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("ancmanage");
    QString info =  QString::number(checkState) + "," + ver ;
    configfile->setValue(QString::number(aid), info);
    configfile->endGroup();
    delete configfile;
}

void AncManageWidget::initManageConfig()
{
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("ancmanage");
    QStringList groups = configfile->allKeys();

    if(groups.isEmpty())
    {
        qDebug()<<"anc manage is empty";
        return;
    }
     int i = 0;
    int aid;
    QString key;
    QString info;
    QStringList list;
    QString ver;
    int isChecked;
    for(i=0; i< groups.size(); i++)
    {
        key = groups.at(i);
        aid = key.toInt();
        info = configfile->value(key).toString();
        list = info.split(",");
        if(list.size() <1)
        {
            return;
        }

        isChecked = list[0].toInt();

        if(list.size() <2)
        {
           ver.clear();
        }else
        {
           ver = list[1];
        }

        qDebug()<<"aid:"<<aid << "checkstate:"<<isChecked<<"ver:"<<ver;

        loadAncItem(aid, isChecked,ver);
    }

    configfile->endGroup();
    delete configfile;
}

/*************************************************************
*	Name:		senDataTimeout
*	Func:		引擎定时向接入基站发送时间同步
*	Input:		void
*	Output:		void
*	Return:		void
**************************************************************/
void AncManageWidget::senDataTimeout(void)
{
	AncItem item;
	QString cmd_send_time;
	QDateTime current_data_time = QDateTime::currentDateTime(); 
	
	//QSettings * configfile;

	int value;
	int i;
	bool ret = false;

	/*	获取基站个数	*/
	QSettings * configfile;
	configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
	configfile->beginGroup("baseMun");
	value = configfile->value("baseMun").toInt();
	configfile->endGroup();
	delete configfile;

	QString current_msec = current_data_time.toString("zzz");
	/*	构建命令	*/
	cmd_send_time = "SET_SYN_TIME=" + current_msec;


	//printf("current_msec1 = %s\n", current_msec.toStdString().data());
	/*	轮询向在线的设备发送	*/
    for(i = 0; i < value; i++)
	{
		ret = getAncItem(i, &item);
		//_udpSocket->writeDatagram(cmd_send_time.toLatin1(),QHostAddress("192.168.100.199"),5000);
		//printf("addr = %s port = %d\n", item.addr.toStdString().data(), item.port);
		if(((i != 0)  && (i % 20) == 0))
		{
			current_data_time = QDateTime::currentDateTime(); 
			current_msec = current_data_time.toString("zzz");
			//printf("current_msec2 = %s\n", current_msec.toStdString().data());
		}
		#if 1
		if(true == ret)
		{
			//_udpSocket->writeDatagram(cmd_send_time.toLatin1(),QHostAddress(item.addr),51000);	//暂时固定端口发送
		}
		#endif
	}

	//emit sendDownLineInfo(11);
	//printf("sendDownLineInfo\n");
   // printf("cmd === %s _rtlsclientValue._ancMaxShowCount = %d\n", cmd_send_time.toStdString().data(), value);

	//printf("senDataTimeout %d\n", current_msec.toInt());
}

/*************************************************************
*	Name:		initAncManage
*	Func:		基站信息初始化
*	Input:		group:	基站所属组	x,y,z:基站坐标
*	Output:		void
*	Return:		void
**************************************************************/
void AncManageWidget::initAncInfoManage(int ancId, int group, double x, double y, double z)
{
#if 0
	printf("initAncInfoManage ancId = %d, group = %d, x=%f, y=%f, z=%f\n", ancId, group, x, y, z);


	int rowCount = ui->ancManageTab->rowCount();
	int index = 0;
	for(index = 0; index < rowCount; index++)
	{
		if(ancId == ui->ancManageTab->item(index,ColumnID)->text().toInt())
		{
		   break;
		}
	}

	if(index == rowCount)
	{
		qDebug()<<"cmd result err";
		return;
	}

	printf("ancId = %d index = %d\n", ancId, index);

	AncItem item;
	getAncItem(ancId, &item);

	//ui->ancManageTab->item(index, ColumnGroup)->setText(QString::number(group, 'd', 0));
	//ui->ancManageTab->item(index, ColumnX)->setText(QString::number(x, 'f', 2));
	//ui->ancManageTab->item(index, ColumnY)->setText(QString::number(y, 'f', 2));
	//ui->ancManageTab->item(index, ColumnZ)->setText(QString::number(z, 'f', 2));
	
	item.group = group;
	item.x = x;
	item.y = y;
	item.z = z;

	setAncItem(ancId, item);
#endif
}



