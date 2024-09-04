# 单行尝试
```cpp
#include<stdio.h>
int main() {
    int array[] = { 9,8,7,6,5,4,3,2,1 };
    int num = sizeof(array) / sizeof(array[0]);
    for (int i=0;i<num-1;i++) {
        printf("===={loop:%d}====\n"); // 错误：格式化字符串未使用变量
        if (array[i] > array[i + 1]) {
            int tmp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = tmp;
            printf("array[%d]:%d\n", i, array[i]);
            printf("array[%d]:%d\n", i + 1, array[i + 1]);
        }
    }
    for (int i = 0; i < num - 1; i++) { // 潜在问题：不打印最后一个元素
        printf("%d", array[i]);
    }
    return 0;
}
```

### 错误结果

- 编译时不会报错，但运行时 `printf("===={loop:%d}====\n");` 这行代码不会按预期打印循环次数，而是打印出字符串字面量（可能是空字符串或包含 `%d` 的字符串，具体取决于编译器和环境）。
- 数组排序部分逻辑正确，但由于 `printf` 语句的错误，不会看到循环次数的正确输出。
- 最后一个数组元素不会被打印出来。

### 分析原因

- `printf("===={loop:%d}====\n");` 中的格式化字符串 `%d` 没有被任何变量替换，因此不会打印出预期的循环次数。
- 第二个循环的条件是 `i < num - 1`，导致最后一个元素不会被打印。

### 改进错误

#### 修改部分的代码

1. 修正 `printf` 语句中的格式化字符串，使其能够正确地打印循环次数。
2. 修改第二个循环的条件，确保打印整个数组。

```cpp
// 修改部分
printf("===={loop:%d}====\n", i); // 修正了格式化字符串
// ...
for (int i = 0; i < num; i++) { // 修改循环条件，确保打印整个数组
    printf("%d", array[i]);
    if (i < num - 1) {
        printf(" "); // 在元素之间打印空格分隔
    }
}
printf("\n"); // 数组打印完毕后换行
```

### 整体代码（标注修改部分）

```cpp
#include<stdio.h>
int main() {
    int array[] = { 9,8,7,6,5,4,3,2,1 };
    int num = sizeof(array) / sizeof(array[0]);
    for (int i=0;i<num-1;i++) {
        printf("===={loop:%d}====\n", i); // 修改：修正了格式化字符串
        if (array[i] > array[i + 1]) {
            int tmp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = tmp;
            printf("array[%d]:%d\n", i, array[i]);
            printf("array[%d]:%d\n", i + 1, array[i + 1]);
        }
    }
    for (int i = 0; i < num; i++) { // 修改：修改了循环条件，确保打印整个数组
        printf("%d", array[i]);
        if (i < num - 1) {
            printf(" "); // 在元素之间打印空格分隔
        }
    }
    printf("\n"); // 数组打印完毕后换行
    return 0;
}
```


# 移动头部实现双层循环
## 简单加入循环
```cpp
#include<stdio.h>
int main() {
	int array[] = { 9,8,7,6,5,4,3,2,1 };
	int num = sizeof(array) / sizeof(array[0]);
	for(int j=0;j<num-1;j++){
		printf("========{outer_loop:%d}========\n", j);
		printf("j:%d:array[%d]:%d\n", j,j,array[j]);
		for (int i=j;i<num-1;i++) {
			printf("===={inner_loop:%d}====\n",i);
			if (array[i] > array[i + 1]) {
				int tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				printf("array[%d]:%d\n", i, array[i]);
				printf("array[%d]:%d\n", i + 1, array[i + 1]);
			}
		}
	}
	for (int i = 0; i < num; i++) {
		printf("%d", array[i]);
	}
	return 0;
}
```
输出结果如下
```shell
========{outer_loop:0}========
j:0:array[0]:9
===={inner_loop:0}====
array[0]:8
array[1]:9
===={inner_loop:1}====
array[1]:7
array[2]:9
===={inner_loop:2}====
array[2]:6
array[3]:9
===={inner_loop:3}====
array[3]:5
array[4]:9
===={inner_loop:4}====
array[4]:4
array[5]:9
===={inner_loop:5}====
array[5]:3
array[6]:9
===={inner_loop:6}====
array[6]:2
array[7]:9
===={inner_loop:7}====
array[7]:1
array[8]:9
========{outer_loop:1}========
j:1:array[1]:7
===={inner_loop:1}====
array[1]:6
array[2]:7
===={inner_loop:2}====
array[2]:5
array[3]:7
===={inner_loop:3}====
array[3]:4
array[4]:7
===={inner_loop:4}====
array[4]:3
array[5]:7
===={inner_loop:5}====
array[5]:2
array[6]:7
===={inner_loop:6}====
array[6]:1
array[7]:7
===={inner_loop:7}====
========{outer_loop:2}========
j:2:array[2]:5
===={inner_loop:2}====
array[2]:4
array[3]:5
===={inner_loop:3}====
array[3]:3
array[4]:5
===={inner_loop:4}====
array[4]:2
array[5]:5
===={inner_loop:5}====
array[5]:1
array[6]:5
===={inner_loop:6}====
===={inner_loop:7}====
========{outer_loop:3}========
j:3:array[3]:3
===={inner_loop:3}====
array[3]:2
array[4]:3
===={inner_loop:4}====
array[4]:1
array[5]:3
===={inner_loop:5}====
===={inner_loop:6}====
===={inner_loop:7}====
========{outer_loop:4}========
j:4:array[4]:1
===={inner_loop:4}====
===={inner_loop:5}====
===={inner_loop:6}====
===={inner_loop:7}====
========{outer_loop:5}========
j:5:array[5]:3
===={inner_loop:5}====
===={inner_loop:6}====
===={inner_loop:7}====
========{outer_loop:6}========
j:6:array[6]:5
===={inner_loop:6}====
===={inner_loop:7}====
========{outer_loop:7}========
j:7:array[7]:7
===={inner_loop:7}====
864213579
```
核心应该是我们的内层循环，在冒泡排序中，每次外层循环后，数组的最后一个元素都会是剩余未排序部分的最大元素，并且这个元素在接下来的排序过程中将不再被考虑（即不再参与比较和交换）。然而，在上面的代码中，尽管您尝试通过减少内层循环的长度来优化（for (int i=0;i<num-1-j;i++)），但实际上这并不是冒泡排序的标准做法，且这种优化方式并没有真正减少不必要的比较。，修改之后的结果

