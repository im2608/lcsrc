#include "sudoku.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include<cstdlib>
#include <vector>
#include <map>
#include <queue>
#include<cmath>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <utility>
#include <numeric>
#include <math.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>
#include <bitset>
#include <random>
#include <cmath>

using namespace std;

//https://leetcode.com/problems/sudoku-solver/description/
//https://baike.baidu.com/item/数独技巧/3533466
/*
*
5 3 4 | . 7 . | . . .
6 7 2 | 1 9 5 | . . .
1 9 8 | . . . | . 6 .
------+-------+------
8 . . | . 6 . | . . 3
4 . . | 8 . 3 | . . 1
7 . . | . 2 . | . . 6
------+-------+------
. 6 . | . . . | 2 8 .
. . . | 4 1 9 | . . 5
. . . | . 8 . | . 7 9


5 3 . | . 7 . | . . .
6 . . | 1 9 5 | . . .
. 9 8 | . . . | . 6 .
------+-------+------
8 . . | . 6 . | . . 3
4 . . | 8 . 3 | . . 1
7 . . | . 2 . | . . 6
------+-------+------
. 6 . | . . . | 2 8 .
. . . | 4 1 9 | . . 5
. . . | . 8 . | . 7 9

5     3       (1 2 4)
6     (2 4 7) (2 4 7)
(1 2) 9       8

2 3 4 6 8
(2 6) 7       (2 4 6 8)
1     9       5
(2 3) (2 3 4) (2 4)


. 9 8
. . . . . 6
5 4 1

(2 3 6 7) 9       8
(2 3 7)   (2 3 7) (2 3 7) . . 6
5         4       1
*/

unordered_map<int, vector<int>> beingpurgedSubmatirx;
vector<int> &get_beingpurgedSubmatirx(int matrixidx)
{
	/*
	* 1 2 3
	* 4 5 6
	* 7 8 9
	*/
	static bool isinited = false;
	if (!isinited)
	{
		beingpurgedSubmatirx[1] = vector<int>({ 2,3,4,6 });
		beingpurgedSubmatirx[2] = vector<int>({ 1,3,5,8 });
		beingpurgedSubmatirx[3] = vector<int>({ 1,2,6,9 });
		beingpurgedSubmatirx[4] = vector<int>({ 1,7,5,6 });
		beingpurgedSubmatirx[5] = vector<int>({ 2,8,4,6 });
		beingpurgedSubmatirx[6] = vector<int>({ 3,9,4,5 });
		beingpurgedSubmatirx[7] = vector<int>({ 1,4,8,9 });
		beingpurgedSubmatirx[8] = vector<int>({ 2,5,7,9 });
		beingpurgedSubmatirx[9] = vector<int>({ 3,6,7,8 });
		isinited = true;
	}

	return beingpurgedSubmatirx[matrixidx];
}

void findonesolution_helper(vector<unordered_set<char>>& solutioncandidates, int idx, vector<char> usedchar, vector<vector<char>>& verifiedsolutions)
{
	if (idx >= solutioncandidates.size())
	{
		verifiedsolutions.push_back(usedchar);
		return;
	}

	for (char c : solutioncandidates[idx])
	{
		vector<char>::iterator itor(usedchar.begin());
		while (itor != usedchar.end())
		{
			if (*itor == c)
				break;
			itor++;
		}
		if (itor == usedchar.end())
		{
			usedchar.push_back(c);
			findonesolution_helper(solutioncandidates, idx + 1, usedchar, verifiedsolutions);
			usedchar.pop_back();
		}
	}
	return;
}

bool findonesolution(vector<unordered_set<char>>& solutioncandidates, vector<vector<char>>& verifiedsolutions)
{
	vector<char> usedchar;

	for (char c : solutioncandidates[0])
	{
		usedchar.push_back(c);
		findonesolution_helper(solutioncandidates, 1, usedchar, verifiedsolutions);
		usedchar.pop_back();
	}
	return true;
}

