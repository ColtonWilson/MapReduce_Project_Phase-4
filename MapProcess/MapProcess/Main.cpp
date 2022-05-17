/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 3
5/15/2022

Main.cpp

Below is Main.cpp file.
This file has the main() function for the MapProcess.exe file.

It takes 3 command line arguments.
- InputFilePath
- Process Number

The process number ranges from 1 to the defined max number of processes.

*/

#define  _WIN32_WINNT   0x0601

//Directives
#include <Windows.h>

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>

#include <boost/timer/timer.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "FileManagement.h"


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
typedef void (*funcMap)(string, string);

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

	std::this_thread::sleep_for(std::chrono::seconds(1));

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


	//Initiate variables to hold the names of the directory locations
	string inputFileName{ "Unknown" };
	string intermediateFileName{ "Unknown" };
	string outputFileName{ "Unknown" };


	//<-----------------Part 1------------------------------------------>
	
	// Mapping
	// convert the data to a string
	string inputFile = argv[0];
	//convert data back
	for (int i = 0; i < inputFile.size(); i++)
	{
		if (inputFile[i] == '\n')
		{
			inputFile[i] = ' ';
		}
		else
		{
			inputFile[i] = inputFile[i];
		}

	}
	
	// store the process number.
	string processNumber = argv[2];

	
	// store the RMAX number.
	string rMaxNumber = argv[3];
	
	// convert the intermediate file path to a string
	string intermediateFilePath = argv[1];

	//convert file path back to normal
	for (int i = 0; i < intermediateFilePath.size(); i++)
	{
		if (intermediateFilePath[i] == '\n')
		{
			intermediateFilePath[i] = ' ';
		}
		else
		{
			intermediateFilePath[i] = intermediateFilePath[i];
		}

	}
	
	// retrieve the size of the intermediate 
	int intermediateFilePathSize = intermediateFilePath.size();
	
	// alter the intermediate file path.
	string alteredIntermediateFilePath = intermediateFilePath.substr(0, intermediateFilePathSize - 4) + processNumber + intermediateFilePath.substr(intermediateFilePathSize - 4);

	
	// assign pointers to the files.
	string* inputFilePntr = &inputFile;
	string* intermediateFilePathPntr = &alteredIntermediateFilePath;

	HINSTANCE mapLibraryHandle;
	funcMap Map;
	const wchar_t* libName = L"MapLibrary";

	mapLibraryHandle = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL

	// perform the following if the mapLibraryHandle is not NULL
	if (mapLibraryHandle != NULL) {

		Map = (funcMap)GetProcAddress(mapLibraryHandle, "Map");

		//Create an input and output stream class
		ifstream inputFileStream;
		ofstream intermediateFileStream;

		//Create an object of the FileManagement class
		FileManagement FileStreamSystem;

		//Open the input file and connect to the in stream. Then double check to make sure file is not corrupt
		FileStreamSystem.openFileInstream(inputFileStream, inputFile);
		FileStreamSystem.fileCorrupt(inputFileStream);

		//Initiate a variable to hold raw data given by the input file
		string data{ "Unknown" };
		int pNum = std::stoi(processNumber);
		int rMax = std::stoi(rMaxNumber);
		int R{ pNum };

		
		//Keep collecting data until the end of file and get a return of "1"
		while (data != "1")
		{
			//Get a line of data from the input file
			FileStreamSystem.readFromFile(inputFileStream, data, R);

			if (data != "1")
			{
				Map(alteredIntermediateFilePath, data);
			}

			R = (rMax);

		}

		// Free the handle to the MapLibrary DLL.
		FreeLibrary(mapLibraryHandle);
	}
}//End of Program