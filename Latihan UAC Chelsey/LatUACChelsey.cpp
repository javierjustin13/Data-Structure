#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

struct Game{
	char title[30];
	char genre[30];
	int stock;
	
	int height;
	
	Game *left, *right; 
};

int max(int a, int b){
	return a < b ? a : b;
}

int getHeight(Game *curr){
	if(curr == NULL) return NULL;
	return curr->height;
}

int calculateHeight(Game *curr){
	return max(getHeight(curr->left), getHeight(curr->right)) + 1;
}

int getBF(Game *curr){
	if(curr == NULL) return NULL;
	return getHeight(curr->left) - getHeight(curr->right);
}

Game *leftRotate(Game *curr){
	Game *newParent = curr->right;
	curr->right = newParent->left;
	newParent->left = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Game *rightRotate(Game *curr){
	Game *newParent = curr->left;
	curr->left = newParent->right;
	newParent->right = curr;
	
	curr->height = calculateHeight(curr);
	newParent->height = calculateHeight(newParent);
	
	return newParent;
}

Game *createGame(const char title[], const char genre[], int stock){
	Game *newGame = (Game*)malloc(sizeof(Game));
	strcpy(newGame->title, title);
	strcpy(newGame->genre, genre);
	newGame->stock = stock;
	newGame->height = 1;
	newGame->left = newGame->right = NULL;
	
	return newGame;
}

Game *insertGame(Game *curr, Game *newGame){
	if(curr == NULL) return newGame;
	else if(strcmp(newGame->title, curr->title) > 0) curr->right = insertGame(curr->right, newGame);
	else if(strcmp(newGame->title, curr->title) < 0) curr->left = insertGame(curr->left, newGame);
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

Game *deleteGame(Game *curr, const char title[]){
	if(curr == NULL) return NULL;
	else if(strcmp(title, curr->title) < 0) curr->left = deleteGame(curr->left, title);
	else if(strcmp(title, curr->title) > 0) curr->right = deleteGame(curr->right, title);
	else{
		
		Game *newCurr = (curr->left) ? curr->left : curr->right;
		
		if(newCurr == NULL){
			free(curr);
			curr = NULL;
		}
		else if(curr->left == NULL|| curr->right == NULL){
			free(curr);
			curr = newCurr;
		}
		else{
			Game *temp = curr->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			
			strcpy(curr->title, temp->title);
			strcpy(curr->genre, temp->genre);
			curr->stock = temp->stock;
			
			curr->left = deleteGame(curr->left, temp->title);
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

void inOrder(Game *curr){
	if(curr == NULL) return;
	inOrder(curr->left);
	printf("%s %s %d\n", curr->title, curr->genre, curr->stock);
	inOrder(curr->right);
}

void preOrder(Game *curr){
	if(curr == NULL) return;
	printf("%s %s %d\n", curr->title, curr->genre, curr->stock);
	preOrder(curr->left);
	preOrder(curr->right);
}

void postOrder(Game *curr){
	if(curr == NULL) return;
	postOrder(curr->left);
	postOrder(curr->right);
	printf("%s %s %d\n", curr->title, curr->genre, curr->stock);
}

Game *dummyData(Game *root){
	root = insertGame(root, createGame("Stardew Valley", "Adventure", 10));
	root = insertGame(root, createGame("Genshin Impact", "Adventure", 10));
	root = insertGame(root, createGame("Valorant", "Adventure", 10));
	return root;
}

Game *searchGame(Game *root, const char title[]){
	if(root == NULL) return NULL;
	else if(strcmp(title, root->title) < 0) return searchGame(root->left, title);
	else if(strcmp(title, root->title) > 0) return searchGame(root->right, title);
	else return root;
}

Game *insertMenu(Game *root){
	char title[50];
	do{
		printf("Insert title[5 - 25 char]: ");
		scanf("%[^\n]", &title); getchar();
	}while(strlen(title) < 5 || strlen(title) > 25 || searchGame(root, title) != NULL);
	
	char genre[50];
	do{
		printf("Insert genre[]: ");
		scanf("%[^\n]", &genre); getchar();
	}while(strcmp(genre, "Action") && strcmp(genre, "Adventure") && strcmp(genre, "RPG") && strcmp(genre, "Card Game"));
	
	int stock;
	do{
		printf("Insert stock[must be at least 1]:");
		scanf("%d", &stock); getchar();
	}while(stock < 1);
	
//	char gameId[5];
//	sprintf(gameId, "GA%03d", countID);
//	countID++; (countID global)
	
	root = insertGame(root, createGame(title, genre, stock));
	return root;
}

void viewMenu(Game *root){
	if(root == NULL){
		printf("There is no data!\n");
		return;	
	} 
	preOrder(root);
}

Game *updateMenu(Game *root){
	char title[100];
	do{
		printf("Insert title[5 - 25 char]: ");
		scanf("%[^\n]", &title); getchar();
	}while(strlen(title) < 5 || strlen(title) > 25);
	
	Game *toUpdate = searchGame(root, title);
	if(toUpdate == NULL){
		printf("Not Found!\n");
		return root;
	}
	
	char opt[100];
	
	do{
		printf("Input option [add | remove]: ");
		scanf("%[^\n]", &opt); getchar();
	}while(strcmpi(opt, "add") != 0 && strcmpi(opt, "remove") != 0);
	
	int qty;
	while(true){
		printf("Input qty: ");
		scanf("%d", &qty); getchar();
		if(strcmpi(opt, "remove") == 0 && qty >= 1 && qty <= toUpdate->stock){
			break;
		}
		else if(strcmpi(opt, "add") == 0 && qty >= 1){
			break;
		}
	}
	
	if(strcmpi(opt, "remove") == 0){
		if(qty == toUpdate->stock){
			root = deleteGame(root, toUpdate->title);
		}
		else{
			toUpdate->stock -= qty;
		}
	}
	else{
		toUpdate->stock += qty;
	}
	
	return root;
}

Game *mainMenu(Game *root){
	int opt;
	while(true){
		printf("1. Insert\n2. View\n3. Update\n4. Exit\n>> ");
		scanf("%d", &opt); getchar();
		if(opt == 1){
			root = insertMenu(root);
		}
		else if(opt == 2){
			viewMenu(root);
		}
		else if(opt == 3){
			root = updateMenu(root);
		}
		else if(opt == 4){
			return root;
		}
	}
}

int main(){
	Game *root = NULL;
	root = dummyData(root);
	root = mainMenu(root);
	
	return 0;
}
