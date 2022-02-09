#include <stdio.h>
#include <string.h>
#include "gram.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        puts("Incorrect number of arguments");
        return -1;
    }

    FILE *input = fopen(argv[1], "r+");
    FILE *grammar = fopen(argv[2], "r+");
    FILE *output = fopen(argv[3], "w+");

    if (input == NULL) {
        printf("Cannot open file at %s\n", argv[1]);
        return -1;
    }
    
    if (grammar == NULL) {
        printf("Cannot open file at %s\n", argv[2]);
        return -1;
    }

    if (output == NULL) {
        printf("Cannot open file at %s\n", argv[3]);
        return -1;
    }

    gram_rule g = lineFromFileToRule(grammar);

    while (strcmp(g.type_name, "end") != 0) {
        printf("Rule for: %s (alias count: %d)\n", g.type_name, g.aliasCount);
        if (g.is_default == 1) printf("This is the default token type\n");
        if (g.is_num == 1) printf("This is the numerical type token\n");
        for (int i = 0; i < g.aliasCount; i++) {
            printf("%s will turn into this token\n", g.aliases[i]);
        }
        printf("\n");
        g = lineFromFileToRule(grammar);
    }

    


    fclose(input);
    fclose(grammar);
    fclose(output);
    return 0;
}