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
//  描述: 使用内核链表来实现奇偶数重排
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

// 包含内核链表头文件
#include "kernel_list.h"


// 设计大结构体节点
struct node
{
	int data; // 数据域
	struct list_head list; // 小结构体
};

// 初始化一条包含头结点的空链表
// 注意，内核链表的实现都是有头结点的
struct node * init_list()
{
	struct node * head = malloc(sizeof(struct node));

	if(head != NULL)
	{
		// 数据域不管
		
		// 小结构体要自己形成循环链表
		// 1. 自己动手
		//head->list.prev = &head->list;
		//head->list.next = &head->list;

		// 2. 直接使用内核链表的实现
		INIT_LIST_HEAD(&head->list);
	}
	return head;
}

// 新建一个节点，并存入数据data
struct node * new_node(int data)
{
	struct node * new = malloc(sizeof(struct node));

	if(new != NULL)
	{
		// 数据域
		new->data = data;
		
		// 小结构体要自己形成循环链表
		INIT_LIST_HEAD(&new->list);
	}
	return new;
}

// 遍历链表，将节点数据显示出来
void show(struct node * head)
{
	struct node *pos;

	list_for_each_entry(pos, &head->list, list)
	{
		printf("%d\t", pos->data);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	// 1，初始化空链表
	struct node * head = init_list();

	// 2，将一些自然数置入链表中
	printf("请输入你要多少个节点:");
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
	{
		// a. 创建新节点new
		struct node *new = new_node(i);

		// b. 将新节点new置入链表的末尾
		// &new->list  是指向new 节点中的小结构体的指针
		// &head->list 是指向head节点中的小结构体的指针
		list_add_tail(&new->list, &head->list);
	}
	show(head);

	// 奇偶数重排
	
	/* ADD YOUR CODE HERE */

	return 0;
}
