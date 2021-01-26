#pragma once
#include <algorithm> 
#include <functional>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
/*
* Following file and function are part of the domain module level of the application
* each function calculate the given tag, which represents a certain operation
*/

/*@		<MAP-INC "N"> , where N is floating point number
*		std::vector<double>& map_inc(double n, std::vector<double>& content), where
*		n the number we want to multiply by еach element of the Tag data 
*		@example:	<MAP-INC "1">1 2 3</MAP-INC> ⇒ 2 3 4
*/
inline std::vector<double>& map_inc(double n, std::vector<double>& content)
{
	int size = content.size();
	for (int i = 0; i < size; i++)
	{
		content[i] += n;
	}
	return content;
}

/*@		<MAP-MLT "N"> , where N is floating point number
*		std::vector<double>& map_mlt(double n, std::vector<double>& content), where
*		n the number we want to add to еach element of the Tag data
*		@example:	<MAP-MLT "2">1 2 3</MAP-MLT> ⇒ 2 4 6
*/
inline std::vector<double>& map_mlt(double n, std::vector<double>& content)
{
	int size = content.size();
	for (int i = 0; i < size; i++)
	{
		content[i] *= n;
	}
	return content;
}

/*@		<AGG-SUM>
*		double agg_sum(std::vector<double>& content), it 
*		manages to calculate the sum of all data elements
*		@example:	<AGG-SUM>1 2 3</AGG-SUM> ⇒ 6
*/
inline double agg_sum(std::vector<double>& content)
{
	double sum = 0;
	int size = content.size();
	for (int i = 0; i < size; i++)
	{
		sum += content[i];
	}
	return sum;
}

/*@		<AGG-PRO>
*		double agg_pro(std::vector<double>& content) it
*		manages to calculate the product of all data elements
*		@example:	<AGG-PRO>1 2 3</AGG-PRO> ⇒ 6
*/
inline double agg_pro(std::vector<double>& content)
{
	double product = 1;
	int size = content.size();
	for (int i = 0; i < size; i++)
	{
		product *= content[i];
	}
	return product;
}

/*@		<AGG-AVG>
*		double agg_avg(std::vector<double>& content) it
*		manages to calculate the average value of all data elements
*		@example:	3.	<AGG-AVG>1 2 3</AGG-AVG> ⇒ 2
*/
inline double agg_avg(std::vector<double>& content)
{
	double sum = 0;
	int size = content.size();
	for (int i = 0; i < size; i++)
	{
		sum += content[i];
	}
	return (sum / size);
}

/*@		<AGG-FST>
*		double agg_fst(std::vector<double>& content) it
*		manages to return the first element of the tag content/data
*		@example:	<AGG-FST>1 2 3</AGG-FST> ⇒ 1
*/
inline double agg_fst(std::vector<double>& content)
{
	return content[0];
}

/*@		<AGG-LST>
*		double agg_lst(std::vector<double>& content) it
*		manages to return the last element of the tag content/data
*		@example:	<AGG-LST>1 2 3</AGG-LST> ⇒ 3
*/
inline double agg_lst(std::vector<double>& content)
{
	return content[content.size() - 1];
}

/*@		<SRT-REV>
*		std::vector<double>& srt_rev(std::vector<double>& content) it
*		manages to return the reversed content
*		@example:	<SRT-REV>1 2 3</SRT-REV> ⇒ 3 2 1 
*/
inline std::vector<double>& srt_rev(std::vector<double>& content)
{
	std::reverse(content.begin(), content.end());
	return content;
}

/*@		<SRT-ORD "ARG">, where ARG = ASC or ARG = DSC 
*		std::vector<double>& srt_ord(std::string order, std::vector<double>& content) it
*		manages to return the sorted content/data
*		@example:	<SRT-ORD "ASC">3 2 1</SRT-ORD> ⇒ 1 2 3 
*		@example:	<SRT-ORD "DSC">1 2 3</SRT-ORD> ⇒ 3 2 1 
*/
inline std::vector<double>& srt_ord(std::string order, std::vector<double>& content)
{
	if (order == "ASC")
	{
		sort(content.begin(), content.end());
	}
	else
	{
		sort(content.begin(), content.end(), std::greater<int>());
	}
	return content;
}
/*@		<SRT-SLC "N">, where N is floating point number
*		std::vector<double> srt_slc(int n, std::vector<double>& content) it
*		manages to return the subcontent from given N 
*		@example: <SRT-SLC "1">3 2 1</SRT-SLC> ⇒ 2 1 
*/
inline std::vector<double> srt_slc(int n, std::vector<double>& content)
{
	int size = content.size();
	std::vector<double> subVector;
	for (int i = n; i < size; i++)
	{
		subVector.push_back(content[i]);
	}
	return subVector;
}
/*@		<SRT-DST>
*		std::vector<double>& srt_dst(std::vector<double> content) it
*		manages to remove the duplicates from the data
*		@example: <SRT-DST>4 8 4 3</SRT-DST> ⇒ 4 8 3 
*/
inline std::vector<double>& srt_dst(std::vector<double> content)
{
	int size = content.size();
	std::vector<double> subVector;
	auto end = content.end();
	for (auto it = content.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	content.erase(end, content.end());

	return content;
}

// helper funtion
inline double takeMapInc(std::string input)
{
	std::string temp;
	int size = 10;

	while (input[size] != '\"')
	{
		temp += input[size];
		size++;
	}

	return atof(temp.c_str());
}
// helper function
inline std::string getOrder(std::string input)
{
	std::string temp;
	int index = 10;

	while (input[index] != '\"')
	{
		temp += input[index];
		index++;
	}

	return temp;
}
// reverse data
inline std::vector<double> reverseContent(std::vector<double> list)
{
	std::vector<double> temp;

	while (!(list.empty()))
	{
		temp.push_back(list.back());
		list.pop_back();
	}

	return temp;
}

// calculated result
inline void result(std::vector<double> content)
{
	std::vector<double> temp;
	temp = content;

	while (!temp.empty())
	{
		std::cout << temp.back() << " ";
		temp.pop_back();
	}
}

// cast to string calcutated result for better experience while saving the result in file
inline std::string toString(std::vector<double>& seq)
{
	std::vector<double> newVector = reverseContent(seq);
	std::stringstream output;
	std::copy(newVector.begin(), newVector.end(), std::ostream_iterator<double>(output, " "));

	return output.str();
}
