#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[100];
    int value;
    Node* left, * right;
    int height;
};

Node *createNode(const char name[], int value) {
    Node *temp = (Node*)malloc(sizeof(Node));
    strcpy(temp->name, name);
    temp->value = value;
    temp->left = temp->right = NULL;
    temp->height = 1;
    return temp;
}

int getMax(int a, int b) {
    return (a >= b) ? a : b;
}

int calculateHeight(Node* node) {
    // int leftHeight = calculateHeight(node->left);
    // int rightHeight = calculateHeight(node->right);
    // return getMax(leftHeight, rightHeight) + 1;
    return (node == NULL) ? NULL : 1 + getMax(calculateHeight(node->left), calculateHeight(node->right));
}

int calculateBalance(Node* node) {
    // int leftHeight = calculateHeight(node->left);
    // int rightHeight = calculateHeight(node->right);
    return (node == NULL) ? NULL : calculateHeight(node->left) - calculateHeight(node->right);
}

Node *rightRotate(Node *node) {
    Node *newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;
    
    node->height = calculateHeight(node);
    newParent->height = calculateHeight(newParent);

    return newParent;
}

Node *leftRotate(Node *node) {
    Node* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    node->height = calculateHeight(node);
    newParent->height = calculateHeight(newParent);

    return newParent;
}

Node *insertNode(Node *curr, const char name[], int value) {
    if (curr == NULL) {
        return createNode(name, value);
    }
    if (value < curr->value) {
        curr->left = insertNode(curr->left, name, value);
    } else if (value > curr->value) {
        curr->right = insertNode(curr->right, name, value);
    } else {
        return curr;
    }

    curr->height = calculateHeight(curr);
    
    int balance = calculateBalance(curr);
    if (balance > 1) {
        if (value > curr->left->value) {
            curr->left = leftRotate(curr->left);
        }
        return rightRotate(curr);
    }
    
    else if (balance < -1) {
        if(value < curr->right->value) {
            curr->right = rightRotate(curr->right);
        }
        return leftRotate(curr);
    }
    return curr;
}

Node* updateFood(Node *curr, int valueSearched, const char newName[]) {
    if (curr == NULL) { printf("\nData not found\n"); return NULL; }
    if (valueSearched < curr->value) curr->left = updateFood(curr->left, valueSearched, newName);
    else if (valueSearched > curr->value) curr->right = updateFood(curr->right, valueSearched, newName);
    else {
        strcpy(curr->name, newName);
        printf("\nData updated\n");
        return curr;
    }
}



void inOrder(Node *curr) {
    if (curr == NULL) return;
    inOrder(curr->left);
    printf("%s %d | height : %d | balance : %d\n", curr->name, curr->value, curr->height, calculateBalance(curr));
    inOrder(curr->right);
}

int main() {
    Node* root = insertNode(NULL, "Sate Padang", 34000);
    root = insertNode(root, "Sate Kambing", 30000);
    root = insertNode(root, "Sate Ayam", 28000);
    root = insertNode(root, "Sate Kelinci", 26000);
    root = insertNode(root, "Sate Taichan", 24000);
    root = insertNode(root, "Sate Kuda", 22000);

    inOrder(root);

    root = updateFood(root, 28000, "Sate Ayam Bakar");
    inOrder(root);

    root = updateFood(root, 40000, "Sate Ayam Bakar");
    inOrder(root);
    return 0;
}
