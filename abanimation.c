#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ablib.h"

int degub = 0;

int powTen(int i) {
	int result = 1;
	for (int p = 0; p < i; p++) {
		result *= 10;
	}
	return result;
}

int carryAnim(char **abacus, int line) {	// could ts be part of the main function? global bool ts?

	int len = 0;
	while ((*abacus)[len] != '\0') len++;
	int line_start = len - (LINELEN * line) + 1;
	int line_end = line_start + LINELEN - 2;

	int j = 0;
	for (int i = line_end - 1; i > line_start; i--) {
		if ((*abacus)[i] == '*' && (*abacus)[i - 1] == '*' && ( (*abacus)[i + 1] == '-' || (*abacus)[i + 1] == '|' )) {
				if (!j) j = i;
		}
		if ((*abacus)[i] == '-' && (*abacus)[i + 1] == '*' && j) {
			char tmp = (*abacus)[i];
			(*abacus)[i] = (*abacus)[j];
			(*abacus)[j] = tmp;
			return 0;
		}
	}
	return 1;
}

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
		//for (int i = 0; i < 9; i++) moveLeft(abacus, line);
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

int main() {
	int done = 0;
	char *aba = initAbacus(LINELEN, 1);
	//char *aba = makeAbacus("9");

	if (degub) printf("%s\n", "some bull shit that the animation shoul dnot overwrite");

	printf("%s\n", aba);


	int p = 0;
	int q = 1;
	int powa = 10;
	int caried = 0;
	while (!done) {

		usleep(30000);

		printf("\033[%dA", q);

		printf("\033[0J");

		int eres = shiftRight(&aba, 1);
		if (eres == 3) {
			p += 10;
			caried = 7;
		}

		if (p > 0 && p % powa == 0) {
			powa *= 10;
			q++;
		}
		if (caried) {
			for (int s = 1; s < q; s++) {
				if ( p % (powa / powTen(q - s)) == 0 ) carryAnim(&aba, s);
			}
			--caried;
		}
		if (degub) printf("%s q: %d, caried: %d, powa: %d, p: %d, powTen(2): %d\n", aba, q, caried, powa, p, powTen(2));
		else printf("%s\n", aba);
	}
	printf("\n");
}
