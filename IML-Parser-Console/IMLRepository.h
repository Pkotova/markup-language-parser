#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include"ExceptionRepository.h"
/*
* @brief explanation 
* The following class controls the input filesystem. It reads the file given by the user, 
* check for exceptions and gives the script to ExceptionRepository for code verification
* it has the ensuign data fields
*  script - the read script from the given by the user file
*  file - filename of file to be open
*  errors - collected errors and exception in the context of correct txt file
*  The class contains mutators methods, which gives accsess to the data fields
*/
class IMLRepository
{
private:
	std::string script;
	std::string file;
	std::string errors; // caught errors

public:
	void setFile(std::string _file);
	std::string& getFile();
	std::string getScript();
	bool check();
};