/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

FileManagement.h

Below is "FileManagement" class, which is called by the Workflow class.
This class is a sub class of the "Workflow" class so the file streams can be used.
This class will allow file system access.
The is a default constructor and no data members.
The member functions include an open and close for both input and output streams.
A function fileCorrupt() to check to see if a input file is corrupt.
A function writeToTempFile() to write to an output file
A function readFromFile() to return a string of one line of rawData from the file.


*/

// Header Guard
#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

//Directives
#include "Workflow.h"

#include <fstream>

//Namespaces
using std::ifstream;
using std::ofstream;



class FileManagement : public WorkFlow
{
public:
	//default constructor
	FileManagement();

	//**********Destructor*********
	~FileManagement();

	//**********Member Functions**********
	void openFileInstream(ifstream& fileStream, const string userFile);
	//Pre-condition: File stream has been created and file Directory has been given
	//Post-conditon:Files have been opened as an instream
	//Open the diractory files that user has given to be able to read

	void openFileOutstream(ofstream& fileStream, const string& userFile);
	//Pre-condition: File stream has been created and file Directory has been given
	//Post-conditon:Files have been opened as an outstream
	//Open the diractory files that user has given and able to read

	void fileCorrupt(ifstream& fileStream);
	//Pre-condition:  File stream has been created and file is open
	//Post-conditon:Failure message will print to screen if file is corrupt. 
	//Check to see if file failed to open

	void closeInputFile(ifstream& fileToClose);
	//Pre-condition: File stream has been created and file is open
	//Post-conditon:File has been closed
	//Close the diractory files that user has given

	void closeOutputFile(ofstream& fileToClose);
	//Pre-condition: File stream has been created and file is open
	//Post-conditon:File has been closed
	//Close the diractory files that user has given

	void writeToTempFile(ofstream& fileStream, const string& data);
	//Pre-Condition:File stream has been created and file is open
	//Post-Condition:File is update with string data
	//Write into a temporary file

	void readFromFile(ifstream& fileStream, string& data);
	//Pre-Condition:File stream has been created and file is open
	//Post-Condition: string data is updated with a line of raw data from input file
	//grab a line of data from the input file

	void clearFile(ofstream& fileStream, const string& userFile);
	//Pre-Condition:File stream has been created
	//Post-Condition:File is empty
	//clear the contents of a file

};
#endif