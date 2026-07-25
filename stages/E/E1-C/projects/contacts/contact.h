#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 1000
#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 12
#define MAX_ADDR 20
#define DEFAULT_SZ 3
#define INC_SZ 2

typedef struct PeoInfo {
    char name[MAX_NAME];
    char sex[MAX_SEX];
    int age;
    char tele[MAX_TELE];
    char addr[MAX_ADDR];
} PeoInfo;

// 静态版
// typedef struct Contact {
//     PeoInfo data[MAX];
//     int sz;
// } Contact;

// 动态版
typedef struct Contact {
    PeoInfo* data;
    int sz;
    int capacity;
} Contact;

enum Option {
    EXIT,
    ADD,
    DEL,
    SEARCH,
    MODIFY,
    SORT,
    PRINT
};

// 初始化通讯录
void InitContact(Contact* pc);

// 添加联系人信息
void AddContact(Contact* pc);

// 打印联系人信息
void PrintContact(const Contact* pc);

// 删除联系人信息
void DelContact(Contact* pc);

// 查找联系人信息
void SearchContact(const Contact* pc);

// 修改联系人信息
void ModifyContact(Contact* pc);

// 排序联系人信息
void SortContact(Contact* pc);

// 销毁通讯录
void DestoryContact(Contact* pc);
