#include <stdio.h>
#include <stdlib.h>

#include "ablib.h"

//char* input1 = "123";

//char* get

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

	struct expression {
		char* x;
		char* y;
		char operator;
	};
	struct expression input = {NULL, NULL, '+'};

	char validops[6] = {'+', '-', '.', '/', '%', '\0'};

	if (argc == 1) shell = true;
	for (int i = 1; i < argc; i++) {
		int is_op = 0;
		if (argv[i][1] == '\0') {
			for (int j = 0; validops[j] != '\0'; j++) {
				if (argv[i][0] == validops[j]) {
					input.operator = validops[j];
					is_op = 1;
					break;
				}
			}
		}
		if (is_op);
		else if (argv[i][0] == '-') {
			if (argv[i][1] == 's') silent = true;
			else if (argv[i][1] == 'a') anim = true;
			else if (argv[i][1] == 'i') shell = true;
			else printf("are you stupid?");
		}
		else {
			if (input.x == NULL) input.x = argv[i];
			else if (input.y == NULL) input.y = argv[i];
		}
	}

	if ((input.x == NULL || input.y == NULL) && shell == false) {
		shell = true;
	}

	if (shell) {
		input.x = getNum();
	}
	//if (!shell) input.x = argv[1];
	//int g = readNum(input.x);

	char *abacus1 = makeAbacus(input.x);
	if (shell) free(input.x);
	if (!silent) printf("%s\n", abacus1);
	if (!silent && !shell) printf("%c\n", input.operator);
	//printf("%s\n+\n", abacus1);

	if (shell) input.y = getNum();
	//if (!shell) input.y = argv[2];
	//int k2 = readNum(input.y);

	char *abacus2 = makeAbacus(input.y);
	if (shell) free(input.y);
	if (!silent) printf("%s", abacus2);
	//printf("%s\n", abacus2);

	switch (input.operator) {
		case '+':
			addition(&abacus2, &abacus1);
			break;
		case '-':
			subtraction(&abacus2, &abacus1);
			break;
		case '.':
			multiplication(&abacus2, &abacus1);
			break;
		case '/':
			division(&abacus2, &abacus1);
			break;
		case '%':
			modulo(&abacus2, &abacus1);
			break;
	}
	//printf("\nabacus2 %c abacus1 = \n%s", input.operator, abacus2);
	printf("\n=\n%s", abacus1);

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
	//modulo(&abacus1, &abacus2);
	//printf("\nabacus2 %% abacus1:\n%s", abacus2);

	printf("\n");
	free(abacus2);
	free(abacus1);

	return 0;
}
