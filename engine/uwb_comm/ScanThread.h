#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include <QThread>
#include <QTimer>
#include <QObject>
#include <QMap>
#include <QDebug>
#include "tagInfo/tagInfo.h"

#define Scan_Debug qDebug

#define START_SCAN_WAIT_TIME_S  6
#define SCAN_PERIOD_MS        500//ÂÖÑ¯Ê±¼ä


class ScanThread : public QThread
{
    Q_OBJECT
public:
    explicit ScanThread(QObject *parent = 0);
    ~ScanThread();
    void scan();
signals:
    void SendCellOnlineStatus(int tagId, uint8_t status);
    void SendAlarm(int tagId, ALARM_TYPE alarmType, uint8_t op);
protected:
    virtual void run();
};
#endif // SCANTHREAD_H
