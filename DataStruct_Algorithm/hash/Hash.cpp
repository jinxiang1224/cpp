#include "Hash.h"
#include <stdio.h>
#include <memory>

int InitHash(HASH_TABLE* table, int capacity)
{
    if(NULL == table)
    {
        return DA_ERROR;
    }
    table->size = 0;
    table->capacity = capacity;
    table->capacity = GetCapacity(table);

    table->hashNode = (STRU_HASH_NODE*)malloc(sizeof(STRU_HASH_NODE) * table->capacity);

    for (int i = 0; i < table->capacity; i++)
    {
        table->hashNode[i].status = EN_STATUS_EMPTY;
    }

    return DA_SUCCESS;
}

/*重新扩容时，哈希表大小*/
int GetCapacity(HASH_TABLE* table)
{
    //哈希表容量递增表，一个合适的素数序列，减少冲突的可能
    const int nPrimeSize = 13;
    const int HashSize[] = 
    {
        7,13,17,101,
        211,307,401,503,
        601,701,809,907,
        997
    };

    for (int i = 0; i < nPrimeSize; i++)
    {
        if (table->capacity < HashSize[i])
        {
            return HashSize[i];
        }
    }

    return HashSize[nPrimeSize - 1];
}

bool CheckCapacity(HASH_TABLE* table)
{
    //检查负载因子大小
    int check_capacity = (table->size * 10) / table->capacity;
    if (check_capacity >= 7)
    {
        return true;
    }

    return false;
}

/*哈希表扩容*/
int RecreateHashTable(HASH_TABLE *table)
{
    HASH_TABLE NewTable;

    //创建新的哈希表
    InitHash(&NewTable,table->capacity);

    for (int i = 0; i < table->capacity; i++)
    {
        if (EN_STATUS_EXIST == table->hashNode[i].status)
        {
            InsertHash(&NewTable,table->hashNode[i].key);
        }
    }

   if (table->hashNode != NULL)
   {
       free(table->hashNode);
       table->hashNode = NULL;
   }

   table->capacity = NewTable.capacity;
   table->size = NewTable.size;
   table->hashNode = NewTable.hashNode;

   return DA_SUCCESS;
}

/*除留余数法*/
int HashFun(HASH_TABLE* table, DATA_TYPE data)
{
    return data % table->capacity;
}

/*冲突时，线性探测返回新的地址*/
int Collision(HASH_TABLE *table, int hash_addr)
{
    return (hash_addr + 1) % (table->capacity);
}

/*哈希表插入关键字*/
/*
step1:给出对应的哈希地址
step2:判断当前哈希地址是否有冲突
step3:有冲突则采用冲突策略，否则将该元素放在该位置
*/
int InsertHash(HASH_TABLE *table, DATA_TYPE data)
{
    if (CheckCapacity(table))
    {
        printf("hash table need to recreate\n");
        RecreateHashTable(table);
    }

    int hash_addr = HashFun(table, data);

    int index = hash_addr;
    
    //冲突检测以及冲突解决方法:线性探测法
    while (table->hashNode[index].status == EN_STATUS_EXIST)
    {
        if (table->hashNode[index].key == data)
        {
            return DA_ALREADY_EXIST;
        }

        index = Collision(table,index);
    }

    printf("key = %d hash addr=%d target= %d\n",data, hash_addr,index);

    table->hashNode[index].key = data;
    table->hashNode[index].status = EN_STATUS_EXIST;
    table->size += 1;

    return DA_SUCCESS;
}

/*哈希表关键字搜索*/
bool SearchHash(HASH_TABLE* table, DATA_TYPE data)
{
    int hash_addr = HashFun(table, data);

    int index = hash_addr;
    //线性探测法，查找
    while (table->hashNode[index].status == EN_STATUS_EXIST)
    {
        //相等则存在
        if (table->hashNode[index].key == data)
        {
            return true;
        }

        //线性探测下一个元素
        index = Collision(table,index);
    }
    
    return false;
}

/*删除哈希关键字*/
/*
采用线性探测法处理散列时的冲突,
当从哈希表删除一个记录时,不应将这个记录的所在位置置空,
否则影响其他记录的查找
*/
bool RemoveHash(HASH_TABLE* table, DATA_TYPE data)
{
    int hash_addr = HashFun(table, data);

    int index = hash_addr;
    //线性探测法，查找
    while (table->hashNode[index].status == EN_STATUS_EXIST)
    {
        //相等则存在
        if (table->hashNode[index].key == data)
        {
            table->hashNode[index].status = EN_STATUS_DELETE;
            table->size--;
            return true;
        }
        //线性探测下一个元素
        index = Collision(table,index);
    }

    return false;
}

void DestoryHash(HASH_TABLE* table)
{
    table->capacity = 0;
    table->size = 0;
    free(table->hashNode);
    table->hashNode = NULL;
}

void PrintHash(HASH_TABLE* table)
{
   printf("哈希表容量为%d, 元素个数为%d\n",table->capacity,table->size);

   for (int i = 0; i < table->capacity; i++)
   {
       if (table->hashNode[i].status == EN_STATUS_EXIST)
       {
           printf("key=%d\t",table->hashNode[i].key);
       }
   }

   printf("\n");

   for (int i = 0; i < table->capacity; i++)
   {
       if (table->hashNode[i].status == EN_STATUS_DELETE)
       {
           printf("delete key=%d\t",table->hashNode[i].key);
       }
   }

   printf("\n");
}

void test_hash()
{
    HASH_TABLE  ht;
    InitHash(&ht, 0);//哈希表初始化

    printf("begin insert data....\n");

    InsertHash(&ht, 37);//插入数据
    InsertHash(&ht, 25);//插入数据
    InsertHash(&ht, 11);//插入数据
    InsertHash(&ht, 36);//插入数据
    InsertHash(&ht, 41);//插入数据
    InsertHash(&ht, 42);//插入数据

    PrintHash(&ht);//打印哈希表;

    printf("begin search data....\n");

    if (SearchHash(&ht,11))
    {
        printf("find  data success...\n");
    }
    else
    {
        printf("find data fail...\n");
    }

    printf("begin remove data....\n");

    RemoveHash(&ht, 11);//插入数据

    PrintHash(&ht);//打印哈希表;

    DestoryHash(&ht);
}
