//
//Breadth first search algorith
//Finds the first empty space on the board and tries to move the highest numbered block into it.. repeats and if it cant move a block to that space, it tries again with the other blank space
//By Kade Walter
//

#include "stdafx.h"
#include "bfs.h"
#include "driver.h"

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
#include <vector>

using namespace std;

extern string GAME_BOARD[5][4];
int c = 0;

void bfs::bfsMain(string name)
{
	ofstream out(name + "BFS.out");
	//print the initial state (0 moves)
	bfs::print(out);
	bfs::solver(out);

	out << "This solution has " << c - 1 << " steps to solve." << endl;
	out.close();
}

void bfs::solver(ofstream &out)
{
	string lastUsed;
	bool solution = false;
	string surrounding[4];
	string p, s, e, w;
	vector<string> q;
	while (solution == false)
	{
		int i, j;
		if ((GAME_BOARD[3][1] == "0") && (GAME_BOARD[3][2] == "0") && (GAME_BOARD[4][1] == "0") && (GAME_BOARD[4][2] == "0"))
		{
			solution = true;
			break;
		}
		else
		{
			for (i = 0; i <= 4; i++)
			{
				for (j = 0; j < 3; j++)
				{
					if (GAME_BOARD[i][j] == " ")
					{
						break;
					}
				}
				if (GAME_BOARD[i][j] == " ")
				{
					break;
				}
			}
			//find the pieces on all 4 sides of the blank to see which is highest
			if (j > 0)
				surrounding[0] = GAME_BOARD[i][j - 1];
			else
				surrounding[0] = "-100";
			if (j < 3)
				surrounding[1] = GAME_BOARD[i][j + 1];
			else
				surrounding[1] = "-100";
			if (i > 0)
				surrounding[2] = GAME_BOARD[i - 1][j];
			else
				surrounding[2] = "-101";
			if (i < 4)
				surrounding[3] = GAME_BOARD[i + 1][j];
			else
				surrounding[3] = "-101";
			if (surrounding[0] == "0")
				q.push_back(surrounding[0]);
			else if (surrounding[1] == "0")
				q.push_back(surrounding[1]);
			else if (surrounding[2] == "0")
				q.push_back(surrounding[2]);
			else if (surrounding[3] == "0")
				q.push_back(surrounding[3]);
			if (q.size() == 0)
			{
				for (int k = 0; k < 4; k++)
				{
					q.push_back(surrounding[k]);
				}
			}
			else
			{
				for (int k = 0; k < 4; k++)
				{
					if (surrounding[k] == q.front())
					{

					}
					else
					{
						q.push_back(surrounding[k]);
					}
				}
			}
			//order the numbers and put them in q
			bool sorted = false;
			while (sorted == false)
			{
				if (q[0] < q[1] && q[0] != "0")
				{
					string temp = q[0];
					q[0] = q[1];
					q[1] = temp;
				}
				if (q[1] < q[2])
				{
					string temp = q[1];
					q[1] = q[2];
					q[2] = temp;
				}
				if (q[2] < q[3])
				{
					string temp = q[2];
					q[2] = q[3];
					q[3] = temp;
				}
				if (q[0] > q[1] && q[1] > q[2] && q[2] > q[3])
				{
					sorted = true;
				}
				else if (q[0] == "0")
				{
					if (q[1] > q[2] && q[2] > q[3])
					{
						sorted = true;
					}
				}
			}
			
			//first, find the location of the highest numbered piece
			bool upCheck, downCheck, rightCheck, leftCheck, moved, pieceCheck;
			moved = upCheck = downCheck = rightCheck = leftCheck = pieceCheck = false;
			string piece = q.front();
			if (piece == lastUsed)
			{
				string temp = piece;
				for (int k = 0; k < q.size() - 1; k++)
				{
					q[k] = q[k + 1];
				}
				int qSize = q.size();
				q[qSize - 1] = temp;
				q.pop_back();
				piece = q.front();
			}
			while (moved == false)
			{
				while (pieceCheck == false)
				{
					if (piece == "-100" || piece == "-101")
					{
						if (q.size() > 1)
						{
							string temp = piece;
							for (int k = 0; k < q.size() - 1; k++)
							{
								q[k] = q[k + 1];
							}
							int qSize = q.size();
							q[qSize - 1] = temp;
							q.pop_back();
							piece = q.front();
						}
					}
					else
						pieceCheck = true;
				}
				if (upCheck == true || leftCheck == true || downCheck == true || rightCheck == true)
				{
					if (q.size() > 1)
					{
						string temp = piece;
						for (int k = 0; k < q.size() - 1; k++)
						{
							q[k] = q[k + 1];
						}
						int qSize = q.size();
						q[qSize - 1] = temp;
						q.pop_back();
						piece = q.front();
					}
					else
					{
						q.clear();
						for (i; i <= 4; i++)
						{
							for (j = j + 1; j < 3; j++)
							{
								if (GAME_BOARD[i][j] == " ")
								{
									break;
								}
							}
							if (GAME_BOARD[i][j] == " ")
							{
								break;
							}
						}
						//find the pieces on all 4 sides of the blank to see which is highest
						if (j > 0)
							surrounding[0] = GAME_BOARD[i][j - 1];
						else
							surrounding[0] = "-100";
						if (j < 3)
							surrounding[1] = GAME_BOARD[i][j + 1];
						else
							surrounding[1] = "-100";
						if (i > 0)
							surrounding[2] = GAME_BOARD[i - 1][j];
						else
							surrounding[2] = "-101";
						if (i < 4)
							surrounding[3] = GAME_BOARD[i + 1][j];
						else
							surrounding[3] = "-101";
						if (surrounding[0] == "0")
							q.push_back(surrounding[0]);
						else if (surrounding[1] == "0")
							q.push_back(surrounding[1]);
						else if (surrounding[2] == "0")
							q.push_back(surrounding[2]);
						else if (surrounding[3] == "0")
							q.push_back(surrounding[3]);
						if (q.size() == 0)
						{
							for (int k = 0; k < 4; k++)
							{
								q.push_back(surrounding[k]);
							}
						}
						else
						{
							for (int k = 0; k < 4; k++)
							{
								if (surrounding[k] == q.front())
								{

								}
								else
								{
									q.push_back(surrounding[k]);
								}
							}
						}
						//order the numbers and put them in q
						bool sorted = false;
						while (sorted == false)
						{
							if (q[0] < q[1] && q[0] != "0")
							{
								string temp = q[0];
								q[0] = q[1];
								q[1] = temp;
							}
							if (q[1] < q[2])
							{
								string temp = q[1];
								q[1] = q[2];
								q[2] = temp;
							}
							if (q[2] < q[3])
							{
								string temp = q[2];
								q[2] = q[3];
								q[3] = temp;
							}
							if (q[0] > q[1] && q[1] > q[2] && q[2] > q[3])
							{
								sorted = true;
							}
							else if (q[0] == "0")
							{
								if (q[1] > q[2] && q[2] > q[3])
								{
									sorted = true;
								}
							}
						}
						upCheck = downCheck = leftCheck = rightCheck = false;
						piece = q.front();
					}

				}
				//if the piece is below, move it up
				if (piece == surrounding[3] && upCheck == false && piece != lastUsed)
				{
					moved = moveUp(i + 1, j);
					upCheck = true;
				}
				//if the pieve is to the left, move it right
				else if (piece == surrounding[1] && leftCheck == false && piece != lastUsed)
				{
					moved = moveLeft(i, j + 1);
					leftCheck = true;
				}
				//if the piece is above, move it down
				else if (piece == surrounding[2] && downCheck == false && piece != lastUsed)
				{
					moved = moveDown(i - 1, j);
					downCheck = true;
				}
				//if the piece is to the right, move it left
				else if (piece == surrounding[0] && rightCheck == false && piece != lastUsed)
				{
					moved = moveRight(i, j - 1);
					rightCheck = true;
				}
				
				
			
			}
			lastUsed = piece;
			print(out);
			q.clear();
		}
	}
}

