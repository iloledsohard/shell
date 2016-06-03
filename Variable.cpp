#include "Variable.h"



//Variable::Variable()
//{
//	address.push_back(this);
//}


Variable::~Variable()
{
}

string Variable::getName() const
{
	return name_;
}

string Variable::getInfo() const
{
	return info_;
}

type Variable::getType() const
{
	return type_;
}