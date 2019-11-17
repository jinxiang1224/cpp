
#include "LinkList.h"
#include <memory>
#include "../base.h"

int Init_LinkList(PLinkLNode *LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    *LinkHead = (PLinkLNode)malloc(sizeof(LinkLNode));
    (*LinkHead)->pNext = NULL;

    return DA_SUCCESS;
}

int Clear_LinkList(PLinkLNode LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    //从第一个结点开始清理
    PLinkLNode CurNode = LinkHead->pNext;
    PLinkLNode NextNode = NULL; 

    while (CurNode)
    {
        //下一个元素
        NextNode = CurNode->pNext;
        
        free(CurNode);

        CurNode = NextNode;
    }

    LinkHead->pNext = NULL;

    return DA_SUCCESS;
}

int Destory_LinkList(PLinkLNode* pLinkHead)
{
    CHECK_PTR_RETURN_ERROR(pLinkHead);
    
    Clear_LinkList(*pLinkHead);

    //释放头结点
    free(*pLinkHead);
    *pLinkHead = NULL;
    
    return DA_SUCCESS;
}

bool IsEmpty_LinkList(PLinkLNode LinkHead)
{
    CHECK_PTR_RETURN_FALSE(LinkHead);
    
    return LinkHead->pNext == NULL ? true : false; 
}

int Length_LinkList(PLinkLNode LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    //从首元素开始清理
    PLinkLNode curNode = LinkHead->pNext;
    int len = 0;

    while (curNode)
    {
        curNode = curNode->pNext;
        len++;
    }

    return len;
}

int GetElem_LinkList(PLinkLNode LinkHead, int pos, DataType *data)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    if (pos >= Length_LinkList(LinkHead))
    {
        return DA_ERROR;
    }

    PLinkLNode curNode = LinkHead->pNext;
    int cur_len = 0;

    while (curNode)
    {
        if (cur_len == pos)
        {
            *data = curNode->data;
            break;
        }

        curNode = curNode->pNext;
        cur_len++;
    }

    return cur_len == pos ? DA_SUCCESS : DA_ERROR;
}

int InsertNode_LinkList(PLinkLNode LinkHead, int pos, DataType data)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    if (pos >= Length_LinkList(LinkHead))
    {
        return DA_ERROR;
    }

    //第一个结点
    PLinkLNode curNode = LinkHead->pNext;
    PLinkLNode PriorNode = NULL;

    int nCurPos = 0;

    while (curNode)
    {
        if (nCurPos == pos)
        {
            GetPriorNode(LinkHead,curNode,&PriorNode);
            break;
        }
        curNode = curNode->pNext;
        nCurPos++;
    }

    if (NULL != PriorNode)
    {
        //新结点
        PLinkLNode NewNode = (PLinkLNode)malloc(sizeof(LinkLNode));
        CHECK_PTR_RETURN_ERROR(NewNode);
        NewNode->data = data;

        //curNode->pNext成为新结点的后继 
        NewNode->pNext = curNode;
        //PriorNode的后继为新结点NewNode
        PriorNode->pNext = NewNode;
    }
    else
    {
        printf("prior node is null\n");
    }



    return DA_SUCCESS;
}

int GetPriorNode(PLinkLNode LinkHead, PLinkLNode PosNode,PLinkLNode* PriorNode)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    CHECK_PTR_RETURN_ERROR(PosNode);
    CHECK_PTR_RETURN_ERROR(PriorNode);

    //从头结点开始
    PLinkLNode curNode = LinkHead;
    while (curNode)
    {
        //比较是否是前驱结点
        if (curNode->pNext == PosNode)
        {
            *PriorNode = curNode;
            break;
        }
        curNode = curNode->pNext;
    }

    return DA_SUCCESS;
}
int DeleteNode_LinkList(PLinkLNode LinkHead, int pos, DataType *pData)
{   
    CHECK_PTR_RETURN_ERROR(LinkHead);
    CHECK_PTR_RETURN_ERROR(pData);

    if (pos >= Length_LinkList(LinkHead))
    {
        return DA_ERROR;
    }

    //第一个结点
    PLinkLNode curNode = LinkHead->pNext;
    PLinkLNode PriorNode = NULL;
    int nCurPos = 0;

    while (curNode)
    {
        if (nCurPos == pos)
        {
            GetPriorNode(LinkHead,curNode,&PriorNode);
            break;
        }
        curNode = curNode->pNext;
        nCurPos++;
    }

    //改变后继
    PriorNode->pNext = curNode->pNext;

    //返回被删除的值
    *pData = curNode->data;
    free(curNode);
    curNode = NULL;

    return DA_SUCCESS;
}