void findSolutionsForSubmatrix(vector<vector<char>>& board, int idx, unordered_map<int, pair<int, int>> submatrixidx, vector<vector<char>>& submatrixsolutions,
							   unordered_map<int, vector<pair<int, int>>> &allsubmatrixholepos)
{
	unordered_set<char> number0to9({ '1','2','3','4','5','6','7','8','9' });
	unordered_set<char> submatrixcandi(number0to9);
	unordered_set<char> submatrixknown;
	vector<unordered_set<char>> solutioncandidates;
	int row = submatrixidx[idx].first;
	int col = submatrixidx[idx].second;

	vector<pair<int, int>> submatrixholepos;

	for (int i = row; i < row + 3; i++)
	{
		for (int j = col; j < col + 3; j++)
		{
			if (board[i][j] != '.')
			{
				submatrixcandi.erase(board[i][j]);
				submatrixknown.insert(board[i][j]);
			}
			else
			{
				submatrixholepos.push_back(pair<int, int>(i, j));
			}
		}
	}

	allsubmatrixholepos[idx] = submatrixholepos;

	for (int i = row; i < row + 3; i++)
	{
		for (int j = col; j < col + 3; j++)
		{
			if (board[i][j] == '.')
			{
				unordered_set<char> numcand(submatrixcandi);
				for (int k = 0; k < 9; k++)
				{
					if (board[i][k] != '.')
						numcand.erase(board[i][k]);
				}

				for (int k = 0; k < 9; k++)
				{
					if (board[k][j] != '.')
						numcand.erase(board[k][j]);
				}

				solutioncandidates.push_back(numcand);				
			}
		}
	}	

	findonesolution(solutioncandidates, submatrixsolutions);
}


void applyonesubmatrixsolution(vector<vector<char>>& board, int idx, vector<char>& onesubmatrixsolution, unordered_map<int, pair<int, int>>& submatrixidx)
{
	int row = submatrixidx[idx].first;
	int col = submatrixidx[idx].second;
	int applyidx = 0;
	for (int i = row; i < row + 3; i++)
	{
		for (int j = col; j < col + 3; j++)
		{
			if (board[i][j] == '.')
			{
				board[i][j] = onesubmatrixsolution[applyidx];
				applyidx++;
			}
		}
	}
	if (applyidx != onesubmatrixsolution.size())
	{
		printf("ERROR!");
	}
}

bool verifyBoardDuringPrefilling(vector<vector<char>>& board, int idx, unordered_map<int, pair<int, int>>& submatrixidx)
{
	unordered_set<char> number0to9({ '1','2','3','4','5','6','7','8','9' });

	int row = submatrixidx[idx].first;
	int col = submatrixidx[idx].second;
	unordered_set<char> tmpnumber0to9(number0to9);

	for (int r = row; r < row + 3; r++)
	{
		for (int c = col; c < col + 3; c++)
		{
			if (tmpnumber0to9.find(board[r][c]) == tmpnumber0to9.end())
				return false;

			tmpnumber0to9.erase(board[r][c]);
		}
	}
	if (tmpnumber0to9.size() != 0)
		return false;

	for (int r = row; r < row + 3; r++)
	{
		tmpnumber0to9.clear();
		for (int c = 0; c < 9; c++)
		{
			if (board[r][c] == '.')
				continue;

			if (tmpnumber0to9.count(board[r][c]) == 0)
				tmpnumber0to9.insert(board[r][c]);
			else
				return false;
		}
	}

	for (int c = col; c < col + 3; c++)
	{
		tmpnumber0to9.clear();
		for (int r = 0; r < 9; r++)
		{
			if (board[r][c] == '.')
				continue;

			if (tmpnumber0to9.count(board[r][c]) == 0)
				tmpnumber0to9.insert(board[r][c]);
			else
				return false;
		}
	}

	return true;
}

bool verifyBoard(vector<vector<char>>& board, unordered_map<int, pair<int, int>>& submatrixidx)
{
	unordered_set<char> number0to9({ '1','2','3','4','5','6','7','8','9' });
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			unordered_set<char> tmpnumber0to9_row(number0to9);
			for (int k = 0; k < 9; k++)
			{
				if (tmpnumber0to9_row.find(board[i][k]) == tmpnumber0to9_row.end())
					return false;

				tmpnumber0to9_row.erase(board[i][k]);
			}

			if (tmpnumber0to9_row.size() != 0)
				return false;

			unordered_set<char> tmpnumber0to9_col(number0to9);
			for (int k = 0; k < 9; k++)
			{
				if (tmpnumber0to9_col.find(board[k][j]) == tmpnumber0to9_col.end())
					return false;

				tmpnumber0to9_col.erase(board[k][j]);
			}

			if (tmpnumber0to9_col.size() != 0)
				return false;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		int row = submatrixidx[i].first;
		int col = submatrixidx[i].second;
		unordered_set<char> tmpnumber0to9(number0to9);
		for (int r = row; r < row + 3; r++)
		{
			for (int c = col; c < col + 3; c++)
			{
				if (tmpnumber0to9.find(board[r][c]) == tmpnumber0to9.end())
					return false;

				tmpnumber0to9.erase(board[r][c]);
			}
		}
		if (tmpnumber0to9.size() != 0)
			return false;
	}

	return true;
}

