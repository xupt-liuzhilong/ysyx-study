#include <stdio.h>

int main() {
//    // 算术运算和逻辑运算
//    int a = 10;
//    int b = 3;
//
//    printf("a + b = %d\n", a + b);
//    printf("a - b = %d\n", a - b);
//    printf("a * b = %d\n", a * b);
//    printf("a / b = %d\n", a / b);
//    printf("a %% b = %d\n", a % b);
//
//    printf("a > b  = %d\n", a > b);
//    printf("a == b = %d\n", a == b);
//    printf("a != b = %d\n", a != b);
//
//    printf("a && b = %d\n", a && b);
//    printf("a || b = %d\n", a || b);
//    printf("!a     = %d\n", !a);
//
//
//    // 位运算
//    unsigned int x = 0x0f;
//    unsigned int y = 0x33;
//
//    printf("\n--- bitwise ---\n");
//    printf("x = 0x%08x\n", x);
//    printf("y = 0x%08x\n", y);
//
//    printf("x & y = 0x%08x\n", x & y);
//    printf("x | y = 0x%08x\n", x | y);
//    printf("x ^ y = 0x%08x\n", x ^ y);
//    printf("~x = 0x%08x\n", ~x);
//
//    printf("x << 1 = 0x%08x\n", x << 1);
//    printf("x >> 1 = 0x%08x\n", x >> 1);
//
//
//    // 验证机器大小端
//    unsigned int inst = 0x12345678;
//    unsigned char *p = (unsigned char*)&inst;
//
//    printf("\ninst = 0x%08x\n", inst);
//    printf("byte 0 = 0x%02x\n", p[0]);
//
//    printf("low byte = 0x%02x\n", inst & 0xff);


    // 取字段
    unsigned int inst = 0x12345678;

    unsigned int opcode = inst & 0x7f;
    unsigned int rd = (inst >> 7) & 0x1f;
    unsigned int funct3 = (inst >> 12) & 0x07;
    unsigned int rs1 = (inst >> 15) & 0x1f;
    unsigned int rs2 = (inst >> 20) & 0x1f;
    unsigned int funct7 = (inst >> 25) & 0x7f;

    printf("\n--- instruction fields ---\n");
    printf("inst = 0x%08x\n", inst);
    printf("opcode = 0x%02x\n", opcode);
    printf("rd = 0x%02x\n", rd);
    printf("funct3 = 0x%02x\n", funct3);
    printf("rs1 = 0x%02x\n", rs1);
    printf("rs2 = 0x%02x\n", rs2);
    printf("funct7 = 0x%02x\n", funct7);


    printf("\n--- byte extract ---\n");
    printf("byte0 = 0x%02x\n", (inst >> 0) & 0xff);
    printf("byte1 = 0x%02x\n", (inst >> 8) & 0xff);
    printf("byte2 = 0x%02x\n", (inst >> 16) & 0xff);
    printf("byte3 = 0x%02x\n", (inst >> 24) & 0xff);

    return 0;
}
