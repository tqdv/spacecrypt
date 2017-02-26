/*Advise: Don't try to read this, this is just my awful holdall file I drag and complete with each new program I make.
Some function name are still in french and uncommented, so if you really want to see, good luck,
I even forgotten how I did many of them with time, that's why this file is useful:
I put here useful function and structures I'm likely to use on future programs
Yes I know, they're not all useful*/

#define _CRT_SECURE_NO_WARNINGS
#include "clist.h"

void lerr(List* liste) {
	if (liste == NULL) {
		exit(EXIT_FAILURE);
	}
}

List* linit(int firstValue) {
	List *liste = malloc(sizeof(*liste));
	El *element = malloc(sizeof(*element));

	if (liste == NULL || element == NULL) {
		exit(EXIT_FAILURE);
	}

	element->n = firstValue;
	element->next = NULL;
	liste->first = element;
	liste->size = 1;

	return liste;
}

DList* dlinit(int firstValue) {
	DList *liste = malloc(sizeof(*liste));
	DEl *element = malloc(sizeof(*element));

	if (liste == NULL || element == NULL) {
		exit(EXIT_FAILURE);
	}

	element->n = firstValue;
	element->next = NULL;
	element->prec = NULL;
	element->pos = 0;
	liste->first = element;
	liste->size = 1;

	return liste;
}

void eins(List* liste, int value) {
	El *newel = malloc(sizeof(*newel));
	if (newel == NULL || liste == NULL) {
		exit(EXIT_FAILURE);
	}
	newel->n = value;
	newel->next = liste->first;
	liste->first = newel;
	liste->size++;
}

void edel(List* liste) {
	lerr(liste);
	if (liste->first != NULL) {
		El *suppr = liste->first;
		liste->first = liste->first->next;
		free(suppr);
		liste->size--;
	}
}

void laff(List* liste) {
	lerr(liste);

	El *aff = liste->first;

	while (aff != NULL) {
		printf("%d -> ", aff->n);
		aff = aff->next;
	}
	printf("NULL\n");
}

List* tablist(int taille, int value) {
	List *liste = linit(value);
	lerr(liste);
	int i = 0;
	for (i = 0; i < taille - 1; i++) {
		eins(liste, value);
	}
	return liste;
}

El* efindfirst(List* liste, int value) {
	lerr(liste);
	El *etemp = liste->first;
	int temp = etemp->n;
	while (temp != value && etemp != NULL) {
		etemp = etemp->next;
		temp = etemp->n;
	}
	return etemp;
}

void einsel(List* liste, El* el, int value) {
	lerr(liste);
	El *temp = liste->first;
	while (temp != el && temp != NULL) {
		temp = temp->next;
	}
	if (temp == NULL) {
		exit(EXIT_FAILURE);
	}
	else {
		El *newel = malloc(sizeof(*newel));
		newel->n = value;
		newel->next = temp->next;
		temp->next = newel;
		liste->size++;
	}
}

void edelel(List* liste, El* el) {
	lerr(liste);
	El *temp = liste->first;
	El *previoustemp = temp;
	if (temp == el) {
		liste->first = el->next;
		free(el);
		liste->size--;
	}
	else {
		while (temp != el && temp != NULL) {
			previoustemp = temp;
			temp = temp->next;
		}
		if (temp != NULL) {
			previoustemp->next = el->next;
			free(el);
			liste->size--;
		}
	}
}

void ldel(List* liste) {
	lerr(liste);
	El *temp = liste->first;
	El *nextemp = temp->next;
	while (nextemp != NULL) {
		free(temp);
		temp = nextemp;
		nextemp = temp->next;
		liste->size--;
	}
	liste->first = NULL;
}

int efindmulti(List* liste, El*** found, int value) {
	lerr(liste);
	int i = 0;
	El *temp = liste->first;
	while (temp != NULL) {
		if (temp->n == value) {
			i++;
		}
		temp = temp->next;
	}
	*found = malloc(i * sizeof(El*));
	if (*found == NULL) {
		exit(EXIT_FAILURE);
	}
	temp = liste->first;
	int j = 0;
	while (temp != NULL) {
		if (temp->n == value) {
			(*found)[j] = temp;
			j++;
		}
		temp = temp->next;
	}
	return i;
}

