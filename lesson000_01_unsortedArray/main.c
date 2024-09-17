#include "unsorted_array.h"
int main()
{
    struct UnsortedArray array = create_array(5); // 初始创建长度为5的数组

    // 添加元素
    append(&array, 10);
    append(&array, 20);
    append(&array, 30);

    // 打印数组内容
    print_array(&array);

    // 扩展并添加更多元素
    append(&array, 40);
    append(&array, 50);
    append(&array, 60); // 此时数组将扩展

    print_array(&array);

    // 释放动态分配的内存
    free(array.arr);

    return 0;
}
