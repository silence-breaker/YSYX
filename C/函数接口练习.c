#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*
char* strcpy(char *dest, char *src)
{
    int i = 0;
    for(i=0;i<sizeof(src);i++)
    {
        dest[i] = src[i];
    }
    if(dest[sizeof(dest)-1]!='\0')
        dest[sizeof(dest)-1]='\0';
    return dest;
}

char *shrink_space(char *dest, const char *src,size_t n)
{
    int i = 0;
    int j = 0;
    int prev_was_space = 0; // 标记前一个字符是否为空白字符
    
    for(i=0; i<n && src[i]!='\0'; i++)
    {
        // 检查当前字符是否为空白字符
        if(src[i]==' ' || src[i]=='\n' || src[i]=='\t' || src[i]=='\r')
        {
            // 如果前一个字符不是空白字符，添加一个空格
            if(!prev_was_space)
            {
                dest[j] = ' ';
                j++;
                prev_was_space = 1;
            }
            // 如果前一个字符也是空白字符，跳过当前字符
        }
        else
        {
            // 非空白字符，直接复制
            dest[j] = src[i];
            j++;
            prev_was_space = 0;
        }
    }
    
    dest[j] = '\0'; // 正确添加字符串结束符
    return dest;
}


int main(void)
{
    char buf[10];
    char src[10];
    printf("请输入字符串\n");
    scanf("%s",src);

    strcpy(buf,src);
    printf("%s\n",buf);

    char article[] = "This Content hoho     \n  is ok  \t      ok?\n        file system uttered words   ok ok      ?end.";
    char processed[100];
    shrink_space(processed,article,sizeof(article));
    printf("%s\n",processed);
    return 0;
}
*/
int main(void)
{
    int i = 1;
    while(1)
    {
        int *p = malloc(i);
        i = 2*i;
    }
}