bool bfs::moveUp(int row, int col)
{
	int pieceSize = 1;
	string piece = GAME_BOARD[row][col];
	//if the piece is the winning piece
	//if the piece is the winning piece
	if (piece == "0")
	{
		pieceSize = 2;
		//check if 0 is to the left
		if (col > 0 && col < 3)
		{
			//we know we pull down and the piece is to the left and up
			if (GAME_BOARD[row][col - 1] == piece)
			{
				if (GAME_BOARD[row - 1][col - 1] == " ")
				{
					string temp = GAME_BOARD[row - 1][col];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row - i][col] = GAME_BOARD[row + i][col];
						GAME_BOARD[row - i][col - 1] = GAME_BOARD[row + i][col - 1];
					}
					GAME_BOARD[row + 1][col] = temp;
					GAME_BOARD[row + 1][col - 1] = temp;
					return true;
				}
				else
					return false;
			}
			else if (GAME_BOARD[row][col + 1] == piece)
			{
				if (GAME_BOARD[row - 1][col + 1] == " ")
				{
					string temp = GAME_BOARD[row - 1][col];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row - i][col] = GAME_BOARD[row + i][col];
						GAME_BOARD[row - i][col + 1] = GAME_BOARD[row + i][col + 1];
					}
					GAME_BOARD[row + 1][col] = temp;
					GAME_BOARD[row + 1][col + 1] = temp;
					return true;
				}
				else
					return false;
			}
		}
		else if (col = 0)
		{
			if (GAME_BOARD[row - 1][col + 1] == " ")
			{
				string temp = GAME_BOARD[row + 1][col];
				for (int i = 0; i < pieceSize; i++)
				{
					GAME_BOARD[row - i][col] = GAME_BOARD[row + i][col];
					GAME_BOARD[row - i][col + 1] = GAME_BOARD[row + i][col + 1];
				}
				GAME_BOARD[row + 1][col] = temp;
				GAME_BOARD[row + 1][col + 1] = temp;
				return true;
			}
			else
				return false;
			
		}
		else if (col = 3)
		{
			if (GAME_BOARD[row - 1][col - 1] == " ")
			{
				string temp = GAME_BOARD[row - 1][col];
				for (int i = 0; i < pieceSize; i++)
				{
					GAME_BOARD[row - i][col] = GAME_BOARD[row + i][col];
					GAME_BOARD[row - i][col - 1] = GAME_BOARD[row + i][col - 1];
				}
				GAME_BOARD[row + 1][col] = temp;
				GAME_BOARD[row + 1][col - 1] = temp;
				return true;
			}
			else
				return false;
		}

	}
	//check piece down, right, and left
	//if piece is long right or left, return false for no move
	else
	{
		//piece goes to the right
		if (col < 3)
		{
			if (GAME_BOARD[row - 1][col + 1] == " ")
			{
				if (GAME_BOARD[row][col + 1] == piece)
				{
					pieceSize = 2;
					for (int k = 0; k < pieceSize; k++)
					{
						string tempEmpty = GAME_BOARD[row - 1][col + k];
						GAME_BOARD[row - 1][col + k] = GAME_BOARD[row][col + k];
						GAME_BOARD[row][col + k] = tempEmpty;
					}
					return true;
				}
			}
			else 
			{
				if (GAME_BOARD[row][col + 1] == piece)
				{
					return false;
				}
			}
		}
		//piece goes to the left
		if (col > 0)
		{
			if (GAME_BOARD[row - 1][col - 1] == " ")
			{
				if (GAME_BOARD[row][col - 1] == piece)
				{
					pieceSize = 2;
					for (int k = 0; k < pieceSize; k++)
					{
						string tempEmpty = GAME_BOARD[row - 1][col - k];
						GAME_BOARD[row - 1][col - k] = GAME_BOARD[row][col - k];
						GAME_BOARD[row][col - k] = tempEmpty;
					}
					return true;
				}
			}
			else
			{
				if (GAME_BOARD[row][col - 1] == piece)
				{
					return false;
				}
			}
		}
		//piece goes down
			if (row < 4)
			{
				if (GAME_BOARD[row + 1][col] == piece)
				{
					pieceSize = 2;
				}
			}
			//move the piece up
			for (int k = 0; k < pieceSize; k++)
			{
				GAME_BOARD[(row - 1 + k)][col] = GAME_BOARD[row][col];
			}
			//fill in the hole
			//fill in the hole
			if (pieceSize > 1)
			{
				GAME_BOARD[(row +1)][col] = " ";
			}
			else
			{
				GAME_BOARD[row][col] = " ";
			}
			return true;
		
	}
	
}

