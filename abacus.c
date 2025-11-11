#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char template[19] =
{'|','*','*','*','*','*','*','*','*','*','-','-','-','-','-','-','-','|','\0',};
static char carryline[19] =
{'|','*','*','*','*','*','*','*','*','*','-','-','-','-','-','-','-','|','\n',};

char* allAbacus(int num_lines, int line_length) {
	return (char*)calloc((1 + (num_lines * line_length)), sizeof(char));
}

int moveRight(char line[]) {
	int len = 18;

	bool foundBead = false;

	for (int i = 0; i < len; i++) {
		if (line[i] == '*' && line[i+1] == '-') {
			foundBead = true;
			break;
		}
	}

	if (!foundBead) return 2;

	for (int i = 0; i < len; i++) {
		if (line[i] == '*' && line[i+1] == '-') {
			for (int j = len - 1; j > i; j--) {
				if (line[j] != '*' && line[j] != '|') {
					char temp = line[i];
					line[i] = line[j];
					line[j] = temp;
					return 0;
				}
			}
			break;
		}
	}
	return 1;
}

// input

char* getNum() {
	size_t input_size = 0;
	char* input_line = NULL;
	printf("Give us a number: ");
	if (getline(&input_line, &input_size, stdin) == -1) {
		free(input_line);
		return NULL;
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

char* makeAb(char s[], int k) {
	char *fullAb = NULL;
	int abLines = k;
	fullAb = allAbacus(abLines, 19);
	char tempAb[19];

	for (int j = 0; j < k; j++) {
		for (int i = 0; i != 19; i++) tempAb[i] = carryline[i];
		for (int i = 0; i != s[j] - '0'; i++) {
			moveRight(tempAb);
		}
		for (int p = 0; p < 19; p++) {
			fullAb[p + j*19] = tempAb[p];
		}
	}
	//fullAb[18+k*19] = '\0';
	return fullAb;
}
char* newLine(char abacus[]) {
	int i = 1;
	for (int q = 0; abacus[q] != '\0'; q++) i++;
	char *new = (char *)calloc((i + 19), sizeof(char));
	for (int q = 0; q < i; q++) {
		new[19 + q] = abacus[q];
	}
	for (int q = 0; q < 18; q++) new[q] = template[q];
	new[18] = '\n';
	return new;
}

char* selecta(char abacus[], int k) {
	int i = 0;
	for (int q = 0; abacus[q] != '\0'; q++) i++;
	if (i < 19 + k*19) return NULL;
	i -= 3+(k*19);
	for (int q = i; abacus[q] != '|'; q--) i--;
	//char *new = NULL;
	//new = calloc(19, sizeof(char));
	char *new = (char *)calloc(19, sizeof(char));
	for (int q = 0; q < 19; q++) {
		new[q] = abacus[i+q];
	}
	return new;
}
bool isLine(char abacus[], int k) {
	int i = 0;
	for (int q = 0; abacus[q] != '\0'; q++) i++;
	if (i < 19 + k*19) return false;
	return true;
}

bool addLines(char a[], char b[]) {
	int q = 1;
	bool carry = false;
	for (int i = 1; i < 18; i++) {
		if (a[i] == '*' && a[i - q] == '-') {
			int res = moveRight(b);
			if (res == 0) {
				q++;
			}
			if (res == 2) {
				for (int i = 0; i < 19; i++) b[i] = template[i];
				carry = true;
				q++;
			}
		}
	}
	return carry;
}

void readAbacus(char abacus[]) {
	int k = 0;
	char num = '0';
	char *temp = selecta(abacus, 0);
	//for (int i = 0; selecta(abacus, i) != NULL; i++) k++;
	for (int i = 1; temp != NULL; i++) {
		k++;
		free(temp);
		temp = selecta(abacus, i);
	}

	for (int i = k-1; i >= 0; i--) {
		free(temp);
		temp = selecta(abacus, i);
		//char *temp = selecta(abacus, i);
		//printf("selecta %d: %s\n", i, selecta(abacus, i));
		num = '9';
		for (;moveRight(temp) != 2;) {
			num--;
		}
		printf("%c", num);
	}
	free(temp);
}
int moveOne(char line[]) {
	int len = 18;

	bool foundBead = false;

	for (int i = 0; i < len; i++) {
		if (line[i] == '*' && line[i+1] == '-') {
			foundBead = true;
			break;
		}
	}

	if (!foundBead) return 2;

	for (int i = 1; i < len; i++) {
		if (line[i] == '*' && line[i+1] == '-' && line[i-1] == '-') {
			char temp = line[i];
			line[i] = line[i+1];
			line[i+1] = temp;
			if (line[i+2] == '*' || line[i+2] == '|') return 1;
			return 0;
		}
	}
	for (int i = 1; i < len; i++) {
		if (line[i] == '*' && line[i+1] == '-') {
			char temp = line[i];
			line[i] = line[i+1];
			line[i+1] = temp;
			return 0;
		}
	}
	return 0;
}

char* addAbucii(char abacus1[], char abacus2[], bool animation) {
	bool carried = false;
	char cared[19];
	int count = 0;
	char *out = NULL;
	out = (char*)calloc(19, sizeof(char));
	for (int k = 0; isLine(abacus1, k) || isLine(abacus2, k); k++) {
		char *temp = newLine(out);
		free(out);
		out = temp;

		if (!isLine(abacus2, k)) {
			char *tmp = newLine(abacus2);
			free(abacus2);
			abacus2 = tmp;
		}
		if (!isLine(abacus1, k)) {
			char *tmp = newLine(abacus1);
			free(abacus1);
			abacus1 = tmp;
		}
		char *aline = selecta(abacus1, k);
		char *bline = selecta(abacus2, k);

		if (carried) carried = addLines(cared, bline);
		bool tocarry = addLines(aline, bline);

		for (int i = 0; i < 18; i++) {
			out[i] = bline[i];
		}
		if (tocarry) {
			for (int i = 0; i < 18; i++) {
				cared[i] = template[i];
			}

			cared[18] = '\0';
			moveRight(cared);
			if (carried) moveRight(cared);

			carried = true;
		}
		//NEW for DISPLAUY
		if (animation) {
			//printf("\n\n");
			//printf("\033[s");
			int t = 0;
			int p = 0;
			for (int q = 0; isLine(abacus1, q) || isLine(abacus2, q); q++) t++;
			for (int q = 0; abacus2[q] != '\0'; q++) p++;
			bool dons = false;
			while (!dons) {
				for (int i = 0; i < 18; i++) {
					abacus2[p - 19*(k+1) + i] = bline[i];
				}
				//printf("\033[%d;1H", k + 1);
				//printf("\033[2K");

				//printf("\033[%d;%dH", t + 1, 19 + 1);

				printf("%c[2J%c[;H",(char) 27, (char) 27);
				//fflush(stdout);
				usleep(10000);
				printf("\r%s", abacus2);
				if (moveOne(bline) == 2) dons = true;
			}
			for (int i = 0; i < 18; i++) {
				abacus2[p - 19*(k+1) + i] = out[i];
			}
			//printf("\033[%d;1H", k + 1);
			//printf("\033[2K");

			printf("%c[2J%c[;H",(char) 27, (char) 27);
			//fflush(stdout);
			usleep(50000);
			printf("\r%s", abacus2);
			//printf("%s\n", out);
		}

		free(aline);
		free(bline);
		count++;
	}
	if (carried) {

		char *final = selecta(out, count);
		if (final == NULL) {
			char *temp = newLine(out);
			free(out);
			out = temp;
			free(final);
			final = selecta(out, count);
		}
		addLines(cared, final);
		for (int i = 0; i < 18; i++) out[i] = final[i];
		free(final);
	}
	free(abacus1);
	free(abacus2);
	return out;
}
void displayAbs(char* abacus1, char* abacus2) {
	int k_1 = 0;
	int k_2 = 0;

	for (int i = 0; isLine(abacus1, i); i++) k_1++;
	for (int i = 0; isLine(abacus2, i); i++) k_2++;

	int k = 0;
	if (k_1 > k_2) k = k_1;
	if (k_1 < k_2) k = k_2;
	if (k_1 == k_2) k = k_1;

	int half_k = 0;
	half_k = (k - (k % 2)) / 2;

	for (int i = 0; i < k; i++) {
		if (i + k_1 < k && k_1 != k) {
			for (int j = 0; j != 18; j++) printf("%c", ' ');
		}
		if (k_1 == k) {
			for (int j = 0; j != 18; j++) printf("%c", abacus1[j + (i * 19)]);
		}
		if (i + k_1 >= k && k_1 != k) {
			for (int j = 0; j != 18; j++) printf("%c", abacus1[j + (i - k + k_1) * 19]);
		}
		if (i == half_k) printf("+");
		if (i != half_k) printf(" ");

		if (i + k_2 < k && k_2 != k) {
			for (int j = 0; j != 18; j++) printf("%c", ' ');
		}
		if (k_2 == k) {
			for (int j = 0; j != 18; j++) printf("%c", abacus2[j + (i * 19)]);
		}
		if (i + k_2 >= k && k_2 != k) {
			for (int j = 0; j != 18; j++) printf("%c", abacus2[j + ((i - k + k_2) * 19)]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]) {

	printf("\033[s");
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

	if (shell) input1 = getNum();
	//if (!shell) input1 = argv[1];
	int g = readNum(input1);

	char *abacus1 = makeAb(input1, g);
	if (shell) free(input1);
	if (!silent && shell) printf("%s", abacus1);
	//if (!silent && !shell) printf("+\n");

	if (shell) input2 = getNum();
	//if (!shell) input2 = argv[2];
	int k2 = readNum(input2);

	char *abacus2 = makeAb(input2, k2);
	if (shell) free(input2);
	if (!silent && shell) printf("%s", abacus2);

	//char *aba2_copy = strdup(abacus2);

	if (!silent && !shell && !anim) displayAbs(abacus1, abacus2);
	//char* combined = NULL;
	//if (!silent) combined = gen_displayAbs(abacus1, abacus2);


	char* result = addAbucii(abacus1, abacus2, anim);
	//printf("%s", abacus2);

	if (!silent && shell) printf("Your result sir:\n%s", result);
	if (!silent && !shell && !anim) printf("=\n%s", result);
	readAbacus(result);
	printf("\n");
	free(result);

	return 0;
}
