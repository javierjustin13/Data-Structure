#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Data {
    char name[20];
    struct Data* next;
};

const int maxArrSize = 20;

struct Data* hashTable[maxArrSize];

int hashFunction(const char name[]) {
    int hashValue = ceil(float(name[0] * name[1]) / float(name[strlen(name) - 1] + name[strlen(name) - 2])); 
    return hashValue % maxArrSize;
}

void insertLinearProbing(const char name[]) {
    struct Data* newData = (struct Data*)malloc(sizeof(struct Data));
    strcpy(newData->name, name);
    newData->next = NULL;
    //Get hash value / key from hash function
    int index = hashFunction(name);
    printf("Hash value of %s is : %d\n", name, index);
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
            if (currIndex >= maxArrSize) {
                currIndex = 0;
            }
            if (currIndex == index) {
                break;
            }
        }
        if (currIndex == index) {
            printf("Hash table is full\n");
        }
        else {
            hashTable[currIndex] = newData;
        }
    }
}

void insertChaining(const char name[]) {
    struct Data* newData = (struct Data*)malloc(sizeof(struct Data));
    strcpy(newData->name, name);
    newData->next = NULL;
    //Get hash value / key from hash function
    int index = hashFunction(name);
    printf("Hash value of %s is : %d\n", name, index);
    //Insert to hash table, apply chaining if needed
    //if current index in hash table is empty
    if (hashTable[index] == NULL) {
        hashTable[index] = newData;
    }
    // if current index in hash table is not empty
    else {
        struct Data* curr = hashTable[index];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newData;
    }
}

void display() {
    for (int i = 0; i < maxArrSize; i++) {
        if (hashTable[i] != NULL) {
            struct Data* curr = hashTable[i];
            while (curr != NULL) {
                printf("%s -> ", curr->name);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

int main() {
    insertLinearProbing("noobmaster96");
    insertLinearProbing("xTyranx");
    insertLinearProbing("RoboFox");
    insertLinearProbing("Derp");
    insertLinearProbing("Youtube21");
    insertLinearProbing("Revan789");
    insertLinearProbing("SnakeyBoy");
    insertLinearProbing("Mario");
    insertLinearProbing("DonChef");
    insertLinearProbing("Herpina");
    display();
    return 0;
}