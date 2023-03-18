#include <stdio.h>
#include <stdlib.h>

struct Data{
    int value;
    struct Data* next;
}*head = NULL, * tail = NULL;

// struct Data* head = NULL; BENTUK LAIN
// struct Data* tail = NULL; BENTUK LAIN

struct Data* newNode(int value) {
    struct Data* node = (struct Data*)malloc(sizeof(struct Data));
    node->value = value;
    // (*node).value = value; BENTUK LAIN 
    node->next = NULL;
    return node;
}

void pushHead(int value) {
    struct Data* node = newNode(value);
    if (head == NULL) {
        head = tail = node;
    }
    // if (!head) {
    //     head = tail = node;
    // }
    else {
        node->next = head;
        head = node;
    }
}

void pushTail(int value) {
    struct Data* node = newNode(value);
    if (head == NULL) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }
}

void pushMid(int value) {
    struct Data* node = newNode(value);
    if (head == NULL) {
        head = tail = node;
        return;
    }
    if (value <= head->value) {
        pushHead(value);
    }
    else if (value >= tail->value) {
        pushTail(value);
    }
    else {
        struct Data* curr = head;
        while (curr->next != NULL && curr->next->value < value) {
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
    }
}

void voidPopHead() {
    if (!head) return;
    else if (head == tail) {
        free(head);
        head = tail = NULL;
    }
    else {
        struct Data* temp = head->next;
        free(head);
        head = temp;
    }
}

void voidPopTail() {
    if (!head) return;
    else if (head == tail) {
        free(head);
        head = tail = NULL;
    }
    else {
        struct Data* curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        free(tail);
        tail = curr;
        tail->next = NULL;
    }
}

void voidPopByValue(int value) {
    if (!head) return;
    else if (value == head->value) {
        voidPopHead();
    }
    else if (value == tail->value) {
        voidPopTail();
    }
    else {
        struct Data* curr = head;
        while (curr->next != NULL && curr->next->value != value) {
            curr = curr->next;
        }
        if (curr->next == NULL) {
            printf("The value you want to delete isn't there\n");
            return;
        }
        struct Data* temp = curr->next; //sebagai node
        // curr->next = curr->next->next;
        curr->next = temp->next;
        free(temp);
    }
}

struct Data* popHead() {
    if (head == NULL) return NULL;
    else {
        struct Data* temp = head;
        if (head == tail) {
            head = tail = NULL;
        }
        else {
            head = head->next;
        }
        return temp;
    }   
}

struct Data* popTail() {
    if (head == NULL) return NULL;
    else {
        struct Data* temp = tail;
        if (head == tail) {
            head = tail = NULL;
            return temp;
        }
        else {
            struct Data* curr = head;
            while (curr->next != tail) {
                curr = curr->next;
            }
            // curr->next = NULL; BISA JUGA GINI
            tail = curr;
            tail->next = NULL;
            return temp;
        }
    }
}

struct Data* popByValue(int value) {
    if (head == NULL) return NULL;
    else {
        if (head == tail) {
            struct Data* temp = head;
            head = tail = NULL;
            return temp;
        }
        else if (head->value == value) {
            popHead();
        }
        else if (tail->value == value) {
            popTail();
        }
        else {
            struct Data* curr = head;
            while (curr->next != NULL && curr->next->value != value) {
                curr = curr->next;
            }
            if (curr->next == NULL){
                return NULL;
            }
            struct Data* temp = curr->next; //sebagai node
            // curr->next = curr->next->next;
            curr->next = temp->next;
            return temp;
        }
    }
}

void popAll() {
    if (head == NULL) {
        printf("No data deleted by popAll\n");
        return;
    }
    while (head != NULL) {
        struct Data* deleted;
        deleted = popHead();
        printf("%d is deleted using popAll\n", deleted->value);
        free(deleted);
    }
}

void printAll() {
    if (head == NULL) {
        printf("There is no data");
    }
    struct Data* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    pushMid(3);
    pushMid(10);
    pushMid(5);
    pushMid(8);
    printAll();
    voidPopByValue(7);
    // pushHead(5);
    // pushHead(10);
    // pushTail(20);
    // pushTail(15);

    // popAll();
    
    // struct Data* deleted;
    // deleted = popHead();
    // if (deleted == NULL) {
    //     printf("No data deleted by popHead!\n");
    // }
    // else {
    //     printf("%d is deleted using popHead\n", deleted->value);
    //     free(deleted);
    // }
    
    // deleted = popTail();
    // if (deleted == NULL) {
    //     printf("No data deleted by popTail\n");
    // }
    // else {
    //     printf("%d is deleted using popTail\n", deleted->value);
    //     free(deleted);
    // }
    
    // deleted = popByValue(8);
    // if (deleted == NULL){
    //     printf("No data deleted by popMid\n");
    // }
    // else {
    //     printf("%d is deleted using popMid\n", deleted->value);
    //     free(deleted);
    // }
    
    printAll();
    return 0;
}
