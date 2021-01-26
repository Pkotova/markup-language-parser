#include "MapTag.h"
/*	@Multy purpose constructor*/
MapTag::MapTag(std::string _name, std::vector<double> _content, std::string _id)
{
	this->name = _name;
	this->content = _content;
	this->id = _id;
}

/*	@adds numberic data to the content*/
void MapTag::add(double _content)
{
	this->content.push_back(_content);
}

/*	@returns the path from the root to node(tag)*/
std::string MapTag::path()
{
	return this->id;
}

/*	@retuns tag name*/
std::string MapTag::getName()
{
	return this->name;
}

/*	@Calculate the value of each node, using funtions from Rechoning.h*/
std::vector<double> MapTag::nodeReckoning(std::vector<double> container)
{
	std::vector<double> result;

	if (isMap_Inc(this->name))
	{
		double temp = takeMapInc(this->name);
		result = map_inc(temp, container);
	}
	else
	{
		//assert
		double temp = takeMapInc(this->name);
		result = map_mlt(temp, container);
	}

	return result;
}

/*	@Return the tag's content/data*/
std::vector<double> MapTag::getContent()
{
	return this->content;
}

/*	@Reverse content, because we add the outcome of each tag to a result,
* so we receive the final result
* in the wrong order, so we need to reverse it to be truly correct*/
void MapTag::reverse()
{
	std::vector<double> temp;

	while (!(this->content.empty()))
	{
		temp.push_back(this->content.back());
		this->content.pop_back();
	}

	this->content = temp;
}

/*  @make a polymorphic clone*/
MapTag* MapTag::clone() const
{
	return new MapTag(*this);
}