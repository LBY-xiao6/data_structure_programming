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



#ifndef LINKQUEUE_NODE2
#define LINKQUEUE_NODE2 int
#endif

typedef LINKQUEUE_NODE2 datatype2;


// 链式队列节点
struct node2
{
	datatype2 data;
	struct node2 *next;
};

// 链式队列的管理结构体
typedef struct
{
	struct node2 *front;
	struct node2 *rear;
	int size;
}linkqueue2;


// 链式队列的操作接口

// 1. 初始化
static linkqueue2 * init_queue2()
{
	linkqueue2 *q = malloc(sizeof(linkqueue2));

	if(q != NULL)
	{
		q->front = NULL;
		q->rear  = NULL;
		q->size  = 0;
	}

	return q;
}

// 4.判断队列是否为空
bool empty2(linkqueue2 *q)
{
	return q->size == 0;
}


// 2.入队
static void en_queue2(linkqueue2 *q, datatype2 data)
{
	// a.创建新节点
	struct node2 * new = malloc(sizeof(struct node2));
	if(new != NULL)
	{
		new->data = data; 
		new->next = NULL;
	}

	// b.将新节点入队（放入队尾）
	if(empty2(q))
		q->front = new;
	else
		q->rear->next = new;

	q->rear = new;
	q->size++;
}


// 3.出队: 返回队头元素指针
static struct node2 *out_queue2(linkqueue2 *q)
{
	// a.队列是空的
	if(empty2(q))
		return NULL;

	// b.队列只有一个元素
	if(q->size == 1)
	{
		q->rear = NULL;
	}

	// c.队列有两个以上元素
	struct node2 *p = q->front;
	q->front = q->front->next;
	q->size--;

	p->next = NULL;
	return p;
}



// 5.取队头元素（不出队）
struct node2 * front2(linkqueue2 *q)
{
	if(empty2(q))
		return NULL;

	return q->front;
}


// 6.获取当前队列元素总数
int size2(linkqueue2 *q)
{
	return q->size;
}


// 7.销毁队列（回归初始化状态）
void destroy2(linkqueue2 *q)
{
	if(empty2(q))
		return;

	// 逐个释放链队列中每一个节点内存
	struct node2 *p = q->front;
	while(p != NULL)
	{
		struct node2 *next = p->next;
		free(p);
		p = next;
	}

	// 让链队列管理结构体回归初始状态
	q->front = NULL;
	q->rear  = NULL;
	q->size  = 0;
}


// 8.遍历
void travel2(linkqueue2 *q, void (*handler)(datatype2 data))
{
	if(empty2(q))
		return;

	struct node2 *p = q->front;
	while(p != NULL)
	{
		// a.访问节点
		handler(p->data);

		// b.到下一个节点
		p = p->next;
	}
}

#endif
