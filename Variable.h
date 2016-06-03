#pragma once
#include <string>
#include <list>
#include "enumerator.h"
using namespace std;

class Variable
{
public:
	Variable();
	~Variable();
	string getName() const;
	string getInfo() const;
	type getType() const;
protected:
	string name_;
	string info_;
	type type_;
	//static list<Variable*> address;
};