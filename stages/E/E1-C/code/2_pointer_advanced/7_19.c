#include <stdio.h>
#include <string.h>

// sizeof(arr) 这里arr表是整个数组，计算的是整个数组的大小
// &arr 这里arr表示的是整个数组，取出整个数组得地址

// int main() {
//     // //一维数组
//     // int a[] = {1,2,3,4};

//     // printf("%d\n",sizeof(a));       // 16
//     // printf("%d\n",sizeof(a+0));     // 4/8
//     // printf("%d\n",sizeof(*a));      // 4
//     // printf("%d\n",sizeof(a+1));     // 4/8
//     // printf("%d\n",sizeof(a[1]));    // 4

//     // printf("%d\n",sizeof(&a));      // 4/8
//     // printf("%d\n",sizeof(*&a));     // 16
//     // printf("%d\n",sizeof(&a+1));    // 4/8
//     // printf("%d\n",sizeof(&a[0]));   // 4/8
//     // printf("%d\n",sizeof(&a[0]+1)); // 4/8


//     // //字符数组
//     // char arr[] = {'a','b','c','d','e','f'};

//     // printf("%d\n", sizeof(arr));        // 6
//     // printf("%d\n", sizeof(arr+0));      // 4/8
//     // printf("%d\n", sizeof(*arr));       // 1
//     // printf("%d\n", sizeof(arr[1]));     // 1
//     // printf("%d\n", sizeof(&arr));       // 4/8
//     // printf("%d\n", sizeof(&arr+1));     // 4/8
//     // printf("%d\n", sizeof(&arr[0]+1));  // 4/8

//     // printf("%d\n", strlen(arr));        // 随机值
//     // printf("%d\n", strlen(arr+0));      // 随机值
//     // // printf("%d\n", strlen(*arr));    // error
//     // // printf("%d\n", strlen(arr[1]));  // error
//     // printf("%d\n", strlen(&arr));       // 随机值
//     // printf("%d\n", strlen(&arr+1));     // 随机值 - 6
//     // printf("%d\n", strlen(&arr[0]+1));  // 随机值 - 1


//     // char arr[] = "abcdef";
//     // // [a b c d e f \0]

//     // printf("%d\n", sizeof(arr));        // 7
//     // printf("%d\n", sizeof(arr+0));      // 4/8
//     // printf("%d\n", sizeof(*arr));       // 1
//     // printf("%d\n", sizeof(arr[1]));     // 1
//     // printf("%d\n", sizeof(&arr));       // 4/8
//     // printf("%d\n", sizeof(&arr+1));     // 4/8
//     // printf("%d\n", sizeof(&arr[0]+1));  // 4/8

//     // printf("%d\n", strlen(arr));        // 6
//     // printf("%d\n", strlen(arr+0));      // 6
//     // // printf("%d\n", strlen(*arr));    // error
//     // // printf("%d\n", strlen(arr[1]));  // error
//     // printf("%d\n", strlen(&arr));       // 6
//     // printf("%d\n", strlen(&arr+1));     // 随机值
//     // printf("%d\n", strlen(&arr[0]+1));  // 5


//     // char *p = "abcdef";

//     // printf("%d\n", sizeof(p));      // 4/8
//     // printf("%d\n", sizeof(p+1));    // 4/8
//     // printf("%d\n", sizeof(*p));     // 1
//     // printf("%d\n", sizeof(p[0]));   // 1
//     // printf("%d\n", sizeof(&p));     // 4/8
//     // printf("%d\n", sizeof(&p+1));   // 4/8
//     // printf("%d\n", sizeof(&p[0]+1));// 4/8

//     // printf("%d\n", strlen(p));      // 6
//     // printf("%d\n", strlen(p+1));    // 5
//     // // printf("%d\n", strlen(*p));  // error
//     // // printf("%d\n", strlen(p[0]));// error
//     // printf("%d\n", strlen(&p));     // 随机值
//     // printf("%d\n", strlen(&p+1));   // 随机值
//     // printf("%d\n", strlen(&p[0]+1));// 5


