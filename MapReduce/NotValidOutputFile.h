/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

NotValidOutputFile.h

Below is the "NotValidOutputFile" class.
This is an exception handler if user inputs a bad file



*/
// Header Guard
#ifndef NOTVALIDOUTPUTFILE_H
#define NOTVALIDOUTPUTFILE_H

//Directives
#include <stdexcept> //stdexcept header contains runtime_error


class NotValidOutputFile : public std::runtime_error
{
public:

	//constructor specifies default error message
	NotValidOutputFile()
		: std::runtime_error{ "Not a valid output file directory." } {}


};

#endif
