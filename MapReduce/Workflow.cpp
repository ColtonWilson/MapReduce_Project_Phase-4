/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Workflow.cpp

Below is Workflow.cpp, which is called by the  main() in Executive.cpp.
The constructor takes three string direcotry names and saves the strings into private data memebrs.
The constructior will then tie together all the header files with supporting logic.
The public data member functions are setters and getters for each data member. 


*/

//Directives
#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Reduce.h"
#include "Sorting.h"

#include <iostream>
#include <fstream>
#include <string>


//Namespaces
using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;


//default constructor
WorkFlow::WorkFlow() {}
//WorkFlow constructor with three parameters
WorkFlow::WorkFlow(string inputFile, string intermediateFile, string outputFile) : inputFileLocation{ inputFile }, intermediateFileLocation{ intermediateFile }, outputFileLocation{ outputFile }
{
	//Create an input and output stream class
	ifstream inputFileStream;
	ofstream intermediateFileStream;
	//Create an object of the FileManagement class
	FileManagement FileStreamSystem;
	//Open the input file and connect to the in stream. Then double check to make sure file is not corrupt
	FileStreamSystem.openFileInstream(inputFileStream, inputFile);
	FileStreamSystem.fileCorrupt(inputFileStream);
	//Clear the contents of the intermediate file which will hold the output of the Map class. This will also close the stream
	FileStreamSystem.clearFile(intermediateFileStream, intermediateFile);
	//Initiate a variable to hold raw data given by the input file
	string data{ "Unknown" };
	//Keep collecting data until the end of file and get a return of "1"
	while (data !=  "1")
	{
		//Get a line of data from the input file
		FileStreamSystem.readFromFile(inputFileStream, data);
		//Check if data was not the end of file
		if (data != "1")
		{
			//Create a Map class obect with the output file and data given.
			//This will add the data to the file given
			Map toTempFile(intermediateFile, data);
		}

	}
	
}

//**********Destructor*********
WorkFlow::~WorkFlow() {}

//**********Setters**********
void WorkFlow::setInputFileLocation(const string& userInputFile) { inputFileLocation = userInputFile; }

void WorkFlow::setIntermediateFileLocation(const string& userIntermediateFile) { intermediateFileLocation = userIntermediateFile; }

void WorkFlow::setOutputFileLocation(const string& userOutputFile) { outputFileLocation = userOutputFile; }

//**********Getters**********
const string WorkFlow::getInputFileLocation(void) { return inputFileLocation; }

const string WorkFlow::getIntermediateFileLocation(void) { return intermediateFileLocation; }

const string WorkFlow::getOutputFileLocation(void) { return outputFileLocation; }

