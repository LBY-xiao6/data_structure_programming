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
//  描述: 实现二叉搜索树BST的按层遍历算法
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

#include "drawtree.h"
#include "head4tree.h"


// 使用之前编写的通用型队列算法
// 并使之存储linktree数据（而不是默认的int）
#define LINKQUEUE_NODE2 linktree
#include "linkqueue.h"


// 一般而言，树不需要头结点
linktree init_bst()
{
	return NULL;
}

bool empty(linktree root)
{
	return root==NULL;
}

// 功能:
// 将数据data，插入以root为根的二叉树中
// 将插入了新数据的新的二叉树的根，返回
linktree bst_insert(linktree root, linktree new)
{
	if(empty(root))
		return new;

	if(new->data < root->data)
		root->lchild = bst_insert(root->lchild, new);
	else if(new->data > root->data)
		root->rchild = bst_insert(root->rchild, new);
	else
		printf("%ld已经存在，不能重复！\n", new->data);

	return root;
}

// 功能:
// 在以root为根的BST中，试图找到data
// 如果找到了，就将它删除
// 如果找不到，就算了
// 返回值: 删除之后的新的二叉树的根
linktree bst_remove(linktree root, int data)
{
	if(empty(root))
		return NULL;

	if(data < root->data)
		root->lchild = bst_remove(root->lchild, data);
	else if(data > root->data)
		root->rchild = bst_remove(root->rchild, data);
	else
	{
		// a.有左子树
		if(root->lchild != NULL)
		{
			// 找到左max，替换，删除左max
			linktree leftmax;
			for(leftmax=root->lchild;
			    leftmax->rchild!=NULL;
			    leftmax=leftmax->rchild);
				
			root->data = leftmax->data;

			root->lchild = bst_remove(root->lchild, leftmax->data);
		}

		// b.无左子树，但有右子树
		else if(root->rchild != NULL)
		{
			// 找到右min，替换，删除右min
			linktree rightmin;
			for(rightmin=root->rchild;
			    rightmin->lchild!=NULL;
			    rightmin=rightmin->lchild);
				
			root->data = rightmin->data;

			root->rchild = bst_remove(root->rchild, rightmin->data);
		}

		// c.没有子树，本身是叶子
		else
		{
			free(root);
			return NULL;
		}
	}

	return root;
}

int main(int argc, char **argv)
{
	// 1.搞一个空BST
	linktree root = init_bst();

	// 2.增加一些节点
	int n;
	while(1)
	{
		scanf("%d", &n);

		if(n == 0)
			break;

		// 插入节点
		if(n > 0)
		{
			linktree new = new_node(n);
			root = bst_insert(root, new);
		}

		// 删除节点
		if(n < 0)
			root = bst_remove(root, -n);

		// 展示一棵树
		draw(root);
	}

	// 3，按层遍历一下
	linkqueue2 *q = init_queue2();

	en_queue2(q, root);

	while(!empty2(q))
	{
		struct node2 * p = out_queue2(q);
		printf("%ld\t", p->data->data);

		if(p->data->lchild != NULL)
			en_queue2(q, p->data->lchild);
		if(p->data->rchild != NULL)
			en_queue2(q, p->data->rchild);
	}
	printf("\n");

	return 0;
}
