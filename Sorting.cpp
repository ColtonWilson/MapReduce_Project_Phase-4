/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Sorting.cpp

Below is Sorting.cpp, which is called by the Workflow class.
The constructor takes the intermediate file path as an argument.
The public data member function "format" will format the data for
the Reduce class.

Example input data: ("a", 1), ("the", 1), ("is", 1), ("the", 1), ("a", 1)
Example output data: ("a", [1, 1]), ("the", [1, 1]), ("is", [1])

*/

// Directives
#include "Sorting.h"

// Reduce constructor
Sorting::Sorting(string* inputOutputFilePath) {

	// update the private data member variable
	intermediateFilePath = *inputOutputFilePath;
}

// Virtual Destructor
Sorting::~Sorting() {

	// clear the wordList
	wordList.clear();
}

// return a reference to the intermediate file path.
string* Sorting::getIntermediateFilePath() {
	return(&intermediateFilePath);
}

// set the reference to the intermediate file path
void Sorting::setIntermediateFilePath(string* inputIntermediateFilePath) {
	intermediateFilePath = *inputIntermediateFilePath;
}

// Formats the data for the Reduce class.
// Example input data: ("a", 1), ("the", 1), ("is", 1), ("the", 1), ("a", 1)
// Example output data : ("a", [1, 1]), ("the", [1, 1]), ("is", [1])
void Sorting::format() {

	// Create local variables. Input file stream object
	ifstream inputFileStreamObj;
	ofstream outputFileStreamObj;
	string line;
	string key{ NULL };

	// create a delimiter to find. Find the following string: ", 1),".
	string closedParenthesis{ ")" };
	string openParenthesis{ "(" };
	size_t openPos{ NULL };
	size_t closedPos{ NULL };
	word wordObj;

	// try reading the file and adding all words to the data structure (linked-list).
	try {
		// open the intermediate file
		inputFileStreamObj.open(intermediateFilePath);

		// get the first line from the file.
		while (getline(inputFileStreamObj, line)) {

			// find the position of the first open parenthesis
			openPos = line.find(openParenthesis);

			// offset for the find method of the string class.
			size_t offset{ 0 };

			// while there are words in this line, keep extracting them.
			while (openPos != string::npos) {

				// find the position of the closed parenthesis
				closedPos = line.find(closedParenthesis, offset);

				// if the open and closed parentheses were found, add the word to the linked list.
				if ((openPos != string::npos) && (closedPos != string::npos)) {

					// extract the first key from the line.
					key = line.substr(openPos + 2, closedPos - openPos - 6);

					// load the temporary word.
					wordObj.key = key;
					wordObj.numberOfOccurrences = 1;

					// push it onto the linked list.
					wordList.push_back(wordObj);
				}

				// update the offset into the line for the next search.
				offset = closedPos + 1;

				// Find the position of the next open parenthesis. 
				openPos = line.find(openParenthesis, offset);
			}
		}

		// close the file
		inputFileStreamObj.close();

	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Sorting::format\" method when reading data from file.\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"Sorting::format\" method when reading data from file.\n";
		throw;
	}

	// erase the contents of the file by opening an output file stream object.
	outputFileStreamObj.open(intermediateFilePath);

	// close the output file stream object.
	outputFileStreamObj.close();

	// list iterator for traversing through the word list.
	list<word>::iterator iteratorWordList1;
	list<word>::iterator iteratorWordList2;

	// words to compare
	word wordTemp1;
	word wordTemp2;

	// Try to write the data back to the intermediate file in the correct
	// format for the reduce class. Example: ("is", [1, 1, 1])
	try {

		// assign iterator
		iteratorWordList2 = wordList.begin();

		// perform the following on the entire list.
		while (iteratorWordList2 != wordList.end()) {

			// assign first temporary word
			wordTemp1 = *iteratorWordList2;

			// have iterator 1 start at the same element
			iteratorWordList1 = iteratorWordList2;

			// increment iterator 1
			iteratorWordList1++;

			// compare each word with the first word in the list.
			while (iteratorWordList1 != wordList.end()) {

				// assign the second word for comparison.
				wordTemp2 = *iteratorWordList1;

				// if the words have the same key, increment the number of occurrences
				// and delete remove the element from the linked list.
				if (wordTemp1.key == wordTemp2.key) {

					// increment number of occurrences.
					wordTemp1.numberOfOccurrences = wordTemp1.numberOfOccurrences + 1;

					// remove the second word from the list.
					iteratorWordList1 = wordList.erase(iteratorWordList1);
				}
				else {
					// increment the iterator to the next word in the list.
					iteratorWordList1++;
				}
			}

			// update the number of occurrences for the element in the linked list.
			*iteratorWordList2 = wordTemp1;

			// increment the second iterator for the next word.
			iteratorWordList2++;
		}

		// reformat file
		outputFileStreamObj.open(intermediateFilePath);

		// send all of the properly formatted data to the intermediate file
		iteratorWordList1 = wordList.begin();

		// number of words per line
		int wordsPerLine{ 7 };
		int counter{ 0 };

		// perform the following operation on the entire list.
		while (iteratorWordList1 != wordList.end()) {

			// assign the termporary word.
			wordTemp1 = *iteratorWordList1;

			// write the output to the text file in the proper format.
			outputFileStreamObj << "(\"" << wordTemp1.key << "\", [";

			// output the correct number of 1's.
			for (int i = 0; i < wordTemp1.numberOfOccurrences - 1; i++) {
				outputFileStreamObj << "1, ";
			}

			// send the last 1 and ending bracket.
			outputFileStreamObj << "1])";

			// increment the iterator.
			iteratorWordList1++;

			// if there are more words to output, send a comma and a space
			if (iteratorWordList1 != wordList.end()) {
				outputFileStreamObj << ", ";
			}

			// increment the counter
			counter = counter + 1;

			// if the counter == wordsPerLine, begin a new line and reset the counter.
			if (counter == wordsPerLine) {
				outputFileStreamObj << "\n";

				// reset the counter.
				counter = 0;
			}
		}

		// close the file.
		outputFileStreamObj.close();
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Sorting::format\" method when writing data to file.\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"Sorting::format\" method when writing data to file.\n";
		throw;
	}
}
