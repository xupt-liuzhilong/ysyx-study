#include <stdio.h>

// 冒泡排序
// void bubble_sort(int* arr, int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (arr[j] > arr[j + 1]) {
//                 int tmp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = tmp;
//             }
//         }
//     }
// }
void print_arr(int* arr, int n) {
    for (int i = 0; i< n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// int main() {
//     int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
//     int n = sizeof(arr) / sizeof (arr[0]);

//     print_arr(arr, n);
//     bubble_sort(arr, n);
//     print_arr(arr, n);
    
//     return 0;
// }


#include <stdlib.h>
#include <string.h>

int cmp_int(const void* p1, const void* p2) {
    return *(int*)p1 - *(int*)p2;
}

void test1() {
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int n = sizeof(arr) / sizeof (arr[0]);
    qsort(arr, n, sizeof(arr[0]), cmp_int);
    print_arr(arr, n);
}

typedef struct student {
    char _name[10];
    int _age;
} stu;

int cmp_name(const void* p1, const void* p2) {
    return strcmp(((stu*)p1)->_name, ((stu*)p2)->_name);
}

int cmp_age(const void* p1, const void* p2) {
    return ((stu*)p1)->_age - ((stu*)p2)->_age;
}

void test2() {
    stu s[3] = {{"zhangsan", 10}, {"lisi", 30}, {"wangwu", 18}};
    int n = sizeof(s) / sizeof(s[0]);
    qsort(s, n, sizeof(s[0]), cmp_name);
    qsort(s, n, sizeof(s[0]), cmp_age);
}

void swap(char* a, char* b, int size) {
    for (int i = 0; i < size; i++) {
        char tmp = *a;
        *a = *b;
        *b = tmp;
        a++;
        b++;
    }
}
// 模仿qsort实现一个通用的冒泡排序算法
void bubble_sort(void* base, int num, int size,
            int (*cmp)(const void* p1, const void* p2)) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (cmp((char*)base + size * j, (char*)base + size * (j + 1)) > 0) {
                swap((char*)base + size * j, (char*)base + size * (j + 1), size);
            }
        }
    }
}

void test3() {
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int n = sizeof(arr) / sizeof (arr[0]);
    bubble_sort(arr, n, sizeof(arr[0]), cmp_int);
    print_arr(arr, n);
}

void test4() {
    stu s[3] = {{"zhangsan", 10}, {"lisi", 30}, {"wangwu", 18}};
    int n = sizeof(s) / sizeof(s[0]);
    bubble_sort(s, n, sizeof(s[0]), cmp_name);
    bubble_sort(s, n, sizeof(s[0]), cmp_age);
}

int main() {
    // test1();
    // test2();
    test3();
    test4();
    return 0;
}