#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

struct Node{
	char name[101];
	long long price;
	char category[101];
	char avail[101];
	
	int height;
	Node *left;
	Node *right;
};

Node *root = NULL;

int max(int a, int b){
	return (a > b) ? a : b;
}

int getHeight(Node *curr){
	if (curr == NULL) return 0;
	return curr->height;
}

int calculateHeight(Node *curr){
	return 1 + max(getHeight(curr->left), getHeight(curr->right));
}

int getBF(Node *curr){
	if (curr == NULL) return 0;
	return getHeight(curr->left) - getHeight(curr->right);
}

Node *leftRotate(Node *curr){
	Node *newParent = curr->right;
	curr->right = newParent->left;
	newParent->left = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Node *rightRotate(Node *curr){
	Node *newParent = curr->left;
	curr->left = newParent->right;
	newParent->right = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Node *createNode(const char name[], long long price, const char category[], const char avail[]){
	Node *newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name); 
	strcpy(newNode->category, category); 
	strcpy(newNode->avail, avail); 
	newNode->price = price;
	newNode->left = newNode->right = NULL;
	newNode->height = 1;
	
	return newNode;
}

Node *insertNode(Node *curr, Node *newNode){
	if(curr == NULL) return newNode;
	else if(strcmp(newNode->name, curr->name) < 0) curr->left = insertNode(curr->left, newNode);
	else if(strcmp(newNode->name, curr->name) > 0) curr->right = insertNode(curr->right, newNode);
	else return curr;
	
	curr->height = calculateHeight(curr);
	int balance = getBF(curr);
	
	if(balance > 1 && getBF(curr->left) >= 0) return rightRotate(curr);
	if(balance < -1 && getBF(curr->right) <= 0) return leftRotate(curr);
	if(balance > 1 && getBF(curr->left) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	if(balance < -1 && getBF(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

Node *deleteNode(Node *curr, const char name[]){
	if(curr == NULL) return NULL;
	else if(strcmp(name, curr->name) < 0) curr->left = deleteNode(curr->left, name);
	else if(strcmp(name, curr->name) > 0) curr->right = deleteNode(curr->right, name);
	else{
		if(curr->left == NULL || curr->right == NULL){
			Node *temp = (curr->left) ? curr->left : curr->right;
			if(temp == NULL){
				temp = curr;
				curr = NULL;
			}
			else{
				*curr = *temp;
			}
			free(temp);
		}
		else{
			Node *temp = curr->left;
			while(temp->right != NULL) temp = temp->right;
			strcpy(curr->name, temp->name);
			strcpy(curr->category, temp->category);
			strcpy(curr->avail, temp->avail);
			curr->price = temp->price;
			
			curr->left = deleteNode(curr->left, temp->name);
		}
	}
	
	if(curr == NULL) return NULL;
	
	curr->height = calculateHeight(curr);
	int balance = getBF(curr);
	
	if(balance > 1 && getBF(curr->left) >= 0) return rightRotate(curr);
	if(balance < -1 && getBF(curr->right) <= 0) return leftRotate(curr);
	if(balance > 1 && getBF(curr->left) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	if(balance < -1 && getBF(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

void preOrder(Node *curr){
	if(curr != NULL){
		printf("%s %lld %s %s\n", curr->name, curr->price, curr->category, curr->avail);
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void inOrder(Node *curr){
	if(curr != NULL){
		inOrder(curr->left);
		printf("%s %lld %s %s\n", curr->name, curr->price, curr->category, curr->avail);
		inOrder(curr->right);
	}
}

void postOrder(Node *curr){
	if(curr != NULL){
		postOrder(curr->right);
		postOrder(curr->left);
		printf("%s %lld %s %s\n", curr->name, curr->price, curr->category, curr->avail);
	}
}

Node *isPriceThere = NULL; 
void searchPrice(Node *curr, long long price){
	if(curr != NULL){
		if(curr->price == price){
			isPriceThere = curr;
			return;
		}
		searchPrice(curr->left, price);
		searchPrice(curr->right, price);
	}
}

int lastInsert = 1;
char ID[10] = {};
void randomID(){
	srand(time(NULL));
	sprintf(ID, "%c%c%c%03d", rand() % 26 + 'A', rand() % 26 + 'A', rand() % 26 + 'A', lastInsert);
}

int inputInt(int a, int b){
	char string[100] = {};
	bool check = true;
	int res;
	do{
		if(check == false){
			printf("Wrong input!\n");
		}
		check = true;
		scanf("%[^\n]", string); getchar();
		for(int i = 0; i < strlen(string); i++){
			if(!isdigit(string[i])){
				check = false;
				break;
			}
		}
		if(check){
			res = atoi(string);
		}
		else{
			res = a-1;
		}
		check = false;
	}while(res < a || res > b);
	
	return res;
}

int main(){
	root = insertNode(root, createNode("A", 10, "Apapun", "Ada"));
	root = insertNode(root, createNode("B", 11, "Apapun", "Ada"));
	root = insertNode(root, createNode("D", 12, "Apapun", "Ada"));
	root = insertNode(root, createNode("F", 13, "Apapun", "Ada"));
	root = insertNode(root, createNode("G", 14, "Apapun", "Ada"));
	root = insertNode(root, createNode("I", 15, "Apapun", "Ada"));
	root = insertNode(root, createNode("J", 16, "Apapun", "Ada"));
	inOrder(root);
	printf("\n");
	root = deleteNode(root, "B");
	inOrder(root);
	printf("\n");
	
	searchPrice(root, 12);
	if(isPriceThere != NULL){
		isPriceThere->price = 30;
	} 
	printf("\n");
	
	inOrder(root);
	
	randomID();
	printf("%s\n", ID);
	
	int aku = inputInt(1,3);
	
	return 0;
}
