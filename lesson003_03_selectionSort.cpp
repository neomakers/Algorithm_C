#include <stdio.h>
#include <string.h>  // 用于 strcspn 函数
// src/read_data.cpp
#include "./headers/read_data.h"  // 相对于 src 文件夹的位置

// src/selection_sort.cpp
#include "./headers/selection_sort.h"  // 相对于 src 文件夹的位置

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
