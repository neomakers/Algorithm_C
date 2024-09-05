#include<stdio.h>
// 宏定义：将变量名和变量值打印出来
#define DEBUG_VAR_ARRAY(var1,var2) printf(#var1": %d "#var2": %d\n",var1,var2)
#define DEBUG_print_loop() printf("======================\n")
#define DEBUG_print_loop_i(var1,var2) printf("==========="#var1"%d==========\n",var2)
int main() {
    int array[] = { 9,8,7,6,5,4,3,2,1 };
    int num = sizeof(array) / sizeof(array[0]);
    for(int j=0;j<num-1;j++){
        DEBUG_print_loop();
        DEBUG_print_loop_i("outter",j);
        for (int i=0;i<num-1-j;i++) {
            DEBUG_print_loop_i("inner",i);
            if (array[i] > array[i + 1]) {
                int tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                DEBUG_VAR_ARRAY(i,array[i]);
                DEBUG_VAR_ARRAY(i+1,array[i+1]);
            }
        }
    }
    for (int i = 0; i < num; i++) {
        DEBUG_VAR_ARRAY(i+1,array[i+1]);
    }
    return 0;
}
