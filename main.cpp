//platz fuer Kommentare
#include <iostream>
#include <string>
#include "Matrix.h"

using namespace std;

int main()
{
	auto A = Matrix<int>(2, 3);
	int zaehler = 0;
	for (auto i = 0; i < 2; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			A.setElement(i, j, zaehler++);
		}
	}
	auto B = A.multiply(A, A);
	for (auto i = 0; i < 2; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			cout << B.getElement(i, j) << endl;
		}
	}
	cin.get();
}

