/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
5/15/2022

Workflow.cpp

---Note: This file does include the BOOST library in order to compile.

Below is Workflow.cpp, which is called by the  main() in Executive.cpp.
The constructor takes three string directory names and saves the strings into private data members.
The constructor will then tie together all the header files with supporting logic.
The public data member functions are setters and getters for each data member.

*/

//Constant R, how many buckets are being used
const int RMAX{ 5 };

//Directives
#include "Workflow.h"
#include "FileManagement.h"
#include "NotValidFile.h"

using std::to_string;

//default constructor
Workflow::Workflow() {}
//WorkFlow constructor with three parameters
Workflow::Workflow(string inputFile, string intermediateFile, string outputFile)
{
	checkFilesValid(inputFile, intermediateFile, outputFile);

	startProgram(getInputFileLocation(), getIntermediateFileLocation(), getOutputFileLocation());
}

//**********Destructor*********
Workflow::~Workflow() {}

//**********Member Function**********


//Path to run if input is a File
void Workflow::startProgram(string inputFile, string intermediateFile, string outputFile)
{
	HINSTANCE mapLibraryHandle;
	funcMap Map;
	const wchar_t* libName = L"MapLibrary";

	mapLibraryHandle = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL

	// perform the following if the mapLibraryHandle is not NULL
	if (mapLibraryHandle != NULL) {

		Map = (funcMap)GetProcAddress(mapLibraryHandle, "Map");

		// Writing from input file to intermediate file
		//Create an input and output stream class
		ifstream inputFileStream;
		ofstream intermediateFileStream;

		//Create an object of the FileManagement class
		FileManagement FileStreamSystem;

		if (boost::filesystem::is_directory(inputFile))
		{
			//<-----------------Part 1 for directory given------------------------------------------>
			//Clear the contents of the intermediate file which will hold the output of the Map class. This will also close the stream
			for (int i = 0; i < RMAX; i++) {
				string tempIntermediateFilePath = updateString(intermediateFile, to_string(i + 1));
				FileStreamSystem.clearFile(intermediateFileStream, tempIntermediateFilePath);
			}

			// insert all of the files in the directory inside a vector of strings.
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
				int R = 0;
				while (data != "1")
				{
					//Get a line of data from the input file
					FileStreamSystem.readFromFile(inputFileStream, data);
					//Check if data was not the end of file
					if (data != "1")
					{
						if (Map != NULL)
						{
							if (R == 0)
							{
								string newIntermediateFileName = updateString(intermediateFile, to_string(R + 1));
								Map(newIntermediateFileName, data);
								R++;
							}
							else
							{
								string newIntermediateFileName = updateString(intermediateFile, to_string(R + 1));
								Map(newIntermediateFileName, data);
								R++;

							}
							R = R % RMAX;

						}
						else
							std::cout << "Did not load Map correctly." << std::endl;
					}
				}
				FileStreamSystem.closeInputFile(inputFileStream);

			}
		}
		else
		{
			//<-----------------Part 1 for file given------------------------------------------>
			//Open the input file and connect to the in stream. Then double check to make sure file is not corrupt
			FileStreamSystem.openFileInstream(inputFileStream, inputFile);
			FileStreamSystem.fileCorrupt(inputFileStream);
			
			//Clear the contents of the intermediate file which will hold the output of the Map class. This will also close the stream
			for (int i = 0; i < RMAX; i++) {
				string tempIntermediateFilePath = updateString(intermediateFile, to_string(i + 1));
				FileStreamSystem.clearFile(intermediateFileStream, tempIntermediateFilePath);
			}

			//Initiate a variable to hold raw data given by the input file
			string data{ "Unknown" };
			//Keep collecting data until the end of file and get a return of "1"
			int R{ 0 };
			while (data != "1")
			{
				//Get a line of data from the input file
				FileStreamSystem.readFromFile(inputFileStream, data);
				//Check if data was not the end of file
				if (data != "1")
				{
					if (Map != NULL)
					{
						if (R == 0)
						{
							string newIntermediateFileName = updateString(intermediateFile, to_string(R + 1));
							Map(newIntermediateFileName, data);
							R = R + 1;
						}
						else
						{
							string newIntermediateFileName = updateString(intermediateFile, to_string(R + 1));
							Map(newIntermediateFileName, data);
							R = R + 1;

						}
						R = R % RMAX;

					}
					else
						std::cout << "Did not load Map correctly." << std::endl;
				}
			}

			FileStreamSystem.closeInputFile(inputFileStream);

		}

		// Free the handle to the MapLibrary DLL.
		FreeLibrary(mapLibraryHandle);


		//<-----------------Part 2------------------------------------------>

		// create an array of process handlers.
		HANDLE* processesHandle;

		// allocate memory for the process handle array.
		processesHandle = (HANDLE*)malloc(RMAX * sizeof(HANDLE));

		// declare the startup info and process information objects.
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		// create the processes
		for (int i = 0; i < RMAX; i++) {

			// convert the process number to a string
			string processNumber = std::to_string(i + 1);

			// create an array to hold an integer in string form.
			wchar_t wCharArray[255];

			// local variable for iterating through character array.
			int index{ 0 };

			// populate the character array with the intermediate file path
			for (int i = 0; i < intermediateFile.size(); i++) {
				wCharArray[index] = intermediateFile[i];
				index = index + 1;
			}

			// insert a space
			wCharArray[index] = ' ';
			index = index + 1;

			// populate the character array with the output file path
			for (int i = 0; i < outputFile.size(); i++) {
				wCharArray[index] = outputFile[i];
				index = index + 1;
			}

			// insert a space
			wCharArray[index] = ' ';
			index = index + 1;


			// insert the process number into the wCharArray
			for (int i = 0; i < processNumber.size(); i++) {
				wCharArray[index] = processNumber[i];
				index = index + 1;
			}

			// end the string with the null character
			wCharArray[index] = 0;

			// convert the process number in string form to LPWSTR
			LPWSTR allArgsLpwstr = wCharArray;

			// zero the memory of the startup info object.
			ZeroMemory(&si, sizeof(si));

			// assign the size of the structure (cb) to the size of the object.
			si.cb = sizeof(si);

			// zero the memory of the process information object.
			ZeroMemory(&pi, sizeof(pi));

			// assign the processes handle array with this handle
			processesHandle[i] = pi.hProcess;

			// Start the child process. 
			if (!CreateProcess(
				L"C:\\Users\\antho\\OneDrive\\Documents\\Projects\\ReduceProcess\\x64\\Debug\\ReduceProcess.exe",   // No module name (use command line)
				allArgsLpwstr,        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				FALSE,          // Set handle inheritance to FALSE
				0,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi)           // Pointer to PROCESS_INFORMATION structure
				)
			{
				printf("CreateProcess failed (%d).\n", GetLastError());
				//return -1;
			}
		}

		// Wait until all child processes exit.
		WaitForMultipleObjects(RMAX, processesHandle, TRUE, INFINITE);

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		// create output file stream object
		ofstream ofstreamObj;

		//Check if there was a directory path
		if (getOutputFileDirectoryLocation() == "")
		{
			// Print the SUCCESS.txt file to output directory.
			FileStreamSystem.openFileOutstream(ofstreamObj, "SUCCESS.txt");

		}
		else
		{
			// Print the SUCCESS.txt file to output directory.
			FileStreamSystem.openFileOutstream(ofstreamObj, getOutputFileDirectoryLocation() + "\\SUCCESS.txt");
		}

		// Close the SUCCESS.txt file.
		FileStreamSystem.closeOutputFile(ofstreamObj);

		// 
		cout << "\nSuccess. Program will now terminate." << endl;

	}
	else {
		BOOST_LOG_TRIVIAL(fatal) << "Error loading MapLibrary DLL in Workflow::startProgram method. Program will shutdown.";
		throw;
	}
}

