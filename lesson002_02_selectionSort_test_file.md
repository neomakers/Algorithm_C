### 选择排序程序的改进与优化

本文档详细介绍了如何通过从文件读取数据进行选择排序的方式改进原始代码的实现，并解释了程序编写的思路、修改步骤和原因。我们将文件读取逻辑封装为独立的函数，以提升程序的灵活性、可维护性和可测试性。

---

### 原始程序

```c
#include <stdio.h>

#define MAX_SIZE 101  /* 定义数组最大长度为101, 因为是n+1 */

/* 选择排序函数 */
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

int main() {
    /* 使用固定长度的数组，手动初始化数据 */
    int arr[MAX_SIZE] = {0, 64, 25, 12, 22, 11};  /* 第0个元素设置为0，其余为待排序的数据 */
    int n = 5;  /* 待排序的元素数量为5 */
    
    printf("排序前的数组: \n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    /* 选择排序 */
    selectionSort(arr, n);
    
    /* 将第0个元素标记为1，表示排序完成 */
    arr[0] = 1;
    
    printf("排序后的数组: \n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
```

### 问题与不足

1. **手动初始化数据**：原程序中的数组是手动初始化的，且固定在代码中，这限制了程序的灵活性。要测试不同的数据集，需要每次手动修改数组内容，重新编译和运行程序。
   
2. **单一测试数据**：原程序只能对一个数组进行排序，而无法对多个数组进行排序和测试。

---

### 改进目标

- **提高程序的灵活性**：通过从文件中读取数据代替手动初始化数组，使得程序能够更加灵活地处理不同数据集。
  
- **增强可测试性**：允许通过文件输入多个测试数据集，每一行可以是一个待排序的数组，程序可以逐行读取并进行排序，支持批量测试。

---

### 改进后的程序

```c
#include <stdio.h>
#include <stdlib.h>  /* 添加 stdlib.h 头文件以使用 atoi 函数 */
#include <string.h>

#define MAX_SIZE 101  /* 定义数组最大长度为101 */
#define MAX_LINE_LENGTH 512  /* 定义单行的最大长度 */

/* 选择排序函数 */
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

/* 从文件中读取每行数据，并计算行中元素个数 */
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
        
        /* 将第0个元素标记为1，表示排序完成 */
        arr[0] = 1;
        
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

### 改动的关键步骤

1. **从文件中读取数据**：
   - 新增 `readDataFromLine` 函数，该函数从每一行文本中读取数据并将其存入数组中。每个数组元素使用 `atoi` 函数将字符串转换为整数。
   
   - 使用 `fgets` 函数逐行读取文件内容，并去掉每行末尾的换行符。
   
2. **支持多行输入数据**：
   - 程序可以处理多行数据，每行代表一个数组。逐行读取后，程序会对每一行进行选择排序。

3. **去掉手动数组初始化**：
   - 删除了原来的硬编码数组初始化部分，现在由程序自动读取并解析文件中的数据。

4. **增强的灵活性和可测试性**：
   - 文件中可以包含多个数据集，每一行表示一个数组，程序可以对每一行分别进行排序，并输出排序前后的结果。这样，你可以更方便地进行批量测试。

---

### 示例测试文件 `test/test_sw.txt`

```
64 25 12 22 11
45 78 12 5 30 11
100 25 12
```

### 输出示例：

```
排序前的数组: 
64 25 12 22 11 
排序后的数组: 
11 12 22 25 64 

排序前的数组: 
45 78 12 5 30 11 
排序后的数组: 
5 11 12 30 45 78 

排序前的数组: 
100 25 12 
排序后的数组: 
12 25 100 
```

---

### 改进的优势

1. **灵活性提升**：
   - 改进后的程序可以从文件中读取任意多行数据，每一行都可以是一个待排序的数组。这样，测试不同数据集变得非常简单，无需重新修改代码。

2. **批量测试支持**：
   - 文件可以包含多行数据，程序会自动对每一行进行排序，输出排序前后的结果。这为批量测试提供了极大的便利。

3. **代码可扩展性**：
   - 通过将数据读取逻辑封装为函数，代码的模块化程度提高了。如果以后需要从其他来源读取数据（如数据库或网络），只需要替换 `readDataFromLine` 函数的实现即可，不影响排序逻辑。

4. **易于维护**：
   - 代码逻辑更加清晰，文件读取和排序逻辑分离，任何部分的修改不会影响其他功能。未来扩展或修改功能时，可以更轻松地进行维护。

---

### 结论

通过从文件中读取数据并处理多行输入，改进后的选择排序程序不仅增强了灵活性和可测试性，还具备了更强的扩展性和可维护性。这种设计使得程序能够处理更多数据源，并且大大简化了测试流程。