#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hash_utils.h"
#include "handText.h"
#include "dictionary.h"

void runTest(HashTable* table, const char* keysFile);

int main()
{
    // cleanText("book.txt", "cleanedBook.txt");
    HashTable* table = createHT();
    parseText("cleanedBook.txt", table);
    //prepareKeys("keys.txt", "preparedKeys.txt");
    runTest(table, "preparedKeys.txt");
    // for (size_t i = 0; i < c_dictSize; i++)
    // {
    //     if (searchHT(table, (const unsigned char*)dict[i])) printf("%s exist!\n", dict[i]);
    // }
    // insertHT(table, "hello");
    // insertHT(table, "world");
    // insertHT(table, "abc");
    // printf("%d\n", searchHT(table, "hello"));
    // deleteHT(table, "hello");
    // visualizeHT(table, "table.svg");
    freeHT(table);
}

void runTest(HashTable* table, const char* keysFile) {
    assert(table);
    FILE* file = fopen(keysFile, "r");
    if (!file) {
        perror("Error opening keys file");
        return;
    }

    char buffer[c_maxWordLen] = {0};
    while (1)
    {
        size_t bytes_read = fread(buffer, 1, 32, file);

        if (bytes_read != 32) break;

        if (searchHT(table, (const unsigned char*)buffer)) 
        {
            buffer[31] = '\0';
            printf("%s exist!\n", buffer);
        }
    }
    fclose(file);
}