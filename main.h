#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <map>
#include <list>

using namespace std;

// class docIndex {
// 	private:
// 		map<int, int> mapDocs; // maps docNum, numTerms
// 		int count = 0;

// 	public:
// 		void test(string input);
//		void createIndex();

// };

// void createDocIndex(int fileNum, int termCount){
// 	mapDocs.insert(pair<int,int>(fileCount,termCount));


// 	// check for doc index
//   	cout << "mapDocs contains:\n";
// 	for (map<int,int>::iterator it=mapDocs.begin(); it!=mapDocs.end(); ++it)
// 		cout << it->first << " => " << it->second << '\n';
// }

void createPostingList(){
	
}

void createIndex(){
	ifstream input; 
	int fileCount = 1;
	map<int, int> mapDocs; // maps docNum, numTerms
	// map<string,pair(int,list<pair(int, int)>)> mapTerms// maps term, (#docs,(freq, doc#))

	// while (fileCount < 21){
		ostringstream fileNum;
	
		// file name
		fileNum << std::setw(2) << std::setfill('0') << fileCount;
		string file = "./data/file" + fileNum.str() + ".txt";
		input.open(file);
		if(input.is_open()){
			int termCount = 0;
			while(!input.eof()){
				string term = ""; 
				input >> term;
				transform(term.begin(), term.end(), term.begin(), ::tolower); 
				// posting list

				
				termCount++;
			}

			// document index
			mapDocs.insert(pair<int,int>(fileCount,termCount));

		}
		input.close();

		fileCount++;
	// }
	cout << "mapDocs contains:\n";
	for (map<int,int>::iterator it=mapDocs.begin(); it!=mapDocs.end(); ++it)
		cout << it->first << " => " << it->second << '\n';
}

void test(string input){

	// TF(t) = (Number of times term t appears in a document) / (Total number of terms in the document).
	// IDF(t) = log_e(Total number of documents / Number of documents with term t in it).



}


#endif