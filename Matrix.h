#pragma once
#include "variable.h"

template<class T>
class Matrix
{
public:
	Matrix(int , int);
	Matrix(int);
	Matrix();
	~Matrix();
private:
	T elements_;
};