bool bfs::moveDown(int row, int col)
{
	int pieceSize = 1;
	string piece = GAME_BOARD[row][col];
	//if the piece is the winning piece
	if (piece == "0")
	{
		pieceSize = 2;
		//check if 0 is to the left
		if (col > 0 && col < 3)
		{
			//we know we pull down and the piece is to the left and up
			if (GAME_BOARD[row][col - 1] == piece)
			{
				if (GAME_BOARD[row + 1][col - 1] == " ")
				{
					string temp = GAME_BOARD[row + 1][col];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row + 1 - i][col] = GAME_BOARD[row - i][col];
						GAME_BOARD[row + 1 - i][col - 1] = GAME_BOARD[row - i][col - 1];
					}
					GAME_BOARD[row - 1][col] = temp;
					GAME_BOARD[row - 1][col - 1] = temp;
					return true;
				}
				else
					return false;
			}
			else if (GAME_BOARD[row][col + 1] == piece)
			{
				if (GAME_BOARD[row + 1][col + 1] == " ")
				{
					string temp = GAME_BOARD[row + 1][col];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row + 1 - i][col] = GAME_BOARD[row - i][col];
						GAME_BOARD[row + 1 - i][col + 1] = GAME_BOARD[row - i][col + 1];
					}
					GAME_BOARD[row - 1][col] = temp;
					GAME_BOARD[row - 1][col + 1] = temp;
					return true;
				}
				else
					return false;
			}
		}
		else if (col = 0)
		{
			if (GAME_BOARD[row][col + 1] == piece)
			{
				if (GAME_BOARD[row + 1][col + 1] == " ")
				{
					string temp = GAME_BOARD[row + 1][col];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row + 1 - i][col] = GAME_BOARD[row - i][col];
						GAME_BOARD[row + 1 - i][col + 1] = GAME_BOARD[row - i][col + 1];
					}
					GAME_BOARD[row - 1][col] = temp;
					GAME_BOARD[row - 1][col + 1] = temp;
					return true;
				}
				else
					return false;
			}
		}
		else if (col = 3)
		{
			if (GAME_BOARD[row][col - 1] == piece)
			{
				if (GAME_BOARD[row + 1][col - 1] == " ")
				{
					string temp = GAME_BOARD[row + 1][col];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row - i][col] = GAME_BOARD[row - i][col];
						GAME_BOARD[row - i][col - 1] = GAME_BOARD[row - i][col - 1];
					}
					GAME_BOARD[row - 1][col] = temp;
					GAME_BOARD[row - 1][col - 1] = temp;
					return true;
				}
				else
					return false;
			}
		}
		
	}
	//check piece down, right, and left
	//if piece is long right or left, return false for no move
	else
	{
		//piece goes to the right
		if (col < 3)
		{
			if (GAME_BOARD[row + 1][col + 1] == " ")
			{
				if (GAME_BOARD[row][col + 1] == piece)
				{
					pieceSize = 2;
					for (int k = 0; k < pieceSize; k++)
					{
						string tempEmpty = GAME_BOARD[row + 1][col + k];
						GAME_BOARD[row + 1][col + k] = GAME_BOARD[row][col + k];
						GAME_BOARD[row][col + k] = tempEmpty;
					}
					return true;
				}
			}
			else
			{
				if (GAME_BOARD[row][col + 1] == piece)
				{
					return false;
				}
			}
		}
		//piece goes to the left
		if (col > 0)
		{
			if (GAME_BOARD[row + 1][col - 1] == " ")
			{
				if (GAME_BOARD[row][col - 1] == piece)
				{
					pieceSize = 2;
					for (int k = 0; k < pieceSize; k++)
					{
						string tempEmpty = GAME_BOARD[row + 1][col - k];
						GAME_BOARD[row + 1][col - k] = GAME_BOARD[row][col - k];
						GAME_BOARD[row][col - k] = tempEmpty;
					}
					return true;
				}
			}
			else
			{
				if (GAME_BOARD[row][col - 1] == piece)
				{
					return false;
				}
			}
		}
		//piece goes down
		if (row > 0)
		{
			if (GAME_BOARD[row - 1][col] == piece)
			{
				pieceSize = 2;
			}
		}
		//move the piece down
		//fill in the hole
		if (pieceSize > 1)
		{
			GAME_BOARD[row][col] = piece;
			GAME_BOARD[row + 1][col] = piece;
			GAME_BOARD[row - 1][col] = " ";
		}
		else
		{
			GAME_BOARD[row + 1][col] = piece;
			GAME_BOARD[row][col] = " ";
		}
		return true;

	}

}