bool getAllSolutions(unordered_map<int, vector<vector<char>>>& allsubmatrixsolutions, int idx,
	unordered_map<int, pair<int, int>>& submatrixidx, vector<vector<char>> board, vector<vector<char>>& out_board)
{
	if (idx == allsubmatrixsolutions.size() + 1)
	{
		if (verifyBoard(board, submatrixidx))
		{
			out_board = board;
			return true;
		}
		return false;
	}

	for (vector<char > eachsubmatirxsolution : allsubmatrixsolutions[idx])
	{
		vector<char> onesubmatirxsolution(eachsubmatirxsolution.begin(), eachsubmatirxsolution.end());
		vector<vector<char>> tmpboard(board);
		applyonesubmatrixsolution(tmpboard, idx, onesubmatirxsolution, submatrixidx);
		if (!verifyBoardDuringPrefilling(tmpboard, idx, submatrixidx))
			continue;

		if (getAllSolutions(allsubmatrixsolutions, idx + 1, submatrixidx, tmpboard, out_board))
			return true;
	}

	return false;
}

void verifySubmatirxByDeterminedSolution(vector<vector<char>>& board, int determinedIdx,
	unordered_map<int, pair<int, int>>& submatrixidx,
	unordered_map<int, vector<vector<char>>>& allsubmatrixsolutions,
	unordered_map<int, vector<pair<int, int>>>& allsubmatrixholepos)
{
}

void purgeCandidatesByDeterminedSolution(vector<vector<char>>& board, int determinedIdx,
	unordered_map<int, pair<int, int>>& submatrixidx,
	unordered_map<int, vector<vector<char>>>& allsubmatrixsolutions,
	unordered_map<int, vector<pair<int, int>>>& allsubmatrixholepos)
{
	int row = submatrixidx[determinedIdx].first;
	int col = submatrixidx[determinedIdx].second;
	vector<int> beingpurgedSubmatirx;

	vector<int>& beingpurgedSubmatirxes = get_beingpurgedSubmatirx(determinedIdx);

	for (int matrixidx : beingpurgedSubmatirxes)
	{
		vector<pair<int, int>>::iterator holepos(allsubmatrixholepos[matrixidx].begin());
		for (int i = 0; i < allsubmatrixholepos[matrixidx].size(); i++)
		{
			int r = allsubmatrixholepos[matrixidx][i].first;
			int c = allsubmatrixholepos[matrixidx][i].second;

			int beingpreguedR = submatrixidx[matrixidx].first;
			int beingpreguedC = submatrixidx[matrixidx].second;

			vector<vector<char>>::iterator onesolultion(allsubmatrixsolutions[matrixidx].begin());
			while (onesolultion != allsubmatrixsolutions[matrixidx].end())
			{
				bool eraseOneSolution = false;
				if (beingpreguedR == row)
				{
					for (int cidx = col; cidx < col + 3; cidx++)
					{
						if ((*onesolultion)[i] == board[r][cidx])
						{
							onesolultion = allsubmatrixsolutions[matrixidx].erase(onesolultion);
							eraseOneSolution = true;
							break;
						}
					}
				}
				else
				{
					for (int ridx = row; ridx < row + 3; ridx++)
					{
						if ((*onesolultion)[i] == board[ridx][c])
						{
							onesolultion = allsubmatrixsolutions[matrixidx].erase(onesolultion);
							eraseOneSolution = true;
							break;
						}
					}
				}
				if (!eraseOneSolution)
					onesolultion++;
			}
		}
	}
}

bool isNumberDetermined(vector<vector<char>>& submatirxsolutions, int idx)
{
	char number = submatirxsolutions[0][idx];
	for (vector<char> eachsolution : submatirxsolutions)
	{
		if (eachsolution[idx] != number)
			return false;
	}
	return true;
}

bool purgeSolutionsByDeterminedNumber_helper(unordered_map<int, vector<vector<char>>>& allsubmatrixsolutions,
											 unordered_map<int, vector<pair<int, int>>>& allsubmatrixholepos,
											 unordered_map<int, pair<int, int>>& submatrixidxPos,
											 int determinedsubmatrixidx,
											 int determinedR, int determinedC, char determinedNumber)
{
	bool purgesomthing = false;
	vector<int>& beingpurgedSubmatirxes = get_beingpurgedSubmatirx(determinedsubmatrixidx);
	for (int matrixidx : beingpurgedSubmatirxes)
	{
		if (allsubmatrixsolutions.find(matrixidx) == allsubmatrixsolutions.end())
			continue;

		vector< vector<char>>& submatrixsolutions = allsubmatrixsolutions[matrixidx];
		vector<pair<int, int>>& submatrixholepos = allsubmatrixholepos[matrixidx];
		for (int i = 0; i < submatrixholepos.size(); i++)
		{
			if (submatrixholepos[i].first == determinedR || submatrixholepos[i].second == determinedC)
			{
				vector< vector<char>>::iterator eachsolutionItor(submatrixsolutions.begin());
				while (eachsolutionItor != submatrixsolutions.end())
				{
					if ((*eachsolutionItor)[i] == determinedNumber)
					{
						eachsolutionItor = submatrixsolutions.erase(eachsolutionItor);
						purgesomthing = true;
					}
					else
					{
						eachsolutionItor++;
					}
				}
			}
		}
	}

	return purgesomthing;
}

