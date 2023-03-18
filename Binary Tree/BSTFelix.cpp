#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};
struct Node* root = NULL;

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* curr, Node* node) {
    if (curr == NULL) return node; // if the tree is empty, return a new node
    else if (node->value < curr->value) curr->left = insertNode(curr->left, node); // if the node's value is less than the current node's value, insert it to the left
    else if (node->value > curr->value) curr->right = insertNode(curr->right, node); // if the node's value is greater than the current node's value, insert it to the right
    return curr; // return the current node
}

void inOrder(Node* curr) {
    if (curr == NULL) return;
    inOrder(curr->left);
    printf("%d ", curr->value);
    inOrder(curr->right);
}

void preOrder(Node* curr) {
    if (curr == NULL) return;
    printf("%d ", curr->value);
    preOrder(curr->left);
    preOrder(curr->right);
}

void postOrder(Node* curr) {
    if (curr == NULL) return;
    postOrder(curr->left);
    postOrder(curr->right);
    printf("%d ", curr->value);
}

Node* deleteNode(Node* curr, int value) {
    if (curr == NULL) return curr; // if the tree is empty, return NULL
    else if (value < curr->value) curr->left = deleteNode(curr->left, value); // if the value is less than the current node's value, delete it from the left
    else if (value > curr->value) curr->right = deleteNode(curr->right, value); // if the value is greater than the current node's value, delete it from the right
    else { // if the value is equal to the current node's value
        if (curr->left == NULL && curr->right == NULL) { // if the node is a leaf node
            free(curr);
            curr = NULL;
        } else if (curr->left == NULL) { // if the node has only right child
            struct Node* temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        }
        else if (curr->right == NULL) { // if the node has only left child
            struct Node* temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
        }
        else { // if the node has two children
            struct Node* temp = curr->left;
            while (temp->right != NULL) temp = temp->right; 
            curr->value = temp->value; 
            curr->left = deleteNode(curr->left, temp->value); // delete the inorder predecessor from the left subtree
        }
    }
    return curr;
}

Node *searchNode(Node* curr, int value) {
    if (curr == NULL) { printf("%d is not in BST\n", value); return curr; }
    else if (value < curr->value) searchNode(curr->left, value);
    else if (value > curr->value) searchNode(curr->right, value);
    else if (value == curr->value) { printf("%d is in BST\n", value); return curr; }
}

void popAll(Node* curr) {
    if (curr == NULL) return;
    popAll(curr->left);
    popAll(curr->right);
    free(curr);
    curr = NULL;
}

Node* deleteAll(Node* curr) {
    while (curr != NULL) {
        curr = deleteNode(curr, curr->value);
    }
    return curr;
}
int main() {
    root = insertNode(root, createNode(10));
    root = insertNode(root, createNode(3));
    root = insertNode(root, createNode(15));
    root = insertNode(root, createNode(7));
    root = insertNode(root, createNode(13));
    root = insertNode(root, createNode(22));
    // root = insertNode(root, createNode(17));
    // inOrder(root);
    // printf("\n");
    preOrder(root);
    printf("\n");
    // postOrder(root);
    // printf("\n");
    // root = deleteNode(root, 2);
    root = deleteNode(root, 10);
    // root = deleteNode(root, 10);
    // inOrder(root);
    // printf("\n");
    preOrder(root);
    printf("\n");
    // postOrder(root);
    // printf("\n");
    // root = deleteAll(root);
    // inOrder(root);
    // printf("\n");
    return 0;
}