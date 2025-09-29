#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//./mycp test_source.txt test_copy.txt 这两个参数如果需要在命令行里输入的话就是作为main函数的参数导入进去
int main(int argc, char *argv[])
{
    // 检查命令行参数
    if (argc != 3) {
        printf("用法: %s <源文件> <目标文件>\n", argv[0]);
        return 1;
    }
    
    // 打开源文件（只读）
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("打开源文件失败");
        exit(EXIT_FAILURE);
    }
    
    // 打开目标文件（写入）
    FILE *fpw = fopen(argv[2], "w");
    if(fpw == NULL) {
        perror("创建目标文件失败");
        fclose(fp);  // 关闭已打开的源文件
        exit(EXIT_FAILURE);
    }
    
    printf("开始复制文件: %s -> %s\n", argv[1], argv[2]);
    
    // 逐字符复制文件内容
    int ch;
    int char_count = 0;
    
    while ((ch = fgetc(fp)) != EOF) {
        if (fputc(ch, fpw) == EOF) {
            perror("写入文件失败");
            fclose(fp);
            fclose(fpw);
            exit(EXIT_FAILURE);
        }
        char_count++;
    }
    
    // 关闭文件
    fclose(fp);
    fclose(fpw);
    
    printf("文件复制完成! 共复制了 %d 个字符\n", char_count);
    
    // 验证复制结果 - 显示目标文件内容
    printf("\n目标文件内容:\n");
    FILE *verify = fopen(argv[2], "r");
    if (verify != NULL) {
        while ((ch = fgetc(verify)) != EOF) {
            putchar(ch);
        }
        fclose(verify);
        printf("\n");
    }
    
    return 0;
}