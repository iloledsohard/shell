//platz fuer Kommentare
#include <iostream>
#include <string>
#include "Matrix.h"

using namespace std;

int main()
{
	auto A = Matrix<int>(2, 3);
	auto zaehler = 0;
	for (auto i = 1; i <= 2; i++)
	{
		for (auto j = 1; j <= 3; j++)
		{
			A.setElement(i, j, zaehler++);
		}
	}
	auto B = A.getTranspose();
	cout << A << endl;
	cout << B << endl;
	cout << A.getProduct(B);
	cin.get();
}

