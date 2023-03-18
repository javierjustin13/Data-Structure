#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    int value;
    char name[100];
    struct Node* next;
    struct Node* prev;
};

struct Node *createNode(const char name[100], int value) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(node->name, name);
    node->value = value;
    node->next = node->prev = NULL;
    return node;
}

void pushHead(struct Node** head, struct Node** tail, struct Node *node) {
    if (*head == NULL | *tail == NULL) {
        *head = *tail = node;
    }
    else {
        (*head)->prev = node;
        node->next = *head;
        *head = node;
    }
}

void pushTail(struct Node** head, struct Node** tail, struct Node* node) {
    if (*head == NULL | *tail == NULL) {
        *head = *tail = node;
    }
    else {
        (*tail)->next = node;
        node->prev = *tail;
        *tail = node;
    }
}

void pushMid(struct Node** head, struct Node **tail, struct Node* node) {
    if (*head == NULL || *tail == NULL) {
        *head = *tail = node;
    }
    else if (strcmp(node->name, (*head)->name) < 0) {
        pushHead(head, tail, node);
    }
    else if (strcmp(node->name, (*tail)->name) > 0) {
        pushTail(head, tail, node);
    }
    else {
        struct Node* curr = *head;
        while (strcmp(node->name, curr->next->name) >= 0) {
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next->prev = node;
        curr->next = node;
        node->prev = curr;
    }
}

void popHead(struct Node** head, struct Node** tail) {
    if (*head == NULL) {
        printf("Your linked list is empty\n");
    }
    else if (*head == *tail) {
        free(head);
        *head = *tail = NULL;
    }
    else {
        *head = (*head)->next;
        free((*head)->prev);
        (*head)->prev = NULL;
    }
}

void popTail(struct Node** head, struct Node** tail) {
    if (*tail == NULL) {
        printf("Your linked list is empty\n");
    }
    else if (*head == *tail) {
        free(tail);
        *head = *tail = NULL;
    }
    else {
        *tail = (*tail)->prev;
        free((*tail)->next);
        (*tail)->next = NULL;
    }
}

void popByName(const char name[], struct Node** head, struct Node** tail) {
    if (*head == NULL || *tail == NULL) {
        printf("Your linked list is empty\n");
        return;
    }
    else if (strcmp(name, (*head)->name) == 0) {
        popHead(head, tail);
    }
    else if (strcmp(name, (*tail)->name) == 0) {
        popTail(head, tail);
    }
    else {
        struct Node* curr = *head;
        while (strcmp(name, curr->name) != 0) {
            if (curr == NULL) {
                printf("The name you want to delete is not in the linked list\n");
                return;
            }
            curr = curr->next;
        }
        // while (curr->next != NULL && strcmp(name, curr->name) != 0) {
        //     curr = curr->next;
        // }
        // if (curr->next == NULL) {
        //     printf("The name you want to delete is not in the linked list\n");
        //     return;
        // }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
    }

}

void popAll(struct Node** head, struct Node** tail) {
    if (*head == NULL || *tail == NULL) {
        printf("Your linked list is empty\n");
        return;
    }
    else {
        while (*head != NULL) {
            popHead(head, tail);
        }
    }
}

void viewLinkedList(struct Node* head) {
    struct Node* curr = head;
    printf("Your Linked List:\n");
    while (curr != NULL) {
        printf("%-10s %-7d\n", curr->name, curr->value);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL, * tail = NULL;
    pushMid(&head, &tail, createNode("Justin", 13));
    pushMid(&head, &tail, createNode("Stephen", 69));
    pushMid(&head, &tail, createNode("Yoga", 26));
    pushMid(&head, &tail, createNode("Ziven", 6));
    pushMid(&head, &tail, createNode("Shamgar", 29));
    pushMid(&head, &tail, createNode("Jennifer", 14));
    pushMid(&head, &tail, createNode("Eva", 26));
    viewLinkedList(head);
    popHead(&head, &tail);
    viewLinkedList(head);
    popTail(&head, &tail);
    viewLinkedList(head);
    popByName("Daniel", &head, &tail);
    popAll(&head, &tail);
    viewLinkedList(head);
    return 0;
}