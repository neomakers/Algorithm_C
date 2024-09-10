#include "selection_sort.h"

/* 选择排序函数实现 */
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
