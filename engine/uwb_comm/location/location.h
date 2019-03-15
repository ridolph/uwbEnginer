#ifndef _LOCATION_H_
#define _LOCATION_H_

#define OFFICE 1

#define MAX_TAG_NUM 200 //64    ���ڲ���
#define MAX_SUB_AREA_NUM 1

typedef enum{
    ILLEGAL_AREA_TYPE = 0,

    //ACTIVITY_ROOM = 1, //���
    CELL_1 = 1,
    //TOLIET_1 = 2 ,

    //CELL_2 = 3,
    //TOLIET_2 = 4 ,

    AREA_OUT_RANGE = 2,//�ڼ�ط�Χ֮��
}AREA_TYPE;


/*
!!!!AREA_TYPE��������±�ֱ��ת����,һ��Ҫע��

Ϊ�˼����ظ���������Ĳ���(�����η��Ͳ���,�����η�1��Χ��
 ��϶������ڲ���1,ͬ�����η�1����,Ҳ����ֻ��Ҫ�ٴ��ж��Ƿ���
 ����1��),��������������ŵ�ʱ��ҲҪ���մ�����ϵ��
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
    unsigned char parallel_num; //�÷�λ���ж��ٸ�ƽ������
}POSITION;
    
/**/
typedef struct area{  
    //��������ڵ��ĸ���λ�����Ϣ,�п���һ����λ�ϻ��ж�����������
    //�������Ⱥ��η�,������������12���η�
    POSITION position[MAX_POSITION];

    //������ķ�Χ���� 
    double x_low;
    double x_high;
    double y_low;
    double y_high; 
    double z_low;
    double z_high;

    //��Ե����
    double left_edge;
    double right_edge;
    double above_edge;
    double blow_edge;
    double head_edge;
    double foot_edge;

    AREA_TYPE area_type;

    //�������ܰ�������������Ϣ����ΪĿǰ�ǰ�����������ÿ��������а��ŵ�,
    //�����Ļ������¼һ������������Ķ��ٸ�������,��һ�����ֵ
    //���ڴ�����֮��ʱ�Ϳ���ֱ��������������������С������,
    //��������Ҫ���AREA_TYPE�е�ö��ֵ��,����淶����
    char sub_area_num;//��Ϊÿ��������վһ��index,���ֵ����������������
    AREA_TYPE sub_area_index_set[MAX_SUB_AREA_NUM];
}AREA;

typedef struct{
    NODE current_node; //��ǰ���������
    AREA_TYPE last_area_type; //��һ����������
    AREA_TYPE last_effect_area_type;
    unsigned char oth_area_cnt;
    unsigned char cell_toilet_cnt;
}TAG;

//���Ա�����������,���ǻ��������������������,�����ٶȾ���,�м�С�ĳ������,
AREA_TYPE findNodeArea(TAG *tag);
AREA_TYPE confirmNodeArea(TAG *tag);
RESULT initAllTag();
RESULT initAllArea();
void testCheckNode();
#endif
