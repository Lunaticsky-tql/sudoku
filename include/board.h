#ifndef _BOOARD_
#define _BOOARD_

#include<vector>
#include<time.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<string.h>

using namespace std;

#endif

class Board {
public:
	int pos[9][9];

	Board() {
		memset(pos, 0, sizeof(pos));
	}

	void initBoard() {
		memset(pos, 0, sizeof(pos));
	}
	void printBoard()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout << pos[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}

	void testBoard()
	{
		int i, j, k, l, m;
		for (i = 0; i < 9; i++)
		{
			for (j = 1; j <= 9; j++)
			{
				for (k = 0; k < 9; k++)
				{
					if (pos[i][k] == j)
						break;
				}
				if (k == 9)
				{
					cout << "Board Error:Raw Error\n";
					return;
				}
					

				for (l = 0; l < 9; l++)
				{
					if (pos[l][i] == j)
						break;
				}
				if (l == 9)
				{
					cout << "Board Error:Col Error\n";
					return;
				}
					
			}

		}

		for (i = 0; i < 9; i += 3)
		{
			for (j = 0; j < 9; j += 3)
			{
				for (k = 1; k <= 9; k++)
				{
					for (l = i; l < i + 3; l++)
					{
						for (m = j; m < j + 3; m++)
						{
							if (pos[l][m] == k)
								break;
						}
						if (pos[l][m] == k)
							break;
					}
					if (l == i + 3)
					{
						cout << "Board Error:3*3 Error\n";
						return;
					}
						
				}
			}
		}

		cout << "Test Success!" << endl;
	}
};
