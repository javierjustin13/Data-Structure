#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 100 // 99 DATA because index 0 is not used
// HEAP = BINARY TREE, PARTIALLY ORDERED
// MAX HEAP = PARENT NODE IS ALWAYS GREATER THAN CHILD NODES
// MIN HEAP = PARENT NODE IS ALWAYS LESS THAN CHILD NODES

struct Node {
    char name[100];
    int value;
};

struct Node nodes[MAXSIZE];

int lastIndex = 1;

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int curr, int size) {
    int left = curr * 2;
    int right = curr * 2 + 1;
    int largest = curr;

    if (left < size && nodes[left].value > nodes[largest].value) {
        largest = left;
    }

    if (right < size && nodes[right].value > nodes[largest].value) {
        largest = right;
    }

    if (largest != curr) {
        swap(&nodes[curr], &nodes[largest]);
        heapify(largest, size);
    }
}


void buildHeap() {
    // LOOP ALL THE NODES THAT HAVE CHILDREN
    for (int i = lastIndex / 2; i >= 1; i--) {
        heapify(i, lastIndex);
    }
}

int search(int value) {
    for (int i = 1; i < lastIndex; i++) {
        if (nodes[i].value == value) return i;
    }
    return -1;
}

void del(int value) {
    int index = search(value);
    if (index == -1) return;
    swap(&nodes[index], &nodes[lastIndex - 1]);
    lastIndex -= 1;
    buildHeap();
}

void insert(const char name[], int value) {
    strcpy(nodes[lastIndex].name, name);
    nodes[lastIndex].value = value;
    lastIndex += 1;
    buildHeap();
}

void view() {
    for (int i = 1; i < lastIndex; i++) {
        printf("%s %d\n", nodes[i].name, nodes[i].value);
    }
}

void heapSort() {
    buildHeap();
    for (int i = lastIndex - 1; i > 1; i--) {
        swap(&nodes[1], &nodes[i]);
        heapify(1, i);
    }
}


int main() {
    insert("Ayam", 30);
    insert("Bebek", 28);
    insert("Domba", 42);
    insert("Anjing", 76);
    view();
    heapSort();
    printf("\n\nAfter Sorting\n\n");
    view();

    return 0;
}
