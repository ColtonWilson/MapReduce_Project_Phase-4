#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include "Workflow.h";
#include "Sorting.h";
#include "Reduce.h";
#include "Map.h";
#include "FileManagement.h";

#include <fstream>


BOOST_AUTO_TEST_SUITE(TestingMapReduce)

BOOST_AUTO_TEST_CASE(Map_Test)
{
	cout << "*****************Map_Test***************" << std::endl;
	ifstream inputFileStream;
	ofstream intermediateFileStream;
	string inputFile = "input.txt";
	string intermediateFile = "intermediate.txt";
	//Create an object of the FileManagement class
	FileManagement FileStreamSystem;
	FileStreamSystem.clearFile(intermediateFileStream, inputFile);
	string firstData{ "This" };
	Map addToFile(inputFile, firstData);
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
			Map addToFile(intermediateFile, data);
		}

	}
	FileStreamSystem.closeInputFile(inputFileStream);

	FileStreamSystem.openFileInstream(inputFileStream, intermediateFile);
	FileStreamSystem.readFromFile(inputFileStream, data);

	const char* a = "(\"this\", 1)";
	BOOST_TEST(data == a);
	
}


BOOST_AUTO_TEST_CASE(Sort_Test)
{
	cout << "*****************Sort_Test***************" << std::endl;
	// Sorting and Reducing
	// declare and initialize local variables.
	string intermediateFilePath = "intermediate.txt"; // intermediate file path
	string* intermediateFilePathPntr = &intermediateFilePath;

	FileManagement FileStreamSystem;

	// initialize local variables
	ofstream outputFileStream;

	// create an instance of the Sorting class.
	Sorting sortingObj(intermediateFilePathPntr);


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

	// local variables used to calculate the percentage
	size_t wordsReduced{ 0 };
	double percentageComplete{ 0 };
	double percentageCompareValue{ 0.05 };
	double percentageCompareIncrementValue{ 0.05 };

		// format the file.
		sortingObj.format();

		// open the intermediate file
		FileStreamSystem.openFileInstream(inputFileStreamObj, *intermediateFilePathPntr);

		// assign the entry string pointer
		entryStrPntr = &entryString;

		FileStreamSystem.closeInputFile(inputFileStreamObj);

		string data{ "Unknown" };

		FileStreamSystem.openFileInstream(inputFileStreamObj, intermediateFilePath);
		FileStreamSystem.readFromFile(inputFileStreamObj, data);

		const char* a = "(\"this\", [1]), (\"1\", [1])";
		BOOST_TEST(data == a);

}


BOOST_AUTO_TEST_CASE(Reduce_Test)
{
	cout << "*****************Reduce_Test***************" << std::endl;
	Workflow percentCheck;
	// Sorting and Reducing
	// declare and initialize local variables.
	string intermediateFilePath = "intermediate.txt"; // intermediate file path
	string outputFilePath = "output.txt";
	string* intermediateFilePathPntr = &intermediateFilePath;
	string* outputFilePathPntr = &outputFilePath;

	// initialize local variables
	ofstream outputFileStream;

	// open the file for editing.
	FileManagement FileStreamSystem;
	FileStreamSystem.clearFile(outputFileStream, outputFilePath);

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

	// local variables used to calculate the percentage
	size_t originalWordListLengthCopy{ 0 };
	double percentageComplete{ 0 };
	double percentageCompareValue{ 0.05 };
	double percentageCompareIncrementValue{ 0.05 };

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

	FileStreamSystem.closeInputFile(inputFileStreamObj);

	string data{ "Unknown" };

	FileStreamSystem.openFileInstream(inputFileStreamObj, "output.txt");
	FileStreamSystem.readFromFile(inputFileStreamObj, data);

	const char* a = "(\"this\"), 1";
	BOOST_TEST(data == a);
}



BOOST_AUTO_TEST_CASE(SeparateFileFromDirectory_Test)
{
	cout << "*****************SeparateFileFromDirectory_Test***************" << std::endl;
	Workflow test;
	test.separateOutputPath("C:\\first\\second\\third\\fourth\\file.txt", "output");
	string direcotryPath = test.getOutputFileDirectoryLocation();

	const char* a = "C:\\first\\second\\third\\fourth";
	BOOST_TEST(direcotryPath == a);

}

BOOST_AUTO_TEST_CASE(FullRunFile_Test)
{
	cout << "*****************FullRunFile_Test***************" << std::endl;
	ifstream inputFileStream;
	ofstream intermediateFileStream;
	string inputFile = "input.txt";
	string intermediateFile = "intermediate.txt";
	string outputFile = "output.txt";
	//Create an object of the FileManagement class
	FileManagement FileStreamSystem;
	FileStreamSystem.clearFile(intermediateFileStream, inputFile);
	string firstData{ "This" };
	Map addToFile(inputFile, firstData);

	Workflow(inputFile, intermediateFile, outputFile);

	string data{ "Unknown" };

	FileStreamSystem.openFileInstream(inputFileStream, "output.txt");
	FileStreamSystem.readFromFile(inputFileStream, data);

	const char* a = "(\"this\"), 1";
	BOOST_TEST(data == a);

}

BOOST_AUTO_TEST_CASE(FullRunDirectory_Test)
{
	cout << "*****************FullRunDirectory_Test***************" << std::endl;
	ifstream inputFileStream;
	ofstream intermediateFileStream;
	string inputFile = "C:\\Users\\Colton Wilson\\Desktop\\CIS687 OOD\\testFolder\\input.txt";
	string intermediateFile = "C:\\Users\\Colton Wilson\\Desktop\\CIS687 OOD\\testFolder\\intermediate.txt";
	string outputFile = "C:\\Users\\Colton Wilson\\Desktop\\CIS687 OOD\\testFolder\\output.txt";
	//Create an object of the FileManagement class
	FileManagement FileStreamSystem;
	FileStreamSystem.clearFile(intermediateFileStream, inputFile);
	string firstData{ "This" };
	Map addToFile(inputFile, firstData);

	Workflow(inputFile, intermediateFile, outputFile);

	string data{ "Unknown" };

	FileStreamSystem.openFileInstream(inputFileStream, outputFile);
	FileStreamSystem.readFromFile(inputFileStream, data);

	const char* a = "(\"this\"), 1";
	BOOST_TEST(data == a);

}

BOOST_AUTO_TEST_CASE(ValidFileCheck_Test)
{
	
	string inputFile = "input";
	string tempFile = "temp";
	string outputFile = "output";
	Workflow workflowTest;
	workflowTest.checkFilesValid(inputFile, tempFile, outputFile);
	
	BOOST_CHECK(true == workflowTest.getValidInputFile());
	BOOST_CHECK(true == workflowTest.getValidIntermediateFile());
	BOOST_CHECK(true == workflowTest.getValidOutputFile());

}



BOOST_AUTO_TEST_SUITE_END()