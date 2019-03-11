// -------------------------------------------------------------------------------------------------------------------
//
//  File: ViewSettingsWidget.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "ViewSettingsWidget.h"
#include "ui_ViewSettingsWidget.h"

#include "RTLSDisplayApplication.h"
#include "QPropertyModel.h"
#include "ViewSettings.h"
#include "OriginTool.h"
#include "ScaleTool.h"
#include "GraphicsView.h"
#include "GraphicsWidget.h"

#include <QFileDialog>
#include <QMessageBox>

int g_klmanEnable = 0;
int g_vec = 3;
extern int g_udp_port;

/*  定义转换编码格式的全局变量   */
QTextCodec *gbCode;

#define Mtr1(s) (gbCode->toUnicode(s))

ViewSettingsWidget::ViewSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewSettingsWidget),
    _floorplanOpen(false)
{
    ui->setupUi(this);

    /* 新增 防止有时候出现显示中文乱码 */
    gbCode = QTextCodec::codecForName("GB2312");//你完全可以改成GB18080等编码

    //ui->tabWidget->setCurrentIndex(0);
    //ui->tabWidget->removeTab(2);
    readFilter();
    readVec();
    readUdpPort();
    QObject::connect(ui->klmanfilterBox, SIGNAL(stateChanged(int)), this, SLOT(klmanftChanged()));
    QObject::connect(ui->vecBox, SIGNAL(currentIndexChanged(int)), this, SLOT(vecChanged(int)));


    QObject::connect(ui->floorplanOpen_pb, SIGNAL(clicked()), this, SLOT(floorplanOpenClicked()));

    QObject::connect(ui->scaleX_pb, SIGNAL(clicked()), this, SLOT(scaleClicked()));
    QObject::connect(ui->scaleY_pb, SIGNAL(clicked()), this, SLOT(scaleClicked()));
    QObject::connect(ui->origin_pb, SIGNAL(clicked()), this, SLOT(originClicked()));

    QObject::connect(ui->saveFP, SIGNAL(clicked()), this, SLOT(saveFPClicked()));
    QObject::connect(ui->gridShow, SIGNAL(clicked()), this, SLOT(gridShowClicked()));
    QObject::connect(ui->showOrigin, SIGNAL(clicked()), this, SLOT(originShowClicked()));
    QObject::connect(ui->showTagHistory, SIGNAL(clicked()), this, SLOT(tagHistoryShowClicked()));
    QObject::connect(ui->showGeoFencingMode, SIGNAL(clicked()), this, SLOT(showGeoFencingModeClicked()));
    QObject::connect(ui->showNavigationMode, SIGNAL(clicked()), this, SLOT(showNavigationModeClicked()));

    QObject::connect(ui->useAutoPos, SIGNAL(clicked()), this, SLOT(useAutoPosClicked()));
    QObject::connect(ui->showTagTable, SIGNAL(clicked()), this, SLOT(tagAncTableShowClicked()));
    QObject::connect(ui->showAnchorTable, SIGNAL(clicked()), this, SLOT(tagAncTableShowClicked()));
    QObject::connect(ui->showAnchorTagCorrectionTable, SIGNAL(clicked()), this, SLOT(tagAncTableShowClicked()));

    QObject::connect(ui->zone1, SIGNAL(editingFinished()), this, SLOT(zone1EditFinished()));
    QObject::connect(ui->zone2, SIGNAL(editingFinished()), this, SLOT(zone2EditFinished()));

    QObject::connect(ui->zone1, SIGNAL(valueChanged(double)), this, SLOT(zone1ValueChanged(double)));
    QObject::connect(ui->zone2, SIGNAL(valueChanged(double)), this, SLOT(zone2ValueChanged(double)));
    QObject::connect(ui->inAlarm, SIGNAL(clicked()), this, SLOT(alarmSetClicked()));
    QObject::connect(ui->outAlarm, SIGNAL(clicked()), this, SLOT(alarmSetClicked()));

    QObject::connect(ui->tagHistoryN, SIGNAL(valueChanged(int)), this, SLOT(tagHistoryNumberValueChanged(int)));

    QObject::connect(RTLSDisplayApplication::viewSettings(), SIGNAL(showSave(bool)), this, SLOT(showSave(bool)));
    QObject::connect(RTLSDisplayApplication::viewSettings(), SIGNAL(showGO(bool, bool)), this, SLOT(showOriginGrid(bool, bool)));
    QObject::connect(RTLSDisplayApplication::viewSettings(), SIGNAL(setFloorPlanPic()), this, SLOT(getFloorPlanPic()));
    QObject::connect(RTLSDisplayApplication::client(), SIGNAL(enableFiltering()), this, SLOT(enableFiltering()));

    QObject::connect(ui->logging_pb, SIGNAL(clicked()), this, SLOT(loggingClicked()));


    _logging = false ;

    ui->label_logfile->setText("");
    if(_logging)
    {
        ui->logging_pb->setText("Stop");
        ui->label_logingstatus->setText("Logging enabled.");
    }
    else
    {
        ui->logging_pb->setText("Start");
        ui->label_logingstatus->setText("Logging disabled.");
    }

    RTLSDisplayApplication::connectReady(this, "onReady()");
}

