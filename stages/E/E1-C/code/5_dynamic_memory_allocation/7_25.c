#include <stdio.h>
#include <stdlib.h>

// 动态内存分配的常见错误：

// 1. 对空指针进行解引用操作
//  - 要对malloc的返回值进行判空操作

// int main() {
//     // int* p = NULL;
//     // *p = 4; // error

//     int* p = (int*)malloc(sizeof(int));
//     if (p != NULL) {
//         *p = 4;
//     }

//     printf("%d\n", *p);

//     free(p);
//     p = NULL;

//     return 0;
// }


// 2. 动态开辟空间越界访问

// int main() {
//     int* p = (int*)malloc(sizeof(int) * 5);

//     for (int  i = 0; i < 10; i++) {
//         // 存在越界访问
//         *(p + i) = i;
//     }

//     free(p)
//     p = NULL;

//     return 0;
// }


// 3. 使用free释放非动态开辟的空间

// int main() {
//     int a = 0;
//     int* p = &a;

//     free(p);// error
//     p = NULL;

//     return 0;
// }


// 4. 使用free只释放动态开辟空间的一部分

// int main() {
//     int* p = (int*)malloc(sizeof(int) * 10);

//     for (int  i = 0; i < 5; i++) {
//         *p++;
//     }

//     free(p);// error
//     p = NULL;

//     return 0;
// }


// 5. 对已经释放的空间重复释放

// int main() {
//     int* p = (int*)malloc(sizeof(int) * 10);

//     free(p);
//     free(p);// error
//     p = NULL;

//     return 0;
// }


// 6. 动态开辟的空间忘记释放

// int main() {
//     int* p = (int*)malloc(sizeof(int) * 10);

//     // 忘记释放长时间运行，可能导致内存泄漏

//     return 0;
// }



// 练习题1
// void GetMemory(char *p)
// {
//     // p是str的一份临时拷贝
//     p = (char *)malloc(100);
//     // 动态开辟的内存是存在p里面的，不影响str
//     // 函数结束，p销毁，而且动态开辟的空间没有销毁
// }
// void Test(void)
// {
//     char *str = NULL;
//     GetMemory(str);// 传进去的是值
//     // str仍为NULL
//     strcpy(str, "hello world");
//     printf(str);
// }


// 练习题2
// char *GetMemory(void)
// {
//     char p[] = "hello world";
//     return p;
//     // p是一个数组，存在栈区
//     // 函数结束，p所指向的空间也就销毁了
// }
// void Test(void)
// {
//     char *str = NULL;
//     str = GetMemory();
//     printf(str);
// }


// 练习题3
// void GetMemory(char **p, int num)
// {
//     *p = (char *)malloc(num);
// }
// void Test(void)
// {
//     char *str = NULL;
//     GetMemory(&str, 100);
//     strcpy(str, "hello");
//     printf(str);
//     // 使用完动态开辟的空间后没有free掉
//     // 可能导致内存泄漏
// }


// 练习题4
// void Test(void)
// {
//     char *str = (char *) malloc(100);
//     strcpy(str, "hello");
//     free(str);
//     // 这里free之后需要把指针置为NULL
//     if(str != NULL)
//     {
//         // str申请的那块空间已经释放掉了，没有办法继续访问
//         strcpy(str, "world");
//         printf(str);
//     }
// }



// C/C++程序分配内存的几个区域：
// 1. 栈区：存放局部变量/数组、函数参数、返回数据、返回地址，函数结束后空间会还给OS
// 2. 堆区：动态开辟的内存，一般不会主动释放
// 3. 代码段（静态区）：全局变量、static数据
// 4. 数据段：常量、函数体（类成员函数和全局函数）



// 柔性数组
// 结构体中最后一个元素允许是一个位置大小的数组
// - 前面必须至少有一个成员
// - sizeof计算大小的时候不包含柔性数组
// - malloc开辟空间的时候，可以多开辟一段空间（期望柔性数组的大小）

struct S {
    int n;
    int arr[];
};

int main() {
    // printf("%d\n", sizeof(struct S)); // 4

    struct S* ps = (struct S*)malloc(sizeof(struct S) + sizeof(int) * 10);
    ps->n = 10;
    for (int i = 0; i < 10; i++) {
        ps->arr[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", ps->arr[i]);
    }
    printf("\n");

    struct S* ptr = (struct S*)realloc(ps, sizeof(struct S) + sizeof(int) * 20);
    if (ptr != NULL) {
        ps = ptr;
    }
    ps->n = 20;
    for (int i = 10; i < 20; i++) {
        ps->arr[i] = i;
    }
    for (int i = 0; i < 20; i++) {
        printf("%d ", ps->arr[i]);
    }
    printf("\n");

    free(ps);
    ps = NULL;

    return 0;
}

// 柔性数组的优点：
// - 方便内存释放，只需要释放一次
// - 有利于访问速度，柔性数组和结构的其他成员在动态开辟的空间上是连续的