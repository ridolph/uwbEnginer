// -------------------------------------------------------------------------------------------------------------------
//
//  File: ViewSettingsWidget.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#ifndef VIEWSETTINGSWIDGET_H
#define VIEWSETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class ViewSettingsWidget;
}

class ViewSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewSettingsWidget(QWidget *parent = 0);
    ~ViewSettingsWidget();

    int applyFloorPlanPic(const QString &path);
    void readFilter();
    void readVec();
    void readUdpPort();

signals:
    void saveViewSettings(void);
    void udpPortChanged(void);

protected slots:
    void onReady();

    void floorplanOpenClicked();
    void updateLocationFilter(int index);
    void enableFiltering(void);
    void originClicked();
    void scaleClicked();

    void gridShowClicked();
    void originShowClicked();
    void tagHistoryShowClicked();

    void saveFPClicked();
    void tagAncTableShowClicked();
    void useAutoPosClicked();
    void showGeoFencingModeClicked();
    void showNavigationModeClicked();
    void alarmSetClicked();

    void zone1ValueChanged(double);
    void zone2ValueChanged(double);
    void zone1EditFinished(void);
    void zone2EditFinished(void);
    void tagHistoryNumberValueChanged(int);

    void showOriginGrid(bool orig, bool grid);
    void getFloorPlanPic(void);
    void showSave(bool);

    void setTagHistory(int h);
    void loggingClicked(void);
    void dsptcpLog(QString str);
    void klmanftChanged();
    void vecChanged(int index);


private slots:
    void on_clearDebugBtn_clicked();

    void on_cleanHisBtn_clicked();

    void on_changeUdpBtn_clicked();

private:
    Ui::ViewSettingsWidget *ui;

    bool _logging ;
    bool _floorplanOpen ;
};

#endif // VIEWSETTINGSWIDGET_H
