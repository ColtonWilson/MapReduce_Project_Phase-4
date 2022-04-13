/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

FileManagement.cpp

Below is FileManagement.cpp, which is called by the Workflow class.
This class is a sub class of the "Workflow" class so the file streams can be used.
This class will allow file system access.
The is a default constructor and no data members.
The member functions include an open and close for both input and output streams.
A function fileCorrupt() to check to see if a input file is corrupt.
A function writeToTempFile() to write to an output file
A function readFromFile() to return a string of one line of rawData from the file. 


*/



//Directives
#include "FileManagement.h"

#include <iostream>
#include <fstream>
#include <string>

//Namespaces
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;



//default constructor
FileManagement::FileManagement() {}

//**********Destructor*********
FileManagement::~FileManagement() {}

//Opens a file as an input stream, function parameters are a reference to input stream and string of file name to open
void FileManagement::openFileInstream(ifstream& fileStream, const string userFile){ fileStream.open(userFile); }

//Opens a file as an output stream, function parameters are a reference to output stream and string of file name to open
//Will append the file, and keep the contents. 
void FileManagement::openFileOutstream(ofstream& fileStream, const string& userFile){ fileStream.open(userFile, std::ios_base::app); }

//Check if open instream file is corrupt and did not open
void FileManagement::fileCorrupt(ifstream& fileStream)
{
	//Check to see if file failed to open
	if (fileStream.fail())
	{
		//If true, print fail to screen and EXIT
		cout << "Input file failed to open" << endl;
		exit(EXIT_FAILURE);


	}
	//else print to screen a success message
	else
	{
		cout << "Input file succesfully opened." << endl;
	}

}

//To write from main input into the temporary intermediate file
void FileManagement::writeToTempFile(ofstream& fileStream, const string& data)
{
	//("jump", 1)...Example of what should be inserted into file
	fileStream << "(\"";
	fileStream << data;
	fileStream << "\", 1)\n";
}
//To read a line of raw data from the input file
void FileManagement::readFromFile( ifstream& fileStream, string& data)
{
	//If reached the end of the file, return one
	if (fileStream.eof())
	{
		data = "1";
	}
	//else update the string with a line of data
	std::getline(fileStream, data);

}

//Clear file of anything written.
void FileManagement::clearFile(ofstream& fileStream, const string& userFile) 
{
	//Open file and then close to clear the contents
	fileStream.open(userFile); 
	closeOutputFile(fileStream);
}

//close an input file
void FileManagement::closeInputFile(ifstream& fileToClose) { fileToClose.close(); }
//close an output file
void FileManagement::closeOutputFile(ofstream& fileToClose){ fileToClose.close(); }