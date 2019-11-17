
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
    return ListInfo.pHead != NULL ? ListInfo.pHead->prev : NULL;
}

/*获取第一个结点*/
PDuLNode GetHeadNode(const DuLNodeInfo& ListInfo)
{
    return ListInfo.pHead != NULL ? ListInfo.pHead->next : NULL;
}

/*置空单链表，保留头结点*/
int ClearDuLinkList(DuLNodeInfo& ListInfo)
{
    PDuLNode CurNode = GetHeadNode(ListInfo);
    if (CurNode == NULL)
    {
        return DA_SUCCESS;
    }

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

void SafeFreeHead(DuLNodeInfo& ListInfo)
{
    if (ListInfo.pHead != NULL)
    {
        free(ListInfo.pHead);
        ListInfo.pHead = NULL;
    }

    ListInfo.nLenth = 0;
}
/*销毁链表*/
int DestoryDuLinkList(DuLNodeInfo& ListInfo)
{
    ClearDuLinkList(ListInfo);

    SafeFreeHead(ListInfo);

    return DA_SUCCESS;
}

int GetDuListLen(DuLNodeInfo& Head)
{
    return Head.nLenth;
}

/*添加一个结点*/
int _AddNode(PDuLNode newnode, PDuLNode pre, PDuLNode next)
{
    printf("add node =%d\n",newnode->data);

    newnode->next = next;
    pre->next = newnode;

    newnode->prev = pre;
    next->prev = newnode;

    return DA_SUCCESS;
}

int ListAddNode(DuLNodeInfo& ListInfo,PDuLNode newnode, PDuLNode pre, PDuLNode next)
{
   ListInfo.nLenth++;
   return _AddNode(newnode,pre,next);
}

/*将当前结点从链表中删除*/
int _DelNode(PDuLNode delNode)
{
    printf("delete node =%d\n",delNode->data);

    PDuLNode pre = delNode->prev;
    PDuLNode next = delNode->next;

    pre->next = next;
    next->prev = pre;

    return DA_SUCCESS;
}

int ListDelNode(DuLNodeInfo& ListInfo,PDuLNode delNode)
{
    ListInfo.nLenth--;
    return _DelNode(delNode);
}

/*追加结点*/
int InsertAfterLinkList(DuLNodeInfo& ListInfo, NodeType data)
{
    PDuLNode NewNode = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;

    return ListAddNode(ListInfo,NewNode,ListInfo.pHead->prev, ListInfo.pHead);
}

/*在头结点后插入*/
int InsertBeforeLinkList(DuLNodeInfo& ListInfo, NodeType data)
{
    PDuLNode NewNode = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    return ListAddNode(ListInfo,NewNode, ListInfo.pHead, ListInfo.pHead->next);
}


/*删除结点并释放资源*/
int DelDuLinkListNode(DuLNodeInfo& ListInfo,PDuLNode& delnode)
{
    ListDelNode(ListInfo,delnode);
    free(delnode);
    delnode = NULL;
    return DA_SUCCESS;
}

/*链表查找*/
PDuLNode FindDuLinkListNode(DuLNodeInfo& ListInfo,NodeType DataValue)
{
    PDuLNode curNode = GetHeadNode(ListInfo);
    PDuLNode FindNode = NULL;

    while (curNode != ListInfo.pHead && curNode != NULL)
    {
        if (curNode->data == DataValue)
        {
            FindNode = curNode;
            break;
        }
        curNode = curNode->next;
    }

    return FindNode;
}
int UnionDuLinkList(DuLNodeInfo& ListInfo1, DuLNodeInfo& ListInfo2)
{

    if (ListInfo1.nLenth == 0)
    {
        DuLNodeInfo ListInfo = ListInfo1;
        ListInfo1 = ListInfo2;
        ListInfo1 = ListInfo;
    }
    else
    {
        PDuLNode curNode = GetHeadNode(ListInfo2);
        PDuLNode FindNode = NULL;
        PDuLNode NextNode = NULL;
        /*遍历list2结点 O(M)*/
        while (curNode != ListInfo2.pHead)
        {
            NextNode = curNode->next;
            //不存在的则插入list1，否则从list2中删除
            //查找的时间复杂度为O(n)
            if (NULL != FindDuLinkListNode(ListInfo1,curNode->data))
            {
                DelDuLinkListNode(ListInfo2, curNode);
            }
            else
            {
                ListDelNode(ListInfo2,curNode);

                ListAddNode(ListInfo1,curNode,ListInfo1.pHead->prev,ListInfo1.pHead);
            }
            curNode = NextNode;
        }
    }

    return DA_SUCCESS;
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
    while(CurNode != ListInfo.pHead && CurNode != NULL)
    {
        printf("%d->",CurNode->data);
        CurNode = (bReverse ? CurNode->prev : CurNode->next);
    }

    printf("NULL,len = %d\n",GetDuListLen(ListInfo));
    return DA_SUCCESS;
}


void TestDuLinkList()
{
    DuLNodeInfo List1;
    DuLNodeInfo List2;
    InitDuLinkList(List1);
    InitDuLinkList(List2);

    InsertBeforeLinkList(List1,4);
    InsertAfterLinkList(List1,1);
    InsertAfterLinkList(List1,2);
    InsertAfterLinkList(List1,3);

    PrintDuLinkList(List1);

    /*
    PDuLNode FindNode = NULL;
    if (FindDuLinkListNode(List1,FindNode,1) == DA_SUCCESS)
    {
        DelDuLinkListNode(List1,FindNode);
    }
    PrintDuLinkList(List1, true);
    */


    InsertBeforeLinkList(List2,1);
    InsertBeforeLinkList(List2,2);
    InsertBeforeLinkList(List2,32);
    PrintDuLinkList(List2);

    UnionDuLinkList(List1, List2);
    printf("union link list:");
    PrintDuLinkList(List1);

    InsertBeforeLinkList(List2,11);
    InsertBeforeLinkList(List2,2);
    InsertBeforeLinkList(List2,32);
    PrintDuLinkList(List2);


    DestoryDuLinkList(List1);
    DestoryDuLinkList(List2);
}