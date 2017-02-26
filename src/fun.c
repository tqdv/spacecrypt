/*This file contain each delimited function for methods.c, some easily reusable "get" functions in both encryption and decryption
or in general to get words and passwords, en/de-cryption methods and output methods
Have fun(ctions)*/
#define _CRT_SECURE_NO_WARNINGS
#include "fun.h"

char** getwords(FILE* in, int* nword, int** sizes) {
	//Get every input.txt words
	*nword = fwcount(in); //number of word in input.txt assuming they are seperate by spaces
	int i = 0, n = 0;
	char c = 0;
	char** words = calloc(*nword, sizeof(char*)); //Will contain every separate words
	*sizes = calloc(*nword, sizeof(int)); //To count the size of each word
	rewind(in);
	while (c != EOF) { //sizes counting
		c = fgetc(in);
		if (isspace(c) || c == EOF) {
			(*sizes)[i] = n;
			n = 0;
			i++;
		}
		else
			n++;
	}
	if (i < *nword) { //verify each word length has been count
		printfcolor("&rWarning!# An error occured while trying to counting word lengths, please make sure input text is just words separate with one space beetween each other and avoid special characters\nDefault memory block to 24 five characters will be set for unknown word lenght, by continuing you take the risk to have memory errors.\nContinue? y/n");
		if (tolower(getch()) != 'y') {
			exit(EXIT_FAILURE);
		}
		for (i; i < *nword; i++) {
			(*sizes)[i] = 25;
		}
	}
	rewind(in);
	for (i = 0; i < *nword; i++) { //enter each word
		words[i] = calloc((*sizes)[i] + 1, sizeof(char));
		fscanf(in, "%s", words[i]);
		words[i][(*sizes)[i]] = '\0';
	}
	return words;
}

char* getpassword() {
	//The simplest way to get a password
	char* password = calloc(50, sizeof(char));
	//50 is enough, is'nt it?
	printf("Please enter the password, only lowercase letters please, maximum 50:\n...? ");
	secureread(password, 50); //my old friend secure read function, I do not even remember exactly how you do work
	int flag = 0, plen = strlen(password), i;
	if (plen == 0)
		flag = 1;
	for (i = 0; i < plen; i++) { //Yes I want to verify you're clever enough to respect instructions (or perhaps your cat walked on you keyboard) 
		if (!islower(password[i])) { //I love ctype.h
			flag = 1;
			break; //YES, I TYPED BREAK!
		}
	}
	while (flag) {
		flag = 0;
		cls();
		printfcolor("&rError!# the password you typed may not contain only lowercase letters, please write it again:\n...? "); //You see, you did it, I was right
		secureread(password, 50);
		plen = strlen(password);
		if (plen == 0)
			flag = 1;
		for (i = 0; i < plen; i++) {
			if (!islower(password[i])) {
				flag = 1;
				break;
			}
		}
	}
	return password;
}

char** spaceencrypt(char** words, int n, int* sizes, char* password) {
	char** cwords = calloc(n, sizeof(char*));
	int i, j;
	int m = strlen(password); //why m? I don't even know
	int as[] = { 1,3,5,7,9,11,15,17,19,21,23,25 }; //12 numbers

	for (i = 0; i < n; i++) { //Simple, encryption word by word, then letter by letter
		cwords[i] = calloc(sizes[i] + 1, sizeof(char));
		for (j = 0; j < sizes[i]; j++) //That's here, letter by letter
			//What a beautiful encryption function, standing on one unique line, is'nt it?
			cwords[i][j] = (as[(sizes[j] * (password[(i + j) % m] - 96)) % 12] * (tolower(words[i][j]) - 97) + i + (password[(i + j) % m] - 97)) % 26 + 97;
	}

	return cwords;
}

