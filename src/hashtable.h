#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Product {
    int id;
    char name[50];
    float price;
    Date date;
} Product;

typedef struct HashTableNode {
    int key;
    Product* value;

    struct HashTableNode* next;
} HashTableNode;

typedef struct HashTable {
    int size;
    HashTableNode** table;
} HashTable;

void initHashTable(HashTable* hashTable, int size);
void insert(HashTable* hashTable, int key, char* value);
char* search(HashTable* hashTable, int key);
int hashFunction(int key, int size);

#endif