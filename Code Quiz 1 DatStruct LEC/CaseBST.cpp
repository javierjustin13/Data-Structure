#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Student {
    char name[100];
    char nim[100];
    Student* left, * right;
}*root = NULL;

Student* createStudent(const char name[], const char nim[]) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent->name, name);
    strcpy(newStudent->nim, nim);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

Student* insertStudent(Student* curr, Student* newStudent) {
    if (curr == NULL) return newStudent;
    else if (strcmpi(newStudent->name, curr->name) < 0) curr->left = insertStudent(curr->left, newStudent);
    else if (strcmpi(newStudent->name, curr->name) > 0) curr->right = insertStudent(curr->right, newStudent);
    return curr;
}

Student* searchStudent(Student *curr, const char toBeSearch[]) {
    if (curr == NULL) return NULL;
    else if (strcmpi(toBeSearch, curr->name) < 0) return searchStudent(curr->left, toBeSearch);
    else if (strcmpi(toBeSearch, curr->name) > 0) return searchStudent(curr->right, toBeSearch);
    else return curr;
}


Student* deleteStudent(Student* curr, const char toBeDeleted[]) {
    if (curr == NULL) return curr;
    else if (strcmpi(toBeDeleted, curr->name) < 0) curr->left = deleteStudent(curr->left, toBeDeleted);
    else if (strcmpi(toBeDeleted, curr->name) > 0) curr->right = deleteStudent(curr->right, toBeDeleted);
    else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
        }
        else if (curr->left != NULL && curr->right == NULL) { 
            Student* temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
        }
        else if (curr->left == NULL && curr->right != NULL) { 
            Student* temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        }
        else {
            Student* temp = curr->left;
            while (temp->right != NULL) temp = temp->right;
            strcpy(curr->name, temp->name);
            strcpy(curr->nim, temp->nim);
            curr->left = deleteStudent(curr->left, temp->name);
        }
    }
    return curr;
}

bool checkNumeric(const char nim[]) {
    for(int i = 0; i < strlen(nim); i++) {
        if (!isdigit(nim[i])) return false;
    }
    return true;
}

void insertMenu() {
    char name[100], nim[100];
    do {
        printf("Name: ");
        scanf("%[^\n]", &name);
        getchar();
    } while (strlen(name) < 3 || strlen(name) > 50);
    do {
        printf("NIM: ");
        scanf("%[^\n]", &nim);
        getchar();
    } while (strlen(nim) != 8 || !checkNumeric(nim));
    Student* temp = searchStudent(root, name);
    if (temp == NULL) {
        Student* newStudent = createStudent(name, nim);
        root = insertStudent(root, newStudent);
    }
    else {
        strcpy(temp->nim, nim);
        printf("Student name already exists, updated NIM instead\n");
    }
}

void deleteMenu() {
    char name[100];
    do {
        printf("Name: ");
        scanf("%[^\n]", name);
        getchar();
    } while (strlen(name) < 3 || strlen(name) > 50);
    Student* temp = searchStudent(root, name);
    if (temp == NULL) {
        printf("Cannot delete student because student name does not exist\n");
    }
    else {
        root = deleteStudent(root, name);
    }
}

void preOrder(Student* curr) {
    if (curr == NULL) return;
    printf("%s %s\n", curr->name, curr->nim);
    preOrder(curr->left);
    preOrder(curr->right);
}


int main() {
    while (true) {
        printf("1. Insert Student\n2. Delete Student\n3. Exit\n");
        int choice;
        do {
            printf(">> ");
            scanf("%d", &choice);
            getchar();
        } while (choice < 1 || choice > 3);
        if (choice == 1) {
            insertMenu();
            printf("\n");
            preOrder(root);
        }
        else if (choice == 2) {
            deleteMenu();
            printf("\n");
            preOrder(root);
        }
        else if (choice == 3) {
            break;
        }
    }
}
