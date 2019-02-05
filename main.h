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
		int stopFlag = false;
	
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
				
				// take out stop words
				for(int i = 0; i < stopList.size(); i++){
					if(strcmp(stopList[i].c_str(),term.c_str())){
						stopFlag = true;
						break;
					}
				}
				if(!stopFlag){

				}

				// posting list


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



}


#endif