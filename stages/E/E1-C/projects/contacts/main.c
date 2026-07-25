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