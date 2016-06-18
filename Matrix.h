#pragma once
#include <iostream>

template<class T>
class Matrix
{
public:
	Matrix(unsigned int, unsigned int);
	explicit Matrix(unsigned int);
	Matrix(const Matrix<T>&);
	~Matrix();
	static Matrix<T> Identity(unsigned int, unsigned int);
	static Matrix<T> Zero(unsigned int, unsigned int);
	Matrix<double> ElementaryMatrixMultiplyRowMatrix(unsigned int, double) const;
	Matrix<bool> ElementaryMatrixSwapRow(unsigned int, unsigned int) const;
	Matrix<double> ElementaryMatrixAddRow(unsigned int, unsigned int, double) const;
	Matrix<double> ElementaryMatrixMultiplyColumn(unsigned int, double) const;
	Matrix<bool> ElementaryMatrixSwapColumn(unsigned int, unsigned int, double) const;
	Matrix<double> ElementaryMatrixAddColum(unsigned int, unsigned int, double) const;
	void makeIdentity();
	void makeZero();
	unsigned int getRowCount() const;
	unsigned int getColumnCount() const;
	unsigned int getElementCount() const;
	bool isSquare() const;
	void setElement(unsigned int, unsigned int, T);
	T getElement(unsigned int, unsigned int) const;
	Matrix<T> getColumn(unsigned int) const;
	void setColumn(unsigned int, const Matrix<T>&);
	Matrix<T> getRow(unsigned int) const;
	void setRow(unsigned int, const Matrix<T>&);
	unsigned int getMaxIndex(unsigned int, unsigned int, unsigned int, unsigned int) const;
	unsigned int getMaxAbsIndex(unsigned int, unsigned int, unsigned int, unsigned int) const;
	unsigned int getRowFromIndex(unsigned int) const;
	unsigned int getColumnFromIndex(unsigned int) const;
	unsigned int getIndex(unsigned int, unsigned int) const;
	Matrix<T> getProduct(const Matrix<T>&) const;
	Matrix<T> getProduct(const T&) const;
	void multiply(Matrix<T>&, const Matrix<T>&) const;
	void multiply(Matrix<T>&, const T&) const;
	T multiplyElement(const Matrix<T>&, unsigned int, unsigned int) const;
	T getDeterminant(); //4
	void LuDecompose(Matrix<T>&); //3
	Matrix<T> getSolution(Matrix<T>); //5
	void solve(Matrix<T>); //5
	void transpose(Matrix<T>&) const;
	Matrix<T> getTranspose() const;
	void invert(Matrix<T>&);
	Matrix<T> getInverse();
	T& operator[](const unsigned int);
private:
	unsigned int rows_;
	unsigned int columns_;
	T* elements_;
};

template <class T>
std::ostream& operator<<(std::ostream& lhs, const Matrix<T>& rhs);




template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns)
{
	rows_ = rows;
	columns_ = columns;
	elements_ = new T[rows*columns];
}

template <class T>
Matrix<T>::Matrix(unsigned int rows)
{
	rows_ = rows;
	columns_ = 1;
	elements_ = new T[rows];
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& obj)
{
	std::cout << "Copy constuctor is used!" << std::endl;
	rows_ = obj.rows_;
	columns_ = obj.columns_;
	elements_ = new T[obj.rows_*obj.columns_];
	for (unsigned int i = 0; i < obj.rows_*obj.columns_; i++)
	{
		elements_[i] = obj.elements_[i];
	}
}

template <class T>
Matrix<T>::~Matrix()
{
	delete[] elements_;
	elements_ = nullptr;
}

template <class T>
Matrix<T> Matrix<T>::Identity(unsigned int rows, unsigned int columns)
{
	auto result = Matrix(rows, columns);
	result.makeIdentity();
	return result;
}

template <class T>
Matrix<T> Matrix<T>::Zero(unsigned int rows, unsigned int columns)
{
	auto result = Matrix(rows, columns);
	result.makeZero();
	return result;
}

