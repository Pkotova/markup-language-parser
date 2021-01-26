#include "IMLRepository.h"
#include <regex>
/*@ The application works only with txt files
*	if the given filename is correct txt file
	- sets the _file to filename
*/
void IMLRepository::setFile(std::string _file)
{
	// check if the input file correct text file
	std::regex rx(".*.txt$");
	bool found = std::regex_match(_file, rx);
	this->file = _file;
	if (found == false)
	{
		this->errors += "Error 150: Unsupported file! \n";
	}
	else
	{
		this->file = _file;
	}
}

/*@ returns filename*/
std::string& IMLRepository::getFile()
{
	return this->file;
}

/*@ Read the given file and returns the script on one row 
*	- example: opened file zad2.txt
*				-----------------
			*	<SRT-ORD "ASC">81 3
				<MAP-INC "1">4 12 55
				</MAP-INC>22
				</SRT-ORD>
				---------------
		output:<SRT-ORD "ASC">81 3<MAP-INC "1">4 12 55</MAP-INC>22</SRT-ORD>
*/
std::string IMLRepository::getScript()
{
	std::cout << "\033[33m" << "open file: ""\033[0m";
	std::string fileName;
	std::cin >> fileName;
	setFile(fileName);
	std::ifstream input_file(this->getFile());
	std::string script;
	std::string text_read;


	if (input_file.fail()) //check for file open failure
	{
		this->errors += "Error 130: File does not exist \n";
		//exit(130);
	}

	else if (input_file.peek() == std::ifstream::traits_type::eof())
	{

		this->errors += "Error 140: File is empty \n";
		//exit(140);
	}
	else
	{
		while (std::getline(input_file, text_read))
		{
			const std::string::size_type position = text_read.find('\r');
			if (position != std::string::npos)
			{
				text_read.erase(position);
			}
			script += text_read;
		}
	}

	if (check())
		return script;
	else
	{
		system("Color 06");
		std::cout << this->errors;
		exit(123);
		return " ";

	}

}

bool IMLRepository::check()
{
	return (errors != "") ? false : true;
}
