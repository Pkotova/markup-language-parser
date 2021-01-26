#pragma once
#include "Reckoning.h"
#include"Verification.h"
#include <iostream>
#include <string>
#include <vector>
/*
* @brief explanation 
* 
* @Tag is an interface, root of is-a relationship
*	each method gives the opportunity to reach the information in each tag, where every
*	tag has id, content and name. 
*	@add - adding data to the content, if nested tags
*   @reverse - reversing tag content
*	@getName, @getContent - mutators, gives access to the Tag data fields
*   @path - returns, the path to each Tag, whether nested or not, 
*	@clone - clones the objects of each hereditary class
*   @nodeReckoning - calculates the given information using the methods in Reckoning.h
*/
class Tag
{
public:
	virtual std::string getName() = 0;
	virtual std::vector<double> getContent() = 0;
	virtual std::string path() = 0; 
	virtual std::vector<double> nodeReckoning(std::vector<double>) = 0;
	virtual void add(double) = 0; 
	virtual void reverse() = 0;	 
	virtual Tag* clone() const = 0;
};