#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <string.h>
#include <windows.h>

using namespace std;

class Sudoku
{
public:
	int *cells[9];
	bool dupe(int val)
	{
		return any_of(begin(cells), end(cells), [&](int *i)
					  { return *i == val; });
	};

	void print()
	{
		for (int i = 0; i < 9; i++)
		{
			cout << (*cells[i]) << " ";
		}
		cout << "\n";
	};
};

void setcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

class Tahta
{
public:
	int data[9][9] = {{0}};
	Sudoku rows[9];
	Sudoku cols[9];
	Sudoku sqrs[9];
	int (*fixed)[9][9];

	Tahta(int (*f)[9][9]) : fixed(f)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				rows[i].cells[j] = &(data[i][j]);
				cols[i].cells[j] = &(data[j][i]);
				sqrs[i].cells[j] = &(data[j / 3 + (i / 3) * 3][j % 3 + (i * 3) % 9]);
			}
		}
	};

	bool isDuplicate(int i, int j, int val)
	{
		rows[i].dupe(val) || cols[j].dupe(val) || sqrs[j / 3 + (i / 3) * 3].dupe(val);
		return rows[i].dupe(val) || cols[j].dupe(val) || sqrs[j / 3 + (i / 3) * 3].dupe(val);
	};

	void solve()
	{
		memcpy(&data, fixed, 9 * 9 * sizeof(int));
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if ((*fixed)[i][j] == 0)
				{
					int n = data[i][j];
					while (true)
					{
						n++;
						if (n > 9)
						{
							data[i][j] = 0;
							do
							{
								if (--j < 0)
								{
									j = 8;
									i--;
								}
							} while ((*fixed)[i][j] > 0);
							j--;
							break;
						}
						if (!isDuplicate(i, j, n))
						{
							data[i][j] = n;
							break;
						};
					}
				}
			}
		}
	};
	void print()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout << data[i][j] << " ";
				if (j == 2 || j == 5)
				{
					setcolor(12);
					cout << "| ";
					setcolor(7);
				}
			}
			cout << "\n";
			if (i == 2 || i == 5)
			{
				for (int k = 0; k < 22; k++)
				{
					setcolor(12);
					cout << "-";
					setcolor(7);
				}
				cout << "\n";
			}
		}
	};
};

int main(int, const char **argv)
{
	int hard[9][9] = {{0, 0, 2, 0, 0, 0, 0, 0, 0},
					  {0, 0, 0, 0, 0, 0, 6, 9, 0},
					  {3, 8, 0, 9, 0, 0, 0, 0, 0},
					  {0, 0, 3, 0, 6, 0, 0, 0, 0},
					  {0, 1, 0, 2, 0, 0, 0, 0, 4},
					  {0, 0, 7, 0, 4, 0, 5, 0, 0},
					  {0, 0, 1, 0, 5, 0, 0, 0, 0},
					  {0, 7, 4, 0, 0, 0, 0, 0, 2},
					  {0, 2, 0, 7, 0, 0, 0, 8, 0}};
	Tahta oyun(&hard);
	clock_t basla;
	basla = clock();
	oyun.solve();
	cout << " Time: " << (clock() - basla) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
	oyun.print();
	return 0;
}