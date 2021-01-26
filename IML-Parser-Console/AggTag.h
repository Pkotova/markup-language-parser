#pragma once
#include"Tag.h"
/*
* @hereditary class of Tag, part of is-a Tag hierarchy
* @ go in Tag.h for brief explanation
*/
class AggTag : public Tag
{
private:
	std::string name;
	std::vector<double> content;
	std::string id;
public:
	AggTag(std::string, std::vector<double>, std::string);
	std::string getName() override;
	std::vector<double> getContent() override;
	std::string path() override;
	void add(double) override;
	void reverse() override;
	std::vector<double> nodeReckoning(std::vector<double>) override;
	AggTag* clone() const override;
};