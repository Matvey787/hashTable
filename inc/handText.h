#ifndef HANDTEXT_H
#define HANDTEXT_H

void cleanText(const char* inputFile, const char* outputFile);
void parseText(const char* file, HashTable* table);
void prepareKeys(const char* rawKeysFile, const char* outputKeysFile);

#endif