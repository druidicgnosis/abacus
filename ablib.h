#ifndef ABLIB_H

#define ABLIB_H

#define LINELEN 19
//extern int linelen;

extern char *template;
extern char *carryline;

//extern char* input1;
//extern char* input2;

extern char* allocateAbacus(int num_lines, int line_length);
extern char* initAbacus(int num_lines, int line_length);
extern bool isLine(char abacus[], int line);
extern void newLine(char **abacus);
extern int moveRight(char **abacus, int line);
extern int moveLeft(char **abacus, int line);
extern int compare(char ab1[], char ab2[]);
extern void addition(char **ab1, char **ab2);
extern void multiplication(char **ab1, char **ab2);
extern int subtraction(char **ab1, char **ab2);
extern int division(char **ab1, char **ab2);
extern int modulo(char **ab1, char **ab2);
extern char* makeAbacus(char s[]);

#endif
