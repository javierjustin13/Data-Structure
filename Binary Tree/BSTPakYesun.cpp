#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data {
	int val;
	struct data* left;
	struct data* right;
};

struct data* root = NULL;

struct data *createData(int val){
	struct data *node = (struct data*) malloc(sizeof(struct data));
	node->val = val;
	node->left = node->right = NULL;
	return node;
}

void insert(struct data *curr, int newVal){
	if(!root){
		root = createData(newVal);
	} else{
		if(newVal < curr->val && curr->left == NULL){ // curr->left == NULL untuk mengecek apakah sudah ada data atau belum
			curr->left = createData(newVal);
			return;
		} else if(newVal > curr->val && curr->right == NULL){ // curr->right == NULL untuk mengecek apakah sudah ada data atau belum
			curr->right = createData(newVal);
			return; 
		} else if(newVal < curr->val){ //
			insert(curr->left, newVal);  
		} else if(newVal > curr->val){
			insert(curr->right, newVal);
		} else{
			printf("The data you insert is already exist\n");
		}
	}
}

void find(struct data *curr, int findVal){
	// Check antara ROOT NULL atau tidak dan untuk berhenti kalau udah di ujung 
	if (curr == NULL) {
		printf("\n%d is NOT found\n", findVal);
		return;
	}
	if (curr->val == findVal) {
		printf("\n%d is found\n", findVal);
		return;
	}
	if (findVal < curr->val) {
		find(curr->left, findVal);
	} else {
		find(curr->right, findVal);
	}
}

struct data* delRecursive(struct data* parent, struct data* NodeToDel) {
	// check if the node is a leaf node
	if (NodeToDel->left == NULL && NodeToDel->right == NULL) {
		if(root == NodeToDel) root = NULL;
		else if(parent->left == NodeToDel) parent->left = NULL;
		else if(parent->right == NodeToDel) parent->right = NULL;
		free(NodeToDel);
		return NULL;
	}
	// check if the node has only left child
	else if (NodeToDel->left != NULL && NodeToDel->right == NULL) {
		struct data* temp = NodeToDel->left;
		if(NodeToDel->val < parent->val) parent->left = temp;
		else parent->right = temp;
		return temp;
	}
	// check if the node has only right child
	else if (NodeToDel->left == NULL && NodeToDel->right != NULL) {
		struct data* temp = NodeToDel->right;
		if (NodeToDel->val < parent->val) parent->left = temp;
		else parent->right = temp;
		return temp;
	}
	// check if node has both left and right child
	else {
		struct data* temp = NodeToDel->left;
		struct data* tParent = NodeToDel;
		while (temp->right != NULL) {
			tParent = temp;
			temp = temp->right;
		}
		NodeToDel->val = temp->val;
		if (tParent->left == temp) tParent->left = temp->left; // if temp is the left child of tParent
		else tParent->right = temp->left; // if temp is the right child of tParent
		return NodeToDel;
		// NodeToDel->val = temp->val;
		// temp = delRecursive(tParent, temp);
		// return NodeToDel;
	}
}
struct data* parent = NULL;
void del(struct data* curr, int delVal) {
	if (curr == NULL) {
		printf("\n%d is NOT available to delete\n", delVal);
		return;
	}
	if (curr->val == delVal) {
		curr = delRecursive(parent, curr);
		return;
	}
	if (delVal < curr->val) {
		parent = curr;
		del(curr->left, delVal);
	}
	else if (delVal > curr->val) {
		parent = curr;
		del(curr->right, delVal);
	}
}

void displayInfix(struct data* curr) {
	if(curr->left != NULL) displayInfix(curr->left);
	printf("%d ", curr->val);
	if(curr->right != NULL) displayInfix(curr->right);
	
//	if(curr != NULL){
//		displayInfix(curr->left);
//		printf("%d ", curr->val);
//		displayInfix(curr->right);
//	}
}

int main(){
	insert(root, 10);
	insert(root, 20);
	insert(root, 9);
	insert(root, 5);
	insert(root, 11);
	insert(root, 1);
	insert(root, 12);
	insert(root, 25);
	insert(root, 30);
	insert(root, 35);
	insert(root, 40);
	
	displayInfix(root);
	printf("\n");

	del(root, 20);
	displayInfix(root);
	printf("\n");
	
	del(root, 10);
	displayInfix(root);
	printf("\n");
	
	del(root, 30);
	displayInfix(root);
	printf("\n");
	// del(root, 10);

	return 0;
}
