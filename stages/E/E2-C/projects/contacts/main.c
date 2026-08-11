// 模拟实现一个通讯录

// 第一版：完成通讯录的一些基本操作
// 第二版：使用动态内存分配控制通讯录大小
// 第三版：通过文件加载和保存通讯录数据

#include "contact.h"

void menu() {
    printf("***************************\n");
    printf("*** 1.add      2.del    ***\n");
    printf("*** 3.search   4.modify ***\n");
    printf("*** 5.sort     6.print  ***\n");
    printf("***        0.exit       ***\n");
    printf("***************************\n");
}

int main() {
    int input;

    Contact con;
    InitContact(&con);
    LoadContact(&con);
    
    do {
        system("cls");
        menu();

        printf("请选择:>");
        scanf("%d", &input);

        switch (input) {
        case ADD:
            AddContact(&con);
            break;
        case DEL:
            DelContact(&con);
            break;
        case SEARCH:
            SearchContact(&con);
            break;
        case MODIFY:
            ModifyContact(&con);
            break;
        case SORT:
            SortContact(&con);
            break;
        case PRINT:
            PrintContact(&con);
            break;
        case EXIT:
            SaveContact(&con);
            DestoryContact(&con);
            printf("退出程序!\n");
            break;
        default:
            printf("请重新选择!\n");
            break;
        }

        printf("按回车继续...");
        getchar();
        getchar();
        system("cls");
    } while (input);

    return 0;
}