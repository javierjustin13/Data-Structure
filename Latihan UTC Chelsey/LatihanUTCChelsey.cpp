#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define SIZE 1007

struct Book{
	char id[100];
	char title[100];
	char author[100];
	char isbn[100];
	int page;
	Book *next;
};

struct Table{
	Book *head, *tail;
}*table[SIZE];

int lastInsert = 1;

int hash(const char id[]){
	int key = 0;
	for(int i = 0; i < strlen(id); i++){
		key += id[i];
	}
	return key % SIZE;
}

void insert(Book* newBook){
	int key = hash(newBook->id);
	if(table[key]->head == NULL){
		table[key]->head = table[key]->tail = newBook;
	}
	else{
		table[key]->tail->next = newBook;
		table[key]->tail = newBook;
	}
}

Book* createBook(const char* id, const char* title, const char* author, const char* isbn, int page){
	Book *newBook = (Book*)malloc(sizeof(Book));
	strcpy(newBook->id, id);
	strcpy(newBook->title, title);
	strcpy(newBook->author, author);
	strcpy(newBook->isbn, isbn);
	newBook->page = page;
	newBook->next = NULL;
	return newBook;
}

void initializeTable(){
	for(int i = 0; i < SIZE; i++){
		table[i] = (Table*)malloc(sizeof(Table));
		table[i]->head = table[i]->tail = NULL;
	}
	return;
}

int choice(int a, int b){
	int result;
	do{
		printf(">> ");
		scanf("%d", &result); getchar();
	}while(result < a || result > b);
	return result;
}

void pressEnter(){
	printf("Press Enter to continue ...\n"); getchar();
}

Book* searchBookID(const char id[]){
	for(int i = 0; i < SIZE; i++){
		Book *curr = table[i]->head;
		while(curr != NULL){
			if(strcmp(curr->id, id) == 0){
				return curr;
			}
			curr = curr->next;
		}
	}
	return NULL;
}

void deleteBook(char id[]){
	int key = hash(id);
	Book *curr = table[key]->head;
	if(strcmp(curr->id, id) == 0){
		table[key]->head = curr->next;
		free(curr);
		curr = NULL;
		return;
	}
	while(strcmp(curr->next->id, id) != 0){
		curr = curr->next;
	}
	Book *del = curr->next;
	curr->next = del->next;
	free(del);
	del = NULL;
}

void viewBook(){
	int emptyTable = 0;
	for(int i = 0; i < SIZE; i++){
		if(table[i]->head == NULL && table[i]->tail == NULL) emptyTable += 1;
	}
	if(emptyTable == SIZE){
		printf("There is no book(s)!\n");
		return;
	}
	puts("================================================================================================================================");
  	puts("| Book ID                  | Book Title                             | Book Author             | ISBN             | Page Number |");
  	puts("================================================================================================================================");
  	for (int i = 0; i < SIZE; i++) {
   		if (table[i]->head != NULL) {
    		Book* curr = table[i]->head;
    		while (curr != NULL) {
     			printf("| %-24s | %-38s | %-23s | %-16s | %-11d |\n", curr->id, curr->title, curr->author, curr->isbn, curr->page);
     			puts("================================================================================================================================");
     			curr = curr->next;
     		}
     	}
    }
}

void removeBook(){
	char id[100];
	viewBook();
	printf("Input book id to delete : ");
	scanf("%[^\n]", &id); getchar();
	Book *del = searchBookID(id);
	if(del == NULL){
		printf("Book not found!\n");
		return;
	}
	printf("Book ID : %s\n", del->id);
	printf("Book Title : %s\n", del->title);
	printf("Book Author : %s\n", del->author);
	printf("Book ISBN : %s\n", del->isbn);
	printf("Page Number : %d\n", del->page);
	
	char yn;
	do{
		printf("Are you sure [y|n]? ");
		scanf("%c", &yn); getchar();
	}while(yn != 'y' && yn != 'n');
	
	if(yn == 'n') return;
	else if(yn == 'y'){
		deleteBook(del->id);
		printf("Delete success!\n");
	}
	
}

bool isNumeric(const char isbn[]){
	for(int i = 0; i < strlen(isbn); i++){
		if(isbn[i] < '0' || isbn[i] > '9') return true;
	}
	return false;
}

bool checkMrMrs(const char author[]){
//	if(author[0] == 'M' && author[1] == 'r' && author[2] == '.' && author[3] == ' '){
//		return false;
//	}
//	else if(author[0] == 'M' && author[1] == 'r' && author[2] == 's' && author[3] == '.' && author[4] == ' '){
//		return false;
//	}
//	return true;

	if(strncmp(author, "Mr. ", 4) == 0 || strncmp(author, "Mrs. ", 5) == 0) return false;
	else return true;
}

bool searchBookTitle(const char title[]){
	for(int i = 0; i < SIZE; i++){
		Book *curr = table[i]->head;
		while(curr != NULL){
			if(strcmp(curr->title, title) == 0){
				return true;
			}
			curr = curr->next;
		}
	}
	return false;
}

void insertBook(){
	char title[100], id[100], author[100], isbn[100];
	int page;
	do{
		printf("Input book title[5-50][unique] : ");
		scanf("%[^\n]", &title); getchar();
		if(searchBookTitle(title)) printf("The book title already exists!\n");
	}while(strlen(title) < 5 || strlen(title) > 50 || searchBookTitle(title));
	
	do{
		printf("Input author name[3-25][Mr. | Mrs. ] : ");
		scanf("%[^\n]", &author); getchar();
	}while(strlen(author) < 3 || strlen(author) > 25 || checkMrMrs(author));
	
	do{
		printf("Input ISBN[10-13][numeric] : ");
		scanf("%[^\n]", &isbn); getchar();
	}while(strlen(isbn) < 10 || strlen(isbn) > 13 || isNumeric(isbn));
	
	do{
		printf("Input page number[>= 16] : ");
		scanf("%d", &page); getchar();
	}while(page < 16);
	
	sprintf(id, "B%05d-%s-%c%c", lastInsert, isbn, toupper(title[0]), toupper(author[0]));
	lastInsert += 1;
	insert(createBook(id, title, author, isbn, page));
}

void printMenu(){
	printf("Bluejack Library\n");
	printf("===================\n");
	printf("1. View Book\n");
	printf("2. Insert Book\n");
	printf("3. Remove Book\n");
	printf("4. Exit\n");
}

int main(){
	initializeTable();
	while(true){
		printMenu();
		int choiceMenu = choice(1, 4);
		if(choiceMenu == 1){
			viewBook();
			pressEnter();
		}
		else if(choiceMenu == 2){
			insertBook();
			pressEnter();
		}
		else if(choiceMenu == 3){
			removeBook();
			pressEnter();
		}
		else if(choiceMenu == 4){
			break;
		}
	}
	return 0;
}
