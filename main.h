#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

typedef pair<int, int> posting; // (docId, freq of term in doc)
typedef pair<int, int> termsInDoc; // (docId, total num terms in doc)

struct term{ 
	string t; // term in index
	set<int> ids; // num of docs with term
	vector<posting> postings; // list of term postings

		// add posting to term
	void addPosting(string text, int docId){
		t = text;
		for(set<int>::iterator i=ids.begin(); i!=ids.end(); ++i){
			if(*i == docId){
				for(int j = 0; j < postings.size(); j++){
					if(postings[j].first == docId){
						postings[j].second++;
						return;
					}
				}
			}
		}
		ids.insert(docId);
		posting p = make_pair(docId, 1);
		postings.push_back(p);
	}
};

struct collection{ 
	vector<termsInDoc> indexDocs; // all docs with num terms
	vector<term> terms; // all terms in collection


	// add term into the collection
	void addTerm(string text, int docId){

		int i, ind = -1;
		for(i = 0; i < terms.size(); i++){
			if(strcmp(text.c_str(), terms[i].t.c_str()) == 0){
				ind = i;
				break;
			}
		}

		if(ind == -1){
			term x;
			x.addPosting(text,docId);
			terms.push_back(x);
			return;
		} else{
			terms[ind].addPosting(text, docId);
		}
	}
}; 

class docIndex{
	private:
		collection index;
		term t; 

		void initVars(){
			index.indexDocs.resize(20);
			t.t = "";			
		}
		/*		
			if term is in word index 
			- display list of positings for that term
			- for each posting, generate the term weightings (tf, idf, tf-idf) as such
		*/
		void print(string text, vector<termsInDoc> docs){
			t.t = text;
			int k = 20; // total num of docs
			int pSize = t.postings.size(); // num of docs with term
			
			// IDF(t) = log_e(Total number of documents / Number of documents with term t in it).
			double idf = log(k / (double)pSize);

			cout << "Format of result: (tf, idf, tf*idf)." << endl;

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
			initVars();

			ifstream input; 
			int fileCount = 1, z = 0;
			string word;

			// used to take out stop words in data files
			ifstream stopWords; 
			vector<string>stopList;
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
					index.indexDocs[z].first = fileCount;
					string inTerms[30];
					while(input >> word){
						int stopFlag = false;

						transform(word.begin(), word.end(), word.begin(), ::tolower); 
						int termCount = 0;
						size_t punct = word.find_first_of(",./<>?\\:;\'\"!@#$%^&*(){}[]-_=+");

						while (punct != string::npos){
							inTerms[termCount] = word.substr(0, punct);
							word = word.substr(punct + 1, word.size());
							punct = word.find_first_of(",./<>?\\:;\'\"!@#$%^&*(){}[]-_=+");
							termCount++;
						}
						inTerms[termCount] = word;

						for(int i = 0; i < stopList.size(); i++){
							if(strcmp(word.c_str(), (stopList[i]).c_str()) == 0){
								stopFlag = true;
								break;
							}
						}
						if(stopFlag){ continue; }

						index.addTerm(word, fileCount);
						index.indexDocs[z].second++;

						termCount++;
					}
				}
				input.close();

				cout << "    file" << index.indexDocs[z].first << "  seen." << endl;
				fileCount++; z++;
			}
		}

	public:
		docIndex(){
			createIndex();
		}

		void tfidf(int ind){
			print(index.terms[ind].t, index.indexDocs);
		}

		void test(string input){
			int i, ind = -1;
			for(i = 0; i < index.terms.size(); i++){
				if(strcmp(input.c_str(), index.terms[i].t.c_str()) == 0){
					ind = i;
					break;
				}
			}

			if(ind == -1){	// if term is in index
				cout << "Term not found in index." << endl;
				return;
			}
			tfidf(ind);
		}

		//testing purposes
		void print_index(){
			// output to docIndex for 2nd index creation
			ofstream output; output.open("index.txt");
			output << "Document Index contains:\n";

			for(int i = 0; i < index.indexDocs.size(); i++){
				termsInDoc k = index.indexDocs[i];
				output << "Doc: " << k.first << ": " << k.second << " terms\n";
			}

			output << "\nPosting List contains:\n";
			for(int i = 0; i < index.terms.size(); i++){
				term k = index.terms[i];
				output << k.t << "(" << k.ids.size() << ")" << endl;
				for(int j = 0; j < k.postings.size(); j++){
					output << "    Doc: " << k.postings[j].first << ": " << k.postings[j].second << " times\n";
				}
			}

			cout << "   Document Index file created. Stop words omitted." << endl;

			output.close();
		}
};



#endif