#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    char title[100];
    char author[100];
    int year;
    int rating;
    int id;
    Node* left, * right;
    int height;
};

int ongoingID = 1;

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

int calculateHeight(Node* curr) {
    return 1 + max(getHeight(curr->left), getHeight(curr->right));
}

Node* leftRotate(Node* curr) {
    Node* newParent = curr->right;
    curr->right = newParent->left;
    newParent->left = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);
    
    return newParent;
}

Node* rightRotate(Node* curr) {
    Node* newParent = curr->left;
    curr->left = newParent->right;
    newParent->right = curr;

    curr->height = calculateHeight(curr);
    newParent->height = calculateHeight(newParent);

    return newParent;
}

Node* createNode(Node* curr, const char title[],const char author[], int year, int rating, int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->height = 1;
    strcpy(newNode->title, title);
    strcpy(newNode->author, author);
    newNode->year = year;
    newNode->rating = rating;
    newNode->id = id;
    newNode->left = newNode->right = NULL;
    ongoingID += 1;
    return newNode;
}

Node* insertNode(Node* curr, Node* newNode) {
    if (curr == NULL) return newNode;
    else if (newNode->id < curr->id) curr->left = insertNode(curr->left, newNode);
    else if (newNode->id > curr->id) curr->right = insertNode(curr->right, newNode);
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

Node* deleteNode(Node* curr, int id) {
    if (curr == NULL) return NULL;
    else if (id < curr->id) curr->left = deleteNode(curr->left, id);
    else if (id > curr->id) curr->right = deleteNode(curr->right, id);
    else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
            return curr;
        }
        else if (curr->left == NULL) {
            Node *temp = curr->left;
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
            curr->id = temp->id;
            curr->left = deleteNode(curr->left, temp->id);
        }
    }

    curr->height = calculateHeight(curr);
    int balance = getBalance(curr);

    if (balance > 1 && getBalance(curr->left) >= 0) {
        return rightRotate(curr);
    }
    if (balance < -1 && getBalance(curr->right) <= 0) {
        return leftRotate(curr);
    }
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
bool found = false;
void checkName(Node* curr, char title[]) {
    if (curr == NULL) return;
    if (strcmp(curr->title, title) == 0) {
        found = true;
        return;
    }
    checkName(curr->left, title);
    checkName(curr->right, title);
}

Node* findNode(Node* curr, int toBeFind) {
    if (curr == NULL) return NULL;
    if (curr->id == toBeFind) return curr;
    if (curr->id < toBeFind) return findNode(curr->right, toBeFind);
    if (curr->id > toBeFind) return findNode(curr->left, toBeFind);
}

void inOrder(Node* curr) {
    if (curr != NULL) {
        inOrder(curr->left);
        printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\nRating: %d\n\n", curr->id, curr->title, curr->author, curr->year, curr->rating);
        inOrder(curr->right);
    }
}

int child = 0;
void countChild(Node* curr) {
    if (curr == NULL) return;
    child++;
    countChild(curr->left);
    countChild(curr->right);
}

int main() {
    Node* root = NULL;
    root = insertNode(root, createNode(root, "More Than Ballons", "Gregor", 1997, 4, ongoingID));
    root = insertNode(root, createNode(root, "Dump Truck", "Heimdall", 2000, 3, ongoingID));
    root = insertNode(root, createNode(root, "Hello World", "Travy", 1999, 4, ongoingID));
    root = insertNode(root, createNode(root, "Secret Tetris", "Tetron", 2010, 5, ongoingID));
    root = insertNode(root, createNode(root, "Florian", "Homer", 1997, 2, ongoingID));
    root = insertNode(root, createNode(root, "Sea Gardener", "Garen", 2005, 4, ongoingID));
    root = insertNode(root, createNode(root, "Wild Dog", "Hisna", 2006, 4, ongoingID));
    root = insertNode(root, createNode(root, "Trump Game", "Fiona", 2009, 2, ongoingID));
    root = insertNode(root, createNode(root, "Class Act", "Navi", 2001, 1, ongoingID));
    root = insertNode(root, createNode(root, "Silly Bear", "Garen", 2020, 5, ongoingID));

    int N;
    scanf("%d", &N); getchar();
    
    for (int i = 0; i < N; i++) {
        char command[15];        
        scanf("%s", &command); getchar();

        if (strcmp(command, "INSERT") == 0) {
            int insertCount;
            scanf("%d", &insertCount); getchar();
            for (int j = 0; j < insertCount; j++) {
                char title[100], author[100];
                int year, rating;
                found = false;
                scanf("%[^#]#%[^#]#%d#%d", &title, &author, &year, &rating); getchar();
                checkName(root, title);
                if (found == true) printf("Title is already there");
                else root = insertNode(root, createNode(root, title, author, year, rating, ongoingID));
            }
        }

        else if (strcmp(command, "FIND") == 0) {
            int idToBeFound;
            scanf("%d", &idToBeFound); getchar();
            Node* nodeToBeFind = findNode(root, idToBeFound);
            if (nodeToBeFind == NULL) printf("Book ID %d not found\n", idToBeFound);
            else {
                printf("Book ID %d found\n", idToBeFound);
                printf("ID: %d\n", nodeToBeFind->id);
                printf("Title: %s\n", nodeToBeFind->title);
                printf("Author: %s\n", nodeToBeFind->author);
                printf("Year: %d\n", nodeToBeFind->year);
                printf("Rating: %d\n", nodeToBeFind->rating);
                printf("\n");
            }
        }
        
        else if (strcmp(command, "DELETE") == 0) {
            int idToBeDeleted;
            scanf("%d", &idToBeDeleted); getchar();
            root = deleteNode(root, idToBeDeleted);
        }
        
        else if (strcmp(command, "SHOWALL") == 0) {
            inOrder(root);
        }

        else if (strcmp(command, "CHECKLEFTROOT") == 0) {
            child = 0;
            countChild(root->left);
            printf("%d\n", child);
        }
        
        else if (strcmp(command, "CHECKRIGHTROOT") == 0) {
            child = 0;
            countChild(root->right);
            printf("%d\n", child);
        }
    }

    return 0;
}