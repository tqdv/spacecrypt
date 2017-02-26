/*This is spacecrypt 1.0, just a simple idea of a young french student (that's me) after its arithmetic class
The goal is to create an encryption method with an alphabetic password that memorize spaces, more details in README.md
I'm not used to comment my own code, moreover my english is not perfect, but I hope you'll understand
what I did, I tried to make my code organized and lighten, if you find errors or optimisation problems which is probable,
please tell me hemispace@outlook.com*/

#include <stdio.h>
#include <stdlib.h>
#include "clist.h"
#include "methods.h"
#include "crypt.h"
#include "fun.h"

int main() {
	int choice = -1;

	while (choice != 27) {
		cls();
		choice = -1;
		printf("Welcome to Spacecrypt 1.0, please choose one option or see README.md for more informations and/or help.\n\n\t1. Encrypt input,\n\t2. Decrypt input,\n\t3. Transfer output.txt contents into input.txt,\n\t4. Open README.md,\n\t5. Exit;\n\n... ? ");
		choice = longread();

		while (!(choice >= 0 && choice <= 5)) {
			printfcolor("&rError...# No corresponding methods found, please enter a number between 1 and 5...\n... ? ");
			choice = longread();
		}

		switch (choice) {
		case 1:
			M1encrypt();
			break;
		case 2:
			M2decrypt();
			break;
		case 3:
			M3swap();
			break;
		case 4:
			M4readme();
			break;
		case 5:
			M5exit(&choice);
			break;
		default:
			cls();
			printfcolor("&rCRITICAL ERROR\nPLEASE MAKE SURE YOU TYPED A NUMBER\n#");
			getch();
			exit(EXIT_FAILURE);
		}
	}
	
	return EXIT_SUCCESS;
}