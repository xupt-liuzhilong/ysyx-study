#include "contact.h"

void InitContact(Contact* pc) {
    // 将内存上的数据都初始化成0
    memset(pc->data, 0, sizeof(pc->data));

    // 刚开始通讯录没有联系人
    pc->sz = 0;
}


void AddContact(Contact* pc) {
    // 判断通讯录是否已满
    if (pc->sz == MAX) {
        printf("通讯录已满！\n");
    }

    // 输入信息
    printf("姓名：");
    scanf("%s", pc->data[pc->sz].name);
    printf("性别：");
    scanf("%s", pc->data[pc->sz].sex);
    printf("年龄：");
    scanf("%d",&(pc->data[pc->sz].age));
    printf("电话：");
    scanf("%s", pc->data[pc->sz].tele);
    printf("住址：");
    scanf("%s", pc->data[pc->sz].addr);
    pc->sz++;

    printf("添加成功!\n");
}


void PrintContact(const Contact* pc) {
    // 打印目录
    printf("%-20s\t%-5s\t%-5s\t%-20s\t%-20s\n", "姓名", "性别", "年龄", "电话", "住址");

    // 打印信息
    for (int i = 0; i < pc->sz; i++) {
        printf("%-20s\t%-5s\t%-5d\t%-20s\t%-20s\n", 
                pc->data[i].name, pc->data[i].sex, 
                pc->data[i].age, pc->data[i].tele, 
                pc->data[i].addr);
    }
}


// 按姓名查找，找到返回对应下标，未找到返回-1
static int FindName(const Contact* pc) {
    // 判断是通讯录是否为空
    if (pc->sz == 0) {
        printf("通讯录为空！\n");
        return -1;
    }

    // 输入并查找姓名
    char name[MAX_NAME] = {0};
    printf("请输入姓名：");
    scanf("%s", name);

    for (int i = 0; i < pc->sz; i++) {
        if (strcmp(pc->data[i].name, name) == 0) {
            return i;
        }
    }

    printf("该姓名不存在！\n");
    return -1;
}


void DelContact(Contact* pc) {
    // 查找要删除的姓名
    int pos = FindName(pc);

    // 判断姓名是否存在
    if (pos == -1) return;

    // 删除信息
    for (int i = pos; i < pc->sz - 1; i++) {
        pc->data[i] = pc->data[i + 1];
    }
    pc->sz--;

    printf("删除成功！\n");
}


void SearchContact(const Contact* pc) {
    // 查找要查找的姓名
    int pos = FindName(pc);

    // 判断姓名是否存在
    if (pos == -1) return;

    // 显示查找信息
    printf("%-20s\t%-5s\t%-5s\t%-20s\t%-20s\n", "姓名", "性别", "年龄", "电话", "住址");
    printf("%-20s\t%-5s\t%-5d\t%-20s\t%-20s\n", 
        pc->data[pos].name, pc->data[pos].sex, 
        pc->data[pos].age, pc->data[pos].tele, 
        pc->data[pos].addr);
}


void ModifyContact(Contact* pc) {
    // 查找要修改的姓名
    int pos = FindName(pc);

    // 判断姓名是否存在
    if (pos == -1) return;

    // 修改信息
    printf("姓名：");
    scanf("%s", pc->data[pos].name);
    printf("性别：");
    scanf("%s", pc->data[pos].sex);
    printf("年龄：");
    scanf("%d",&(pc->data[pos].age));
    printf("电话：");
    scanf("%s", pc->data[pos].tele);
    printf("住址：");
    scanf("%s", pc->data[pos].addr);
}


void SortContact(Contact* pc) {
    // 判断是通讯录是否为空
    if (pc->sz == 0) {
        printf("通讯录为空！\n");
        return;
    }

    // 排序
    for (int i = 0; i < pc->sz - 1; i++) {
        for (int j = 0; j < pc->sz - i - 1; j++) {
            if (strcmp(pc->data[j].name, pc->data[j + 1].name) > 0) {
                PeoInfo tmp = pc->data[j];
                pc->data[j] = pc->data[j + 1];
                pc->data[j + 1] = tmp;
            }
        }
    }

    printf("按照姓名从小到大排序成功！\n");
}