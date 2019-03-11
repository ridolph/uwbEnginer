
#include "Mylog.h"
#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QTextCodec>



#define LOG_FILE_MAX_SIZE  209715200 //200*1024*1024
QFile * Mylog::_file = NULL;
int Mylog::_resvDays = 30;
int Mylog::_lastHour = 0;


Mylog::Mylog()
{
}

Mylog::~Mylog()
{

}

/***自动清理一个月之前的日志记录****/
void Mylog::checkClearLog()
{
    QString baseName;
    QDateTime file_time;
    QDateTime cur_time = QDateTime::currentDateTime();
    int days;

    QString logDir = QString("L_LOG/");
    QDir t_writeDir(logDir);
    if(!t_writeDir.exists())
    {
       return;
    }

    t_writeDir.setFilter(QDir::Files);
    QFileInfoList logFiles = t_writeDir.entryInfoList();
    for(int i=0; i< logFiles.length(); i++)
    {
        baseName = logFiles[i].baseName();
        file_time = QDateTime::fromString(baseName,"yyyyMMdd-hhmmss");
        days = file_time.daysTo(cur_time);
        if(days > _resvDays)
        {
             QFile::remove(logFiles[i].absoluteFilePath());
        }
    }

}

void Mylog::createLog()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timeStr = time.toString("yyyyMMdd-hhmmss"); //设置显示格式

    QString logDir = QString("L_LOG/");
    QDir t_writeDir(logDir);
    if(t_writeDir.exists())
    {

    }
    else
    {
        return;// 不自动创建
        QDir tDir;
        tDir.mkpath(logDir);
    }

    QString logFile =  logDir + timeStr + QString(".log");

    _file = new QFile(logFile);

    _file->open(QIODevice::Append|QIODevice::Text);

    //打开文件是否成功
    if(!_file->isOpen())
    {
        return;
    }

    _file ->close();
}


void Mylog::writeLog(QString log)
{\
    if(NULL == _file)
    {
        createLog();
    }
    QTime current_time = QTime::currentTime();
    QDateTime date_time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timeStr = date_time.toString("[yyyyMMdd-hh:mm:ss]"); //设置显示格式
    unsigned int pos = 0;
    //check clear expired log
    int cur_hour = current_time.hour();
    if(cur_hour != _lastHour)
    {
        checkClearLog();
    }

    //write log
    _file->open(QIODevice::Append|QIODevice::Text);
    //声明一个文本流对象,与文件绑定
    QTextStream t_textStream(_file);
    //t_textStream.setCodec(QTextCodec::codecForName("utf-8"));
    t_textStream << log << "\r\n";
    pos = _file->pos();
    _file->flush();
    _file->close();
    if(pos > LOG_FILE_MAX_SIZE)
    {
        delete _file;
        createLog();
    }

    _lastHour = current_time.hour();
}

void Mylog::init()
{
    _file  = NULL;
}



void Mylog::outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;

    QString logDir = QString("L_LOG/");
    QDir t_writeDir(logDir);
    if(!t_writeDir.exists())
    {
        return;
    }


    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }


   // QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString current_date = QString("[%1]").arg(current_date_time);
    QString message = QString("%1 %2").arg(current_date).arg(msg);
    writeLog(message);
    mutex.unlock();

}



