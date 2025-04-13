#ifndef HASH_UTILS_H
#define HASH_UTILS_H

const size_t c_tableSize =  750;
const size_t c_maxWordLen = 100;

typedef struct Node {
    char* word;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct Bucket {
    Node* head;
    Node* tail;
} Bucket;

typedef struct HashTable {
    Bucket* buckets;
} HashTable;

HashTable* createHT();
void freeHT(HashTable* table);
void insertHT(HashTable* table, const unsigned char* word);
int searchHT(HashTable* table, const unsigned char* word);
void deleteHT(HashTable* table, const unsigned char* word);
void visualizeHT(HashTable* table, const char* outputFile);
#endif // HASH_UTILS_H
