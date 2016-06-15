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
	unsigned int getRowCount() const;
	unsigned int getColumnCount() const;
	unsigned int getElementCount() const;
	void setElement(unsigned int, unsigned int, T);
	T getElement(unsigned int, unsigned int) const;
	void multiply(Matrix<T>&, const Matrix<T>&);
	void multiply(Matrix<T>&, const T&);
	Matrix<T> getProduct(const Matrix<T>&);
	Matrix<T> getProduct(const T&);
	void transpose(Matrix<T>&);
	Matrix<T> getTranspose();
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
	elements_ = new T[rows*columns]();
}

template <class T>
Matrix<T>::Matrix(unsigned int rows)
{
	rows_ = rows;
	columns_ = 1;
	elements_ = new T[rows]();
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& obj)
{
	std::cout << "Copy constuctor is used!" << std::endl;
	rows_ = obj.rows_;
	columns_ = obj.columns_;
	elements_ = new T[obj.rows_*obj.columns_]();
	for (auto i = 0; i < obj.rows_*obj.columns_; i++)
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
void Matrix<T>::setElement(unsigned int row, unsigned int column, T value)
{
	if (0 < row && row <= getRowCount() && 0 < column && column <= getColumnCount())
		elements_[(column - 1)*getRowCount() + row - 1] = value;
	else
		throw "Index out of bounds.";
}

template <class T>
T Matrix<T>::getElement(unsigned int row, unsigned int column) const
{
	if (0 < row && row <= getRowCount() && 0 < column && column <= getColumnCount())
		return elements_[(column - 1)*getRowCount() + row - 1];
	throw "Index out of bounds.";
}

template <class T>
void Matrix<T>::multiply(Matrix<T>& result, const Matrix<T>& faktor)
{
	if (getColumnCount() != faktor.getRowCount())
	{
		throw "Inner dimensions missmatch.";
	}
	auto rowsMissmatch = result.getRowCount() != getRowCount();
	auto columnsMissmatch = result.getColumnCount() != faktor.getColumnCount();
	if (rowsMissmatch || columnsMissmatch)
	{
		throw "Result dimensions missmatch.";
	}
	for (unsigned int i = 1; i <= getRowCount(); i++)
	{
		for (unsigned int j = 1; j <= faktor.getColumnCount(); j++)
		{
			T element = 0;
			for (unsigned int k = 1; k <= faktor.getRowCount(); k++)
			{
				element += getElement(i, k)*faktor.getElement(k, j);
			}
			result.setElement(i, j, element);
		}
	}
}

template <class T>
void Matrix<T>::multiply(Matrix<T>& result, const T& faktor)
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
Matrix<T> Matrix<T>::getProduct(const Matrix<T>& faktor)
{
	auto result = Matrix<T>(getRowCount(), faktor.getColumnCount());
	multiply(result, faktor);
	return result;
}

template <class T>
Matrix<T> Matrix<T>::getProduct(const T&faktor)
{
	auto result = Matrix<T>(getRowCount, getColumnCount);
	for (unsigned int i = 1; i <= getElementCount(); i++)
	{
		result[i] = this[i];
	}
	return result;
}

template <class T>
void Matrix<T>::transpose(Matrix<T>& result)
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
Matrix<T> Matrix<T>::getTranspose()
{
	auto result = Matrix(getColumnCount(), getRowCount());
	transpose(result);
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
