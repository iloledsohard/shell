#pragma once
#include<iostream>
using namespace std;

class Complex
{
public:
	Complex();
	explicit Complex(double r);
	Complex(double r, double i);
	~Complex();
	double getReal() const;
	double getImaginary() const;
	Complex conjugate() const;
private:
	double real_;
	double imaginary_;
};