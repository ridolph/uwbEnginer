#ifndef LINKLIST_H
#define LINKLIST_H


#include <QString>

/*  数据类型重定义  */
typedef unsigned char   uint_8;
typedef unsigned short  uint_16;
typedef unsigned int    uint_32;


/*  节点类型标志    */
#define TAG_NODE_FLAG   1
#define ANC_NODE_FLAG   2



/*  基站信息结构体  */
typedef struct 
{
    uint_8      type;                       /*  消息类型    */
    uint_8      anchor_id;                  /*  基站编号    */
    uint_8      anchor_status;              /*  基站状态    */
    uint_16     online_tag_number;          /*  在线标签数量*/
    uint_32     timestamp;                  /*  时间戳  */

    double      pos_x;                      /*  坐标X   */  
    double      pos_y;                      /*  坐标Y   */
    double      pos_z;                      /*  坐标Z   */
    
}AncInfoStr;



/*  标签信息结构体  */
typedef struct
{
    uint_8      type;           /*  消息类型    */
    uint_16     tag_id;         /*  标签ID  */
    uint_16     tag_status;     /*  标签状态    */
    uint_32     pos_code;       /*  所在地区编号    */
    uint_32     timestamp;      /*  时间戳  */
    
    double      pos_x;          /*  坐标X   */
    double      pos_y;          /*  坐标Y   */
    double      pos_z;          /*  坐标Z   */

    QString     up_time;        /*  上线时间    */
    QString     down_time;      /*  下线时间    */
    
    uint_16     heart_rate;     /*  心率值  */     
    uint_16     tag_charge;     /*  标签电量    */
}TagInfoStr;




/*  基站节点信息    */
typedef struct AncLinkNode
{
    AncInfoStr data;
    struct AncLinkNode* next;
}AncLinkNode;



/*  标签节点信息    */
typedef struct TagLinkNode
{
    TagInfoStr data;
    struct TagLinkNode *next;
}TagLinkNode;





class LinkList
{
public:
    LinkList();
    ~LinkList();


    void LinkListInsert(AncInfoStr data);
    void LinkListInsert(TagInfoStr data);
    void LinkListModify(AncLinkNode data);
    void LinkListModify(TagLinkNode data);
    void LinkListGetData(AncLinkNode *data);
    void LinkListGetData(TagLinkNode *data);
    void LinkListDelData(AncLinkNode data);
    void LinkListDelData(TagLinkNode data);
    

private:
    AncLinkNode *anc_head;  /*  基站节点    */
    TagLinkNode *tag_head;  /*  标签节点    */
    int anc_length;
    int tag_length;     
};

#endif // LINKLIST_H