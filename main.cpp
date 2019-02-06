#include <iostream>
#include "main.h"

#include <ctype.h>

using namespace std;

int main(){

	// create index here
	cout << "Creating index." << endl;
	docIndex *index = new docIndex();

	// index->print_index(); // testing purposes
	cout << "Index created." << endl << endl;


	cout << "Enter a term to query: " << endl;

	string input = "";
	cin >> input; transform(input.begin(), input.end(), input.begin(), ::tolower);

	while (input != "quit"){
		// test user input here
		index->test(input);

		cout << endl;
		cout << "Enter a term to query: " << endl;
		cin >> input; transform(input.begin(), input.end(), input.begin(), ::tolower);
	}

	return 0;
}