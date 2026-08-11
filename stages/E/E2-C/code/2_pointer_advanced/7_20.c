#include <stdio.h>

// 练习1
// 杨氏矩阵：每行从左向右递增，每列从上到下递增
// 在这个矩阵中找一个数，时间复杂度 O(N)

// int find(int arr[3][3], int* px, int * py, int k) {
//     // 初始化当前元素为矩阵右上角元素
//     int x = 0;
//     int y = *py - 1;

//     while (x < *px && y >= 0) { // 判断是否越界
//         // 用整个矩阵的右上角的元素与k比较
//         // 如果小于k，表示该行的最大值小于k，改行不可能出现k
//         if (arr[x][y] < k) {
//             x++;// 划掉矩阵当前行，跳转到下一行
//         }
//         // 如果大于k，表示该列的最小值大于k，改列不可能出现k
//         else if (arr[x][y] > k) {
//             y--;// 划掉矩阵当前列，跳转到左边小的一列
//         }
//         else {
//             *px = x;// 用来返回k的下标
//             *py = y;
//             return 1;
//         }
//     }

//     // 如果越界循环结束，说明没有找到k
//     return 0;
// }

// int main() {
//     int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//     int x = 3;
//     int y = 3;
//     int k = 7;

//     if (find(arr, &x, &y, k)) {
//         printf("找到了!\n");
//         printf("下标是：%d %d\n", x, y);
//     }
//     else {
//         printf("没找到！\n");
//     }

//     return 0;
// }


// 练习2
// 左旋转字符串k次
// 例 "ABCDEF" 左旋转2次得到 "CDEFAB"

#include <string.h>

// 方法一：将左边的字符串保存起来，后面的字符向前移动，把保存的字符放到最后
// 重复这个动作k次，即得到左旋转k次后的结果
// void string_left_rotate(char* str, int k) {
//     int len = strlen(str);
//     for (int i = 0; i < k; i++) {
//         char tmp = str[0];

//         for (int j = 0; j < len - 1; j++) {
//             str[j] = str[j + 1];
//         }

//         str[len - 1] = tmp;
//     }
// }

// 方法二：先逆序左边字符串，再逆序右边字符串，最后逆序整体字符串
// void reverse(char* left, char* right) {
//     while (left < right) {
//         char tmp = *left;
//         *left = *right;
//         *right = tmp;
//         left++;
//         right--;
//     }
// }
// void string_left_rotate(char* str, int k) {
//     int len = strlen(str);
//     reverse(str, str + k - 1);
//     reverse(str + k, str + len - 1);
//     reverse(str, str + len - 1);
// }

// int main() {
//     char arr[] = "ABCDEF";
//     int k = 2;

//     string_left_rotate(arr, k);

//     printf("%s\n", arr);

//     return 0;
// }


// 练习3
// 判断一个字符串是不是另一个字符串旋转后的结果
// 例 "EFABCD" 是 "ABCDEF" 左旋转4次（或右旋转2次）后的结果

// 方法一：
// 列举str1的每一种旋转结果与str2进行比较
// int is_string_rotate(char* str1, char* str2) {
//     int len = strlen(str1);

//     for (int i = 0; i < len; i++) {
//         char tmp = str1[0];
//         for (int j = 0; j < len - 1; j++) {
//             str1[j] = str1[j + 1];
//         }
//         str1[len - 1] = tmp;

//         if (strcmp(str1, str2) == 0) {
//             return 1;
//         }
//     }

//     return 0;
// }

// 方法二：
// 对str1后面追加一个str1，然后判断str2是不是这个字符串的子串
int is_string_rotate(char* str1, char* str2) {
    // 首先要判断两个字符串的长度是否相等
    if (strlen(str1) != strlen(str2)) {
        return 0;
    }

    // 对str1进行扩展，后面加上len长度的str1
    int len = strlen(str1);
    strncat(str1, str1, len);

    // 判断str2是不是str1的子串，如果是返回对应字符地址，否则返回NULL
    char* ret = strstr(str1, str2);

    return ret != NULL;
}

int main() {
    char arr1[20] = "ABCDEF";
    char arr2[] = "DEFABC";

    if (is_string_rotate(arr1, arr2)) {
        printf("yes\n");
    }
    else {
        printf("no\n");
    }

    return 0;
}