void ViewSettingsWidget::onReady()
{
    QPropertyDataWidgetMapper *mapper = QPropertyModel::newMapper(RTLSDisplayApplication::viewSettings(), this);
    mapper->addMapping(ui->gridWidth_sb, "gridWidth");
    mapper->addMapping(ui->gridHeight_sb, "gridHeight");

    mapper->addMapping(ui->floorplanFlipX_cb, "floorplanFlipX", "checked");
    mapper->addMapping(ui->floorplanFlipY_cb, "floorplanFlipY", "checked");
    mapper->addMapping(ui->gridShow, "showGrid", "checked");
    mapper->addMapping(ui->showOrigin, "showOrigin", "checked");

    mapper->addMapping(ui->floorplanXOff_sb, "floorplanXOffset");
    mapper->addMapping(ui->floorplanYOff_sb, "floorplanYOffset");

    mapper->addMapping(ui->floorplanXScale_sb, "floorplanXScale");
    mapper->addMapping(ui->floorplanYScale_sb, "floorplanYScale");
    mapper->toFirst();

    QObject::connect(ui->floorplanFlipX_cb, SIGNAL(clicked()), mapper, SLOT(submit())); // Bug with QDataWidgetMapper (QTBUG-1818)
    QObject::connect(ui->floorplanFlipY_cb, SIGNAL(clicked()), mapper, SLOT(submit()));
    QObject::connect(ui->gridShow, SIGNAL(clicked()), mapper, SLOT(submit())); // Bug with QDataWidgetMapper (QTBUG-1818)
    QObject::connect(ui->showOrigin, SIGNAL(clicked()), mapper, SLOT(submit()));

    //by default the Geo-Fencing is OFF

    ui->showTagHistory->setChecked(true);

    ui->zone1->setDisabled(true);
    ui->zone2->setDisabled(true);
    ui->label_z1->setDisabled(true);
    ui->label_z2->setDisabled(true);
    ui->outAlarm->setDisabled(true);
    ui->inAlarm->setDisabled(true);

    ui->tabWidget->setCurrentIndex(0);

    RTLSDisplayApplication::graphicsWidget()->zone1Value(ui->zone1->value());
    RTLSDisplayApplication::graphicsWidget()->zone2Value(ui->zone2->value());
    RTLSDisplayApplication::graphicsWidget()->setAlarm(ui->inAlarm->isChecked(), ui->outAlarm->isChecked());

    ui->filtering->setEnabled(false);//lyz 去掉自带的滤波算法
    ui->filtering->addItems(RTLSDisplayApplication::client()->getLocationFilters());
    QObject::connect(ui->filtering, SIGNAL(currentIndexChanged(int)), this, SLOT(updateLocationFilter(int)));
}

ViewSettingsWidget::~ViewSettingsWidget()
{
    delete ui;
}

void ViewSettingsWidget::readFilter()
{
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("filter");
    g_klmanEnable = configfile->value("klman").toBool();
    configfile->endGroup();

    ui->klmanfilterBox->setChecked(g_klmanEnable);
}

void ViewSettingsWidget::readVec()
{
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("vec");
    g_vec = configfile->value("vec").toInt();
    configfile->endGroup();
    delete  configfile;

    if(1 == g_vec)
    {
        ui->vecBox->setCurrentIndex(0);
    }
    else
    {
        ui->vecBox->setCurrentIndex(1);
    }
}

void ViewSettingsWidget::readUdpPort()
{
    QSettings * configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("udpport");
    g_udp_port = configfile->value("port").toInt();
    ui->udpPortEdit->setText(QString::number(g_udp_port));
    configfile->endGroup();
    delete  configfile;
}


void ViewSettingsWidget::klmanftChanged()
{
    if(ui->klmanfilterBox->isChecked())
    {
       g_klmanEnable = 1;
    }
    else
    {
        g_klmanEnable = 0;
    }

    QSettings *configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->setValue("/filter/klman", g_klmanEnable);
    delete configfile;
}

void ViewSettingsWidget::vecChanged(int index)
{
    if(index == 0)
    {
        g_vec = 1;
    }
    else
    {
        g_vec = 3;
    }

    QSettings *configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->setValue("/vec/vec", g_vec);
    delete configfile;
}

