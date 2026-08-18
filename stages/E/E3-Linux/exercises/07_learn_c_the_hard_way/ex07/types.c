#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main() {
    printf("--- basic types ---\n");

    printf("sizeof(char) = %zu\n", sizeof(char));
    printf("sizeof(short) = %zu\n", sizeof(short));
    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(long) = %zu\n", sizeof(long));
    printf("sizeof(long long) = %zu\n", sizeof(long long));
    printf("sizeof(float) = %zu\n", sizeof(float));
    printf("sizeof(double) = %zu\n", sizeof(double));
    printf("sizeof(void *) = %zu\n", sizeof(void *));


    printf("\n--- fixed width types ---\n");

    printf("sizeof(uint8_t) = %zu\n", sizeof(uint8_t));
    printf("sizeof(uint16_t) = %zu\n", sizeof(uint16_t));
    printf("sizeof(uint32_t) = %zu\n", sizeof(uint32_t));
    printf("sizeof(uint64_t) = %zu\n", sizeof(uint64_t));


    printf("\n--- singed and unsigned ---\n");

    int32_t a = -1;
    uint32_t b = -1;

    printf("a = %d\n", a);
    printf("b = %u\n", b);
    printf("b = 0x%08x\n", b);


    printf("\n--- signed/unsigned comparison ---\n");

    int32_t s = -1;
    uint32_t u = 1;

    printf("s = %d\n", s);
    printf("u = %u\n", u);

    if (s < u) {
        printf("s < u is true\n");
    } else {
        printf("s < u is false\n");
    }

    if ((int64_t)s < (int64_t)u) {
        printf("after cast: s < u is true\n");
    } else {
        printf("after cast: s < u is false\n");
    }


    printf("\n--- unsigned overflow ---\n");

    uint32_t x = UINT32_MAX;

    printf("before: x = %u\n", x);
    printf("before: x = 0x%08x\n", x);

    x++;

    printf("after: x = %u\n", x);
    printf("after: x = 0x%08x\n", x);

    uint32_t y = 0;

    printf("\ny before = %u\n", y);

    y--;

    printf("y after = %u\n", y);
    printf("y hex = 0x%08x\n", y);

    return 0;
}
