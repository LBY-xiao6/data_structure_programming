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
//  描述: 选择排序算法示例
//
////////////////////////////////////////////////
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <strings.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int comp_count = 0; // 数据比较次数
int swap_count = 0; // 数据交换次数

void show(int data[], int len)
{
	int i;
	for(i=0; i<len; ++i)
	{
		printf("%d\t", data[i]);
	}
	printf("\n");
}

void swap(int *a, int *b)
{
	swap_count++;

	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void selection_sort(int data[], int len)
{
	for(int i=0; i<len; i++)
	{
		int min=i;

		for(int j=i+1; j<len; j++)
		{
			comp_count++;
			if(data[j] < data[min])
				min = j;
		}

		swap(&data[i], &data[min]);
	}
}

int main(int argc, char **argv)
{
	// generate some random data
	srand(time(NULL));

	int i, data[100];
	for(i=0; i<100; ++i)
	{
		int exp = (int)pow(10, rand()%3+3);
		data[i] = rand() % exp;
	}
	printf("随机序列: ");
	show(data, 100);

	selection_sort(data, 100);
	printf("选择排序: ");
	show(data, 100);

	printf("总共比较次数: %d\n", comp_count);
	printf("总共交换次数: %d\n", swap_count);
	return 0;
}
