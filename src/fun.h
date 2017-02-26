#ifndef H_FUN
#define H_FUN

#include "clist.h"
#include "crypt.h"

char** getwords(FILE* in, int* nword, int** sizes);
char* getpassword();
char** spaceencrypt(char** words, int n, int* sizes, char* password);
char** spacedecrypt(char** cwords, int n, int* sizes, char* password);
void tooutput(FILE* out, char** words, int n, int* sizes, char* password);
int* readhints(FILE* in, int* n, char* password);
char** getcwords(FILE* in, int n, int* sizes);
void finalout(FILE* out, char** words, int n);

#endif