template <class T>
Matrix<double> Matrix<T>::ElementaryMatrixMultiplyRowMatrix(unsigned int row, double factor) const
{
	auto result = Matrix<double>::Identity(getRowCount(), getRowCount());
	result.setElement(row, row, factor);
	return result;
}

template <class T>
Matrix<bool> Matrix<T>::ElementaryMatrixSwapRow(unsigned int lhs, unsigned int rhs) const
{
	auto result = Matrix<bool>::Identity(getRowCount(), getRowCount());
	result.setElement(lhs, rhs, true);
	result.setElement(rhs, lhs, true);
	return result;
}

template <class T>
Matrix<double> Matrix<T>::ElementaryMatrixAddRow(unsigned int lhs, unsigned int rhs, double factor) const
{
	auto result = Matrix<double>::Identity(getRowCount(), getRowCount());
	result.setElement(lhs, rhs, factor);
	return result;
}

template <class T>
Matrix<double> Matrix<T>::ElementaryMatrixMultiplyColumn(unsigned int column, double factor) const
{
	auto result = Matrix<double>::Identity(getColumnCount(), getColumnCount());
	result.setElement(column, column, factor);
	return result;
}

template <class T>
Matrix<bool> Matrix<T>::ElementaryMatrixSwapColumn(unsigned int lhs, unsigned int rhs, double factor) const
{
	auto result = Matrix<bool>::Identity(getColumnCount(), getColumnCount());
	result.setElement(lhs, rhs, true);
	result.setElement(rhs, lhs, true);
	return result;
}

template <class T>
Matrix<double> Matrix<T>::ElementaryMatrixAddColum(unsigned int lhs, unsigned int rhs, double factor) const
{
	auto result = Matrix<double>::Identity(getColumnCount(), getColumnCount());
	result.setElement(lhs, rhs, factor);
	return result;
}

template <class T>
void Matrix<T>::makeIdentity()
{
	makeZero();
	auto maxIter = getRowCount() < getColumnCount() ? getRowCount() : getColumnCount();
	for (unsigned int i = 1; i <= maxIter; i++)
	{
		setElement(i, i, 1);
	}
}

template <class T>
void Matrix<T>::makeZero()
{
	for (unsigned int i = 1; i <= getElementCount(); i++)
	{
		this[i] = 0;
	}
}

template <class T>
unsigned int Matrix<T>::getRowCount() const
{
	return rows_;
}

template <class T>
unsigned Matrix<T>::getColumnCount() const
{
	return columns_;
}

template <class T>
unsigned int Matrix<T>::getElementCount() const
{
	return columns_*rows_;
}

template <class T>
bool Matrix<T>::isSquare() const
{
	return getColumnCount == getRowCount;
}

template <class T>
void Matrix<T>::setElement(unsigned int row, unsigned int column, T value)
{
	if (0 < row && row <= getRowCount() && 0 < column && column <= getColumnCount())
		elements_[getIndex(row, column)] = value;
	else
		throw "Index out of bounds.";
}

template <class T>
T Matrix<T>::getElement(unsigned int row, unsigned int column) const
{
	if (0 < row && row <= getRowCount() && 0 < column && column <= getColumnCount())
		return elements_[getIndex(row, column)];
	throw "Index out of bounds.";
}

template <class T>
Matrix<T> Matrix<T>::getColumn(unsigned int column) const
{
	auto result = Matrix(getRowCount(), 1);
	for (unsigned int row = 1; row <= getRowCount(); row++)
	{
		result[row] = getElement(row, column);
	}
	return result;
}

template <class T>
void Matrix<T>::setColumn(unsigned int column, const Matrix<T>& value)
{
	auto dimensionsMissMatch = getRowCount() != value.getElementCount();
	if (dimensionsMissMatch)
		throw "Dimensions missmatch.";
	for (unsigned int row = 1; row <= getColumnCount(); row++)
	{
		setElement(row, column, value[row]);
	}
}

