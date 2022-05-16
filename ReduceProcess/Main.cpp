/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
5/15/2022

Main.cpp

Below is Main.cpp file. 
This file has the main() function for the ReduceProcess.exe file.

It takes 3 command line arguments.
- IntermediateFilePath
- OutputFilePath
- Process Number

The process number ranges from 1 to the defined max number of processes.

*/

#define  _WIN32_WINNT   0x0601

//Directives
#include <Windows.h>

#include <iostream>
#include <string>
#include <fstream>

#include <boost/timer/timer.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "Sorting.h"

//Name spaces
using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;
using std::runtime_error;

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

// definition for reduce function in ReduceLibrary DLL.
typedef void (*funcReduce)(string, string);

void init_logging()
{
	logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

	logging::add_file_log(
		keywords::file_name = "logResult.log",
		keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%"
	);

	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::info
	);

	logging::add_common_attributes();
}

int main(int argc, char* argv[])
{
	init_logging();

	//Boost logging used to log errors, warnings, info, fatals etc.
	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

	/* set console output codepage to UTF-8 */
	if (!SetConsoleOutputCP(CP_UTF8)) {
		std::cerr << "error: unable to set UTF-8 codepage.\n";
		return 1;
	}

	//Start timer
	boost::timer::auto_cpu_timer t(3, "%w seconds\n");
	
	//Initiate variables to hold the names of the directory locations
	string inputFileName{ "Unknown" };
	string intermediateFileName{ "Unknown" };
	string outputFileName{ "Unknown" };

	//Banner Message
	cout << "*************************************************************************************"
		<< "\n\t\t\tReduce process created.";
	cout.flush();

	//<-----------------Part 2------------------------------------------>
	// Sorting and Reducing
	
	// convert the file path to a string
	string intermediateFilePath = argv[0];
	
	// store the process number.
	string processNumber = argv[2];

	// retrieve the size of the output 
	int intermediateFilePathSize = intermediateFilePath.size();

	// alter the output file path.
	string alteredIntermediateFilePath = intermediateFilePath.substr(0, intermediateFilePathSize - 4) + processNumber + intermediateFilePath.substr(intermediateFilePathSize - 4);

	// convert the output file path to a string
	string outputFilePath = argv[1];

	// retrieve the size of the output 
	int outputFilePathSize = outputFilePath.size();

	// alter the output file path.
	string alteredOutputFilePath = outputFilePath.substr(0, outputFilePathSize - 4) + processNumber + outputFilePath.substr(outputFilePathSize - 4);

	// assign pointers to the files.
	string* intermediateFilePathPntr = &alteredIntermediateFilePath;
	string* outputFilePathPntr = &alteredOutputFilePath;

	// Load the Reduce constructor from the ReduceLibrary DLL
	HINSTANCE reduceDllHandle;
	funcReduce Reduce;
	const wchar_t* reduceLibraryName = L"ReduceLibrary";

	// Load the library (DLL).
	reduceDllHandle = LoadLibraryEx(reduceLibraryName, NULL, NULL);   // Handle to DLL

	// perform the following if the DLL was able to be loaded.
	if (reduceDllHandle != NULL) {

		// Load the Reduce constructor from the DLL.
		Reduce = (funcReduce)GetProcAddress(reduceDllHandle, "Reduce");

		// initialize local variables
		ofstream outputFileStream;

		//Open file and then close to clear the contents
		outputFileStream.open(alteredOutputFilePath);
		outputFileStream.close();

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

		try {
			// format the file.
			sortingObj.format();

			// inform the user.
			cout << "\nWorkflow is now parsing the intermediate file and calling the Reduce class on each entry." << endl;

			// open the intermediate file
			try {
				inputFileStreamObj.open(*intermediateFilePathPntr);
			}

			// catch exception handled in exception class here
			catch (const runtime_error& exception) {
				cout << "\nException occurred in \"ReduceProcess::Main\".\n";
				cout << exception.what();
				throw exception;
			}

			// catch any exception here
			catch (...) {
				cout << "\nException occurred in \"ReduceProcess::Main\".\n";
				throw;
			}

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
						Reduce(alteredOutputFilePath, entryString);
					}

					// update the offset into the line for the next search.
					offset = closedPos + 1;

					// Find the position of the next open parenthesis. 
					openPos = line.find(openParenthesis, offset);
				}
			}

			// Free the handle to the ReduceLibrary DLL.
			FreeLibrary(reduceDllHandle);
		}

		// catch any exception here
		catch (...)
		{
			BOOST_LOG_TRIVIAL(fatal) << "Error in Workflow class inputIsFile function. Program will shutdown";
			throw;
		}
	}
	else {
		BOOST_LOG_TRIVIAL(fatal) << "Error loading ReduceLibrary DLL in Workflow::startProgram method. Program will shutdown";
		throw;
	}
}//End of Program
