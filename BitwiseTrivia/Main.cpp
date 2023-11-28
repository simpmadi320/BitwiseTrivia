#include <iostream>
#include <cstdlib>
#include <bitset>
#include <fstream>
#include <string>
#include <iomanip> // For setw
using namespace std;

//Binary Definition ***

static int difficulty = 0; //1=Easy, 2=Normal, 3=Hard

// Prompt question puts the text out to ask the use a question, and is generic to ask all in this format but one's complement 
void PromptQuestion(string line1, string oper, int val1, int val2) {
	if (difficulty != 3) cout << line1 << endl;
	cout << "What is " << val1 << oper << val2 << "?" << endl;
	if (difficulty == 1) cout << "Hint: " << bitset<4>(val1) << oper << bitset<4>(val2) << endl;
}

//Polymorphism - In this situation only used for Binray Ones Complements
void PromptQuestion(int val1) {
	if (difficulty != 3) cout << "BINARY ONES COMPLEMENTS " << endl <<" Note C++ represents in two's complement" << endl;
	cout << "What is ~" << val1 << "?" << endl;
	if (difficulty == 1) cout << "Hint: ~" << bitset<32>(val1) << endl;
}

/*Start Of Questions*/
//Bitwise OR: If at least one bit in a given two are "1" then the result will be "1"
int BitwiseOR(int val1, int val2) {
	PromptQuestion("BITWISE OR", "|=", val1, val2);
	return val1 |= val2;
}

//Bitwise AND: If both bits in a column are "1" then the result will be "1"
int BitwiseAND(int val1, int val2) {
	PromptQuestion("BITWISE AND", "&=", val1, val2);
	return val1 &= val2;
}

//One's Complement: Turns all "1"s to "0"s, and all "0"s to "1"s, it wil result in (val1 * -1) - 1
int BinaryOnesComplement(int val1) {
	PromptQuestion(val1);
	return ~val1;
}

//Bitwise Exclusive Or: If only one bit in a given two are "1" then the result will be "1"
int BitwiseXOR(int val1, int val2) {
	PromptQuestion("BITWISE XOR", "^=", val1, val2);
	return val1 ^= val2;
}

//Shift Right: Shifts bits to the right by removing the most right column. This divides a number by 2. 0010 = 2 shift right by "1" makes 0001 = 1
int ShiftRight(int val1, int val2) {
	PromptQuestion("SHIFT RIGHT", ">>", val1, val2);
	return val1 >> val2;
}

//Shift Left: Shifts bits to the left by adding a "0" to the most right column. This doubles a number. 0010 = 2 shift left by "1" makes 0100 = 4
int ShiftLeft(int val1, int val2) {
	PromptQuestion("SHIFT LEFT", "<<", val1, val2);
	return val1 << val2;
}
/*End Of Questions*/

//These methods are initialized here, but written below main
void SetTitle(char title[]);
void SetHighscores(int highScores[][3]);
void SetDifficulty();
int SetQuestion();
void SaveHighscores(int highScores[][3]);

