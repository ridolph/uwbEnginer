#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "UWB_SQL.h"
#include <QDebug>
#include <qdatetime.h>

UWB_SQL::UWB_SQL(const char *host_name, const char *db_name, const char *user, const char *password)
{
    m_dbconn = QSqlDatabase::addDatabase("QMYSQL");
    m_dbconn.setHostName(host_name);		//主机名字
    m_dbconn.setDatabaseName(db_name);		//数据库名字
    m_dbconn.setUserName(user);				//设置用户名
    m_dbconn.setPassword(password);			//设置密码
    if (m_dbconn.open())
    {
        qDebug() << "Database open successful!";
        m_is_open = true;
        m_query = (QSqlQuery)m_dbconn;
    }
    else
    {
        qDebug() << "Database open faild!";
        m_is_open = false;
    }
}

int32_t UWB_SQL::SavePrisonerPosition(int32_t tag_id, double x, double y, double z)
{
    char sql_cmd[500];

    if (!m_is_open)
        return -1;

    memset(sql_cmd, 0, sizeof(sql_cmd));

    QDateTime cur_time = QDateTime::currentDateTime();      //获取当前时间
    int timestamp = cur_time.toTime_t();                    //将当前时间转为时间戳
    QString str_CurTime = cur_time.toString("yyyy-MM-dd hh:mm:ss");//将当前时间转为格式化字符串
    QByteArray byte_array = str_CurTime.toLatin1();
    char *pos_time = byte_array.data();

    sprintf(sql_cmd,
            "INSERT INTO pr_coordinates_%d (tag_id, timestamp, position_time, position_x, position_y, position_z) VALUES (%d, %d, \"%s\", %f, %f, %f);",
            tag_id, tag_id, timestamp, pos_time, x, y, z);

    qDebug() << sql_cmd;

    bool ret = m_query.exec(sql_cmd);
    if(ret)
    {
        qDebug() << "success";
        return 0;
    }
    else
    {
        qDebug() << "error";
        return -2;
    }

}

char *UWB_SQL::GetPrisonerHistoryData(int32_t tag_id, char *start_time, char *end_time)
{
    char sql_cmd[500];
    QList <cJSON *> obj_list;
    cJSON *prisioner_hist_obj = NULL;

    if (!m_is_open)
        return NULL;

    if ((start_time == NULL) || (end_time == NULL))
        return NULL;

    memset(sql_cmd, 0, sizeof(sql_cmd));
    QDateTime time_begin = QDateTime::fromString(start_time, "yyyy-MM-dd hh:mm:ss");
    int timestamp_begin = time_begin.toTime_t();
    QDateTime time_end = QDateTime::fromString(end_time, "yyyy-MM-dd hh:mm:ss");
    int timestamp_end = time_end.toTime_t();

#if 0
    sprintf(sql_cmd,
            "SELECT position_time, position_x, position_y, position_z FROM pr_coordinates_%d WHERE timestamp >= %d AND timestamp <= %d;",
            tag_id, timestamp_begin, timestamp_end);
#else
    sprintf(sql_cmd,
            "SELECT position_time, position_x, position_y, position_z FROM pr_coordinates_%d ORDER BY id DESC LIMIT 10;",
            tag_id);
#endif

    //qDebug() << sql_cmd;

	bool ret = m_query.exec(sql_cmd);
    if (!ret)
        return NULL;

    cJSON *prisioner_hist_array = cJSON_CreateArray();
    if (prisioner_hist_array == NULL)
        return NULL;

    m_query.seek(-1);
    while(m_query.next())
    {
        prisioner_hist_obj = cJSON_CreateObject();
        if (prisioner_hist_obj == NULL)
            return NULL;

        obj_list << prisioner_hist_obj;

        QByteArray byte_array = m_query.value(0).toString().toLatin1();
        char *time = byte_array.data();

        cJSON_AddNumberToObject(prisioner_hist_obj, "tag_id", tag_id);
        cJSON_AddStringToObject(prisioner_hist_obj, "time", time);
        cJSON_AddNumberToObject(prisioner_hist_obj, "pos_x", m_query.value(1).toDouble());
        cJSON_AddNumberToObject(prisioner_hist_obj, "pos_y", m_query.value(2).toDouble());
        cJSON_AddNumberToObject(prisioner_hist_obj, "pos_z", m_query.value(3).toDouble());
        cJSON_AddItemToArray(prisioner_hist_array, prisioner_hist_obj);
    }

    char *strPosData = cJSON_Print(prisioner_hist_array);

    cJSON_Delete(prisioner_hist_array);

    return strPosData;
#if 0
out:
    for(int i = obj_list.begin(); i != obj_list.end(); i++)
    {
        if (obj_list[i])
            cJSON_Delete(obj_list[i]);
    }

    return NULL;
#endif
}

