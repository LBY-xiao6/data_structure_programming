////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)
//
//  微信公众号: 秘籍酷
//  技术交流群: 260492823（QQ群）
//  GitHub链接: https://github.com/vincent040
//
//  描述: 单向循环链表演示
//
////////////////////////////////////////////////

#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>

// 设计节点
struct node
{
	int data;
	struct node * next;
};

struct node * init_list()
{
	return NULL;
}

// 创建新节点
// 成功时，返回新节点的地址
// 失败时，返回NULL
struct node * new_node(int data)
{
	struct node *new = malloc(sizeof(struct node));

	if(new != NULL)
	{
		// 初始化这个新节点
		new->data = data; // 数据域
		new->next = new;  // 指针域
	}

	return new;
}

// 判断单向循环链表（无头节点）是否为空
// 是就返回true
// 否就返回false
bool empty(struct node * head)
{
	return head == NULL;
}

// 将新节点new，插入到链表的末尾，称为新的尾节点
void add_list_tail(struct node * (*phead), struct node *new)
{
	// 边界情况
	if(empty(*phead))
	{
		*phead = new;
		return;
	}


	// 定义一个尾指针
	struct node * tail;

	// 让tail从头开始往后遍历，直到找到末尾节点为止
	tail = *phead;
	while(tail->next != *phead)
	{
		tail = tail->next;
	}

	// 让原链表的末尾节点，指向新的尾节点
	tail->next = new;

	// 将新的尾节点，指向首节点
	new->next = *phead;
}

// 输出整条链表的节点
void show(struct node * head)
{
	if(empty(head))
	{
		printf("链表是空的\n");
		return;
	}

	struct node * p = head;
	do{
		printf("%d\t", p->data);
		p = p->next;
	}while(p != head);
	printf("\n");
}

// 将节点p从单向循环链表中剔除，并释放
// 返回p的下一个节点
struct node * del(struct node *p)
{
	// 1，找到你要删除的节点的前面的节点
	struct node * pre;
	pre = p;
	while(pre->next != p)
		pre = pre->next;

	// 2，让链表跳过要p，不带他玩
	pre->next = p->next;
	
	// 3，释放节点p
	free(p);

	return pre->next;
}

// 数3出局
// 将单循环链表中的节点依次数3出局
// 最后剩下最多不超过2个节点
struct node * count3(struct node * head)
{
	if(empty(head))
		return head;

	while(head != head->next->next)
	{
		head = del(head->next->next);
	}

	return head;
}

int main(int argc, char **argv)
{
	// 1，初始化一个空的循环链表
	struct node * head = init_list();


	// 2，将一些自然数插入循环链表的尾部
	printf("请输入你要的节点数量:\n");
	int n;
	scanf("%d", &n);

	for(int i=1; i<=n; i++)
	{
		// a. 创建一个新节点new
		struct node * new = new_node(i);

		if(new == NULL)
		{
			perror("节点内存申请失败");
			exit(0);
		}

		// b. 将新节点插入到链表的尾部
		// 由于必须修改实参head，因此要传递&head
		add_list_tail(&head, new);
	}
	show(head);

	// 3，数三出局
	head = count3(head);

	// 4，输出幸存者
	printf("幸存者:");
	show(head);

#ifdef A	
	// 5，销毁链表
	destroy(head);
#endif

	return 0;
}
