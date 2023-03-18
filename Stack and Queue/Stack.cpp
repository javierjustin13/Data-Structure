#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    char name[20];
    int age;
    struct Data* next;
}*head = NULL;

struct Data* newNode(const char name[], int age){
    struct Data *node = (struct Data*)malloc(sizeof(struct Data));
    strcpy(node->name, name);
    node->age = age;
    node->next = NULL;
    return node;
}

void push(const char name[], int age){
    struct Data* node = newNode(name, age);
    if(head == NULL){
        head = node;
    }
    else{
        node->next = head;
        head = node;
    }
}

void pop(){
    if(head == NULL){
        printf("Your stack is empty\n");
    }
    else{
        struct Data *del = head;
        head = head->next;
        free(del);
    }
}

void display(){
    struct Data *curr = head;
    printf("Stack: \n");
    while(curr != NULL){
        printf("%s %d\n", curr->name, curr->age);
        curr = curr->next;
    }
}

int main(){
    push("Anjing", 18);
    push("Kucing", 10);
    push("Kancil", 21);
    display();
    pop();
    display();
    return 0;
}