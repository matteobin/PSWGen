#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

int getRandNumBtwn(int min, int max) {
	int range = max - min + 1;
	int remainder = RAND_MAX % range;
	int randomNumber;
	do {
		randomNumber = rand();
	} while (randomNumber >= RAND_MAX - remainder);
	return min + randomNumber % range;
}

void showHelp(char name[]) {
	printf("Welcome to PaSsWord Generator 3.1! Coded by Matteo Bini.\nThis software creates alpha-numeric, pseudo-randomly chosen from 25 to 50 characters-long passwords.\n\nUsage: %s <option(s)>\nOptions:\n-h, --help\t\tshow help\n-l, --length NUMBER\tset password length\n-n, --numbers-only\tcreates a number only password\n-ci, --case-insensitive\tcreates a lowercase only password\n-c, --complex\t\tcreates an even more complex password, with special characters as well\nSpecial characters:\t !\"#$%%&'()*+,-./:;<=>?@[\\]^_`{|}~\n\nAfter running the command, all you have to do is copy and paste your new password wherever you need to.\n", name);
}

int main(int argc, char* argv[]) {	
	int len = 0;
    int numsOnly = 0;
	int caseSens = 1;
	int complex = 0;
	char arg[19];
	for (int i=1; i<argc; ++i) {
		if (strlen(argv[i]) > 18) {
			continue;
		}
		strcpy(arg, argv[i]);
		if (strcmp(arg, "-h")==0 || strcmp(arg, "--help")==0) {
			showHelp(argv[0]);
			return 0;
		} else {
            if (strcmp(arg, "-l")==0 || strcmp(arg, "--length")==0) {
                if (i+1<argc) {
                    sscanf(argv[++i], "%i", &len);
                    if (len<=0 || len>50) {
                        printf("\nERROR: length option requires a valid number between 1 and 50.\n");
                        len = 0;
                    }
                }
                else {
                    printf("\nERROR: length option requires at least one number between 1 and 50.\n");
                }
            }
            if (strcmp(arg, "-n")==0 || strcmp(arg, "--numbers-only")==0) {
                numsOnly = 1;
            } else if (strcmp(arg, "-ci")==0 || strcmp(arg, "--case-insensitive")==0) {
			    caseSens = 0;
		    } else if (strcmp(arg, "-c")==0 || strcmp(arg, "--complex")==0) {
			    complex = 1;
		    }
		}
	}
	srand(time(NULL));
	if (len==0) {
		len = getRandNumBtwn(25, 50);
	}
    char availChars[96] = "0123456789";
	int availCharsNum = 10;
    if (!numsOnly) {
        strcat(availChars, "abcdefghijklmnopqrstuvwxyz");
        availCharsNum += 26;
        if (caseSens) {
            strcat(availChars, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            availCharsNum += 26;
        }
        if (complex) {
            strcat(availChars, " !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
            availCharsNum += 33;
        }
    }
	char psw[51] = "";
	char randChar[2] = "";
	int randCharInd;
	for (int i=0; i<len; i++) {
		randCharInd = getRandNumBtwn(0, availCharsNum - 1);
		strncpy(randChar, availChars + randCharInd, 1);
		strcat(psw, randChar);
	}
    printf("\nYour password is: %s.\n", psw);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, 51);
	memcpy(GlobalLock(hMem), psw, 51);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
    return 0;
}
