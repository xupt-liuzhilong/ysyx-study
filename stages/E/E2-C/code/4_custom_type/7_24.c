#include <stdio.h>

// 联合体/共用体
// c 和 i 共用一段内存空间
union Un {
    char c;
    int i;
};

int main() {
    union Un u;
    // 联合体的大小是最大的成员大小与对齐数的整数倍的最大值
    printf("%d\n", sizeof(u)); // 4

    u.c = 1;
    printf("%x\n", u.c);
    printf("%x\n", u.i);

    u.i = 0x11223344;
    printf("%x\n", u.c);
    printf("%x\n", u.i);    

    return 0;
}


// 实现一个通讯录
