#include "common.h"
#include "token.h"
#include "gram.h"
#define MAXRULES 64

int main(int argc, char **argv)
{
    if (argc != 3) {
        puts("Incorrect number of arguments");
        return -1;
    }

    FILE *tokenFile = fopen(argv[1], "r+");
    FILE *binaryFile = fopen(argv[2], "w+");

    if (!tokenFile)
    {
        printf("File %s failed to open\n", argv[1]);
    }
    if (!binaryFile)
    {
        printf("File %s failed to open\n", argv[2]);
    }

    gram_rule g = lineFromFileToRule(tokenFile);
	gram_rule *rules = malloc(sizeof(gram_rule) * MAXRULES);
	int count = 0;
    while (strcmp(g.type_name, "end") != 0) {
		if (count < MAXRULES) rules[count++] = g;
		
        g = lineFromFileToRule(tokenFile);
    }
    rules[count++] = g;

    writeRulesToFile(binaryFile, rules, count);

    fclose(tokenFile);
    fclose(binaryFile);

    return 0;
}