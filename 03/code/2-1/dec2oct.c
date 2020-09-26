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
//  描述: 十进制转八进制
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

/*
// 自定义我要用这个栈来放什么东西
#define SEQSTACK_NODE xxx
*/

#include "seqstack.h"

int main(int argc, char **argv)
{
	// 初始化一个空栈
	stack *s  = init_stack(20);

	// 将短除法中的余数，逐个入栈
	int n;
	scanf("%d", &n);

	while(n > 0)
	{
		push(s, n%8); // 将余数入栈
		n /= 8;
	}

	// 将栈中的元素，逐个出栈，得到结果
	int a;
	printf("0");
	while(top(s, &a))
	{
		printf("%d", a);
		pop(s);
	}
	printf("\n");

	return 0;
}
