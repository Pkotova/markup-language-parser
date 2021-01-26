#include "ResultRepository.h"
#include<regex>
#include<iostream>
#include<fstream>

/*@ set result*/
void ResultRepository::setResult(std::string result)
{
	this->result = result;
}

const std::string& ResultRepository::getResult()
{
	return this->result;
}

/*	@ The application works only with txt files
*	if the given filename is correct txt file
	- sets the _file to filename
*/
void ResultRepository::setFilename(std::string filename)
{
	// check if the input file correct text file
	std::regex rx(".*.txt$");
	bool found = std::regex_match(filename, rx);
	this->filename = filename;
	if (found == false)
	{
		this->errors += "Error 150: Unsupported file! \n";
	}
	else
	{
		this->filename = filename;
	}
}

/*	@ returns filename*/
const std::string& ResultRepository::getFilename() const
{
	return this->filename;
}

/*	@ checks for any collected errors*/
bool ResultRepository::check()
{
	return (errors == "") ? true : false;
}

/* @ create file if doesnt exist*/
std::ofstream& ResultRepository::createFile(std::string filename)
{
	std::ofstream file{ filename };
	std::cout << "\033[32m" << "File was successfully created!" << "\033[0m" << std::endl;
	return file;
}

/* @ save result*/
void ResultRepository::save()
{
	std::cout << "\033[33m"<< "save in file: ""\033[0m";
	std::string fileName;
	std::cin >> fileName;
	setFilename(fileName);
	std::ofstream output_file(this->getFilename());
	std::string script;
	std::string text_read;


	if (output_file.fail()) //check for file open failure
	{
		std::cout << "Error 130: File does not exist \n Do you want to create it? (Y/N) \n";
		char answer;
		std::cin >> answer;
		if (answer == 'Y')
		{
			createFile(filename);
		}
		else
		{
			this->errors += "Error 130: File does not exist \n";
		}
	}
	if (output_file.is_open())
	{
		output_file << this->result;
		output_file.close();
		std::cout << "\033[32m" << "Result was successfully saved!" << "\033[0m" << std::endl;
	}
	else
	{
		std::cout << "\033[31m" << "File filed!" << "\033[0m" << std::endl;
	}
	std::cout << errors;
}