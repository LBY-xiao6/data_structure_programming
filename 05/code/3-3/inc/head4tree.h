///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: lab/tree/headers/head4tree.h
//  日期: 2017-9
//  描述: 本文件为二叉树核心头文件。
//        任何使用本二叉树结构算法的程序，在包含本头文件之前
//        都需要将如下宏定义成二叉树节点需要表达的数据类型：
//
//              TREE_NODE_DATATYPE
//
//        否则二叉树的节点数据类型一律默认为 int
//
//  作者: Vincent Lin (林世霖)   微信公众号：秘籍酷
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef _HEAD4TREE_H_
#define _HEAD4TREE_H_

/*
 * Any application applying this linked-tree data structure should
 * define the macro "TREE_NODE_DATATYPE" before include this head
 * file, otherwise, the macro will be defined to 'int' as follow.
 *
*/

#ifndef TREE_NODE_DATATYPE
#define TREE_NODE_DATATYPE long
#endif

#include "common.h"

#define MAX(a, b) ({ \
		typeof(a) _a = a; \
		typeof(b) _b = b; \
		(void)(&_a == &_b);\
		_a > _b? _a : _b; \
		})

typedef TREE_NODE_DATATYPE tn_datatype;

typedef struct _tree_node
{
	tn_datatype data;
	struct _tree_node *lchild;
	struct _tree_node *rchild;

}treenode, *linktree;

void pre_travel(linktree, void (*handler)(linktree));
void mid_travel(linktree, void (*handler)(linktree));
void post_travel(linktree, void (*handler)(linktree));
void level_travel(linktree, void (*handler)(linktree));

linktree bst_find(linktree root, tn_datatype data);

static linktree new_node(tn_datatype data)
{
	linktree new = malloc(sizeof(treenode));
	if(new != NULL)
	{
		new->data = data;
		new->lchild = NULL;
		new->rchild = NULL;
	}
	return new;
}

#endif