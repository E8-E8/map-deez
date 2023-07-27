#include "hash-table.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 4096

uint64_t hash_function(const char* name, size_t length) {
    uint64_t hash_value = 0;
    for(int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = hash_value * name[i];
    }

    return hash_value;
}



int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("usage: <wordlist filename> <num guesses>\n");
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    // uint32_t num_guesses = atol(argv[2]);

    const int tablesize = (1<<20);
    hash_table *table = hash_table_create(tablesize, hash_function);

    FILE* fp = fopen(filename, "r");
    char buffer[MAX_LINE];

    uint32_t numwords = 0;

    while(!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL) {
        buffer[strcspn(buffer, "\n\r")] = 0;
        char* newentry = malloc(strlen(buffer) + 1);
        strcpy(newentry, buffer);

        hash_table_insert(table, newentry, newentry);
        numwords++;
    }

    fclose(fp);

    printf("Loaded %d words to the hashtable\n", numwords);

    char* ht_object = hash_table_lookup(table, "BoJack");

    hash_table_print(table);

    printf("BoJack exists in my cool hashmap here is his value: %s", ht_object);
}




