#include <stdio.h>

char a[4][3][2] = {{{'a', 'b'}, {'c', 'd'}, {'e', 'f'}},
		   {{'g', 'h'}, {'i', 'j'}, {'k', 'l'}},
		   {{'m', 'n'}, {'o', 'p'}, {'q', 'r'}},
		   {{'s', 't'}, {'u', 'v'}, {'w', 'x'}}};

char (*pa)[2] = &a[1][0];
char (*ppa)[3][2] = &a[1];
char show_pa; // 声明为全局变量，但不在这里初始化
char show_ppa; // 声明为全局变量，但不在这里初始化

int main(void)
{
    // 在函数内部初始化
    show_pa = (*(pa+5))[1]; //不像数组名，可以直接加索引，需要先解引用为数组然后再加索引
    show_ppa = (*(ppa+1))[2][1];
    
    printf("%c %c\n", show_pa, show_ppa);
    return 0;
}



