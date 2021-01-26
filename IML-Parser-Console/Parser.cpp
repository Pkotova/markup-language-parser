#include "Parser.h"
#include"AggTag.h"
#include"MapTag.h"
#include"SrtTag.h"
#include"Reckoning.h"

/*	@copy private method, part of canonical representation*/
void Tree::copy(const Tree& other)
{
	setTag(other.currentTag);
	setLeft(other.left);
	setRight(other.right);
}

/*	@destroy private method, part of canonical representation*/
void Tree::destroy()
{
	delete[] this->currentTag;
	delete[] this->left;
	delete[] this->right;
}

/*	@default constructor, delegating multy purpose constructor*/
Tree::Tree() : Tree(nullptr, nullptr, nullptr) {}

/*	@copy constructor*/
Tree::Tree(const Tree& other)
{
	this->copy(other);
}

/*	@operator=*/
Tree& Tree::operator=(const Tree& other)
{
	if (this != &other)
	{
		this->copy(other);
	}

	return *this;
}

/*	@multy purpose constructor*/
Tree::Tree(Tag* _currentTag, Tree* _left, Tree* _right) : currentTag(nullptr), left(nullptr), right(nullptr)
{
	this->currentTag = _currentTag;
	this->left = _left;
	this->right = _right;
}

/*	@destructor, destroys the tree and free the memory*/
Tree::~Tree()
{
	if (this == nullptr)
	{
		return;
	}

	if (this->left == nullptr && this->right == nullptr)
	{
		this->destroy();
		return;
	}

	this->left->~Tree();
	this->right->~Tree();
}

/*	@set root tag*/
void Tree::setTag(Tag* newTag)
{
	if (this->currentTag != nullptr)
	{
		delete[] this->currentTag;
		this->currentTag = newTag;
	}
}

/*	@get root tag*/
const Tag* Tree::getTag() const
{
	return this->currentTag;
}

/*	@set left subtree*/
void Tree::setLeft(Tree* newLeft)
{
	if (this->left != nullptr)
	{
		delete[] this->left;
		this->left = newLeft;
	}
}

/*	@get left subtree*/
const Tree* Tree::getLeft() const
{
	return this->left;
}

/*	@set right subtree*/
void Tree::setRight(Tree* newRight)
{
	if (this->right != nullptr)
	{
		delete[] this->right;
		this->right = newRight;
	}
}

/*	@get right subtree*/
const Tree* Tree::getRight() const
{
	return this->right;
}

/*	@modify id to each node which is certain tag*/
void Tree::modifyIndex(size_t& index, Tree*& tree, std::string& input, std::string& id)
{
	std::vector<double> currentContent;
	std::string tempTagName;
	while (input[index] != '>') 
	{
		tempTagName += input[index];
		index++;
	}

	tempTagName += input[index]; 
	index++;
	// construct each node
	if (tempTagName[1] == 'M')
	{
		tree = new Tree{ new MapTag{tempTagName, currentContent, id}, nullptr, nullptr }; // initialize new instance of class MapTag
	}
	else if (tempTagName[1] == 'A')
	{
		tree = new Tree{ new AggTag{tempTagName, currentContent, id}, nullptr, nullptr };// initialize new instance of class AggTag
	}
	else if (tempTagName[1] == 'S')
	{
		tree = new Tree{ new SrtTag{tempTagName, currentContent, id}, nullptr, nullptr };// initialize new instance of class SrtTag
	}
}

/*	@add content into nodes/ tags*/
void Tree::addContent(size_t& index, Tree*& tree, std::string& input)
{
	std::string number; // number variable for saving digits
	double tempNumber; // we need to cast each string to double number

	while (input[index] != ' ' && input[index] != '<') 
	{
		number += input[index];
		index++;
	}

	tempNumber = atof(number.c_str()); // "atof" is casting const char* to double and ".c_str()" converts const char* to string 
	tree->currentTag->add(tempNumber);

}

/*	@catch tags in same lavel of the tree*/
void Tree::sameLavelTags(size_t& index, Tree*& tree, std::string& input, std::string& _id)
{
	Tree* tempTree = tree->right;
	std::string id = "RL";

	while (tempTree->left != nullptr) 
	{
		tempTree = tempTree->left;
		id += "L";
	}

	tempTree->left = generateTree(tempTree->left, input, index, _id + id);

	Tree* temp = biggestIndexPos(tree->right); // variable for the node with biggest index in the input
	int copyCounter = copies(tempTree->left, temp) - 1; // variable for the number of nodes with the same tag name before the current node in the input
	std::string currentTag;
	currentTag = temp->currentTag->getName();

	while (!(input[index] == '/' && input[index + 1] == currentTag[1] && copyCounter == 0)) 
	{
		if (input[index] == '/' && input[index + 1] == currentTag[1] && copyCounter != 0)
		{
			copyCounter--;
		}

		index++;
	}
	while (input[index] != '>') // until we end closing tag
	{
		index++;
	}
}

