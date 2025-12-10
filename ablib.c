#include <stdio.h>
#include <stdlib.h>

#include "ablib.h"

char* template = "|*********-------|";
char* carryline = "|*********-------|\n";

char* allocateAbacus(int num_lines, int line_length) {
	char* abacus = calloc(num_lines * line_length, sizeof(char));
	if (abacus == NULL) exit(EXIT_FAILURE);
	return abacus;
}

char* initAbacus(int num_lines, int line_length) {
	char* abacus = calloc(num_lines * line_length, sizeof(char));
	if (abacus == NULL) exit(EXIT_FAILURE);
	for (int i = 0; i < LINELEN; i++) abacus[i] = template[i];
	return abacus;
}

bool isLine(char abacus[], int line) {
	int i = 2;
	for (int p = 0; abacus[p] != '\0'; p++) {
		i++;
	}
	if (i < LINELEN * line) return false;
	else return true;
}

// newLine realloc	// unfucked
void newLine(char **abacus) {
	int i = 1;
	for (int p = 0; (*abacus)[p] != '\0'; p++) i++;
	int newlen = i + LINELEN;
	char* newAb = realloc(*abacus, newlen);
	if (newAb == NULL) return;

	for (int p = i - 1; p >= 0; p--) newAb[p + LINELEN] = newAb[p];
	for (int p = 0; p < LINELEN; p++) newAb[p] = carryline[p];

	*abacus = newAb;
}

//need isLine and newLine for this.
int moveRight(char **abacus, int line) {

	while (!isLine(*abacus, line)) newLine(abacus);

	bool foundBead = false;

	int len = 0;
	while ((*abacus)[len] != '\0') len++;

	int line_start = len - (LINELEN * line) + 1;
	int line_end = len - (LINELEN * (line - 1)) - 1;	// why. ts jst linestart + LINELEN -1

	for (int i = line_start; i < line_end; i++) {
		if ((*abacus)[i] == '*' && (*abacus)[i+1] == '-') {
			foundBead = true;
			break;
		}
		if ((*abacus)[i] == '-' && (*abacus)[i+1] == '*') {
			foundBead = false;
			break;
		}
	}

	if (!foundBead) {
		for (int i = line_start; i < line_end; i++) (*abacus)[i] = carryline[i - line_start];
		moveRight(abacus, line + 1);
		return 0;
	}

	for (int i = line_start; i < line_end; i++) {
		if ((*abacus)[i] == '*' && (*abacus)[i+1] == '-') {
			for (int j = line_end - 1; j > i; j--) {
				if ((*abacus)[j] != '*' && (*abacus)[j] != '|') {
					char temp = (*abacus)[i];
					(*abacus)[i] = (*abacus)[j];
					(*abacus)[j] = temp;
					return 0;
				}
			}
			break;
		}
	}
	return 1;
}

int moveLeft(char **abacus, int line) {

	if (!isLine(*abacus, line)) return 2;

	bool foundBead = false;

	int len = 1;
	while ((*abacus)[len] != '\0') len++;

	int line_start = len - (LINELEN * line) + 1;
	int line_end = line_start + LINELEN - 2;

	for (int i = line_start; i < line_end; i++) {
		if ((*abacus)[i+1] == '*' && ((*abacus)[i] == '-')) {
			foundBead = true;
			break;
		}
		if ((*abacus)[i] == '-' && (*abacus)[i+1] == '|') {
			foundBead = false;
			break;
		}
	}

	if (!foundBead) {
		if (moveLeft(abacus, line + 1) != 2) {
			for (int i = 0; i < 9; i++) moveRight(abacus, line);
			return 0;
		}
		else return 2;
	}

	for (int i = line_end; i > line_start; i--) {
		if ((*abacus)[i] == '*' && (*abacus)[i-1] == '-') {
			for (int j = line_start + 1; j < i; j++) {
				if ((*abacus)[j] != '*' && (*abacus)[j] != '|') {
					char temp = (*abacus)[i];
					(*abacus)[i] = (*abacus)[j];
					(*abacus)[j] = temp;
					return 0;
				}
			}
			break;
		}
	}
	return 1;
}

