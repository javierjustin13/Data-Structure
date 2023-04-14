#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
    char username[100];
    char job[100];
    int score;
    int matchCount;
    int win;
    int lose;
    int draw;
    double winrate;
    int height;
    Player* left;
    Player* right;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Player* curr) {
    if (curr == NULL) return 0;
    return curr->height;
}

int getBalance(Player* curr) {
    if (curr == NULL) return 0;
    return getHeight(curr->left) - getHeight(curr->right);
}

Player* rightRotate(Player* T) {
    //Node T that violates balance
    Player* S = T->left;
    Player* B = S->right;

    //Rotate
    T->left = B;
    S->right = T;

    //Update height
    T->height = 1 + max(getHeight(T->left), getHeight(T->right));
    S->height = 1 + max(getHeight(S->left), getHeight(S->right));

    return S;
}

Player* leftRotate(Player* T) {
    //Node T that violates balance
    Player* S = T->right;
    Player* B = S->left;

    //Rotate
    T->right = B;
    S->left = T;

    //Update height
    T->height = 1 + max(getHeight(T->left), getHeight(T->right));
    S->height = 1 + max(getHeight(S->left), getHeight(S->right));

    return S;
}

Player* createPlayer(const char username[], const char job[], int score, int matchCount, int win, int lose, int draw) {
    Player * newPlayer = (Player*)malloc(sizeof(Player));
    strcpy(newPlayer->username, username);
    strcpy(newPlayer->job, job);
    newPlayer->score = score;
    newPlayer->matchCount = matchCount;
    newPlayer->win = win;
    newPlayer->lose = lose;
    newPlayer->draw = draw;
    newPlayer->winrate = ((double)win / (double)matchCount) * 100;
    newPlayer->height = 1;
    newPlayer->left = NULL;
    newPlayer->right = NULL;
    return newPlayer;
}

