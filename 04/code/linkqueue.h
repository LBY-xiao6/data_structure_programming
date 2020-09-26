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
//  描述: 通用型的链式队列
//
////////////////////////////////////////////////

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

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



#ifndef LINKQUEUE_NODE
#define LINKQUEUE_NODE int
#endif

typedef LINKQUEUE_NODE datatype;


// 链式队列节点
struct node
{
	datatype data;
	struct node *next;
};

// 链式队列的管理结构体
typedef struct
{
	struct node *front;
	struct node *rear;
	int size;
}linkqueue;


// 链式队列的操作接口

// 1. 初始化
static linkqueue * init_queue()
{
	linkqueue *q = malloc(sizeof(linkqueue));

	if(q != NULL)
	{
		q->front = NULL;
		q->rear  = NULL;
		q->size  = 0;
	}

	return q;
}

// 4.判断队列是否为空
bool empty(linkqueue *q)
{
	return q->size == 0;
}


// 2.入队
static void en_queue(linkqueue *q, datatype data)
{
	// a.创建新节点
	struct node * new = malloc(sizeof(struct node));
	if(new != NULL)
	{
		new->data = data; 
		new->next = NULL;
	}

	// b.将新节点入队（放入队尾）
	if(empty(q))
		q->front = new;
	else
		q->rear->next = new;

	q->rear = new;
	q->size++;
}


// 3.出队: 返回队头元素指针
static struct node *out_queue(linkqueue *q)
{
	// a.队列是空的
	if(empty(q))
		return NULL;

	// b.队列只有一个元素
	if(q->size == 1)
	{
		q->rear = NULL;
	}

	// c.队列有两个以上元素
	struct node *p = q->front;
	q->front = q->front->next;
	q->size--;

	p->next = NULL;
	return p;
}



// 5.取队头元素（不出队）
struct node * front(linkqueue *q)
{
	if(empty(q))
		return NULL;

	return q->front;
}


// 6.获取当前队列元素总数
int size(linkqueue *q)
{
	return q->size;
}


// 7.销毁队列（回归初始化状态）
void destroy(linkqueue *q)
{
	if(empty(q))
		return;

	// 逐个释放链队列中每一个节点内存
	struct node *p = q->front;
	while(p != NULL)
	{
		struct node *next = p->next;
		free(p);
		p = next;
	}

	// 让链队列管理结构体回归初始状态
	q->front = NULL;
	q->rear  = NULL;
	q->size  = 0;
}


// 8.遍历
void travel(linkqueue *q, void (*handler)(datatype data))
{
	if(empty(q))
		return;

	struct node *p = q->front;
	while(p != NULL)
	{
		// a.访问节点
		handler(p->data);

		// b.到下一个节点
		p = p->next;
	}
}

#endif
