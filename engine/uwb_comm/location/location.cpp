#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QSettings>
#include "location.h"
#include <QString>
#include <QStringList>
#include <QDebug>

AREA g_AllArea[AREA_OUT_RANGE + 1];
TAG *g_AllTagList = NULL;

extern int g_jumpAllowCount ;//允许跳变的点数

//判断是否在划分的区域内
static bool isNodeInArea(NODE *node, AREA *area) 
{
    if((node->x >= area->x_low) && (node->x <= area->x_high) &&
       (node->y >= area->y_low) && (node->y <= area->y_high) &&
       (node->z >= area->z_low) && (node->z <= area->z_high))
    {
        return true;
    }
    
    return false;
}

//判断是否在扩展区域内
static bool isNodeInAreaEx(NODE *node, AREA *area)
{
    if((node->x >= (area->x_low - area->left_edge)) &&
       (node->x <= (area->x_high + area->right_edge)) &&
       (node->y >= (area->y_low - area->above_edge)) &&
       (node->y <= (area->y_high + area->blow_edge))&&
       (node->z >= (area->z_low - area->foot_edge))&&
       (node->z <= (area->z_high + area->head_edge)))
    {
        return true;
    }

    return false;
}

static void amendNodePos(NODE *node, AREA *area)
{
    if(node->x > area->x_high)
    {
        node->x = area->x_high - 0.3;
    }
    if(node->x < area->x_low)
    {
        node->x = area->x_low + 0.3;
    }
    if(node->y > area->y_high)
    {
        node->y = area->y_high - 0.3;
    }
    if(node->y < area->y_low)
    {
        node->y = area->y_low + 0.3;
    }
    if(node->z > area->x_high)
    {
        node->z = area->x_high - 0.3;
    }
    if(node->z < area->x_low)
    {
        node->z = area->x_low + 0.3;
    }
}

static void amendSubToMainPos(NODE *node, AREA *subArea)
{
    //只改变一下Y坐标
    node->y = subArea->y_high + subArea->above_edge;
}

static AREA_TYPE findNodeInSubAreaEx(TAG *tag, int area_index)
{
    char i = 0;
    AREA *area = NULL;

    area = &g_AllArea[area_index];
    if(area_index != area->area_type)
    {
        return ILLEGAL_AREA_TYPE;
    }

    if(0 == area->sub_area_num)
    {
        return (AREA_TYPE)area_index;
    }

    AREA_TYPE subAreaIndex = area->sub_area_index_set[0];
    area = &g_AllArea[subAreaIndex];

    if(true == isNodeInAreaEx(&tag->current_node, area))
    {
         return subAreaIndex;
    }
    else
    {
        return (AREA_TYPE)area_index;
    }
}

static AREA_TYPE findNodeInSubArea(TAG *tag, int area_index)
{
    char i = 0;
    AREA *area = NULL;

    area = &g_AllArea[area_index];
    if(area_index != area->area_type)
    {
        return ILLEGAL_AREA_TYPE;
    }
    
    if(0 == area->sub_area_num)
    {
        return (AREA_TYPE)area_index;
    }

    AREA_TYPE subAreaIndex = area->sub_area_index_set[0];
    area = &g_AllArea[subAreaIndex];
    
    if(true == isNodeInArea(&tag->current_node, area))
    {
         return subAreaIndex;
    }
    else
    {
        return (AREA_TYPE)area_index;
    }
}

static AREA_TYPE findNodeAreaEdge(TAG * tag)
{
    int i = 0;
    AREA *area = NULL;

    for(i = ILLEGAL_AREA_TYPE+1; i < AREA_OUT_RANGE ; ++i)
    {
        area = &g_AllArea[i];

        if(true == isNodeInAreaEx(&tag->current_node, area))
        {
            return findNodeInSubAreaEx(tag, i);
        }
        else
        {
            i += area->sub_area_num; //跳过其包含的区域,不用再次判断
        }
    }

    return AREA_OUT_RANGE;
}


