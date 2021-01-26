#pragma once
#include"Tag.h"
/*
* @hereditary class of Tag, part of is-a Tag hierarchy
* @ go in Tag.h for brief explanation
*/
class MapTag : public Tag
{
private:
	std::string name;
	std::vector<double> content;
	std::string id; 
public:
	MapTag(std::string, std::vector<double>, std::string);
	void add(double) override;
	std::string path() override;
	std::string getName() override;
	std::vector<double> nodeReckoning(std::vector<double>) override;
	std::vector<double> getContent() override;
	void reverse() override;
	MapTag* clone() const override;
};
// 3 4 5 -> 5 4 3 