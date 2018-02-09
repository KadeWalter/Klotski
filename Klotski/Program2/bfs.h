#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

class bfs
{
public:
	void bfsMain(string name);
	void solver(ofstream &out);
	void print(ofstream &out);
	bool moveUp(int row, int col);
	bool moveDown(int row, int col);
	bool moveLeft(int row, int col);
	bool moveRight(int row, int col);
};

