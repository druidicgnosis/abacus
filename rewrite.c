#include <stdio.h>
#include <stdlib.h>

static int linelen = 19;

static char* template = "|*********-------|";
static char* carryline = "|*********-------|\n";

static char* test = "|******-------***|";
static char* test2 = "|-------*********|";

static char* input1 = "123";
static char* input2 = "54321";

char* allocateAbacus(int num_lines, int line_length) {
	char* abacus = (char*)calloc(num_lines * line_length, sizeof(char));
	if (abacus == NULL) exit(EXIT_FAILURE);
	return abacus;
}

bool isLine(char abacus[], int line) {
	int i = 1;
	for (int p = 0; abacus[p] != '\0'; p++) {
		i++;
	}
	if (i < linelen * line) return false;
	if (i >= linelen * line) return true;
}

// newLine realloc
void newLine(char **abacus) {
	int i = 1;
	for (int p = 0; (*abacus)[p] != '\0'; p++) i++;
	int newlen = i + linelen;
	char* newAb = realloc(*abacus, newlen);
	if (newAb == NULL) return;
	for (int p = 0; p < linelen; p++) {
		newAb[p+linelen] = newAb[p];
		newAb[p] = carryline[p];
	}
	*abacus = newAb;
}

// alt newLine
//void newLine(char **abacus) {
//	int i = 1;
//	for (int p = 0; (*abacus)[p] != '\0'; p++) i++;
//	printf("i:%d\n", i);
//	int newlen = i + linelen;
//	char* newAb = allocateAbacus(1, newlen);
//	if (newAb == NULL) return;
//	for (int p = 0; p < linelen; p++) newAb[p+19] = (*abacus)[p];
//	for (int p = 0; p < linelen; p++) newAb[p] = carryline[p];
//	free(*abacus);
//	*abacus = newAb;
//}

//need isLine and newLine for this.
int moveRight(char **abacus, int line) {

	while (!isLine(*abacus, line)) newLine(abacus);

	bool foundBead = false;

	int len = 0;
	while ((*abacus)[len] != '\0') len++;

	int line_start = len - (linelen * line) + 1;
	int line_end = len - (linelen * (line - 1)) - 1;

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

int main() {

	// test for carry creating new line
	char* Ab = allocateAbacus(1, linelen);
	Ab[18] = '\0';
	for (int i = 0; i < linelen; i++) Ab[i] = test2[i];
	printf("Ab:\n%s\n", Ab);
	moveRight(&Ab, 1);
	printf("moveRight(Ab, 1):\n%s\n", Ab);
	free(Ab);

	// test for carry to existing line
	char* Ab2 = allocateAbacus(1, linelen);
	Ab2[18] = '\0';
	for (int i = 0; i < linelen; i++) Ab2[i] = test2[i];
	newLine(&Ab2);
	printf("Ab2:\n%s\n", Ab2);
	moveRight(&Ab2, 1);
	printf("moveRight(Ab2, 1):\n%s\n", Ab2);
	free(Ab2);

	return 0;
}
