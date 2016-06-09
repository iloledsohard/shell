#pragma once

template<class T>
class Matrix
{
public:
	Matrix(unsigned int, unsigned int);
	explicit Matrix(unsigned int);
	~Matrix();
	unsigned int getRowCount() const;
	unsigned int getColumnCount() const;
	void setElement(unsigned int, unsigned int, T);
	T getElement(unsigned int, unsigned int) const;
	Matrix<T> multiply(const Matrix<T>&,const Matrix<T>&);

private:
	unsigned int rows_;
	unsigned int columns_;
	T** elements_;
};

template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns)
{
	rows_ = rows;
	columns_ = columns;
	elements_ = new T*[rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		elements_[i] = new T[columns];
	}
}

template <class T>
Matrix<T>::Matrix(unsigned int rows)
{
	rows_ = rows;
	columns_ = 1;
	elements_ = new T*[rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		elements_[i] = new T[1];
	}
}

template <class T>
Matrix<T>::~Matrix()
{
	for (unsigned int i = 0; i < rows_; i++)
	{
		delete[] elements_[i];
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
	return rows_;
}

template <class T>
void Matrix<T>::setElement(unsigned int row, unsigned int column, T value)
{
	elements_[row][column] = value;
}

template <class T>
T Matrix<T>::getElement(unsigned int row, unsigned int column) const
{
	return elements_[row][column];
}

template <class T>
Matrix<T> Matrix<T>::multiply(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	if (lhs.getColumnCount()!=rhs.getRowCount())
	{
		throw "Dimensions Missmatch";
	}
	auto result = Matrix<T>(lhs.getRowCount(), rhs.getColumnCount());
	for (unsigned int i = 0; i < lhs.getRowCount(); i++)
	{
		for (unsigned int j = 0; j < rhs.getColumnCount(); j++)
		{
			T element = 0;
			for (unsigned int k = 0; k < lhs.getRowCount(); k++)
			{
				element += lhs.getElement(i, k)*rhs.getElement(k, j);
			}
			result.setElement(i, j, element);
		}
	}
	return result;
}
