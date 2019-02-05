#include <iostream>
#include "main.h"

#include <ctype.h>

using namespace std;

int main(){

	// create index here
	cout << "creating index." << endl;
	createIndex();
	cout << "index created." << endl << endl;


	cout << "Enter a term to query: " << endl;

	string input = "";
	cin >> input; transform(input.begin(), input.end(), input.begin(), ::tolower);

	while (input != "quit"){
		// test user input here
		test(input);

		cout << endl;
		cin >> input; transform(input.begin(), input.end(), input.begin(), ::tolower);
	}

	return 0;
}