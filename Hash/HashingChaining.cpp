#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int size = 26;

struct Node {
    char string[101];
    int num;
    struct Node *next, *prev;
};

struct Row {
    struct Node*head, *tail;
}*table[size];

Row* createRow() {
    Row* row = (Row*)malloc(sizeof(Row));
    row->head = row->tail = NULL;
    return row;
}

Node* createNode(const char *string, int num) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->num = num;
    strcpy(node->string, string);
    node->next = node->prev = NULL;
    return node;
}

void view() {
    for (int i = 0; i < size; i++) {
        printf("%d | ", i);
        Row* row = table[i];
        if (row != NULL) {
            Node* curr = table[i]->head;
            while (curr != NULL) {
                printf("%s-%d-->", curr->string, curr->num);
                curr = curr->next;
            }
            printf("\n");
        }
        else {
            printf("-\n");
        }
    }
}

int hash(const char* string) {
    char c = string[0];
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    else if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return c % size;
}

void insertNode(const char* string, int num) {
    int key = hash(string);
    if (table[key] == NULL) {
        table[key] = createRow();
        table[key]->head = table[key]->tail = createNode(string, num);
        return;
    }
    // PUSH TAIL 
    Node* node = createNode(string, num);
    table[key]->tail->next = node;
    node->prev = table[key]->tail;
    table[key]->tail = node;
    // Node* node = createNode(string, num);
    
    // if (table[key]->head == NULL || table[key]->tail == NULL) {
    //     table[key]->head = table[key]->tail = node;
    // }
    // else if (strcmp(node->string, table[key]->head->string) < 0) {
    //     table[key]->head->prev = node;
    //     node->next = table[key]->head;
    //     table[key]->head = node;
    // }
    // else if (strcmp(node->string, table[key]->tail->string) > 0) {
    //     table[key]->tail->next = node;
    //     node->prev = table[key]->tail;
    //     table[key]->tail = node;
    // }
    // else {
    //     struct Node* curr = table[key]->head;
    //     while (curr->next != NULL && strcmp(node->string, curr->next->string) >= 0) {
    //         curr = curr->next;
    //     }
    //     node->next = curr->next;
    //     curr->next->prev = node;
    //     curr->next = node;
    //     node->prev = curr;
    // }
}

void deleteNode(const char* string) {
    int key = hash(string);
    if (table[key] == NULL) {
        printf("%s not found\n", string);
        return;
    }
    if (strcmp(table[key]->head->string, string) == 0) {
        if (table[key]->head == table[key]->tail) {
            free(table[key]->head);
            table[key]->head = table[key]->tail = NULL;
            free(table[key]);
            table[key] = NULL;
            return;
        }
        else {
            table[key]->head = table[key]->head->next;
            free(table[key]->head->prev);
            table[key]->head->prev == NULL;
            return;
        }
    }
    else if (strcmp(table[key]->tail->string, string) == 0) {
        if (table[key]->head == table[key]->tail) {
            free(table[key]->head);
            table[key]->head = table[key]->tail = NULL;
            free(table[key]);
            table[key] = NULL;
            return;
        }
        else {
            table[key]->tail = table[key]->tail->prev;
            free(table[key]->tail->next);
            table[key]->tail->next == NULL;
            return;
        }
    }
    else {
        Node* curr = table[key]->head;
        while (curr != NULL && strcmp(curr->string, string) != 0) {
            curr = curr->next;
        }
        if (curr == NULL) {
            printf("%s not found", string);
            return;
        }
        else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            free(curr);
            curr = NULL;
            return;
        }
    }

}

int main() {

    insertNode("Budi", 20);
    insertNode("Bade", 23);
    insertNode("Beri", 18);
    insertNode("Clara", 20);
    insertNode("Deni", 15);
    insertNode("Daki", 19);
    insertNode("Fuki", 16);
    insertNode("Baki", 30);
    view();
    deleteNode("Beri");
    deleteNode("Clara");
    view();
    return 0;
}