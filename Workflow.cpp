/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Workflow.cpp

---Note: This file does include the BOOST library in order to compile.

Below is Workflow.cpp, which is called by the  main() in Executive.cpp.
The constructor takes three string directory names and saves the strings into private data members.
The constructor will then tie together all the header files with supporting logic.
The public data member functions are setters and getters for each data member. 


*/

//Directives
#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Reduce.h"
#include "Sorting.h"
#include "NotValidInputFile.h"
#include "NotValidOutputFile.h"


//default constructor
WorkFlow::WorkFlow() {}
//WorkFlow constructor with three parameters
WorkFlow::WorkFlow(string inputFile, string intermediateFile, string outputFile)
{
	if (boost::filesystem::is_directory(inputFile))
	{
		inputIsDirectory(inputFile, intermediateFile, outputFile);
	}
	else
	{
		inputIsFile(inputFile, intermediateFile, outputFile);
	}
	/*
	

	//----------------Verify if file directories are valid--------------
	
	//Verify if the input directory given is valid
	//Keep asking until valid file is given
	while (validInputFile == false)
	{
		//try block to attempt to the input file directory
		try {
			setInputFileLocation(inputFile);
		}
		//If not valid then throw exception
		catch (const NotValidInputFile& notValidFileException) {
			cout << "Exception occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validInputFile == false)
		{
			cout << "\nPlease enter a valid input file directory.\n"
				<< "Input File Directory: >>> ";
			cin >> inputFile;
		}

	}

	//Get path to intermediate output directory
	separateOutputPath(intermediateFile, "intermediate");
	while (validIntermediateFile == false)
	{
		//try block to attempt to the input file directory
		try {
			setIntermediateFileLocation(intermediateFile);
		}
		//If not valid then throw exception
		catch (const NotValidInputFile& notValidFileException) {
			cout << "Exception occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validIntermediateFile == false)
		{
			cout << "\nPlease enter a valid temporary intermediate file directory.\n"
				<< "Intermediate File Directory: >>> ";
			cin >> intermediateFile;
			//separateOutputPath(intermediateFile, "intermediate");
		}

	}

	//Get path to final output directory
	separateOutputPath(outputFile, "output");
	while (validOutputFile == false)
	{
		//try block to attempt to the input file directory
		try {
			setOutputFileLocation(getOutputFileDirectoryLocation());
		}
		//If not valid then throw exception
		catch (const NotValidInputFile& notValidFileException) {
			cout << "Exception occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validOutputFile == false)
		{
			cout << "\nPlease enter a valid final output file directory.\n"
				<< "Output File Directory: >>> ";
			cin >> outputFile;
			separateOutputPath(outputFile, "output");
		}

	}
	
	*/

	
}

//**********Destructor*********
WorkFlow::~WorkFlow() {}

//**********Member Function**********


//Path to run if input is a File
void WorkFlow::inputIsFile(string inputFile, string intermediateFile, string outputFile)
{
	//<-----------------Part 1------------------------------------------>
	// Writing from input file to intermediate file
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
	while (data != "1")
	{
		//Get a line of data from the input file
		FileStreamSystem.readFromFile(inputFileStream, data);
		//Check if data was not the end of file
		if (data != "1")
		{
			//Create a Map class object with the output file and data given.
			//This will add the data to the file given
			Map toTempFile(intermediateFile, data);
		}

	}
	FileStreamSystem.closeInputFile(inputFileStream);

	//<-----------------Part 2------------------------------------------>
	// Sorting and Reducing
	// declare and initialize local variables.
	string intermediateFilePath = intermediateFile; // intermediate file path
	string outputFilePath = outputFile;
	string* intermediateFilePathPntr = &intermediateFilePath;
	string* outputFilePathPntr = &outputFilePath;

	// initialize local variables
	ofstream outputFileStream;

	// open the file for editing.
	FileStreamSystem.clearFile(outputFileStream, outputFile);

	// create an instance of the Sorting class.
	Sorting sortingObj(intermediateFilePathPntr);

	// create an instance of the Reduce class.
	Reduce reduceObj(outputFilePathPntr);

	// Create local variables. Input file stream object
	ifstream inputFileStreamObj;
	string line;
	string entryString{ NULL };
	string* entryStrPntr{ NULL };

	// create a delimiter to find the following string: ")"
	string closedParenthesis{ ")" };
	string openParenthesis{ "(" };
	size_t openPos{ NULL };
	size_t closedPos{ NULL };

	try {
		// format the file.
		sortingObj.format();

		// open the intermediate file
		FileStreamSystem.openFileInstream(inputFileStreamObj, *intermediateFilePathPntr);

		// assign the entry string pointer
		entryStrPntr = &entryString;

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

				// if the open and closed parentheses were found, pass the substring to the reduce class.
				if ((openPos != string::npos) && (closedPos != string::npos)) {

					// extract the entry. 
					entryString = line.substr(openPos, (closedPos - openPos) + 1);

					// pass the string to the reduce method from the Reduce class.
					reduceObj.reduce(entryStrPntr);
				}

				// update the offset into the line for the next search.
				offset = closedPos + 1;

				// Find the position of the next open parenthesis. 
				openPos = line.find(openParenthesis, offset);
			}
		}

		// Print the SUCCESS.txt file to output directory.
		FileStreamSystem.openFileOutstream(outputFileStream, getOutputFileDirectoryLocation() + "\\SUCCESS.txt");

		// Close the SUCCESS.txt file.
		FileStreamSystem.closeOutputFile(outputFileStream);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Workflow::Constructor\".\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"Workflow::Constructor\".\n";
		throw;
	}
	//Print SUCCESS file to output directory
	FileStreamSystem.openFileOutstream(outputFileStream,  "SUCCESS.txt");
	FileStreamSystem.closeOutputFile(outputFileStream);


}

