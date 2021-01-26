#pragma once
#include<string>
#include "Parser.h"
#include "ExceptionRepository.h"
#include "ResultRepository.h"
/*
* @brief explanation 
* this class is part of the presentation layer of the project,
* it manages user experience and gives different oportunities to the user 
* by menus, messages. Summed up - it controls the application flow
* @ you will find brief explanations for each of the methods below in IMLManagementView.cpp
*/
class IMLManagementView
{
public:
	void menu();
	void run();
	void filesystem();
	void inlineCode();
	bool askForSaveAs();
	void saveas(std::string);
	bool isTxt(std::string);
};