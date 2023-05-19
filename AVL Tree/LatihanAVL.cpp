#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct Node{
	int key;
	char color[10];
	int total;
	
	int height;
	Node *right;
	Node *left;
};

Node *root = NULL;

int max(int a, int b){
	return (a > b) ? a : b;
}

int getHeight(Node *curr){
	if(curr == NULL) return 0;
	return curr->height;
}

int calculateHeight(Node *curr){
	return 1 + max(getHeight(curr->left), getHeight(curr->right));
}

int getBF(Node *curr){
	if(curr == NULL) return 0;
	return getHeight(curr->left) - getHeight(curr->right);
}

int getTotal(Node *curr){
	if(curr == NULL) return 0;
	return curr->total;
}

int calculateTotal(Node *curr){
	return curr->key + getTotal(curr->left) + getTotal(curr->right);
}

void updateColor(Node *curr){
	if(getTotal(curr->right) > getTotal(curr->left)) strcpy(curr->color, "pink");
	else if(getTotal(curr->right) < getTotal(curr->left)) strcpy(curr->color, "yellow");
	else if(getTotal(curr->right) == getTotal(curr->left)) strcpy(curr->color, "white");
}

Node *leftRotate(Node *curr){
	Node *newParent = curr->right;
	curr->right = newParent->left;
	newParent->left = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	curr->total = calculateTotal(curr);
	newParent->total = calculateTotal(newParent);
	
	updateColor(curr);
	updateColor(newParent);
	
	return newParent;
}

Node *rightRotate(Node *curr){
	Node *newParent = curr->left;
	curr->left = newParent->right;
	newParent->right = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	curr->total = calculateTotal(curr);
	newParent->total = calculateTotal(newParent);
	
	updateColor(curr);
	updateColor(newParent);
	
	return newParent;
}

Node *createNode(Node *curr, int key){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->height = 1;
	newNode->left = newNode->right = NULL;
	newNode->total = key;
	strcpy(newNode->color, "white");
	
	return newNode;
}

Node *insertNode(Node *curr, int key){
	if(curr == NULL) return createNode(curr, key);
	else if(key < curr->key) curr->left = insertNode(curr->left, key);
	else if(key > curr->key) curr->right = insertNode(curr->right, key);
	else return curr;
	
	int balance = getBF(curr);
	curr->height = calculateHeight(curr);
	curr->total = calculateTotal(curr);	
	updateColor(curr);
	
	if(balance > 1 && getBF(curr->left) >= 0) return rightRotate(curr);
	if(balance > 1 && getBF(curr->left) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	if(balance < -1 && getBF(curr->right) <= 0) return leftRotate(curr);
	if(balance < -1 && getBF(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
}

Node *deleteNode(Node *curr, int key){
	if (curr == NULL) return NULL;
	else if(key < curr->key) curr->left = deleteNode(curr->left, key);
	else if(key > curr->key) curr->right = deleteNode(curr->right, key);
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
			curr->key = temp->key;
			curr->left = deleteNode(curr->left, temp->key);
		}
	}
	
	if(curr == NULL) return NULL;
	
	int balance = getBF(curr);
	curr->height = calculateHeight(curr);
	curr->total = calculateTotal(curr);	
	updateColor(curr);
	
	if(balance > 1 && getBF(curr->left) >= 0) return rightRotate(curr);
	if(balance > 1 && getBF(curr->left) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	if(balance < -1 && getBF(curr->right) <= 0) return leftRotate(curr);
	if(balance < -1 && getBF(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	} 	
	return curr;
}

void preOrder(Node *curr){
	if(curr != NULL){
		printf("%d %s\n", curr->key, curr->color);
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void inOrder(Node *curr){
	if(curr != NULL){
		inOrder(curr->left);
		printf("%d %s\n", curr->key, curr->color);
		inOrder(curr->right);
	}
}

void postOrder(Node *curr){
	if(curr != NULL){
		postOrder(curr->left);
		postOrder(curr->right);
		printf("%d %s\n", curr->key, curr->color);
	}
}

Node *searchNode(Node *curr, int key){
	if(curr == NULL) return NULL;
	else if(key < curr->key) return searchNode(curr->left, key);
	else if(key > curr->key) return searchNode(curr->right, key);
	else return curr;
}

int pink = 0;
int yellow = 0;
int white = 0;

void countColorChildren(Node *curr, int value){
	if(curr != NULL){
		if(curr->key != value){
			if(strcmp(curr->color, "pink") == 0) pink += 1;
			else if(strcmp(curr->color, "white") == 0) white += 1;
			else if(strcmp(curr->color, "yellow") == 0) yellow += 1;
		}
		countColorChildren(curr->left, value);
		countColorChildren(curr->right, value);
	}
}

void describeNode(int numberToBeDesrcibed){
	Node *toBeDesrcibed = searchNode(root, numberToBeDesrcibed);
	if(toBeDesrcibed == NULL) printf("The number does not exist\n");
	else{
		printf("value : %d\n", toBeDesrcibed->key);
		printf("keyword : %s\n", toBeDesrcibed->color);
		pink = yellow = white = 0;
		countColorChildren(toBeDesrcibed, numberToBeDesrcibed);
		printf("number of pink children: %d\n", pink);
		printf("number of white children: %d\n", white);
		printf("number of yellow children: %d\n", yellow);
	}
}


int main(){
	int N;
	scanf("%d", &N); getchar();
	for(int i = 0; i < N; i++){
		char command[20];
		scanf("%s", &command); getchar();
		
		if(strcmp(command, "INSERT") == 0){
			int numberToBeInserted;
			scanf("%d", &numberToBeInserted); getchar();
			root = insertNode(root, numberToBeInserted);
		}
		
		else if(strcmp(command, "VIEW") == 0){
			inOrder(root);
		}
		
		else if(strcmp(command, "DESCRIBE") == 0){
			int numberToBeDescribed;
			scanf("%d", &numberToBeDescribed); getchar();
			describeNode(numberToBeDescribed);
		}
		
		else if(strcmp(command, "DELETE") == 0){
			int numberToBeDeleted;
			scanf("%d", &numberToBeDeleted); getchar();
			root = deleteNode(root, numberToBeDeleted);
			inOrder(root);
		}
	}
	return 0;
}

