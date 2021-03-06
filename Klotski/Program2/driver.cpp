//
//Hua Rong Path (Project 2)
//By Kade Walter
//CS 438
//Due Date: 2/6/2018 at 12:30 pm
//This program solves Hua Rong (Klotski) Paths
//Performance:
//   BFS: HR4 and HR10 are working
//   DFS: Is implemented in a similar way to BFS, but none of the HR wanted to work... the algorith runs forever becuase it gets stuck in a loop that I couldnt figure out how to fix.
//

#include "stdafx.h"
#include "bfs.h"
#include "dfs.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <sstream>

using namespace std;

string GAME_BOARD[5][4];
string filename;
/*
GOAL BLOCK IS ALWAYS:
		0 0
		0 0
*/

int main()
{
	bfs bfs;
	dfs dfs;
	bool playing = true;
	while (playing)
	{
		string s;
		//gets the file for the gameboard
		cout << "Please enter the name of the puzzle. (no file extension)" << endl;
		cout << "Enter Q or Quit to terminate the program." << endl;
		cin >> s;
		//quits the program
		if ((s == "Q") || (s == "Quit"))
		{
			playing = false;
			break;
		}
		//error trap to remove the file extension if the user provided one, so we will always find the right file.
		filename = s + ".in";
		//creates the gameboard
		ifstream in(filename);
		string line;
		string data;
		int i = 0;
		while (!in.eof())
		{
			int j = 0;
			getline(in, line);
			stringstream ss(line);
			while (!ss.eof())
			{
				ss >> data;
				if (data == "b")
					data = " ";
				GAME_BOARD[i][j] = data;
				j++;
			}
			i++;
		}
		//ask for the algorithm to use
		cout << "\tSelect a search method:" << endl;
		cout << "\t1. Depth-first Search" << endl;
		cout << "\t2. Breadth-first Search" << endl;
		string choice;
		bool selection = false;
		while (!selection)
		{
			cin >> choice;
			if (choice == "1")
			{
				selection = true;
				dfs.dfsMain(s);
			}
			else if (choice == "2")
			{
				selection = true;
				bfs.bfsMain(s);
			}
			else
			{
				cout << "Invalid choice. Please try again." << endl;
			}
		}
		cout << "Done." << endl;
	}
    return 0;
}

