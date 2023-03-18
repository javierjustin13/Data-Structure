#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int val;
    Node* left;
    Node* right;
};
Node* root = NULL;

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* curr, Node* node) {
    if (curr == NULL) return node;
    else if (node->val > curr->val) curr->right = insert(curr->right, node);
    else if (node->val < curr->val) curr->left = insert(curr->left, node);
    return curr;
}

void printInfix(Node* curr) {
    if (curr == NULL) return;
    printInfix(curr->left);
    printf("%d ", curr->val);
    printInfix(curr->right);
}

void printPrefix(Node* curr) {
    if (curr == NULL) return;
    printf("%d ", curr->val);
    printInfix(curr->left);
    printInfix(curr->right);
}

void printPostfix(Node* curr) {
    if (curr == NULL) return;
    printInfix(curr->left);
    printInfix(curr->right);
    printf("%d ", curr->val);
}

void searchNode(Node* curr, int valToBeSearched) {
    if (curr == NULL) {
        printf("%d is not found in BST\n", valToBeSearched);
        return;
    }
    else if (valToBeSearched < curr->val) searchNode(curr->left, valToBeSearched);
    else if (valToBeSearched > curr->val) searchNode(curr->right, valToBeSearched);
    else if (curr->val == valToBeSearched) {
        printf("%d is found in BST\n", valToBeSearched);
        return;
    }
}

Node* deleteNode(Node* curr, int valToBeDeleted) {
    if (curr == NULL) { printf("%d is not in BST", valToBeDeleted); return curr; }
    else if (valToBeDeleted < curr->val) curr->left = deleteNode(curr->left, valToBeDeleted);
    else if (valToBeDeleted > curr->val) curr->right = deleteNode(curr->right, valToBeDeleted);
    else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr); curr = NULL;
        }

        else if (curr->left != NULL && curr->right == NULL) {
            Node* temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
        }

        else if (curr->left == NULL && curr->right != NULL) {
            Node* temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        }

        else if (curr->left != NULL && curr->right != NULL) {
            Node* temp = curr->left;
            while (temp->right != NULL) temp = temp->right;
            curr->val = temp->val;
            curr->left = deleteNode(curr->left, temp->val);
        }
    }
    return curr;
}

int main() {
    root = insert(root, createNode(10));
    root = insert(root, createNode(3));
    root = insert(root, createNode(15));
    root = insert(root, createNode(7));
    root = insert(root, createNode(13));
    root = insert(root, createNode(22));
    printf("\nInfix: \n"); printInfix(root); printf("\n"); 
    printf("\nPostfix: \n"); printPostfix(root); printf("\n"); 
    printf("\nPrefix: \n"); printPrefix(root); printf("\n"); 
    searchNode(root, 10);
    searchNode(root, 7);
    root = deleteNode(root, 3);
    printf("\nPrefix: \n"); printPrefix(root); printf("\n"); printf("\n");
    
    return 0;
}
