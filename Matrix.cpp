#include "Matrix.h"

Matrix::Matrix(int row, int column, string arg)
{
	type_ = MATRIX;
	name_ = arg;
	info_ = "Hier wird Information stehen";
	elements_ = nullptr;
	// ReSharper disable once CppNonReclaimedResourceAcquisition
	elements_ = new double[row, column];
}

Matrix::~Matrix()
{
	delete[] elements_;
	elements_ = nullptr;
}

double Matrix::operator()(int i, int j) const
{
	return elements_[i, j];
}