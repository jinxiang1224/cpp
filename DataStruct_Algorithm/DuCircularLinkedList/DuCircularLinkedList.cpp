
#include "DuCircularLinkedList.h"
#include "../base.h"

/* 
双向循环链表
ListInfo
 ____      head       node       node         head
|len |     ___        ___        ___          ___ 
|----|<---|   | <--- |   | <--- |   |  <---  |   |
|Head|--->|   | ---> |   | ---> |   |   ---> |   | 
|____|    |___|      |___|      |___|        |___|
                    
*/                         
int InitDuLinkList(DuLNodeInfo& ListInfo)
{
    ListInfo.pHead = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(ListInfo.pHead);

    ListInfo.pHead->data = -1;
    /*空循环链表*/
    ListInfo.pHead->prev = ListInfo.pHead;
    ListInfo.pHead->next = ListInfo.pHead;
    /*长度为0*/
    ListInfo.nLenth = 0;

    return DA_SUCCESS;
}

/*获取尾部结点*/
PDuLNode GetTailNode(const DuLNodeInfo& ListInfo)
{
    return ListInfo.pHead->prev;
}

/*获取第一个结点*/
PDuLNode GetHeadNode(const DuLNodeInfo& ListInfo)
{
    return ListInfo.pHead->next;
}

/*置空单链表，保留头结点*/
int ClearDuLinkList(DuLNodeInfo& ListInfo)
{
    PDuLNode CurNode = GetHeadNode(ListInfo);
    PDuLNode NextNode = NULL;
    while(CurNode != ListInfo.pHead)
    {
        NextNode = CurNode->next;
        free(CurNode);
        CurNode = NextNode;
    }

    /*指向头结点本身*/
    ListInfo.pHead->next = ListInfo.pHead;
    ListInfo.pHead->prev = ListInfo.pHead;
    ListInfo.nLenth = 0;

    return DA_SUCCESS;
}

/*销毁链表*/
int DestoryDuLinkList(DuLNodeInfo& ListInfo)
{
    ClearDuLinkList(ListInfo);

    free(ListInfo.pHead);
    ListInfo.pHead = NULL;

    return DA_SUCCESS;
}

int GetDuListLen(DuLNodeInfo& Head)
{
    return Head.nLenth;
}

/*添加一个结点*/
int AddNode(PDuLNode newnode, PDuLNode pre, PDuLNode next)
{
    printf("add node =%d\n",newnode->data);

    newnode->next = next;
    pre->next = newnode;

    newnode->prev = pre;
    next->prev = newnode;

    return DA_SUCCESS;
}

/*将当前结点从链表中删除*/
int DelNode(PDuLNode delNode)
{
    printf("delete node =%d\n",delNode->data);

    PDuLNode pre = delNode->prev;
    PDuLNode next = delNode->next;

    pre->next = next;
    next->prev = pre;

    return DA_SUCCESS;
}

/*追加结点*/
int InsertAfterLinkList(DuLNodeInfo& ListInfo, NodeType data)
{
    PDuLNode NewNode = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    ListInfo.nLenth++;

    return AddNode(NewNode,ListInfo.pHead->prev, ListInfo.pHead);
}

/*在头结点后插入*/
int InsertBeforeLinkList(DuLNodeInfo& ListInfo, NodeType data)
{
    PDuLNode NewNode = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    ListInfo.nLenth++;
    return AddNode(NewNode, ListInfo.pHead, ListInfo.pHead->next);
}


/*删除结点并释放资源*/
int DelDuLinkListNode(DuLNodeInfo& ListInfo,PDuLNode& delnode)
{
    DelNode(delnode);
    free(delnode);
    delnode = NULL;

    ListInfo.nLenth--;
    return DA_SUCCESS;
}

/*链表查找*/
int FindDuLinkListNode(DuLNodeInfo& ListInfo, PDuLNode& FindNode,NodeType DataValue)
{
    PDuLNode curNode = GetHeadNode(ListInfo);
    int bRet = DA_ERROR;

    while (curNode != ListInfo.pHead && curNode != NULL)
    {
        if (curNode->data == DataValue)
        {
            FindNode = curNode;
            bRet = DA_SUCCESS;
            break;
        }
        curNode = curNode->next;
    }

    return bRet;
}

/*链表打印*/
int PrintDuLinkList(DuLNodeInfo& ListInfo, bool bReverse/* = false*/)
{
    PDuLNode CurNode = NULL;

    if (bReverse)
    {
        CurNode = GetTailNode(ListInfo);
        printf("from tail print:");
    } 
    else
    {
        CurNode = GetHeadNode(ListInfo);
        printf("from head print:");
    }

    //结束条件为是否等于头结点
    while(CurNode != ListInfo.pHead)
    {
        printf("%d->",CurNode->data);
        CurNode = (bReverse ? CurNode->prev : CurNode->next);
    }

    printf("NULL,len = %d\n",GetDuListLen(ListInfo));
    return DA_SUCCESS;
}


void TestDuLinkList()
{
    DuLNodeInfo head;
    InitDuLinkList(head);
    PrintDuLinkList(head);
    InsertBeforeLinkList(head,4);
    InsertAfterLinkList(head,1);
    InsertAfterLinkList(head,2);
    InsertBeforeLinkList(head,3);

    PrintDuLinkList(head);

    PDuLNode FindNode = NULL;
    if (FindDuLinkListNode(head,FindNode,1) == DA_SUCCESS)
    {
        DelDuLinkListNode(head,FindNode);
    }
    PrintDuLinkList(head, true);

    ClearDuLinkList(head);

    PrintDuLinkList(head);

    InsertBeforeLinkList(head,1);
    InsertBeforeLinkList(head,2);
    InsertBeforeLinkList(head,3);

    PrintDuLinkList(head);

    DestoryDuLinkList(head);
}