#include "base.h"

#ifndef  __HASH_H__
#define  __HASH_H__

typedef enum
{
    EN_STATUS_EMPTY,
    EN_STATUS_DELETE,
    EN_STATUS_EXIST,
}ENUM_DATA_STATUS;

typedef int DATA_TYPE;

typedef struct
{
    DATA_TYPE   key;
    ENUM_DATA_STATUS status;
}STRU_HASH_NODE;

typedef struct
{
    STRU_HASH_NODE* hashNode;
    int size;
    int capacity;
}HASH_TABLE;

int InitHash(HASH_TABLE* table, int capacity);

/*创建哈希表*/
int CreateHash(HASH_TABLE* table, int capacity);

/*哈希表关键字搜索*/
bool SearchHash(HASH_TABLE* table, DATA_TYPE data);

/*哈希表插入关键字*/
int InsertHash(HASH_TABLE *table, DATA_TYPE data);

/*删除指定的关键字*/
bool RemoveHash(HASH_TABLE* table, DATA_TYPE data);

/*检测是否需要扩容*/
bool CheckCapacity(HASH_TABLE* table);

/*哈希表容量算法*/
int GetCapacity(HASH_TABLE* table);

/*哈希表扩容*/
int RecreateHashTable(HASH_TABLE *table);

/*哈希函数*/
int HashFun(HASH_TABLE* table, DATA_TYPE data);

/*检测冲突，开放地址法->线性探测法*/
int Collision(HASH_TABLE *table, int *p);

/*删除哈希表*/
void DestoryHash(HASH_TABLE* table);

/*打印哈希表*/
void PrintHash(HASH_TABLE* table);

/*测试哈希函数*/
void test_hash();




#endif
