#include <iostream>
#include <fstream>	//file reading
#include <ctime>	//for random
#include <string>
#include <vector>
using namespace std; 


class Letters {
public:
	vector<char> unsed;
	vector<char> wrong;
	vector<char> inword;
	vector<char> inplace;

	void display();
};


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


string toLower(string text) {

	string lowerString;

	for (auto c : text) lowerString += tolower(c);
	return lowerString;

}//coverts paramater string into lowercase


//FUNCTIONS AND CONSTS DELCARED - used below main
bool openFile(ifstream& file);

string goToWord(ifstream& file, int place);

void compareString(string word, vector<char> guess);

void screenReset(vector<char> v);

void outputVector(vector<char> v);

vector<char> typingFunc();


const int LINESLEN = 3102;
const int MAXGUESS = 6;
const int WORDLEN = 5;


//MAIN CODE BLOCK//
int main() {

	int guessCount = 0;

	bool validate;			//looping bool val
	int randomPlace;		//pointer val
	string word;

	srand(time(0));	//used for srand
	title("Wordleish", true);

	//open words file
	ifstream myFile;
	myFile.open("5-letter-words.txt");
	validate =  openFile(myFile);	//only completes code if file is open

	if (validate) {

		randomPlace = rand() % LINESLEN; //3102 number of lines
		word = goToWord(myFile, randomPlace);
		//func to skip through get lines till the line of the pointer 
		myFile.close();

		cout << word << endl; //debug only *REMOVE*


		do {

			vector<char> guess;
			guess = typingFunc();
			//take 1-5 guesses from user

			compareString(word, guess);
			guessCount++;
			//output results

		
		} while (guessCount < MAXGUESS);

		cout << "Attempt Failed! - too many guesses\nThe Word was: " << word << endl;
		//display word - fail message


	} 

};	//END OF MAIN//


//funcs//
bool openFile(ifstream& file) {

	if (!file) {
		cout << "ERROR, When Opening File!" << endl;
		return false;
	}

	file >> noskipws; //makes it so that whitespace is read
	return true;

};//function to open files, takes in the fstream file value as refrence returns a bool value depending on if it was opened
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


void compareString(string word, vector<char> guess) {

	//goes through the vector comparing the chars
	//outpits V or X accordingly
	for (int i = 0;i < WORDLEN; i++) {
		
		if (guess[i] == word[i]) {
			cout << "V";
		}
		else if (word.find(guess[i]) != -1) {		//if find() is not eqaul to -1 then that char is in the word somewhere hence the '?'
			cout << "?";
		}
		else {
			cout << "X";
		}

	}

	cout << "\n-----\n";	//formatting

}


void screenReset(vector<char> v) {

	system("cls");
	title("Wordleish", true);

	outputVector(v);

}


vector<char> typingFunc() {

	vector<char> word;
	char c;
	string s;
	int count = 0;

	while (count < WORDLEN) {
		cin >> c;
		word.push_back(c);

		count++;
	}
	word.resize(WORDLEN);	//gets rid of any extras 
	return word;
}


void outputVector(vector<char> v) {

	cout << endl;
	for (int i = 0;i < v.size();i++) {
		cout << v[i];
	}		//outputs vector of the users current word

}


void Letters::display() {
	title("\n\nLetters\n\n", false);
	outputVector(unsed);
	outputVector(wrong);
	outputVector(inword);
	outputVector(inplace);
	//outputs all the letter vecs

}