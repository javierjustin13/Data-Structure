#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int value;
    struct tnode* next;
    struct tnode* prev;
}*head = NULL, *tail = NULL;

struct tnode* newNode(int value) {
    struct tnode* node = (struct tnode*)malloc(sizeof(struct tnode));
    node->value = value;
    node->next = node->prev = NULL;
    return node;
}

void pushTail(int value) {
    struct tnode* node = newNode(value);
    if (head == NULL || tail == NULL) {
        head = tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void pushHead(int value) {
    struct tnode* node = newNode(value);
    if (head == NULL || tail == NULL) {
        head = tail = node;
    }
    else {
        head->prev = node;
        node->next = head;
        head = node;
    }
}

void pushMid(int value) {
    struct tnode* node = newNode(value);
    if (head == NULL || tail == NULL) {
        head = tail = node;
    }
    else if (head == tail) {
        head->next = node;
        node->prev = head;
        tail = node;
    }
    else {
        struct tnode* curr = head;
        while (curr->next != NULL && curr->next->value < value) {
            curr = curr->next;
        }
        if (curr->next == NULL) {
            pushTail(value);
        }
        else {
            node->next = curr->next;
            curr->next->prev = node;
            curr->next = node;
            node->prev = curr;
        }
    }
}

void popHead() {
    if (head == NULL || tail == NULL) {
        return;
    }
    else if (head == tail) {
        free(head);
        head = tail = NULL;
    }
    else {
        head = head->next;
        free(head->prev);
        head->prev = NULL;
    }
}

void popTail() {
    if (head == NULL || tail == NULL) {
        return;
    }
    else if (head == tail) {
        free(head);
        head = tail = NULL;
    }
    else {
        tail = tail->prev;
        free(tail->next);
        tail->next = NULL;
    }
}

void popByValue(int value) {
    if (head == NULL || tail == NULL) {
        return;
    }
    else if (head == tail && value == head->value) {
        free(head);
        head = tail = NULL;
    }
    else if (value == head->value) {
        popHead();
    }
    else if (value == tail->value) {
        popTail();
    }
    else {
        struct tnode* curr = head;
        while (curr->next != NULL && curr->next->value != value) {
            curr = curr->next;
        }
        if (curr->next == NULL) {
            printf("Value not found");
            return;
        }
        else {
            struct tnode* deleted = curr->next;
            curr->next = deleted->next;
            deleted->next->prev = curr;
            free(deleted);
        }
    }
}

void popAll() {
    while(head != NULL) {
        popHead();
    }
}

void printLinkedList() {
    struct tnode* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    pushTail(10);
    pushTail(15);
    pushTail(20);
    pushTail(25);
    pushTail(30);
    pushHead(5);
    printLinkedList();
    popByValue(13);
    return 0;
}