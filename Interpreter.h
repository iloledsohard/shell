#pragma once
#include <iostream>
using namespace std;


class Interpreter
{
public:
	Interpreter();
	~Interpreter();

	static void startUp();
	static void read(string* line);
	static void write(const string &line);
	static int work(const string &line);
};