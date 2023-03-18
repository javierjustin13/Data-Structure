#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	char name[100];
	int value;
	Node *left, *right;
};

Node *createNode(const char name[], int value){
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->value = value;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node *insertNode(Node *curr, Node *newNode){
	if(curr == NULL) return newNode;
	else if(strcmp(newNode->name, curr->name) < 0) curr->left = insertNode(curr->left, newNode);
	else if(strcmp(newNode->name, curr->name) > 0) curr->right= insertNode(curr->right, newNode);
	return curr;
}

void preOrder(Node *curr){
	if(curr == NULL) return;
	printf("%s %d\n", curr->name, curr->value);
	preOrder(curr->left);
	preOrder(curr->right);
}

void inOrder(Node *curr){
	if(curr == NULL) return;
	inOrder(curr->left);
	printf("%s %d\n", curr->name, curr->value);
	inOrder(curr->right);
}

void postOrder(Node *curr){
	if(curr == NULL) return;
	postOrder(curr->left);
	postOrder(curr->right);
	printf("%s %d\n", curr->name, curr->value);
}

Node *searchNode(Node *curr, const char toBeSearch[]){
	if(curr == NULL) return NULL;
	else if(strcmp(toBeSearch, curr->name) < 0) return searchNode(curr->left, toBeSearch);
	else if(strcmp(toBeSearch, curr->name) > 0) return searchNode(curr->right, toBeSearch);
	else return curr;
}

Node *updateNode(Node *curr, const char toBeUpdated[], int newValue){
	if(curr == NULL) return NULL;
	else if(strcmp(toBeUpdated, curr->name) < 0) curr->left = updateNode(curr->left, toBeUpdated, newValue);
	else if(strcmp(toBeUpdated, curr->name) > 0) curr->right = updateNode(curr->right, toBeUpdated, newValue);
	else curr->value = newValue;
	return curr;
}

Node *findPredecessor(Node *curr){
	Node *predecessor = curr->left;
	while(predecessor->right != NULL) predecessor = predecessor->right;
	return predecessor;
}

Node *findSuccessor(Node *curr){
	Node *successor = curr->right;
	while(successor->left != NULL) successor = successor->left;
	return successor;
}

Node *deleteNode(Node *curr, const char toBeDeleted[]){
	if(curr == NULL) return curr;
	else if(strcmp(toBeDeleted, curr->name) < 0) curr->left = deleteNode(curr->left, toBeDeleted);
	else if(strcmp(toBeDeleted, curr->name) > 0) curr->right = deleteNode(curr->right, toBeDeleted);
	else{
		if(curr->left == NULL && curr->right == NULL){
			free(curr);
			curr = NULL;
		}
		else if(curr->left != NULL && curr->right == NULL){ //HAVE LEFT CHILD
			Node *temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
		}
		else if(curr->left == NULL && curr->right != NULL){ //HAVE RIGHT CHILD
			Node *temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
		}
		else{ //HAVE BOTH CHILD
			Node *temp = findPredecessor(curr);
			printf("Predecessor : %s %d\n", temp->name, temp->value);
			strcpy(curr->name, temp->name);
			curr->value = temp->value;
			curr->left = deleteNode(curr->left, temp->name);
			
//			Node *temp = findSuccessor(curr);
//			printf("Successor : %s %d\n", temp->name, temp->value);
//			strcpy(curr->name, temp->name);
//			curr->value = temp->value;
//			curr->right = deleteNode(curr->right, temp->name);
		}
	}
	return curr;
}

int main(){
	Node *root = NULL;	
	root = insertNode(root, createNode("Justin", 30));
	root = insertNode(root, createNode("Jacky", 15));
	root = insertNode(root, createNode("Hans", 45));
	root = insertNode(root, createNode("Stephen", 20));
	root = insertNode(root, createNode("Bella", 13));
	root = updateNode(root, "Hans", 69);
	root = deleteNode(root, "Justin");
	printf("\nPreOrder\n"); preOrder(root);
	printf("\nInOrder\n"); inOrder(root);
	printf("\nPostOrder\n"); postOrder(root);
	Node *nodeSearched = searchNode(root, "Eva");
	if(nodeSearched == NULL) printf("\nNot found!\n");
	else printf("\n%s %d is found!\n", nodeSearched->name, nodeSearched->value);
	return 0;
}