bool bfs::moveLeft(int row, int col)
{
	int pieceSize = 1;
	string piece = GAME_BOARD[row][col];
	//if the piece is the winning piece
	//if the piece is the winning piece
	if (piece == "0")
	{
		pieceSize = 2;
		//check if 0 is to the left
		if (row > 0 && row < 4)
		{
			//we know we pull down and the piece is to the left and up
			if (GAME_BOARD[row - 1][col] == piece)
			{
				if (GAME_BOARD[row - 1][col - 1] == " ")
				{
					string temp = GAME_BOARD[row][col - 1];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row][col - i] = GAME_BOARD[row][col + i];
						GAME_BOARD[row - 1][col- i] = GAME_BOARD[row - 1][col + i];
					}
					GAME_BOARD[row][col + 1] = temp;
					GAME_BOARD[row - 1][col + 1] = temp;
					return true;
				}
				else
					return false;
			}
			else if (GAME_BOARD[row + 1][col] == piece)
			{
				if (GAME_BOARD[row + 1][col - 1] == " ")
				{
					string temp = GAME_BOARD[row][col - 1];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row][col - i] = GAME_BOARD[row][col + i];
						GAME_BOARD[row + 1][col - i] = GAME_BOARD[row + 1][col + i];
					}
					GAME_BOARD[row][col + 1] = temp;
					GAME_BOARD[row + 1][col + 1] = temp;
					return true;
				}
				else
					return false;
			}
		}
		else if (row = 0)
		{
			if (GAME_BOARD[row + 1][col] == piece)
			{
				if (GAME_BOARD[row + 1][col - 1] == " ")
				{
					string temp = GAME_BOARD[row][col - 1];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row][col - i] = GAME_BOARD[row][col + i];
						GAME_BOARD[row + 1][col - i] = GAME_BOARD[row + 1][col + i];
					}
					GAME_BOARD[row][col + 1] = temp;
					GAME_BOARD[row + 1][col + 1] = temp;
					return true;
				}
				else
					return false;
			}

		}
		else if (row = 4)
		{
			if (GAME_BOARD[row - 1][col] == piece)
			{
				if (GAME_BOARD[row - 1][col - 1] == " ")
				{
					string temp = GAME_BOARD[row][col - 1];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row][col - i] = GAME_BOARD[row][col + i];
						GAME_BOARD[row - 1][col - i] = GAME_BOARD[row - 1][col + i];
					}
					GAME_BOARD[row][col + 1] = temp;
					GAME_BOARD[row - 1][col + 1] = temp;
					return true;
				}
				else
					return false;
			}
		}

	}
	//check piece down, right, and left
	//if piece is long right or left, return false for no move
	else
	{
		//check down
		if (row < 4)
		{
			if (GAME_BOARD[row + 1][col - 1] == " ")
			{
				if (GAME_BOARD[row + 1][col] == piece)
				{
					pieceSize = 2;
					for (int k = 0; k < pieceSize; k++)
					{
						string tempEmpty = GAME_BOARD[row + k][col - 1];
						GAME_BOARD[row + k][col - 1] = GAME_BOARD[row + k][col];
						GAME_BOARD[row + k][col] = tempEmpty;
					}
					return true;
				}
			}
			else
			{
				if (GAME_BOARD[row + 1][col] == piece)
				{
					return false;
				}
			}
		}
		//check up
		if (row > 0)
		{
			if (GAME_BOARD[row - 1][col - 1] == " ")
			{
				if (GAME_BOARD[row - 1][col] == piece)
				{
					pieceSize = 2;
					for (int k = 0; k < pieceSize; k++)
					{
						string tempEmpty = GAME_BOARD[row - k][col - 1];
						GAME_BOARD[row - k][col - 1] = GAME_BOARD[row - k][col];
						GAME_BOARD[row - k][col] = tempEmpty;
					}
					return true;
				}
			}
			else
			{
				if (GAME_BOARD[row - 1][col] == piece)
				{
					return false;
				}
			}
		}
		//piece goes down
		if (col < 3)
		{
			if (GAME_BOARD[row][col + 1] == piece)
			{
				pieceSize = 2;
			}
		}
		if (pieceSize > 1)
		{
			GAME_BOARD[row][col] = piece;
			GAME_BOARD[row][col - 1] = piece;
			GAME_BOARD[row][col + 1] = " ";
		}
		else
		{
			GAME_BOARD[row][col - 1] = piece;
			GAME_BOARD[row][col] = " ";
		}
	}

}

