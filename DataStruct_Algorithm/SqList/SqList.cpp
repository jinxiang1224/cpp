#include "SqList.h"
#include <memory>
#include "../base.h"

void print_error()
{
    printf("%s error %d ...\n",__FUNCTION__,__LINE__);
}

int InitList_Sq(STRU_SQ_LIST* list)
{
    CHECK_PTR_RETURN_ERROR(list);
    list->elem = NULL;
    list->nCapacity  = INI_MAX_SIZE;
    list->nLength = 0;
    list->nIncrementSize = INCREMENT_SIZE;
    
    return DA_SUCCESS;
}

int CreateList_Sq(STRU_SQ_LIST* list, int nMaxSize /* = INI_MAX_SIZE */, int nInCrementSize /* = INCREMENT_SIZE */)
{
    CHECK_PTR_RETURN_ERROR(list);

    InitList_Sq(list);
    
    //线性数组地址
    list->elem = (ElemType*)malloc(sizeof(ElemType) * nMaxSize);
    if (NULL == list->elem)
    {
        return DA_ERROR;
    }
    memset(list->elem,0,sizeof(ElemType) * nMaxSize);

    list->nCapacity = nMaxSize;
    list->nIncrementSize = nInCrementSize;
    list->nLength = 0;

    return DA_SUCCESS;
}

/*时间复杂度为O(n)*/
int FindElem_Sq(STRU_SQ_LIST* list,ElemType data)
{
    CHECK_PTR_RETURN_ERROR(list);

    int ret = DA_ERROR;

    for (UINT32 i = 0; i < list->nLength; i++)
    {
        if (data == list->elem[i])
        {
            ret = DA_SUCCESS;
            break;
        }
    }

    return ret;
}

/*时间复杂度为O(1) 常量级别*/
int Pushback_Sq(STRU_SQ_LIST* list, ElemType data)
{
    CHECK_PTR_RETURN_ERROR(list);

    //先扩展 后赋值
    if (list->nLength >= list->nCapacity)
    {
        //扩容
        printf("recreate sq list...\n");
        Increment(list);
        printf("recreate sq list ok...\n");
    }

    list->elem[list->nLength] = data;
    list->nLength++;
    return DA_SUCCESS;
}

/*时间复杂度为O(n)=(n-1)/2 */
int InsertElem_Sq(STRU_SQ_LIST* list,unsigned nPos, ElemType data)
{
    CHECK_PTR_RETURN_ERROR(list);

    if (nPos > (list->nLength + 1))
    {
        print_error();
        return DA_ERROR;
    }

     //先扩展 后赋值  在赋值
    if (list->nLength >= list->nCapacity)
    {
        //扩容
        printf("recreate sq list...\n");
        Increment(list);
        printf("recreate sq list ok...\n");
        
    }

    //往右移
    for (UINT32 i = list->nLength; i > nPos; i--)
    {
        list->elem[i] = list->elem[i-1];
    }
    
    list->elem[nPos] = data;
    list->nLength++;

    return DA_ERROR;
}

int Increment(STRU_SQ_LIST* list)
{
    CHECK_PTR_RETURN_ERROR(list);

    size_t new_buff_size = list->nCapacity + list->nIncrementSize;

    ElemType* new_buff = (ElemType*)(malloc(sizeof(ElemType)*new_buff_size));
    if (NULL == new_buff)
    {
        print_error();
        return DA_ERROR;
    }

    memset(new_buff,0,sizeof(ElemType) * new_buff_size);
    
    for (UINT32 i = 0; i < list->nLength; i++)
    {
        new_buff[i] = list->elem[i];
    }
    
    free(list->elem);

    list->elem = new_buff;
    list->nCapacity  += list->nIncrementSize;

    return DA_SUCCESS;
}

/*时间复杂度为O(n)=(n-1)/2 */
int DeleteElem_Sq(STRU_SQ_LIST* list, unsigned nPos, ElemType* data)
{
    CHECK_PTR_RETURN_ERROR(list);

    if (nPos >= list->nLength)
    {
        return DA_ERROR;
    }

    //返回值
    *data = list->elem[nPos];

    //元素左移
    for (UINT32 i = nPos + 1; i < list->nLength; i++)
    {
        list->elem[i - 1] = list->elem[i];
    }

    list->nLength--;

    printf("delete data %d..\n", *data);

    return DA_SUCCESS;
}

int GetLenth_Sq(STRU_SQ_LIST* list)
{
    CHECK_PTR_RETURN_ERROR(list);

    return list->nLength;
}