Player* insertPlayer(Player *curr, Player *newPlayer) {
    if (curr == NULL) return newPlayer;
    else if(newPlayer->score < curr->score) curr->left = insertPlayer(curr->left, newPlayer);
    else if (newPlayer->score > curr->score) curr->right = insertPlayer(curr->right, newPlayer);
    else if (newPlayer->winrate <= curr->winrate) curr->left = insertPlayer(curr->left, newPlayer);
    else if (newPlayer->winrate > curr->winrate) curr->right = insertPlayer(curr->right, newPlayer);

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    int balance = getBalance(curr);
    if (balance > 1 && getBalance(curr->left) >= 0) return rightRotate(curr);
    if (balance < -1 && getBalance(curr->right) <= 0) return leftRotate(curr);
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

Player *searchPlayer(Player *curr, int score) {
    if (curr == NULL) return NULL;
    else if (score < curr->score) return searchPlayer(curr->left, score);
    else if (score > curr->score) return searchPlayer(curr->right, score);
    else return curr;
}

Player* deletePlayer(Player* curr, int score) {
    if (curr == NULL) return curr;
    else if (score < curr->score) curr->left = deletePlayer(curr->left, score);
    else if (score > curr->score) curr->right = deletePlayer(curr->right, score);
    else {
        Player* temp;
        //Case 1: No child
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
            return curr;
        }
        //Case 2: One child
        else if (curr->left == NULL) {
            temp = curr->left;
            free(curr);
            return temp;
        }
        else if (curr->right == NULL) {
            temp = curr->right;
            free(curr);
            return temp;
        }
        //Case 3: Two child
        else {
            temp = curr->left;
            while (temp->right != NULL) temp = temp->right;
            strcpy(curr->username, temp->username);
            strcpy(curr->job, temp->job);
            curr->matchCount = temp->matchCount;
            curr->win = temp->win;
            curr->score = temp->score;
            curr->lose = temp->lose;
            curr->draw = temp->draw;
            curr->winrate = temp->winrate;
            curr->left = deletePlayer(curr->left, temp->score);
        }
    }
    
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    int balance = getBalance(curr);
    if (balance > 1 && getBalance(curr->left) >= 0) return rightRotate(curr);
    if (balance < -1 && getBalance(curr->right) <= 0) return leftRotate(curr);
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

void findPlayer(Player* curr, int score) {
    if (curr) {
        findPlayer(curr->left, score);
        if (score == curr->score) printf("%s [%s] (%0.lf%%) %d\n", curr->username, curr->job, curr->winrate, curr->score);
        findPlayer(curr->right, score);
    }
}

int currScoreBeingChecked = -1;
int tempDataLastIndex = 0;
struct tempData {
    char username[100];
    char job[100];
    double winrate;
}tempDataKeep[50];

void showAll(Player* curr)
{
    if (curr) {
        showAll(curr->left);
        if (currScoreBeingChecked == -1) {
            currScoreBeingChecked = curr->score;
            tempDataLastIndex = 0;
        }
        
        if (currScoreBeingChecked != curr->score) {
            printf("Score %d\n", currScoreBeingChecked);

            currScoreBeingChecked = curr->score;

            for (int i = tempDataLastIndex - 1; i >= 0;i--)
            {
                printf("%d. %s [%s] (%.0f%%)\n", tempDataLastIndex - i, tempDataKeep[i].username, tempDataKeep[i].job, tempDataKeep[i].winrate);
            }
            printf("\n");

            tempDataLastIndex = 0;
        }
        if (currScoreBeingChecked == curr->score)
        {
            tempData t;
            strcpy(t.username, curr->username);
            strcpy(t.job, curr->job);
            t.winrate = curr->winrate;
            tempDataKeep[tempDataLastIndex++] = t;
        }

        showAll(curr->right);
    }
}

int main() {
    Player* root = NULL;
    root = insertPlayer(root, createPlayer("Gregor", "Sniper", 113, 10, 9, 1, 0));
    root = insertPlayer(root, createPlayer("Heimdall", "Druid", 300, 100, 50, 50, 0));
    root = insertPlayer(root, createPlayer("Travy", "Warrior", 300, 200, 100, 100, 0));
    root = insertPlayer(root, createPlayer("Tetron", "Novice", 300, 50, 25, 25, 0));
    root = insertPlayer(root, createPlayer("Homer", "Druid", 113, 10, 8, 2, 0));
    root = insertPlayer(root, createPlayer("Garet", "Warrior", 113, 100, 70, 30, 0));

    int N;
    char command[100];
    scanf("%d", &N); getchar();
    
    for (int i = 0; i < N; i++) {
        scanf("%s", &command); getchar();
        
        if (strcmp(command, "INSERT") == 0) {
            int insertProcess;
            scanf("%d", &insertProcess); getchar();
            for(int i = 0; i < insertProcess; i++) {
                char username[100], job[100];
                int score, matchCount, win, lose, draw, jobEnum;
                scanf("%[^#]#%d#%d#%d#%d#%d#%d\n", &username, &jobEnum, &score, &matchCount, &win, &lose, &draw); 
                if (jobEnum == 0) strcpy(job, "Novice");
                else if (jobEnum == 1) strcpy(job, "Warrior");
                else if (jobEnum == 2) strcpy(job, "Sniper");
                else if (jobEnum == 3) strcpy(job, "Wizard");
                else if (jobEnum == 4) strcpy(job, "Druid");
                else if (jobEnum == 5) strcpy(job, "Assasin");
                root = insertPlayer(root, createPlayer(username, job, score, matchCount, win, lose, draw));
            }
        }
        
        else if (strcmp(command, "FIND") == 0) {
            int scoreToFind;
            scanf("%d", &scoreToFind); getchar();
            printf("Score %d\n", scoreToFind);
            Player* temp = searchPlayer(root, scoreToFind);
            if (temp == NULL) printf("No data found for %d\n", scoreToFind);
            else findPlayer(root, scoreToFind);
        }
        
        else if (strcmp(command, "DELETE") == 0) {
            int scoreToDelete;
            scanf("%d", &scoreToDelete); getchar();
            root = deletePlayer(root, scoreToDelete);
        }
        
        else if (strcmp(command, "SHOWALL") == 0) {
            showAll(root);

            printf("Score %d\n", currScoreBeingChecked);

            for (int i = tempDataLastIndex - 1; i >= 0;i--)
            {
                printf("%d. %s [%s] (%.0lf%%)\n", tempDataLastIndex - i, tempDataKeep[i].username, tempDataKeep[i].job, tempDataKeep[i].winrate);
            }
            tempDataLastIndex = 0;
            currScoreBeingChecked = -1;
        }

        else { 
            printf("Command not found!\n");
        }
    }
    return 0;
}