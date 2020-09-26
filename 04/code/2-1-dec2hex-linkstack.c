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
//  描述: 十进制转十六进制
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

// 直接包含栈的实现头文件
// 并修改默认存储的元素类型为char
#define LINKSTACK_NODE char
#include "linkstack.h"

int main(int argc, char **argv)
{
	// 初始化一个空栈
	linkstack *s  = init_stack();

	// 将短除法中的余数，逐个入栈
	int n;
	scanf("%d", &n);

	while(n > 0)
	{
		int tmp = n%16;
		switch(tmp)
		{
		case 0 ... 9:
			push(s, tmp+'0');
			break;
		case 10 ... 15:
			push(s, tmp+'A'-10);
			break;
		}

		n /= 16;
	}

	// 将栈中的元素，逐个出栈，得到结果
	char a;
	printf("0x");
	while(!empty(s))
	{
		// 取栈顶
		struct node *tmp = top(s);
		printf("%c", tmp->data);

		// 删除栈顶
		pop(s);
	}
	printf("\n");

	return 0;
}
