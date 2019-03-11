/********************************************************************************

 * Copyright (C), 2019-2020, QianKunWuLian. Co., Ltd.

 * FileName: LinkList.cpp

 * Author:	Luo     Version:	V2.0      Date:	20190308	

 * Description:     �������

 * Version:       	V2.0

 * Function List:   

    1. -------

 * History:         // ��ʷ�޸ļ�¼

      <author>  <time>   <version >   <desc>

      	Luo    19/03/08     2.0       �½�ģ��

 *******************************************************************************/
 


#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/*************************************************************
*	Name:		LinkList
*	Func:		���캯��
*	Input:		
*	Output:		
*	Return:		
**************************************************************/
LinkList::LinkList()
{
	anc_head = new AncLinkNode;
	anc_head->next = NULL;
	anc_length = 0;

	tag_head = new TagLinkNode;
	tag_head->next = NULL;
	tag_length = 0;
}

/*************************************************************
*	Name:		~LinkList
*	Func:		��������
*	Input:		
*	Output:		
*	Return:		
**************************************************************/
LinkList::~LinkList()
{
	printf("~LinkList()\n");
	delete anc_head;
	delete tag_head;
	tag_length = 0;
	tag_length = 0;
}




/*************************************************************
*	Name:		LinkListInsert
*	Func:		��������	β�巨
*	Input:		Ҫ���������,AncLinkNode ��վ��Ϣ
*	Output:		
*	Return:		void
**************************************************************/
void LinkList::LinkListInsert(AncInfoStr data)
{
	AncLinkNode *p;
	AncLinkNode *temp;

	p = anc_head;

	temp = new AncLinkNode;
	temp->data = data;
	p->next = temp;
	p = temp;
}

/*************************************************************
*	Name:		LinkListInsert
*	Func:		��������	β�巨
*	Input:		Ҫ���������,TagLinkNode ��ǩ��Ϣ
*	Output:		
*	Return:		void
**************************************************************/
void LinkList::LinkListInsert(TagInfoStr data)
{
	TagLinkNode *p;
	TagLinkNode *temp;

	p = tag_head;

	temp = new TagLinkNode;
	temp->data = data;
	p->next = temp;
	p = temp;
}


/*************************************************************
*	Name:		LinkListInsert
*	Func:		�޸�������Ϣ
*	Input:		Ҫ�޸ĵ�����,AncLinkNode ��վ��Ϣ
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListModify(AncLinkNode data)
{

}

/*************************************************************
*	Name:		LinkListModify
*	Func:		�޸�������Ϣ
*	Input:		Ҫ�޸ĵ�����,TagLinkNode ��ǩ��Ϣ
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListModify(TagLinkNode data)
{

}

/*************************************************************
*	Name:		LinkListGetData
*	Func:		��ȡ������������	AncLinkNode ��վ��Ϣ
*	Input:		��ȡ���ݴ�ŵĵ�ַ
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListGetData(AncLinkNode *data)
{

}

/*************************************************************
*	Name:		LinkListGetData
*	Func:		��ȡ������������	TagLinkNode ��ǩ��Ϣ
*	Input:		Ҫ���������,TagLinkNode ��ǩ��Ϣ
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListGetData(TagLinkNode *data)
{

}

/*************************************************************
*	Name:		LinkListDelData
*	Func:		ɾ����������
*	Input:		Ҫɾ��������,AncLinkNode ��վ��Ϣ
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListDelData(AncLinkNode data)
{

}

/*************************************************************
*	Name:		LinkListDelData
*	Func:		ɾ����������
*	Input:		Ҫɾ��������,TagLinkNode ��վ��Ϣ
*	Output:		
*	Return:		void
**************************************************************/
void LinkList::LinkListDelData(TagLinkNode data)
{

}




