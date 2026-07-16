#include <stdio.h>

// 指针进阶学习

// // 1.指针变量 - 存放地址的变量
// int main() {
//     char* str1 = "hello";   // 字符串常量的是不可以修复的，相同的常量字符串只存储一次
//     char* str2 = "hello";   // 两个下相同的常量字符串的内存地址是相同的
//     char str3[] = "hello";  // 字符数组的数组名存放的是首元素的地址
//     char str4[] = "hello";  // 两个数组要开辟两个不同的空间，首元素地址必然不同

//     if (str1 == str2) {
//         printf("same\n");
//     }
//     else {
//         printf("no same\n");
//     }
//     if (str3 == str4) {
//         printf("same\n");
//     }
//     else {
//         printf("no same\n");
//     }

//     return 0;
// }


// 2.指针数组 - 存放指针的数组

// int main() {
//     int a[5] = {1, 2, 3, 4, 5};
//     int b[] = {2, 3, 4, 5, 6};
//     int c[] = {3, 4, 5, 6, 7};

//     int* arr[3] = {a, b, c};
//     // 指针数组可以模拟实现二维数组，也可以用二维数组的方式访问
//     // 但是二维数组元素的存储是连续的，与指针数组模拟实现的有所不同
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 5; j++) {
//             printf("%d ", arr[i][j]);
//         }
//         printf("\n");
//     }

//     return 0;
// }


// 3.数组指针 - 指向数组的指针

// int main() {
//     int arr[10] = {1, 2, 3, 4, 5};
//     int (*parr)[10] = &arr; // 这里 parr 是一个数组指针，存放的是一个数组的地址

//     double* d[5];
//     double* (*pd)[5] = &d;

//     return 0;
// }

// void print1(int arr[3][5], int r, int c) {
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 5; j++) {
//             printf("%d ", arr[i][j]);
//         }
//         printf("\n");
//     }
// }
// void print2(int (*arr)[5], int r, int c) {
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 5; j++) {
//             printf("%d ", (*((*arr) + i)) + j);
//         }
//         printf("\n");
//     }
// }
// int main() {
//     int arr[3][5] = {{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}};
//     print1(arr, 3, 5);
//     print2(&arr, 3, 5);
//     return 0;
// }

// int main() {
//     int arr[5];     // 数组
//     int *arr[5];    // 指针数组
//     int (*arr)[5];  // 数组指针
//     int (*arr[10])[5];// 存放数组指针的数组
//     return 0;
// }


// 4.数组传参、指针传参

// // (1) 一维数组传参
// void test(int arr[]) {}     // ok
// void test(int arr[10]) {}   // ok
// void test(int* arr) {}      // ok
// void test2(int* arr[20]) {} // ok
// void test2(int** arr) {}    // ok
// int main() {
//     int arr[10] = {0};
//     int* arr2[20] = {0};
//     test(arr);
//     test2(arr2);// arr2数组名表示首元素的地址，也就是二级指针的地址
//     return 0;
// }

// // (2) 二维数组传参
// void test(int arr[3][5]) {} // ok
// void test(int arr[][]) {}   // no - 只能省略行，不能省略列
// void test(int arr[][5]) {}  // ok
// void test(int* arr) {}      // no
// void test(int* arr[5]) {}   // no
// void test(int (*arr)[5]) {} // ok
// void test(int** arr) {}     // no
// int main() {
//     int arr[3][5] = {0};
//     test(arr);
//     return 0;
// }
