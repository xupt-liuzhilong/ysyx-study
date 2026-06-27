#include <stdio.h>

int sum(int n);
int factorial(int n);
int fib(int n);

int main() {
    int n = 5;

    printf("sum = %d\n", sum(n));

    printf("factorial = %d\n", factorial(n));

    printf("fib = %d\n", fib(n));

    return 0;
}

int sum(int n) {
    if (n == 0) {
        return 0;
    }

    return n + sum(n - 1);
}

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

int fib(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    return fib(n - 1) + fib(n - 2);
}