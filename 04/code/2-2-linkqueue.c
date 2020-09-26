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
//  描述:
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

// 直接使用队列默认的元素类型int
#include "linkqueue.h"

void show(int data)
{
	printf("%d\t", data);
}

int main(int argc, char **argv)
{
	// 1.初始化一个空队列
	linkqueue *q = init_queue();

	// 2.不断输入数据
	int n;
	while(1)
	{
		// 用户输入了数字！入队！
		if(scanf("%d", &n) == 1)
		{
			en_queue(q, n);
		}

		// 用户输入了非数字！清空scanf的缓冲区并出队
		else
		{
			// a.清空缓冲区中所有的非数字字符
			while(getchar()!='\n');

			// b.出队
			struct node *tmp = out_queue(q);
			if(!tmp)
				printf("出队失败\n");
			else
				printf("出队:%d\n", tmp->data);
		}

		// 不管是入队出队，操作之后都显示当前队列元素
		printf("当前队列元素:\n");
		travel(q, show);
		printf("\n");
	}


	return 0;
}
