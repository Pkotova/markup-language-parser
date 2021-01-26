#include "ExceptionRepository.h"
#include <fstream>
IMLRepository il;
/*	@Default constructor, used when the user wants to experience the application
*	with the filesystem
*/
ExceptionRepository::ExceptionRepository()
{
	this->script = il.getScript();
	this->errors = "";
}

/*	@Parametric contructor, used when the user wants to experience the application
*	like an interpretator, without setup filesystem
*/
ExceptionRepository::ExceptionRepository(std::string script)
{
	this->script = script;
	this->errors = "";
}

/*	@Reads the file Exception.txt (you can find it in the project folders)
*			@@[the text file contains all possible mistakes which can trigger the app.]
*	The methods returns LinkedList [you can find the definition in LinkedList.h] full of
*	exceptions read from the file. 
*	@Brief explanation + in the body of the method: first element of the linked list will be an exception "100: Missing openning tag"
*	the exception is with code "100", and message ":Missing opening tag"
*/
LinkedList<Exception>* ExceptionRepository::ExceptionList()
{
	std::fstream file;
	LinkedList<Exception>* result = new LinkedList<Exception>(); // create object ot type LinkedList full of Exceptions
	std::string msg = "";
	int code = 0;
	Exception* temp = nullptr;
	char buffer[200];

	file.open("Exceptions.txt");// manage to try to open the file (more explanation about the Exception.txt file, you can find 
								// above the definition of this method
	if (!file)	//if failing open the project
	{
		std::cout << "Exception: file could not be opened" << std::endl;
	}
	while (!file.eof())	// while we reach the end of the file
	{
		//each line is a new Exception
		temp = new Exception();
		file.getline(buffer, 200);
		temp->setCode(atoi(buffer));
		file.getline(buffer, 200);
		msg = buffer;
		temp->setMessage(msg);
		// fill the linked list with the read exception
		result->addEnd(*temp);
	}
	file.close(); // close the file
	return result; // returns the result
}

/*	@Returns any exception by its code, 
*	std::string ExceptionRepository::returnByCode(int _code), where 
*	_code is given code, 
*	@example: returnByCode(100), will returns "100: Missing openning tag"
*	@Brief explanation in the body of the method
*/
std::string ExceptionRepository::returnByCode(int _code)
{
	std::string exception; // each exception might be seen as a simple string, so we 
						  // declarate a temp string 
	for (size_t i = 0; i < ExceptionList()->Size(); ++i) // we go throught ExceptionList we created in the ExceptionList()
	{
		if (ExceptionList()->getElementAt(i).getCode() == _code) // when we find a coincidence
		{
			exception += std::to_string(ExceptionList()->getElementAt(i).getCode()); // initialize the temp exception with the values of the found object
			exception += ExceptionList()->getElementAt(i).getMessage();
		}
	}
	return exception + '\n'; // '\n' will help us to count the exceptions
}

/*	@Returns given script from IMLRepository
*/
std::string ExceptionRepository::getScript()
{
	return this->script;
}

/*	@Each tag has opening and closing symbols [<,>] 
*	The following methods count the < and >
*/
int ExceptionRepository::countOpenSymbols()
{
	int counter = 0;
	int i = 0;
	while (this->getScript()[i] != '\0')
	{
		if (this->getScript()[i] == '<')
		{
			counter++;
		}
		i++;
	}
	return counter;
}

int ExceptionRepository::countCloseSymbols()
{
	int counter = 0;
	int i = 0;

	while (this->getScript()[i] != '\0')
	{
		if (this->getScript()[i] == '>')
		{
			counter++;
		}
		i++;
	}
	return counter;
}

bool ExceptionRepository::missingSymbol()
// is missing = yes if is missing , = false if is not missing
{
	return (countCloseSymbols() == countOpenSymbols()) ? false : true;
}

/*	@Following methods helps finding if there is any syntax mistakes
*	having in mind dashes, quotes and spaces, if any of this is missing
*	or is too much an exception will be saved in errors field
*	
*	for the verifications are used regular expressions, which 
*	gives us more insurance when it comes to clear syntax
* 
*/
bool ExceptionRepository::isValidSRTTag(std::string tag)
{
	std::regex rev("(SRT-REV)");	
	std::regex asc("(SRT-ORD)(\")(ASC)(\")");
	std::regex dsc("(SRT-ORD)(\")(DSC)(\")");
	std::regex dst("(SRT-DST)");
	std::regex slc("(SRT-SLC)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	return  (regex_match(tag, asc) ||
		regex_match(tag, dsc) ||
		regex_match(tag, slc) ||
		regex_match(tag, dst) ||
		regex_match(tag, rev))
		? true : false;
}