AREA_TYPE findNodeArea(TAG *tag)
{
    int i = 0;
    AREA *area = NULL;

    for(i = ILLEGAL_AREA_TYPE+1; i < AREA_OUT_RANGE ; ++i)
    {
        area = &g_AllArea[i];
        
        if(true == isNodeInArea(&tag->current_node, area))
        {  
            return findNodeInSubArea(tag, i);
        }
        else
        {
            i += area->sub_area_num; //跳过其包含的区域,不用再次判断
        }
    }
    
    return AREA_OUT_RANGE;
}


AREA_TYPE confirmNodeArea(TAG *tag)
{
    AREA *area, *last_area = NULL;
    AREA_TYPE area_type = AREA_OUT_RANGE, tmp_area_type = AREA_OUT_RANGE;
    int i = 0, j = 0;


    //一、根据标签坐标计算所在区域
    area_type = findNodeArea(tag);//找到坐标所在的区域
    if(area_type == AREA_OUT_RANGE)//如果为超范围区域
    {
       tmp_area_type =  findNodeAreaEdge(tag);//判断坐标是否是在合法区域的扩展区域内.
       if(area_type != tmp_area_type)//是在合法区域的扩展区域内
       {
           area_type = tmp_area_type;
           area = &g_AllArea[area_type];
           amendNodePos(&tag->current_node, area);
       }
    }

    //二、本次计算得到的区域跟记录的标签所在区域进行对比,最终确定坐标及区域.
    if((tag->last_area_type == area_type) || (tag->last_area_type == AREA_OUT_RANGE))//如果相同或者上次为超范围区域
    {
        tag->oth_area_cnt = 0;
        tag->cell_toilet_cnt = 0;
        qDebug()<<"all cnt:0";
        return area_type;//返回本次区域
    }

    //确定本次计算的所在的区域是否在上次所待的区域扩展区域内。
    area = &g_AllArea[area_type];
    last_area = &g_AllArea[tag->last_area_type];

    if(area_type == last_area->sub_area_index_set[0])//由主区域进入包含区域
    {
        tag->oth_area_cnt = 0;
        tag->cell_toilet_cnt++;
        qDebug()<<"cell_toilet_cnt:"<<tag->oth_area_cnt;
        if(tag->cell_toilet_cnt >= g_jumpAllowCount)
        {
            tag->cell_toilet_cnt = 0;
            return area_type;
        }

        amendSubToMainPos(&tag->current_node, area);
        return tag->last_area_type;
    }
    else//区域切换
    {
        if(false == isNodeInAreaEx(&tag->current_node, last_area))//不在扩展区域内
        {
            tag->cell_toilet_cnt = 0;
            tag->oth_area_cnt++;
            qDebug()<<"oth cnt:"<<tag->oth_area_cnt;
            if(tag->oth_area_cnt >= g_jumpAllowCount)
             {
                 tag->oth_area_cnt = 0;
                 return area_type;
            }

        }

        amendNodePos(&tag->current_node, last_area);
        return tag->last_area_type;
    }
}




RESULT initAllTag()
{
    int malloc_len = MAX_TAG_NUM * sizeof(TAG);
    
    g_AllTagList = (TAG *)malloc(malloc_len);
    if(NULL == g_AllTagList)
    {
        return RET_FAILED;
    }

    memset(g_AllTagList, 0, malloc_len);
    
    return RET_SUCCESS;
}

