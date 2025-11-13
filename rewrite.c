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

char* initAbacus(int num_lines, int line_length) {
	char* abacus = (char*)calloc(num_lines * line_length, sizeof(char));
	if (abacus == NULL) exit(EXIT_FAILURE);
	for (int i = 0; i < linelen; i++) abacus[i] = template[i];
	return abacus;
}

bool isLine(char abacus[], int line) {
	int i = 2;
	for (int p = 0; abacus[p] != '\0'; p++) {
		i++;
	}
	if (i < linelen * line) return false;
	if (i >= linelen * line) return true;
}

// newLine realloc	// unfucked
void newLine(char **abacus) {
	int i = 1;
	for (int p = 0; (*abacus)[p] != '\0'; p++) i++;
	int newlen = i + linelen;
	char* newAb = realloc(*abacus, newlen);
	if (newAb == NULL) return;

	for (int p = i - 1; p >= 0; p--) newAb[p + linelen] = newAb[p];
	for (int p = 0; p < linelen; p++) newAb[p] = carryline[p];

	*abacus = newAb;
}

//need isLine and newLine for this.
int moveRight(char **abacus, int line) {

	while (!isLine(*abacus, line)) newLine(abacus);

	bool foundBead = false;

	int len = 0;
	while ((*abacus)[len] != '\0') len++;

	int line_start = len - (linelen * line) + 1;
	int line_end = len - (linelen * (line - 1)) - 1;	// why. ts jst linestart + linelen -1

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

	int line_start = len - (linelen * line) + 1;
	int line_end = line_start + linelen - 2;
	//printf("linestart: %c\nlineend: %c\n", (*abacus)[line_start], (*abacus)[line_end]);

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
}

// new jawns below
int compare(char ab1[], char ab2[]) {
	for (int i = 0; isLine(ab1, i) || isLine(ab2, i); i++) {
		if (!isLine(ab1, i)) return 2;
		if (!isLine(ab2, i)) return 1;
	}
	//idk same thing but like ab1[i] == * && ab1[i+] || ...
	//hmm... cant just count and compare that'd be cheating. make temp and cmpr 9s complement?
	//more like jst if there exist ab1[i] == * && ab2[i] != * for i <= 9
	for (int k = 1; ab1[(k*linelen)-1] != '\0'; k++) {
		for (int i = 1; i <= 9; i++) {
			if (ab1[i + ((k-1)*linelen)] == '*' && ab2[i + ((k-1)*linelen)] == '-') return 2;
			if (ab1[i + ((k-1)*linelen)] == '-' && ab2[i + ((k-1)*linelen)] == '*') return 1;
		}
	}
	return 0;
}

void addalt(char **ab1, char **ab2) {	// can't add abacus to itself
	while (moveLeft(ab1, 1) != 2) moveRight(ab2, 1);
}

void addition(char **ab1, char **ab2) {

	int len = 0;
	while ((*ab1)[len] != '\0') len++;

	int k = 1;
	int q = 1;
	while (isLine(*ab1, k)) {
		int line_start = len - (linelen * k) + 1;
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
	char *result = initAbacus(19, 1);
	//char *temp = initAbacus(19, 1);
	while (subtraction(ab1, ab2) != 1) {
		moveRight(&result, 1);
	}
	free(*ab2);
	*ab2 = result;
}

int modulo(char **ab1, char **ab2) {
	while (subtraction(ab1, ab2) != 1);
	return 0;
}

// input &etc
char* makeAbacus(char s[]) {
	char *out = allocateAbacus(1, linelen);
	out[18] = '\0';
	for (int i = 0; i < linelen; i++) out[i] = template[i];

	int k = 0;
	while (s[k] != '\0') k++;

	for (int i = k - 1; i >= 0; i--) {
		int j = 0;
		while (j != s[i] - '0') {
			moveRight(&out, k - i);
			j++;
		}
	}
	return out;
}

int main() {

	//// test for carry creating new line
	char* Ab = allocateAbacus(1, linelen);
	Ab[18] = '\0';
	for (int i = 0; i < linelen; i++) Ab[i] = test2[i];

	printf("Ab:\n%s", Ab);
	//moveRight(&Ab, 1);
	//printf("moveRight(Ab, 1):\n%s\n", Ab);
	////free(Ab);

	//// test for carry to existing line
	//char* Ab2 = allocateAbacus(1, linelen);
	//Ab2[18] = '\0';
	//for (int i = 0; i < linelen; i++) Ab2[i] = test2[i];
	//newLine(&Ab2);
	//printf("Ab2:\n%s\n", Ab2);
	//moveRight(&Ab2, 1);
	//moveRight(&Ab2, 1);
	//printf("moveRight(Ab2, 1):\n%s\n", Ab2);
	////free(Ab2);

	////addition
	//addition(&Ab, &Ab2);
	//printf("addition:\n%s\n", Ab2);
	//addition(&Ab2, &Ab2);
	//printf("multiplication: ab2*2:\n%s", Ab2);
	//printf("\ncompare(Ab, Ab2): %d\n", compare(Ab, Ab2));
	//free(Ab);
	//free(Ab2);

	char* abonis = makeAbacus(input1);
	printf("\nmakeAb(%s):\n%s", input1, abonis);

	//multiplication(&abonis, &Ab);
	subtraction(&Ab, &abonis);
	printf("\nabonis - Ab:\n%s", abonis);
	printf("\nAb post subtraction:\n%s", Ab);

	// division
	division(&Ab, &abonis);
	printf("\nabonis / Ab:\n%s", abonis);
	printf("\nAb post division:\n%s", Ab);

	//modulo
	modulo(&Ab, &abonis);
	printf("\nabonis %% Ab:\n%s", abonis);

	printf("\n");
	free(abonis);
	free(Ab);

	return 0;
}