void ereplall(List* liste, int value, int newvalue) {
	lerr(liste);
	El **elements = NULL;
	int n = efindmulti(liste, &elements, value);
	int i = 0;
	for (i = 0; i < n; i++) {
		elements[i]->n = newvalue;
	}
	free(elements);
}

void edelall(List* liste, int value) {
	lerr(liste);
	El **elements = NULL;
	int n = efindmulti(liste, &elements, value);
	int i = 0;
	for (i = 0; i < n; i++) {
		edelel(liste, elements[i]);
	}
	free(elements);
}

void empiler(List *liste, int value) {
	lerr(liste);
	El *newel = malloc(sizeof(*newel));
	if (newel == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newel->n = value;
	newel->next = liste->first;
	liste->first = newel;
	liste->size++;
}

int depiler(List* liste) {
	lerr(liste);
	int temp = 0;
	El *ptemp = liste->first;
	if (liste->first != NULL) {
		temp = ptemp->n;
		liste->first = ptemp->next;
		free(ptemp);
		liste->size--;
	}
	return temp;
}

void affpile(List* liste) {
	lerr(liste);
	El *temp = liste->first;
	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}

	printf("\n");
}

void enfiler(List *liste, int value)
{
	lerr(liste);
	El *newel = malloc(sizeof(*newel));
	if (newel == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newel->n = value;
	newel->next = NULL;
	El* temp = NULL;

	if (liste->first != NULL)
	{
		temp = liste->first;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newel;
		liste->size++;
	}
	else
	{
		liste->first = newel;
		liste->size = 1;
	}
}

int defiler(List* liste) {
	lerr(liste);
	int temp = 0;
	if (liste->first != NULL)
	{
		El *ptemp = liste->first;
		temp = ptemp->n;
		liste->first = ptemp->next;
		free(ptemp);
		liste->size--;
	}
	return temp;
}

void afffile(List* liste) {
	lerr(liste);
	El *temp = liste->first;
	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}

	printf("\n");
}

void secureread(char *word, int maxsize) {
	char *p = NULL;
	if (fgets(word, maxsize, stdin) != NULL) {
		p = strchr(word, '\n');
		if (p != NULL)
		{
			*p = '\0';
		}
		else
		{
			buffercls();
		}
	}
	else {
		buffercls();
		error();
	}
}

void buffercls(void) {
	int c = 0;
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}

void error(void) {
	system("cls");
	printf("MEMORY FATAL ERROR\n");
	getch();
	exit(0);
}

List* totolist(int begin, int end, int increment) {
	List *liste = NULL;
	int i = 0;
	if (abs(begin + increment - end) < abs(begin - end)) {
		liste = linit(begin);
		if (increment > 0) {
			for (i = begin + increment; i <= end; i += increment) {
				enfiler(liste, i);
			}
		}
		else if (increment < 0) {
			for (i = begin + increment; i >= end; i += increment) {
				enfiler(liste, i);
			}
		}

	}
	return liste;
}

char* ecoread(int maxsize) {
	int i = 0;
	char *word = malloc(maxsize * sizeof(char));
	if (word == NULL) {
		error();
	}
	secureread(word, maxsize);
	int taille = strlen(word);
	taille++;
	char* neword = malloc(taille * sizeof(char));
	if (neword == NULL) {
		error();
	}
	for (i = 0; i < taille; i++) {
		neword[i] = word[i];
	}
	free(word);
	return neword;
}

List* lrand(int size, int min, int max) {
	srand(time(NULL));
	int randnum = 0, i = 0;
	max++;
	List* liste = NULL;
	if (min < max) {
		randnum = rand() % (max - min) + min;
		liste = linit(randnum);
		size--;
		for (i = 0; i < size; i++) {
			randnum = rand() % (max - min) + min;
			eins(liste, randnum);
		}
	}
	return liste;
}

int ecount(List* liste, int value) {
	lerr(liste);
	int temp = 0, count = 0;
	El* etemp = 0;
	etemp = liste->first;
	while (etemp != NULL) {
		temp = etemp->n;
		if (temp == value) {
			count++;
		}
		etemp = etemp->next;
	}
	return count;
}

long longread(void)
{
	char *nbs = malloc(20 * sizeof(char));

	if (nbs != NULL)
	{
		secureread(nbs, 20);
		return strtol(nbs, NULL, 10);
	}
	else
	{
		error();
	}
}