RESULT initAllArea()
{
    AREA *area = NULL;
    int i = 0, j = 0;
    QString areaIdStr;
    QSettings *configfile;
    QString posStr, edgeStr;
    QStringList list;
    memset(&g_AllArea, 0, sizeof(g_AllArea));

    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    //牢房1
    configfile->beginGroup("officevirtualarea");
    area = &g_AllArea[CELL_1];
    area->area_type = CELL_1;
    area->sub_area_num = 0;
    areaIdStr = QString::number(CELL_1);
    posStr = configfile->value(areaIdStr).toString();
    if(posStr.isEmpty())
    {
        qDebug()<<"read uwbconfig.ini no officevirtualarea  config!!!!!!";
    }
    //qDebug()<<"ps str:"<<posStr;
    list = posStr.split(",");
    //qDebug()<<"CELL pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();
    area->z_low = list[4].toDouble();
    area->z_high = list[5].toDouble();
    configfile->endGroup();
    configfile->beginGroup("officeareaedge");
    edgeStr = configfile->value(areaIdStr).toString();
    if(edgeStr.isEmpty())
    {
        qDebug()<<"read uwbconfig.ini no officeareaedge config!!!!!";
    }
    list = edgeStr.split(",");
    area->left_edge = list[0].toDouble();
    area->right_edge = list[1].toDouble();
    area->above_edge = list[2].toDouble();
    area->blow_edge = list[3].toDouble();
    area->head_edge = list[4].toDouble();
    area->foot_edge = list[5].toDouble();

    configfile->endGroup();
    //qDebug()<<"CELL_1 edge:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();


#if 0 //办公室两个房间
    //读取配置文件
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    qDebug()<<"jumpcount:"<<g_jumpAllowCount;

    //活动室
    //牢房1
    configfile->beginGroup("officevirtualarea");
    area = &g_AllArea[CELL_1];
    area->area_type = CELL_1;
    area->sub_area_num = 1;
    area->sub_area_index_set[0] = TOLIET_1;
    areaIdStr = QString::number(CELL_1);
    posStr = configfile->value(areaIdStr).toString();
    if(posStr.isEmpty())
    {
        qDebug()<<"read uwbconfig.ini no officevirtualarea  config!!!!!!";
    }
    qDebug()<<"ps str:"<<posStr;
    list = posStr.split(",");
    qDebug()<<"CELL_1 pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();
    area->z_low = list[4].toDouble();
    area->z_high = list[5].toDouble();
    configfile->endGroup();
    configfile->beginGroup("officeareaedge");
    edgeStr = configfile->value(areaIdStr).toString();
    if(edgeStr.isEmpty())
    {
        qDebug()<<"read uwbconfig.ini no officeareaedge config!!!!!";
    }
    list = edgeStr.split(",");
    area->left_edge = list[0].toDouble();
    area->right_edge = list[1].toDouble();
    area->above_edge = list[2].toDouble();
    area->blow_edge = list[3].toDouble();
    area->head_edge = list[4].toDouble();
    area->foot_edge = list[5].toDouble();

    configfile->endGroup();
    qDebug()<<"CELL_1 edge:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();

    //1208 方向暂时没用.
    /*area->position[ABOVE].parallel_num = 1;
    area->position[ABOVE].area_node[0] = &g_AllArea[TOLIET_1];
    area->position[BELOW].parallel_num = 0;
    area->position[LEFT].parallel_num = 0;
    area->position[RIGHT].parallel_num = 1;
    area->position[RIGHT].area_node[0] = &g_AllArea[CELL_2];
    */

    //牢房1厕所
    configfile->beginGroup("officevirtualarea");
    area = &g_AllArea[TOLIET_1];
    area->area_type = TOLIET_1;
    area->sub_area_num = 0;
    areaIdStr = QString::number(TOLIET_1);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"TOLIET_1 pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();
    area->z_low = list[4].toDouble();
    area->z_high = list[5].toDouble();
    configfile->endGroup();
    configfile->beginGroup("officeareaedge");
    edgeStr = configfile->value(areaIdStr).toString();
    if(edgeStr.isEmpty())
    {
        qDebug()<<"read uwbconfig.ini no officeareaedge config!!!!!";
    }
    list = edgeStr.split(",");
    area->left_edge = list[0].toDouble();
    area->right_edge = list[1].toDouble();
    area->above_edge = list[2].toDouble();
    area->blow_edge = list[3].toDouble();
    area->head_edge = list[4].toDouble();
    area->foot_edge = list[5].toDouble();
    configfile->endGroup();
    qDebug()<<"TOLIET_1 edge:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();

    /*area->position[ABOVE].parallel_num = 0;
    area->position[BELOW].parallel_num = 1;
    area->position[BELOW].area_node[0] = &g_AllArea[CELL_1];
    area->position[LEFT].parallel_num = 0;
    area->position[RIGHT].parallel_num = 0;
    */


    //牢房2
    configfile->beginGroup("officevirtualarea");
    area = &g_AllArea[CELL_2];
    area->area_type = CELL_2;
    area->sub_area_num = 1;
    area->sub_area_index_set[0] = TOLIET_2;
    areaIdStr = QString::number(CELL_2);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"CELL_2 pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();
    area->z_low = list[4].toDouble();
    area->z_high = list[5].toDouble();
    configfile->endGroup();
    configfile->beginGroup("officeareaedge");
    edgeStr = configfile->value(areaIdStr).toString();
    if(edgeStr.isEmpty())
    {
        qDebug()<<"read uwbconfig.ini no officeareaedge config!!!!!";
    }
    list = edgeStr.split(",");
    area->left_edge = list[0].toDouble();
    area->right_edge = list[1].toDouble();
    area->above_edge = list[2].toDouble();
    area->blow_edge = list[3].toDouble();
    area->head_edge = list[4].toDouble();
    area->foot_edge = list[5].toDouble();
    configfile->endGroup();
    qDebug()<<"CELL_2 edge:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();

    /*area->position[ABOVE].parallel_num = 1;
    area->position[ABOVE].area_node[0] = &g_AllArea[TOLIET_2];
    area->position[BELOW].parallel_num = 0;
    area->position[LEFT].parallel_num = 1;
    area->position[LEFT].area_node[0] = &g_AllArea[CELL_1];
    area->position[RIGHT].parallel_num = 0;
    */

    //牢房2厕所
    configfile->beginGroup("officevirtualarea");
    area = &g_AllArea[TOLIET_2];
    area->area_type = TOLIET_2;
    area->sub_area_num = 0;
    areaIdStr = QString::number(TOLIET_2);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"TOLIET_2 pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();
    area->z_low = list[4].toDouble();
    area->z_high = list[5].toDouble();
    configfile->endGroup();
    configfile->beginGroup("officeareaedge");
    edgeStr = configfile->value(areaIdStr).toString();
    if(edgeStr.isEmpty())
    {
        qDebug()<<"read uwbconfig.ini no officeareaedge config!!!!!";
    }
    list = edgeStr.split(",");
    area->left_edge = list[0].toDouble();
    area->right_edge = list[1].toDouble();
    area->above_edge = list[2].toDouble();
    area->blow_edge = list[3].toDouble();
    area->head_edge = list[4].toDouble();
    area->foot_edge = list[5].toDouble();
    configfile->endGroup();
    qDebug()<<"TOLIET_2 edge:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble() \
           <<list[3].toDouble()<<list[4].toDouble()<<list[5].toDouble();
    /*area->position[ABOVE].parallel_num = 0;
    area->position[BELOW].parallel_num = 1;
    area->position[BELOW].area_node[0] = &g_AllArea[CELL_2];
    area->position[LEFT].parallel_num = 0;
    area->position[RIGHT].parallel_num = 0;
    */
    delete configfile;
#endif

#if 0 //监狱
    memset(&g_AllArea, 0, sizeof(g_AllArea));
    //读取配置文件
    configfile =  new QSettings("uwbconfig.ini", QSettings::IniFormat);
    configfile->beginGroup("officevirtualarea");
    //活动室
    area = &g_AllArea[ACTIVITY_ROOM];
    area->area_type = ACTIVITY_ROOM;
    area->sub_area_num = 0;
    //上面是过厅B,且只有上面位置有AREA
    area->position[ABOVE].parallel_num = 1;
    area->position[ABOVE].area_node[1] = &g_AllArea[HALL_B];
    area->position[BELOW].parallel_num = 0;
    area->position[LEFT].parallel_num = 0;
    area->position[RIGHT].parallel_num = 0;
    areaIdStr = QString::number(ACTIVITY_ROOM);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"active pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();

    //走廊
    area = &g_AllArea[LOBBY];
    area->area_type = LOBBY;
    area->sub_area_num = 0;
    //左面是过厅B
    area->position[LEFT].parallel_num = 1;
    area->position[LEFT].area_node[1] = &g_AllArea[HALL_B];
    //上面是12个牢房
    area->position[ABOVE].parallel_num = 12;
    area->position[ABOVE].area_node[1] = &g_AllArea[CELL_1];
    area->position[ABOVE].area_node[2] = &g_AllArea[CELL_2];
    area->position[ABOVE].area_node[3] = &g_AllArea[CELL_3];
    area->position[ABOVE].area_node[4] = &g_AllArea[CELL_4];
    area->position[ABOVE].area_node[5] = &g_AllArea[CELL_5];
    area->position[ABOVE].area_node[6] = &g_AllArea[CELL_6];
    area->position[ABOVE].area_node[7] = &g_AllArea[CELL_7];
    area->position[ABOVE].area_node[8] = &g_AllArea[CELL_8];
    area->position[ABOVE].area_node[9] = &g_AllArea[CELL_9];
    area->position[ABOVE].area_node[10] = &g_AllArea[CELL_10];
    area->position[ABOVE].area_node[11] = &g_AllArea[CELL_11];
    area->position[ABOVE].area_node[12] = &g_AllArea[CELL_12];
    areaIdStr = QString::number(LOBBY);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"LOBBY pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();

    //过厅B
    area = &g_AllArea[HALL_B];    
    area->area_type = HALL_B;
    area->sub_area_num = 0;
    //上面是阅览室
    area->position[ABOVE].parallel_num = 1;
    area->position[ABOVE].area_node[1] = &g_AllArea[READING_ROOM];
    //下面是活动室
    area->position[BELOW].parallel_num = 1;
    area->position[BELOW].area_node[1] = &g_AllArea[ACTIVITY_ROOM];
    //左边有2个,过厅或者开水间
    area->position[LEFT].parallel_num = 2;
    area->position[LEFT].area_node[1] = &g_AllArea[HALL_A];
    area->position[LEFT].area_node[2] = &g_AllArea[TALK_ROOM];
    //右边是走廊
    area->position[RIGHT].parallel_num = 1;
    area->position[RIGHT].area_node[1] = &g_AllArea[LOBBY];
    areaIdStr = QString::number(HALL_B);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"HALL_B pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();
    
    //过厅A
    area = &g_AllArea[HALL_A];
    area->area_type = HALL_A;
    area->sub_area_num = 0;
    //右边是过厅B,
    area->position[RIGHT].parallel_num = 1;
    area->position[RIGHT].area_node[1] = &g_AllArea[HALL_B];
    areaIdStr = QString::number(HALL_A);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"HALL_A pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();

    //TALK_ROOM
    area = &g_AllArea[TALK_ROOM];
    area->area_type = TALK_ROOM;
    area->sub_area_num = 0;
    //右边是过厅B,
    area->position[RIGHT].parallel_num = 1;
    area->position[RIGHT].area_node[1] = &g_AllArea[HALL_B];   
    //上面是更衣室
    area->position[ABOVE].parallel_num = 1;
    area->position[ABOVE].area_node[1] = &g_AllArea[CHANGE_ROOM];
    areaIdStr = QString::number(TALK_ROOM);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"TALK_ROOM pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();
    
    //更衣室
    area = &g_AllArea[CHANGE_ROOM];
    area->area_type = CHANGE_ROOM;
    area->sub_area_num = 1;
    area->sub_area_index_set[0] = BOILED_ROOM;
    //下面是开水间
    area->position[BELOW].parallel_num = 1;
    area->position[BELOW].area_node[1] = &g_AllArea[TALK_ROOM];
    areaIdStr = QString::number(CHANGE_ROOM);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"CHANGE_ROOM pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();

    //开水间
    area = &g_AllArea[BOILED_ROOM];
    area->area_type = BOILED_ROOM;
    area->sub_area_num = 0;
    //下面是谈话间
    area->position[BELOW].parallel_num = 1;
    area->position[BELOW].area_node[0] = &g_AllArea[TALK_ROOM];
    areaIdStr = QString::number(BOILED_ROOM);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"BOILED_ROOM pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();

    //阅览室
    area = &g_AllArea[READING_ROOM];
    area->area_type = READING_ROOM;
    area->sub_area_num = 0;
    //下面是过厅B
    area->position[BELOW].parallel_num = 1;
    area->position[BELOW].area_node[0] = &g_AllArea[HALL_B];
    areaIdStr = QString::number(READING_ROOM);
    posStr = configfile->value(areaIdStr).toString();
    list = posStr.split(",");
    qDebug()<<"READING_ROOM pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
    area->x_low = list[0].toDouble();
    area->x_high = list[1].toDouble();
    area->y_low = list[2].toDouble();
    area->y_high = list[3].toDouble();

#if 1
    //牢房
    j = CELL_12 - CELL_1+2;
    for(i = 0; i < j; i=i+2)
    {
        area = &g_AllArea[CELL_1 + i];
        area->area_type = (AREA_TYPE)(CELL_1 + i);
        //每个牢房有一个厕所的子区域
        area->sub_area_num = 1;
        area->sub_area_index_set[0] = AREA_TYPE(CELL_1 + i +1);
        //上面是厕所
        area->position[ABOVE].parallel_num = 1;
        area->position[ABOVE].area_node[0] = &g_AllArea[TOLIET_1 + i];
        //下面是走廊
        area->position[BELOW].parallel_num = 1;
        area->position[BELOW].area_node[0] = &g_AllArea[LOBBY];

        areaIdStr = QString::number(CELL_1+i);
        posStr = configfile->value(areaIdStr).toString();
        list = posStr.split(",");
        qDebug()<<"CELL_"<<i/2 + 1<<"pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
        area->x_low = list[0].toDouble();
        area->x_high = list[1].toDouble();
        area->y_low = list[2].toDouble();
        area->y_high = list[3].toDouble();
    }
#endif
    //厕所
    j = TOLIET_12 - TOLIET_1 +2;
    for(i = 0; i < j; i=i+2)
    {
        area = &g_AllArea[TOLIET_1 + i]; 
        area->area_type = (AREA_TYPE)(TOLIET_1 + i);
        area->sub_area_num = 0;
        //下面是牢房
        area->position[BELOW].parallel_num = 1;
        area->position[BELOW].area_node[1] = &g_AllArea[CELL_1 + i];
        areaIdStr = QString::number(TOLIET_1+i);
        posStr = configfile->value(areaIdStr).toString();
        list = posStr.split(",");
        //qDebug("i=%d,j=%d,i+2=%d",i,j,i+2);
        qDebug()<<"TOLIET_"<<i/2 + 1<<"pos:"<<list[0].toDouble()<<list[1].toDouble()<<list[2].toDouble()<<list[3].toDouble();
        area->x_low = list[0].toDouble();
        area->x_high = list[1].toDouble();
        area->y_low = list[2].toDouble();
        area->y_high = list[3].toDouble();
    }    

    configfile->endGroup();
    delete configfile;
#endif
    return RET_SUCCESS;
}

void testCheckNode()
{
   AREA_TYPE areaType = AREA_OUT_RANGE;
   TAG node = {{33,1.5}, (AREA_TYPE)1};
   areaType =findNodeArea(&node);
   qDebug()<<"area type:"<<areaType;

}
