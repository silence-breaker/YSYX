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
/*
int main(void)
{
    int i = 1;
    while(1)
    {
        int *p = malloc(i);
        i = 2*i;
    }
}
*/
/*
int add(int a)
{
    a = a+1;
    return a;
}

int main(void)
{
    int a = 0;
    add(a);
    printf("%d\n",a);
    return 0;

}
*/
/*
#include <stdarg.h>

// 辅助函数：输出整数
void print_int(int num) {
    if (num < 0) {
        putchar('-');
        num = -num;
    }
    if (num >= 10) {
        print_int(num / 10);
    }
    putchar(num % 10 + '0');
}

// 辅助函数：输出浮点数
void print_float(double num) {
    if (num < 0) {
        putchar('-');
        num = -num;
    }
    
    // 输出整数部分
    int int_part = (int)num;
    print_int(int_part);
    
    // 输出小数点
    putchar('.');
    
    // 输出小数部分（保留6位）
    double frac_part = num - int_part;
    for (int i = 0; i < 6; i++) {
        frac_part *= 10;
        int digit = (int)frac_part;
        putchar(digit + '0');
        frac_part -= digit;
    }
}

// 辅助函数：输出字符串
void print_string(const char *str) {
    while (*str) {
        putchar(*str);
        str++;
    }
}

void myprintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int i = va_arg(args, int);
                print_int(i);  // 修改：使用专门的函数输出整数
            } else if (*format == 'f') {
                double d = va_arg(args, double);
                print_float(d);  // 修改：使用专门的函数输出浮点数
            } else if (*format == 'c') {
                // char 被提升为 int
                int c = va_arg(args, int);
                putchar(c);
            } else if (*format == 's') {
                char *s = va_arg(args, char *);
                print_string(s);  // 修改：使用专门的函数输出字符串
            } else {
                putchar('%');
                putchar(*format);
            }
        } else {
            putchar(*format);
        }
        format++;
    }
    
    va_end(args);
}

int main(void)
{
    myprintf("Hello %s! Your score is %d and average is %f. Grade: %c\n", "Alice", 95, 89.5, 'A');
    return 0;
}
*/

#include <string.h>

char *strtok(char *str, const char *delim)
{
    static char *last = NULL; // 保存上次调用的位置
    if (str != NULL) {
        last = str; // 如果传入新字符串，重置 last
    } else if (last == NULL) {
        return NULL; // 如果没有更多的字符串可处理，返回 NULL
    }

    // 跳过开头的分隔符
    while (*last && strchr(delim, *last)) {
        last++;
    }

    if (*last == '\0') {
        last = NULL; // 没有更多的标记
        return NULL;
    }

    char *start = last; // 标记当前 token 的开始位置

    // 找到下一个分隔符
    while (*last && !strchr(delim, *last)) {
        last++;
    }

    if (*last) {
        *last = '\0'; // 用 null 字符终止当前 token
        last++; // 移动到下一个字符，准备下一次调用
    } else {
        last = NULL; // 没有更多的标记
    }

    return start; // 返回当前 token 的起始位置

}

char *strtok_r(char *str, const char *delim, char **saveptr)
{
    char *start;

    if (str != NULL) {
        *saveptr = str; // 如果传入新字符串，重置 saveptr
    } else if (*saveptr == NULL) {
        return NULL; // 如果没有更多的字符串可处理，返回 NULL
    }

    // 跳过开头的分隔符
    while (**saveptr && strchr(delim, **saveptr)) {
        (*saveptr)++;
    }

    if (**saveptr == '\0') {
        *saveptr = NULL; // 没有更多的标记
        return NULL;
    }

    start = *saveptr; // 标记当前 token 的开始位置

    // 找到下一个分隔符
    while (**saveptr && !strchr(delim, **saveptr)) {
        (*saveptr)++;
    }

    if (**saveptr) {
        **saveptr = '\0'; // 用 null 字符终止当前 token
        (*saveptr)++; // 移动到下一个字符，准备下一次调用
    } else {
        *saveptr = NULL; // 没有更多的标记
    }

    return start; // 返回当前 token 的起始位置
}

char URL[]="http://www.google.cn/search?complete=1&hl=zh-CN&ie=GB2312&q=linux&meta=";

int main(void)
{
    printf("%s\n",URL);
    
    char *token;
    printf("使用 strtok:\n");
    token = strtok(URL,"?");
    printf("路径部分为\n");
    printf("%s\n",token);
    printf("键部分为\n"); 
    while ((token = strtok(NULL, "&")) != NULL) {
        printf("%s\n",token);
    }
    //注意在执行strtok的时候已经把URL数组的特殊字符都改成了'\0'，所以如果再用strtok的话就得重新赋值URL数组
    strcpy(URL,"http://www.google.cn/search?complete=1&hl=zh-CN&ie=GB2312&q=linux&meta=");
    printf("使用 strtok_r:\n");
    char *saveptr;
    token = strtok_r(URL,"?",&saveptr);
    printf("路径部分为\n");
    printf("%s\n",token);
    printf("键部分为\n"); 
    while ((token = strtok_r(NULL, "&",&saveptr)) != NULL) {
        printf("%s\n",token);
    }
    return 0;
}