void ViewSettingsWidget::enableFiltering(void)
{
     ui->filtering->setEnabled(true);
}

void ViewSettingsWidget::updateLocationFilter(int index)
{
     RTLSDisplayApplication::client()->setLocationFilter(index);
}

int ViewSettingsWidget::applyFloorPlanPic(const QString &path)
{
    QPixmap pm(path);

    if (pm.isNull())
    {
        //QMessageBox::critical(this, "Could not load floor plan", QString("Failed to load image : %1").arg(path));
        return -1;
    }

    ui->floorplanPath_lb->setText(QFileInfo(path).fileName());
    RTLSDisplayApplication::viewSettings()->setFloorplanPixmap(pm);
    _floorplanOpen = true;
    ui->floorplanOpen_pb->setText("Clear");

    return 0;
}


void ViewSettingsWidget::getFloorPlanPic()
{
    applyFloorPlanPic(RTLSDisplayApplication::viewSettings()->getFloorplanPath());
}

void ViewSettingsWidget::floorplanOpenClicked()
{
    if(_floorplanOpen == false)
    {
        QString path = QFileDialog::getOpenFileName(this, "Open Bitmap", QString(), "Image (*.png *.jpg *.jpeg *.bmp)");
        if (path.isNull()) return;

        if(applyFloorPlanPic(path) == 0) //if OK set/save the path string
        {
            RTLSDisplayApplication::viewSettings()->floorplanShow(true);
            RTLSDisplayApplication::viewSettings()->setFloorplanPath(path);
        }
        _floorplanOpen = true;
        ui->floorplanOpen_pb->setText("Clear");
    }
    else
    {
       RTLSDisplayApplication::viewSettings()->floorplanShow(false);
       RTLSDisplayApplication::viewSettings()->clearSettings();
       _floorplanOpen = false;
       ui->floorplanOpen_pb->setText("Open");
       ui->floorplanFlipX_cb->setChecked(false);
       ui->floorplanFlipY_cb->setChecked(false);
       ui->floorplanXScale_sb->setValue(0.0);
       ui->floorplanYScale_sb->setValue(0.0);
       ui->floorplanXOff_sb->setValue(0.0);
       ui->floorplanYOff_sb->setValue(0.0);
       ui->floorplanPath_lb->setText("");
    }
}

void ViewSettingsWidget::showOriginGrid(bool orig, bool grid)
{
    Q_UNUSED(orig)

    ui->gridShow->setChecked(grid);
    ui->showOrigin->setChecked(orig);
}

void ViewSettingsWidget::gridShowClicked()
{
    RTLSDisplayApplication::viewSettings()->setShowGrid(ui->gridShow->isChecked());
}

void ViewSettingsWidget::originShowClicked()
{
    RTLSDisplayApplication::viewSettings()->setShowOrigin(ui->showOrigin->isChecked());
}

void ViewSettingsWidget::showNavigationModeClicked()
{
    if(ui->showNavigationMode->isChecked())
    {
        ui->showGeoFencingMode->setChecked(false);
        showGeoFencingModeClicked();
    }
    else
    {
        ui->showGeoFencingMode->setChecked(true);
        showGeoFencingModeClicked();
    }
}


void ViewSettingsWidget::showGeoFencingModeClicked()
{
    RTLSDisplayApplication::graphicsWidget()->showGeoFencingMode(ui->showGeoFencingMode->isChecked());

    if(ui->showGeoFencingMode->isChecked())
    {
        ui->showTagHistory->setDisabled(true);
        ui->tagHistoryN->setDisabled(true);

        ui->zone1->setEnabled(true);
        ui->zone2->setEnabled(true);
        ui->label_z1->setEnabled(true);
        ui->label_z2->setEnabled(true);
        ui->outAlarm->setEnabled(true);
        ui->inAlarm->setEnabled(true);

        ui->showNavigationMode->setChecked(false);
        //set auto positioning to off when in geo-fencing mode
        RTLSDisplayApplication::client()->setUseAutoPos(false);
        ui->useAutoPos->setDisabled(true);
    }
    else
    {
        ui->showTagHistory->setDisabled(false);
        ui->tagHistoryN->setDisabled(false);

        ui->zone1->setDisabled(true);
        ui->zone2->setDisabled(true);
        ui->label_z1->setDisabled(true);
        ui->label_z2->setDisabled(true);
        ui->outAlarm->setDisabled(true);
        ui->inAlarm->setDisabled(true);

        ui->useAutoPos->setDisabled(false);
        useAutoPosClicked();

        ui->showNavigationMode->setChecked(true);
    }

}