bool IsEmpty_Sq(STRU_SQ_LIST* list)
{
    CHECK_PTR_RETURN_FALSE(list);

    return list->nLength == 0 ? true : false;
}

int PrintList_Sq(STRU_SQ_LIST* list)
{
    CHECK_PTR_RETURN_ERROR(list);
    for (UINT32 i = 0; i < list->nLength; i++)
    {
        printf("%d\t",list->elem[i]);
    }
    printf("\n");

    return DA_SUCCESS;
}

int Destory_Sq(STRU_SQ_LIST* list)
{
    CHECK_PTR_RETURN_ERROR(list);
    free(list->elem);
    list->elem = NULL;
    list->nLength = 0;
    list->nCapacity = 0;
    return DA_ERROR;
}

int GetElem(STRU_SQ_LIST* list,unsigned nPos, ElemType* data)
{
    CHECK_PTR_RETURN_ERROR(list);

    if (nPos >= list->nLength)
    {
        return DA_ERROR;
    }

    //返回值
    *data = list->elem[nPos];

    return DA_SUCCESS;
}
//1 == 2 : 0 1 > 2 : 1 1 < 2 : -1
int CompareList_Sq(STRU_SQ_LIST* list1,STRU_SQ_LIST* list2)
{
    CHECK_PTR_RETURN_ERROR(list1);
    CHECK_PTR_RETURN_ERROR(list2);

    int i = 0;

    //先进行字典排序，直至某一个list比较完成
    for (;i < list1->nLength && i < list2->nLength; i++)
    {
        if (list1->elem[i] > list2->elem[i])
        {
            return  1;
        }
        else if (list1->elem[i] < list2->elem[i])
        {
            return -1;
        }
    }

    //后续再比较长度，得出大小
    if (list1->nLength == list2->nLength)
    {
        return 0;
    }
    else if (list1->nLength > list2->nLength)
    {
        return 1;
    }

    return -1;
}

void swap(ElemType* a, ElemType* b)
{
   ElemType c = *a;
   *a = *b;
   *b = c;
}

int ReverseList_Sq(STRU_SQ_LIST* list)
{
    UINT32 usMiddle = list->nLength / 2;
    //需要交换的次数
    for (int i = 0; i < usMiddle; i++)
    {
        //首尾交换
        swap(&(list->elem[i]), &(list->elem[list->nLength - i - 1]));
    }

    return DA_SUCCESS;
}

/*
时间复杂度为 O(n^2)
*/
int GetUniqueElem_Sq(STRU_SQ_LIST* list1,STRU_SQ_LIST* list2)
{
    CHECK_PTR_RETURN_ERROR(list1);
    CHECK_PTR_RETURN_ERROR(list2);

    if (list2->nLength == 0)
    {
        return DA_ERROR;
    }

    //第一个必定不重复
    Pushback_Sq(list1, list2->elem[0]);

    //剩余的检测
    for (UINT32 i = 1; i < list2->nLength; i++)
    {
      if (DA_ERROR == FindElem_Sq(list1, list2->elem[i]))
      {
          Pushback_Sq(list1, list2->elem[i]);
      }
    }

    return DA_SUCCESS;
}



int test_sq_list()
{
    STRU_SQ_LIST list;
    PSTRU_SQ_LIST pList = &list;
    CreateList_Sq(pList);

    if (IsEmpty_Sq(pList))
    {
        printf("sq list is empty...\n");
    }

    Pushback_Sq(pList,121);
    Pushback_Sq(pList,123);
    Pushback_Sq(pList,122);

    InsertElem_Sq(pList,0,11);
    InsertElem_Sq(pList,1,12);
    Pushback_Sq(pList,1232);

    PrintList_Sq(pList);

    ReverseList_Sq(pList);

    PrintList_Sq(pList);

    Destory_Sq(pList);

    pList = NULL;


    STRU_SQ_LIST list1;
    STRU_SQ_LIST list2;

    CreateList_Sq(&list1);

    CreateList_Sq(&list2);
    Pushback_Sq(&list2,1);
    Pushback_Sq(&list2,22);
    Pushback_Sq(&list2,12);
    Pushback_Sq(&list2,22);

    printf("compare sq list %d\n",CompareList_Sq(&list1,&list2));

    GetUniqueElem_Sq(&list1, &list2);

    PrintList_Sq(&list1);

    Destory_Sq(&list1);
    Destory_Sq(&list2);

    return 0;
}

