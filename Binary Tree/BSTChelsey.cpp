#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	char name[100];
	int value;
	struct Node *left, *right;
};

struct Node *createFood(const char name[], int value){
	struct Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->value = value;
	newNode->right = newNode->left = NULL;
	return newNode;
}

struct Node* insertNode(struct Node *curr, struct Node *newNode){
	if(curr == NULL) return newNode;
	else if(strcmp(newNode->name, curr->name) < 0) curr->left = insertNode(curr->left, newNode);
	else if(strcmp(newNode->name, curr->name) > 0) curr->right = insertNode(curr->right, newNode);
	return curr;
} 

void preOrder(struct Node *curr){
	if(curr == NULL) return;
	printf("%s %d\n", curr->name, curr->value);
	preOrder(curr->left);
	preOrder(curr->right);
}

void inOrder(struct Node *curr){
	if(curr == NULL) return;
	inOrder(curr->left);
	printf("%s %d\n", curr->name, curr->value);
	inOrder(curr->right);
}

void postOrder(struct Node *curr){
	if(curr == NULL) return;
	postOrder(curr->left);
	postOrder(curr->right);
	printf("%s %d\n", curr->name, curr->value);
}

struct Node *findPredecessor(struct Node *curr){
	struct Node *predecessor = curr->left;
	while(predecessor->right != NULL) predecessor = predecessor->right;
	return predecessor;
}

struct Node *findSuccessor(struct Node *curr){
	struct Node *successor = curr->right;
	while(successor->left != NULL) successor = successor->left;
	return successor;
}

struct Node *deleteNode(struct Node *curr, const char name[]){
	if(curr == NULL) return NULL;
	else if(strcmp(name, curr->name) < 0) curr->left = deleteNode(curr->left, name);	
	else if(strcmp(name, curr->name) > 0) curr->right = deleteNode(curr->right, name);
	else if(strcmp(name, curr->name) == 0){
		if(curr->left == NULL && curr->right == NULL){
			free(curr);
			curr = NULL;
		}
		else if(curr->left != NULL && curr->right == NULL){
			struct Node* temp = curr->left;
			strcpy(curr->name, temp->name);
			curr->value = temp->value;
			curr->left = deleteNode(curr->left, temp->name);
		} 
		else if(curr->left == NULL && curr->right != NULL){
			struct Node* temp = curr->right;
			strcpy(curr->name, temp->name);
			curr->value = temp->value;
			curr->right = deleteNode(curr->right, temp->name);
		}
		else if(curr->left != NULL && curr->right != NULL){
//			struct Node *temp = findPredecessor(curr);
//			printf("Predecessor : %s\n", temp->name);
//			strcpy(curr->name, temp->name);
//			curr->value = temp->value;
//			curr->left = deleteNode(curr->left, temp->name);
			
			struct Node *temp = findSuccessor(curr);
			printf("Successor : %s\n", temp->name);
			strcpy(curr->name, temp->name);
			curr->value = temp->value;
			curr->right = deleteNode(curr->right, temp->name);
		}
	}	
	return curr;
}

struct Node* searchNode(struct Node *curr, const char name[]){
	if(curr == NULL) return NULL;
	else if(strcmp(name, curr->name) < 0) return searchNode(curr->left, name);	
	else if(strcmp(name, curr->name) > 0) return searchNode(curr->right, name);
	else{
		return curr;
	}
	return NULL;
}

struct Node* updateNode(struct Node *curr, const char name[], int newValue){
	if(curr == NULL) return NULL;
	else if(strcmp(name, curr->name) < 0) curr->left = updateNode(curr->left, name, newValue);	
	else if(strcmp(name, curr->name) > 0) curr->right = updateNode(curr->right, name, newValue);
	else{
		curr->value = newValue;
	}
	return curr;
}

int calculateHeight(struct Node *curr){
	if(curr == NULL) return 0;
	int leftHeight = calculateHeight(curr->left);
	int rightHeight = calculateHeight(curr->right);
	if(leftHeight >= rightHeight) return leftHeight + 1;
	else return rightHeight + 1;
}


int main(){
	struct Node *root = NULL;
	root = insertNode(root, createFood("Sate Padang", 34));
	root = insertNode(root, createFood("Ayam Bakar", 30));
	root = insertNode(root, createFood("Telur Bebek", 69));
	root = insertNode(root, createFood("Udang Goreng", 20));
	root = insertNode(root, createFood("Nasi Goreng", 20));
	root = insertNode(root, createFood("Pudding", 20));
	root = insertNode(root, createFood("Ramen", 20));
	root = insertNode(root, createFood("Asinan", 20));
	
	root = deleteNode(root, "Sate Padang");
	
	struct Node *toSearch = searchNode(root, "Pudding");
	if(toSearch == NULL) printf("Not found!\n");
	else printf("Found : %s %d\n", toSearch->name, toSearch->value);

	root = updateNode(root, "Ramen", 100);

	
	printf("\npreOrder :\n");
	preOrder(root);
	printf("\ninOrder :\n");
	inOrder(root);
	printf("\npostOrder : \n");
	postOrder(root);
	return 0;
}