//      //二维数组
//     int a[3][4] = {0};

//     printf("%d\n",sizeof(a));           // 48
//     printf("%d\n",sizeof(a[0][0]));     // 4
//     printf("%d\n",sizeof(a[0]));        // 16
//     printf("%d\n",sizeof(a[0]+1));      // 4/8
//     printf("%d\n",sizeof(*(a[0]+1)));   // 4
//     printf("%d\n",sizeof(a+1));         // 4/8
//     printf("%d\n",sizeof(*(a+1)));      // 16
//     printf("%d\n",sizeof(&a[0]+1));     // 4/8
//     printf("%d\n",sizeof(*(&a[0]+1)));  // 16
//     printf("%d\n",sizeof(*a));          // 16
//     printf("%d\n",sizeof(a[3]));        // 16

//     return 0;
// }


// // 笔试题1
// int main()
// {
//     int a[5] = { 1, 2, 3, 4, 5 };
//     int *ptr = (int *)(&a + 1);
//     printf( "%d,%d", *(a + 1), *(ptr - 1)); // 2, 5
//     return 0;
// }


// // 笔试题2
// // 由于还没学习结构体，这里告知结构体的大小是20个字节
// struct Test
// {
//     int Num;
//     char *pcName;
//     short sDate;
//     char cha[2];
//     short sBa[4];
// }*p;
// // 假设p 的值为0x100000。 如下表表达式的值分别为多少？
// // 已知，结构体Test类型的变量大小是20个字节
// int main()
// {
//     printf("%p\n", p + 0x1);                // 0x100014
//     printf("%p\n", (unsigned long)p + 0x1); // 0x100001
//     printf("%p\n", (unsigned int*)p + 0x1); // 0x100004
//     return 0;
// }


// // 笔试题3
// int main()
// {
//     int a[4] = { 1, 2, 3, 4 };
//     int *ptr1 = (int *)(&a + 1);
//     int *ptr2 = (int *)((int)a + 1);
//     printf( "%x,%x", ptr1[-1], *ptr2); // 4, 2000000
//     return 0;
// }
 

// // 笔试题4
// int main() 
// {
//     int a[3][2] = { (0, 1), (2, 3), (4, 5) }; 
//     // (0, 1)逗号表达式，运算结果是 1
//     // 实际存储 {1, 3, 5, 0, 0, 0}
//     int *p;
//     p = a[0];
//     printf( "%d", p[0]);
//     return 0;
// }


// // 笔试题5
// int main()
// {
//     int a[5][5];
//     int(*p)[4];
//     p = a;
//     printf( "%p,%d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]); // FFFFFFFC, -4
//     // 指针相减返回的是两个指针之间元素的个数，小地址减大地址得负值
//     return 0;
// }


// // 笔试题6
// int main()
// {
//     int aa[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//     int *ptr1 = (int *)(&aa + 1);
//     int *ptr2 = (int *)(*(aa + 1));
//     printf( "%d,%d", *(ptr1 - 1), *(ptr2 - 1));// 10, 5
//     return 0;
// }


// // 笔试题7
// int main()
// {
//     char *a[] = {"work","at","alibaba"};
//     char**pa = a;
//     pa++;
//     printf("%s\n", *pa); // at
//     return 0;
// }


// 笔试题8
int main()
{
    char *c[] = {"ENTER","NEW","POINT","FIRST"};
    char**cp[] = {c+3,c+2,c+1,c};
    char***cpp = cp;
    printf("%s\n", **++cpp);        // POINT
    printf("%s\n", *--*++cpp+3);    // ER
    printf("%s\n", *cpp[-2]+3);     // ST
    printf("%s\n", cpp[-1][-1]+1);  // EW
    return 0;
}