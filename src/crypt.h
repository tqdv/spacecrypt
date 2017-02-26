#ifndef H_CRYPT
#define H_CRYPT

#include "clist.h"

int pgcd(int a, int b);
int invmod(int a, int b);
int mod(int x, int n);
void fctdecrypt(int* a, int* b);


#endif