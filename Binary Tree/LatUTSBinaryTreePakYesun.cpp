#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CustomerNode {
    char name[100];
    char membership[100];
    struct CustomerNode* left;
    struct CustomerNode* right;
} *CustomerRoot = NULL;

struct MembershipNode {
    char membership[100];
    //Non-member, Bronce, Silver, Gold, Platinum
    struct MembershipNode* left;
    struct MembershipNode* right;
} *MembershipRoot = NULL;

CustomerNode* createCustomerNode(const char name[], char membership[]) {
    CustomerNode* newCustomerNode = (CustomerNode*)malloc(sizeof(CustomerNode));
    strcpy(newCustomerNode->name, name);
    strcpy(newCustomerNode->membership, membership);
    newCustomerNode->left = newCustomerNode->right = NULL;
    return newCustomerNode;
}

MembershipNode* createMembershipNode(const char membership[]) {
    MembershipNode* newMembershipNode = (MembershipNode*)malloc(sizeof(MembershipNode));
    strcpy(newMembershipNode->membership, membership);
    newMembershipNode->left = newMembershipNode->right = NULL;
    return newMembershipNode;
}

CustomerNode* insertCustomerNode(CustomerNode* curr, CustomerNode* node) {
    if (curr == NULL) return node;
    else if (strcmp(node->name, curr->name) < 0) curr->left = insertCustomerNode(curr->left, node);
    else if (strcmp(node->name, curr->name) > 0) curr->right = insertCustomerNode(curr->right, node);
    return curr;
}

MembershipNode* insertMembershipNode(MembershipNode* curr, MembershipNode* node) {
    if (curr == NULL) return node; 
    else if (strcmp(node->membership, curr->membership) < 0) curr->left = insertMembershipNode(curr->left, node); 
    else if (strcmp(node->membership, curr->membership) > 0) curr->right = insertMembershipNode(curr->right, node); 
    return curr; 
}

bool searchMembership(MembershipNode* curr, const char membershipSearch[]) {
    if (curr == NULL) return false;
    else if (strcmp(membershipSearch, curr->membership) < 0) return searchMembership(curr->left, membershipSearch);
    else if (strcmp(membershipSearch, curr->membership) > 0) return searchMembership(curr->right, membershipSearch);
    else if (strcmp(curr->membership, membershipSearch) == 0) return true;
}

CustomerNode* searchCustomer(CustomerNode* curr, const char nameSearch[]) {
    if (curr == NULL) return curr;
    else if (strcmp(nameSearch, curr->name) < 0) return searchCustomer(curr->left, nameSearch);
    else if (strcmp(nameSearch, curr->name) > 0) return searchCustomer(curr->right, nameSearch);
    else if (strcmp(curr->name, nameSearch) == 0) return curr;
}

CustomerNode* deleteCustomerNode(CustomerNode* curr,const char nameToBeDeleted[]) {
    if (curr == NULL) return curr;
    else if (strcmp(nameToBeDeleted, curr->name) < 0) curr->left = deleteCustomerNode(curr->left, nameToBeDeleted);
    else if (strcmp(nameToBeDeleted, curr->name) > 0) curr->right = deleteCustomerNode(curr->right, nameToBeDeleted);
    else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr); curr = NULL;
        }
        else if (curr->left != NULL && curr->right == NULL) {
            CustomerNode* temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
        }
        else if (curr->left == NULL && curr->right != NULL) {
            CustomerNode* temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        }
        else if (curr->left != NULL && curr->right != NULL) {
            CustomerNode* temp = curr->left;
            while (temp->right != NULL) temp = temp->right;
            strcpy(curr->name, temp->name);
            strcpy(curr->membership, temp->membership);
            curr->left = deleteCustomerNode(curr->left, temp->name);
        }
    }
    return curr;
}

void printMenu() {
    printf("Menu\n===================\n1. Add New Customer\n2. View Customer\n3. Delete Customer\n4. Exit\n");
}

int choose(int a, int b) {
    int choice = 0;
    do {
        printf("Choose: ");
        scanf("%d", &choice); getchar();
    } while (choice < a || choice > b);
    return choice;
}

void addNewCustomer() {
    char customerName[100] = {};
    char customerMembership[100] = {};
    do {
        printf("Customer's Name [3-50 characters]:\n");
        scanf("%[^\n]", &customerName); getchar();
    } while (strlen(customerName) < 3 || strlen(customerName) > 50);

    do {
        printf("Customer's Membership [Non-member | Bronze | Silver | Gold | Platinum]:\n");
        scanf("%s", &customerMembership); getchar();
    } while (!searchMembership(MembershipRoot, customerMembership));

    CustomerNode *tempSearcher = searchCustomer(CustomerRoot, customerName);
    if (tempSearcher != NULL && strcmp(tempSearcher->name, customerName) == 0)  {
        strcpy(tempSearcher->membership, customerMembership);
        printf("Customer already exists! Updated membership!\n");
    }
    else {
        CustomerRoot = insertCustomerNode(CustomerRoot, createCustomerNode(customerName, customerMembership));
    }
    return;
}

void viewCustomer(CustomerNode* curr, CustomerNode* root) {
    if (root == NULL) {
        printf("List is empty\n");
        return;
    }
    if (curr == NULL) return;
    viewCustomer(curr->left, root);
    printf("%s | %s\n", curr->name, curr->membership);
    viewCustomer(curr->right, root);
}

void deleteCustomer(CustomerNode* root) {
    if (root == NULL) {
        printf("The list is empty, nothing to be deleted!\n");
        return;
    }
    else {
        char customerName[100] = {};
        do {
            printf("Customer's Name [3-50 characters]:\n");
            scanf("%[^\n]", &customerName); getchar();
        } while (strlen(customerName) < 3 || strlen(customerName) > 50);

        CustomerRoot = deleteCustomerNode(CustomerRoot, customerName);
    }
}

int main() {
    MembershipRoot = insertMembershipNode(MembershipRoot, createMembershipNode("Non-member"));
    MembershipRoot = insertMembershipNode(MembershipRoot, createMembershipNode("Bronze"));
    MembershipRoot = insertMembershipNode(MembershipRoot, createMembershipNode("Silver"));
    MembershipRoot = insertMembershipNode(MembershipRoot, createMembershipNode("Gold"));
    MembershipRoot = insertMembershipNode(MembershipRoot, createMembershipNode("Platinum"));
    while (true) {
        printMenu();
        int choice = choose(1, 4);
        if (choice == 1) addNewCustomer();
        else if (choice == 2) viewCustomer(CustomerRoot, CustomerRoot);
        else if (choice == 3) deleteCustomer(CustomerRoot);
        else if (choice == 4) break;
    }
    return 0;
}