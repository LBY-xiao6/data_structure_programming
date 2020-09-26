#include <stdio.h>

#include "seqstack.h"

int main(void)
{
	stack *s = init_stack(10);

	push(s, 1);
	push(s, 2);
	push(s, 3);
	push(s, 4);
	push(s, 5);
	
	// 应该输出54321
	int c;
	while(!empty(s))
	{
		top(s, &c);
		printf("%d", c);

		pop(s);
	}
	printf("\n");

	return 0;
}