char** spacedecrypt(char** cwords, int n, int* sizes, char* password) {
	/*Almost the same way of functionning that encryption method, report to it for more details*/
	char** words = calloc(n, sizeof(char*));
	int i, j, a, b;
	int m = strlen(password);
	int as[] = { 1,3,5,7,9,11,15,17,19,21,23,25 }; //12 numbers

	for (i = 0; i < n; i++) {
		words[i] = calloc(sizes[i] + 1, sizeof(char));
		for (j = 0; j < sizes[i]; j++) {
			//What an awful decryption function, 3 lines, shameful
			a = as[(sizes[j] * (password[(i + j) % m] - 96)) % 12];
			b = i + (password[(i + j) % m] - 97);
			fctdecrypt(&a, &b); //simple maths in there
			words[i][j] = (a*(cwords[i][j] - 97) + b) % 26 + 97;
		}
	}
	return words;
}

void tooutput(FILE* out, char** words, int n, int* sizes, char* password) {
	//This is for write encryption result in output.txt

	//First create an encrypted char string with each word length to allow print back spaces on decryption
	int m = strlen(password), i;
	char* strsizes = calloc(n + 1, sizeof(char));
	int as[] = { 1,3,5,7,9,11,15,17,19,21,23,25 }; //12 numbers
	for (i = 0; i < n; i++) {
		strsizes[i] = (as[(n*i)%12]*sizes[i] + (password[i%m] - 97)) % 26 + 97;
	}
	strsizes[n] = '\0';

	//Then encypt the number of numbers of words and then the number of words in another string
	int l = (int)log10(n) + 1;
	char* strn = calloc(l + 2, sizeof(char));
	strn[0] = (l + (password[0] - 97)) % 26 + 97;
	int np = n, r = 0;
	for (i = 1; i < l + 1; i++) {
		r = np % 10;
		np -= r;
		np /= 10;
		strn[l + 1 - i] = (r + (password[(l + 1 - i)%m] - 97)) % 26 + 97;
	}
	strn[l + 1] = '\0';

	//Finally write all of this in output.txt in the order you can see below
	rewind(out);
	fprintf(out, "%s", strn); //1st
	for (i = 0; i < n; i++) { //2nd
		fprintf(out, "%s", words[i]);
	}
	fprintf(out, "%s", strsizes); //3rd
}

int* readhints(FILE* in, int* n, char* password) {
	//This is to read number of word from the encrypted file
	char c = 0;
	rewind(in);
	c = fgetc(in);
	if (c == EOF) { //always check
		printfcolor("&rError! input.txt seems to be empty... Press any key to quit...\n");
		exit(EXIT_FAILURE);
	}
	int l = mod(c - password[0], 26), m = strlen(password);
	int i;
	for (i = 0; i < l; i++) {
		c = fgetc(in);
		*n += mod(c - password[(i+1)%m], 26) * (int)pow(10, l - i - 1);
	} //now *n contain the number of number in the number of words

	int as[] = { 1,3,5,7,9,11,15,17,19,21,23,25 }; //12 numbers
	int* sizes = calloc(*n, sizeof(int));
	int a, b;
	fseek(in, -*n, SEEK_END);
	for (i = 0; i < *n; i++) { //decrypt and read the word lengths
		c = fgetc(in);
		a = as[(*n*i)%12];
		b = password[i%m] - 97;
		fctdecrypt(&a, &b);
		sizes[i] = (a * (c - 97) + b) % 26;
	}
	return sizes;
}

char** getcwords(FILE* in, int n, int* sizes) {
	//Now thanks to the word lenghts we can get each encrypted word, to be decrypted later
	rewind(in);
	fseek(in, (int)log10(n) + 2, SEEK_CUR); //because first letters are for number information for readhints method
	char** cwords = calloc(n, sizeof(char*));
	int i, j;
	for (i = 0; i < n; i++) { //simply read
		cwords[i] = calloc(sizes[i], sizeof(char));
		for (j = 0; j < sizes[i]; j++) {
			cwords[i][j] = fgetc(in);
		}
	}
	return cwords;
}

void finalout(FILE* out, char** words, int n) {
	//To complicated for me to explain...
	int i;
	for (i = 0; i < n; i++) {
		fprintf(out, "%s", words[i]);
		if (i < n - 1) {
			fprintf(out, " "); //spaces are here!
		}
	}
}