#ifndef H_CLIST
#define H_CLIST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <ctype.h>

#define BLACK 0
#define DARKBLUE 1
#define GREEN 2
#define BLUEGREY 3
#define BROWN 4
#define PURPLE 5
#define KAKI 6
#define LIGHTGREY 7
#define GREY 8
#define BLUE 9
#define LIME 10
#define CYAN 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15

#define HLIME a
#define HCYAN b
#define HRED c
#define HPINK d
#define HYELLOW e
#define HWHITE f

typedef struct El El;
struct El {
	int n;
	/*int x;
	int y;*/
	El *next;
};

typedef struct List List;
struct List {
	El *first;
	int size;
};

typedef struct DEl DEl;
struct DEl {
	int n;
	DEl *next;
	DEl *prec;
	int pos;
};

typedef struct DList DList;
struct DList {
	DEl *first;
	int size;
};


typedef struct Coord Coord;
struct Coord {
	int x;
	int y;
};

void lerr(List*);
List* linit(int);
DList* dlinit(int firstValue);
void eins(List*, int);
void edel(List*);
void laff(List*);
List* tablist(int, int);
El* efindfirst(List*, int);
void einsel(List*, El*, int);
void edelel(List*, El*);
void ldel(List*);
int efindmulti(List*, El***, int);
void ereplall(List*, int, int);
void edelall(List*, int);
void empiler(List*, int);
int depiler(List*);
void affpile(List*);
void enfiler(List*, int);
int defiler(List*);
void afffile(List*);
void secureread(char *word, int maxsize);
void buffercls(void);
void error(void);
List* totolist(int, int, int);
char* ecoread(int);
List* lrand(int, int, int);
int ecount(List*, int);
long longread(void);
void elproba(List*, int, int);
int lsomme(List*);
void cls(void);
char** tabxychar(int, int);
void color(int, int);
void printfcolor(char*);
int** tabxyint(int, int);
long** tabxylong(long x, long y);
double** tabxydouble(int x, int y);
FILE* sfile(char* dossier, char* fichier, char* extension, char* mode);
FILE* readfile(char* nom);
void nextdladd(DEl *el, int value);
void precdladd(DList* l, DEl *el, int value);
char* romanize(int n);
char* reverstring(char* string, int size);
int* revertab(int* tab, int size);
int* longtotab(long n);
List* tabtolist(int* tab, int size);
List* longtolist(long n);
int* listtotab(List* l);
int fwcount(FILE* f);

#endif