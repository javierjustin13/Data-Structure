#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 26

struct Data {
    char name[100];
    int value;
    Data* next;
    Data* prev;
};

struct Table {
    Data *head,*tail;
}*table[SIZE] = {NULL};

struct Data *createNode(const char name[], int value) {
    struct Data *newNode = (struct Data*)malloc(sizeof(struct Data));
    strcpy(newNode->name, name);
    newNode->value = value;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void initializeTable() {
    for(int i = 0; i < SIZE; i++) {
        table[i] = (Table*)malloc(sizeof(Table));
        table[i]->head = table[i]->tail = NULL;
    }
    return;
}

void view() {
    for (int i = 0; i < SIZE; i++) {
        struct Data* curr = table[i]->head;
        printf("%d ", i);
        while (curr) {
            printf("%s %d->", curr->name, curr->value);
            curr = curr->next;
        }
        printf("\n");
    }
    return;
}

int hash(const char name[]) {
    char firstChar = name[0];
    if(firstChar >= 'a' && firstChar <= 'z') {
        return (firstChar - 'a') % SIZE;
    }
    else if (firstChar >= 'A' && firstChar <= 'Z') {
        return (firstChar - 'A') % SIZE;
    }
    else {
        return firstChar % SIZE;
    }
}

void pushHead(int key, struct Data* newNode) {
    if (table[key]->head == NULL) {
        table[key]->head = table[key]->tail = newNode;
    }
    else {
        newNode->next = table[key]->head;
        table[key]->head->prev = newNode;
        table[key]->head = newNode;
    }
    return;
}

void pushTail(int key, struct Data* newNode) {
    if (table[key]->head == NULL) {
        table[key]->head = table[key]->tail = newNode;
    }
    else {
        newNode->prev = table[key]->tail;
        table[key]->tail->next = newNode;
        table[key]->tail = newNode;
    }
    return;
}

void pushSort(int key, struct Data* newNode) {
    struct Data* curr = table[key]->head;
    while (curr != NULL && strcmp(newNode->name, curr->next->name) >= 0) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    newNode->prev = curr;
    curr->next->prev = newNode;
    curr->next = newNode;
    return;
}

void insert(const char name[], int value) {
    int key = hash(name);
    struct Data* newNode = createNode(name, value);
    if (table[key]->head == NULL || strcmp(name, table[key]->head->name) < 0) {
        pushHead(key, newNode);
    }
    else if (strcmp(name, table[key]->tail->name) >= 0) {
        pushTail(key, newNode);
    }
    else {
        pushSort(key, newNode);
    }
}

void popHead(int key) {
    if (table[key]->head == NULL) return;
    else if (table[key]->head == table[key]->tail) {
        free(table[key]->head);
        table[key]->head = table[key]->tail = NULL;
    }
    else {
        struct Data* temp = table[key]->head;
        table[key]->head = table[key]->head->next;
        free(temp);
        table[key]->head->prev = NULL;
    }
    return;
}

void popTail(int key) {
    if (table[key]->head == NULL) return;
    else if (table[key]->head == table[key]->tail) {
        free(table[key]->head);
        table[key]->head = table[key]->tail = NULL;
    }
    else {
        struct Data* temp = table[key]->tail;
        table[key]->tail = table[key]->tail->prev;
        free(temp);
        table[key]->tail->next = NULL;
    }
    return;
}

void popMid(int key, const char name[]) {
    struct Data* curr = table[key]->head;
    while (curr != NULL && strcmp(name, curr->name) != 0) {
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("The data you want to delete isn't there\n");
        return;
    }
    else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
    }
    return;
}


void deleteByName(const char name[]) {
    int key = hash(name);
    if (table[key] == NULL) {
        printf("The data you want to delete isn't there\n");
        return;
    }
    else if (strcmp(name, table[key]->head->name) == 0) {
        popHead(key);
    }
    else if (strcmp(name, table[key]->tail->name) == 0) {
        popTail(key);
    }
    else {
        popMid(key, name);
    }
    return;
}

int main() {
    initializeTable();
    insert("Ayam Bakar", 12);
    insert("Anjing Goreng", 10);
    insert("Anak Kambing", 9);
    insert("Sate Padang", 1);
    insert("Sate Ayam", 14);
    insert("Sop Jagung", 13);
    insert("Suka Kamu", 69);
    deleteByName("Sate Ayam");
    deleteByName("Sop Jagung");
    deleteByName("Anjing");
    view();
    return 0;
}