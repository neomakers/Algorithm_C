### 文件读取与选择排序程序的设计与实现

本项目的目标是创建一个模块化的选择排序程序，从文件中读取数据并进行排序。为了提高代码的可读性、可维护性和复用性，我们将代码模块化，分成多个文件进行管理。

---

### 项目结构

项目的文件结构如下：

```bash
D:.
│  lesson001_01_bubble_sort.md
│  lesson001_02_debug_disp.cpp
│  lesson001_03_bubble_sort.cpp
│  lesson001_04_debug.cpp
│  lesson002_01_selectionSort_test_file.cpp
│  lesson002_02_selectionSort_test_file.cpp
│  lesson002_02_selectionSort_test_file.md
│  lesson002_03_selectionSort.md
│  lesson003_03_selectionSort.cpp
│
├─headers
│      read_data.h
│      selection_sort.h
│
├─src
│      read_data.cpp
│      selection_sort.cpp
│
└─test
        test_sw.txt
```

- `headers/`: 包含头文件，用于声明各模块中的函数。
- `src/`: 包含源文件，分别实现数据读取和选择排序。
- `test/`: 包含测试数据文件 `test_sw.txt`，其中每行数据为待排序的数组。
- 其余 `lessonXXX` 文件是不同的测试和实现代码。

---

### 设计思路

为了实现更好的模块化设计，我们将关键功能分成两个独立模块：
1. **文件读取模块**：从指定的文件中逐行读取数据并解析为数组。
2. **选择排序模块**：实现经典的选择排序算法，对数组进行排序。

主程序则将这两个模块结合，完成文件读取和排序的任务。

---

### 各模块的实现

#### 1. 文件读取模块 (`read_data.h` 和 `read_data.cpp`)

- `read_data.h` 头文件声明了函数 `readDataFromLine`，该函数从文件的一行字符串中解析出整数数组。
  
```c
#ifndef READ_DATA_H
#define READ_DATA_H

/* 函数声明 */
int readDataFromLine(char *line, int arr[]);

#endif /* READ_DATA_H */
```

- `read_data.cpp` 实现了 `readDataFromLine` 函数。该函数使用 `strtok` 分割字符串，将数据转化为整数并存入数组。

```c
#include "../headers/read_data.h"
#include <stdlib.h>
#include <string.h>

/* 从字符串读取数据并解析为整数数组 */
int readDataFromLine(char *line, int arr[]) {
    int n = 0;
    char *token = strtok(line, " ");
    
    /* 使用strtok按空格分割数据 */
    while (token != NULL) {
        arr[++n] = atoi(token);  /* 将字符串转换为整数并保存到数组中 */
        token = strtok(NULL, " ");
    }
    
    return n;  /* 返回元素个数 */
}
```

#### 2. 选择排序模块 (`selection_sort.h` 和 `selection_sort.cpp`)

- `selection_sort.h` 头文件声明了 `selectionSort` 函数，该函数对传入的数组进行选择排序。

```c
#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

/* 选择排序函数声明 */
void selectionSort(int arr[], int n);

#endif /* SELECTION_SORT_H */
```

- `selection_sort.cpp` 实现了 `selectionSort` 函数。该函数遍历数组，通过交换实现升序排序。

```c
#include "../headers/selection_sort.h"

void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    
    /* 外层循环控制第i个位置需要放置的最小值 */
    for (i = 1; i <= n; i++) {
        minIndex = i;
        for (j = i + 1; j <= n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        /* 交换最小值到第i个位置 */
        if (minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}
```

#### 3. 主程序 (`lesson003_03_selectionSort.cpp`)

主程序负责调用文件读取和排序功能，处理用户输入，并最终输出排序结果。

```c
#include <stdio.h>
#include <string.h>  // 用于 strcspn 函数
#include "./headers/read_data.h"  // 包含数据读取函数
#include "./headers/selection_sort.h"  // 包含选择排序函数

#define MAX_SIZE 101  /* 定义数组最大长度为101 */
#define MAX_LINE_LENGTH 512  /* 定义单行的最大长度 */

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];  /* 用于存储每一行的数据 */
    int arr[MAX_SIZE];  /* 定义数组 */
    int n;  /* 数组元素数量 */
    
    const char *filename = "test/test_sw.txt";  /* 测试文件路径 */
    
    /* 打开文件 */
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s!\n", filename);
        return 1;
    }

    /* 逐行读取文件内容 */
    while (fgets(line, sizeof(line), file)) {
        /* 清除末尾的换行符 */
        line[strcspn(line, "\n")] = 0;
        
        /* 读取当前行的数据并获取元素个数 */
        n = readDataFromLine(line, arr);
        
        /* 输出排序前的数组 */
        printf("排序前的数组: \n");
        for (int i = 1; i <= n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        
        /* 选择排序 */
        selectionSort(arr, n);
        
        /* 输出排序后的数组 */
        printf("排序后的数组: \n");
        for (int i = 1; i <= n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n\n");
    }
    
    /* 关闭文件 */
    fclose(file);
    
    return 0;
}
```

---

### 编译和运行

编译时需要将主程序与两个模块一起编译。可以使用以下命令：

```bash
g++ lesson002_03_selectionSort.cpp src/read_data.cpp src/selection_sort.cpp -I headers -o selection_sort_program
```

此命令告诉编译器在 `headers/` 目录中查找头文件，并将 `src/` 目录中的源文件编译为可执行程序 `selection_sort_program`。

---

### 测试文件

在 `test/test_sw.txt` 文件中放置测试数据。格式如下，每一行表示一个待排序的数组：

```
64 25 12 22 11
45 78 12 5 30 11
100 25 12
```

程序将逐行读取文件内容，对每行数据进行选择排序并输出排序结果。

---

### 总结

该程序通过模块化的方式，将文件读取、排序功能分离成独立的模块，并在主程序中调用。这种设计不仅提高了代码的复用性和可维护性，也使得代码结构更加清晰，易于扩展。通过这种设计，我们可以方便地实现其他排序算法或读取不同的数据源，只需适当调整模块和主程序即可。