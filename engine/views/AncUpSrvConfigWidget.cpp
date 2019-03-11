#include "AncUpSrvConfigWidget.h"
#include "ui_AncUpSrvConfigWidget.h"
#include <QSettings>

AncUpSrvConfigWidget::AncUpSrvConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AncUpSrvConfigWidget)
{
    ui->setupUi(this);
}

AncUpSrvConfigWidget::~AncUpSrvConfigWidget()
{
    delete ui;
}

void AncUpSrvConfigWidget::on_okBtn_clicked()
{
#if 1
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->setValue("/upgradeserver/addr", ui->upSrvAddrEdit->text());
    configfile->setValue("/upgradeserver/port", ui->upSrvPortEdit->text());
    configfile->setValue("/upgradeserver/file_path", ui->upFilePathEdit->text());
    configfile->setValue("/upgradeserver/anc_ver", ui->verEdit->text());
    delete configfile;

    QString ver = ui->verEdit->text();
    emit verChanged(ver);
#endif
    this->close();
}

void AncUpSrvConfigWidget::on_cancelBtn_clicked()
{
    this->close();
}

void AncUpSrvConfigWidget::readSetting()
{


    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("upgradeserver");
    QString addr = configfile->value("addr").toString();
    QString port = configfile->value("port").toString();
    QString filePath = configfile->value("file_path").toString();
    QString ver = configfile->value("anc_ver").toString();
    configfile->endGroup();
    delete configfile;

    ui->upSrvAddrEdit->clear();
    ui->upSrvPortEdit->clear();
    ui->upFilePathEdit->clear();
    ui->verEdit->clear();
    ui->upSrvAddrEdit->insert(addr);
    ui->upSrvPortEdit->insert(port);
    ui->upFilePathEdit->insert(filePath);
    ui->verEdit->insert(ver);
}
