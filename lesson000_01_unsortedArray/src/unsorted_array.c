// unsorted_array.c

#include "unsorted_array.h"

// 初始化数组
struct UnsortedArray create_array(unsigned int initial_len)
{
    struct UnsortedArray array;
    array.len = initial_len;
    array.filled = 0;
    array.arr = (int *)malloc(initial_len * sizeof(int));

    if (array.arr == NULL)
    {
        printf("内存分配失败\n");
        exit(1); // 内存分配失败时退出程序
    }

    return array;
}

// 扩展数组大小
void expand_array(struct UnsortedArray *array)
{
    unsigned int new_len = array->len * 2;
    int *new_arr = (int *)realloc(array->arr, new_len * sizeof(int));

    if (new_arr == NULL)
    {
        printf("内存重新分配失败\n");
        exit(1); // 内存重新分配失败时退出程序
    }

    array->arr = new_arr;
    array->len = new_len;
}

// 添加元素
void append(struct UnsortedArray *array, int value)
{
    if (array->filled == array->len)
    {
        expand_array(array);
    }
    array->arr[array->filled] = value;
    array->filled++;
}

// 打印数组
void print_array(struct UnsortedArray *array)
{
    printf("数组长度: %u, 已填充元素个数: %u\n", array->len, array->filled);
    for (unsigned int i = 0; i < array->filled; i++)
    {
        printf("%d ", array->arr[i]);
    }
    printf("\n");
}
