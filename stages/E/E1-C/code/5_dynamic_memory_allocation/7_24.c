#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// 1. malloc() - 动态分配一段内存空间，默认不初始化内存
// void* malloc(size_t size);

// int main() {
//     int* p = (int*)malloc(sizeof(int) * 10);

//     for (int i = 0; i < 10; i++) {
//         scanf("%d", p + i);
//     }

//     for (int i = 0; i < 10; i++) {
//         printf("%d ", *(p + i));
//     }

//     free(p);
//     p = NULL;

//     return 0;
// }

// 2. free() - 释放动态内存分配的空间
// - free后p的地址不是NULL，仍然指向原来空间，这时p就会变成野指针
// - 每次free后尽量手动将指针置空
// 如果动态分配内存后不free长时间会导致内存泄漏，操作系统卡顿等问题


// 3. calloc() - 分配连续的num个size大小的内存空间，并初始化内存为0
// void* colloc(size_t num, size_t size);

// int main() {
//     int* p = (int*)calloc(10, sizeof(int));

//     for (int i = 0; i < 10; i++) {
//         printf("%d ", *(p + i));
//     }

//     free(p);
//     p = NULL;

//     return 0;
// }


// 4. realloc() - 给原来动态分配的的内存空间，重新分配一段新的内存空间
// - 如果原空间后空间大小足够只需要继续在其后分配空间到要求大小为止，返回原地址
// - 否则，重新找一段内存空间一段要求大小的空间，并将原地址空间的数据拷贝过来，返回新的地址
// void* colloc(size_t size);

int main() {
    int* p = (int*)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++) {
        scanf("%d", p + i);
    }

    p = (int*)realloc(p, sizeof(int) * 20);

    for (int i = 0; i < 10; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    for (int i = 10; i < 20; i++) {
        scanf("%d", p + i);
    }

    for (int i = 0; i < 20; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    free(p);
    p = NULL;

    return 0;
}