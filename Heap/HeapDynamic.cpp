#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// HEAP = BINARY TREE, PARTIALLY ORDERED
// MAX HEAP = PARENT NODE IS ALWAYS GREATER THAN CHILD NODES
// MIN HEAP = PARENT NODE IS ALWAYS LESS THAN CHILD NODES

struct Node {
    char name[100];
    int value;
};

struct Heap {
    Node* nodes;
    int capacity;
    int lastIndex;
}heap;

void initializeHeap() {
    // heap = {NULL, 2,  1};
    heap.capacity = 2;
    heap.lastIndex = 1;
    heap.nodes = (Node*)malloc(sizeof(Node) * heap.capacity);
}

void resizeHeap() {
    heap.capacity *= 2;
    heap.nodes = (Node*)realloc(heap.nodes, sizeof(Node) * heap.capacity);
}

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int curr, int size) {
    int left = curr * 2;
    int right = curr * 2 + 1;
    int largest = curr;

    if (left < size && heap.nodes[left].value > heap.nodes[largest].value) {
        largest = left;
    }

    if (right < size && heap.nodes[right].value > heap.nodes[largest].value) {
        largest = right;
    }

    if (largest != curr) {
        swap(&heap.nodes[curr], &heap.nodes[largest]);
        heapify(largest, size);
    }
}


void buildHeap() {
    // LOOP ALL THE NODES THAT HAVE CHILDREN
    for (int i = heap.lastIndex / 2; i >= 1; i--) {
        heapify(i, heap.lastIndex);
    }
}

int search(int value) {
    for (int i = 1; i < heap.lastIndex; i++) {
        if (heap.nodes[i].value == value) return i;
    }
    return -1;
}

void del(int value) {
    int index = search(value);
    if (index == -1) return;
    swap(&heap.nodes[index], &heap.nodes[heap.lastIndex - 1]);
    heap.lastIndex -= 1;
    buildHeap();
}

void insert(const char name[], int value) {
    if (heap.lastIndex == heap.capacity) {
        resizeHeap();
    }
    strcpy(heap.nodes[heap.lastIndex].name, name);
    heap.nodes[heap.lastIndex].value = value;
    heap.lastIndex += 1;
    buildHeap();
}

void view() {
    for (int i = 1; i < heap.lastIndex; i++) {
        printf("%s %d\n", heap.nodes[i].name, heap.nodes[i].value);
    }
}

void heapSort() {
    buildHeap();
    for (int i = heap.lastIndex - 1; i > 1; i--) {
        swap(&heap.nodes[1], &heap.nodes[i]);
        heapify(1, i);
    }
}


int main() {
    initializeHeap();
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
