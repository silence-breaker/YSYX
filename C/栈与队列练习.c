/*
#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

struct point { int row, col; } stack[512];
int top = 0;

void push(struct point p)
{
	stack[top++] = p;
}

struct point pop(void)
{
	return stack[--top];
}

int is_empty(void)
{
	return top == 0;
}

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

void print_maze(void)
{
	int i, j;
	for (i = 0; i < MAX_ROW; i++) {
		for (j = 0; j < MAX_COL; j++)
			printf("%d ", maze[i][j]);
		putchar('\n');
	}
	printf("*********\n");
}

struct point predecessor[MAX_ROW][MAX_COL] = {
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
};

void visit(int row, int col, struct point pre)
{
	struct point visit_point = { row, col };
	maze[row][col] = 2;
	predecessor[row][col] = pre;
	push(visit_point);
}

int main(void)
{
	struct point p = { 0, 0 };

	maze[p.row][p.col] = 2;
	push(p);	
	
	while (!is_empty()) {
		p = pop();
		if (p.row == MAX_ROW - 1  
		    && p.col == MAX_COL - 1)
			break;
		if (p.col+1 < MAX_COL    
		    && maze[p.row][p.col+1] == 0)
			visit(p.row, p.col+1, p);
		if (p.row+1 < MAX_ROW     
		    && maze[p.row+1][p.col] == 0)
			visit(p.row+1, p.col, p);
		if (p.col-1 >= 0        
		    && maze[p.row][p.col-1] == 0)
			visit(p.row, p.col-1, p);
		if (p.row-1 >= 0        
		    && maze[p.row-1][p.col] == 0)
			visit(p.row-1, p.col, p);
		print_maze();
	}
	if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1) {
		printf("(%d, %d)\n", p.row, p.col);
		while (predecessor[p.row][p.col].row != -1) {
			p = predecessor[p.row][p.col];
			printf("(%d, %d)\n", p.row, p.col);
		}
	} else
		printf("No path!\n");

	return 0;
}
*/


/*
#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

// 迷宫地图：0-通路, 1-墙, 2-已走过的路径, 3-尝试过但走不通的死路
int maze[MAX_ROW][MAX_COL] = {
    0, 1, 0, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
};

void print_maze(void)
{
    int i, j;
    for (i = 0; i < MAX_ROW; i++) {
        for (j = 0; j < MAX_COL; j++)
            printf("%d ", maze[i][j]);
        putchar('\n');
    }
    printf("*********\n");
}

/**
 * @brief 递归解决迷宫问题
 * @param row 当前行
 * @param col 当前列
 * @return 1 如果找到路径, 0 如果找不到
 */
