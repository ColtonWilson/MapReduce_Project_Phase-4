/*Colton Wilson and Anthony Redamonti
*CSE 687- Object Oriented Design
*Syracuse University
*MapReduce - Phase #1
*04/07/22
*This program contains the function definitions to the member functions located in FileManagement.h
*/
/*File Management*/
//Directives
#include "FileManagement.h"
#include "Workflow.h"


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


void FileManagement::openFileInstream(ifstream& fileStream, const string userFile)
{
	fileStream.open(userFile);

}
void FileManagement::openFileOutstream(ofstream& fileStream, const string& userFile)
{	
	fileStream.open(userFile, std::ios_base::app);
	
}

void FileManagement::fileCorrupt(ifstream& fileStream)
{
	//Check to see if file failed to open
	if (fileStream.fail())
	{
		//If true, print fail to screen and EXIT
		cout << "Input file failed to open" << endl;
		exit(EXIT_FAILURE);


	}
	else
	{
		cout << "Input file succesfully opened." << endl;
	}

}


//<-----------------------------Starting updates---------> Going to set this up to only access to read and write
void FileManagement::writeToTempFile(ofstream& fileStream, const string& data)
{
	//("jump", 1)
	fileStream << "(\"";
	fileStream << data;
	fileStream << "\", 1)\n";
}

void FileManagement::readFromFile( ifstream& fileStream, string& data)
{
	if (fileStream.eof())
	{
		data = "1";
	}
	std::getline(fileStream, data);

}






void FileManagement::clearFile(ofstream& fileStream) { fileStream.clear(); }
void FileManagement::closeInputFile(ifstream& fileToClose) { fileToClose.close(); }
void FileManagement::closeOutputFile(ofstream& fileToClose){ fileToClose.close(); }