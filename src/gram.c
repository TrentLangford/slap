#include "common.h"

#define MAX_WORD_LENGTH 64

typedef struct gram_rule
{
    char *type_name;
    char **aliases;
    int aliasCount;
    int is_default;
    int is_num;
} gram_rule;

//  https://stackoverflow.com/questions/5457608/how-to-remove-the-character-at-a-given-index-from-a-string-in-c
void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

gram_rule lineFromFileToRule(FILE *fptr) {
    // Get the next line from the file (we set size and line to null to allow the function to allocate it for us)
    // Remove the trailing newline, we don't need it
    size_t size;
    char *line = NULL;
    char *line2;
    getline(&line, &size, fptr);
    removeChar(line, '\n');

    // Allocate a duplicate line that we need for some reason. This probably causes a memory leak.
    line2 = malloc(sizeof(char) * strlen(line));
    strcpy(line2, line);


    // Separate the line into tokens and get the first token
    char * token = strtok(line, " ");
    gram_rule g = {NULL, NULL, 0, 0, 0};
    g.type_name = malloc(sizeof(char) * strlen(token));
    strcpy(g.type_name, token);

    if (strcmp(token, "end") == 0) {
        // Free memory that we won't get to later
        if (line != NULL) free(line);
        if (line2 != NULL) free(line2);

        return g;
    }

    // Count the amount of tokens left to parse
    int tokenCount = 0;
    while(token != NULL) {
        if (strcmp(token, g.type_name)) {
            tokenCount++;
        }
        token = strtok(NULL, " ");
    }
    // Put all of the tokens into the array
    char **tokens = (char **)malloc(sizeof(char *) * tokenCount);
    // Use the second duplicate line to trick the compiler (why does this work?)
    token = strtok(line2, " ");
    // i also happens to be the amount of aliases
    int i = 0;
    while(token != NULL) {
        // Make sure we skip the name and colon tokens in the line
        if (strcmp(token, g.type_name) != 0) {
            tokens[i] = (char*) malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(tokens[i], token);
            tokens[i][strlen(token)] = '\0'; // For protection ??
            i++;
        }

        token = strtok(NULL, " ");
    }

    g.aliases = (char **)malloc(sizeof(char *) * i);
    g.aliasCount = i;

    // Put the tokens from the token array into the alias list
    for (int j = 0; j < i; j++) {
        g.aliases[j] = malloc(sizeof(char) * strlen(tokens[j]));
        strcpy(g.aliases[j], tokens[j]);
    }

    // Check if this grammar rule if for the default/number type
    if (g.aliasCount == 1) {
        if (strcmp(g.aliases[0], "{num}") == 0) g.is_num = 1;
        else g.is_num = 0;
        
        if (strcmp(g.aliases[0], "{def}") == 0) g.is_default = 1;
        else g.is_default = 0;
    }

    // Clean memory leaks (any memory allocated and not returned needs to be freed)
    if (line != NULL) free(line);
    if (line2 != NULL) free(line2);
    if (tokens != NULL) {
        for (int i = 0; i < tokenCount; i++) {
            if (tokens[i] != NULL) free(tokens[i]); // Freeing the original pointer doesn't free the pointers it was referencing, so we need to do it ourselves
        }
        free(tokens);
    }

    return g;
}

void writeRulesToFile(FILE *fp, gram_rule *rules, int count)
{
    fwrite(&count, sizeof(int), 1, fp);
    for (int i = 0; i < count; i++)
    {
        unsigned short typename_s = strlen(rules[i].type_name);
        fwrite(&typename_s, sizeof(unsigned short), 1, fp);

        fwrite(rules[i].type_name, sizeof(char), typename_s, fp);

        fwrite(&rules[i].aliasCount, sizeof(int), 1, fp);

        for (int n = 0; n < rules[i].aliasCount; n++)
        {
            unsigned short aliaslen = strlen(rules[i].aliases[n]);
            fwrite(&aliaslen, sizeof(unsigned short), 1, fp);

            fwrite(rules[i].aliases[n], sizeof(char), aliaslen, fp);
        }

        fwrite(&rules[i].is_num, sizeof(int), 1, fp);
        fwrite(&rules[i].is_default, sizeof(int), 1, fp);
    }

}

gram_rule * readRulesFromFile(FILE *fp)
{
    rewind(fp);
    int count = 0;
    fread(&count, sizeof(int), 1, fp);

    gram_rule *rules = malloc(sizeof(gram_rule) * count);

    for (int i = 0; i < count; i++)
    {
        unsigned short typename_s;
        fread(&typename_s, sizeof(unsigned short), 1, fp);
        rules[i].type_name = malloc(sizeof(char) * typename_s);
        fread(rules[i].type_name, sizeof(char), typename_s, fp);

        fread(&rules[i].aliasCount, sizeof(int), 1, fp);

        rules[i].aliases = malloc(sizeof(char *) * rules[i].aliasCount);

        for (int n = 0; n < rules[i].aliasCount; n++)
        {
            unsigned short aliaslen;
            fread(&aliaslen, sizeof(unsigned short), 1, fp);
            rules[i].aliases[n] = malloc(sizeof(char) * aliaslen);

            fread(rules[i].aliases[n], sizeof(char), aliaslen, fp);
        }

        fread(&rules[i].is_num, sizeof(int), 1, fp);
        fread(&rules[i].is_default, sizeof(int), 1, fp);
    }

    return rules;
}
