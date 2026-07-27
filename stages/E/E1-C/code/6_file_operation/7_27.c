#include <stdio.h>

// 文件操作

// 1. 文件打开和关闭
// int main() {
//     // 打开文件
//     FILE* pf = fopen("test.dat", "r");
//     if (pf == NULL) {
//         perror("fopen");
//         return 1;
//     }

//     // 关闭文件
//     fclose(pf);
//     pf = NULL;

//     return 0;
// }


// 2. fputc() 写一个字符
// int main() {
//     FILE* pf = fopen("test.dat", "r");
//     if (pf == NULL) {
//         perror("fopen");
//         return 1;
//     }

//     fputc('h', pf);
//     fputc('e', pf);
//     fputc('l', pf);
//     fputc('l', pf);
//     fputc('o', pf);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }


// 3. fgetc() 读一个字符
// int main() {
//     FILE* pf = fopen("test.dat", "r");
//     if (pf == NULL) {
//         perror("fopen");
//         return 1;
//     }

//     int ret = fgetc(pf);
//     printf("%c\n", ret);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }


// 4. fputs() 写一个字符串
// int main() {
//     FILE* pf = fopen("test.dat", "r");
//     if (pf == NULL) {
//         perror("fopen");
//         return 1;
//     }

//     fputs("hello world!\n", pf);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }


// 5. fgets() 读一个字符串
// int main() {
//     FILE* pf = fopen("test.dat", "r");
//     if (pf == NULL) {
//         perror("fopen");
//         return 1;
//     }

//     char arr[10];
//     fgets(arr, 6, pf);
//     printf("%s\n", arr);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }


// 6. fprintf() 格式化写入数据
// struct S {
//     char name[10];
//     int age;
// };
// int main() {
//     FILE* pf = fopen("test.dat", "w");
//     if (pf == NULL) {
//         perror("fopen");
//         return 1;
//     }

//     struct S s = {"zhangsan", 20};
//     fprintf(pf, "%s %d\n", s.name, s.age);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }


// 7. fscanf() 格式化读取数据
// struct S {
//     char name[10];
//     int age;
// };
// int main() {
//     FILE* pf = fopen("test.dat", "r");
//     if (pf == NULL) {
//         perror("fopen");
//         return 1;
//     }

//     struct S s = {0};
//     fscanf(pf, "%s %d", (char*)&(s.name), &(s.age));
//     printf("%s %d\n", s.name, s.age);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }


// 8. fwrite() 二进制形式写数据
// struct S {
//     char name[10];
//     int age;
// };
// int main() {
//     FILE* pf = fopen("test.dat", "w");
//     if (pf == NULL) {
//         perror("fopen");
//         return 1;
//     }

//     struct S s = {"zhangsan", 20};
//     fwrite(&s, sizeof(struct S), 1, pf);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }


// 9. fread() 二进制形式读数据
struct S {
    char name[10];
    int age;
};
int main() {
    FILE* pf = fopen("test.dat", "r");
    if (pf == NULL) {
        perror("fopen");
        return 1;
    }

    struct S s = {0};
    fread(&s, sizeof(struct S), 1, pf);
    printf("%s %d\n", s.name, s.age);

    fclose(pf);
    pf = NULL;

    return 0;
}