bool ExceptionRepository::isValidMAPTag(std::string tag)
{
	std::regex inc("(MAP-INC)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	std::regex mlt("(MAP-MLT)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	return (std::regex_match(tag, inc) || std::regex_match(tag, mlt)) ? true : false;
}

bool ExceptionRepository::isValidAGGTag(std::string tag)
{
	std::regex sum("(AGG-SUM)");
	std::regex pro("(AGG-PRO)");
	std::regex avg("(AGG-AVG)");
	std::regex fst("(AGG-FST)");
	std::regex lst("(AGG-LST)");
	return (std::regex_match(tag, sum)
		|| std::regex_match(tag, pro)
		|| std::regex_match(tag, avg)
		|| std::regex_match(tag, fst)
		|| std::regex_match(tag, lst)) ? true : false;
}

/*	@Having in mind that we receive the script as string we need to know if we have 
* correct numeric data so the methods:
*	@ExceptionRepository::isDigit(std::string data) // helps to check if one single char is digit 
*			example: isDigit('3') => true, but isDigit('a') => false;

*/
bool ExceptionRepository::isDigit(char symbol)
{
	return (symbol >= '0' && symbol <= '9');
}

/*	@ExceptionRepository::isDigit(std::string data) // helps to check if one single char is digit 
* example: isDigit('3') = > true, but isDigit('a') = > false;*/
bool ExceptionRepository::isDigit(std::string data)
{
	auto result = double();
	auto i = std::istringstream(data);

	i >> result;

	return !i.fail() && i.eof();
}

/*@Checks if all parts of the reciev script is valid data whether a verificated opening, closing tag or number*/
bool ExceptionRepository::isSupportedTag(std::string tag)
{
	if (tag == "MAP-INC" || tag == "MAP-MLT" ||
		tag == "AGG-SUM" || tag == "AGG-PRO" ||
		tag == "AGG-AVG" || tag == "AGG-FST" ||
		tag == "AGG-LST" || tag == "SRT-REV" ||
		tag == "SRT-ORD" || tag == "SRT-SLC" ||
		tag == "SRT-DST" || tag == "/MAP-INC" ||
		tag == "/MAP-MLT" || tag == "/AGG-SUM" ||
		tag == "/AGG-PRO" || tag == "/AGG-AVG" ||
		tag == "/AGG-FST" || tag == "/AGG-LST" ||
		tag == "/SRT-REV" || tag == "/SRT-ORD" ||
		tag == "/SRT-SLC" || tag == "/SRT-DST" ||
		tag == "ASC" || tag == "DSC" ||
		isDigit(tag))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*	@By using isSupportedTag(..) method, the method below checks if all pieces of the recieved script
are syntactically clear and verified*/
bool ExceptionRepository::isSyntaxClear() // if all of the code is supported
{
	bool result = true;
	LinkedList<std::string> info = fullSplit();
	size_t size = info.Size();

	for (size_t i = 0; i < size; i++)
	{
		if (isSupportedTag(info.getElementAt(i)) == false) //checking all elements
		{
			std::cout << info.getElementAt(i) << ": ";
			errors += returnByCode(103);		//Exception [103: Unknown tag used]
			return false;
		}
	}
	return true;
}

/*	@each tag information has opening <TAG-NAME> and closing </TAG-NAME>
*	the following verify the presence оf enough opening and closing tags
*/
bool ExceptionRepository::isMissingTag() // if is missing opening or closing tag returns true, 
// if it has all tags it returns false
{
	LinkedList<std::string> info = fullSplit();
	int countTags = 0;
	int countSlash = 0;
	int size = info.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (!isDigit(info.getElementAt(i)) &&
			info.getElementAt(i) != "ASC" &&
			info.getElementAt(i) != "DSC")
		{
			countTags++;
		}
		if (info.getElementAt(i)[0] == '/') // count '/' symbols, which declarate closing tag
		{
			countSlash++;
		}
	}
	if (countTags / 2 > countSlash)	// if opening tags are more than closing => 
	{
		errors += returnByCode(102); // Exception [102: Missing closing tag]
	}
	else if (countTags / 2 < countSlash) // if closing tags are more than opening =>
	{
		errors += returnByCode(100);// Exception [100: Missing opening tag]
	}
	else
	{
		return false;
	}
	return true; //otherwise the script is clear;
}

/*	@check if all the given data for calculation is numeric
*/
bool ExceptionRepository::numericParameters()
{
	LinkedList<std::string> parameters = getAllData();

	int size = parameters.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (!isDigit(parameters.getElementAt(i)))
		{
			std::cout << parameters.getElementAt(i) << std::endl;
			errors += returnByCode(122);	// Exception [122:Non-numeric parameters]
			return false;
		}

	}
	return true;
}

