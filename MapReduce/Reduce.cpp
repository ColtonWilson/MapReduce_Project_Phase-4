/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Reduce.cpp

Below is the Reduce.cpp. 
The Reduce class is called by the Workflow class.
The constructor takes the output file path as an argument.
The public data member function "reduce" takes an input string as
its argument. It interprets the key and calculates the total in
the iterator before calling the private data member function
"export." Export will simply write the data in the correct format
to the output file path destination.

*/

// Directives
#include "Reduce.h"

// Reduce constructor
Reduce::Reduce(string* inputOutputFilePath) {
	
	// update the private data member variable
	outputFilePath = *inputOutputFilePath;
}

// Virtual Destructor
Reduce::~Reduce() {

}

// return a reference to the output file path.
string* Reduce::getOutputFilePath() {
	return(&outputFilePath);
}

// set the reference to the output file path
void Reduce::setOutputFilePath(string* inputOutputFilePath) {
	outputFilePath = *inputOutputFilePath;
}

// sums up the iterators and calls the export method.
// inputString is in form ("apple", [1, 1, 1, 1])
void Reduce::reduce(string* inputString) {

	// create a delimiter to find. Find the open bracket "[" character.
	string openBracket = "\", [";

	// create a delimiter to find. Find the closed bracket "]" character.
	string closedBracket = "])";

	// create a substring of just the iterator (all 1's).
	string iterator = (*inputString).substr((*inputString).find(openBracket), (*inputString).find(closedBracket));

	// calculate the number of 1's
	size_t numberOfOnes = (iterator.length() - 4) / 3;

	// find the position of the "\", [" string.
	size_t position = (*inputString).find("\", [");

	// extract the key
	string key = (*inputString).substr(2, position - 2);

	// export the data to the output file path.
	exportt(key, numberOfOnes);
}

// export the data to the output file path (one entry at a time)
void Reduce::exportt(string key, size_t sum) {
	
	// initialize local variables
	ofstream outputFile;

	// open the file for editing.
	outputFile.open(outputFilePath, ios_base::app);

	// write the output to the text file in the proper format.
	outputFile << "(\"" << key << "\"), " << to_string(sum) << "\n";

	// close the file.
	outputFile.close();
}
