/*
 * Main.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: kailau
 */


#include <iostream>
using namespace std;

// The count of possible character that can be used in the password

// (a-z):26 (a-Z):52 (a-0):62 (a-')'):72
int characterSymbols = 62;


// Base password to check cracker on
string securedPassword;


// Set the secured password
void inputPassword(){
	cout << "Please enter a password:\n";
	cin >> securedPassword;
}

// check if test password is equal to secured password
bool checkPassword(string str){
	return str == securedPassword;
}

// Check if all characters of the string are the last possible combination
bool isStringEnd(string s)
{
    int n = s.length();
    for (int i = 1; i < n; i++)
        if (s[i] != ')')
            return false;

    return true;
}

class testProperties{
public:
	int wordLength;
	int charLength;
	int *tryChars;

	// Setup empty one letter password test
	testProperties(){
		wordLength = 1;
		charLength = 1;
		tryChars = new int[1];
	}

	// Check to see if password needs additional character
	// If not, change it to next combination
	void updatePassword(){
		// Get the number of characters from the right labeled ')'
		int endCount = 0;
		for(int i = wordLength - 1; i >= 0; i--){
			if(tryChars[i] == characterSymbols - 1){
				endCount++;
			}
			else{
				break;
			}
		}
		// If there are no end characters, move to next possible combination at last letter
		if(endCount == 0){
			tryChars[wordLength - 1]++;
		}
		// If there are some end characters, reset them and move the character before them down by one
		else if(endCount < wordLength){
			tryChars[wordLength - endCount - 1]++;
			for(int i = wordLength - endCount; i < wordLength; i++){
				tryChars[i] = 0;
			}
		}
		// If all characters are ')' add a new digit and reset all characters
		else{
			wordLength++;

			tryChars = new int[wordLength];

			for(int i = 0; i <= wordLength; i++){
				tryChars[i] = 0;
			}

			charLength = wordLength;
		}
	}
};

// algorithm for checking all possible passwords
string crackPassword(){
	cin.ignore();

	// List of possible characters in password
	const char possibleChars[72] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','G','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','9','0','!','@','#','$','%','^','&','*','(',')'};

	// Variable used to test if password is correct
	string password;

	// Number of characters in an instance of password and which character of possible_chars to try for each letter
	testProperties properties;

	while(!checkPassword(password)){
		password = "";
		for(int c_index = 0; c_index < properties.charLength; c_index++){

			char charToAdd = possibleChars[properties.tryChars[c_index]];
			password += charToAdd;

		}
		properties.updatePassword();
		cout << password << endl;
	}

	return password;
}


int main(){

	inputPassword();

	cout << "Press enter to crack the password.\n";
	cin.ignore();

	string crackedPassword = crackPassword();

	cout << "\nThe password is: " << crackedPassword << endl;

	return 0;
}






