#include "verify.h"
#include "aes.h"
#include <stdio.h>
#include <string.h>
#include <QSettings>
#include <QDateTime>
#include <QDebug>
#include <QDir>


#define EXPIRED_YEAR    2019
#define EXPIRED_MONTH   7
#define EXPIRED_DAY     15



/***************************
 * func : 字符转化数字
 * eg:
 *'9' -> 9
 *'a' -> 10
 *'A' -> 10
***************************/
void assicTohex(unsigned char *param)
{
    if (*param >= '0' && *param <= '9')
        *param -= '0';
    else if (*param >= 'a' && *param <= 'f')
        *param -= ('a' - 10);
    else if (*param >= 'A' && *param <= 'F')
        *param -= ('A' - 10);
    else
       *param = 0;
}

/**********************************
*func: 字符串转化为十六进制*
*eg: "ABCDEF" -> 0xab, 0xcd, 0xef
************************************/
void strTohexes(char *pStr, int strSz, unsigned char *pHex)
{
    int i = 0;
    unsigned char tmp = 0;
    for (; i < strSz; i += 2) {
        *pHex = *pStr++;
        assicTohex(pHex);
        *pHex <<= 4;
        tmp = *pStr++;
        assicTohex(&tmp);
        *pHex += tmp;
        pHex++;
    }
}


void createLicense()
{
    QString logDir = QString("Qt5Rend.dll");
    QDir t_writeDir(logDir);
    if(t_writeDir.exists())
    {
        //qDebug()<<"dir  is exist";
    }
    else
    {
        //qDebug()<<"dir log is not exist";
        updateRemainTime(5040);
    }
}


int verifyDate()
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime expiredTime;
    int time;

    //createLicense();

    QDate date(EXPIRED_YEAR, EXPIRED_MONTH, EXPIRED_DAY);
    expiredTime.setDate(date);

    int days = now.daysTo(expiredTime);
    //qDebug()<<"days:"<<days;

    if(days > 0)//未到期
    {
        return 1;
    }
    else if(days == 0)//到期那一天
    {
        time = getRemainTime();
        if(time > 60)
        {
            updateRemainTime(60);
            return 1;
        }
        else if((0<time)&&(time <= 60))
        {
            return 1;
        }
        else if(time <= 0)
        {
            return 0;
        }
    }
    else//到期
    {
        updateRemainTime(1);
        return 0;
    }

}



/*********************************
*func: 获取剩余试用时间
*retun: 0：读取错误|到期
*       >0: 剩余试用时间
********************************/

int getRemainTime()
{

    unsigned char key[]={
            0x05,0x15,0x89,0x63,
            0x14,0xdc,0xe8,0x59,
            0x0c,0xc7,0xad,0xdf,
            0xab,0x75,0x61,0x9a
    };

    QSettings * configfile;
    configfile =  new QSettings("Qt5Rend.dll", QSettings::IniFormat);
    configfile->beginGroup("test");
    QString lic = configfile->value("test").toString();
    configfile->endGroup();

    char buf[64] = {0};
    unsigned char dencrypt[16] = {0};
    char out[16] = {0};
    memcpy(buf, lic.toLatin1().data(), lic.length());
    buf[32] = 0;
    strTohexes(buf, 32, dencrypt);

    AES aes(key);
    aes.InvCipher(dencrypt,(unsigned char*)out );
    //printf("out:%s\n", out);

    char *p = NULL;
    p = strstr(out, "time:");
    if(NULL == p)
    {
        return 0;
    }

    int time = atoi(p+strlen("time:"));
    //printf("get remain time:%d\n", time);
    if(time > 0)
    {
        return time;
    }

  return 0;
}

/*********************************
*func: 设置剩余试用时间
********************************/
void updateRemainTime(int time)
{
    char encrypt[16] = {0};
    unsigned char out[16] = {0};
    unsigned char confuse[3] = {0};
    char dumpBuf[64] = {0};
    unsigned char key[]={
            0x05,0x15,0x89,0x63,
            0x14,0xdc,0xe8,0x59,
            0x0c,0xc7,0xad,0xdf,
            0xab,0x75,0x61,0x9a
    };

    snprintf(encrypt, sizeof(encrypt), "%s%d","time:", time);
    AES aes(key);
    aes.Cipher((unsigned char*)encrypt, out);

    int i;
    for(i=0; i<sizeof(out); i++)
    {
        snprintf(dumpBuf+i*2, sizeof(dumpBuf), "%02X", out[i]);
    }
    confuse[0] = out[3] | out[15] & out[4];
    confuse[1] = out[6] | out[7]  & out[9];
    confuse[2] = out[8] | out[13] & out[15];

    int len = strlen(dumpBuf);
    for(i=0; i<sizeof(confuse); i++)
    {
        snprintf(dumpBuf + len + i*2, sizeof(confuse), "%02X", confuse[i]);
    }


    //printf("dumpBuf:%s\n", dumpBuf);

    QString license = QString(dumpBuf);

    QSettings *configfile;
    configfile =  new QSettings("Qt5Rend.dll", QSettings::IniFormat);
    configfile->setValue("/test/test", license);
    delete configfile;
}


