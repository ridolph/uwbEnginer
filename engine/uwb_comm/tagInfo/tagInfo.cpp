#include "tagInfo.h"
#include <QDebug>
#include <time.h>
#include <QMap>
#include <QSettings>


ID_TIME_MAP  g_idTimeMap;//时间记录
ID_ALARM_MAP g_idAlarmMap;//报警信息记录
ID_ONLINE_MAP g_idOnlineMap;//上下线状态记录
ID_CELL_MAP   g_idCellMap;//所属牢房记录
ID_TAG_LASTINFO_MAP  g_idTagLastInfoMap;//标签坐标区域信息记录


int g_id_max;//记录ini文件中id的数量.

int tagIdS[MAX_TAG_NUM] ={0};//存放ini文件中读取到的标签id


//init tag-lastinfo map
void initTaglastInfo()
{
    TAG tmpTag ;
    tmpTag.current_node.x = 0xff;
    tmpTag.current_node.y = 0xff;
    tmpTag.current_node.z = 0xff;
    tmpTag.last_area_type = AREA_OUT_RANGE;
    tmpTag.last_effect_area_type = AREA_OUT_RANGE;
    tmpTag.oth_area_cnt = 0;
    tmpTag.cell_toilet_cnt = 0;

    int i = 0;
    for(i=0; i<g_id_max; i++)
    {
        g_idTagLastInfoMap.insert(tagIdS[i], tmpTag);
    }
}

//记录tag目前坐标，区域，区域跳变计数
bool  setTagLastInfo(int id, TAG taginfo)
{
    ID_TAG_LASTINFO_MAP::Iterator iter;

    iter = g_idTagLastInfoMap.find(id);
    if(iter != g_idTagLastInfoMap.end())
    {
        iter.value() = taginfo;
        return true;
    }
    return false;
}

//查看tag目前所在的区域
bool  getTagLastInfo(int id, TAG *pTag)
{

    ID_TAG_LASTINFO_MAP::Iterator iter;

    iter = g_idTagLastInfoMap.find(id);
    if(iter != g_idTagLastInfoMap.end())
    {
        *pTag = iter.value();
        return true;
    }
    return false;
}

//从ini文件中读取id存放到数组tagIdS[],记录id数量g_id_max
void initTagIdSet()
{
    //读取配置文件
    QSettings *configfile;
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("prisonerids");
    QString posStr = configfile->value("ids").toString();
    QStringList list = posStr.split(",");
    g_id_max = list.size();
    //My_Debug()<<"max id num:"<<g_id_max;
    for(int i=0; i<g_id_max; i++)
    {
        tagIdS[i] = list[i].toInt();
        //My_Debug()<<"tagid:"<<i<< tagIdS[i];
    }

    configfile->endGroup();
}

//检测tagid 是否在列表里面
bool checkTagIsLegal(int id)
{
	int i = 0;
	
	for(int i=0; i<g_id_max; i++)
    {
        if(id == tagIdS[i])
			return true;
    }

	return false;
}


//记录tag应属的牢房号
void initIdCellMap()
{
    int i = 0;
    QSettings *configfile;
    QString idStr;
    AREA_TYPE areaType;

    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("prisonercell");
    for(i=0; i<g_id_max; i++)
    {
       idStr = QString::number(tagIdS[i],10);
       areaType = (AREA_TYPE)configfile->value(idStr).toInt();
       g_idCellMap.insert(tagIdS[i], areaType);
       //My_Debug()<<idStr<<":areaType:"<<areaType;
    }

    configfile->endGroup();
}

//查找TAG应属的牢房号
bool  getTagCell(int id, AREA_TYPE *pAreaType)
{
    ID_CELL_MAP::Iterator iter = g_idCellMap.find(id);
    if(iter != g_idCellMap.end())
    {
        *pAreaType = iter.value();
        return true;
    }

    return false;
}




//初始化tag状态为下线状态
void initTagOnlineInfo()
{
    int i = 0;

    for(i=0; i<g_id_max; i++)
    {
        g_idOnlineMap.insert(tagIdS[i], OFF_LINE);
    }

}

//记录tag的上下线状态
bool setTagOnlineStatus(int id, ONLINE_STATUS status)
{
    ID_ONLINE_MAP::Iterator iter = g_idOnlineMap.find(id);
    if(iter != g_idOnlineMap.end())
    {
        iter.value() = status;
        return true;
    }

    return false;
}

