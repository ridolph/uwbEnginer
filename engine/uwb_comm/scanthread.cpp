#include "ScanThread.h"
#include "tagInfo/tagInfo.h"
#include <time.h>


extern int tagIdS[MAX_TAG_NUM];//��ǩid
extern int g_id_max;

extern int  g_signal_vanish_timeout;
extern int  g_stay_timeout;
extern int  g_other_cell_timeout;


ScanThread::ScanThread(QObject *parent):QThread(parent)
{
   // qDebug()<<"scan thread start";
}

ScanThread::~ScanThread()
{

}


void ScanThread::run()
{
    sleep(START_SCAN_WAIT_TIME_S);//�ȴ���������
    while(1)
    {
        scan();
        msleep(SCAN_PERIOD_MS);
    }
}


void ScanThread::scan()
{
    int sec;
    int i;
    AREA_TYPE areaType;
    ALARM_TYPE alarmType;
    AREA_TYPE prisonerCell;
    int tagId = -1;
    bool ret = false;
    TIME_RECORD timeRecord;

    int loctTime;
    int toiletTime;
    int otherCellTime;
    ONLINE_STATUS onlineStatus;
    TAG tagInfo;

    sec = clock()/CLOCKS_PER_SEC;

    for(i = 0; i < g_id_max; i++)
    {
        tagId = tagIdS[i];

        getTagLastInfo(tagId,&tagInfo);
        areaType = tagInfo.last_area_type;
        getTagRecordTime(tagId, &timeRecord);
        getTagAlarm(tagId, &alarmType);
        getTagOnlineStatus(tagId, &onlineStatus);
        getTagCell(tagId, &prisonerCell);

        loctTime = timeRecord.loctTime;
        toiletTime = timeRecord.toiletTime;
        otherCellTime = timeRecord.otherCellTime;

        if((sec >= loctTime)&&((sec - loctTime) <= g_signal_vanish_timeout))//locatime���ǳ�ʼֵ�������յ���ǩ����ʱ��
        {
            if(areaType < AREA_OUT_RANGE)
            {
                if(alarmType & ALARM_OUT_RANGE)
                {
                    alarmType &= ~ALARM_OUT_RANGE;
                    setTagAlarm(tagId, alarmType);
                    //ȡ����������澯
                    emit SendAlarm(tagId, ALARM_OUT_RANGE, ALARM_CANCEL);
                }
            }

            if(ON_LINE != onlineStatus)
            {
                //����
                setTagOnlineStatus(tagId, ON_LINE);
                emit SendCellOnlineStatus(tagId, ON_LINE);


                /*qDebug()<<"send tag"<<tagId<<"on line";
                //setTagAlarm(tagId, ALARM_NONE);
                emit SendAlarm(tagId, ALARM_NO_SIGNAL, ALARM_CANCEL);
                qDebug()<<"send tag"<<tagId<<"cancel no signal ";
                */

                if(alarmType & ALARM_NO_SIGNAL)
                {
                    alarmType &= ~ALARM_NO_SIGNAL;
                    setTagAlarm(tagId, alarmType);
                    emit SendAlarm(tagId, ALARM_NO_SIGNAL, ALARM_CANCEL);
                }

                if(toiletTime == DEFAULT_TOILET_TIME)
                {
                    setTagToiletTime(tagId, sec);
                }
                if(otherCellTime == DEFAULT_OTHER_CELL_TIME)
                {
                    setTagOtherCellTime(tagId, sec);
                }

                alarmType |=  ALARM_OUT_RANGE;
                setTagAlarm(tagId, alarmType);

            }

            switch(areaType)
            {
            case CELL_1:
           // case CELL_2:

                if(alarmType & AREA_OUT_RANGE)
                {
                    alarmType &= ~AREA_OUT_RANGE;
                    setTagAlarm(tagId, alarmType);
                    emit SendAlarm(tagId, ALARM_OUT_RANGE, ALARM_CANCEL);
                    qDebug()<<"send tag"<<tagId<<"cancel alarm out range";
                }


                if(alarmType & ALARM_STAY_LONG)//ȡ���ײ�������ʱ��澯
                {
                    alarmType &= ~ALARM_STAY_LONG;
                    setTagAlarm(tagId, alarmType);
                    emit SendAlarm(tagId,ALARM_STAY_LONG,ALARM_CANCEL);
                }


                if(areaType != prisonerCell)//����
                {
                    if((sec - otherCellTime)>= g_other_cell_timeout)
                    {
                        if((alarmType & ALARM_OTHER_CELL) == 0)
                        {
                             alarmType |= ALARM_OTHER_CELL;
                             setTagAlarm(tagId, alarmType);
                             //���ʹ���澯��
                             emit SendAlarm(tagId, ALARM_OTHER_CELL,ALARM_SET);
                             qDebug()<<"send tag"<<tagId<<"set other cell alarm";
                        }
                        setTagOtherCellTime(tagId, sec);//�Ѿ����͹����౨����ȡ�������¼
                    }

                   setTagToiletTime(tagId, sec);//ȡ���ײ�����¼
                }
                else//�����Լ����η���
                {
                    if(alarmType & ALARM_OTHER_CELL)
                    {

                        //todoȡ�����и澯��
                        //setTagAlarm(tagId, ALARM_NONE);
                        //emit SendAlarm(tagId, ALARM_NONE,ALARM_SET);
                        // qDebug()<<"send tag"<<tagId<<"set none alarm";
                        //ȡ������澯
                        alarmType &= ~ALARM_OTHER_CELL;
                        setTagAlarm(tagId, alarmType);
                        emit SendAlarm(tagId, ALARM_OTHER_CELL, ALARM_CANCEL);
                        qDebug()<<"send tag"<<tagId<<"cancel othcell alarm";
                    }


                    setTagToiletTime(tagId, sec);//ȡ���ײ�����¼
                    setTagOtherCellTime(tagId, sec);//ȡ�������¼
                }

                break;
           /* case TOLIET_1:
            case TOLIET_2:
                if((areaType-1) != prisonerCell)//���ڱ��˵Ĳ�����//�жϴ���
                {
                    if((sec - otherCellTime) >= g_other_cell_timeout)
                    {
                        if((alarmType & ALARM_OTHER_CELL) == 0)
                        {
                            alarmType |= ALARM_OTHER_CELL;
                            setTagAlarm(tagId, alarmType);
                            //todo ���ʹ���澯��
                            emit SendAlarm(tagId, ALARM_OTHER_CELL,ALARM_SET);
                            qDebug()<<"send tag"<<tagId<<"set other cell alarm";
                        }
                        setTagOtherCellTime(tagId, sec);//�Ѿ����͹�����澯��ȡ�������¼
                    }
                }
                else//�����Լ��η�-������
                {

                    if(alarmType & ALARM_OTHER_CELL)//����д���澯��ȡ��
                    {
                        alarmType &= ~ALARM_OTHER_CELL;
                        setTagAlarm(tagId, alarmType);
                        //����ȡ������澯��
                        emit SendAlarm(tagId, ALARM_OTHER_CELL,ALARM_CANCEL);
                        qDebug()<<"send tag"<<tagId<<"cancel other cell alarm";
                    }

                    setTagOtherCellTime(tagId, sec);//ȡ�������¼
                }

                if((sec - toiletTime)> g_stay_timeout)//�ж϶ײ�����ʱ
                {
                    if((alarmType & ALARM_STAY_LONG) == 0)
                    {
                        alarmType |= ALARM_STAY_LONG;
                        setTagAlarm(tagId, alarmType);
                        //todo���Ͷ�������ʱ���������
                        emit SendAlarm(tagId, ALARM_STAY_LONG, ALARM_SET);
                        qDebug()<<"send tag"<<tagId<<"set stay toilet timeout alarm";
                    }
                    setTagToiletTime(tagId,sec);//ȡ���ײ�����¼
                }

                break;*/
            case AREA_OUT_RANGE://����Χ��
                 if((alarmType & ALARM_OUT_RANGE) == 0)
                 {
                     alarmType |= ALARM_OUT_RANGE;
                     setTagAlarm(tagId, alarmType);
                     //todo���͵���Χ���澯
                     emit SendAlarm(tagId,ALARM_OUT_RANGE,ALARM_SET);
                     qDebug()<<"send tag:"<< tagId<<"set out range alarm";
                 }
                 if(alarmType & ALARM_STAY_LONG)//ȡ���ײ�������ʱ��澯
                 {
                     alarmType &= ~ALARM_STAY_LONG;
                     setTagAlarm(tagId, alarmType);
                     emit SendAlarm(tagId,ALARM_STAY_LONG,ALARM_CANCEL);
                 }
                 if(alarmType & ALARM_OTHER_CELL)//ȡ������澯
                 {
                     alarmType &= ~ALARM_OTHER_CELL;
                     setTagAlarm(tagId, alarmType);
                     emit SendAlarm(tagId, ALARM_OTHER_CELL, ALARM_CANCEL);
                     qDebug()<<"send tag"<<tagId<<"cancel othcell alarm";
                 }
                 setTagToiletTime(tagId, sec);//ȡ���ײ�����¼
                 setTagOtherCellTime(tagId, sec);//ȡ�������¼


                default:
                break;

            }
        }
        else
        {
            if(OFF_LINE != onlineStatus)//����
            {
              //�����ź���ʧ�澯//���ߡ�
              setTagOnlineStatus(tagId, OFF_LINE);
              setTagAlarm(tagId, ALARM_NO_SIGNAL);
              emit SendCellOnlineStatus(tagId, OFF_LINE);
              qDebug()<<"send tag"<<tagId<<"off line";
              emit SendAlarm(tagId, ALARM_NO_SIGNAL, ALARM_SET);
              qDebug()<<"send tag"<<tagId<<"set no signal alarm";
            }
        }
    }
}



