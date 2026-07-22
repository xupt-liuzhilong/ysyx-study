#include <stdio.h>
#include <string.h>

// 1.strlen() 求字符串长度
// size_t strlen(const char* str); 

// int main() {
//     char s[] = "hello";
//     int len = strlen(s);
//     printf("%d\n", len);
//     return 0;
// }

// 模拟实现strlen
// a.计数法
// int my_strlen(const char* str) {
//     int cnt = 0;

//     while (*str) {
//         cnt++;
//         str++;
//     }

//     return cnt;
// }

// b.递归法
// int my_strlen(const char* str) {
//     if (*str == '\0') {
//         return 0;
//     }

//     return 1 + my_strlen(str + 1);
// }

// c.指针减指针
// int my_strlen(const char* str) {
//     char* p = str;

//     while (*p) {
//         p++;
//     }

//     return p - str;
// }

// int main() {
//     char s[] = "hello";
//     int len = my_strlen(s);
//     printf("%d\n", len);
//     return 0;
// }


// 2.strcpy()字符串拷贝函数
// char* strcpy(char* destination, const char* source);

// int main() {
//     char str1[10] = "hello";
//     char str2[] = "world";
//     strcpy(str1, str2);
//     printf("%s\n", str1);
//     return 0;
// }

// 模拟实现strcpy
// char* my_strcpy(char* dest, const char* src) {
//     char* ret = dest;
//     while ((*dest++ = *src++)) {
//         ;
//     }

//     return ret;
// }

// int main() {
//     char str1[10] = "hello";
//     char str2[] = "world";
//     my_strcpy(str1, str2);
//     printf("%s\n", str1);
//     return 0;
// }


// 3.strcat()字符串追加函数
// char* strcat(char* destination, const char* source);

// int main() {
//     char str1[20] = "hello ";
//     char str2[] =  "world";
//     printf("%s\n", strcat(str1, str2));
//     return 0;
// }

// 模拟实现strcat()
// char* my_strcat(char* dest, const char* src) {
//     char* ret = dest;

//     while (*dest) {
//         dest++;
//     }
//     while ((*dest++ = *src++)) {
//         ;
//     }

//     return ret;
// }

// int main() {
//     char str1[20] = "hello ";
//     char str2[] =  "world";
//     printf("%s\n", my_strcat(str1, str2));
//     return 0;
// }
