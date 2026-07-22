#include <stdio.h>
#include <string.h>

// 4.strcmp() - 字符串比较函数
// int strcmp(const char* str1, const char* str2);

// int main() {
//     char str1[] = "abcdef";
//     char str2[] = "abcd";
//     int ret = strcmp(str1, str2);
//     printf("%d\n", ret);
//     return 0;
// }

// 模拟实现strcmp
// int my_strcmp(const char* str1, const char* str2) {
//     while (*str1 == *str2) {
//         if (*str1 == '\0') {
//             return 0;
//         }
//         str1++;
//         str2++;
//         if (*str1 > *str2) {
//             return 1;
//         }
//         if (*str1 < *str2) {
//             return -1;
//         }
//     }
// }

// int main() {
//     char str1[] = "abcdef";
//     char str2[] = "abcdef";
//     int ret = my_strcmp(str1, str2);
//     printf("%d\n", ret);
//     return 0;
// }


// 5.strncpy()
// int main() {
//     char arr[20] = "abcdef";
//     // strncpy(arr, arr, 2);
//     strncpy(arr, "hello", 3);

//     printf("%s\n", arr);
//     return 0;
// }


// 6.strncat()
// int main() {
//     char arr[20] = "abcdef";
//     strncat(arr, arr, 2);
//     strncat(arr, "hello", 3);

//     printf("%s\n", arr);
//     return 0;
// }


// 7.strncmp()
// int main() {
//     char str1[] = "abcdef";
//     char str2[] = "abcd";
//     int ret = strncmp(str1, str2, 4);
//     printf("%d\n", ret);
// }


// 8.strstr() - 查找子串函数
// 返回第一个匹配成功子串字符的地址
// char* strstr(const char* str1, const char* str2);

// int main() {
//     char* str1 = "abbcdef";
//     char* str2 = "bbc";
//     char* p = strstr(str1, str2);
//     printf("%s\n", p);
//     return 0;
// }

// 模拟实现strstr
// char* my_strstr(const char* str1, const char* str2) {
//     if (!*str2) {
//         return (char*)str1;
//     }

//     char* cp = (char*)str1;
//     char *s1, *s2;

//     while (*cp) {
//         s1 = cp;
//         s2 = (char*)str2;
//         while (*s2 && (*s1 == *s2)) {
//             s1++;
//             s2++;
//         }

//         if (!*s2) {
//             return cp;
//         }

//         cp++;
//     }
    
//     return NULL;
// }

// int main() {
//     char* str1 = "abbbcdef";
//     char* str2 = "bbc";
//     char* p = my_strstr(str1, str2);
//     printf("%s\n", p);
//     return 0;
// }


// 9.strtok() - 分割字符串
// 第一次传递字符串地址和分隔符地址，返回第一个分割出来的子串的地址
// 后续可以传递NULL和分隔符地址，每次返回一个后续分割出的子串的地址
// int main() {
//     char* p = "lzl@edu.com";
//     char* s = "@.";

//     char arr[20];
//     strcpy(arr, p);

//     char* str = NULL;

//     for (str = strtok(arr, s); str != NULL;str = strtok(NULL, s)) {
//         printf("%s\n", str);
//     }

//     return 0;
// }

// 10.strerror() - 返回错误码对应的错误信息
// int main() {
//     printf("%s\n", strerror(0));
//     printf("%s\n", strerror(1));
//     printf("%s\n", strerror(2));
//     printf("%s\n", strerror(3));
//     printf("%s\n", strerror(4));
//     printf("%s\n", strerror(5));
//     return 0;
// }

#include <errno.h>
int main() {
    FILE* pf;
    pf = fopen("test.c", "r");
    if (pf == NULL) {
        // 这里 errno 保存的是最后一个错误码
        printf("%s\n", strerror(errno));
    }
    return 0;
}
