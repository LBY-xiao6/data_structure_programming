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
//  描述: 希尔排序算法示例
//
////////////////////////////////////////////////
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

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
	return;
}

//                    起点    节点个数    间距
void insert_sort(int data[], int len, int dlta)
{
	if(len <= 1)
		return;

	for(int i=dlta; i<len*dlta; i+=dlta)
	{
		int j, tmp = data[i];
		for(j=i-dlta; j>=0; j-=dlta)
		{
			comp_count++;
			if(data[j] < tmp)
				break;

			swap_count++;
			data[j+dlta] = data[j];
		}

		data[j+dlta] = tmp;
	}
}

void shell_sort(int data[], int len)
{
	if(len <= 1)
		return;

	for(int dlta=len/2; dlta>0; dlta/=2)
	{
		for(int i=0; i<dlta; ++i)
		{
			//           起点   节点个数  间距
			insert_sort(data+i, len/dlta, dlta);
		}
	}
}

int main(void)
{
	// generate som random data
	srand(time(NULL));

	int i, data[100];
	for(i=0; i<100; i++)
	{
		int exp = (int)pow(10, rand()%3+3);
		data[i] = rand()%exp;
	}
	printf("随机序列: ");
	show(data, 100);

	printf("希尔排序: ");
	shell_sort(data, 100);
	show(data, 100);

	printf("总共比较次数: %d\n", comp_count);
	printf("总共移动次数: %d\n", swap_count);

	return 0;
}
