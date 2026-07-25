// 2026/7/25
// BC93 公务员面试
// https://www.nowcoder.com/share/jump/5656432511784965749890

// 方法一：数组法
// #include <stdio.h>

// int main() {
//     int n = 7;

//     int arr[7];
//     int score = 0;
//     int min = 0;
//     int max = 0;
//     int sum = 0;

//     int i = 0;
//     while (scanf("%d", &score) != EOF) {
//         arr[i] = score;
//         max = arr[max] > arr[i] ? max : i;
//         min = arr[min] < arr[i] ? min : i;
//         sum += arr[i];
//         i++;

//         if (i == n) {
//             double avg = (sum - arr[max] - arr[min]) * 1.0 / (n - 2);
//             printf("%.2lf\n", avg);
//             i = 0;
//             min = 0;
//             max = 0;
//             sum = 0;
//         }
//     }

//     return 0;
// }


// 方法二：直接求和
#include <stdio.h>

int main() {
    int score = 0;
    int sum = 0;
    int max = 0;
    int min = 100;

    int i = 0;
    while (scanf("%d", &score) != EOF) {
        max = max > score ? max : score;
        min = min < score ? min : score;
        sum += score;
        i++;

        if (i == 7) {
            printf("%.2lf\n", (sum - max - min) / 5.0);
            i = 0;
            sum = 0;
            min = 0;
            max = 100;
        }
    }

    return 0;
}
