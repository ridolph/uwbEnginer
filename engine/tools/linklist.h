#ifndef LINKLIST_H
#define LINKLIST_H


#include <QString>

/*  ���������ض���  */
typedef unsigned char   uint_8;
typedef unsigned short  uint_16;
typedef unsigned int    uint_32;


/*  �ڵ����ͱ�־    */
#define TAG_NODE_FLAG   1
#define ANC_NODE_FLAG   2



/*  ��վ��Ϣ�ṹ��  */
typedef struct 
{
    uint_8      type;                       /*  ��Ϣ����    */
    uint_8      anchor_id;                  /*  ��վ���    */
    uint_8      anchor_status;              /*  ��վ״̬    */
    uint_16     online_tag_number;          /*  ���߱�ǩ����*/
    uint_32     timestamp;                  /*  ʱ���  */

    double      pos_x;                      /*  ����X   */  
    double      pos_y;                      /*  ����Y   */
    double      pos_z;                      /*  ����Z   */
    
}AncInfoStr;



/*  ��ǩ��Ϣ�ṹ��  */
typedef struct
{
    uint_8      type;           /*  ��Ϣ����    */
    uint_16     tag_id;         /*  ��ǩID  */
    uint_16     tag_status;     /*  ��ǩ״̬    */
    uint_32     pos_code;       /*  ���ڵ������    */
    uint_32     timestamp;      /*  ʱ���  */
    
    double      pos_x;          /*  ����X   */
    double      pos_y;          /*  ����Y   */
    double      pos_z;          /*  ����Z   */

    QString     up_time;        /*  ����ʱ��    */
    QString     down_time;      /*  ����ʱ��    */
    
    uint_16     heart_rate;     /*  ����ֵ  */     
    uint_16     tag_charge;     /*  ��ǩ����    */
}TagInfoStr;




/*  ��վ�ڵ���Ϣ    */
typedef struct AncLinkNode
{
    AncInfoStr data;
    struct AncLinkNode* next;
}AncLinkNode;



/*  ��ǩ�ڵ���Ϣ    */
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
    AncLinkNode *anc_head;  /*  ��վ�ڵ�    */
    TagLinkNode *tag_head;  /*  ��ǩ�ڵ�    */
    int anc_length;
    int tag_length;     
};

#endif // LINKLIST_H