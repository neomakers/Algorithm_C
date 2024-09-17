// unsorted_array.h

#ifndef UNSORTED_ARRAY_H
#define UNSORTED_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

// 定义 UnsortedArray 结构体
struct UnsortedArray
{
    unsigned int len;    // 数组的总长度
    unsigned int filled; // 数组中已存储的元素个数
    int *arr;            // 动态分配的数组
};

// 函数声明
struct UnsortedArray create_array(unsigned int initial_len);
void expand_array(struct UnsortedArray *array);
void append(struct UnsortedArray *array, int value);
void print_array(struct UnsortedArray *array);

#endif // UNSORTED_ARRAY_H