/*	@catch nesing */
void Tree::nesting(size_t& index, Tree*& tree, std::string& input, std::string& _id)
{
	tree->right = generateTree(tree->right, input, index, _id + "R");

	Tree* temp = biggestIndexPos(tree->right); // biggest index
	int copyCounter = copies(tree->right, temp) - 1; 
	std::string currentTag;
	currentTag = temp->currentTag->getName();

	while (!(input[index] == '/' && input[index + 1] == currentTag[1] && copyCounter == 0)) 
	{
		if (input[index] == '/' && input[index + 1] == currentTag[1] && copyCounter != 0)
		{
			copyCounter--;
		}

		index++;
	}
	while (input[index] != '>') 
	{
		index++;
	}
}

/*	@generate tree */
Tree* Tree::generateTree(Tree*& tree, std::string& input, size_t index, std::string identificator)
{
	std::vector<double> currentContent;

	modifyIndex(*&index, tree, input, identificator);


	while (input[index] != '\0') 
	{
		if (isdigit(input[index]) == 4 || input[index] == '-') // case if the current symbol is positve or negative number
		{
			addContent(index, tree, input);
		}
		if (input[index] == '<') // nesting
		{
			if (input[index + 1] == '/') // or closing tag
			{
				while (input[index] != '>')
				{
					index++;
				}

				if (input[index + 1] == '<' && input[index + 2] != '/') // more than one nesting
				{
					tree->left = generateTree(tree->left, input, index + 1, identificator + "L"); // generate left subtree
					return tree;
				}
				else // in this case there are more symbols from the previous node 
				{
					return tree;
				}
			}
			else if (tree->right != nullptr) // case for tag at same level
			{
				sameLavelTags(index, tree, input, identificator);
			}
			else if (input[index] != '>') // case for tag with lower level, nesting
			{
				nesting(index, tree, input, identificator);
			}
		}
		index++;
	}

	return tree;
}

/*	@biggest index position, [leftest? tag] */
Tree* Tree::biggestIndexPos(Tree* current)
{
	if (current->left == nullptr) // the bottom
	{
		return current;
	}

	return biggestIndexPos(current->left);
}

/*	@tag copies after current tag*/
int Tree::copies(Tree* current, Tree* match)
{
	if (current == nullptr) 
	{
		return 0;
	}

	if (current->currentTag->getName() == match->currentTag->getName()) 
	{
		return 1 + copies(current->left, match) + copies(current->right, match);
	}

	return 0 + copies(current->left, match) + copies(current->right, match);
}

/*	@reverse tree*/
void Tree::treeReversion(Tree*& first)
{
	if (first == nullptr) // the bottom
	{
		return;
	}

	first->currentTag->reverse(); // reverse current node's content

	treeReversion(first->right);
	treeReversion(first->left);
}

int Tree::nodeDuplicates(Tree* first, Tree* current)
{
	if (first->currentTag->path() == current->currentTag->path() || first == nullptr) // the bottom
	{
		return 0;
	}

	if (first->currentTag->getName() == current->currentTag->getName() && first->currentTag->getContent() == current->currentTag->getContent()) // case if the current tag's name is the same as the one to compare; processing all cases
	{
		if (first->right == nullptr && first->left == nullptr)
		{
			return 1;
		}
		if (first->right != nullptr && first->left != nullptr)
		{
			return 1 + nodeDuplicates(first->right, current) + nodeDuplicates(first->left, current);
		}
		if (first->right == nullptr)
		{
			return 1 + nodeDuplicates(first->left, current);
		}

		return 1 + nodeDuplicates(first->right, current);
	}

	if (first->right == nullptr && first->left == nullptr)
	{
		return 0;
	}
	if (first->right != nullptr && first->left != nullptr)
	{
		return 0 + nodeDuplicates(first->right, current) + nodeDuplicates(first->left, current);
	}
	if (first->right == nullptr)
	{
		return 0 + nodeDuplicates(first->left, current);
	}

	return 0 + nodeDuplicates(first->right, current);
}

