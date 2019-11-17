#ifndef __DU_CIRCULAR_LINKEDLIST__
#define __DU_CIRCULAR_LINKEDLIST__

typedef  int NodeType;

/*真正结点信息*/
typedef struct _DuLNode
{
    NodeType data;
    struct _DuLNode *prev;
    struct _DuLNode *next;
}DuLNode,*PDuLNode;

/*链表信息*/
/*相对普通结构,这种方式可以快速获取链表长度,避免的遍历操作*/
typedef struct
{
    int     nLenth; /*链表长度*/
    PDuLNode pHead;  /*链表头结点*/
}DuLNodeInfo;

/*初始化双向循环链表*/
int InitDuLinkList(DuLNodeInfo& ListInfo);

/*置空单链表，保留头结点*/
int ClearDuLinkList(DuLNodeInfo& ListInfo);

/*销毁链表*/
int DestoryDuLinkList(DuLNodeInfo& ListInfo);

/*添加一个结点,结点本身已存在*/
int ListAddNode(DuLNodeInfo& ListInfo,PDuLNode newnode, PDuLNode pre, PDuLNode next);

/*删除一个结点，结点本身仍存在*/
int ListDelNode(DuLNodeInfo& ListInfo,PDuLNode delNode);

/*获取链表长度*/
int GetDuListLen(DuLNodeInfo& ListInfo);

/*在头结点后插入，新生成的结点*/
int InsertBeforeLinkList(DuLNodeInfo& ListInfo, NodeType data);

/*追加结点，新生成的结点*/
int InsertAfterLinkList(DuLNodeInfo& ListInfo, NodeType data);

/*获取头结点*/
PDuLNode GetTailNode(const DuLNodeInfo& ListInfo);

/*获取尾结点*/
PDuLNode GetHeadNode(const DuLNodeInfo& ListInfo);

/*删除结点并释放资源*/
int DelDuLinkListNode(DuLNodeInfo& ListInfo,PDuLNode& delnode);

/*链表查找*/
PDuLNode FindDuLinkListNode(DuLNodeInfo& ListInfo,NodeType DataValue);

/*链表打印*/
int UnionDuLinkList(DuLNodeInfo& ListInfo1, DuLNodeInfo& ListInfo2);

/*链表打印*/
int PrintDuLinkList(DuLNodeInfo& ListInfo, bool bReverse = false);

void TestDuLinkList();



#endif
