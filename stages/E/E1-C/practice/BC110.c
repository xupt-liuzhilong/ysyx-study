// 2026/7/25
// BC110 X形图案
// https://www.nowcoder.com/share/jump/5656432511784964077552

// 方法一：二维数组
// #include <stdio.h>
// #include <string.h>

// int main() {
//     int n;

//     while (scanf("%d", &n) != EOF) {
//         char arr[20][20];
//         memset(arr, ' ', sizeof(arr));

//         for (int i = 0; i < n; i++) {
//             arr[i][i] = '*';
//             arr[i][n - i - 1] = '*';
//         }

//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < n; j++) {
//                 printf("%c", arr[i][j]);
//             }
//             printf("\n");
//         }
//     }
    
//     return 0;
// }



// 方法二：直接打印
#include <stdio.h>

int main() {
    int n;

    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j || (i + j == n - 1)) {
                    printf("*");
                }
                else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
    
    return 0;
}