void ViewSettingsWidget::tagHistoryNumberValueChanged(int value)
{
    RTLSDisplayApplication::graphicsWidget()->tagHistoryNumber(value);
}

void ViewSettingsWidget::zone1EditFinished(void)
{
    RTLSDisplayApplication::graphicsWidget()->zone1Value(ui->zone1->value());
}

void ViewSettingsWidget::zone2EditFinished(void)
{
    RTLSDisplayApplication::graphicsWidget()->zone2Value(ui->zone2->value());
}

void ViewSettingsWidget::zone1ValueChanged(double value)
{
    RTLSDisplayApplication::graphicsWidget()->zone1Value(value);
}

void ViewSettingsWidget::zone2ValueChanged(double value)
{
    RTLSDisplayApplication::graphicsWidget()->zone2Value(value);
}

void ViewSettingsWidget::useAutoPosClicked()
{
    RTLSDisplayApplication::client()->setUseAutoPos(ui->useAutoPos->isChecked());

    RTLSDisplayApplication::graphicsWidget()->anchTableEditing(!ui->useAutoPos->isChecked());
}

void ViewSettingsWidget::tagAncTableShowClicked()
{
    RTLSDisplayApplication::graphicsWidget()->setShowTagAncTable(ui->showAnchorTable->isChecked(),
                                                                 ui->showTagTable->isChecked(),
                                                                 ui->showAnchorTagCorrectionTable->isChecked());
}

void ViewSettingsWidget::setTagHistory(int h)
{
    ui->tagHistoryN->setValue(h);
}


void ViewSettingsWidget::tagHistoryShowClicked()
{
    RTLSDisplayApplication::graphicsWidget()->setShowTagHistory(ui->showTagHistory->isChecked());
}


void ViewSettingsWidget::loggingClicked(void)
{
    if(_logging == false)
    {
        _logging = true ;
        RTLSDisplayApplication::client()->openLogFile("");
        ui->logging_pb->setText("Stop");
        ui->label_logingstatus->setText("Logging enabled.");
        ui->label_logfile->setText(RTLSDisplayApplication::client()->getLogFilePath());
    }
    else
    {
        RTLSDisplayApplication::client()->closeLogFile();
        ui->logging_pb->setText("Start");
        ui->label_logingstatus->setText("Logging disabled.");
        ui->label_logfile->setText("");
        ui->saveFP->setChecked(false);
        _logging = false ;
    }
}

void ViewSettingsWidget::dsptcpLog(QString str)
{
    ui->tcpDebugBrow->moveCursor(QTextCursor::End);
    ui->tcpDebugBrow->insertPlainText(str);
    ui->tcpDebugBrow->moveCursor(QTextCursor::End);
}


void ViewSettingsWidget::on_clearDebugBtn_clicked()
{
    ui->tcpDebugBrow->clear();
}

void ViewSettingsWidget::alarmSetClicked()
{
    RTLSDisplayApplication::graphicsWidget()->setAlarm(ui->inAlarm->isChecked(), ui->outAlarm->isChecked());
}

void ViewSettingsWidget::saveFPClicked()
{
    RTLSDisplayApplication::viewSettings()->setSaveFP(ui->saveFP->isChecked());

    if(ui->saveFP->isChecked())
    {
        //save the current settings when clicked
       emit saveViewSettings();
    }
}

void ViewSettingsWidget::showSave(bool save)
{
    ui->saveFP->setChecked(save);
}

void ViewSettingsWidget::originClicked()
{
    OriginTool *tool = new OriginTool(this);
    QObject::connect(tool, SIGNAL(done()), tool, SLOT(deleteLater()));
    RTLSDisplayApplication::graphicsView()->setTool(tool);
}

void ViewSettingsWidget::scaleClicked()
{
    ScaleTool *tool = NULL;

    if (QObject::sender() == ui->scaleX_pb)
        tool = new ScaleTool(ScaleTool::XAxis, this);
    else if (QObject::sender() == ui->scaleY_pb)
        tool = new ScaleTool(ScaleTool::YAxis, this);

    QObject::connect(tool, SIGNAL(done()), tool, SLOT(deleteLater()));
    RTLSDisplayApplication::graphicsView()->setTool(tool);
}



void ViewSettingsWidget::on_cleanHisBtn_clicked()
{
    tagHistoryNumberValueChanged(ui->tagHistoryN->value());
}

void ViewSettingsWidget::on_changeUdpBtn_clicked()
{
    QString str = ui->udpPortEdit->text();
    if(str.isEmpty())
        return;

    g_udp_port = str.toInt();

    QSettings *configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->setValue("/udpport/port", g_udp_port);
    delete configfile;

    emit udpPortChanged();
}