// new jawns below
int compare(char ab1[], char ab2[]) {	//prev. returned which was bigger but changed for now to return equality
	for (int i = 0; isLine(ab1, i) || isLine(ab2, i); i++) {
		if (!isLine(ab1, i)) return 0;
		if (!isLine(ab2, i)) return 0;
	}
	//idk same thing but like ab1[i] == * && ab1[i+] || ...
	//hmm... cant just count and compare that'd be cheating. make temp and cmpr 9s complement?
	//more like jst if there exist ab1[i] == * && ab2[i] != * for i <= 9
	for (int k = 1; ab1[(k*LINELEN)-1] != '\0'; k++) {
		for (int i = 1; i <= 9; i++) {
			if (ab1[i + ((k-1)*LINELEN)] == '*' && ab2[i + ((k-1)*LINELEN)] == '-') return 0;
			if (ab1[i + ((k-1)*LINELEN)] == '-' && ab2[i + ((k-1)*LINELEN)] == '*') return 0;
		}
	}
	return 1;
}

//void addalt(char **ab1, char **ab2) {	// can't add abacus to itself
//	while (moveLeft(ab1, 1) != 2) moveRight(ab2, 1);
//}

void addition(char **ab1, char **ab2) {	//ab1 unchanged ab2a result
										//^le industry worst practice. let the code speak for itself bro
	int len = 0;
	while ((*ab1)[len] != '\0') len++;

	int k = 1;
	int q = 1;
	while (isLine(*ab1, k)) {
		int line_start = len - (LINELEN * k) + 1;
		for (int p = line_start + 1; p < line_start + 17; p++) {
			if ((*ab1)[p] == '*' && (*ab1)[p - q] == '-') {
				moveRight(ab2, k);
				q++;
			}
		}
		k++;
		q = 1;
	}
}

void multiplication(char **ab1, char **ab2) {	//subtraction first? some sort of moveleft firster?
	char *multiple = initAbacus(19, 1);
	bool first = true;
	while (moveLeft(ab1, 1) != 2) {
		if (first) addition(ab2, &multiple);
		else addition(&multiple, ab2);
		first = false;
	}
	free(multiple);
}

int subtraction(char **ab1, char **ab2) {	//subtracting 1 from 2
											//added maintaining ab1 value. feels like bloat but necessary for division afaik
	bool negative = false;
	char *ab1cpy = initAbacus(1, 19);

	while (moveLeft(ab1, 1) != 2) {
		moveRight(&ab1cpy, 1);
		if (moveLeft(ab2, 1) == 2) {
			moveRight(ab2, 1);
			negative = true;
			break;
		}
	}
	if (!negative) {
		free(*ab1);
		*ab1 = ab1cpy;
		return 0;
	}
	while (moveLeft(ab1, 1) != 2) {
		moveRight(ab2, 1);
		moveRight(&ab1cpy, 1);
	}
	free(*ab1);
	*ab1 = ab1cpy;
	return 1;
}

int division(char **ab1, char **ab2) {	//dividing 2 by 1
	char *result = initAbacus(LINELEN, 1);
	while (subtraction(ab1, ab2) != 1) {
		moveRight(&result, 1);
	}
	free(*ab2);
	*ab2 = result;
	return 0;
}

int modulo(char **ab1, char **ab2) {	//ab2 % ab1
	char *ab1cpy = initAbacus(LINELEN, 1);
	int res = subtraction(ab1, ab2);
	while (res != 1) {
		res = subtraction(ab1, ab2);
	}
	addition(ab1, &ab1cpy);
	subtraction(ab2, ab1);
	free(*ab2);
	*ab2 = *ab1;
	*ab1 = ab1cpy;
	return 0;
}

// input &etc
char* makeAbacus(char s[]) {
	char *out = initAbacus(LINELEN, 1);

	int k = 0;
	while (s[k] != '\0') {
		k++;
	}

	for (int i = k - 1; i >= 0; i--) {
		int j = 0;

		char c = '0';
		if (s[i] < '0' || s[i] > '9') c = s[i];
		else c = s[i] - '0';

		while (j != c) {
			moveRight(&out, k - i);
			j++;
		}
	}
	return out;
}

int readAbacus(char* aba) {

	int head = 0;
	int digit = 9;
	int out = 0;
	int lineNo = 1;

	do {
		out *= 10;
		while (aba[++head] != '-') {
			digit--;
		}
		out += digit;
		digit = 9;
		head = LINELEN * lineNo++ - 1;
	} while (aba[head++] != '\0');

	return out;
}

char* intAb(int num) {

	char str[20];
	snprintf(str, sizeof(str), "%d", num);

	char* abacus = makeAbacus(str);

	return abacus;
}
