#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ablib.h"

//static char termlate[19] =
//{'|','*','*','*','*','*','*','*','*','*','-','-','-','-','-','-','-','|', '\0',};

int shiftRight(char **abacus, int line) {	// exits: 0 = completed move, 1 = error, 2 = successful partial move, 3 = carry creating newline

	while (!isLine(*abacus, line)) newLine(abacus);

	int foundBead = 0;

	int len = 0;
	while ((*abacus)[len] != '\0') len++;

	int line_start = len - (LINELEN * line) + 1;
	int line_end = len - (LINELEN * (line - 1)) - 1;	// why. ts jst linestart + LINELEN -2

	for (int i = 1; (*abacus)[i] != '\0'; i++) {
		if ((*abacus)[i] == '*' && (*abacus)[i+1] == '-' && (*abacus)[i-1] == '-') {
			char temp = (*abacus)[i];
			(*abacus)[i] = (*abacus)[i + 1];
			(*abacus)[i + 1] = temp;

			if ((*abacus)[i + 2] == '|' || (*abacus)[i + 2] == '*') return 0;	//new check for completion
			else return 2;
		}
	}

	for (int i = line_start; i < line_end; i++) {
		if ((*abacus)[i] == '*' && (*abacus)[i+1] == '-') {
			foundBead = 1;
			break;
		}
	}

	if (!foundBead) {
		//for (int i = line_start; i < line_end; i++) (*abacus)[i] = carryline[i - line_start];
		for (int i = 0; i < 9; i++) moveLeft(abacus, line);
		shiftRight(abacus, line + 1);
		return 3;
	}

	for (int i = line_start; i < line_end; i++) {
		if ((*abacus)[i] == '*' && (*abacus)[i+1] == '-') {
			char temp = (*abacus)[i];
			(*abacus)[i] = (*abacus)[i + 1];
			(*abacus)[i + 1] = temp;
			return 2;
		}
	}
	return 1;
}

//int shiftRightWrapper(char **abacus, int line) {
//	int complete = 0;
//
//	while (!complete) {
//		shiftRight(abacus, line);
//}

int main() {
	bool done = false;
	char *aba = initAbacus(LINELEN, 1);

	printf("%s\n", aba);


	int p = 0;
	int q = 1;
	int powa = 10;
	while (!done) {

		usleep(10000);

		printf("\033[%dA", q);

		printf("\033[0J");

		//if (shiftRight(&aba, 1) == 3) {
		//	powa *= 10;
		//	q++;
		//}

		int eflag = shiftRight(&aba, 1);
		if (eflag == 3) {
			powa *= 10;
			q++;
		}
		//if (eflag == 0) printf("%s complete\n", aba);
		//else printf("%s\n", aba);
		printf("%s\n", aba);
	}
	printf("\n");
}
