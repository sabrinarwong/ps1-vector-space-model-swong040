#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "docIndex.h"
#include <fstream>
#include <iomanip>
#include <sstream>


using namespace std;

void createPostingList(){
	
}

void createIndices(){
	ifstream input; 
	int fileCount = 1;
	
	while (fileCount < 21){
		ostringstream count;
	
		count << std::setw(2) << std::setfill('0') << fileCount;
		string file = "./data/file" + count.str() + ".txt";
		input.open(file);
		if(input.is_open()){
			// cout << file << endl;


			// posting list

			// document index

		}

		fileCount++;
	}

}


#endif