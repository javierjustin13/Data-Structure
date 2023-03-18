#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    char name[20];
    int age;
    struct Data* next;
}*head = NULL, *tail = NULL;

struct Data* newNode(const char name[], int age) {
    struct Data* node = (struct Data*)malloc(sizeof(struct Data));
    strcpy(node->name, name);
    node->age = age;
    node->next = NULL;
    return node;
}

void push(const char name[], int age) {
    struct Data* node = newNode(name, age);
    if (tail == NULL) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }
}

void pop() {
    if (head == NULL) {
        printf("Your queue is empty\n");
    }
    else {
        struct Data* del = head;
        head = head->next;
        free(del);
    }
}

void display() {
    struct Data* curr = head;
    printf("Queue: \n");
    while (curr != NULL) {
        printf("%s %d\n", curr->name, curr->age);
        curr = curr->next;
    }
}

int main() {
    push("Anjing", 18);
    push("Kucing", 10);
    push("Kancil", 21);
    display();
    pop();
    display();
    return 0;
}