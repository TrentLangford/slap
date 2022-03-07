#include "common.h"
#include "gram.h"
#include "token.h"

#define MAXRULES 64

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
	gram_rule *rules = malloc(sizeof(grammar) * MAXRULES);
	int count = 0;
    while (strcmp(g.type_name, "end") != 0) {
		if (count < MAXRULES) rules[count++] = g;
		
        g = lineFromFileToRule(grammar);
    }
    rules[count++] = g;

    FILE *grambin = fopen("src/bin/grambin.bin", "w+");

    writeRulesToFile(grambin, rules, count);
    gram_rule *readout = readRulesFromFile(grambin);
    int i = 0;
    while (strcmp(readout[i].type_name, "end") != 0)
    {
        printf("%s\n", readout[i].type_name);
        i++;
    }

    char buff[64];
	fgets(buff, 64, stdin);

	char *word = malloc(sizeof(char) * strlen(buff));
	strcpy(word, buff);
	removeChar(word, '\n');
	token tok = wordToToken(word, rules, count);

	if (tok.type != NULL) printf("{%s:%s}\n", tok.type, tok.value);
	
    fclose(input);
    fclose(grammar);
    fclose(output);
    return 0;
}