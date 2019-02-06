# ps1-vector-space-model-swong040
ps1-vector-space-model-swong040 created by GitHub Classroom

## Running PS1
To run Phase 2 of this project, run the following commands:

```bash
git clone https://github.com/CS172-UCR/ps1-vector-space-model-swong040.git;
g++ -Wall -w -std=c++11 main.cpp -o main.out;
./main.out;
```
The user can type in a word and the program will return whether or not the term is in the index. If the term is, then a postings list with the term and its corresponding (tf, idf, tf.idf) result is shown.

## About
Included in this repo is: 
1. an excel sheet of Part 1
2. source code (main.cpp and main.h) to create indices and compute tf.idf for the term
	a. file *main.h* has the code for docIndex() and test()
3. the output file (output.txt) of the tests ran.

## Assumptions
* Terms are not stemmed.

## Contributing
Sabrina Wong
swong040@ucr.edu
861195047