```cpp
	#include<stdio.h>
	int main() {
		int array[] = { 9,8,7,6,5,4,3,2,1 };
		int num = sizeof(array) / sizeof(array[0]);
		for(int j=0;j<num-1;j++){
			printf("========{outer_loop:%d}========\n", j);
			printf("j:%d:array[%d]:%d\n", j,j,array[j]);
			for (int i=0;i<num-1-j;i++) {
				printf("===={inner_loop:%d}====\n",i);
				if (array[i] > array[i + 1]) {
					int tmp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = tmp;
					printf("array[%d]:%d\n", i, array[i]);
					printf("array[%d]:%d\n", i + 1, array[i + 1]);
				}
			}
		}
		for (int i = 0; i < num; i++) {
			printf("%d", array[i]);
		}
		return 0;
	}
```
输出结果
```
========{outer_loop:0}========
j:0:array[0]:9
===={inner_loop:0}====
array[0]:8
array[1]:9
===={inner_loop:1}====
array[1]:7
array[2]:9
===={inner_loop:2}====
array[2]:6
array[3]:9
===={inner_loop:3}====
array[3]:5
array[4]:9
===={inner_loop:4}====
array[4]:4
array[5]:9
===={inner_loop:5}====
array[5]:3
array[6]:9
===={inner_loop:6}====
array[6]:2
array[7]:9
===={inner_loop:7}====
array[7]:1
array[8]:9
========{outer_loop:1}========
j:1:array[1]:7
===={inner_loop:0}====
array[0]:7
array[1]:8
===={inner_loop:1}====
array[1]:6
array[2]:8
===={inner_loop:2}====
array[2]:5
array[3]:8
===={inner_loop:3}====
array[3]:4
array[4]:8
===={inner_loop:4}====
array[4]:3
array[5]:8
===={inner_loop:5}====
array[5]:2
array[6]:8
===={inner_loop:6}====
array[6]:1
array[7]:8
========{outer_loop:2}========
j:2:array[2]:5
===={inner_loop:0}====
array[0]:6
array[1]:7
===={inner_loop:1}====
array[1]:5
array[2]:7
===={inner_loop:2}====
array[2]:4
array[3]:7
===={inner_loop:3}====
array[3]:3
array[4]:7
===={inner_loop:4}====
array[4]:2
array[5]:7
===={inner_loop:5}====
array[5]:1
array[6]:7
========{outer_loop:3}========
j:3:array[3]:3
===={inner_loop:0}====
array[0]:5
array[1]:6
===={inner_loop:1}====
array[1]:4
array[2]:6
===={inner_loop:2}====
array[2]:3
array[3]:6
===={inner_loop:3}====
array[3]:2
array[4]:6
===={inner_loop:4}====
array[4]:1
array[5]:6
========{outer_loop:4}========
j:4:array[4]:1
===={inner_loop:0}====
array[0]:4
array[1]:5
===={inner_loop:1}====
array[1]:3
array[2]:5
===={inner_loop:2}====
array[2]:2
array[3]:5
===={inner_loop:3}====
array[3]:1
array[4]:5
========{outer_loop:5}========
j:5:array[5]:6
===={inner_loop:0}====
array[0]:3
array[1]:4
===={inner_loop:1}====
array[1]:2
array[2]:4
===={inner_loop:2}====
array[2]:1
array[3]:4
========{outer_loop:6}========
j:6:array[6]:7
===={inner_loop:0}====
array[0]:2
array[1]:3
===={inner_loop:1}====
array[1]:1
array[2]:3
========{outer_loop:7}========
j:7:array[7]:8
===={inner_loop:0}====
array[0]:1
array[1]:2
123456789
```
