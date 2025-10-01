#include <stdio.h>
#include "doublylinkedlist.h"

void print_item(link p)
{
	printf("%d\n", p->item); 
}
/*
int main(void)
{
	link p = make_node(10);
	insert(p);
	p = make_node(5);
	insert(p);
	p = make_node(90);
	insert(p);
	p = search(5);
	delete(p);
	free_node(p);
	traverse(print_item);
	destroy();

	p = make_node(100);
	enqueue(p);
	p = make_node(200);
	enqueue(p);
	p = make_node(250);
	enqueue(p);
	while (p = dequeue()) {
		print_item(p);
		free_node(p);
	}

	return 0;
}
*/

// Josephus问题
int main(void)
{
	int i = 0;
	int j = 0;
	int N = 0;
	int M = 0;
	link p, q;

	printf("请输入总人数N和报数上限M：");
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		link p = make_node(i);
		enqueue(p);
	}// N N-1 N-2 ... 3 2 1

	// 外层循环：每一圈杀人
	while (1) {
		// 计算当前剩余人数
		int count = 0;
		for (q = head->next; q != tail; q = q->next) {
			count++;
		}
		
		// 如果剩余人数 <= M-1，结束
		if (count <= M - 1) {
			break;
		}
		
		// 这一圈杀人
		i = 0;
		for (p = head->next; p != tail;) {  // 注意：这里移除了 p = p->next
			if (++i == M) {
				q = p->next;  // 保存下一个节点
				delete(p);
				free_node(p);  // 释放内存
				p = q;  // 移动到下一个节点
				i = 0;
			} else {
				p = p->next;  // 只有在不删除时才移动
			}
		}
	}

	printf("最后剩下的人是：\n");
	traverse(print_item);
	destroy();

	return 0;
}

	
	
	
	