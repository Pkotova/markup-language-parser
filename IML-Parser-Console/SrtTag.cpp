#include "SrtTag.h"
/*	@Multy purpose constructor*/
SrtTag::SrtTag(std::string _name, std::vector<double> _content, std::string _id)
{
	this->name = _name;
	this->content = _content;
	this->id = _id;
}

/*	@adds numberic data to the content*/
void SrtTag::add(double _content)
{
	this->content.push_back(_content);
}

/*	@returns the path from the root to node(tag)*/
std::string SrtTag::path()
{
	return this->id;
}

/*	@retuns tag name*/
std::string SrtTag::getName()
{
	return this->name;
}

/*	@Calculate the value of each node, using funtions from Rechoning.h*/
std::vector<double> SrtTag::nodeReckoning(std::vector<double> container)
{
	std::vector<double> result;

	if (isSrt_Rev(this->name))
	{
		result = srt_rev(container);
	}
	else if (isSrt_Ord_ASC(this->name))
	{
		result = srt_ord(getOrder(this->name), container);
	}
	else if (isSrt_Ord_DSC(this->name))
	{
		result = srt_slc((double)takeMapInc(this->name), container);
	}
	else if (isSrt_Slc(this->name))
	{
		result = srt_slc((double)takeMapInc(this->name), container);
	}
	else if (isSrt_Dst(this->name))
	{
		result = srt_dst(reverseContent(container));
		result = reverseContent(result);
	}

	return result;
}

/*	@Return the tag's content/data*/
std::vector<double> SrtTag::getContent()
{
	return this->content;
}

/*	@Reverse content, because we add the outcome of each tag to a result,
* so we receive the final result
* in the wrong order, so we need to reverse it to be truly correct*/
void SrtTag::reverse()
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
SrtTag* SrtTag::clone() const
{
	return new SrtTag(*this);
}