/*	@move id to the end of the tag*/
void Tree::moveToEnd(size_t& index, std::string& input, std::string& temp)
{
	// <agg-fst><L><R>"LLD"
	while (input[index] != '>')
	{
		temp += input[index];
		index++;
	}

	temp += input[index];
}

/*	@add data to the content*/
void Tree::createContent(size_t& index, std::vector<double>& data, std::string& input)
{
	std::string number;
	double tempNumber;

	while (input[index] != ' ' && input[index] != '<')
	{
		number += input[index];
		index++;
	}

	tempNumber = atof(number.c_str()); // convert string to double
	data.push_back(tempNumber);
}

/*	@check if data is correct*/
bool Tree::flagValue(std::vector<double> data, Tree* tree)
{
	std::vector<double> tempNumbers = reverseContent(data);
	std::vector<double> tempContent = tree->currentTag->getContent();

	while (!(tempNumbers.empty()))
	{
		if (tempNumbers.back() != tempContent.back())
		{
			return false;
		}

		tempNumbers.pop_back();
		tempContent.pop_back();
	}

	return true;
}

/*	@catch if a data is nested between tags*/
std::vector<double> Tree::getDataAfter(Tree* first, Tree* tree, std::string& input)
{
	std::vector<double> numbers;
	size_t index = 0;
	int duplicates = nodeDuplicates(first, tree); 

	while (input[index] != '\0')
	{
		std::string temp;
		size_t tempIndex = index;

		if (input[index] == '<' && input[index + 1] != '/')
		{
			while (input[tempIndex] != '>')
			{
				temp += input[tempIndex];
				tempIndex++;
			}

			temp += input[tempIndex];
		}
		index = tempIndex;

		if (temp == tree->currentTag->getName())
		{
			if (duplicates == 0) // case if the current tag is reached in the input
			{

				while (input[index] != '<' && input[index] != '\0')
				{
					if (isdigit(input[index]) == 4 || input[index] == '-') // positive or negative  number
					{
						std::string number;
						double tempNumber;

						while (input[index] != ' ' && input[index] != '<')
						{
							number += input[index];
							index++;
						}

						tempNumber = atof(number.c_str()); // string to double
						numbers.push_back(tempNumber);
					}
					else
					{
						index++;
					}
				}
				std::vector<double> tempContent;
				std::vector<double> tempNumbers = reverseContent(numbers);

				tempContent = tree->currentTag->getContent();

				bool flag = true;

				while (!(tempNumbers.empty()))
				{
					if (tempNumbers.back() != tempContent.back())
					{
						flag = false;
						break;
					}

					tempNumbers.pop_back();
					tempContent.pop_back();
				}

				if (flag == true)
				{
					index++;

					while (!(numbers.empty()))
					{
						numbers.pop_back();
					}

					while (input[index] != '<' && input[index] != '\0')
					{

						if (isdigit(input[index]) == 4 || (input[index] == '-' && isdigit(input[index + 1]) == 4)) 
						{
							std::string number1;
							double tempNumber1;

							while (input[index] != ' ' && input[index] != '<')
							{
								number1 += input[index];
								index++;
							}

							tempNumber1 = atof(number1.c_str()); 
							numbers.push_back(tempNumber1);
						}
						else
						{
							index++;
						}
					}

					return numbers;

				}

				while (!(numbers.empty()))
				{
					numbers.pop_back();
				}
			}
			else
			{
				duplicates--;
			}
		}

		index++;
	}

	return numbers;
}

/*	@return collected data after running trought the tree*/
std::vector<double> Tree::getData(Tree* first, Tree* tree, std::string& input)
{
	std::vector<double> data;
	size_t index = 0;
	int duplicates = nodeDuplicates(first, tree); 

	while (input[index] != '\0')
	{
		std::string temp;

		if (input[index] == '<')
		{
			moveToEnd(index, input, temp);
		}

		if (temp == tree->currentTag->getName())
		{
			if (duplicates == 0) 
			{
				index++;

				while (input[index] != '<' && input[index] != '\0')
				{
					if (isdigit(input[index]) == 4 || input[index] == '-') 
					{
						createContent(index, data, input);
					}
					else
					{
						index++;
					}
				}

				if (flagValue(data, tree) == true)
				{
					return data;
				}
				else
				{
					while (!(data.empty()))
					{
						data.pop_back();
					}
				}
			}
			else
			{
				duplicates--;
			}
		}
		index++;
	}
	return data;
}

/*	@generate right subtree*/
void Tree::generatRightSubtree(std::vector<double>& newRight, std::vector<double>& temp)
{
	while (!(newRight.empty()))
	{
		temp.push_back(newRight.back());
		newRight.pop_back();
	}
}

