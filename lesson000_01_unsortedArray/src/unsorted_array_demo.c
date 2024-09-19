#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // 包含 INT_MAX 宏



// 定义无序数组的数据结构
struct UnsortedArray {
    unsigned int len;    // 数组的总长度
    unsigned int filled; // 数组中已存储的元素个数
    int *arr;            // 动态分配的数组
};

// 创建 UnsortedArray 的函数
struct UnsortedArray create(unsigned int size) {
    struct UnsortedArray ua;
    ua.len = size;
    ua.filled = 0;  // 初始化时还没有存储任何元素
    ua.arr = (int *)malloc(size * sizeof(int));  // 为数组动态分配内存

    if (ua.arr == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }

    return ua;
}

// 调整数组大小的函数，将数组长度加倍
void resize(struct UnsortedArray *ua) {
    unsigned int new_len = ua->len * 2;
    int *new_arr = (int *)realloc(ua->arr, new_len * sizeof(int));  // 调整数组大小

    if (new_arr == NULL) {
        printf("内存重新分配失败！\n");
        exit(1);
    }

    ua->arr = new_arr;
    ua->len = new_len;

    printf("数组大小已加倍，现在大小为: %u\n", ua->len);
}

// 向数组中追加元素的函数
void append(struct UnsortedArray *ua, int v) {
    // 如果数组已满，调用 resize 函数将其大小加倍
    if (ua->filled == ua->len) {
        resize(ua);
    }

    // 在数组中添加新元素
    ua->arr[ua->filled] = v;
    ua->filled++;
}

// 打印数组内容的辅助函数
void printUnsortedArray(struct UnsortedArray ua) {
    printf("数组内容：");
    for (unsigned int i = 0; i < ua.filled; i++) {
        printf("%d ", ua.arr[i]);
    }
    printf("\n");
}

// 向数组的指定位置插入元素的函数
void insert(struct UnsortedArray *ua, int i, int v) {
    // 如果数组已满，调用 resize 函数将其大小加倍
    if (ua->filled == ua->len) {
        resize(ua);
    }

    // 如果插入位置不合法，打印错误信息
    if (i < 0 || i > ua->filled) {
        printf("插入位置无效！\n");
        return;
    }

    // 将数组中的元素后移，为新元素腾出位置
    for (int j = ua->filled - 1; j >= i; j--) {
        ua->arr[j + 1] = ua->arr[j];
    }

    // 在指定位置插入新元素
    ua->arr[i] = v;
    ua->filled++;  // 更新已存储的元素个数
}

// 从数组中删除指定位置的元素
void remove_element(struct UnsortedArray *ua, int i) {
    // 如果数组为空或者位置无效，则不进行任何操作
    if (ua->filled == 0 || i < 0 || i >= ua->filled) {
        printf("无法删除，数组为空或删除位置无效！\n");
        return;
    }

    // 将数组中从位置 i+1 开始的元素前移一位，覆盖删除的元素
    for (int j = i + 1; j < ua->filled; j++) {
        ua->arr[j - 1] = ua->arr[j];
    }

    // 更新已存储的元素个数
    ua->filled--;

    printf("已删除位置 %d 的元素，当前数组长度: %u\n", i, ua->filled);
}


// 查找数组中的最小元素
int find_min(struct UnsortedArray *ua) {
    // 如果数组为空，返回 INT_MAX 表示无最小值
    if (ua->filled == 0) {
        printf("数组为空，无法找到最小值！\n");
        return INT_MAX;  // INT_MAX 是 int 类型的最大值，表示无效结果
    }

    // 初始化最小值为第一个元素
    int min = ua->arr[0];

    // 遍历数组，找到最小值
    for (unsigned int i = 1; i < ua->filled; i++) {
        if (ua->arr[i] < min) {
            min = ua->arr[i];
        }
    }

    return min;
}

// 查找数组中的最大元素
int find_max(struct UnsortedArray *ua) {
    // 如果数组为空，返回 INT_MIN 表示无最大值
    if (ua->filled == 0) {
        printf("数组为空，无法找到最大值！\n");
        return INT_MIN;  // INT_MIN 是 int 类型的最小值，表示无效结果
    }

    // 初始化最大值为第一个元素
    int max = ua->arr[0];

    // 遍历数组，找到最大值
    for (unsigned int i = 1; i < ua->filled; i++) {
        if (ua->arr[i] > max) {
            max = ua->arr[i];
        }
    }

    return max;
}


int main() {
    unsigned int size = 5;
    
    // 创建一个大小为5的无序数组
    struct UnsortedArray ua = create(size);

    // 示例：向数组中追加一些数据
    append(&ua, 5);
    append(&ua, 3);
    append(&ua, 9);
    append(&ua, 1);
    append(&ua, 7);

    // 打印当前数组
    printUnsortedArray(ua);

    // 继续追加，触发数组扩容
    append(&ua, 10);
    append(&ua, 15);

    // 打印扩容后的数组
    printUnsortedArray(ua);

    // 向数组中追加一些数据
    insert(&ua, 0, 15);
    insert(&ua, 1, 13);
    insert(&ua, 2, 19);
    insert(&ua, 3, 11);
    insert(&ua, 4, 17);

    // 打印当前数组
    printUnsortedArray(ua);
        // 从数组中删除某个元素
    remove_element(&ua, 2);  // 删除索引为2的元素
    printUnsortedArray(ua);

    // 尝试删除第0个元素
    remove_element(&ua, 0);
    printUnsortedArray(ua);

    // 尝试删除无效位置
    remove_element(&ua, 10);
    // 查找数组中的最小值
    int min_value = find_min(&ua);
    if (min_value != INT_MAX) {
        printf("数组中的最小值是: %d\n", min_value);
    }

    // 查找数组中的最大值
    int max_value = find_max(&ua);
    if (max_value != INT_MIN) {
        printf("数组中的最大值是: %d\n", max_value);
    }


    // 释放内存
    free(ua.arr);

    return 0;
}