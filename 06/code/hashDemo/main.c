#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 设计节点
struct node
{
    char data[20];
    struct node * next;
};

// 设计哈希表的管理结构体
typedef struct
{
    int capacity; // 总容量
    int size;     // 当前节点数量

    struct node **hash; // 哈希表
}hash_table;

hash_table * init_hashtable(int cap)
{
    // 分配管理结构体
    hash_table * ht = calloc(1, sizeof(hash_table));
    if(ht != NULL)
    {
        ht->capacity = cap;
        ht->size     = 0;

        ht->hash = calloc(cap, sizeof(struct node *));
        if(ht->hash == NULL)
        {
            free(ht);
            return NULL;
        }
    }

    return ht;
}

int hash(const char *data)
{
    int sum = 0;
    for(int i=0; i<strlen(data); i++)
        sum += data[i];

    // 除留余数法获取节点对应的哈希地址
    return sum%19;
}

void show(hash_table *ht)
{
    for(int i=0; i<ht->capacity; i++)
    {
        printf("ht[%d]: ", i);

        struct node *p = ht->hash[i];
        while(p != NULL)
        {
            printf("--> \"%s\" ", p->data);
            p = p->next;
        }

        printf("\n");
    }
}

int search(hash_table *ht, const char *data)
{
    // 查找data所在的位置
    int pos = hash(data);
    if(ht->hash[pos] == NULL)
        return -1;

    struct node *p;
    for(p=ht->hash[pos]; p!=NULL; p=p->next)
    {
        if(strcmp(data, p->data) == 0)
            return pos;
    }
    return -1;
}

int main()
{
    // 创建空的哈希表
    hash_table *ht = init_hashtable(20);

    // 存入数据（造表）
    while(1)
    {
        // 输入一个节点
        struct node *newnode = calloc(1, sizeof(struct node));
        if(newnode != NULL)
        {
            // 按 ctrl+d 结束输入
            if(gets(newnode->data) == NULL)
                break;
        }

        // 获取节点的哈希地址（哈希表的位置）
        int pos = hash(newnode->data);

        // 解决冲突
        // 1，如果没有冲突，那么直接置入节点
        if(ht->hash[pos] == NULL)
            ht->hash[pos] = newnode;
        // 2，如果有冲突，那么将节点置入冲突链表的末尾
        else
        {
            struct node *tail;
            for(tail=ht->hash[pos];
                tail->next!=NULL;
                tail = tail->next);
            tail->next = newnode;
        }

        // 显示当前哈希表的状态
        show(ht);
    }

    // 查表
    while(1)
    {
        printf("请输入你要查的字符串:\n");

        char str[20];
        gets(str);

        int pos = search(ht, str);
        if(pos == -1)
            printf("查无此人\n");
        else
            printf("你要的数据在: ht[%d]\n", pos);
    }

    return 0;
}
