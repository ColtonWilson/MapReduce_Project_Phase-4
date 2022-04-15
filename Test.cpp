#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include "Workflow.h";
#include "Sorting.h";
#include "Reduce.h";
#include "Map.h";
#include "FileManagement.h";

#include <fstream>

BOOST_AUTO_TEST_CASE(first_test)
{
	ifstream inputFileStream;
	ofstream intermediateFileStream;
	string inputFile = "input.txt";
	string intermediateFile = "intermediate.txt";
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
	FileStreamSystem.closeInputFile(inputFileStream);

	FileStreamSystem.openFileInstream(inputFileStream, intermediateFile);
	FileStreamSystem.readFromFile(inputFileStream, data);

	const char* a = "(\"this\", 1)";
	BOOST_TEST(data == a);
	
}