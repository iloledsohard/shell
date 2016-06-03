#pragma once
#include "variable.h"
class Matrix :
	public Variable
{
public:
	Matrix(int , int, string);
	~Matrix();
	double operator()(int i, int j) const;
private:
	double* elements_;
};