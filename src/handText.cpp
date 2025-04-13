#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "hash_utils.h"
#include "handText.h"

void cleanText(const char* inputFile, const char* outputFile)
{
    FILE* in = fopen(inputFile, "r");
    if (!in)
    {
        printf("Failed to open input file: %s\n", inputFile);
        return;
    }

    FILE* out = fopen(outputFile, "w");
    if (!out)
    {
        printf("Failed to open output file: %s\n", outputFile);
        fclose(in);
        return;
    }

    int c = 0;
    bool f_prChar = 0;
    while ((c = fgetc(in)) != EOF)
    {
        if (isalpha(c))
        {
            fputc(c, out);
            f_prChar = 1;
        }
        else if (c == ' ' && f_prChar)
        {
            fputc('\0', out);
            f_prChar = 0;
        }
    }
    fputc('\0', out);
    fclose(in);
    fclose(out);
}

void parseText(const char* file, HashTable* table)
{
    // open file for reading and writing
    int fileDescriptor = open(file, O_RDWR);
    if (fileDescriptor == -1) 
    {
        printf("Failed to open file: %s\n", file);
        return;
    }

    // get file info
    struct stat file_info = {0};
    if (fstat(fileDescriptor, &file_info) == -1) 
    {
        close(fileDescriptor);
        printf("Failed to get file info: %s\n", file);
        return;
    }

    size_t local_numOfSymbols = (size_t)file_info.st_size;

    // check if file is empty
    // if (local_numOfSymbols == 0) 
    // {
    //     *buffer = nullptr;

    //     if (numOfSymbols) *numOfSymbols = 0;
    //     if (numOfStrs) *numOfStrs = 0;

    //     close(fileDescriptor);
    //     return EMPTY_FILE;
    // }

    void* mapped = mmap(NULL, local_numOfSymbols, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);
    if (mapped == MAP_FAILED)
    {
        close(fileDescriptor);
        printf("Failed to map file: %s\n", file);
        return;
    }

    // buffer is pointing to mapped memory
    unsigned char* buffer = (unsigned char*)mapped;

    while (*buffer != '\0')
    {
        //fprintf(stderr, "%s\n", buffer);
        insertHT(table, buffer);
        buffer += strlen((char*)buffer) + 1;
    }
    // count number of strings if it's needed
    // if (numOfStrs != nullptr) 
    // {
    //     *numOfStrs = 0;
    //     for (size_t i = 0; i < local_numOfSymbols; i++) 
    //     {
    //         if ((*buffer)[i] == '\n') 
    //         {
    //             (*numOfStrs)++;
    //         }
    //     }
    //     // and the last string
    //     if (local_numOfSymbols > 0 && (*buffer)[local_numOfSymbols - 1] != '\n') 
    //     {
    //         (*numOfStrs)++;
    //     }
    // }

    // size of file
    // if (numOfSymbols != nullptr) {
    //     *numOfSymbols = local_numOfSymbols;
    //     printf("size of file %u", local_numOfSymbols);
    // }

    // close descriptor
    close(fileDescriptor);

    //return NO_ERR;
}

// void generateKeys(const char* textFile, const ch)
// {
//     int fileDescriptor = open(file, O_RDWR);
//     if (fileDescriptor == -1) 
//     {
//         printf("Failed to open file: %s\n", file);
//         return;
//     }

//     // get file info
//     struct stat file_info = {0};
//     if (fstat(fileDescriptor, &file_info) == -1) 
//     {
//         close(fileDescriptor);
//         printf("Failed to get file info: %s\n", file);
//         return;
//     }

//     return 
// }

void prepareKeys(const char* rawKeysFile, const char* outputKeysFile) {

    FILE* inFile = fopen(rawKeysFile, "r");
    if (!inFile) {
        perror("Error opening input file");
        return;
    }

    FILE* outFile = fopen(outputKeysFile, "w");
    if (!outFile) {
        perror("Error opening output file");
        fclose(inFile);
        return;
    }

    char buffer[32] = {0};

    while (fgets(buffer, sizeof(buffer), inFile)) {
        size_t len = strlen(buffer) - 1;

        if (len < 32)
        {
            memset(buffer + len , 0, 32 - len);
        }

        fwrite(buffer, sizeof(char), 32, outFile);
    }

    fclose(inFile);
    fclose(outFile);
}