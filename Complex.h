#pragma once
#include <ostream>
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
	void setReal(double);
	void setImaginary(double);
	
	Complex conjugate() const;
private:
	double real_;
	double imaginary_;
};

ostream& operator<<(ostream& lhs, const Complex& rhs);
istream& operator >> (istream& lhs, Complex& rhs);
Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator+(double const& lhs, Complex const& rhs);
Complex operator+(const Complex& lhs, const double rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator-(double const& lhs, Complex const& rhs);
Complex operator-(const Complex& lhs, const double rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator*(double const& lhs, Complex const& rhs);
Complex operator*(const Complex& lhs, const double rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);
Complex operator/(double const& lhs, Complex const& rhs);
Complex operator/(const Complex& lhs, const double rhs);