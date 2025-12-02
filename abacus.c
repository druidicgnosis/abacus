#include <stdio.h>
#include <stdlib.h>

#include "ablib.h"

char* getNum() {
	size_t input_size = 0;
	char* input_line = NULL;
	printf("> ");
	if (getline(&input_line, &input_size, stdin) == -1) {
		free(input_line);
		return NULL;
	}
	for (int i = 0; input_line[i] != '\0'; i++) {
		if (input_line[i] == '\n') input_line[i] = '\0';
	}
	return input_line;
}

int getExpr(char** x, char** y, char* op) {
	char *inpud = getNum();
	if (inpud == NULL) {
		return -1;
	}
	char **element[] = {x, (char **)op, y};
	int index = 0;
	char *start = inpud;
	for (int i = 0; inpud[i] != '\0' && inpud[i] != '\n'; i++) {
		if (index > 2) {
			free(inpud);
			return 1;
		}
		if (inpud[i] == ' ') {
			inpud[i] = '\0';
			*element[index++] = start;
			start = &inpud[i + 1];
		}
	}
	if (index < 2) {
		free(inpud);
		return 1;
	}
	*element[index] = start;
	*op = (*element[1])[0];
	return 0;
}

int main(int argc, char* argv[]) {

	bool shell = false;
	bool silent = false;
	bool anim = false;
	//char *input1 = NULL;
	//char *input2 = NULL;

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

	while (1) {
		if (shell) {
			int getresult = getExpr(&input.x, &input.y, &input.operator);
			if (getresult == 1) {
				printf("are you stupid?\n");
				continue;
			}
			else if (getresult == -1) break;
		}

		char *abacus1 = makeAbacus(input.x);
		if (!silent) printf("%s\n", abacus1);
		if (!silent) printf("%c\n", input.operator);

		char *abacus2 = makeAbacus(input.y);
		if (!silent) printf("%s", abacus2);

		if (shell) free(input.x);

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
			default:
				printf("are you stupid?\n");
				if (shell) continue;
				else break;
		}
		if (!silent) printf("\n=\n%s = ", abacus1);
		int digits = readAbacus(abacus1);
		printf("%d", digits);

		printf("\n");
		free(abacus2);
		free(abacus1);

		if (!shell) break;
	}

	return 0;
}
