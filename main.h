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
};

struct collection{ 
	vector<termsInDoc> indexDocs; // all docs with num terms
	vector<term> terms; // all terms in collection
}; 

class docIndex{
	private:
		collection index;
		term t; 

		// exists in the collectino, returns index number
		int exist(string text){
			int i;
			for(i = 0; i < index.terms.size(); i++){
				if(!strcmp(text.c_str(), index.terms[i].t.c_str())){
					return i;
				}
			}
			return -1;
		}

		// add term into the collection
		void addTerm(string text, int docId){
			cout << text << endl;
			int i = exist(text);
			term x = addPosting(text,docId);

			if(i > -1){
				index.terms[i] = addPosting(text, docId);
			} else{
				term x = addPosting(text,docId);
				index.terms.push_back(x);
			}
		}

		// add posting to term
		term addPosting(string text, int docId){
			t.t = text;
			for(set<int>::iterator i=t.ids.begin(); i!=t.ids.end(); ++i){
				if(*i == docId){
					for(int j = 0; j < t.postings.size(); j++){
						if(t.postings[j].first == docId){
							t.postings[j].second++;
							return t;
						}
					}
				}
			}
			t.ids.insert(docId);
			posting p = make_pair(docId, 1);
			t.postings.push_back(p);

			return t;
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
			ifstream input; 
			int fileCount = 1;
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
					while(!input.eof()){
						int stopFlag = false;

						input >> word;
						transform(word.begin(), word.end(), word.begin(), ::tolower); 
						
						// take out stop words then count terms

						// take out hyphenated words
						// posting list

						// batch of documents -> partial index -> index merge
						// sorted list -> merge lists of the same

						for(int i = 0; i < stopList.size(); i++){
							if(strcmp(word.c_str(), (stopList[i]).c_str())){
								stopFlag = true;
								break;
							}
						}
						if(!stopFlag){
							cout << "flag true" << endl;
							addTerm(word, fileCount);
							index.indexDocs[fileCount--].second++;
						}
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

		void tfidf(int ind){
			print(index.terms[ind].t, index.indexDocs);
		}

		void test(string input){
			int exists = exist(input);
			if(exists == -1){	// if term is in index
				cout << "Term not found in index." << endl;
				return;
			}
			tfidf(exists);
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
				output << k.t << endl << "    num docs with term: " << k.ids.size();
				for(int j = 0; j < k.postings.size(); j++){
					output << "    Doc: " << k.postings[j].first << ": " << k.postings[j].second << " times\n";
				}
			}

			cout << "   Document Index file created. Stop words omitted." << endl;

			output.close();
		}
};



#endif