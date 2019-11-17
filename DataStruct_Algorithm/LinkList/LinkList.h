#ifndef  __LINK_LIST_H__
#define  __LINK_LIST_H__

typedef int DataType;

/*单链表的线性表结构*/
typedef struct LNode 
{
    DataType  data;     /*元素类型*/
    struct LNode* pNext;
}LinkLNode, *PLinkLNode;

/*带头结点的单链表列表*/

/*初始化单链表*/
int Init_LinkList(PLinkLNode *pLinkHead);

/*置空单链表，保留头结点*/
int Clear_LinkList(PLinkLNode LinkHead);

/*销毁单链表，连同头结点也销毁*/
int Destory_LinkList(PLinkLNode* pLinkHead);

/*判断链表是否为空*/
bool IsEmpty_LinkList(PLinkLNode LinkHead);

/*返回链表元素的个数*/
int Length_LinkList(PLinkLNode LinkHead);

/*返回第i个链表元素*/
int GetElem_LinkList(PLinkLNode LinkHead, int i, DataType *e);

/*查找元素*/
//int FindElem_LinkList(PLinkLNode LinkHead, DataType data, PLinkLNode node);

/*在单链表L第i个位置之前插入e*/
int InsertNode_LinkList(PLinkLNode LinkHead, int i, DataType data);

/*删除单链表L第i个位置的值，并用e接收*/
int DeleteNode_LinkList(PLinkLNode LinkHead, int pos, DataType *pData);

/*头插法建立单链表L(逆序输入)*/
int InsertNodeByHead(PLinkLNode LinkHead, DataType data);

/*尾插法建立单链表L(顺序输入)*/
int InsertNodeByTail(PLinkLNode LinkHead, DataType data);

/*获取前驱元素*/
int GetPriorNode(PLinkLNode LinkHead, PLinkLNode PosNode,PLinkLNode* PriorNode);

/*打印元素*/
int PrintLinkList(PLinkLNode LinkHead);

/*翻转链表*/
int ReverseLinkList(PLinkLNode* LinkHead);


void Test_LinkList();

#endif
