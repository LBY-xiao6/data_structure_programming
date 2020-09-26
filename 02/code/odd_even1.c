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
//  描述: 双向链表演示
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

	struct node *prev;
	struct node *next;
};

struct node * init_list(void)
{
	// 申请一个头结点堆内存空间
	struct node * head = malloc(sizeof(struct node));

	if(head != NULL)
	{
		// 数据域不管
		// 指针域指向自身
		head->prev = head;
		head->next = head;
	}

	return head;
}

struct node * new_node(int data)
{
	// 申请一个新结点堆内存空间
	struct node * new = malloc(sizeof(struct node));

	if(new != NULL)
	{
		// 数据域不管
		new->data = data;

		// 指针域指向自身
		new->prev = new;
		new->next = new;
	}

	return new;
}

// 将新节点new，置入链表head的末尾
void list_add_tail(struct node * head, struct node *new)
{
	new->prev = head->prev;
	new->next = head;

	head->prev->next = new;
	head->prev = new;
}

bool empty(struct node * head)
{
	// 只有头结点，就代表链表为空
	return head->next == head;
}

void show(struct node *head)
{
	if(empty(head))
		return;

	struct node *p;
	p = head->next;

	while(p != head)
	{
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	// 1，初始化一条空的双向循环链表（容器）
	struct node * head = init_list();

	// 2，将一些自然数放入链表
	printf("请输入你要的节点个数:\n");
	int n;
	scanf("%d", &n);

	for(int i=1; i<=n; i++)
	{
		// a. 创建新的节点new
		struct node * new = new_node(i);

		// b. 将新节点new，置入链表的末尾
		list_add_tail(head, new);
	}
	show(head);

	return 0;
}
