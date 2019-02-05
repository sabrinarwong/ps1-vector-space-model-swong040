#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

typedef pair<int, int> posting; // (docId, freq of term in doc)
typedef pair<int, int> termsInDoc; // (docId, total num terms in doc)

struct term{ 
	string t; // term in index
	set<int> ids; // num of docs with term
	vector<posting> postings; // list of term postings

	term(string text): t(text) {}; 

};


class docIndex{
	private:
		// check if term is in index
		void addPosting(string text, int docId){
			term t = text;
			for(set<int>::iterator i=t.ids.begin(); i!=t.ids.end(); ++i){
				if(*i == docId){
					for(int j = 0; j < t.postings.size(); j++){
						if(t.postings[j].first == docId){
							t.postings[j].second++;
							return;
						}
					}
				}
			}
			t.ids.insert(docId);
			posting p = make_pair(docId, 1);
			t.postings.push_back(p);
		}

		/*		
			if term is in word index 
			- display list of positings for that term
			- for each posting, generate the term weightings (tf, idf, tf-idf) as such
		*/
		void print(string text, vector<termsInDoc> docs){
			term t = text;
			int k = 20; // total num of docs
			int pSize = t.postings.size(); // num of docs with term
			
			// IDF(t) = log_e(Total number of documents / Number of documents with term t in it).
			double idf = log(k / (double)pSize);

			for(int i = 0; i < pSize; i++){
				int id, n;
				int freq = t.postings[i].second; // freq of term in doc
				for(int j = 0; j < docs.size(); j++){
					if(t.postings[i].first == docs[j].first){
						id = docs[j].first;
						n = docs[j].second;	// total num terms in doc
						break;
					}
				}
				// TF(t) = (Number of times term t appears in a document) / (Total number of terms in the document).
				double tf = freq / (double)n;

				cout << "Doc: " << id << " : (" 
					 << tf << ", " 
					 << idf << ", " 
					 << tf * idf << ")" << endl;
			}



		}


		void createIndex(){
			ifstream input; 
			int fileCount = 1;

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

						// take out hyphenated words
						// posting list

						// batch of documents -> partial index -> index merge
						// sorted list -> merge lists of the same

						termCount++;

					}

					// document index

				}
				input.close();

				fileCount++;
			}

		}

	public:
		docIndex(){
			createIndex();
		}

};

void test(string input){

	// int exists = docIndex::search(input);
	// if(exists){	// if term is in index
	// 	docIndex::print(exists);

	// } else{
	// 	cout << "Term not found in index." << endl;
	// 	return;
	// }

}

#endif