int InsertNodeByTail(PLinkLNode LinkHead, DataType data)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    printf("insert data %d\n",data);

    //头结点
    PLinkLNode curNode = LinkHead;

    //判断是否到达尾结点
    while (curNode->pNext)
    {
        curNode = curNode->pNext;
    }

    //新结点
    PLinkLNode NewNode = (PLinkLNode)malloc(sizeof(LinkLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    NewNode->pNext = NULL;
    
    //改变后继结点
    curNode->pNext = NewNode;


    return DA_SUCCESS;
}

int InsertNodeByHead(PLinkLNode LinkHead, DataType data)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    printf("insert data %d\n",data);

    //新结点
    PLinkLNode NewNode = (PLinkLNode)malloc(sizeof(LinkLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    NewNode->pNext = LinkHead->pNext;

    LinkHead->pNext = NewNode;
    
    return DA_SUCCESS;
}

int PrintLinkList(PLinkLNode LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    //第一个结点
    PLinkLNode curNode = LinkHead->pNext;
    while (curNode)
    {
        printf("%d->",curNode->data);
        curNode = curNode->pNext;
    }
    printf("NULL\n");

    return DA_SUCCESS;
}

/*翻转链表*/
int ReverseLinkList(PLinkLNode *LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    //指向第一个结点
    PLinkLNode IndcateNode = (*LinkHead)->pNext;

    //将待逆置的表构造为空表
    PLinkLNode L = *LinkHead;
    L->pNext = NULL;

    PLinkLNode InsertNode = NULL;

    while(IndcateNode)
    {
        //保存被"删除"的结点信息
        InsertNode = IndcateNode;
        //指向下一个结点
        IndcateNode = IndcateNode->pNext;

        //头插入新结点
        InsertNode->pNext = L->pNext;//改变被"删除"的后继
        L->pNext = InsertNode;//改变头结点的后继
    }

    *LinkHead = L;

    return DA_SUCCESS;
}

/*翻转链表*/
int ReverseLinkList2(PLinkLNode *LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    //指向第一个结点
    PLinkLNode p = (*LinkHead)->pNext;
    if (p == NULL)
    {
        return DA_SUCCESS;
    }

    //p的后继结点
    PLinkLNode q = p->pNext;

    //第一个结点的指针域
    p->pNext = NULL;

    //临时结点
    PLinkLNode pre = NULL;

    while(q)
    {
        //保存结点
        pre = p;

        //移动结点
        p = q;
        q = q->pNext;

        //改变链表指向
        p->pNext = pre;
    }

    (*LinkHead)->pNext = p;

    return DA_SUCCESS;
}


void Test_LinkList()
{
    PLinkLNode Head = NULL;
    
    Init_LinkList(&Head);

    if (IsEmpty_LinkList(Head))
    {
        printf("link list is empty\n");
    }

    InsertNodeByHead(Head,1);
    InsertNodeByHead(Head,2);
    InsertNodeByHead(Head,3);
    InsertNodeByHead(Head,4);

    PrintLinkList(Head);

    Clear_LinkList(Head);
    printf("clear list\n");
    InsertNodeByTail(Head,10);
    InsertNodeByTail(Head,20);

    PrintLinkList(Head);

    DataType DataValue = 0;
    
    if (DA_SUCCESS != DeleteNode_LinkList(Head, 1,&DataValue))
    {
        printf("delete node error ...\n");
    } 
    else
    {
        printf("delete data %d\n",DataValue);
        PrintLinkList(Head);
    }

    InsertNode_LinkList(Head,0,110);
    InsertNode_LinkList(Head,1,1100);

    PrintLinkList(Head);
    
    ReverseLinkList(&Head);

    PrintLinkList(Head);

    ReverseLinkList2(&Head);

    PrintLinkList(Head);

    Destory_LinkList(&Head);
}