/*
int solve_maze_recursive(int row, int col)
{
    // 1. 检查越界或障碍物
    if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL || maze[row][col] != 0) {
        return 0; // 此路不通
    }

    // 2. 标记当前位置为已走过
    maze[row][col] = 2;
    print_maze(); // 打印每一步的探索过程

    // 3. 检查是否到达终点 (Base Case for success)
    if (row == MAX_ROW - 1 && col == MAX_COL - 1) {
        printf("找到路径，开始回溯打印:\n");
        printf("(%d, %d)\n", row, col);
        return 1; // 成功找到路径
    }

    // 4. 递归探索四个方向：下、右、上、左 (可以调整顺序)
    if (solve_maze_recursive(row + 1, col)) { // 向下
        printf("(%d, %d)\n", row, col);
        return 1;
    }
    if (solve_maze_recursive(row, col + 1)) { // 向右
        printf("(%d, %d)\n", row, col);
        return 1;
    }
    if (solve_maze_recursive(row - 1, col)) { // 向上
        printf("(%d, %d)\n", row, col);
        return 1;
    }
    if (solve_maze_recursive(row, col - 1)) { // 向左
        printf("(%d, %d)\n", row, col);
        return 1;
    }

    // 5. 如果四个方向都走不通，说明是死路，进行回溯
    maze[row][col] = 3; // 标记为死路
    printf("死路回溯...\n");
    print_maze();
    return 0; // 此路不通，返回失败
}

int main(void)
{
    printf("开始探索迷宫...\n");
    if (solve_maze_recursive(0, 0)) {
        printf("成功找到从起点到终点的路径！\n");
    } else {
        printf("没有找到路径！\n");
    }

    printf("\n最终迷宫状态 (2表示正确路径, 3表示探索过的死路):\n");
    print_maze();

    return 0;
}
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 5
#define MAX_COL 5

// 最小所需队列大小 - 根据测试得出
#define QUEUE_SIZE 5

// 简化的点结构，不需要存储前驱了
struct point { 
    int row, col; 
};

// 环形队列
struct point *queue;
int head = 0;
int tail = 0;
int queue_capacity = QUEUE_SIZE;
int max_queue_usage = 0; // 跟踪队列的最大使用量

// 检查队列是否已满
int is_full(void)
{
    return (tail + 1) % queue_capacity == head;
}

// 检查队列是否为空
int is_empty(void)
{
    return head == tail;
}

// 将点加入队列
void enqueue(struct point p)
{
    if (is_full()) {
        printf("队列已满，无法继续！当前队列容量: %d\n", queue_capacity);
        exit(1);
    }
    queue[tail] = p;
    tail = (tail + 1) % queue_capacity;
    
    // 跟踪队列的当前使用量和最大使用量
    int current_usage = (tail >= head) ? (tail - head) : (queue_capacity - head + tail);
    if (current_usage > max_queue_usage) {
        max_queue_usage = current_usage;
    }
}

// 从队列中取出一个点
struct point dequeue(void)
{
    if (is_empty()) {
        printf("队列为空！\n");
        exit(1);
    }
    struct point p = queue[head];
    head = (head + 1) % queue_capacity;
    return p;
}

// 迷宫数组
int maze[MAX_ROW][MAX_COL] = {
    0, 1, 0, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
};

// 记录每个单元格是否已被访问
int visited[MAX_ROW][MAX_COL] = {0};

// 访问一个新位置
void visit(int row, int col)
{
    if (visited[row][col]) return;
    
    struct point visit_point = { row, col };
    visited[row][col] = 1; // 标记为已访问
    enqueue(visit_point);
}

int solve_maze(void)
{
    struct point p = { 0, 0 };
    
    // 标记起点为已访问
    visited[p.row][p.col] = 1;
    enqueue(p);
    
    while (!is_empty()) {
        p = dequeue();
        
        // 如果到达终点
        if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1) {
            return 1; // 找到路径
        }
        
        // 探索四个方向（右、下、左、上）
        // 右
        if (p.col+1 < MAX_COL && maze[p.row][p.col+1] != 1 && !visited[p.row][p.col+1])
            visit(p.row, p.col+1);
        // 下
        if (p.row+1 < MAX_ROW && maze[p.row+1][p.col] != 1 && !visited[p.row+1][p.col])
            visit(p.row+1, p.col);
        // 左
        if (p.col-1 >= 0 && maze[p.row][p.col-1] != 1 && !visited[p.row][p.col-1])
            visit(p.row, p.col-1);
        // 上
        if (p.row-1 >= 0 && maze[p.row-1][p.col] != 1 && !visited[p.row-1][p.col])
            visit(p.row-1, p.col);
    }
    
    return 0; // 没找到路径
}

int main(void)
{
    // 分配队列内存
    queue = (struct point *)malloc(queue_capacity * sizeof(struct point));
    if (queue == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }
    
    // 初始化访问状态
    for (int r = 0; r < MAX_ROW; r++) {
        for (int c = 0; c < MAX_COL; c++) {
            visited[r][c] = 0;
        }
    }
    
    // 解决迷宫问题
    printf("使用大小为 %d 的环形队列求解迷宫问题\n", QUEUE_SIZE);
    int result = solve_maze();
    
    // 输出结论
    printf("\n结论: 迷宫%s路径能到达终点\n", result ? "有" : "没有");
    printf("队列最大使用量: %d 个元素\n", max_queue_usage);
    printf("解决此迷宫问题至少需要 %d 个元素的环形队列空间\n", max_queue_usage + 1);
    
    // 释放队列内存
    free(queue);
    
    return 0;
}