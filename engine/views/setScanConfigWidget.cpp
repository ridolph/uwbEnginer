#include "setScanConfigWidget.h"
#include "ui_setScanConfigWidget.h"
#include <QSettings>
#include <QDebug>
#include <QMessageBox>

int  g_signal_vanish_timeout  = 0;//信号消失超时
int  g_stay_timeout = 0;//厕所滞留超时
int  g_other_cell_timeout = 0;//串监超时
int  g_jumpAllowCount = 0;//最大允许跳变点数
int g_locCorrectEnable = 0;

setScanConfigWidget::setScanConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setScanConfigWidget)
{
    ui->setupUi(this);

    this->setWindowTitle("设置扫描参数");
    this->setFixedSize(276,290);

    QRegExp regx;
    QRegExpValidator *pExpValidator;
    regx = QRegExp("[0-9]{0,5}");
    pExpValidator =new QRegExpValidator(regx, this);
    ui->othCellEdit->setValidator(pExpValidator);
    ui->vanishEdit->setValidator(pExpValidator);
    ui->stayEdit->setValidator(pExpValidator);

    regx = QRegExp("[0-9]{0,2}");
    pExpValidator =new QRegExpValidator(regx, this);
    ui->jumpCountEdit->setValidator(pExpValidator);

    readSetting();

    connect(ui->locCorrectEnableBox, SIGNAL(stateChanged(int)), this, SLOT(locCorrectProcess()));
#if 1 //不可更改
    ui->othCellEdit->setDisabled(1);
    ui->vanishEdit->setDisabled(1);
    ui->stayEdit->setDisabled(1);
    ui->jumpCountEdit->setDisabled(1);
    ui->locCorrectEnableBox->setDisabled(1);
    ui->locCorrectEnableBox->setChecked(0);
#endif
}

setScanConfigWidget::~setScanConfigWidget()
{
    delete ui;
}

void setScanConfigWidget::locCorrectProcess()
{
    bool check = ui->locCorrectEnableBox->isChecked();
    if(ui->locCorrectEnableBox->isChecked())
    {
        ui->jumpCountEdit->setEnabled(1);
    }
    else
    {
        ui->jumpCountEdit->setEnabled(0);
    }
}

void setScanConfigWidget::readSetting()
{
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("scanconfig");
    g_stay_timeout = configfile->value("staytimeout").toInt();
    if(g_stay_timeout == 0)//判断是否为空
    {
        qDebug()<<"uwbconfig.ini scanconfig err";
    }
    g_other_cell_timeout = configfile->value("othercelltimeout").toInt();
    g_signal_vanish_timeout = configfile->value("signalvanishtimeout").toInt();

    g_locCorrectEnable = configfile->value("loccorrectenable").toBool();
    g_jumpAllowCount = configfile->value("jumpallowcount").toInt();
    if(g_jumpAllowCount == 0)
    {
        qDebug()<<"uwbconfig.ini jumpallowcount 0";
    }
    //qDebug()<<"jumpcount:"<<g_jumpAllowCount<<"loccorrectenable"<<g_locCorrectEnable;
    configfile->endGroup();

    delete configfile;

    ui->stayEdit->clear();
    ui->stayEdit->insert(QString::number(g_stay_timeout));
    ui->othCellEdit->clear();
    ui->othCellEdit->insert(QString::number(g_other_cell_timeout));
    ui->vanishEdit->clear();
    ui->vanishEdit->insert(QString::number(g_signal_vanish_timeout));
    ui->jumpCountEdit->clear();
    ui->jumpCountEdit->insert(QString::number(g_jumpAllowCount));
    ui->locCorrectEnableBox->setChecked(g_locCorrectEnable);

    if(false == g_locCorrectEnable)
    {
       ui->jumpCountEdit->setEnabled(false);
    }

}

void setScanConfigWidget::on_okConfigBtn_clicked()
{
    int tmp_stay_timeout;
    int tmp_other_timeout;
    int tmp_vanish_timeout;
    int tmp_jump_count;
    bool tmp_enable1 ;
    bool tmp_enable2;


    tmp_stay_timeout = ui->stayEdit->text().toInt();
    tmp_other_timeout = ui->othCellEdit->text().toInt();
    tmp_vanish_timeout = ui->vanishEdit->text().toInt();
    tmp_jump_count  = ui->jumpCountEdit->text().toInt();
    tmp_enable1 = ui->locCorrectEnableBox->isChecked();

    if((tmp_stay_timeout <= 0)||(tmp_other_timeout <= 0)||(tmp_vanish_timeout <= 0))
    {
        QMessageBox::warning(this,"警告","参数不正确!");
        return ;
    }

    g_stay_timeout = tmp_stay_timeout;
    g_other_cell_timeout = tmp_other_timeout;
    g_signal_vanish_timeout = tmp_vanish_timeout;
    g_jumpAllowCount = tmp_jump_count;
    g_locCorrectEnable = tmp_enable1;
    writeSetting();

    close();
}

void setScanConfigWidget::on_cancelConfigBtn_clicked()
{
    close();
}

void setScanConfigWidget::writeSetting()
{
    //qDebug()<<"stay:"<<g_stay_timeout<<"other:"<<g_other_cell_timeout<<"vanish:"<<g_signal_vanish_timeout<<"jumpcount"\
            <<g_jumpAllowCount;//<<"klmanenable"<<g_klmanEnable;
    QSettings *configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->setValue("/scanconfig/staytimeout", g_stay_timeout);
    configfile->setValue("/scanconfig/othercelltimeout", g_other_cell_timeout);
    configfile->setValue("/scanconfig/signalvanishtimeout",g_signal_vanish_timeout);
    configfile->setValue("/scanconfig/jumpallowcount",g_jumpAllowCount);
    configfile->setValue("/scanconfig/loccorrectenable",g_locCorrectEnable);
    delete configfile;
}

