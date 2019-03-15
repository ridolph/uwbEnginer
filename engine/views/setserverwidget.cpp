#include "setserverwidget.h"
#include "ui_setserverwidget.h"
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QTextCodec>


QTextCodec *serGbkCode;
#define SerMtr(s) (serGbkCode->toUnicode(s))


setServerWidget::setServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setServerWidget)
{
    ui->setupUi(this);

	/* 新增 防止有时候出现显示中文乱码 */
    serGbkCode = QTextCodec::codecForName("GB2312");//你完全可以改成GB18080等编码

    QRegExp regx;
    QRegExpValidator *pExpValidator;
    regx = QRegExp("[0-9]{0,5}");
    pExpValidator =new QRegExpValidator(regx, this);
    ui->portEdit->setValidator(pExpValidator);
	ui->portEdit_2->setValidator(pExpValidator);

    regx = QRegExp(".{0,64}");
    pExpValidator =  new QRegExpValidator(regx, this);
    ui->addrEdit->setValidator(pExpValidator);
	ui->addrEdit_2->setValidator(pExpValidator);

    this->setWindowTitle(SerMtr("设置tcp服务器"));
    this->setFixedSize(500,400);
    readSetting();
    connect(ui->cancelBtn, SIGNAL(clicked(bool)), this, SLOT(close()));

}

setServerWidget::~setServerWidget()
{
    delete ui;
}

void setServerWidget::readSetting()
{
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("javatcpserver");
    QString inaddr = configfile->value("inaddr").toString();
    if(inaddr.isEmpty())
    {
        qDebug()<<"uwbconfig.ini inserver impty";
        QMessageBox::warning(this,"警告","uwbconfig.ini inserver impty!");

    }

	QString outaddr = configfile->value("outaddr").toString();
    if(outaddr.isEmpty())
    {
        qDebug()<<"uwbconfig.ini outserver impty";
        QMessageBox::warning(this,"警告","uwbconfig.ini outserver impty!");
    }
    int inport = configfile->value("inport").toInt();
	int outport = configfile->value("outport").toInt();
    delete configfile;

    ui->addrEdit->clear();
    ui->portEdit->clear();
	ui->addrEdit_2->clear();
    ui->portEdit_2->clear();
    ui->addrEdit->insert(inaddr);
    ui->portEdit->insert(QString::number(inport));
	ui->addrEdit_2->insert(outaddr);
    ui->portEdit_2->insert(QString::number(outport));
}

void setServerWidget::on_setBtn_clicked()
{
    QString inaddr = ui->addrEdit->text();
    int inport = ui->portEdit->text().toInt();
    qDebug()<<inaddr<<inport;

	QString outaddr = ui->addrEdit_2->text();
    int outport = ui->portEdit_2->text().toInt();
    qDebug()<<outaddr<<outport;
	
    emit setServer(inaddr, inport);
	emit setOutServer(outaddr,outport);
    close();
}