template <class T>
Matrix<T> Matrix<T>::getRow(unsigned int row) const
{
	auto result = Matrix(1, getColumnCount());
	for (unsigned int column = 1; column <= getColumnCount(); column++)
	{
		result[column] = getElement(row, column);
	}
	return result;
}

template <class T>
void Matrix<T>::setRow(unsigned int row, const Matrix<T>& value)
{
	auto dimensionsMissMatch = getColumnCount() != value.getElementCount();
	if (dimensionsMissMatch)
		throw "Dimensions missmatch.";
	for (unsigned int column = 1; column <= getRowCount(); column++)
	{
		setElement(row, column, value[column]);
	}
}

template <class T>
unsigned int Matrix<T>::getMaxIndex(unsigned int rowLower, unsigned int rowUpper, unsigned int columnLower, unsigned int columnUpper) const
{
	auto rowIndexIsRight = 0 < rowLower || rowLower <= rowUpper || rowUpper <= getRowCount();
	auto columnIndexIsRight = 0 < columnLower || columnLower <= columnUpper || columnUpper <= getColumnCount();
	if (!rowIndexIsRight || !columnIndexIsRight)
		throw "Index out of bounds.";
	T max = getElement(rowLower, columnLower);
	unsigned int index = 1;
	for (auto row = rowLower; row <= rowUpper; row++)
	{
		for (auto column = columnLower; column <=columnUpper; column++)
		{
			if (getElement(row, column) > max)
			{
				max = getElement(row, column);
				index = getIndex(row, column);
			}
		}
	}
	return index;
}

template <class T>
unsigned int Matrix<T>::getMaxAbsIndex(unsigned int rowLower, unsigned int rowUpper, unsigned int columnLower, unsigned int columnUpper) const
{
	auto rowIndexIsRight = 0 < rowLower || rowLower <= rowUpper || rowUpper <= getRowCount();
	auto columnIndexIsRight = 0 < columnLower || columnLower <= columnUpper || columnUpper <= getColumnCount();
	if (!rowIndexIsRight || !columnIndexIsRight)
		throw "Index out of bounds.";
	T max = 0;
	unsigned int index = 1;
	for (auto row = rowLower; row <= rowUpper; row++)
	{
		for (auto column = columnLower; column <= columnUpper; column++)
		{
			auto element = getElement(row, column) >= 0 ? getElement(row, column) : -getElement(row, column);
			if (element > max)
			{
				max = element;
				index = getIndex(row, column);
			}
		}
	}
	return index;
}

template <class T>
unsigned int Matrix<T>::getRowFromIndex(unsigned int index) const
{
	if (0 < index && index <= getElementCount())
		return ((index - 1) % getRowCount()) + 1;
	throw "Index out of bounds.";
}

template <class T>
unsigned int Matrix<T>::getColumnFromIndex(unsigned int index) const
{
	if (0 < index && index <= getElementCount())
		return (index - 1) / getRowCount() + 1;
	throw "Index out of bounds.";
}

template <class T>
unsigned int Matrix<T>::getIndex(unsigned int row, unsigned int column) const
{
	return (column - 1)*getRowCount() + row - 1;
}

template <class T>
void Matrix<T>::multiply(Matrix<T>& result, const Matrix<T>& factor) const
{
	if (getColumnCount() != factor.getRowCount())
	{
		throw "Inner dimensions missmatch.";
	}
	auto rowsMissmatch = result.getRowCount() != getRowCount();
	auto columnsMissmatch = result.getColumnCount() != factor.getColumnCount();
	if (rowsMissmatch || columnsMissmatch)
	{
		throw "Result dimensions missmatch.";
	}
	for (unsigned int row = 1; row <= getRowCount(); row++)
	{
		for (unsigned int column = 1; column <= factor.getColumnCount(); column++)
		{
			auto element = multiplyElement(factor, row, column);
			result.setElement(row, column, element);
		}
	}
}

