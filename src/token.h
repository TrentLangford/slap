#ifndef __TOKEN_H_
#define __TOKEN_H_

#include "gram.h"

typedef struct token
{
    char *type;
    char *value;
} token;

token wordToToken(char *word, gram_rule *rules, int rCount);

#endif