#include <stdio.h>
#include <stdlib.h>

struct Data {
    int val;
    int height;
    Data* left, * right;
};

Data* root = NULL;
Data* temp = NULL;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Data *curr) {
    if (curr == NULL) return 0;
    return curr->height;
}

int getBalance(Data *curr) {
    if (curr == NULL) return 0;
    return getHeight(curr->left) - getHeight(curr->right);
}

Data* rightRotate(Data* T) {
    //Node T that violates balance
    Data* S = T->left;
    Data* B = S->right;

    //Rotate
    T->left = B;
    S->right = T;

    //Update height
    T->height = 1 + max(getHeight(T->left), getHeight(T->right));
    S->height = 1 + max(getHeight(S->left), getHeight(S->right));

    return S;
}

Data* leftRotate(Data* T) {
    //Node T that violates balance
    Data* S = T->right;
    Data* B = S->left;

    //Rotate
    T->right = B;
    S->left = T;

    //Update height
    T->height = 1 + max(getHeight(T->left), getHeight(T->right));
    S->height = 1 + max(getHeight(S->left), getHeight(S->right));

    return S;
}



Data* createNode(int val) {
    temp = (Data*)malloc(sizeof(Data));
    temp->val = val;
    temp->height = 1;
    temp->left = temp->right = NULL;
    return temp;
}

Data *insertNode(Data *curr, int val){
    if(curr == NULL) return createNode(val);
    else if(val < curr->val) curr->left = insertNode(curr->left, val);
    else if(val > curr->val) curr->right = insertNode(curr->right, val);
    else return curr;

    //Update height
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    //Check balance
    int balance = getBalance(curr);

    //Case Left Left
    // if (balance > 1 && val < curr->left->val) return rightRotate(curr);
    if(balance > 1 && getBalance(curr->left) >= 0) return rightRotate(curr);
    
    //Case Right Right
    // if (balance < -1 && val > curr->right->val) return leftRotate(curr);
    if (balance < -1 && getBalance(curr->right) <= 0) return leftRotate(curr);
    
    //Case Left Right
    // if (balance > 1 && val > curr->left->val) {
    //     curr->left = leftRotate(curr->left);
    //     return rightRotate(curr);
    // }
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }

    //Case Right Left
    // if (balance < -1 && val < curr->right->val) {
    //     curr->right = rightRotate(curr->right);
    //     return leftRotate(curr);
    // }
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

Data* deleteNode(Data* curr, int val) {
    if(curr == NULL) return curr;
    else if(val < curr->val) curr->left = deleteNode(curr->left, val);
    else if(val > curr->val) curr->right = deleteNode(curr->right, val);
    else {
        //Case 1: No child
        if(curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
            return curr;
        }
        //Case 2: One child
        else if (curr->left == NULL) {
            temp = curr->right;
            free(curr);
            return temp;
        }
        else if(curr->right == NULL) {
            temp = curr->left;
            free(curr);
            return temp;
        }
        //Case 3: Two child
        else {
            temp = curr->left;
            while(temp->right != NULL) temp = temp->right;
            curr->val = temp->val;
            curr->left = deleteNode(curr->left, temp->val);
        }
    }
    //Update height
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    //Check balance
    int balance = getBalance(curr);

    //Case Left Left
    // if (balance > 1 && val < curr->left->val) return rightRotate(curr);
    if (balance > 1 && getBalance(curr->left) >= 0) return rightRotate(curr);

    //Case Right Right
    // if (balance < -1 && val > curr->right->val) return leftRotate(curr);
    if (balance < -1 && getBalance(curr->right) <= 0) return leftRotate(curr);

    //Case Left Right
    // if (balance > 1 && val > curr->left->val) {
    //     curr->left = leftRotate(curr->left);
    //     return rightRotate(curr);
    // }
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }

    //Case Right Left
    // if (balance < -1 && val < curr->right->val) {
    //     curr->right = rightRotate(curr->right);
    //     return leftRotate(curr);
    // }
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

void preOrder(Data *curr){
    if(curr != NULL){
        printf("%d ", curr->val);
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void peek() {
    if (root != NULL) printf("\nRoot: %d\n\n", root->val);
    else printf("\nRoot: NULL\n\n");
}

int main() {
    root = insertNode(root, 70);
    root = insertNode(root, 80);
    root = insertNode(root, 90);
    root = insertNode(root, 100);
    root = insertNode(root, 50);
    root = deleteNode(root, 80);
    root = deleteNode(root, 50);
    root = deleteNode(root, 90);
    preOrder(root);
    peek();
    return 0;
}

