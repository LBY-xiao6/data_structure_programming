#include <stdio.h>

#define SEQSTACK_NODE char
#include "seqstack.h"

int main(void)
{
	stack *s = init_stack(10);

	push(s, 'a');
	push(s, 'b');
	push(s, 'c');
	push(s, 'd');
	push(s, 'e');
	
	// 应该输出edcba
	char c;
	while(!empty(s))
	{
		top(s, &c);
		printf("%c", c);

		pop(s);
	}
	printf("\n");

	return 0;
}
