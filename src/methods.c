/*This file regroups the methods, separate with one function for each choice from the main menu of the program*/

#define _CRT_SECURE_NO_WARNINGS //This is because I like to use Visual Studio and it does'nt like when I use unsecure functions, but I don't care
#include "methods.h"

void M1encrypt() {
	//Confirm action: erase output file to proceed
	cls();
	printf("This will erase output.txt content... Are you sure? y/n\n... ? ");
	if (tolower(getch()) != 'y')
		return;
	cls();

	//Open files input and output
	FILE* in = readfile("input.txt");
	FILE* out = fopen("output.txt", "w+");
	if (in == NULL || out == NULL) {
		cls();
		printfcolor("&rError...# Unable to read files, please make sure your repertory is not in secure access or corrupt, press any key to quit...\n");
		exit(EXIT_FAILURE);
	}

	int nword = 0; // Will counter number of words
	int* sizes = NULL; //Will contain each word length
	char** words = getwords(in, &nword, &sizes); //Will contain every separate words of input.txt
	fclose(in);

	cls();
	char* password = getpassword();

	char** cwords = spaceencrypt(words, nword, sizes, password); //get the encrypted result from the array
	
	//do not forget to clean an output result
	free(words[0]);
	free(words);
	tooutput(out, cwords, nword, sizes, password); //output function of encrypt method
	fclose(out);
	free(cwords[0]);
	free(sizes);
	free(password);
	printfcolor("&vSuccess!# Press any key to continue...");
	getch();
}

void M2decrypt() {
	cls();
	printf("This will erase output.txt content... Are you sure? y/n\n... ? ");
	if (tolower(getch()) != 'y')
		return;

	//Open files input and output
	FILE* in = readfile("input.txt");
	FILE* out = fopen("output.txt", "w+");
	if (in == NULL || out == NULL) {
		cls();
		printfcolor("&rError...# Unable to read files, please make sure your repertory is not in secure access or corrupt, press any key to quit...\n");
		exit(EXIT_FAILURE);
	}

	cls();
	char* password = getpassword();
	int nword = 0; // Will counter number of words
	int* sizes = NULL; //Will contain each word length
	sizes = readhints(in, &nword, password);
	
	char** cwords = getcwords(in, nword, sizes); //Will contain every separate input.txt within words thank to the hints
	fclose(in);
	char** words = spacedecrypt(cwords, nword, sizes, password);

	//again, do not forget to clean and output result
	free(cwords[0]);
	free(cwords);
	finalout(out, words, nword); //output function of decrypt method
	fclose(out);
	free(words[0]);
	free(sizes);
	free(password);
	printfcolor("&vSuccess!# Press any key to continue...");
	getch();
}

void M3swap() {
	cls();
	printf("This will erase input.txt content... Are you sure? y/n\n... ? ");
	if (tolower(getch()) != 'y')
		return;

	//Open files input and output
	FILE* in = readfile("output.txt");
	FILE* out = fopen("input.txt", "w+");
	if (in == NULL || out == NULL) {
		cls();
		printfcolor("&rError...# Unable to read files, please make sure your repertory is not in secure access or corrupt, press any key to quit...\n");
		exit(EXIT_FAILURE);
	}
	
	//Transfer output.txt into intput.txt char by char (can I say bit by bit?)
	cls();
	char c = 0;
	while (c != EOF) {
		c = fgetc(in);
		if (c != EOF)
			fputc(c, out);
	}
	fclose(in);
	fclose(out);

	printfcolor("&vSuccess!# Press any key to continue...");
	getch();
}

void M4readme() {
	//what a complex function, I don't know how to explain.. Sorry
	cls();
	system("start README.md");
}

void M5exit(int* choice) {
	//Should be shorter way to exit, but I like when the successful program thread end in main.c return.
	cls();
	printf("Are you sure? y/n");
	if (tolower(getch()) == 'y') {
		*choice = 27; 
		/*You want to know why I use 27? Simple, it's ESC key code, 
		I often use it to exit, I thought I would have done in this program but I don't. 
		Whatever I let it here...*/
	}
}