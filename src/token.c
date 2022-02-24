#include "token.h"

// This function is pretty nifty and is loosely based on a similar operation defined in Codepulse's programming language tutorial series
int isNumber(char *word)
{
    int len = strlen(word);
    int dots = 0;
    char nums[11] = "0123456789";
    for (int i = 0; i < len; i++)
    {
        if (word[i] == '.')
        {
            dots++;
            continue;
        }
            
        if (dots > 1)
        {
            return 0;
        }

        int hasNum = 0;
        for (int n = 0; n < 11; n++)
        {
            if (nums[n] == '\0') continue;
            if (word[i] == nums[n])
            {
                hasNum++;
                break;
            }
        }
        if (hasNum == 0)
        {
            return 0;
        }
    }
    return 1;
}

token wordToToken(char *word, gram_rule *rules, int rCount) {
    // Set the defaults to null incase the user does not define a default token
	token result = {NULL, NULL};
    // Keep track of the default and number rules if they exist
	gram_rule def = {NULL, NULL, 0, 0, 0};
	gram_rule num = {NULL, NULL, 0, 0, 0};

    // First pass to set the default and number rules and grab any tokens if possible
	for (int i = 0; i < rCount; i++)
	{   
		for (int x = 0; x < rules[i].aliasCount; x++)
		{
            if (rules[i].is_num)
            {
                num = rules[i];
                continue;
            }
            if (rules[i].is_default)
            {
                def = rules[i];
                continue;
            }
			if (strcmp(rules[i].aliases[x], word) == 0)
			{
				result.type = malloc(sizeof(char) * strlen(rules[i].type_name));
				strcpy(result.type, rules[i].type_name);

				result.value = malloc(sizeof(char) * strlen(word));
				strcpy(result.value, word);
			}
		}
	}

    // Second "pass" to see if the word should be a number, else return a default token if it is defined
    if (result.type == NULL)
    {
        if (isNumber(word) == 1)
        {
            result.type = malloc(sizeof(char) * strlen(num.type_name));
            strcpy(result.type, num.type_name);
        }
        else
        {
            result.type = malloc(sizeof(char) * strlen(def.type_name));
            strcpy(result.type, def.type_name);
        }

        result.value = malloc(sizeof(char) * strlen(word));
        strcpy(result.value, word);
    }

  return result;
}

