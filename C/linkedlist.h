/* linkedlist.h */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node *link;
struct node {
	unsigned char item;
	link prev,next;
};

extern link make_node(unsigned char item);
extern void free_node(link p);
extern link search(unsigned char key);
extern void insert(link p);
extern void delete(link p);
extern void traverse(void (*visit)(link));
extern void destroy(void);
extern void push(link p);
extern link pop(void);
extern void reverse(void);
#endif