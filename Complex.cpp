#include "Complex.h"
#include <string>
#include <iostream>

using namespace std;

Complex::Complex()
{
	real_ = 0;
	imaginary_ = 0;
}

Complex::Complex(double real)
{
	real_ = real;
	imaginary_ = 0;
}

Complex::Complex(double real, double imaginary)
{
	real_ = real;
	imaginary_ = imaginary;
}


Complex::~Complex()
{
}

double Complex::getReal() const
{
	return real_;
}

double Complex::getImaginary() const
{
	return imaginary_;
}

void Complex::setReal(double real)
{
	real_ = real;
}

void Complex::setImaginary(double imaginary)
{
	imaginary_ = imaginary;
}

Complex Complex::conjugate() const
{
	return Complex(this->real_, -this->imaginary_);
}

ostream& operator<<(ostream& lhs, const Complex& rhs)
{
	if (rhs.getImaginary() >= 0) return lhs << rhs.getReal() << "+" << rhs.getImaginary() << "i";
	return lhs << rhs.getReal() << rhs.getImaginary() << "i";
}

istream& operator >> (istream& lhs, Complex& rhs)
{
	string line;
	getline(lhs, line);
	string::size_type sz;
	rhs.setReal(stod(line, &sz));
	rhs.setImaginary(stod(line.substr(sz)));
	return lhs;
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.getReal() + rhs.getReal(), lhs.getImaginary() + rhs.getImaginary());
}

Complex operator+(double const& lhs, Complex const& rhs)
{
	return Complex(lhs + rhs.getReal(), rhs.getImaginary());
}

Complex operator+(const Complex& lhs, const double rhs)
{
	return Complex(lhs.getReal() + rhs, lhs.getImaginary());
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.getReal() - rhs.getReal(), lhs.getImaginary() - rhs.getImaginary());
}

Complex operator-(double const& lhs, Complex const& rhs)
{
	return Complex(lhs - rhs.getReal(), rhs.getImaginary());
}

Complex operator-(const Complex& lhs, const double rhs)
{
	return Complex(lhs.getReal() - rhs, lhs.getImaginary());
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.getReal()*rhs.getReal() - lhs.getImaginary()*rhs.getImaginary(), lhs.getReal()*rhs.getImaginary() + lhs.getImaginary()*rhs.getReal());
}

Complex operator*(const double& lhs, const Complex& rhs)
{
	return Complex(lhs*rhs.getReal(), lhs*rhs.getImaginary());
}

Complex operator*(const Complex& lhs, const double rhs)
{
	return Complex(lhs.getReal()*rhs, lhs.getImaginary()*rhs);
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
	auto denum = (rhs.getReal()*rhs.getReal() + rhs.getImaginary() + rhs.getImaginary());
	return Complex((lhs.getReal()*rhs.getReal() + lhs.getImaginary()*rhs.getImaginary()) / denum, lhs.getImaginary()*rhs.getReal() - lhs.getReal()*rhs.getImaginary() / denum);
}

Complex operator/(const double& lhs, const Complex& rhs)
{
	auto denum = (rhs.getReal()*rhs.getReal() + rhs.getImaginary() + rhs.getImaginary());
	return Complex((lhs*rhs.getReal()) / denum, - lhs*rhs.getImaginary() / denum);
}

Complex operator/(const Complex& lhs, const double rhs)
{
	return Complex(lhs.getReal()/rhs, lhs.getImaginary()/rhs);
}
