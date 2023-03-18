#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Game {
    char name[100];
    int rating;
    int hoursPlayed;
    Game* left, * right;
};

struct GameQueue {
    char name[100];
    int rating;
    int hoursPlayed;
    GameQueue* next;
};

Game* root = NULL;
GameQueue* head = NULL, * tail = NULL;

Game* createGame(const char name[], int rating, int hoursPlayed) {
    Game* newGame = (Game*)malloc(sizeof(Game));
    strcpy(newGame->name, name);
    newGame->rating = rating;
    newGame->hoursPlayed = hoursPlayed;
    newGame->left = newGame->right = NULL;
    return newGame;
}

GameQueue* createGameQueue(const char name[], int rating, int hoursPlayed) {
    GameQueue* newGame = (GameQueue*)malloc(sizeof(GameQueue));
    strcpy(newGame->name, name);
    newGame->rating = rating;
    newGame->hoursPlayed = hoursPlayed;
    newGame->next = NULL;
    return newGame;
}

Game* insertGame(Game* curr, Game* newGame) {
    if (curr == NULL) return newGame;
    else if (strcmpi(newGame->name, curr->name) < 0) curr->right = insertGame(curr->right, newGame);
    else if (strcmpi(newGame->name, curr->name) > 0) curr->left = insertGame(curr->left, newGame);
    return curr;
}

void pushPriorityByRating(GameQueue* newGameQueue) {
    if(head == NULL && tail == NULL) {
        head = tail = newGameQueue;
    }
    else if (head->rating < newGameQueue->rating) {
        newGameQueue->next = head;
        head = newGameQueue;
    }
    else if (tail->rating >= newGameQueue->rating) {
        tail->next = newGameQueue;
        tail = newGameQueue;
    }
    else {
        GameQueue* curr = head;
        while (curr->next != NULL && curr->next->rating > newGameQueue->rating) {
            curr = curr->next;
        }
        newGameQueue->next = curr->next;
        curr->next = newGameQueue;
    }
}

Game* searchGame(Game* curr, const char toBeSearch[]) {
    if (curr == NULL) return NULL;
    else if (strcmpi(toBeSearch, curr->name) < 0) return searchGame(curr->left, toBeSearch);
    else if (strcmpi(toBeSearch, curr->name) > 0) return searchGame(curr->right, toBeSearch);
    else return curr;
}

Game* deleteGame(Game* curr, const char toBeDeleted[]) {
    if (curr == NULL) return curr;
    else if (strcmpi(toBeDeleted, curr->name) < 0) curr->left = deleteGame(curr->left, toBeDeleted);
    else if (strcmpi(toBeDeleted, curr->name) > 0) curr->right = deleteGame(curr->right, toBeDeleted);
    else {
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
        }
        else if (curr->left != NULL && curr->right == NULL) {
            Game* temp = curr;
            curr = curr->left;
            free(temp);
            temp = NULL;
        }
        else if (curr->left == NULL && curr->right != NULL) {
            Game* temp = curr;
            curr = curr->right;
            free(temp);
            temp = NULL;
        }
        else {
            Game* temp = curr->left;
            while (temp->right != NULL) temp = temp->right;
            strcpy(curr->name, temp->name);
            curr->rating = temp->rating;
            curr->hoursPlayed = temp->hoursPlayed;
            curr->left = deleteGame(curr->left, temp->name);
        }
    }
    return curr;
}

void popGameQueueByName(const char toBeDeleted[]) {
    if (head == NULL && tail == NULL) return;
    else if (strcmpi(toBeDeleted, head->name) == 0) {
        GameQueue* temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
        if (head == NULL) tail = NULL;
    }
    else {
        GameQueue* curr = head;
        while (curr->next != NULL && strcmpi(toBeDeleted, curr->next->name) != 0) {
            curr = curr->next;
        }
        if (curr->next != NULL) {
            GameQueue* temp = curr->next;
            curr->next = temp->next;
            free(temp);
            temp = NULL;
            if (curr->next == NULL) tail = curr;
        }
    }
}

