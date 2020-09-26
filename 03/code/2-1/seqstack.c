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
//  描述: 顺序栈的实现
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

#include "seqstack.h"

// 栈的初始化
// 成功时，返回栈的管理结构体指针
// 失败时，返回NULL
stack * init_stack(int size)
{
	// 申请栈的管理结构体
	stack * s = malloc(sizeof(stack));
	if(s != NULL)
	{
		s->size = size;
		s->top  = -1;
		
		s->data = calloc(size, sizeof(datatype));
		if(s->data == NULL)
		{
			free(s);
			return NULL;
		}
	}

	return s;
}

// 入栈: 将数据data，置入栈s的栈顶中
bool push(stack *s, datatype data)
{
	// 栈已满，无法置入
	if(full(s))
		return false;

	s->data[++s->top] = data;
	return true;
}

// 出栈: 将栈顶元素删除
bool pop(stack *s)
{
	if(empty(s))
		return false;

	s->top--;
	return true;
}

// 取栈顶元素
bool top(stack *s, datatype *pdata)
{
	if(empty(s))
		return false;

	*pdata = s->data[s->top];
	return true;
}

// 判断栈是否已满、是否为空
bool empty(stack *s)
{
	return s->top == -1;
}

bool full(stack *s)
{
	return s->top == s->size-1;
}