/*	@Several of the available tags has attributes, which means their syntax is 
*	<TAG-NAME "ATTRIBUTE">, we need to verify if the ATTRIBUTE is missing or it is unavailable type
*/
bool ExceptionRepository::isMissingAttribute() // If is missing return true
{
	LinkedList<std::string> info = halfSplit(); // example for line MAP-INC"-1"
	for (size_t i = 0; i < info.Size(); i++)
	{
		if ((isValidAGGTag(info.getElementAt(i)) == false
			&& isValidMAPTag(info.getElementAt(i)) == false
			&& isValidSRTTag(info.getElementAt(i)) == false)
			&& (isDigit(info.getElementAt(i)) == false &&
				info.getElementAt(i)[0] != '/'))
		{
			std::cout << info.getElementAt(i) << " ";
			errors += returnByCode(120);// Exception [120:missing attribute]
			return true;
		}
	}

	return false;
}

/*	@Count collected exceptions, this is helper method
*/
int ExceptionRepository::countExceptions()
{
	int counter = 0;
	for (size_t i = 0; i < errors.size(); i++)
	{
		if (errors[i] == '\n')
		{
			counter++;
		}
	}
	return counter;
}

/*	@Run all verification methods and if we collected any mistakes we inform the user*/
std::string ExceptionRepository::cleanScript()
{
	std::cout << "****************\n";
	isSyntaxClear();
	isMissingTag();
	numericParameters();
	isMissingAttribute();
	if (errors != "")
	{
		std::cout << this->errors;
		system("Color 06");
		std::cout << "\033[31m" << "Build: 0 succeeded " << countExceptions() << " failed" << "\033[0m" << std::endl;
	}
	else
	{
		std::cout << "\033[32m" << "Build: 1 succeeded, 0 failed" << "\033[0m" << std::endl;
		return this->script;
	}
	std::cout << "****************\n\n";
	exit(120);
}

/*	@Collects all data/content*/
LinkedList<std::string>& ExceptionRepository::getAllData()
{
	LinkedList<std::string>* data = new LinkedList<std::string>();
	LinkedList<std::string> info = halfSplit();
	//info.print();

	int size = info.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (isDigit(info.getElementAt(i)[0]))
		{
			data->addEnd(info.getElementAt(i));
		}
	}
	return *data;
}

/*	@Removes all spaces*/
std::string ExceptionRepository::clearSpaces()
{
	std::string removeSpaces = getScript();
	removeSpaces.erase(remove(removeSpaces.begin(), removeSpaces.end(), ' '), removeSpaces.end());
	return removeSpaces;
}
/*	@ Fully split the script by [^\\s<>\":;!?]+ */
LinkedList<std::string>& ExceptionRepository::fullSplit()
{
	LinkedList<std::string>* tags = new LinkedList<std::string>();
	std::string script = getScript();
	int i = 0;
	if (!missingSymbol()) // if there is no missing </> symbol
	{
		std::regex words_regex("[^\\s<>\":;!?]+");
		auto words_begin = std::sregex_iterator(script.begin(), script.end(), words_regex);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator i = words_begin; i != words_end; ++i)
			tags->addEnd((*i).str());// << '\n';
		return *tags;
	}
	else
	{
		if (countCloseSymbols() > countOpenSymbols())
		{
			errors += returnByCode(101);
			system("Color 06");
			std::cout << returnByCode(101);
			std::cout << "\033[31m" << "Build: 0 succeeded " << countExceptions() << " failed" << "\033[0m" << std::endl;
			//exit(101);
		}
		else
		{
			errors += returnByCode(104);
			system("Color 06");
			std::cout << returnByCode(104);
			std::cout << "\033[31m" << "Build: 0 succeeded " << countExceptions() << " failed" << "\033[0m" << std::endl;
			//exit(104);
		}
	}
	if (tags->isEmpty())
	{
		exit(120);
	}
}

/*	@ Halfly split the script by [[^\<>:;!?]+ */
LinkedList<std::string>& ExceptionRepository::halfSplit()
{
	LinkedList<std::string>* tags = new LinkedList<std::string>();
	std::string script = clearSpaces();
	int i = 0;
	if (!missingSymbol())
	{
		std::regex words_regex("[^\<>:;!?]+");
		auto words_begin = std::sregex_iterator(script.begin(), script.end(), words_regex);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator i = words_begin; i != words_end; ++i)
			tags->addEnd((*i).str());// << '\n';
		return *tags;
	}
	else
	{
		if (countCloseSymbols() > countOpenSymbols())
		{
			errors += returnByCode(101);
			system("Color 06");
			std::cout << returnByCode(101);
			std::cout << "\033[31m" << "Build: 0 succeeded " << countExceptions() << " failed" << "\033[0m" << std::endl;
			//exit(101);
		}
		else
		{
			errors += returnByCode(104);
			system("Color 06");
			std::cout << returnByCode(104);
			std::cout << "\033[31m" << "Build: 0 succeeded " << countExceptions() << " failed" << "\033[0m" << std::endl;
			//exit(104);

		}
	}
	if (tags->isEmpty())
	{
		exit(120);
	}
}