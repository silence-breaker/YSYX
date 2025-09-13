#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


/* 产生随机数
int a[N];
srand(time(NULL));
void gen_random(int upper_bound,int lower_bound)
{
	int i;
	for (i = 0; i < N; i++)
       a[i] = lower_bound + rand() % (upper_bound - lower_bound);
}

void print_random()
{
	int i;
	for (i = 0; i < N; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main(void)
{
	gen_random(20,10);
	print_random();
	return 0;
}
*/
/*
#define N 4
int a[N] = {1,2,3,4};

// 交换数组中的两个元素
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 打印当前数组
void print_array()
{
    int i;
    for (i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// 递归生成全排列
// start: 当前处理的起始位置
// n: 数组长度
void permute(int start, int n)
{
    int i;
    
    // Base case: 如果起始位置已经到达数组末尾，打印当前排列
    if (start == n - 1)
    {
        print_array();
        return;
    }
    
    // 对当前位置start开始，依次将后面的元素换到start位置
    for (i = start; i < n; i++)
    {
        // 将第i个元素交换到当前处理的位置start
        swap(&a[start], &a[i]);
        
        // 递归处理剩余元素（start+1到末尾）
        permute(start + 1, n);
        
        // 恢复交换，回溯到原始状态，以便进行下一次交换
        swap(&a[start], &a[i]);
    }
}





int main()
{
    printf("生成 %d 个数的全排列：\n", N);
    permute(0, N);
    return 0;
}
*/

int main(void)
{
	char gesture[3][10] = {"scissor","stone","cloth"};
	int man,computer,result,ret;
	srand(time(NULL));
	while(1){
		computer = rand()%3;
		printf("\nInput your gesture (0-scissor 1-stone 2-cloth):\n ");
		ret = scanf("%d",&man);
		if(ret!=1 || man<0 || man>2)
		{
			printf("Invalid input! Please input 0,1 or 2.\n");
			continue;
		}
		printf("Your gesture: %s\t Computer's gesture: %s\n",gesture[man],gesture[computer]);
		result = (man-computer + 4)%3-1;
		if(result==0)
			printf("It's a draw!\n");
		else if(result==1)
			printf("You win!\n");
		else
			printf("You lose!\n");
	}
	return 0;
}