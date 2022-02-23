#include "gram.h"

typedef struct token
{
    char *type;
    char *value;
} token;

token wordToToken(char *word, gram_rule *rules, int rCount) {
    token result;
	gram_rule def;
	gram_rule num;
	for (int i = 0; i < rCount; i++)
	{
		for (int x = 0; x < rules[i].aliasCount; x++)
		{
			if (strcmp(rules[i].aliases[x], word) == 0)
			{
				result.type = malloc(sizeof(char) * strlen(rules[i].type_name));
				strcpy(result.type, rules[i].type_name);

				result.value = malloc(sizeof(char) * strlen(word));
				strcpy(result.value, word);
			}
		}
	}
	
	
    return result;
}

