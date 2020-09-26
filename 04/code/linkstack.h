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
//  描述: 链式栈
//
////////////////////////////////////////////////

#ifndef LINKSTACK_H
#define LINKSTACK_H

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

// 链式栈存储的元素类型，默认是int
#ifndef LINKSTACK_NODE
#define LINKSTACK_NODE int
#endif

typedef LINKSTACK_NODE datatype;

// 链式栈数据节点的类型
struct node
{
	datatype data;
	struct node *next;
};

// 链式栈的管理结构体
typedef struct
{
	// 指向链式栈的顶部元素
	// 链栈为空时，top指向NULL
	struct node *top;

	// 链式栈的元素总数
	int size; 
}linkstack;


// 初始化空栈
static linkstack * init_stack()
{
	linkstack * s = malloc(sizeof(linkstack));
	if(s != NULL)
	{
		s->top  = NULL;
		s->size = 0;
	}
	return s;
}

// 判断栈是否为空
static bool empty(linkstack *s)
{
	return s->size == 0;
}

// 入栈
static bool push(linkstack *s, datatype data)
{
	struct node *new = malloc(sizeof(struct node));
	if(new != NULL)
	{
		new->data = data;
		new->next = NULL;
	}
	else
		return false;

	new->next = s->top;
	s->top = new;

	s->size++;
	return true;
}

// 出栈（即删除栈顶元素），并释放节点
static void pop(linkstack *s)
{
	if(empty(s))
		return;

	struct node *p = s->top;
	s->top = s->top->next;
	s->size--;

	p->next = NULL;
	free(p);
}

// 取栈顶元素（不出栈）
static struct node *top(linkstack *s)
{
	if(empty(s))
		return NULL;

	return s->top;
}



#endif
