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
