#pragma once
#include "variable.h"
class Matrix
{
public:
	Matrix(int , int, string);
	~Matrix();
private:
	double* elements_;
};