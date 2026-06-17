#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"

int hashFunction(int key, int size) {
    return key % size;
}

void initHashTable(HashTable* hashTable, int size) {
    hashTable->size = size;
    hashTable->table = (HashTableNode**)malloc(size * sizeof(HashTableNode*));

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
}

void insert(HashTable* hashTable, int key, char* value) {
    int index = hashFunction(key, hashTable->size);
    HashTableNode* newNode = (HashTableNode*)malloc(sizeof(HashTableNode));
    
    newNode->key = key;
    newNode->value = strdup(value);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}