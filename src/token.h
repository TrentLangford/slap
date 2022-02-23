#ifndef __TOKEN_H_
#define __TOKEN_H_

typedef struct token
{
    char *type;
    char *value;
} token;

token wordToToken(char *word, gram_rule *rules, int rCount);

#endif