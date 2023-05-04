#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 0 white
// 1 pink
// 2 yellow

struct Node {
    int value;
    int color;
    int height;
    int total;
    Node* left, * right;
};

Node* root = NULL;

int max(int a, int b){
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

int getTotal(Node* curr) {
    if (curr == NULL) return 0;
    return curr->total;
}

int calculateTotal(Node* curr) {
    return curr->value + getTotal(curr->left) + getTotal(curr->right);
}

int calculateHeight(Node* curr) {
    return 1 + max(getHeight(curr->left), getHeight(curr->right));
}

Node* leftRotate(Node* curr) {
    Node* newParent = curr->right;
    
    curr->right = newParent->left;
    newParent->left = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(curr);

    curr->total = calculateTotal(curr);
    newParent->total = calculateTotal(curr);
    
    if (getTotal(curr->left) < getTotal(curr->right)) curr->color = 1;
    else if (getTotal(curr->left) > getTotal(curr->right)) curr->color = 2;
    else curr->color = 0;

    if (getTotal(newParent->left) < getTotal(newParent->right)) newParent->color = 1;
    else if (getTotal(newParent->left) > getTotal(newParent->right)) newParent->color = 2;
    else newParent->color = 0;
    
    return newParent;
}

Node* rightRotate(Node* curr) {
    Node* newParent = curr->left;
    
    curr->left = newParent->right;
    newParent->right = curr;
    
    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(curr);

    curr->total = calculateTotal(curr);
    newParent->total = calculateTotal(curr);

    if (getTotal(curr->left) < getTotal(curr->right)) curr->color = 1;
    else if (getTotal(curr->left) > getTotal(curr->right)) curr->color = 2;
    else curr->color = 0;

    if (getTotal(newParent->left) < getTotal(newParent->right)) newParent->color = 1;
    else if (getTotal(newParent->left) > getTotal(newParent->right)) newParent->color = 2;
    else newParent->color = 0;

    return newParent;
}

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->height = 1;
    newNode->color = 0;
    newNode->total = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* curr, int value) {
    if (curr == NULL) return createNode(value);
    else if (value < curr->value) curr->left = insertNode(curr->left, value);
    else if (value > curr->value) curr->right = insertNode(curr->right, value);
    else return curr;

    curr->height = calculateHeight(curr);
    
    curr->total = calculateTotal(curr);

    if (getTotal(curr->left) < getTotal(curr->right)) curr->color = 1;
    else if (getTotal(curr->left) > getTotal(curr->right)) curr->color = 2;
    else curr->color = 0;

    int balance = getBalance(curr);
    // Left Left
    if (balance > 1 && getBalance(curr->left) >= 0) return rightRotate(curr);
    // Right Right
    if (balance < -1 && getBalance(curr->right) <= 0) return leftRotate(curr);
    // Left Right
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    // Right Left
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

Node* deleteNode(Node* curr, int value) {
    if (curr == NULL) return curr;
    else if (value < curr->value) curr->left = deleteNode(curr->left, value);
    else if (value > curr->value) curr->right = deleteNode(curr->right, value);
    else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
            return curr;
        }
        else if (curr->left == NULL) {
            Node* temp = curr->left;
            free(curr);
            return temp;
        }
        else if (curr->right == NULL) {
            Node* temp = curr->right;
            free(curr);
            return temp;
        }
        else {
            Node* temp = curr->left;
            while (temp->right != NULL) temp = temp->right;
            curr->value = temp->value;
            curr->left = deleteNode(curr->left, temp->value);
        }
    }

    curr->height = calculateHeight(curr);

    curr->total = calculateTotal(curr);

    if (getTotal(curr->left) < getTotal(curr->right)) curr->color = 1;
    else if (getTotal(curr->left) > getTotal(curr->right)) curr->color = 2;
    else curr->color = 0;
    
    int balance = getBalance(curr);
    // Left Left
    if (balance > 1 && getBalance(curr->left) >= 0) return rightRotate(curr);
    // Right Right
    if (balance < -1 && getBalance(curr->right) <= 0) return leftRotate(curr);
    // Left Right
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    // Right Left
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

void inOrder(Node* curr) {
    if (curr != NULL) {
        inOrder(curr->left);
        printf("%d %d\n", curr->value, curr->color);
        inOrder(curr->right);
    }
}

int white, pink, yellow;
void countColorChild(Node* curr, int value)
{
    if (curr)
    {
        countColorChild(curr->left, value);
        if (curr->value != value)
        {
            if (curr->color == 0)
            {
                white++;
            }
            if (curr->color == 1)
            {
                pink++;
            }
            if (curr->color == 2)
            {
                yellow++;
            }
        }
        countColorChild(curr->right, value);
    }
}

void describeNode(Node* curr, int value) {
    if (curr == NULL) return;
    else if (value < curr->value) describeNode(curr->left, value);
    else if (value > curr->value) describeNode(curr->right, value);
    else {
        white = yellow = pink = 0;
        printf("value : %d\n", curr->value);
        printf("keyword : %d\n", curr->color);
        countColorChild(curr, value);
        printf("pink children : %d\n", pink);
        printf("white children : %d\n", white);
        printf("yellow children : %d\n", yellow);
    }
}

int main() {
    // root = insertNode(root, 50);
    // root = insertNode(root, 20);
    // root = insertNode(root, 75);
    // root = insertNode(root, 120);
    // root = insertNode(root, 2);
    // root = insertNode(root, 160);
    // root = insertNode(root, 69);
    // inOrder(root);

    root = insertNode(root, 10);
    root = insertNode(root, 11);
    root = insertNode(root, 12);
    root = insertNode(root, 13);
    describeNode(root, 11);
    return 0;
}