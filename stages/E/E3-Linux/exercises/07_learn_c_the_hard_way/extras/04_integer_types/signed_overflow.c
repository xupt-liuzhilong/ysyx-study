#include <stdio.h>
#include <stdint.h>

int main() {
    int32_t z = INT32_MAX;

    printf("before = %d\n", z);

    z++;

    printf("after = %d\n", z);

    return 0;
}
