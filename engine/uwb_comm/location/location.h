#ifndef _LOCATION_H_
#define _LOCATION_H_

#define OFFICE 1

#define MAX_TAG_NUM 200 //64    用于测试
#define MAX_SUB_AREA_NUM 1

typedef enum{
    ILLEGAL_AREA_TYPE = 0,

    //ACTIVITY_ROOM = 1, //活动室
    CELL_1 = 1,
    //TOLIET_1 = 2 ,

    //CELL_2 = 3,
    //TOLIET_2 = 4 ,

    AREA_OUT_RANGE = 2,//在监控范围之外
}AREA_TYPE;


/*
!!!!AREA_TYPE会和区域下标直接转换的,一定要注意

为了减少重复包含区域的查找(比如牢房和厕所,不在牢房1范围内
 则肯定不会在厕所1,同理在牢房1里面,也仅仅只需要再次判断是否在
 厕所1中),这样在设计区域编号的时候也要按照从属关系来
*/

typedef enum{
    ABOVE = 0,
    BELOW = 1,
    LEFT = 2,
    RIGHT = 3,
    HEAD = 4,
    FOOT = 5,
    MAX_POSITION = 6,
}POSITION_TYPE;

typedef enum{
    RET_SUCCESS = 0,
    RET_FAILED = 1,
}RESULT;

typedef struct node{
    double x;
    double y;
    double z;
}NODE;

typedef struct direction{
    void *area_node[AREA_OUT_RANGE];
    unsigned char parallel_num; //该方位上有多少个平行区域
}POSITION;
    
/**/
typedef struct area{  
    //该区域紧邻的四个方位相关信息,有可能一个方位上还有多个相关联区域
    //比如走廊和牢房,在走廊上面有12个牢房
    POSITION position[MAX_POSITION];

    //该区域的范围坐标 
    double x_low;
    double x_high;
    double y_low;
    double y_high; 
    double z_low;
    double z_high;

    //边缘保护
    double left_edge;
    double right_edge;
    double above_edge;
    double blow_edge;
    double head_edge;
    double foot_edge;

    AREA_TYPE area_type;

    //该区域能包含的子区域信息，因为目前是按照数组来对每个区域进行安放的,
    //这样的话如果记录一个大区域包含的多少个子区域,当一个点的值
    //不在大区域之内时就可以直接跳过其所包含的所有小区域了,
    //这样就需要配合AREA_TYPE中的枚举值来,必须规范定义
    char sub_area_num;//因为每个子区域都站一个index,这个值是其下所有子区域
    AREA_TYPE sub_area_index_set[MAX_SUB_AREA_NUM];
}AREA;

typedef struct{
    NODE current_node; //当前所在坐标点
    AREA_TYPE last_area_type; //上一次所在区域
    AREA_TYPE last_effect_area_type;
    unsigned char oth_area_cnt;
    unsigned char cell_toilet_cnt;
}TAG;

//尝试遍历所有区域,但是会跳过互相包含的子区域,查找速度居中,有极小的出错概率,
AREA_TYPE findNodeArea(TAG *tag);
AREA_TYPE confirmNodeArea(TAG *tag);
RESULT initAllTag();
RESULT initAllArea();
void testCheckNode();
#endif
