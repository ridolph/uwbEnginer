/********************************************************************************

 * Copyright (C), 2019-2020, QianKunWuLian. Co., Ltd.

 * FileName: LinkList.cpp

 * Author:	Luo     Version:	V2.0      Date:	20190308	

 * Description:     链表操作

 * Version:       	V2.0

 * Function List:   

    1. -------

 * History:         // 历史修改记录

      <author>  <time>   <version >   <desc>

      	Luo    19/03/08     2.0       新建模块

 *******************************************************************************/
 


#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/*************************************************************
*	Name:		LinkList
*	Func:		构造函数
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
*	Func:		析构函数
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
*	Func:		插入链表	尾插法
*	Input:		要插入的数据,AncLinkNode 基站信息
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
*	Func:		插入链表	尾插法
*	Input:		要插入的数据,TagLinkNode 标签信息
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
*	Func:		修改链表信息
*	Input:		要修改的数据,AncLinkNode 基站信息
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListModify(AncLinkNode data)
{

}

/*************************************************************
*	Name:		LinkListModify
*	Func:		修改链表信息
*	Input:		要修改的数据,TagLinkNode 标签信息
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListModify(TagLinkNode data)
{

}

/*************************************************************
*	Name:		LinkListGetData
*	Func:		获取整个链表数据	AncLinkNode 基站信息
*	Input:		获取数据存放的地址
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListGetData(AncLinkNode *data)
{

}

/*************************************************************
*	Name:		LinkListGetData
*	Func:		获取整个链表数据	TagLinkNode 标签信息
*	Input:		要插入的数据,TagLinkNode 标签信息
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListGetData(TagLinkNode *data)
{

}

/*************************************************************
*	Name:		LinkListDelData
*	Func:		删除链表数据
*	Input:		要删除的数据,AncLinkNode 基站信息
*	Output:		
*	Return:		void
**************************************************************/

void LinkList::LinkListDelData(AncLinkNode data)
{

}

/*************************************************************
*	Name:		LinkListDelData
*	Func:		删除链表数据
*	Input:		要删除的数据,TagLinkNode 基站信息
*	Output:		
*	Return:		void
**************************************************************/
void LinkList::LinkListDelData(TagLinkNode data)
{

}




