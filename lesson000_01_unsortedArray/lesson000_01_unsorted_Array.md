
# 无序数组

## 生成create_array和print_array

1. **`create_array(int *array, int array_size, int N)`**：
   - **功能**：初始化数组的前 `N` 个元素为随机生成的整数（范围 0 到 99），并将剩余的元素初始化为 `-1`，表示未初始化。
   - **参数**：
     - `int *array`：指向数组的指针，用于存储数据。
     - `int array_size`：数组的总长度。
     - `int N`：需要初始化的整数个数。

2. **`print_array(int *array, int array_size)`**：
   - **功能**：遍历并打印数组的所有元素。如果元素为 `-1`（表示未初始化），则输出 `"None"`；否则，输出实际的整数值。
   - **参数**：
     - `int *array`：指向数组的指针，表示需要打印的数组。
     - `int array_size`：数组的长度，用于控制遍历范围。

3. **`main()`**：
   - **功能**：程序的入口函数。它创建一个长度为 `M` 的数组，调用 `create_array` 进行数组初始化，并调用 `print_array` 打印数组内容。
   - **操作流程**：
     1. 创建一个长度为 `M` 的数组。
     2. 随机初始化前 `N` 个元素，并将未初始化的元素设置为 `-1`。
     3. 打印整个数组的内容。
  
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 包含 memset 函数
#include <time.h>

#define UNINITIALIZED_VALUE -1 // 用于表示未初始化的值

// 创建并初始化数组的函数
void create_array(int *array, int array_size, int N)
{
    // 使用 memset 将数组初始化为 UNINITIALIZED_VALUE
    memset(array, UNINITIALIZED_VALUE, array_size * sizeof(int));

    // 随机生成 N 个整数并赋值到数组的前 N 个位置
    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % 100; // 随机生成 0 到 99 之间的整数
    }
}

// 打印数组的函数
void print_array(int *array)
{
    for (int i = 0; i < sizeof(array); i++)
    {
        if (array[i] == UNINITIALIZED_VALUE)
        {
            printf("None "); // 打印表示未初始化的值
        }
        else
        {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}

int main()
{
    int M = 10;   // 数组的总长度
    int N = 5;    // 需要初始化的整数个数
    int array[M]; // 创建长度为 M 的数组

    srand(time(0)); // 设置随机种子

    // 调用 create_array 函数来初始化数组
    create_array(array, M, N);

    // 调用 print_array 函数来打印数组
    print_array(array);

    return 0;
}
```

## 优化数组管理：在数组中嵌入元素计数

在编程过程中，我们经常需要管理数组中的数据。在大多数情况下，数组只是一个连续的存储空间，而无法告诉我们当前存储了多少个元素。虽然我们可以通过外部变量来记录存储的元素个数，但这样会增加管理的复杂性。如果不小心修改或忘记更新这个变量，可能会导致数据处理出错。

为了解决这个问题，我们可以考虑将数组的第 0 个位置专门用于存储当前存储的元素个数，而把从第 1 个位置开始的空间用来存放实际的数据。这样，每次操作数组时，我们只需要访问第 0 个位置就能清楚地知道数组中有多少有效的元素。

通过这种方式，数组不仅能够存储数据，还能同时记录自身的状态。这是一种非常实用的思路，特别是在动态管理数组的场景下。接下来，我们会通过一个简单的程序实现这个想法。


```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 包含 memset 函数
#include <time.h>

#define UNINITIALIZED_VALUE -1 // 用于表示未初始化的值

// 创建并初始化数组的函数，第0个位置存储N
void create_array(int *array, int array_size, int N)
{
    // 第 0 个位置存储元素个数 N
    array[0] = N;

    // 随机生成 N 个整数并赋值到数组的后 N 个位置
    for (int i = 1; i <= N; i++)
    {
        array[i] = rand() % 100; // 随机生成 0 到 99 之间的整数
    }

    // 剩余位置初始化为 UNINITIALIZED_VALUE
    for (int i = N + 1; i < array_size; i++)
    {
        array[i] = UNINITIALIZED_VALUE;
    }
}

// 打印数组的函数，第0个位置存储N
void print_array(int *array, int array_size)
{
    int N = array[0]; // 从第 0 个位置获取当前存储的元素个数
    printf("数组中的元素个数: %d\n", N);

    // 遍历数组的后续位置
    for (int i = 1; i < array_size; i++)
    {
        if (array[i] == UNINITIALIZED_VALUE)
        {
            printf("None "); // 打印表示未初始化的值
        }
        else
        {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}

int main()
{
    int M = 10;         // 实际存储数字的长度
    int N = 5;          // 需要初始化的整数个数
    int array[M + 1];   // 创建长度为 M + 1 的数组，第0个位置存储N

    srand(time(0));     // 设置随机种子

    // 调用 create_array 函数来初始化数组
    create_array(array, M + 1, N);

    // 调用 print_array 函数来打印数组
    print_array(array, M + 1);

    return 0;
}
```

通过这样的设计，我们能够简化数组管理的复杂度，同时确保数据的正确性，避免外部变量管理上的潜在错误。这也是我们在编写代码时应该时刻考虑的：如何让程序变得更加简洁高效，同时减少出错的可能性。

## Append和Insert