bool purgeSolutionsByDeterminedNumber(unordered_map<int, vector<vector<char>>>& allsubmatrixsolutions,
									  unordered_map<int, vector<pair<int, int>>> allsubmatrixholepos,
									  unordered_map<int, pair<int, int>> submatrixPos)
{
	bool purgesomthing = false;
	for (int submatrixidx = 1; submatrixidx <= 9; submatrixidx++)
	{
		if (allsubmatrixsolutions.find(submatrixidx) == allsubmatrixsolutions.end())
			continue;

		vector<vector<char>>& submatirxsolutions = allsubmatrixsolutions[submatrixidx];
		int candidatenumber = submatirxsolutions[0].size();
		for (int n = 0; n < candidatenumber; n++)
		{
			if (isNumberDetermined(submatirxsolutions, n))
			{
				int determinedR = allsubmatrixholepos[submatrixidx][n].first;
				int determinedC = allsubmatrixholepos[submatrixidx][n].second;

				if (purgeSolutionsByDeterminedNumber_helper(allsubmatrixsolutions, allsubmatrixholepos, submatrixPos,
															submatrixidx, determinedR, determinedC, submatirxsolutions[0][n]))
					purgesomthing = true;
			}
		}
	}

	return purgesomthing;
}

void solveSudoku(vector<vector<char>>& board)
{
	unordered_map<int, pair<int, int>> submatrixidxPos;
	submatrixidxPos[1] = pair<int, int>(0, 0);
	submatrixidxPos[2] = pair<int, int>(0, 3);
	submatrixidxPos[3] = pair<int, int>(0, 6);
	submatrixidxPos[4] = pair<int, int>(3, 0);
	submatrixidxPos[5] = pair<int, int>(3, 3);
	submatrixidxPos[6] = pair<int, int>(3, 6);
	submatrixidxPos[7] = pair<int, int>(6, 0);
	submatrixidxPos[8] = pair<int, int>(6, 3);
	submatrixidxPos[9] = pair<int, int>(6, 6);

	unordered_map<int, vector<vector<char>>> allsubmatrixsolutions;
	unordered_map<int, vector<pair<int,int>>> allsubmatrixholepos;

	for (int i = 1; i <= 9; i++)
	{
		vector<vector<char>> onesubmatrixsolutions;
		findSolutionsForSubmatrix(board, i, submatrixidxPos, onesubmatrixsolutions, allsubmatrixholepos);
		if (onesubmatrixsolutions.size() == 1)
		{
			vector<char> onesubmatirxsolution(onesubmatrixsolutions[0].begin(), onesubmatrixsolutions[0].end());
			applyonesubmatrixsolution(board, i, onesubmatirxsolution, submatrixidxPos);
		}
		else
		{
			allsubmatrixsolutions[i] = onesubmatrixsolutions;
		}
	}

	for (int i = 1; i <= 9; i++)
	{
		if (allsubmatrixsolutions.find(i) == allsubmatrixsolutions.end())
		{
			purgeCandidatesByDeterminedSolution(board, i, submatrixidxPos, allsubmatrixsolutions, allsubmatrixholepos);
		}
	}

	while (purgeSolutionsByDeterminedNumber(allsubmatrixsolutions, allsubmatrixholepos, submatrixidxPos))
	{		
	}

	for (vector<char > eachsubmatirxsolution : allsubmatrixsolutions[1])
	{
		vector<char> onesubmatirxsolution(eachsubmatirxsolution.begin(), eachsubmatirxsolution.end());
		vector<vector<char>> tmpboard(board);
		applyonesubmatrixsolution(tmpboard, 1, onesubmatirxsolution, submatrixidxPos);
		if (!verifyBoardDuringPrefilling(tmpboard, 1, submatrixidxPos))
			continue;

		if (getAllSolutions(allsubmatrixsolutions, 2, submatrixidxPos, tmpboard, board))
		{
			break;
		}
	}
}
