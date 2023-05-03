#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node {
    int id;
    char name[101];
    int value;
    int height;
    Node *left;
    Node *right;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* curr) {
    if (curr == NULL) return 0;
    return curr->height;
}

int getBalance(Node* curr) {
    if (curr == NULL) return 0;
    return getHeight(curr->left) - getHeight(curr->right);
}

int calculateHeight(Node *curr){
    return max(getHeight(curr->left), getHeight(curr->right)) + 1;
}

Node* rightRotate(Node* curr) {
    Node* newParent = curr->left;
    curr->left = newParent->right;
    newParent->right = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);

    return newParent;
}

Node* leftRotate(Node* curr) {
    Node* newParent = curr->right;
    curr->right = newParent->left;
    newParent->left = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);

    return newParent;
}

Node* createNode(int id, const char name[], int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->value = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* curr, Node* newNode) {
    if (curr == NULL) return newNode;
    else if(newNode->id < curr->id) curr->left = insertNode(curr->left, newNode);
    else if (newNode->id > curr->id) curr->right = insertNode(curr->right, newNode);
    
    curr->height = calculateHeight(curr);
    int balance = getBalance(curr);

    if (balance > 1) {
        if(newNode->id <= curr->left->id) return rightRotate(curr);
        else if (newNode->id > curr->left->id) {
            curr->left = leftRotate(curr->left);
            return rightRotate(curr);
        }
    }
    else if(balance < -1) {
        if(newNode->id > curr->right->id) return leftRotate(curr);
        else if (newNode->id < curr->right->id) {
            curr->right = rightRotate(curr->right);
            return leftRotate(curr);
        }
    }
    return curr;

    // if (balance > 1) {
    //     if (value > curr->left->value) {
    //         curr->left = leftRotate(curr->left);
    //     }
    //     return rightRotate(curr);
    // }

    // else if (balance < -1) {
    //     if (value < curr->right->value) {
    //         curr->right = rightRotate(curr->right);
    //     }
    //     return leftRotate(curr);
    // }
    // return curr;
}

Node* deleteNode(Node* curr, int id) {
    if (curr == NULL) return NULL;
    else if (id < curr->id) curr->left = deleteNode(curr->left, id);
    else if (id > curr->id) curr->right = deleteNode(curr->right, id);
    else {
        if (curr->right == NULL && curr->left == NULL) {
            free(curr);
            curr = NULL;
        }
        else if (curr->right == NULL) {
            Node* temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
        }
        else if (curr->left == NULL) {
            Node* temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        }
        else {
            Node* temp = curr->left;
            while (temp != NULL && temp->right != NULL) temp = temp->right;
            curr->id = temp->id;
            strcpy(curr->name, temp->name);
            curr->value = temp->value;
            curr->left = deleteNode(curr->left, temp->id);
        }
    }
    if (curr == NULL) return NULL;
    curr->height = calculateHeight(curr);
    int balance = getBalance(curr);

    if (balance > 1) {
        if (getBalance(curr->left) >= 0) return rightRotate(curr);
        else if (getBalance(curr->left) < 0) {
            curr->left = leftRotate(curr->left);
            return rightRotate(curr);
        }
    }
    else if (balance < -1) {
        if (getBalance(curr->right) <= 0) return leftRotate(curr);
        else if (getBalance(curr->right) > 0) {
            curr->right = rightRotate(curr->right);
            return leftRotate(curr);
        }
    }
    return curr;
}

void inOrder(Node* curr) {
    if (curr == NULL) return;
    inOrder(curr->left);
    printf("%-3d %-30s %-6d (%d)\n", curr->id, curr->name, curr->value, curr->height);
    inOrder(curr->right);
}

int main() {
    Node* root = NULL;
    
    // root = insertNode(root, createNode(10, "Bakso", 20000));
    // root = insertNode(root, createNode(5, "Mie Ayam", 15000));
    // root = insertNode(root, createNode(3, "Salad", 10000));
    // root = insertNode(root, createNode(20, "Curry", 17500));
    // root = insertNode(root, createNode(30, "Nasi Uduk", 25000));
    
    root = insertNode(root, createNode(5, "Bakso", 20000));
    root = insertNode(root, createNode(4, "Mie Ayam", 15000));
    root = insertNode(root, createNode(3, "Salad", 10000));
    root = insertNode(root, createNode(2, "Curry", 17500));
    root = insertNode(root, createNode(1, "Nasi Uduk", 25000));

    root = deleteNode(root,3);
    root = deleteNode(root,5);
    root = deleteNode(root,1);
    root = deleteNode(root,4);
    root = deleteNode(root,2);

    inOrder(root);
    return 0;
}