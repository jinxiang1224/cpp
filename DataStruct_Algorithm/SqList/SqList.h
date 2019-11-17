#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

/************************************************************************
                      顺序表特点总结                                 
1.顺序表是一组存储地址连续的存储单元
2.顺序表的插入、删除、查找时间复杂度为O(n)
3.适用于不经常删除、插入、查找的场景
4.顺序表具有随机存取的特点
************************************************************************/

typedef int ElemType;
typedef unsigned int UINT32;

/*线性表结构*/
typedef struct
{
    ElemType  *elem;     /*元素类型*/
    UINT32       nLength;  /*线性表当前大小*/
    UINT32       nCapacity;/*线性表当前最大容量*/
    UINT32       nIncrementSize;/*线性表扩充幅度*/
}STRU_SQ_LIST, *PSTRU_SQ_LIST;

#define  INI_MAX_SIZE  (5)
#define  INCREMENT_SIZE (3)

/*初始化线性表*/
int InitList_Sq(STRU_SQ_LIST* list);

/*创建线性表*/
int CreateList_Sq(STRU_SQ_LIST* list, 
               int nMaxSize = INI_MAX_SIZE,
               int nInCrementSize = INCREMENT_SIZE);

/*查找元素*/
int FindElem_Sq(STRU_SQ_LIST* list,ElemType data);

/*插入元素*/
int InsertElem_Sq(STRU_SQ_LIST* list,unsigned nPos, ElemType data);

/*插入元素*/
int Pushback_Sq(STRU_SQ_LIST* list, ElemType data);

/*元素扩充*/
int Increment(STRU_SQ_LIST* list);

/*元素删除*/
int DeleteElem_Sq(STRU_SQ_LIST* list,unsigned nPos, ElemType* data);

/*获取长度*/
int GetLenth_Sq(STRU_SQ_LIST* list);

/*获取某个位置的元素*/
int GetElem(STRU_SQ_LIST* list,unsigned nPos, ElemType* data);

/*判断释放为空表*/
bool IsEmpty_Sq(STRU_SQ_LIST* list);

/*打印元素*/
int PrintList_Sq(STRU_SQ_LIST* list);

/*销毁线性表*/
int Destory_Sq(STRU_SQ_LIST* list);

/*以下为扩展功能*/

/*翻转线性表*/
int ReverseList_Sq(STRU_SQ_LIST* list);

/*比较线性表大小*/
int CompareList_Sq(STRU_SQ_LIST* list1,STRU_SQ_LIST* list2);

/*从list2中构造提取元素不同的线性表*/
int GetUniqueElem_Sq(STRU_SQ_LIST* list1,STRU_SQ_LIST* list2);


/*测试线性表用例*/

int test_sq_list();


#endif
