#include <stdio.h>
#include <stdlib.h>

// 交换两个元素的辅助函数
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 分区函数
int partition(int arr[], int l, int r) {
    int pivot = arr[r];  // 选择最右边的元素作为基准点
    int i = l - 1;       // i 是小于 pivot 的最后一个元素的索引

    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[r]);  // 将基准点放到正确的位置
    return i + 1;                // 返回基准点的位置
}

// 快速选择函数
int quickSelect(int arr[], int len, int k) {
    // 如果数组为空或 k 超出范围，返回一个无效值
    if (len == 0 || k < 0 || k >= len) {
        printf("输入无效！\n");
        return -1;  // 这里返回 -1 作为无效标记
    }

    int start = 0;
    int end = len - 1;

    // 循环直到找到第 k 小的元素
    while (start < end) {
        int idx = partition(arr, start, end);  // 调用分区函数

        if (idx == k) {
            return arr[idx];  // 找到第 k 小的元素
        } else if (idx > k) {
            end = idx - 1;  // 缩小右侧边界
        } else {
            start = idx + 1;  // 缩小左侧边界
        }
    }

    return arr[start];  // 返回找到的元素
}

int main() {
    int arr[] = {1, 12, 3, 5, 7, 19, 4, 2, 6, 4, 11};
    int len = sizeof(arr) / sizeof(arr[0]);
    int k = 8;  // 查找第 5 小的元素

    int result = quickSelect(arr, len, k);
    if (result != -1) {
        printf("数组中第 %d 小的元素是: %d\n", k, result);
    }

    return 0;
}