int main() {

	//Writes the title, with an underline underneath
	char title[] = "Bitwise Trivia!";
	SetTitle(title);

	//Set Difficulty. Easy says bitwise name and 
	SetDifficulty();

	//Check file, if error close file
	//Note: array is a reference type and is mutable in methods
	int highScores[][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	SetHighscores(highScores);

	
	int input;
	int score = 0;
	
	//Keep asking questions until an incorrect answer is provided
	while (true) {
		
		//Pulls a randomized question and answer
		int ans = SetQuestion();

		//Pulls the user's answer
		cin >> input;

		//If correct, increment the score, if false display the answer and final score as well as stop asking questions
		if (input == ans) {
			cout << "Correct!" << endl << endl;
			score++;
		}
		else {
			cout << "Incorrect :(" << endl;
			cout << "The answer was " << ans << endl << endl;
			cout << "Final score was " << score << endl;
			break;
		}
	}

	//If it's a new highscore, bump the previous records down a rank (if needed) and insert this score where applicable
	//Note that this is the same code for all difficulty levels as only one column will be affect per game
	if (score >= highScores[difficulty - 1][0]) { //If a new first place
		cout << "New First Place score!: " << score << endl;
		highScores[difficulty - 1][2] = highScores[difficulty - 1][1];
		highScores[difficulty - 1][1] = highScores[difficulty - 1][0];
		highScores[difficulty - 1][0] = score;
	}
	else if (score >= highScores[difficulty - 1][1]) { //If a new second place
		cout << "New Second Place score!: " << score << endl;
		highScores[difficulty - 1][2] = highScores[difficulty - 1][1];
		highScores[difficulty - 1][1] = score;
	}
	else if (score > highScores[difficulty - 1][2]) { //If a new third place
		cout << "New Third Place score!: " << score << endl;
		highScores[difficulty - 1][2] = score;
	}

	//Save the record to a file
	SaveHighscores(highScores);
	
	//End program
	return 0;
}

//Writes the title at the top of the console
void SetTitle(char title[]) {
	
	// Writes the text that's offset, replace each letter with 
	// a dash to make a underline on a second line
	std::cout << setw(2 * strlen(title)) << title << std::endl;
	for (int i = 0; i < strlen(title); i++) title[i] = '-';
	std::cout << setw(2 * strlen(title)) << title << std::endl;
}

//User input to set the difficulty of the game after the prompt
void SetDifficulty() {
	cout << "Would you like to play in " << endl;
	cout << "1. Easy Mode - Shows the numbers as binary" << endl; //View operator name, hint, and question
	cout << "2. Normal Mode - No hints provided" << endl; //View operator name and questoin
	cout << "3. Hard Mode - No mode header, must go off the signs alone" << endl; //View only question

	std::cin >> difficulty;

	cout << endl;
}

//Randomly select a question, these methods will display it on screen, then return the answer to compare if the user was correct
int SetQuestion() {

	//Needs to seed the randomizer, without this the random number 
	//generator would always be the same
	srand(time(NULL));

	int operationSelector = rand() % 7; //returns 0-6
	int val1 = rand() % 16; //returns 0-15 or 0000 to 1111
	int val2 = rand() % 16; //returns 0-15 or 0000 to 1111

	switch (operationSelector) {
	case 0:
		return BitwiseOR(val1, val2);
		break;
	case 1:
		return BitwiseAND(val1, val2);
		break;
	case 2:
		return BinaryOnesComplement(val1);
		break;
	case 3:
		return BitwiseXOR(val1, val2);
		break;
	case 4:
		return BitwiseXOR(val1, val2);
		break;
	case 5:
		return ShiftRight(val1, val2);
		break;
	case 6:
		return ShiftLeft(val1, val2);
		break;
	default:
		return 0;
		break;
	}
}

//Reads in a file, if no file is found let all scores by 0
void SetHighscores(int highScores[][3]) {
	
	string myText;
	ifstream MyReadFile("filename.txt");

	// Check if the file is open
	if (!MyReadFile.is_open()) {
		return; // Return, the default highscores are 0,0,0 across the board
	}

	//Highscores in file are written as #-#-#, these delimiter of "-" allows numbers to be any character in length
	for (int i = 0; i < 3 && getline(MyReadFile, myText); i++) {
		
		//Find the first and second dash
		int firstDelimiter = myText.find("-");
		string tempString = myText.substr(firstDelimiter + 1, myText.length()-1);
		int secondDelimiter = tempString.find("-");

		//Find the numbers inbetween the dashes
		highScores[0][i] = stoi(myText.substr(0, firstDelimiter));
		highScores[1][i] = stoi(myText.substr(firstDelimiter + 1, myText.length() - secondDelimiter));
		highScores[2][i] = stoi(myText.substr(myText.length() - secondDelimiter, myText.length()));

	}
	
	//Output the highscores of the difficulty previously inputted by the user
	cout << "High Scores!" << endl;
	cout << "First: " << highScores[difficulty-1][0] << endl;
	cout << "Second: " << highScores[difficulty - 1][1] << endl;
	cout << "Third: " << highScores[difficulty - 1][2] << endl << endl;

	//Close file
	MyReadFile.close();
}


//Saves the new highscores at the end of the run
void SaveHighscores(int highScores[][3]) {

	ofstream MyFile("filename.txt");
	MyFile << highScores[0][0] << "-" << highScores[1][0] << "-" << highScores[2][0] << endl;
	MyFile << highScores[0][1] << "-" << highScores[1][1] << "-" << highScores[2][1] << endl;
	MyFile << highScores[0][2] << "-" << highScores[1][2] << "-" << highScores[2][2] << endl;

}