void elproba(List* liste, int min, int max) {
	int i = 0;
	for (i = min; i <= max; i++) {
		printf("%d : %d / ", i, ecount(liste, i));
	}
	printf("\n");
}

void cls(void) {
	system("cls");
}

char** tabxychar(int x, int y) {
	int i = 0;
	char **tabx = calloc(x, sizeof(char*));
	char *taby = calloc(x * y, sizeof(char));
	for (i = 0; i < x; i++) {
		tabx[i] = &taby[i * y];
	}
	return tabx;
}

void color(int t, int f)
{
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H, f * 16 + t);
}

void printfcolor(char *txt) {
	char c = -1;
	int i = 0, flag = 0;
	while (c != '\0') {
		flag = 0;
		while (c != '&' && c != '\0') {
			c = txt[i];
			if (c != '&' && c != '\0') {
				printf("%c", c);
			}
			i++;
		}
		if (c == '&') {
			c = txt[i];
			if (c == 'r') {
				i++;
				color(12, 0);
			}
			else if (c == 'b') {
				i++;
				color(9, 0);
			}
			else if (c == 'v') {
				i++;
				color(10, 0);
			}
			else if (c == 'y') {
				i++;
				color(11, 0);
			}
			else if (c == 'r') {
				i++;
				color(12, 0);
			}
			else if (c == 's') {
				i++;
				color(13, 0);
			}
			else if (c == 'j') {
				i++;
				color(14, 0);
			}
			else if (c == 'f') {
				i++;
				color(1, 0);
			}
			else if (c == 'c') {
				i++;
				color(2, 0);
			}
			else if (c == 'a') {
				i++;
				color(3, 0);
			}
			else if (c == 'm') {
				i++;
				color(4, 0);
			}
			else if (c == 'p') {
				i++;
				color(5, 0);
			}
			else if (c == 'k') {
				i++;
				color(6, 0);
			}
			else if (c == 'g') {
				i++;
				color(7, 0);
			}
			else if (c == '&') {
				i++;
				flag = 1;
				c = txt[i];
				if (c == '&') {
					i++;
					c = txt[i];
					printf("&");
				}
				else if (c == 'e') {
					i++;
					c = txt[i];
					if (c == 'a') {
						i++;
						printf("%c", 130);
					}
					else if (c == 'g') {
						i++;
						printf("%c", 138);
					}
					else if (c == 'c') {
						i++;
						printf("%c", 136);
					}
					else if (c == 't') {
						i++;
						printf("%c", 137);
					}
				}
				else if (c == 'a') {
					i++;
					c = txt[i];
					if (c == 'g') {
						i++;
						printf("%c", 133);
					}
					else if (c == 'c') {
						i++;
						printf("%c", 131);
					}
					else if (c == 't') {
						i++;
						printf("%c", 132);
					}
				}
				else if (c == 'o') {
					i++;
					c = txt[i];
					if (c == 'c') {
						i++;
						printf("%c", 147);
					}
					else if (c == 't') {
						i++;
						printf("%c", 148);
					}
				}
				else if (c == 'u') {
					i++;
					c = txt[i];
					if (c == 'g') {
						i++;
						printf("%c", 151);
					}
					else if (c == 'c') {
						i++;
						printf("%c", 150);
					}
					else if (c == 't') {
						i++;
						printf("%c", 129);
					}
				}
				else if (c == 'i') {
					i++;
					c = txt[i];
					if (c == 'c') {
						i++;
						printf("%c", 140);
					}
					else if (c == 't') {
						i++;
						printf("%c", 139);
					}
				}
			}
			if (!flag) {
				while (c != '#' && c != '\0') {
					c = txt[i];
					if (c == '&') {
						i++;
						c = txt[i];
						if (c == '&') {
							i++;
							c = txt[i];
							if (c == '&') {
								i++;
								printf("&");
							}
							else if (c == 'e') {
								i++;
								c = txt[i];
								if (c == 'a') {
									i++;
									printf("%c", 130);
								}
								else if (c == 'g') {
									i++;
									printf("%c", 138);
								}
								else if (c == 'c') {
									i++;
									printf("%c", 136);
								}
								else if (c == 't') {
									i++;
									printf("%c", 137);
								}
							}
							else if (c == 'a') {
								i++;
								c = txt[i];
								if (c == 'g') {
									i++;
									printf("%c", 133);
								}
								else if (c == 'c') {
									i++;
									printf("%c", 131);
								}
								else if (c == 't') {
									i++;
									printf("%c", 132);
								}
							}
							else if (c == 'o') {
								i++;
								c = txt[i];
								if (c == 'c') {
									i++;
									printf("%c", 147);
								}
								else if (c == 't') {
									i++;
									printf("%c", 148);
								}
							}
							else if (c == 'u') {
								i++;
								c = txt[i];
								if (c == 'g') {
									i++;
									printf("%c", 151);
								}
								else if (c == 'c') {
									i++;
									printf("%c", 150);
								}
								else if (c == 't') {
									i++;
									printf("%c", 129);
								}
							}
							else if (c == 'i') {
								i++;
								c = txt[i];
								if (c == 'c') {
									i++;
									printf("%c", 140);
								}
								else if (c == 't') {
									i++;
									printf("%c", 139);
								}
							}
						}
						c = txt[i];
					}
					if (c != '#' && c != '\0') {
						printf("%c", c);
					}
					i++;
				}
				color(15, 0);
			}
		}
	}
}

