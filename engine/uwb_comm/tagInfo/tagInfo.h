#ifndef _TAG_INFO_
#define _TAG_INFO_

#include <QMap>
#include <QDebug>
#include"../location/location.h"

#define My_Debug  qDebug

#define DEFAULT_LOCT_TIME            0xffffff
#define DEFAULT_TOILET_TIME          0
#define DEFAULT_OTHER_CELL_TIME      0



typedef unsigned int ALARM_TYPE;

#define ALARM_CANCEL        0
#define ALARM_SET           1

#define ALARM_NONE              0
#define ALARM_OUT_RANGE         0x01//电子围栏
#define ALARM_OTHER_CELL        0x02//串监
#define ALARM_STAY_LONG       0x04//待在厕所时间太长。
#define ALARM_NO_SIGNAL         0x08//信号消失


#define ALARM_OTHER_CELL_STR    "0101"
#define ALARM_OUT_RANGE_STR     "0102"
#define ALARM_STAY_TIMOUT_STR   "0201"
#define ALARM_NO_SIGNAL_STR     "0202"

#define ALARM_LEVEL_REMIND      "03"
#define ALARM_LEVEL_COMMON      "02"
#define ALARM_LEVEL_BAD         "01"


#define MSG_TYPE_ONLINE_STATUS      1
#define MSG_TYPE_POSITION           2
#define MSG_TYPE_ALARM              3
#define MSG_TYPE_PING               4
#define MSG_TYPE_HEART              7


typedef enum {
    OFF_LINE = 0,
    ON_LINE = 1,
    INIT_ONLINE
}ONLINE_STATUS;

typedef struct{
    int loctTime;
    int toiletTime;
    int otherCellTime;
}TIME_RECORD;

typedef QMap<int, TIME_RECORD> ID_TIME_MAP;
typedef QMap<int, AREA_TYPE> ID_AREA_MAP;
typedef QMap<int, ALARM_TYPE> ID_ALARM_MAP;
typedef QMap<int, ONLINE_STATUS> ID_ONLINE_MAP;
typedef QMap<int, AREA_TYPE> ID_CELL_MAP;
typedef QMap<int, TAG>ID_TAG_LASTINFO_MAP;

bool setTagAlarm(int id, ALARM_TYPE type);
bool getTagAlarm(int id, ALARM_TYPE *pType);
bool setTagOnlineStatus(int id, ONLINE_STATUS status);
bool getTagOnlineStatus(int id, ONLINE_STATUS *pStatus);
bool getTagCell(int id, AREA_TYPE *pAreaType);
void initTagTimeInfo();
bool setTagLoctTime(int id, int time);
bool setTagToiletTime(int id, int time);
bool setTagOtherCellTime(int id, int time);
bool getTagRecordTime(int id, TIME_RECORD* pRecordTime);
bool  getTagLastInfo(int id, TAG *pTag);
bool  setTagLastInfo(int id, TAG taginfo);
void initTaglastInfo();

void tagInfoInit();
void timeTest();


#endif