void editGameQueueByName(const char toBeEdited[], int rating) {
    GameQueue* curr = head;
    while (curr != NULL && strcmpi(toBeEdited, curr->name) != 0) {
        curr = curr->next;
    }
    if (curr != NULL) {
        curr->rating = rating;
    }
}

void printGameQueue() {
    printf("View By Rating\n");
    GameQueue* curr = head;
    while (curr != NULL) {
        printf("%s %d %d\n", curr->name, curr->rating, curr->hoursPlayed);
        curr = curr->next;
    }
}

void printMenu() {
    printf("1. Insert\n2. Delete\n3. View\n4. Exit\n");
}

void inOrder(Game* curr) {
    if (curr == NULL) return;
    inOrder(curr->left);
    printf("%s %d %d\n", curr->name, curr->rating, curr->hoursPlayed);
    inOrder(curr->right);
}

bool checkAlphaNumeric(const char nim[]) {
    for (int i = 0; i < strlen(nim); i++) {
        if (!isalnum(nim[i]) && !isspace(nim[i])) return false;
    }
    return true;
}

int scanRating(int min, int max){
    char rand[100] = {};
    int satisfied;
    int res;
    do {
        satisfied = 1;
        printf("Rating : ");
        scanf("%[^\n]", rand);
        getchar();

        if (!strlen(rand))
        {
            satisfied = 0;
        }
        else
        {
            for (int i = 0; i < strlen(rand);i++)
            {
                if (!isdigit(rand[i]))
                {
                    satisfied = 0;
                    break;
                }
            }
            if (satisfied == 1)
            {
                res = atoi(rand);
            }
        }
    } while (!satisfied || res < min || res > max);
    return res;
}

int scanHoursPlayed(int min, int max){
    char rand[100] = {};
    int satisfied;
    int res;
    do {
        satisfied = 1;
        printf("Hours Played : ");
        scanf("%[^\n]", rand);
        getchar();

        if (!strlen(rand))
        {
            satisfied = 0;
        }
        else
        {
            for (int i = 0; i < strlen(rand);i++)
            {
                if (!isdigit(rand[i]))
                {
                    satisfied = 0;
                    break;
                }
            }
            if (satisfied)
            {
                res = atoi(rand);
            }
        }
    } while (!satisfied || res < min || res > max);
    return res;
}

int main() {
    while (true)
    {
        inOrder(root);
        printMenu();
        int choice;
        do
        {
            printf(">> ");
            scanf("%d", &choice); getchar();
        } while (choice < 1 || choice > 4);

        if (choice == 1) {
            char name[100];
            int rating, hoursPlayed;
            do {
                printf("Name : ");
                scanf("%[^\n]", &name); getchar();
            } while (strlen(name) < 1 || strlen(name) > 100 || !checkAlphaNumeric(name));
            
            rating = scanRating(1, 10);

            hoursPlayed = scanHoursPlayed(0, 2000);
            
            Game* temp = searchGame(root, name);
            if (temp == NULL) {
                root = insertGame(root, createGame(name, rating, hoursPlayed));
                pushPriorityByRating(createGameQueue(name, rating, hoursPlayed));
            }
            else {
                temp->rating = rating;
                editGameQueueByName(name, rating);
                printf("Game name already exists, updated rating instead\n");
            }
        }
        else if (choice == 2) {
            char name[100];
            do {
                printf("Name : ");
                scanf("%[^\n]", &name); getchar();
            } while (strlen(name) < 1 || strlen(name) > 100 || !checkAlphaNumeric(name));
            Game* temp = searchGame(root, name);
            if (temp == NULL) {
                printf("Game name does not exist\n");
            }
            else {
                root = deleteGame(root, name);
                popGameQueueByName(name);
            }
        }
        else if (choice == 3) {
            printGameQueue();
        }
        else if (choice == 4) {
            break;
        }
        printf("Press enter to continue\n"); getchar();
    }
    
    return 0;
}