/*	@catch if tags are nested on the same level*/
void Tree::sameLevelNesting(Tree* current, Tree* first, std::string& input, std::vector<double>& newRight, std::vector<double>& temp, std::vector<double>& containerForCurrentContent)
{
	Tree* tempCurrent = current->right;

	while (tempCurrent->left != nullptr)
	{
		std::vector<double> leftSubtree;
		leftSubtree = treeResult(first, tempCurrent->left, input);

		if (newRight.back() == leftSubtree.back())
		{
			std::vector<double> afterTag = getDataAfter(first, tempCurrent, input);
			afterTag = reverseContent(afterTag);

			while (!(afterTag.empty()))
			{
				temp.push_back(afterTag.back());
				afterTag.pop_back();
				containerForCurrentContent.pop_back();
			}

			temp.push_back(newRight.back());
			newRight.pop_back();

			tempCurrent = tempCurrent->left;
		}
		else
		{
			temp.push_back(newRight.back());
			newRight.pop_back();
		}
	}
}

/*	@calculate nesting tags*/
void Tree::nestingResult(std::vector<double>& containerForCurrentContent, Tree* current, Tree* first, std::string& input, std::vector<double>& newRight)
{
	std::vector<double> temp;
	std::vector<double> numbersGetNumbers = getData(first, current, input);

	while (!(containerForCurrentContent.empty()))
	{
		if (!(numbersGetNumbers.empty()))
		{
			temp.push_back(containerForCurrentContent.back());
			containerForCurrentContent.pop_back();
			numbersGetNumbers.pop_back();
		}
		else if (newRight.empty())
		{
			temp.push_back(containerForCurrentContent.back());
			containerForCurrentContent.pop_back();
		}

		if (numbersGetNumbers.empty())
		{
			if (current->right != nullptr)
			{
				if (current->right->left != nullptr && current->right->left->right == nullptr)
				{
					sameLevelNesting(current, first, input, newRight, temp, containerForCurrentContent);
				}
				else
				{
					generatRightSubtree(newRight, temp);
				}
			}
			else
			{
				generatRightSubtree(newRight, temp);
			}
		}
	}

	while (!(temp.empty())) // add all information in the node's content
	{
		containerForCurrentContent.push_back(temp.back());
		temp.pop_back();
	}
	containerForCurrentContent = reverseContent(containerForCurrentContent);
}

/*	@calculate non nested tags*/
void Tree::resultNONNesting(std::vector<double>& containerForCurrentContent, std::vector<double>& newRight)
{
	containerForCurrentContent = reverseContent(containerForCurrentContent); // reverse content

	while (!(newRight.empty()))
	{
		containerForCurrentContent.push_back(newRight.back());
		newRight.pop_back();
	}
}

/*	@generate lest subtree*/
void Tree::leftSubtree(Tree* first, Tree* current, std::string& input, std::vector<double>& newResult, std::vector<double>& containerForCurrentContent)
{
	std::vector<double> newLeft;
	newLeft = treeResult(first, current->left, input);

	newResult = nodeResult(current, containerForCurrentContent); // calculate current node's content

	while (!(newLeft.empty())) // add left subtree result
	{
		newResult.push_back(newLeft.back());
		newLeft.pop_back();
	}
}

/*	@calculate each node result*/
std::vector<double> Tree::nodeResult(Tree* first, std::vector<double>& container)
{
	return first->currentTag->nodeReckoning(container);
}
/*	@calculate all nodes result*/
std::vector<double> Tree::treeResult(Tree* first, Tree* current, std::string& input)
{
	std::vector<double> containerForCurrentContent;
	std::vector<double> newResult;

	if (current == nullptr) // the bottom
	{
		return newResult;
	}

	if (current->left == nullptr && current->right == nullptr)
	{
		containerForCurrentContent = current->currentTag->getContent();
		newResult = nodeResult(current, containerForCurrentContent); // calculate node result
		return newResult;
	}

	std::vector<double> newRight = treeResult(first, current->right, input);

	if ((!(getData(first, current, input).empty())) || (getData(first, current, input).empty() && (!(current->currentTag->getContent().empty()))))  // case if there are no numbers before the current
	{
		containerForCurrentContent = current->currentTag->getContent();
		nestingResult(containerForCurrentContent, current, first, input, newRight);
	}
	else
	{
		resultNONNesting(containerForCurrentContent, newRight);
	}

	leftSubtree(first, current, input, newResult, containerForCurrentContent);
	newResult = reverseContent(newResult);

	return newResult;
}