#pragma once
#include<iostream>
#include <string>
#include <regex>
/*
* @verification for the @@syntax of each possible tag, if some of these methods returns false,
* the code is not clear;
*/
/*
* @syntax: <MAP-INC "N">, where N is floating point number
*/
inline bool isMap_Inc(std::string tag)
{
	std::regex inc("(<MAP-INC) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");
	if (regex_match(tag, inc)) return true;
	return false;
}
/*
* @syntax: <MAP-MLT "N">, where N is floating point number
*/
inline bool isMap_Mlt(std::string tag)
{
	std::regex mlt("(<MAP-MLT) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");
	if (regex_match(tag, mlt)) return true;
	return false;
}
/*
* @syntax: <AGG-SUM>
*/
inline bool isAgg_Sum(std::string tag)
{
	std::regex sum("(<AGG-SUM>)");
	if (regex_match(tag, sum)) return true;
	return false;
}
/*
* @syntax: <AGG-PRO>
*/
inline bool isAgg_Pro(std::string tag)
{
	std::regex pro("(<AGG-PRO>)");
	if (regex_match(tag, pro)) return true;
	return false;
}
/*
* @syntax: <AGG-AVG>
*/
inline bool isAgg_Avg(std::string tag)
{
	std::regex avg("(<AGG-AVG>)");
	if (regex_match(tag, avg)) return true;
	return false;
}
/*
* @syntax: <AGG-FST>
*/
inline bool isAgg_Fst(std::string tag)
{
	std::regex fst("(<AGG-FST>)");
	if (regex_match(tag, fst)) return true;
	return false;
}
/*
* @syntax: <AGG-LST>
*/
inline bool isAgg_Lst(std::string tag)
{
	std::regex lst("(<AGG-LST>)");
	if (regex_match(tag, lst)) return true;
	return false;
}
/*
* @syntax: <SRT-REV>
*/
inline bool isSrt_Rev(std::string tag)
{
	std::regex rev("(<SRT-REV>)");
	if (regex_match(tag, rev)) return true;
	return false;
}
/*
* @syntax: <SRT-ORD "ARG">, where ARG is ASC
*/
inline bool isSrt_Ord_ASC(std::string tag)
{
	std::regex asc("(<SRT-ORD) (\")(ASC)(\">)");
	if (regex_match(tag, asc)) return true;
	return false;
}
/*
* @syntax: <SRT-ORD "ARG">, where ARG is DSC
*/
inline bool isSrt_Ord_DSC(std::string tag)
{
	std::regex dsc("(<SRT-ORD) (\")(DSC)(\">)");
	if (regex_match(tag, dsc)) return true;
	return false;
}
/*
* @syntax: <SRT-SLC "N">, where N is positive number
*/
inline bool isSrt_Slc(std::string tag)
{
	std::regex slc("(<SRT-SLC) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");
	if (regex_match(tag, slc)) return true;
	return false;
}
/*
* @syntax: <SRT-DST> 
*/
inline bool isSrt_Dst(std::string tag)
{
	std::regex dst("(<SRT-DST>)");
	if (regex_match(tag, dst)) return true;
	return false;
}