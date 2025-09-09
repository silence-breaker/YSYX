#!/bin/bash

# 检查是否提供了文件名参数
if [ $# -eq 0 ]; then
    echo "用法: $0 <C文件名>"
    echo "例如: $0 深入理解函数练习.c"
    exit 1
fi

# 获取文件名
c_file=$1

# 检查文件是否存在
if [ ! -f "$c_file" ]; then
    echo "错误: 文件 '$c_file' 不存在"
    exit 1
fi

# 从C文件名中生成可执行文件名（移除.c后缀）
executable="${c_file%.c}"

# 编译C文件
echo "正在编译 $c_file..."
gcc "$c_file" -lm -Wall -o "$executable"

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "编译成功! 正在执行 $executable..."
    echo "----------------------------------------"
    # 执行编译后的程序
    ./"$executable"
    echo "----------------------------------------"
    echo "程序执行完毕。"
else
    echo "编译失败。"
    exit 1
fi
