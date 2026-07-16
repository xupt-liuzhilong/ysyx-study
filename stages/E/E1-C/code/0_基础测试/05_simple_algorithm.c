// // 1. 求最小公倍数
// #include <stdio.h>

// // 方法一：加法
// int main() {
//     int a, b;
//     scanf("%d %d", &a, &b);
    
//     // 最小公倍数至少是a和b的最小值
//     int m = a > b ? a : b;
//     while (1) {
//         if (m % a == 0 && m % b == 0) {
//             printf("%d", m);
//             break;
//         }

//         m++;
//     }

//     return 0;
// }

// // 方法二：乘法
// int main() {
//     int a, b;
//     scanf("%d %d", &a, &b);
    
//     for (int i = 1; ; i++) {
//         if ((a * i) / b == 0) {
//             printf("%d", a * i);
//             break;
//         }
//     }

//     return 0;
// }

// // 方法三：辗转相除法
// // 先求最大公约数，再用两数之积除以最大公约数
// int main() {
//     int a, b;
//     scanf("%d %d", &a, &b);

//     int m = a;
//     int n = b;
//     int c = m % n;
//     while (c != 0) {
//         m = n;
//         n = c;
//         c = m % n;
//     }

//     int d = (a * b) / c;
//     printf("%d", d);

//     return 0;
// }


// 2. 逆序字符串
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char* left, char* right) {
    while (left < right) {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
}

int main() {
    char str[100];
    gets(str);

    // 逆序整个字符串
    int len = strlen(str);
    reverse(str, str + len - 1);

    // 每个单词逆序
    char* start = str;
    while (*start) {
        char* end = start;

        while (*end != ' ' && *end != '\0') {
            end++;
        }

        reverse(start, end - 1);

        if (*end != '\0') {
            start = end + 1;
        }
        else {
            start = end;
        }
    }

    printf("%s", str);
    
    return 0;
}