// Get File Name from a Path with or without extension
void Workflow::separateOutputPath(const string userInputFile, const string& fileType)
{
	try {

		// Create a Path object from File Path
		boost::filesystem::path pathObj(userInputFile);

		// set the path of the user submitted file
		boost::filesystem::path p(userInputFile);

		//get the parent path
		boost::filesystem::path dir = p.parent_path();

		if (fileType == "output")
		{
			//set data member as a string to remember the path
			setOutputFileDirectoryLocation(dir.string());

		}
		else
		{
			//set data member as a string to remember the path
			setIntermediateFileDirectoryLocation(dir.string());
		}



	}
	// catch any exception here
	catch (...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Error in Workflow class separateOutputPath function. Program will shutdown";
		throw;

	}


}

void Workflow::checkFilesValid(string& inputFile, string& intermediateFile, string& outputFile)
{
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
		catch (const NotValidFile& notValidFileException) {
			cout << "\nException occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validInputFile == false)
		{
			cout << "\nPlease enter a valid input file directory.\n"
				<< "Input File Directory: ";
			std::getline(cin, inputFile);
		}

	}

	//Get path to intermediate output directory
	//separateOutputPath(intermediateFile, "intermediate");
	while (validIntermediateFile == false)
	{
		//try block to attempt to the input file directory
		try {

			setIntermediateFileLocation(intermediateFile);
		}
		//If not valid then throw exception
		catch (const NotValidFile& notValidFileException) {
			cout << "\nException occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validIntermediateFile == false)
		{
			cout << "\nPlease enter a valid temporary intermediate file directory.\n"
				<< "Intermediate File Directory: ";
			std::getline(cin, intermediateFile);
		}

	}

	//Get path to final output directory
	//separateOutputPath(outputFile, "output");
	while (validOutputFile == false)
	{
		//try block to attempt to the input file directory
		try {
			setOutputFileLocation(outputFile);
		}
		//If not valid then throw exception
		catch (const NotValidFile& notValidFileException) {
			cout << "\nException occurred: "
				<< notValidFileException.what() << endl;
		}
		//Ask user for another input file directory
		if (validOutputFile == false)
		{
			cout << "\nPlease enter a valid final output file directory.\n"
				<< "Output File Directory: ";
			std::getline(cin, outputFile);

		}

	}

}

//Check if the input file is valid
bool Workflow::checkIfFIle(const string& userInputFile)
{
	// Create a Path object from given path string
	boost::filesystem::path pathObj(userInputFile);
	// Check if path exists and is of a regular file
	if (!boost::filesystem::exists(pathObj) && (!boost::filesystem::is_regular_file(pathObj) || !boost::filesystem::is_directory(pathObj)))
	{
		BOOST_LOG_TRIVIAL(warning) << "Input Directory does not exist.";
		return true;
	}


	return false;
}

//Check if the output file is valid
bool Workflow::checkOfFIle(const string& userInputFile, const string& fileType)
{
	// Create a Path object from given path string
	boost::filesystem::path pathObj(userInputFile);
	// Check if path exists
	if (boost::filesystem::exists(pathObj))
	{
		return false;
	}
	else
	{
		//Check to see if the last file is a .txt 
		if (userInputFile.substr(userInputFile.find_last_of(".") + 1) == "txt")
		{
			//Separate if it does from file
			separateOutputPath(userInputFile, fileType);

			if (fileType == "output")
			{
				if (!(getOutputFileDirectoryLocation() == ""))
				{
					boost::filesystem::create_directories(getOutputFileDirectoryLocation());
				}

			}
			else
			{
				if (!(getIntermediateFileDirectoryLocation() == ""))
				{
					cout << getIntermediateFileDirectoryLocation();
					boost::filesystem::create_directories(getIntermediateFileDirectoryLocation());
				}

			}



			return false;
		}
		else
		{
			BOOST_LOG_TRIVIAL(warning) << "Program must write to a '.txt' file location.";
			return true;
		}
	}
}

string Workflow::updateString(string origional, string toAdd)
{

	int strLength = origional.size();
	return origional.substr(0, strLength - 4) + toAdd + origional.substr(strLength - 4);

}
//**********Setters**********
// Set the input file location.
void Workflow::setInputFileLocation(const string& userInputFile)
{

	//Verify input call to checkIfFile()
	if (checkIfFIle(userInputFile))
	{
		//If return true then throw exception
		throw NotValidFile{}; //terminate function

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
void Workflow::setIntermediateFileLocation(const string& userIntermediateFile)
{
	string intermediateFileToCheck = userIntermediateFile;


	//Verify input call to checkIfFile()
	if (checkOfFIle(intermediateFileToCheck, "intermediate"))
	{
		//If return true then throw exception
		throw NotValidFile{}; //terminate function

	}
	//If false then insert into inputFileLocation 
	else
	{
		// Create a Path object from given path string
		boost::filesystem::path pathObj(intermediateFileToCheck);
		//Check if using a file and not a directory
		if (intermediateFileToCheck.substr(intermediateFileToCheck.find_last_of(".") + 1) != "txt")
		{

			intermediateFileToCheck = intermediateFileToCheck + "\\Intermediate.txt";
			BOOST_LOG_TRIVIAL(warning) << "Directory must include a '.txt' file to write to at the end. Will write a Intermediate.txt in same directory. ";

		}

		//Separate if it does from file
		separateOutputPath(intermediateFileToCheck, "intermediate");

		//intermediateFileLocation = userIntermediateFile;
		intermediateFileLocation = intermediateFileToCheck;
		//update validInputFile
		validIntermediateFile = true;

	}

}

// Set the output file location.
void Workflow::setOutputFileLocation(const string& userOutputFile)
{
	string outputFileToCheck = userOutputFile;


	//Verify input call to checkIfFile()
	if (checkOfFIle(outputFileToCheck, "output"))
	{

		//If return true then throw exception
		throw NotValidFile{}; //terminate function

	}
	//If false then insert into inputFileLocation 
	else
	{

		// Create a Path object from given path string
		boost::filesystem::path pathObj(outputFileToCheck);
		//Check if using a file and not a directory
		if (outputFileToCheck.substr(outputFileToCheck.find_last_of(".") + 1) != "txt")
		{
			outputFileToCheck = outputFileToCheck + "\\Output.txt";
			BOOST_LOG_TRIVIAL(warning) << "Directory must include a '.txt' file to write to at the end. Will write a Output.txt in same directory. ";


		}
		//Separate if it does from file
		separateOutputPath(outputFileToCheck, "output");
		outputFileLocation = outputFileToCheck;
		//update validInputFile
		validOutputFile = true;

	}


}

void Workflow::setIntermediateFileDirectoryLocation(const string& userOutputFile) { intermediateFileDirectoryLocation = userOutputFile; }

// Set the output file directory location.
void Workflow::setOutputFileDirectoryLocation(const string& userOutputFile) { outputFileDirectoryLocation = userOutputFile; }


//**********Getters**********

// Get the input file location.
const string Workflow::getInputFileLocation(void) { return inputFileLocation; }

// Get the intermediate file location.
const string Workflow::getIntermediateFileLocation(void) { return intermediateFileLocation; }

// Get the output file location.
const string Workflow::getOutputFileLocation(void) { return outputFileLocation; }

const string Workflow::getIntermediateFileDirectoryLocation(void) { return intermediateFileDirectoryLocation; }

// Get the output file directory location.
const string Workflow::getOutputFileDirectoryLocation(void) { return outputFileDirectoryLocation; }

// Get the bool if input file is valid. 
const bool  Workflow::getValidInputFile(void) { return validInputFile; }

// Get the bool if intermediate file is valid. 
const bool  Workflow::getValidIntermediateFile(void) { return validIntermediateFile; }

// Get the bool if output file is valid. 
const bool  Workflow::getValidOutputFile(void) { return validOutputFile; }
