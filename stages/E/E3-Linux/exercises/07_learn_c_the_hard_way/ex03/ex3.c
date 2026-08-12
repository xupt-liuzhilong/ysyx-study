#include <stdio.h>

int main(void) {
    int age = 20;
    int height = 171;
    double weight = 62.5;
    char *name = "Liuzhilong";

    printf("Name:%s\n", name);
    printf("Age:%d\n", age);
    printf("Height:%d cm\n", height);
    printf("Weight:%.1f kg\n", weight);


    printf("\n--- width demo ---\n");

    printf("|%d|\n", 123);
    printf("|%8d|\n", 123);
    printf("|%-8d|\n", 123);
    printf("|%08d|\n", 123);


    double pi = 3.1415926535;

    printf("\n--- precision demo ---\n");

    printf("%f\n", pi);
    printf("%.2f\n", pi);
    printf("%.4f\n", pi);
    printf("%10.2f\n", pi);


    int value = 255;

    printf("\n--- integer format demo ---\n");

    printf("decimal: %d\n", value);
    printf("hex:     %x\n", value);
    printf("HEX:     %X\n", value);
    printf("octal:   %o\n", value);


    printf("\n--- escape demo ---\n");

    printf("hello\nworld\n");
    printf("name\tage\theight\n");
    printf("\"YSYX\"\n");
    printf("C:\\Users\\test\n");


    unsigned int pc = 0x1234abcd;

    printf("PC = 0x%08x\n", pc);

    return 0;
}
