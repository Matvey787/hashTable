#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hash_utils.h"

static void   freeNode     (Node* node);
static Node*  createNode   (const unsigned char* word);
static size_t hashFunction (const unsigned char* word);

HashTable* createHT()
{
    HashTable* table = (HashTable*)calloc(1, sizeof(HashTable));
    if (!table)
    {
        printf("Memory allocation failed for table\n");
        exit(1);
    }
    table->buckets = (Bucket*)malloc(c_tableSize * sizeof(Bucket));
    if (!table->buckets) 
    {
        printf("Memory allocation failed for buckets\n");
        free(table);
        exit(1);
    }
    for (size_t i = 0; i < c_tableSize; i++) {
        table->buckets[i].head = NULL;
        table->buckets[i].tail = NULL;
    }
    return table;
}

void freeHT(HashTable* table) 
{
    assert(table);

    for (size_t i = 0; i < c_tableSize; i++) 
    {
        Node* currNode = table->buckets[i].head;
        while (currNode != NULL) 
        {
            Node* temp = currNode;
            currNode = currNode->next;
            freeNode(temp);
        }
    }
    free(table->buckets);
    free(table);
}

void insertHT(HashTable* table, const unsigned char* word)
{
    size_t index = hashFunction(word);
    Node* newNode = createNode(word);

    if (table->buckets[index].head == NULL)
    {
        table->buckets[index].head = newNode;
        table->buckets[index].tail = newNode;
        return;
    }

    // check if word already exists
    Node* current = table->buckets[index].head;
    while (current != NULL) 
    {
        if (strcmp(current->word, (const char*)word) == 0) 
        {
            free(newNode->word);
            free(newNode);
            return;
        }
        current = current->next;
    }
    // add new node
    Bucket* necBucket = &table->buckets[index];

    newNode->prev = necBucket->tail;
    necBucket->tail->next = newNode;
    necBucket->tail = newNode;
}

int searchHT(HashTable* table, const unsigned char* word)
{
    assert(table);
    assert(word);
    
    size_t index = hashFunction(word);
    Node* current = table->buckets[index].head;
    while (current != NULL) 
    {
        if (strcmp(current->word, (const char*)word) == 0) 
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void deleteHT(HashTable* table, const unsigned char* word)
{
    assert(table);
    assert(word);

    size_t index = hashFunction(word);
    Node* current = table->buckets[index].head;

    while (current != NULL) {
        if (strcmp(current->word, (const char*)word) == 0) 
        {
            if (current->prev == NULL && current->next == NULL)
            {
                table->buckets[index].head = NULL;
                table->buckets[index].tail = NULL;
            }
            else if (current->prev == NULL)
            {
                table->buckets[index].head = current->next;
                current->next->prev = NULL;
            }
            else if (current->next == NULL)
            {
                table->buckets[index].tail = current->prev;
                current->prev->next = NULL;
            }
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            freeNode(current);
            return;
        }
        current = current->next;
    }
    printf("Word '%s' not found for deletion\n", word);
}

void visualizeHT(HashTable* table, const char* outputFile)
{
    assert(table);
    assert(outputFile);

    system("touch hashtable.dot");
    FILE* dotFile = fopen("hashtable.dot", "w");
    if (!dotFile)
    {
        printf("Failed to create DOT file\n");
        return;
    }

    fprintf(dotFile, "digraph HashTable {\n");
    fprintf(dotFile, "    rankdir=LR;\n");
    fprintf(dotFile, "    node [shape=box];\n");

    for (size_t i = 0; i < c_tableSize; i++)
    {
        fprintf(dotFile, "    bucket%zu [label=\"Bucket %zu\"];\n", i, i);

        Node* current = table->buckets[i].head;
        if (current == NULL)
        {
            fprintf(dotFile, "    bucket%zu -> empty%zu [style=invis];\n", i, i);
            fprintf(dotFile, "    empty%zu [label=\"(empty)\", shape=plaintext];\n", i);
        } else
        {
            size_t nodeIndex = 0;
            char prevNodeName[32];
            while (current != NULL) 
            {
                char nodeName[32];
                sprintf(nodeName, "bucket%zu_node%zu", i, nodeIndex);
                fprintf(dotFile, "    %s [label=\"%s\"];\n", nodeName, current->word);

                if (nodeIndex == 0)
                {
                    fprintf(dotFile, "    bucket%zu -> %s;\n", i, nodeName);
                } else 
                {
                    fprintf(dotFile, "    %s -> %s;\n", prevNodeName, nodeName);
                }
                strcpy(prevNodeName, nodeName);
                current = current->next;
                nodeIndex++;
            }
        }
    }

    fprintf(dotFile, "}\n");
    fclose(dotFile);

    char command[256];
    sprintf(command, "dot -Tsvg hashtable.dot -o %s", outputFile);
    int result = system(command);
    if (result == 0) {
        printf("Visualization saved to %s\n", outputFile);
    } else {
        printf("Failed to generate visualization\n");
    }
}

static void freeNode(Node* node) 
{
    free(node->word);
    free(node);
}

static Node* createNode(const unsigned char* word)
{
    assert(word);
    Node* node = (Node*)malloc(sizeof(Node));

    if (!node)
    {
        printf("Memory allocation failed for node\n");
        exit(1);
    }
    node->word = (char*)malloc(strlen((const char*)word) + 1);
    
    if (!node->word)
    {
        printf("Memory allocation failed for word\n");
        free(node);
        exit(1);
    }
    strcpy(node->word, (const char*)word);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

static size_t hashFunction(const unsigned char* word)
{
    assert(word);
    unsigned long hash = 0;

    for (size_t i = 0; word[i] != '\0'; i++) 
    {
        hash += (unsigned long)word[i];
    }
    return hash % c_tableSize;
}