//Path to run if input is a directory
void WorkFlow::inputIsDirectory(string inputFile, string intermediateFile, string outputFile)
{
	//<-----------------Part 1------------------------------------------>
// Writing from input file to intermediate file
//Create an input and output stream class
	ifstream inputFileStream;
	ofstream intermediateFileStream;
	//Create an object of the FileManagement class
	FileManagement FileStreamSystem;
	//Clear the contents of the intermediate file which will hold the output of the Map class. This will also close the stream
	FileStreamSystem.clearFile(intermediateFileStream, intermediateFile);

	vector<string> listOfFiles = FileStreamSystem.getAllFilesInDir(inputFile);

	for (auto str : listOfFiles)
	{
		cout << str << endl;
	}

	cout << "*************************************************************************" << endl;
	//Open the input file and connect to the in stream. Then double check to make sure file is not corrupt
	for (auto str : listOfFiles)
	{
		FileStreamSystem.openFileInstream(inputFileStream, str);
		FileStreamSystem.fileCorrupt(inputFileStream);

		//Initiate a variable to hold raw data given by the input file
		string data{ "Unknown" };
		//Keep collecting data until the end of file and get a return of "1"
		while (data != "1")
		{
			//Get a line of data from the input file
			FileStreamSystem.readFromFile(inputFileStream, data);
			//Check if data was not the end of file
			if (data != "1")
			{
				//Create a Map class object with the output file and data given.
				//This will add the data to the file given
				Map toTempFile(intermediateFile, data);
			}

		}
		FileStreamSystem.closeInputFile(inputFileStream);

	}
	
	
	

	//<-----------------Part 2------------------------------------------>
	// Sorting and Reducing
	// declare and initialize local variables.
	string intermediateFilePath = intermediateFile; // intermediate file path
	string outputFilePath = outputFile;
	string* intermediateFilePathPntr = &intermediateFilePath;
	string* outputFilePathPntr = &outputFilePath;

	// initialize local variables
	ofstream outputFileStream;

	// open the file for editing.
	FileStreamSystem.clearFile(outputFileStream, outputFile);

	// create an instance of the Sorting class.
	Sorting sortingObj(intermediateFilePathPntr);

	// create an instance of the Reduce class.
	Reduce reduceObj(outputFilePathPntr);

	// Create local variables. Input file stream object
	ifstream inputFileStreamObj;
	string line;
	string entryString{ NULL };
	string* entryStrPntr{ NULL };

	// create a delimiter to find the following string: ")"
	string closedParenthesis{ ")" };
	string openParenthesis{ "(" };
	size_t openPos{ NULL };
	size_t closedPos{ NULL };

	try {
		// format the file.
		sortingObj.format();

		// open the intermediate file
		FileStreamSystem.openFileInstream(inputFileStreamObj, *intermediateFilePathPntr);

		// assign the entry string pointer
		entryStrPntr = &entryString;

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

				// if the open and closed parentheses were found, pass the substring to the reduce class.
				if ((openPos != string::npos) && (closedPos != string::npos)) {

					// extract the entry. 
					entryString = line.substr(openPos, (closedPos - openPos) + 1);

					// pass the string to the reduce method from the Reduce class.
					reduceObj.reduce(entryStrPntr);
				}

				// update the offset into the line for the next search.
				offset = closedPos + 1;

				// Find the position of the next open parenthesis. 
				openPos = line.find(openParenthesis, offset);
			}
		}

		// Print the SUCCESS.txt file to output directory.
		FileStreamSystem.openFileOutstream(outputFileStream, getOutputFileDirectoryLocation() + "\\SUCCESS.txt");

		// Close the SUCCESS.txt file.
		FileStreamSystem.closeOutputFile(outputFileStream);
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Workflow::Constructor\".\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"Workflow::Constructor\".\n";
		throw;
	}
	//Print SUCCESS file to output directory
	FileStreamSystem.openFileOutstream(outputFileStream, getOutputFileDirectoryLocation() + "\\SUCCESS.txt");
	FileStreamSystem.closeOutputFile(outputFileStream);


}



