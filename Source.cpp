#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std; 


static void title(string text, bool banner) {
	string temp = text;
	int MAX = size(temp);		//sets to length of text
	cout << "=======================================================================================================================" << endl;
	cout << endl << "                                               ";
	if (banner) {
		for (int i = 0;i < MAX;i++) {
			cout << "-";
		}
	}
	cout << endl << "                                               " << text;
	cout << endl << "                                               ";
	if (banner) {
		for (int i = 0;i < MAX;i++) {
			cout << "-";
		}		//couts a '-' for the length of the string on the bottom and top
	}			//all titles are passed with a boolean value if they want a banner over the text or not
	cout << endl << endl;
	cout << "=======================================================================================================================" << endl;
}
//used for vanity, displaying titles with a border if passed with a true boolean value


//FUNCTIONS AND CONSTS DELCARED - used below main
bool openFile(ifstream& file);

string goToWord(ifstream& file, int place);

void compareString(string word, string guess);

void typingFunc();

const int LINESLEN = 3102;
const int MAXGUESS = 6;
const int WORDLEN = 5;


//MAIN CODE BLOCK//
int main() {

	int guessCount = 1;

	bool validate;			//looping bool val
	int randomPlace;		//pointer val
	string word;

	srand(time(0));	//used for srand
	title("Wordle*", true);

	//open words file
	ifstream myFile;
	myFile.open("5-letter-words.txt");
	validate =  openFile(myFile);

	if (validate) {

		randomPlace = rand() % LINESLEN; //3102 number of lines
		word = goToWord(myFile, randomPlace);
		//func to skip through get lines till the line of the pointer 
		myFile.close();

		cout << word << endl;

		do {
			string guess;
			cout << "Take Guess Number " << guessCount << "...\n";
			guess = typingFunc();
			//take 1-5 guesses from user

			compareString(word, guess);
			guessCount++;
			//output results
		
		} while (guessCount < MAXGUESS);
		cout << "attempt failed - too many guesses\n";
		//display word 


	} //makes sure file opened before continuing and crashing

};


//funcs
bool openFile(ifstream& file) {
	if (!file) {
		cout << "ERROR, When Opening File!" << endl;
		return false;
	}
	file >> noskipws; //makes it so that whitespace is read
	return true;
};	//function to open files, takes in the fstream file value as refrence returns a bool value depending on if it was opened
//function used for validation as well as opening


string goToWord(ifstream& file, int place) {
	string temp;

	for (int i = 1; i < place; i++) {
		getline(file, temp);
	}
	//cycles through until it finds it
	return temp;
	//sets string to the word
}


void compareString(string word, string guess) {
	
	for (int i = 0;i < WORDLEN; i++) {
		
		if (word[i] == guess[i]) {
			cout << "V";
		}
		else {
			cout << "X";
		}

	}
	cout << "\n";
}


void typingFunc() {

	char c;

	for (int i = 0;i > WORDLEN;i++) {

		cin >> c;
		cout << c;

	}
	cout << "\nWant to send this word?\n";
}