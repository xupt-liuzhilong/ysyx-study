#include <stdio.h>
#include <stdlib.h>

// 单链表节点结构
struct Node {
    int data;           // 当前数据
    struct Node *next;  // 下一个节点地址
};

// 创建一个新节点并初始化
struct Node *create_node(int data);
// 在链表结尾插入一个新节点（尾插法）
void push_back(struct Node **head, int data);
// 打印链表内容
void print_list(struct Node *head);
// 删除链表中第一个数据为 value 的节点
void delete_value(struct Node **head, int value);
// 释放整个链表
void free_list(struct Node *head);
// 统计链表节点个数
int length(struct Node *head);
// 查找链表中是否含有值为 value 的节点
int find_value(struct Node *head, int value);

int main() {
    struct Node *head = NULL;

    push_back(&head, 10);
    push_back(&head, 20);
    push_back(&head, 30);
    push_back(&head, 40);

    print_list(head);
    printf("len = %d\n", length(head));

    delete_value(&head, 10);
    print_list(head);

    delete_value(&head, 30);
    print_list(head);

    delete_value(&head, 40);
    print_list(head);

    printf("is_find = %d\n", find_value(head, 40));

    free_list(head);
    head = NULL;

    return 0;
}

struct Node *create_node(int data) {
    // malloc 在堆区申请一块 Node 大小的空间
    struct Node *node = malloc(sizeof(struct Node));

    // malloc 申请空间失败判断
    if (node == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    // 初始化新节点
    node->data = data;
    node->next = NULL;  // 新节点刚创建时，还没有连接到其他节点

    return node;
}

// head 是二级指针，因为空链表插入第一个节点时，需要修改外部的 head
void push_back(struct Node **head, int data) {
    struct Node *new_node = create_node(data);

    // 如果链表为空，新节点就是第一个节点，需要用 head 指向它
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    // cur 用来遍历链表，从头节点开始
    struct Node *cur = *head;

    // 找到最后一个节点
    while (cur->next != NULL) {
        cur = cur->next;
    }

    // 把最后一个节点的 next 指向新节点
    cur->next = new_node;
}

void print_list(struct Node *head) {
    struct Node *cur = head;

    while (cur != NULL) {
        printf("%d", cur->data);

        if (cur->next != NULL) {
            printf(" -> ");
        }

        cur = cur->next;
    }

    printf(" -> NULL\n");
}

// head 是二级指针，因为删除节点时可能要修改外部的 head
void delete_value(struct Node **head, int value) {
    // 空链表不用删除
    if (*head == NULL) {
        return;
    }

    struct Node *cur = *head;   // 当前节点
    struct Node *prev = NULL;   // 当前节点的上一个节点

    // 向后查找值为 value 的节点
    while (cur != NULL && cur->data != value) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        return; // 没有找到直接返回
    }

    if (prev == NULL) {         // 说明要删的是头节点
        *head = cur->next;      // 头指针要指向头节点的下一个节点
    } else {                    // 删除普通节点
        prev->next = cur->next; // 让前一个节点直接跳过当前节点，直接指向下一个节点
    }

    free(cur);
}

void free_list(struct Node *head) {
    struct Node *cur = head;

    while (cur != NULL) {
        // 必须保存下一个节点的地址
        // 因为 free 后，cur 指向的内存就不能访问了
        struct Node *next = cur->next;
        free(cur);
        cur = next;
    }
}


int length(struct Node *head) {
    int count = 0;
    struct Node *cur = head;

    while (cur != NULL) {
        count++;
        cur = cur->next;
    }

    return count;
}

int find_value(struct Node *head, int value) {
    struct Node *cur = head;

    while (cur != NULL) {
        if (cur->data == value) {
            return 1;
        }
        cur = cur->next;
    }

    return 0;
}
