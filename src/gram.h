#ifndef __GRAM_H_
#define __GRAM_H_

#include "common.h"

typedef struct gram_rule
{
    char *type_name;
    char **aliases;
    int aliasCount;
    int is_default;
    int is_num;
} gram_rule;

void removeChar(char *str, char garbage);

// Returns  a single grammar rule, with a type of end if the end command is reached.
gram_rule lineFromFileToRule(FILE *fptr);


void writeRulesToFile(FILE *fp, gram_rule *rules, int count);
gram_rule *readRulesFromFile(FILE *fp);

#endif