#ifndef MY_LOG_H
#define MY_LOG_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QTimer>
#include <QFile>

/***************************************************
 *     qInstallMessageHandler(Mylog::outputMessage);
***************************************************/

class  Mylog: public QObject
{
    Q_OBJECT
public :
    Mylog();
    ~Mylog();

    static void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static void createLog();
    static void writeLog(QString log);
    static void init();
    static void checkClearLog();
public:
    static QFile *_file;
    static int _lastHour;
    static int _resvDays;

};






#endif
