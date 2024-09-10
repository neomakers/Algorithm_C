#include <stdlib.h>  /* 包含 atoi 函数 */
#include <string.h>
#include "read_data.h"

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
