#include "Exception.h"
/*@Sets exception code*/
void Exception::setCode(int _code)
{
	this->code = _code;
}

/*@Sets exception message*/
void Exception::setMessage(std::string& _message)
{
	this->message = _message;
}

/*@returns exceptions code*/
int Exception::getCode()
{
	return this->code;
}

/*@returns exception message*/
std::string& Exception::getMessage()
{
	return this->message;
}