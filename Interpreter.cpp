#include "Interpreter.h"
#include <string>

Interpreter::Interpreter()
{
}


Interpreter::~Interpreter()
{
}

void Interpreter::startUp()
{
	cout << "Interpreter initializiert" << endl;
	cout << "hier wird start-info stehen" << endl;
	cout << endl;
}

void Interpreter::read(string* line)
{
	cout << ">>";
	getline(cin, *line);
}

void Interpreter::write(const string& line)
{
	cout << line << endl;
}

int Interpreter::work(const string& line)
{
	if (line == "quit")
	{
		return 1;
	}
	if (line == "info")
	{
		startUp();
		return 0;
	}
	if (line == "cls")
	{
		system("cls");
		return 0;
	}
	write("Unknown command: "+line);
	return 0;
}

