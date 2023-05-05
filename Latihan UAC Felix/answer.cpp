#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Property {
    char id[6];
    int N;
    int length;
    char type[20];

    int height;
    Property* left, * right;
};

Property* root = NULL;

int max(int a, int b) {
    return a < b ? a : b;
}

int getHeight(Property* curr) {
    if (curr == NULL) return 0;
    return curr->height;
}

int getBalance(Property* curr) {
    if (curr == NULL) return 0l;
    return getHeight(curr->left) - getHeight(curr->right);
}

int calculateHeight(Property* curr) {
    if (curr == NULL) return 0;
    return 1 + max(getHeight(curr->left), getHeight(curr->right));
}

Property* rightRotate(Property* curr) {
    Property* newParent = curr->left;
    curr->left = newParent->right;
    newParent->right = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(curr);

    return newParent;
}

Property* leftRotate(Property* curr) {
    Property* newParent = curr->right;
    curr->right = newParent->left;
    newParent->left = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(curr);

    return newParent;
}

Property* createProperty(const char id[], int N, int length, const char type[]) {
    Property* newProperty = (Property*)malloc(sizeof(Property));
    strcpy(newProperty->id, id);
    newProperty->N = N;
    newProperty->length = length;
    strcpy(newProperty->type, type);
    newProperty->left = newProperty->right = NULL;
    newProperty->height = 1;
    return newProperty;
}

Property* insertProperty(Property* curr, Property* newProperty) {
    if (curr == NULL) return newProperty;
    else if(strcmp(newProperty->id, curr->id) < 0) curr->left = insertProperty(curr->left, newProperty);
    else if(strcmp(newProperty->id, curr->id) > 0) curr->right = insertProperty(curr->right, newProperty);
    else return curr;

    curr->height = calculateHeight(curr);

    int balance = getBalance(curr);

    if (balance > 1 && getBalance(curr->left) >= 0) return rightRotate(curr);
    if (balance < -1 && getBalance(curr->right) <= 0) return leftRotate(curr);
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

Property* deleteProperty(Property* curr, const char id[]) {
    if (curr == NULL) return NULL;
    else if (strcmp(id, curr->id) < 0) curr->left = deleteProperty(curr->left, id);
    else if (strcmp(id, curr->id) > 0) curr->right = deleteProperty(curr->right, id);
    else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
        }
        else if (curr->right == NULL) {
            Property* temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
        }
        else if (curr->left == NULL) {
            Property* temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        }
        else {
            Property* temp = curr->left;
            while (temp->right != NULL) temp = temp->right;
            strcpy(curr->id, temp->id);
            curr->N = temp->N;
            curr->length = temp->length;
            strcpy(curr->type, temp->type);
            curr->left = deleteProperty(curr->left, temp->id);     
        }
    }

    if (curr == NULL) return curr;

    curr->height = calculateHeight(curr);

    int balance = getBalance(curr);

    if (balance > 1 && getBalance(curr->left) >= 0) return rightRotate(curr);
    if (balance < -1 && getBalance(curr->right) <= 0) return leftRotate(curr);
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

Property* searchProperty(Property* curr, const char id[]) {
    if (curr == NULL) return NULL;
    else if (strcmp(id, curr->id) < 0) return searchProperty(curr->left, id);
    else if (strcmp(id, curr->id) > 0) return searchProperty(curr->right, id);
    return curr;
}

void deleteAll() {
    while (root != NULL) root = deleteProperty(root, root->id);
}

void printProperty(Property *curr) {
    long long area = 0;
    const double phi = 3.14;
    int landPrice;
    if (strcmp(curr->type, "rural") == 0) landPrice = 2000;
    else if (strcmp(curr->type, "capital") == 0) landPrice = 5500;
    else if (strcmp(curr->type, "metro") == 0) landPrice = 10000;

    if (curr->N == 4) area = pow(curr->length, 2);
    else area = (curr->N * pow(curr->length, 2)) / (4 * tan(phi / curr->N));
    printf("%5s  | %-2d | %-4d | %-20s | %-15d |\n", curr->id, curr->N, curr->length, curr->type, landPrice * area);
    
}

void preOrder(Property* curr) {
    if (curr == NULL) return;
    printProperty(curr);
    preOrder(curr->left);
    preOrder(curr->right);
}

void inOrder(Property* curr) {
    if(curr == NULL) return;
    inOrder(curr->left);
    printProperty(curr);
    inOrder(curr->right);
}

int main() {
    
    root = insertProperty(root,
        createProperty("TX003", 5, 10, "capital"));
    root = insertProperty(root,
        createProperty("TX001", 7, 100, "rural"));
    root = insertProperty(root,
        createProperty("TX005", 5, 15, "rural"));
    root = insertProperty(root,
        createProperty("TX006", 4, 5, "capital"));
    root = insertProperty(root,
        createProperty("TX002", 10, 20, "metro"));
    root = insertProperty(root,
        createProperty("TX004", 8, 8, "metro"));

    // deleteAll();
    // root = deleteProperty(root, root->id);

    inOrder(root);
    return 0;
}