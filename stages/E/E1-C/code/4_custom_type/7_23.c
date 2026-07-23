#include <stdio.h>

// 自定义类型 - 结构体

// 1. 基本结构
// struct Student {
//     char name[20];
//     int age;
//     double score;
// };

// int main() {
//     struct Student s = {"zhangsan", 20, 98.2};
//     printf("name:%s\nage:%d\nscore%lf\n", s.name, s.age, s.score);
//     return 0;
// }


// 2. 结构体重命名
// typedef struct Student {
//     char name[20];
//     int age;
//     double score;
// } Stu;

// int main() {
//     Stu s = {"zhangsan", 20, 98.2};
//     printf("name:%s\nage:%d\nscore%lf\n", s.name, s.age, s.score);
//     return 0;
// }


// 3. 结构体自引用
// 方便后续数据结构和链表的学习
// typedef struct Node {
//     int data;
//     struct Node* next;
// } Node;


// 4. 结构体内存对齐规则：
// - 第一个成员放在偏移量为 0 的位置；
// - 每个成员要放在自己对齐数的整数倍位置；
// - 对齐数通常取“成员自身大小”和“编译器默认对齐数”中的较小值；
// - 整个结构体的大小，必须最大对齐数的整数倍。
// 很多编译器环境下，默认对齐数通常是 8。

// 如果嵌套了结构体的情况，嵌套的结构体对齐到自己的最大对齐数的整数倍处，
// 结构体的整体大小就是所有最大对齐数（含嵌套结构体的对齐数）的整数倍。

// //练习1
// struct S1
// {
//  char c1;
//  int i;
//  char c2;
// };
// //练习2
// struct S2
// {
//  char c1;
//  char c2;
//  int i;
// };
// //练习3
// struct S3
// {
//  double d;
//  char c;
//  int i;
// };
// //练习4-结构体嵌套问题
// struct S4
// {
//  char c1;
//  struct S3 s3;
//  double d;
// };
// int main() {
//     printf("%d\n", sizeof(struct S1));  // 12
//     printf("%d\n", sizeof(struct S2));  // 8
//     printf("%d\n", sizeof(struct S3));  // 16
//     printf("%d\n", sizeof(struct S4));  // 32
//     return 0;
// }

// 总体来说：结构体的内存对齐是拿空间来换取时间的做法。
// 在设计结构体的时候，让占用空间小的成员尽量集中在一起。


// 5. 结构体传参
// 可以传结构体类型也可以传结构体指针
// 建议传结构体指针，好处是可以自由确定是否修改内容，可以节省创建临时变量的空间
// struct S {
//     int a;
//     char c;
//     double d;
// };
// void fun1(struct S* s) {
//     printf("%d, %c, %.2lf\n", s->a, s->c, s->d);
// }
// void fun2(struct S s) {
//     printf("%d, %c, %.2lf\n", s.a, s.c, s.d);
// }
// int main() {
//     struct S s = {2, 'd', 3.14};
//     fun1(&s);
//     fun2(s);
//     return 0;
// }


// 6. 位段 - 结构体实现位段
// - 位段的类型必须是int、unsigned int、signed int 或者 char
// - 位段的成员后面有一个冒号和数字（代表所占 bit 大小）
// - 跟结构相比，位段可以达到同样的效果，但是可以很好的节省空间，但是有跨平台的问题存在
// struct S {
//     char c1 : 3;
//     char c2 : 4;
//     char c3 : 5;
//     char c4 : 4;
// } s;

// int main() {
//     s.c1 = 10;
//     s.c2 = 12;
//     s.c3 = 3;
//     s.c4 = 4;
    
//     printf("%d\n", sizeof(s)); // 3
//     // 调试可知内存分配给 s 的空间是 3 个字节
//     // 且内容分别是 62 03 04 （十六进制）
//     // -由此可知VS环境下，位段的分配顺序是从右往左（从低位到高位）分配的
//     // -当一个结构包含两个位段且内存空间不够时，或开辟另一段空间来存储
//     // 但是这两个结果在其他环境下是不确定的

//     return 0;
// }


// 7. 枚举
// 枚举的优点：
// - 增加代码的可读性和可维护性
// - 和#define定义的标识符比较枚举有类型检查，更加严谨
// - 防止了命名污染（封装）
// - 便于调试
// - 使用方便，一次可以定义多个常量

// enum Color {
//     RED = 3,
//     GREEN = 7,
//     BLUE
// };

// int main() {
//     printf("%d\n", RED);
//     printf("%d\n", GREEN);
//     printf("%d\n", BLUE);
//     return 0;
// }
