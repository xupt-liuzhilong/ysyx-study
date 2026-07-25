// 2026/7/25
// BC74 获得月份天数
// https://www.nowcoder.com/share/jump/5656432511784969872023

#include <stdio.h>

int main() {
    int MonthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int year, month;
    while (scanf("%d %d", &year, &month) != EOF) {
        int day = MonthDays[month];

        if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month == 2) {
            day++;
        }

        printf("%d\n", day);
    }

    return 0;
}