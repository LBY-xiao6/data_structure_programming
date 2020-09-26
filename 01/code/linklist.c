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
//  描述: 单链表的演示 
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

// 1，设计节点
struct node
{
	int data;         // 数据域
	struct node *next;// 指针域
};

// 分配一个头结点，并做好初始化
// 最后返回头结点的地址
struct node * init_list()
{
	// 为头结点申请堆内存
	struct node *head = malloc(sizeof(struct node));

	// 申请成功的情况下，对头结点进行初始化
	if(head != NULL)
	{
		// 数据域不管
		// 指针域置空
		head->next = NULL;
	}
	return head;
}

// 创建一个新节点来存放数据data
struct node * new_node(int data)
{
	// 试图申请一块节点内存
	struct node *new = malloc(sizeof(struct node));

	// 如果申请成功，那么就妥善地初始化数据域和指针域
	if(new != NULL)
	{
		new->data = data; // 数据域
		new->next = NULL; // 指针域
	}

	return new;
}

// 将新节点new，插入到以head为首的链表的末尾
void add_list_tail(struct node *head, struct node *new)
{
	// 1. 找到tail
	struct node *tail = head;
	while(tail->next != NULL)
	{
		tail = tail->next;
	}

	// 2. 将新节点接入链表的尾部
	tail->next = new;
}

// 将以head为首的链表的每个节点展现出来
void show(struct node * head)
{
	// 判断链表头指针的合法性
	if(head == NULL)
	{
		printf("链表尚未初始化，或已销毁\n");
		return;
	}

	// p指向第一个有效数据（跳过头结点）
	struct node *p = head->next;

	if(p == NULL)
	{
		printf("链表无数据\n");
		return;
	}

	// 只要p不为空，就打印出来
	while(p != NULL)
	{
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
}

// 将链表翻转
void revert(struct node * head)
{
	// 将原链表，切开成两边
	struct node * p = head->next;
	head->next = NULL;

	// 将p为首的链表，逐个移动到head的后面
	while(p != NULL)
	{
		// 1
		struct node * tmp = p->next;
		
		// 2 
		p->next = head->next;	

		// 3
		head->next = p;

		p = tmp;
	}
}

// 从头开始，销毁（释放）每个节点
struct node * destroy(struct node * head)
{
	struct node * p = head;
	struct node * tmp;

	while(p != NULL)
	{
		tmp = p->next;
		free(p);

		p = tmp;
	}

	return NULL;
}

int main(int argc, char **argv)
{
	// 2，初始化一个空链表
	struct node *head;
	head = init_list();
	if(head == NULL)
	{
		perror("分配内存失败");
		exit(0);
	}

	// 3，将一些自然数依次插入链表
	int n;
	printf("请输入你要插入的节点个数:");
	scanf("%d", &n);

	for(int i=1; i<=n; i++)
	{
		// a. 创建新节点
		struct node * new = new_node(i);

		// b. 将新节点new，插入链表head的末尾
		add_list_tail(head, new);
	}
	// 展示一下当前的链表
	show(head);


	// 4，翻转这些节点，并输出
	revert(head);
	show(head);


	// 5，销毁链表
	head = destroy(head);
	show(head);

	return 0;
}
