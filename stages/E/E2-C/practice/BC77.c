// 2026/7/25
// BC77 有序序列插入一个整数
// https://www.nowcoder.com/share/jump/5656432511784969944110


#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[51] = {0};
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int x = 0;
    scanf("%d", &x);

    int i = 0;
    for (i = 0; i < n; i++) {
        if (x <= arr[i]) {
            for (int j = n; j > i; j--) {
                arr[j] = arr[j - 1];
            }

            arr[i] = x;
            break;
        }
    }
    if (i == n) {
        arr[i] = x;
    }

    for (int i = 0; i <= n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}