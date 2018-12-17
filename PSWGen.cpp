#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

static int getRandomNumberBetween(int min, int max) {
	int range = max - min + 1;
	int remainder = RAND_MAX % range;
	int randomNumber;
	do {
		srand(time(NULL));
		randomNumber = rand();
	} while (randomNumber >= RAND_MAX - remainder);
	return min + randomNumber % range;
}

static void showHelp(string name) {
	cout << "Welcome to PaSsWord Generator 2.3! Coded by Matteo Bini.\n";
	cout << "This software creates alpha-numeric, pseudo-randomly chosen from 25 to 50 characters-long passwords\nand it automatically copies them to the system clipboard.\n";
	cout << "\nUsage: " << name << " <option(s)>\n";
	cout << "Options:\n";
	cout << "-h, --help\t\tshow help\n";
	cout << "-l, --length NUMBER\tset password length\n";
	cout << "-c, --complex\t\tcreates a complex password, with special characters as well\n";
	cout << "Special characters:\t !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~\n";
	cout << "\nAfter running the command, all you have to do is paste your new password wherever you need to.\n";
}

int main(int argc, char* argv[]) {	
	int length = getRandomNumberBetween(25, 50);
	bool complex = false;
	string arg;
	for (int i=1; i<argc; ++i) {
        arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
			showHelp(argv[0]);
			return 0;
        } else if ((arg == "-l") || (arg == "--length")) {
            if(i+1 < argc) {
                try {
                    length = stoi(argv[++i]);
                } catch(invalid_argument) {
                    cout << "\nERROR: length option requires a valid number.\n";
				}
				catch (out_of_range) {
					cout << "\nERROR: length option out of range.\n";
				}
            } else {
                cout << "\nERROR: length option requires at least one number.\n";
            }
		} else if ((arg == "-c") || (arg == "--complex")) {
			complex = true;
		}
    }
    cout << "\nYour password is: ";
	string password = "";
	
	string charStr =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	if (complex) {
		charStr.append(" !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
	}
	srand(time(NULL));
	for (int i=0; i<length; ++i) {
		password += charStr.at(rand() % (charStr.length()));
	}
	
	cout << password << ".\n";

	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, length+1);
	memcpy(GlobalLock(hMem), password.c_str(), strlen(password.c_str())+1);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}