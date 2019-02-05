#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include <string.h>

using namespace std;


void createIndex(){
	ifstream input; 
	int fileCount = 1;
	map<int, int> mapDocs; // maps docNum, numTerms

	// used to take out stop words in data files
	ifstream stopWords; vector<string>stopList;
	stopWords.open("stoplist.txt");
	if(stopWords.is_open()){
		while(!stopWords.eof()){
			string stop;
			stopWords >> stop;
			stopList.push_back(stop);
		}
	}
	stopWords.close();
	cout << "   Stop Words vector created." << endl;

	while (fileCount < 21){
		ostringstream fileNum;
	
		// file name
		fileNum << std::setw(2) << std::setfill('0') << fileCount;
		string file = "./data/file" + fileNum.str() + ".txt";
		input.open(file);

		// read current document
		if(input.is_open()){
			int termCount = 0;
			while(!input.eof()){
				string term = ""; 
				int stopFlag = false;

				input >> term;
				transform(term.begin(), term.end(), term.begin(), ::tolower); 
				
				// take out stop words then count terms
				for(int i = 0; i < stopList.size(); i++){
					if(strcmp(stopList[i].c_str(), term.c_str())==0){
						//if term matches a stop word
						stopFlag = true;
						break;
					}
				}
				if(stopFlag) continue; // next term if curr is stop word

				
				// take out hyphenated words
				// posting list

				// batch of documents -> partial index -> index merge
				// sorted list -> merge lists of the same

				termCount++;

			}

			// document index
			mapDocs.insert(pair<int,int>(fileCount,termCount));

		}
		input.close();

		fileCount++;
	}

	// output to docIndex for 2nd index creation
	ofstream output; output.open("docIndex.txt");
	output << "Document Index contains:\n";
	for (map<int,int>::iterator it=mapDocs.begin(); it!=mapDocs.end(); ++it)
		output << "Doc: " << it->first << ": " << it->second << " terms\n";
	cout << "   Document Index file created. " << endl;

	output.close();
}

void test(string input){

	// TF(t) = (Number of times term t appears in a document) / (Total number of terms in the document).
	// IDF(t) = log_e(Total number of documents / Number of documents with term t in it).

	/* if term is in index
		display list of posting
		generate (tf,idf, tf-idf)
	if not in index
		display message
		return to main
	*/


	if(false){
		// if term is in index
		// 	display list of posting
		// 	generate (tf,idf, tf-idf)
	} else{
		cout << "Term not found in index." << endl;
		return;
	}

}


#endif