#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxArrSize = 20;

struct Data {
    char heroName[20];
    char heroType[5]; //STR AGI INT
    int lvl;
    struct Data* next;
};

struct Data* hashTable[maxArrSize];

int hashFunction(const char heroName[]) {
    int hashValue = 0;
    for (int i = 0; i < strlen(heroName); i++) {
        hashValue += heroName[i];
    }
    return hashValue % maxArrSize;
}

void insert(const char heroName[], const  char heroType[], int lvl) {
    struct Data *newData = (struct Data*)malloc(sizeof(struct Data));
    strcpy(newData->heroName, heroName);
    strcpy(newData->heroType, heroType);
    newData->lvl = lvl;
    newData->next = NULL;
    //Get hash value / key from hash function
    int index = hashFunction(heroName);
    printf("Hash value of %s is : %d\n", heroName, index);
    //Insert to hash table, apply chaining if needed
    //if current index in hash table is empty
    if (hashTable[index] == NULL) {
        hashTable[index] = newData;
    }
    // if current index in hash table is not empty
    else {
        int currIndex = index + 1;
        while (hashTable[currIndex] != NULL) {
            currIndex++;
            if(currIndex >= maxArrSize) {
                currIndex = 0;
            }
            if(currIndex == index) {
                break;
            }
        }
        if(currIndex == index) {
            printf("Hash table is full\n");
        }
        else {
            hashTable[currIndex] = newData;
        }
    }

}

void display() {
    for (int i = 0; i < maxArrSize; i++) {
        if (hashTable[i] != NULL) {
            struct Data* curr = hashTable[i];
            while (curr != NULL) {
                printf("%s -> ", curr->heroName);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

int main() {
    insert("Axe", "STR", 1);
    insert("Lina", "INT", 1);
    insert("Anil", "INT", 1);
    insert("Luna", "AGI", 1);
    insert("Stephen", "STR", 1);
    insert("Exa", "STR", 1);
    display();
    return 0;
}