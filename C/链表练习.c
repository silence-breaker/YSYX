/* main.c */
#include <stdio.h>
#include "linkedlist.h"

void print_item(link p)
{
	printf("%d\n", p->item); 
}

int main(void)
{
	link p = make_node(10);
	insert(p);
	p = make_node(5);
	insert(p);
	p = make_node(90);
	insert(p);
	p = make_node(100);
	push(p);
	p = make_node(200);
	push(p);
	p = make_node(250);
	push(p);
    traverse(print_item);
    reverse();
    traverse(print_item);
	while (p = pop()) {
		
		free_node(p);
	}
    

	return 0;
}
