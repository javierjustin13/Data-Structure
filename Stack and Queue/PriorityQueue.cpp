#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    char name[20];
    char nim[5];
    float gpa;
    struct Data* next;
};
struct Data* head = NULL;
struct Data* tail= NULL;

struct Data* newNode(const char name[], const char nim[], float gpa) {
    struct Data* node = (struct Data*)malloc(sizeof(struct Data));
    strcpy(node->name, name);
    strcpy(node->nim, nim);
    node->gpa = gpa;
    node->next = NULL;
    return node;
}

void pushPriorityByGPA(const char name[], const char nim[], float gpa) {
    //Priority based on GPA descending
    struct Data* node = newNode(name, nim, gpa);
    if (head == NULL && tail == NULL) {
        head = tail = node;
    }
    else if (head->gpa < node->gpa) {
        node->next = head;
        head = node;
    }
    else if (tail->gpa >= node->gpa) {
        tail->next = node;
        tail = node;
    }
    else {
        struct Data* curr = head;
        while (curr->next != NULL && curr->next->gpa > node->gpa) {
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
    }
}

void pushPriorityByNIM(const char name[], const char nim[], float gpa) {
    //Priority based on NIM descending
    struct Data* node = newNode(name, nim, gpa);
    if (head == NULL) {
        head = tail = node;
    }
    else if (strcmp(head->nim, node->nim) < 0) {
        node->next = head;
        head = node;
    }
    else if (strcmp(tail->nim, node->nim) >= 0) {
        tail->next = node;
        tail = node;
    }
    else {
        struct Data* curr = head;
        while (curr->next != NULL && strcmp(curr->next->nim, node->nim) >= 0) {
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
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

void print() {
    struct Data* curr = head;
    printf("\n             Queue\n");
    printf("================================\n");
    printf("| Name      | NIM    | GPA     |\n");
    printf("================================\n");
    while (curr != NULL) {
        printf("| %-9s | %-6s | %-7.2f |\n", curr->name, curr->nim, curr->gpa);
        curr = curr->next;
    }
    printf("================================\n");
}

int main() {
    pushPriorityByNIM("Justin", "1313", 3.4);
    pushPriorityByNIM("Jason", "6969", 2.5);
    pushPriorityByNIM("Marvel", "2323", 3.5);
    pushPriorityByNIM("Delvin", "3434", 4.0);
    pushPriorityByNIM("Stephen", "2121", 3.7);
    pushPriorityByNIM("JCM", "2121", 3.2);
    pushPriorityByNIM("JDM", "2954", 3.53);
    pushPriorityByNIM("SWL", "5432", 3.21);
    print();
    pop();
    pop();
    print();
    return 0;
}