bool bfs::moveRight(int row, int col)
{
	int pieceSize = 1;
	string piece = GAME_BOARD[row][col];
	//if the piece is the winning piece
	//if the piece is the winning piece
	if (piece == "0")
	{
		pieceSize = 2;
		//check if 0 is to the left
		if (row > 0 && row < 4)
		{
			//we know we pull down and the piece is to the left and up
			if (GAME_BOARD[row - 1][col] == piece)
			{
				if (GAME_BOARD[row - 1][col + 1] == " ")
				{
					string temp = GAME_BOARD[row][col + 1];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row][col + i] = GAME_BOARD[row][col - i];
						GAME_BOARD[row - 1][col + i] = GAME_BOARD[row - 1][col - i];
					}
					GAME_BOARD[row][col - 1] = temp;
					GAME_BOARD[row - 1][col - 1] = temp;
					return true;
				}
				else
					return false;
			}
			else if (GAME_BOARD[row + 1][col] == piece)
			{
				if (GAME_BOARD[row + 1][col + 1] == " ")
				{
					string temp = GAME_BOARD[row][col + 1];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row][col + i] = GAME_BOARD[row][col - i];
						GAME_BOARD[row + 1][col + i] = GAME_BOARD[row + 1][col - i];
					}
					GAME_BOARD[row][col - 1] = temp;
					GAME_BOARD[row + 1][col - 1] = temp;
					return true;
				}
				else
					return false;
			}
		}
		else if (row = 0)
		{
			if (GAME_BOARD[row + 1][col] == piece)
			{
				if (GAME_BOARD[row + 1][col + 1] == " ")
				{
					string temp = GAME_BOARD[row][col + 1];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row][col + i] = GAME_BOARD[row][col - i];
						GAME_BOARD[row + 1][col + i] = GAME_BOARD[row + 1][col - i];
					}
					GAME_BOARD[row][col - 1] = temp;
					GAME_BOARD[row + 1][col - 1] = temp;
					return true;
				}
				else
					return false;
			}
		}
		else if (row = 4)
		{
			if (GAME_BOARD[row - 1][col] == piece)
			{
				if (GAME_BOARD[row - 1][col + 1] == " ")
				{
					string temp = GAME_BOARD[row][col + 1];
					for (int i = 0; i < pieceSize; i++)
					{
						GAME_BOARD[row][col + i] = GAME_BOARD[row][col - i];
						GAME_BOARD[row - 1][col + i] = GAME_BOARD[row - 1][col - i];
					}
					GAME_BOARD[row][col - 1] = temp;
					GAME_BOARD[row - 1][col - 1] = temp;
					return true;
				}
				else
					return false;
			}
		}

	}
	//check piece down, right, and left
	//if piece is long right or left, return false for no move
	else
	{
		//check down
		if (row < 4)
		{
			if (GAME_BOARD[row + 1][col + 1] == " ")
			{
				if (GAME_BOARD[row + 1][col] == piece)
				{
					pieceSize = 2;
					for (int k = 0; k < pieceSize; k++)
					{
						string tempEmpty = GAME_BOARD[row + k][col + 1];
						GAME_BOARD[row + k][col + 1] = GAME_BOARD[row + k][col];
						GAME_BOARD[row + k][col] = tempEmpty;
					}
					return true;
				}
			}
			else
			{
				if (GAME_BOARD[row + 1][col] == piece)
				{
					return false;
				}
			}
		}
		//check up
		if (row > 0)
		{
			if (GAME_BOARD[row - 1][col + 1] == " ")
			{
				if (GAME_BOARD[row - 1][col] == piece)
				{
					pieceSize = 2;
					for (int k = 0; k < pieceSize; k++)
					{
						string tempEmpty = GAME_BOARD[row - k][col + 1];
						GAME_BOARD[row - k][col + 1] = GAME_BOARD[row - k][col];
						GAME_BOARD[row - k][col] = tempEmpty;
					}
					return true;
				}
			}
			else
			{
				if (GAME_BOARD[row - 1][col] == piece)
				{
					return false;
				}
			}
		}
		//piece goes down
		if (col > 0)
		{
			if (GAME_BOARD[row][col - 1] == piece)
			{
				pieceSize = 2;
			}
		}
		//move the piece up
		for (int k = 0; k < pieceSize; k++)
		{
			GAME_BOARD[row][col + k] = GAME_BOARD[row][col];
		}
		//fill in the hole
		if (pieceSize > 1)
		{
			GAME_BOARD[row][(col - 1)] = " ";
		}
		else
		{
			GAME_BOARD[row][col] = " ";
		}
		return true;

	}

}

void bfs::print(ofstream &out)
{
	//prints the move number
	out << c << endl;
	c++;
	//prints the current state of the board
	for (int i = 0; i < 5; i++)
	{
		out << "\t";
		for (int j = 0; j < 4; j++)
		{
			out << GAME_BOARD[i][j] << " ";
		}
		out << endl;
	}
	out << endl;
}