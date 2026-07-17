#include <stdio.h>

// 一级指针传参
// void test(int* a) {}
// int main() {
//     int a = 10;
//     int* pa = &a;

//     test(&a);
//     test(pa);

//     return 0;
// }


// 二级指针传参
// void test(char** c) {}
// void test2(int** a) {}
// int main() {
//     char c = 'w';
//     char* pc = &c;
//     char** ppc = &pc;
//     test(&pc);
//     test(ppc);

//     int arr[10] = {0};
//     int (*pa)[10] = &arr;
//     test2(pa);

//     return 0;
// }


// 函数指针 - 指向函数的指针
// int Add(int a, int b) {
//     return a + b;
// }
// int main() {
//     int (*pf)(int, int) = &Add;
//     // int (*pf)(int, int) = Add;   // Add和&Add都存放的是函数的地址

//     int a = (*pf)(3, 4);
//     int b = pf(3, 4);
//     int c = Add(3, 4);

//     printf("%d, %d, %d\n", a, b, c);

//     return 0;
// }


// 函数指针数组 - 存放函数指针的数组
// int Add(int a, int b) {
//     return a + b;
// }
// int Sub(int a, int b) {
//     return a - b;
// }
// int main() {
//     int (*pf1)(int, int) = &Add;
//     int (*pf2)(int, int) = &Sub;

//     int (*pfarr[2])(int, int) = {Add, Sub};

//     int ret = pfarr[0](1, 2);
//     printf("%d", ret);

//     return 0;
// }

// 简易的计算器实现
int Add(int a, int b) {
    return a + b;
}
int Sub(int a, int b) {
    return a - b;
}
int Mul(int a, int b) {
    return a * b;
}
int Div(int a, int b) {
    return a / b;
}
void menu() {
    printf("*************************\n");
    printf("***** 1.Add   2.Sub *****\n");
    printf("***** 3.Mul   4.Div *****\n");
    printf("*****     0.exit    *****\n");
    printf("*************************\n");
}
// int main() {
//     int input = 0;
//     do {
//         menu();
//         printf("请选择：");
//         scanf("%d", &input);
//         int x = 0;
//         int y = 0;
//         int ret = 0;
//         switch (input) {
//             case 1:
//                 printf("请输入两个操作数：");
//                 scanf("%d %d", &x, &y);
//                 ret = Add(x, y);
//                 printf("ret = %d\n", ret);
//                 break;
//             case 2:
//                 printf("请输入两个操作数：");
//                 scanf("%d %d", &x, &y);
//                 ret = Sub(x, y);
//                 printf("ret = %d\n", ret);
//                 break;
//             case 3:
//                 printf("请输入两个操作数：");
//                 scanf("%d %d", &x, &y);
//                 ret = Mul(x, y);
//                 printf("ret = %d\n", ret);
//                 break;
//             case 4:
//                 printf("请输入两个操作数：");
//                 scanf("%d %d", &x, &y);
//                 ret = Div(x, y);
//                 printf("ret = %d\n", ret);
//                 break;
//             case 0:
//                 printf("程序结束\n");
//                 break;
//             default:
//                 printf("输入错误，请重新选择\n");
//                 break;
//         }
//     } while (input != 0);

//     return 0;
// }

// 函数指针数组做计算器
// int main() {
//     int input = 0;
//     int (*Alu[5])(int, int) = {0, Add, Sub, Mul, Div};
//     do {
//         menu();

//         printf("请选择：");
//         scanf("%d", &input);

//         if (input > 0 && input <= 4) {
//             int x, y;
//             printf("请输入两个操作数：");
//             scanf("%d %d", &x, &y);
//             int ret = Alu[input](x, y);
//             printf("ret = %d\n", ret);
//         }
//         else if (input == 0) {
//             printf("退出程序\n");
//         }
//         else {
//             printf("输入错误，请重新选择\n");
//         }
//     } while (input != 0);

//     return 0;
// }


// 指向函数指针数组的指针
// int main() {
//     int (*pfarr[10])(int, int);
//     int (*(*pa)[10])(int, int) = &pfarr;
//     return 0;
// }


// 回调函数 - 在另一个函数通过函数指针的方式调用函数
// int A(int a) {
//     return a;
// }
// void B(int (*pf)(int)) {
//     int b = pf(1);
//     printf("%d\n", b);
// }
// int main(void) {
//     B(A);
//     return 0;
// }

// 回调函数做计算器
// int Alu(int (*pf)(int, int)) {
//     int x = 0;
//     int y = 0;
//     printf("请输入两个操作数：");
//     scanf("%d %d", &x, &y);
//     return pf(x, y);
// }
// int main() {
//     int input = 0;
//     do {
//         menu();
//         printf("请选择：");
//         scanf("%d", &input);
//         int ret = 0;
//         switch (input) {
//             case 1:
//                 ret = Alu(Add);
//                 printf("ret = %d\n", ret);
//                 break;
//             case 2:
//                 ret = Alu(Sub);
//                 printf("ret = %d\n", ret);
//                 break;
//             case 3:
//                 ret = Alu(Mul);
//                 break;
//             case 4:
//                 ret = Alu(Div);
//                 printf("ret = %d\n", ret);
//                 break;
//             case 0:
//                 printf("程序结束\n");
//                 break;
//             default:
//                 printf("输入错误，请重新选择\n");
//                 break;
//         }
//     } while (input != 0);

//     return 0;
// }
