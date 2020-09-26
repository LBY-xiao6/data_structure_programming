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
//  描述: 快速排序算法示例
//
////////////////////////////////////////////////
#include <time.h>
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

int comp_count = 0;
int swap_count = 0;

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

int partition(int data[], int len)
{
	if(len <= 1)
		return 0;

	int i = 0;
	int j = len-1;
	while(i < j)
	{
		// 从右向左比较，顺序j--，逆序交换
		comp_count++;
		while(data[i]<=data[j] && i<j)
			j--;
		swap(&data[i], &data[j]);

		// 从左向右比较，顺序i++，逆序交换
		comp_count++;
		while(data[i]<=data[j] && i<j)
			i++;
		swap(&data[i], &data[j]);
	}

	return i;
}

void quick_sort(int data[], int len)
{
	if(len <= 1)
		return;

	int pivot = partition(data, len);

	quick_sort(data, pivot);
	quick_sort(data+pivot+1, len-pivot-1);
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	int i, data[100];
	for(i=0; i<100; ++i)
	{
		data[i] = rand() % 1000;
	}
	printf("随机序列: ");
	show(data, 100);

	printf("快速排序: ");
	quick_sort(data, 100);
	show(data, 100);

	printf("总共比较次数: %d\n", comp_count);
	printf("总共交换次数: %d\n", swap_count);

	return 0;
}