template <class T>
void Matrix<T>::multiply(Matrix<T>& result, const T& faktor) const
{
	auto rowsMissmatch = result.getRowCount() != getRowCount();
	auto columnsMissmatch = result.getColumnCount() != getColumnCount();
	if (rowsMissmatch || columnsMissmatch)
		throw "Result dimensions missmatch.";
	for (unsigned int i = 1; i <= getElementCount(); i++)
	{
		result[i] = this[i] * faktor;
	}
}

template <class T>
T Matrix<T>::multiplyElement(const Matrix<T>& factor, unsigned int row, unsigned int column) const
{
	T element = 0;
	for (unsigned int i = 1; i <= factor.getRowCount(); i++)
	{
		element += getElement(row, i)*factor.getElement(i, column);
	}
	return element;
}

template <class T>
Matrix<T> Matrix<T>::getProduct(const Matrix<T>& faktor) const
{
	auto result = Matrix<T>(getRowCount(), faktor.getColumnCount());
	multiply(result, faktor);
	return result;
}

template <class T>
Matrix<T> Matrix<T>::getProduct(const T&faktor) const
{
	auto result = Matrix<T>(getRowCount, getColumnCount);
	for (unsigned int i = 1; i <= getElementCount(); i++)
	{
		result[i] = this[i];
	}
	return result;
}

template <class T>
T Matrix<T>::getDeterminant()
{
	auto result = Matrix<T>(getRowCount, getColumnCount);
	return result;
}

template <class T>
void Matrix<T>::LuDecompose(Matrix<T>& P)
{
	auto isPRowWrong = P.getRowCount() != getRowCount();
	auto isPColumnWrong = P.getColumnCount() != getRowCount();
	if (isPColumnWrong || isPRowWrong)
		throw "P Matrix dimensions missmatch.";
	for (unsigned int column = 1; column <= getColumnCount(); column++)
	{
		//auto pivotRow = getMaxAbsOutOfColumnIndex(column); //methode ersetzen
		/*auto P_temp = ElementaryMatrixSwapRow(column, pivotRow);
		auto row_temp = getRow(pivotRow);
		setRow(pivotRow, getRow(column));
		setRow(column, row_temp);
		auto pivot = getElement(pivotRow, column);*/
		for (auto row = column; row<=getRowCount(); row++)
		{
			
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::getSolution(Matrix<T>)
{
	auto result = Matrix(4, 4);
	return result;
}

template <class T>
void Matrix<T>::solve(Matrix<T>)
{
}

template <class T>
void Matrix<T>::transpose(Matrix<T>& result) const
{
	auto resultRowMissmatch = result.getRowCount() != getColumnCount();
	auto resultColumnMissmatch = result.getColumnCount() != getRowCount();
	if (resultColumnMissmatch || resultRowMissmatch)
		throw "Result dimensions missmatch.";
	for (unsigned int i = 1; i <= result.getRowCount(); i++)
	{
		for (unsigned int j = 1; j <= result.getColumnCount(); j++)
		{
			result.setElement(i, j, getElement(j, i));
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::getTranspose() const
{
	auto result = Matrix(getColumnCount(), getRowCount());
	transpose(result);
	return result;
}

template <class T>
void Matrix<T>::invert(Matrix<T>& result)
{
	if (!isSquare)
		throw "Is not square matrix.";
}

template <class T>
Matrix<T> Matrix<T>::getInverse()
{
	auto result = Matrix(getColumnCount(), getRowCount());
	invert(result);
	return result;
}

template <class T>
T& Matrix<T>::operator[](const unsigned int index)
{
	if (index <= getElementCount())
		return elements_[index - 1];
	throw "Index out of bounds.";
}

template <class T>
std::ostream& operator<<(std::ostream& lhs, const Matrix<T>& rhs)
{
	for (unsigned int i = 1; i <= rhs.getRowCount(); i++)
	{
		for (unsigned int j = 1; j <= rhs.getColumnCount(); j++)
		{
			lhs << rhs.getElement(i, j) << "\t";
		}
		std::cout << std::endl;
	}
	return lhs;
}
