#include "AggTag.h"
/*	@Multy purpose constructor*/
AggTag::AggTag(std::string _name, std::vector<double> _content, std::string _id)
{
	this->name = _name;
	this->content = _content;
	this->id = _id;
}

/*	@adds numberic data to the content*/
void AggTag::add(double _content)
{
	this->content.push_back(_content);
}

/*	@returns the path from the root to node(tag)*/
std::string AggTag::path()
{
	return this->id;
}

/*	@retuns tag name*/
std::string AggTag::getName()
{
	return this->name;
}

/*	@Calculate the value of each node, using funtions from Rechoning.h*/
std::vector<double> AggTag::nodeReckoning(std::vector<double> container)
{
	std::vector<double> result; // result for each node
	//checks the type of each tag
	if (isAgg_Sum(this->name))	
	{
		//calculates the result and add the outcome to the result
		result.push_back(agg_sum(container));
	}
	else if (isAgg_Pro(this->name))
	{
		result.push_back(agg_pro(container));
	}
	else if (isAgg_Avg(this->name))
	{
		result.push_back(agg_avg(container));
	}
	else if (isAgg_Fst(this->name))
	{
		result.push_back(agg_fst(container));
	}
	else
	{
		result.push_back(agg_lst(srt_rev(container)));
	}

	return result;
}

/*	@Return the tag's content/data*/
std::vector<double> AggTag::getContent()
{
	return this->content;
}

/*	@Reverse content, because we add the outcome of each tag to a result, 
* so we receive the final result 
* in the wrong order, so we need to reverse it to be truly correct*/
void AggTag::reverse()
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
AggTag* AggTag::clone() const
{
	return new AggTag(*this);
}
