/* doublylinkedlist.c */
#include <stdlib.h>
#include "doublylinkedlist.h"

struct node tailsentinel;
struct node headsentinel = {0, NULL, &tailsentinel};
struct node tailsentinel = {0, &headsentinel, NULL};

link head = &headsentinel;  // 移除static，使其可以被外部访问
link tail = &tailsentinel;  // 移除static，使其可以被外部访问

link make_node(unsigned char item)
{
	link p = malloc(sizeof *p);
	p->item = item;
	p->prev = p->next = NULL;
	return p;
}

void free_node(link p)
{
	free(p);
}

link search(unsigned char key)
{
	link p;
	for (p = head->next; p != tail; p = p->next)
		if (p->item == key)
			return p;
	return NULL;
}

void insert(link p)
{
	p->next = head->next;
	head->next->prev = p;
	head->next = p;
	p->prev = head;
}

void delete(link p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
}

void traverse(void (*visit)(link))
{
	link p;
	for (p = head->next; p != tail; p = p->next)
		visit(p);
}

void destroy(void)
{
	link q, p = head->next;
	head->next = tail;
	tail->prev = head;
	while (p != tail) {
		q = p;
		p = p->next;
		free_node(q);
	}
}

void enqueue(link p)
{
	insert(p);
}

link dequeue(void)
{
	if (tail->prev == head)
		return NULL;
	else {
		link p = tail->prev;
		delete(p);
		return p;
	}
}