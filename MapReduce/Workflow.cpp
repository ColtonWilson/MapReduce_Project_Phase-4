/*Colton Wilson and Anthony Redamonti
*CSE 687- Object Oriented Design
*Syracuse University
*MapReduce - Phase #1
*04/07/22
*This program contains the function definitions to the member functions located in Workflow.h
*/

//Directives
#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Reduce.h"
#include "Sorting.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


//Namespaces
using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;


//default constructor
//TODO:Can to a try-catch to make sure actual string values are submitted
WorkFlow::WorkFlow() {}
//WorkFlow constructor with three parameters
WorkFlow::WorkFlow(string inputFile, string intermediateFile, string outputFile) : inputFileLocation{ inputFile }, intermediateFileLocation{ intermediateFile }, outputFileLocation{ outputFile }
{
	

	ifstream inputFileStream;
	ofstream intermediateFileStream;

	FileManagement FileStreamSystem;
	FileStreamSystem.openFileInstream(inputFileStream, inputFile);
	FileStreamSystem.fileCorrupt(inputFileStream);
	FileStreamSystem.clearFile(intermediateFileStream);
	FileStreamSystem.closeOutputFile(intermediateFileStream);
	
	string data{ "Unknown" };
	while (data !=  "1")
	{
		FileStreamSystem.readFromFile(inputFileStream, data);
		if (data != "1")
		{
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

void WorkFlow::setFirstAttempt(const bool& update)
{
	firstAttempt = update;
}


//**********Getters**********
const string WorkFlow::getInputFileLocation(void) { return inputFileLocation; }

const string WorkFlow::getIntermediateFileLocation(void) { return intermediateFileLocation; }

const string WorkFlow::getOutputFileLocation(void) { return outputFileLocation; }

const bool WorkFlow::getFirstAttempt(void) { return firstAttempt; }