//获取tag的上下线状态
bool getTagOnlineStatus(int id, ONLINE_STATUS *pStatus)
{
    ID_ONLINE_MAP::ConstIterator iter = g_idOnlineMap.find(id);
    if(iter != g_idOnlineMap.end())
    {
        *pStatus = iter.value();
        return true;
    }

    return false;
}

//init tag-alarm map
void initTagAlarmInfo()
{
    int i = 0;

    for(i=0; i<g_id_max; i++)
    {
        g_idAlarmMap.insert(tagIdS[i], ALARM_NONE);
    }

}

//记录tag的告警状态
bool setTagAlarm(int id, ALARM_TYPE type)
{
    ID_ALARM_MAP::Iterator iter = g_idAlarmMap.find(id);
    if(iter != g_idAlarmMap.end())
    {
        iter.value() = type;
        return true;
    }

    return false;
}

//获取tag当前的警告状态
bool getTagAlarm(int id, ALARM_TYPE *pType)
{
    ID_ALARM_MAP::Iterator iter = g_idAlarmMap.find(id);
    if(iter != g_idAlarmMap.end())
    {
        *pType = iter.value();
        return true;
    }

   return false;
}



//init id-time map
void initTagTimeInfo()
{
   int i = 0;
   TIME_RECORD defaultTime = {DEFAULT_LOCT_TIME, DEFAULT_TOILET_TIME, DEFAULT_OTHER_CELL_TIME};

   for(i=0; i<MAX_TAG_NUM; i++)
   {
       g_idTimeMap.insert(tagIdS[i], defaultTime);
   }
}

//查找tagID是否在tagID的记录里面
bool checkTagIsInTimeMap(int id)
{
    ID_TIME_MAP::ConstIterator iter = g_idTimeMap.find(id);

    if(iter != g_idTimeMap.end())
    {
        return true;
    }

    return false;
}
//获取tag的记录时间
bool getTagRecordTime(int id, TIME_RECORD* pRecordTime)
{
    ID_TIME_MAP::ConstIterator iter = g_idTimeMap.find(id);
    while(iter != g_idTimeMap.constEnd())
    {
        pRecordTime->loctTime = iter.value().loctTime;
        pRecordTime->toiletTime = iter.value().toiletTime;
        pRecordTime->otherCellTime = iter.value().otherCellTime;
        return true;
    }
    return false;
}

//记录tag发送数据的时间
bool setTagLoctTime(int id, int time)
{
    ID_TIME_MAP::Iterator iter;

    iter = g_idTimeMap.find(id);
    if(iter != g_idTimeMap.end())
    {
        iter.value().loctTime = time;
        return true;
    }
    return false;
}

//记录tag toilet时间
bool setTagToiletTime(int id, int time)
{
    ID_TIME_MAP::Iterator iter;

    iter = g_idTimeMap.find(id);
    if(iter != g_idTimeMap.end())
    {
        iter.value().toiletTime = time;
        return true;
    }
    return false;
}

//记录tag串仓时间
bool setTagOtherCellTime(int id, int time)
{
    ID_TIME_MAP::Iterator iter;

    iter = g_idTimeMap.find(id);
    if(iter != g_idTimeMap.end())
    {
        iter.value().otherCellTime = time;
        return true;
    }
    return false;
}

void tagInfoInit()
{
    initTagIdSet();
    initIdCellMap();
    initTagTimeInfo();
    initTagAlarmInfo();
    initTagOnlineInfo();
    initTaglastInfo();
}

void timeTest()
{
   int id = 1;
   bool ret = false;
   AREA_TYPE areaType;
   ALARM_TYPE alarmType;
   ONLINE_STATUS onlineStatus;

   initTagIdSet();
   initIdCellMap();
   initTagTimeInfo();
   setTagLoctTime(1,89);
   setTagToiletTime(1,900);
   setTagOtherCellTime(1,7867);

   initTagAlarmInfo();
   setTagAlarm(1,ALARM_STAY_LONG);

   initTagOnlineInfo();
   setTagOnlineStatus(1,ON_LINE);

   ret = getTagOnlineStatus(1,&onlineStatus);
   if(ret != false)
   {
       My_Debug()<<"ID:1, onlineStatus:"<<onlineStatus;
   }

   ret = getTagAlarm(1,&alarmType);
   if(ret != false)
   {
       My_Debug()<<"id:"<<1<<"alarmType:"<<alarmType;
   }


   TIME_RECORD tmpTime;
   ret = getTagRecordTime(1, &tmpTime);
   if(ret == true)
   {
        My_Debug()<<"id:"<<id<<"time:"<<tmpTime.loctTime<<tmpTime.toiletTime<<tmpTime.otherCellTime;
   }
}
