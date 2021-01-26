#pragma once
#include "Tag.h"
#include <string>
#include <vector>
/*
* @Parser file, is part of the application layer of the application 
* it is defined as the data structure Tree, where each node is Tag
* and each subtree is another tree
* This class generate a new tree structure where the root is the first tag in the script given from ExceptionRepository 
* - if its verificated and clean(without mistakes). 
*	In Parser.cpp you will find brief explanation for each of the following methods
*/

class Tree
{
private:
	Tag* currentTag;
	Tree* left;
	Tree* right;

	void copy(const Tree&);
	void destroy();

public:

	Tree();
	Tree(const Tree&);
	Tree& operator=(const Tree&);
	Tree(Tag*, Tree*, Tree*);
	~Tree();

	void setTag(Tag* newTag);
	const Tag* getTag() const;

	void setLeft(Tree* newLeft);
	const Tree* getLeft() const;

	void setRight(Tree* newRight);
	const Tree* getRight() const;

	void modifyIndex(size_t&, Tree*&, std::string&, std::string&);
	void addContent(size_t&, Tree*&, std::string&);
	void sameLavelTags(size_t&, Tree*&, std::string&, std::string&);
	void nesting(size_t&, Tree*&, std::string&, std::string&);

	Tree* generateTree(Tree*&, std::string&, size_t, std::string);
	Tree* biggestIndexPos(Tree*);

	int copies(Tree*, Tree*);

	void treeReversion(Tree*&);

	int nodeDuplicates(Tree*, Tree*);

	void moveToEnd(size_t&, std::string&, std::string&);
	void createContent(size_t&, std::vector<double>&, std::string&);
	bool flagValue(std::vector<double>, Tree*);

	std::vector<double> getDataAfter(Tree*, Tree*, std::string&);
	std::vector<double> getData(Tree*, Tree*, std::string&);

	void generatRightSubtree(std::vector<double>&, std::vector<double>&);
	void sameLevelNesting(Tree*, Tree*, std::string&, std::vector<double>&, std::vector<double>&, std::vector<double>&);
	void nestingResult(std::vector<double>&, Tree*, Tree*, std::string&, std::vector<double>&);
	void resultNONNesting(std::vector<double>&, std::vector<double>&);
	void leftSubtree(Tree*, Tree*, std::string&, std::vector<double>&, std::vector<double>&);


	std::vector<double> nodeResult(Tree*, std::vector<double>&);
	std::vector<double> treeResult(Tree*, Tree*, std::string&);
};