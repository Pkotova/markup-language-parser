#pragma once
#include<string>
/*
*	@brief explanation
* The following class controls the ouput filesystem. It manage to save the given result
* from the Parser. It has the following data fields
* result - received result from Parser
* filename - file for the result to be saved in 
* errors - collect errors
*/
class ResultRepository
{
private:
	std::string result;
	std::string filename;
	std::string errors;
public:
	void setResult(std::string result);
	const std::string& getResult();
	void setFilename(std::string filename);
	const std::string& getFilename()const;
	bool check();
	std::ofstream& createFile(std::string filename);
	void save();
};