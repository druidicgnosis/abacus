#include <stdio.h>
#include <stdlib.h>

static char* template = "|*********-------|";
static char* carryline = "|*********-------|\n";
static char* test = "|******-------***|";

static char* input1 = "123";
static char* input2 = "54321";

char* allocateAbacus(int num_lines, int line_length) {
	char* abacus = (char*)calloc(num_lines * line_length, sizeof(char));
	if (abacus == NULL) exit(EXIT_FAILURE);
	return abacus;
}

bool isLine(char abacus[], int line) {
	int i = 1;	// i=1 so i refers to len not index
	for (int p = 0; abacus[p] != '\0'; p++) i++;
	if (i < 19 * line) return false;
	if (i >= 19 * line) return true;
}

void newLine(char **abacus) {
	int i = 1;	// i=1 so i refers to len not index
	for (int p = 0; (*abacus)[p] != '\0'; p++) i++;
	int newlen = i + 19;
	char* newAb = realloc(*abacus, newlen);
	if (newAb == NULL) return;
	for (int p = 0; p < 19; p++) newAb[p+19] = newAb[p];
	for (int p = 0; p < 19; p++) newAb[p] = carryline[p];
	*abacus = newAb;
}

//need isLine and newLine for this.
int moveRight(char abacus[], int line) {

	bool foundBead = false;
}

int main() {

	char* Ab = allocateAbacus(1, 19);

	//Bullshid testing
	//for (int i = 0; i < 20; i++) Ab[i] = test[i];
	//printf("Ab: \n%s\n", Ab);
	//char* newAb = realloc(Ab, 28);
	//for (int p = 0; p < 19; p++) newAb[p+19] = newAb[p];
	//for (int p = 0; p < 19; p++) newAb[p] = carryline[p];
	//printf("newAb: \n%s", newAb);

	for (int i = 0; i < 19; i++) Ab[i] = template[i];
	if (isLine(Ab, 1)) printf("Ab at least 1 line long\n");
	if (!isLine(Ab, 2)) printf("Ab NOT 2 line long\n");

	newLine(&Ab);
	printf("%s\n", Ab);

	
	if (isLine(Ab, 1)) printf("Ab at least 1 line long\n");
	if (!isLine(Ab, 2)) printf("Ab NOT 2 line long\n");
	else printf("Ab at least 2 line long");
	return 0;
}
