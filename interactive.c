#include <stdio.h>
#include <stdlib.h>

#include "ablib.h"

char* input1 = "123";
char* input2 = "54321";

char* getNum() {
	size_t input_size = 0;
	char* input_line = NULL;
	printf("Give us a number: ");
	if (getline(&input_line, &input_size, stdin) == -1) {
		free(input_line);
		return NULL;
	}
	for (int i = 0; input_line[i] != '\0'; i++) {
		if (input_line[i] == '\n') input_line[i] = '\0';
	}
	return input_line;
}

int readNum(char s[]) {	//cheating??
	int k = 0;
	for (int i = 0; s[i] != '\0'; i++) {
		for (char c = '0'; c <= '9'; c++) {
			if (s[i] == c) k++;
		}
	}
	return k;
}

int main(int argc, char* argv[]) {

	bool shell = false;
	bool silent = false;
	bool anim = false;
	char *input1 = NULL;
	char *input2 = NULL;

	if (argc == 1) shell = true;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 's') silent = true;
			else if (argv[i][1] == 'a') anim = true;
			else if (argv[i][1] == 'i') shell = true;
			else printf("are you stupid?");
		}
		else {
			if (input1 == NULL) input1 = argv[i];
			else if (input2 == NULL) input2 = argv[i];
			else {
				printf("are you stupid?");
				return 1;
			}
		}
	}
	if ((input1 == NULL || input2 == NULL) && shell == false) {
		shell = true;
	}

	if (shell) {
		input1 = getNum();
	}
	//if (!shell) input1 = argv[1];
	//int g = readNum(input1);

	char *abacus1 = makeAbacus(input1);
	if (shell) free(input1);
	if (!silent && shell) printf("%s\n", abacus1);
	if (!silent && !shell) printf("+\n");
	//printf("%s\n+\n", abacus1);

	if (shell) input2 = getNum();
	//if (!shell) input2 = argv[2];
	//int k2 = readNum(input2);

	char *abacus2 = makeAbacus(input2);
	if (shell) free(input2);
	if (!silent && shell) printf("%s", abacus2);
	//printf("%s\n", abacus2);

	//addition(&abacus1, &abacus2);
	////printf("%s", abacus2);

	//if (!silent && shell) printf("abacii added:\n%s", abacus2);
	//if (!silent && !shell && !anim) printf("=\n%s", abacus2);
	////readAbacus(result);
	//printf("\n");
	//free(result);

	// subtraction
	//int res = subtraction(&abacus1, &abacus2);
	//if (res == 0) printf("\nabacus2 = abacus2 - abacus1:\n%s", abacus2);
	//else printf("\nabacus2 = abacus2 - abacus1:\n-%s", abacus2);
	//printf("\nabacus1 post subtraction:\n%s", abacus1);

	//// division
	//division(&abacus1, &abacus2);
	//printf("abacus2 = abacus2 / abacus1:\n%s", abacus2);
	//printf("\nabacus1 post division:\n%s", abacus1);

	//modulo
	modulo(&abacus1, &abacus2);
	printf("\nabacus2 %% abacus1:\n%s", abacus2);

	printf("\n");
	free(abacus2);
	free(abacus1);

	return 0;
}
