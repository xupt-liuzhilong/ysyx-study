#include <stdio.h>
#include <string.h>


// 1. memcpy() - 内存拷贝函数
// void* memcpy(void* destination, const void* source, size_t num);

// int main() {
//     int arr1[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     int arr2[20] = {0};
//     memcpy(arr2, arr1, sizeof(int) * 5);
//     return 0;
// }

// 模拟实现memcpy
// void* my_memcpy(void* dest, const void* src, size_t num) {
//     char* p1 = (char*)dest;
//     char* p2 = (char*)src;

//     while (num--) {
//         *p1++ = *p2++;
//     }

//     return dest;
// }

// int main() {
//     int arr1[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     int arr2[20] = {0};
//     my_memcpy(arr2, arr1, sizeof(int) * 5);
//     return 0;
// }


// 2. memmove() - 同一段地址内的内存拷贝
// void* memmove(void* destination, const void* source, size_t num);

// int main() {
//     int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     memmove(arr + 2, arr, sizeof(int) * 5);
//     return 0;
// }

// 模拟实现memmove
// void* my_memmove(void* dest, const void* src, size_t num) {
//     char* p1 = (char*)dest;
//     char* p2 = (char*)src;

//     if (p1 < p2) {
//         while (num--) {
//             *p1++ = *p2++;
//         }
//     }
//     else {
//         while (num--) {
//             *(p1 + num) = *(p2 + num);
//         }
//     }

//     return dest;
// }

// int main() {
//     int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     // my_memmove(arr + 2, arr, sizeof(int) * 5);
//     my_memmove(arr, arr + 2, sizeof(int) * 5);
//     return 0;
// }


// 3. memcmp() - 内存比较函数
// int memcmp(const void* ptr1, const void* ptr2, size_t num);

// int main() {
//     int arr1 [10] = {1, 2, 3, 4, 5};
//     int arr2 [10] = {1, 2, 3};

//     int ret = memcmp(arr2, arr1, sizeof(int) * 5);
//     printf("%d\n", ret);

//     return 0;
// }


// 4. memset() - 内存设置函数
// void* memcmp(void* ptr, int value, size_t num);

// int main() {
//     int arr[10];
//     memset(arr, 1, 20); // 每个字节置为1
//     return 0;
// }