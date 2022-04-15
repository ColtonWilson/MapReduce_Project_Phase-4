/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

NotValidInputFile.h

Below is the "NotValidInputFile" class.
This is an exception handler if user inputs a bad file



*/
// Header Guard
#ifndef NOTVALIDINPUTFILE_H
#define NOTVALIDINPUTFILE_H

//Directives
#include <stdexcept> //stdexcept header contains runtime_error


class NotValidInputFile : public std::runtime_error
{
public:

	//constructor specifies default error message
	NotValidInputFile()
		: std::runtime_error{ "Not a valid input file directory." } {}


};

#endif
