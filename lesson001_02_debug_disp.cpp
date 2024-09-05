#include<stdio.h>

// 宏定义：将变量名和变量值打印出来
#define DEBUG_VAR_array(var1,var2) printf(#var1": %d "#var2": %d\n",var1,var2)

int main() {
    int a = 5;
    int b = 10;
    int array[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int num = sizeof(array) / sizeof(array[0]);


    // 打印数组中的某个元素
    for (int i = 0; i < num; i++) {
        DEBUG_VAR_array(i,array[i]); // 自动打印array[i]的值
    }

    return 0;
}