int** tabxyint(int x, int y) {
	int i = 0;
	int **tabx = calloc(x, sizeof(int*));
	int *taby = calloc(x * y, sizeof(int));
	for (i = 0; i < x; i++) {
		tabx[i] = &taby[i * y];
	}
	return tabx;
}

long** tabxylong(long x, long y) {
	int i = 0;
	long **tabx = calloc(x, sizeof(long*));
	long *taby = calloc(x * y, sizeof(long));
	for (i = 0; i < x; i++) {
		tabx[i] = &taby[i * y];
	}
	return tabx;
}

double** tabxydouble(int x, int y) {
	int i = 0;
	double **tabx = calloc(x, sizeof(double*));
	double *taby = calloc(x * y, sizeof(double));
	for (i = 0; i < x; i++) {
		tabx[i] = &taby[i * y];
	}
	return tabx;
}

FILE* sfile(char* dossier, char* fichier, char* extension, char* mode) {
	FILE* file = NULL;
	char* chemin = calloc(strlen(dossier) + strlen(fichier) + strlen(extension) + 3, sizeof(char));
	
	strcat(chemin, dossier);
	strcat(chemin, "/");
	strcat(chemin, fichier);
	strcat(chemin, ".");
	strcat(chemin, extension);
	file = fopen(chemin, mode);
	free(chemin);
	return file;
}

FILE* readfile(char* nom) {
	FILE* file = NULL;
	file = fopen(nom, "r");
	if (file == NULL) {
		file = fopen(nom, "w+");
	}
	if (file == NULL) {
		printfcolor("&rErreur ! Impossible de lire et/ou &&eacrire le fichier!#\n&jLe chemin d'acc&&egs doit &&ectre refus&&ea...#\n");
		getch();
		exit(EXIT_FAILURE);
	}

	return file;
}

