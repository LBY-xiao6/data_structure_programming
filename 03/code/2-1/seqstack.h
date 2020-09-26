#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// 该程序模块提供栈的功能
// 默认处理的是int数据
// 用户如需处理其他自定义数据，请定义如下宏，如:
// #define SEQSTACK_NODE xxx

// 如果用户没有自定义顺序栈元素类型
// 那么类型默认为int
#ifndef SEQSTACK_NODE 
#define SEQSTACK_NODE int
#endif

typedef SEQSTACK_NODE datatype;

// 顺序栈的管理结构体
typedef struct seqstack
{
	int size;
	int top;

	datatype *data;
}stack;

// 以下是栈的操作接口

// 初始化
// size: 初始状态下，空栈的容量
stack * init_stack(int size);

// 入栈
// 成功返回真，失败（当栈已满的时候）返回假
bool push(stack *s, datatype data);

// 出栈: 将栈顶元素删除
// 成功返回真，失败（当栈为空的时候）返回假
bool pop(stack *s);

// 读取栈顶: 将栈顶元素返回
bool top(stack *s, datatype *pdata);

// 判断满
bool full(stack *s);

// 判断空
bool empty(stack *s);

#endif
