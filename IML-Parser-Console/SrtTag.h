#pragma once
#include"Tag.h"
/*
* @hereditary class of Tag, part of is-a Tag hierarchy
* @ go in Tag.h for brief explanation
*/
class SrtTag : public Tag
{
private:
	std::string name;
	std::vector<double> content;
	std::string id;
public:
	SrtTag(std::string, std::vector<double>, std::string);
	void add(double) override;
	std::string path() override;
	std::string getName() override;
	std::vector<double> nodeReckoning(std::vector<double>) override;
	std::vector<double> getContent() override;
	void reverse() override;
	SrtTag* clone() const override;
};