// Get File Name from a Path with or without extension
void WorkFlow::separateOutputPath(const string userInputFile, const string& fileType)
{
	try {
		// Create a Path object from File Path
		boost::filesystem::path pathObj(userInputFile);

		// Check if file has stem i.e. filename without extension
		if (pathObj.has_stem())
		{
			if (fileType == "intermediate")
			{
				// set the path of the user submitted file
				boost::filesystem::path p(userInputFile);

				//get the parent path
				boost::filesystem::path dir = p.parent_path();

				//set data member as a string to remember the path
				setIntermediateFileDirectoryLocation(dir.string());

				//setIntermediateFileLocation(userInputFile);
			}

			else
			{
				// set the path of the user submitted file
				boost::filesystem::path p(userInputFile);

				//get the parent path
				boost::filesystem::path dir = p.parent_path();

				//set data member as a string to remember the path
				setOutputFileDirectoryLocation(dir.string());

				//setOutputFileLocation(userInputFile);
			}
		}
		else
		{
			/*if (fileType == "intermediate")
			{
				// set the file name with extension from path object
				setIntermediateFileLocation(userInputFile);
			}
			else
			{
				// set the file name with extension from path object
				setOutputFileLocation(userInputFile);
			}*/
		}
	}

	// catch exception handled in exception class here
	catch (const runtime_error& exception) {
		cout << "\nException occurred in \"Workflow::Constructor\".\n";
		cout << exception.what();
		throw exception;
	}

	// catch any exception here
	catch (...) {
		cout << "\nException occurred in \"Workflow::Constructor\".\n";
		throw;
	}


}

//Check if the input file is valid
bool WorkFlow::checkIfFIle(const string& userInputFile)
{
	// Create a Path object from given path string
	boost::filesystem::path pathObj(userInputFile);
	// Check if path exists and is of a regular file
	if (!boost::filesystem::exists(pathObj) && !boost::filesystem::is_regular_file(pathObj))
		return true;

	return false;
}

//Check if the output file is valid
bool WorkFlow::checkOfFIle(const string& userInputFile)
{
	// Create a Path object from given path string
	boost::filesystem::path pathObj(userInputFile);
	// Check if path exists and is of a regular file
	if (!boost::filesystem::exists(pathObj) && !boost::filesystem::is_directory(pathObj))
		return true;

	return false;
}
//**********Setters**********
// Set the input file location.
void WorkFlow::setInputFileLocation(const string& userInputFile) 
{
	 
	//Verify input call to checkIfFile()
	if (checkIfFIle(userInputFile))
	{
		//If return true then throw exception
		throw NotValidInputFile{}; //terminate function
	}
	//If false then insert into inputFileLocation 
	else
	{
		inputFileLocation = userInputFile;
		//update validInputFile
		validInputFile = true;

	}

}

// Set the intermediate file location.
void WorkFlow::setIntermediateFileLocation(const string& userIntermediateFile) 
{
	//Verify input call to checkIfFile()
	if (checkOfFIle(userIntermediateFile))
	{
		//If return true then thro exception
		throw NotValidOutputFile{}; //terminate function
	}
	//If false then insert into inputFileLocation 
	else
	{
		//intermediateFileLocation = userIntermediateFile;
		separateOutputPath(userIntermediateFile, "intermediate");
		//update validInputFile
		validIntermediateFile = true;

	}
	
}

// Set the output file location.
void WorkFlow::setOutputFileLocation(const string& userOutputFile) 
{ 
	//Verify input call to checkIfFile()
	if (checkOfFIle(userOutputFile))
	{
		//If return true then throw exception
		throw NotValidInputFile{}; //terminate function
	}
	//If false then insert into inputFileLocation 
	else
	{
		outputFileLocation = userOutputFile;
		//update validInputFile
		validInputFile = true;

	}
	

}
// Set the intermediate file directory location.
void WorkFlow::setIntermediateFileDirectoryLocation(const string& userOutputFile) { intermediateFileDirectoryLocation = userOutputFile; }

// Set the output file directory location.
void WorkFlow::setOutputFileDirectoryLocation(const string& userOutputFile) { outputFileDirectoryLocation = userOutputFile; }


//**********Getters**********

// Get the input file location.
const string WorkFlow::getInputFileLocation(void) { return inputFileLocation; }

// Get the intermediate file location.
const string WorkFlow::getIntermediateFileLocation(void) { return intermediateFileLocation; }

// Get the output file location.
const string WorkFlow::getOutputFileLocation(void) { return outputFileLocation; }

// Get the intermediate file directory location.
const string WorkFlow::getIntermediateFileDirectoryLocation(void) { return intermediateFileDirectoryLocation; }

// Get the output file directory location.
const string WorkFlow::getOutputFileDirectoryLocation(void) { return outputFileDirectoryLocation; }


