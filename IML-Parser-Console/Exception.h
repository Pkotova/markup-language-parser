#pragma once
#include <iostream>
#include <string>
/*
* @brief explanation
* Class Exception give the chance to rule all exceptions the program prints
* it contains data field such as 
* code - each exception has its own code
* message - each exception has a specific message, which gives the user brief knowledge where his mistake is
* --
* the methods included are mutators, setters&getters, which gives straight access to data fields
*/
class Exception
{
private:
	int code;
	std::string message;
public:

	void setCode(int _code);
	void setMessage(std::string& _message);
	int getCode();
	std::string& getMessage();
};