void nextdladd(DEl *el, int value)
{
	DEl *newel = malloc(sizeof(*newel));
	if (newel == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newel->n = value;
	newel->next = NULL;
	newel->prec = el;
	newel->pos = el->pos + 1;
	el->next = newel;
}

void precdladd(DList *l, DEl *el, int value)
{
	DEl *newel = malloc(sizeof(*newel));
	if (newel == NULL)
	{
		exit(EXIT_FAILURE);
	}

	newel->n = value;
	newel->next = el;
	newel->prec = NULL;
	newel->pos = el->pos - 1;
	el->prec = newel;
	l->first = newel;
}

char* romanize(int n) {
	char* m = NULL;
	int* x = calloc(7, sizeof(int));
	int* p = calloc(7, sizeof(int));
	int size = 0, i, j, k;

	x[0] = n % 5;
	if (n % 10 >= 5) {
		x[1] = 1;
	}
	x[2] = (n - x[1] * 5 - x[0]) % 50;
	x[2] /= 10;
	if ((n - x[1] * 5 - x[0]) % 100 >= 50) {
		x[3] = 1;
	}
	x[4] = (n - x[3] * 50 - x[2] * 10 - x[1] * 5 - x[0]) % 500;
	x[4] /= 100;
	if ((n - x[3] * 50 - x[2] * 10 - x[1] * 5 - x[0]) % 1000 >= 500) {
		x[5] = 1;
	}
	x[6] = (n - x[5] * 500 - x[4] * 100 - x[3] * 50 - x[2] * 10 - x[1] * 5 - x[0]) / 1000;
	
	if (x[0] == 4) {
		x[0] = 0;
		if (x[1]) {
			p[2] = 1;
			x[1] = 0;
		}
		else {
			p[1] = 1;
		}
	}
	if (x[2] == 4) {
		x[2] = 0;
		if (x[3]) {
			p[4] = 1;
			x[3] = 0;
		}
		else {
			p[3] = 1;
		}
	}
	if (x[4] == 4) {
		x[4] = 0;
		if (x[5]) {
			p[6] = 1;
			x[5] = 0;
		}
		else {
			p[5] = 1;
		}
	}

	for (i = 0; i < 7; i++) {
		size += x[i] + p[i] * 2;
	}

	m = calloc(size + 1, sizeof(char));
	for (i = 0; i < x[6]; i++) {
		m[i] = 'M';
	}
	if (p[6]) {
		m[i] = 'C';
		i++;
		m[i] = 'M';
		i++;
	}
	else if (p[5]) {
		m[i] = 'C';
		i++;
		m[i] = 'D';
		i++;
	}
	else if (x[5]) {
		m[i] = 'D';
		i++;
	}
	j = i;
	for (k = i; k < j + x[4]; k++) {
		m[k] = 'C';
		i++;
	}
	if (p[4]) {
		m[i] = 'X';
		i++;
		m[i] = 'C';
		i++;
	}
	else if (p[3]){
		m[i] = 'X';
		i++;
		m[i] = 'L';
		i++;
	}
	else if (x[3]) {
		m[i] = 'L';
		i++;
	}
	j = i;
	for (k = i; k < j + x[2]; k++) {
		m[k] = 'X';
		i++;
	}
	if (p[2]) {
		m[i] = 'I';
		i++;
		m[i] = 'X';
		i++;
	}
	else if (p[1]) {
		m[i] = 'I';
		i++;
		m[i] = 'V';
		i++;
	}
	else if (x[1]) {
		m[i] = 'V';
		i++;
	}
	j = i;
	for (k = i; k < j + x[0]; k++) {
		m[k] = 'I';
		i++;
	}

	m[size] = '\0';
	free(x);
	free(p);
	
	return m;
}

char* reverstring(char* string, int size) {
	if (!size) {
		size = strlen(string);
	}
	char* cpy = calloc(size + 1, sizeof(char));
	int i;
	for (i = 0; i < size; i++) {
		cpy[i] = string[size - i - 1];
	}
	cpy[size] = '\0';
	free(string);
	return cpy;
}

int* revertab(int* tab, int size) {
	int* cpy = calloc(size, sizeof(int));
	int i;
	for (i = 0; i < size; i++) {
		cpy[i] = tab[size - i - 1];
	}
	free(tab);
	return cpy;
}

int* longtotab(long n) {
	int* tab = calloc(1, sizeof(int));
	int size = 1;
	tab[0] = n % 10;
	n -= tab[0];
	n /= 10;
	while (n) {
		size++;
		tab = realloc(tab, size * sizeof(int));
		tab[size - 1] = n % 10;
		n -= tab[size - 1];
		n /= 10;
	}
	return revertab(tab, size);
}

int longlen(long n) {
	int size = 1;
	n -= n % 10;
	n /= 10;
	while (n) {
		size++;
		n -= n % 10;
		n /= 10;
	}
	return size;
}

List* tabtolist(int* tab, int size) {
	List* l = linit(tab[size - 1]);
	int i;
	for (i = 1; i < size; i++) {
		eins(l, tab[size - i - 1]);
	}
	return l;
}

List* longtolist(long n) {
	return tabtolist(longtotab(n), longlen(n));
}

int* listtotab(List* l) {
	int i;
	int* tab = calloc(l->size, sizeof(int));
	El* tmp = l->first;
	for (i = 0; i < l->size; i++) {
		tab[i] = tmp->n;
		tmp = tmp->next;
	}
	return tab;
}

int fwcount(FILE* f) {
	if (f == NULL)
		return -1;
	
	int n = 0;
	char c = 0, cp = 0;

	rewind(f);
	while (c != EOF) {
		cp = c;
		c = fgetc(f);
		if ((isspace(c) || c == EOF) && !isspace(cp))
			n++;
	}
	rewind(f);
	return n;
}