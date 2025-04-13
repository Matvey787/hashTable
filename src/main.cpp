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
    runTest(table, "keys.txt");
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

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file)) 
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (searchHT(table, (const unsigned char*)buffer)) 
        {
            printf("%s exist!\n", buffer);
        }
    }

    fclose(file);
}