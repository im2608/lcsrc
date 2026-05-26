// lc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
#include <ranges>
#include <cassert>
#include <variant>
#include "lc.h"
#include ".\lc\sudoku.h"

using namespace std;

// SSL 证书验证问题。可以临时禁用 SSL 验证来推送：
// git -c http.sslVerify=false push -u origin main

// 数组分割等和子集问题中的 dp 是一个二维数组 dp[i][j], i 是0 到物品的数量， j 是从 0 到希望取得的最大价值
// dp[i][j] 表示的是 从 1 -- i 个的物品，能否取得 j 的价值。 取值为 true or false。它取值根据俩个情况：
// 1. 前 i-1 个物品已经能够取得 j，此时 dp[i-1][j] = true
// 2. 或是前 i-1 个物品能够取得 j - num[i-1] 的价值 (此时 dp[i-1][j-nums[i-1]] = true)， 此处暗含着再加上 num[i] 的价值则可以达到 j 的价值,
// 以上两条满足 1 条则 dp[i][j] = true, 意味着 1 -- i 个物品能够得到 j 的价值。
// 最终的目标是dp[i][target] 
// 
// 一维数组优化：dp[j+1]
// for (int i = 0; i < n; i++) 
// {
//	int num = nums[i];
//	for (int j = target; j >= num; j--) 
//  {
//		if (dp[j - num])  // 1 维数组优化。这里意思是从 1 到 i-1 的数能够得到 j -nums[i] 的价值，则此处加上 nums[i] 则说明 1 到 j 的数能得到 j 的价值
//		{
//			dp[j] = true;
//		}
//	}
//}
//

// 字符串向左循环移动算法：
// 1. 对称交换。
// 2. 根据向左移动的步数将字符串分为两个部分， 分别对称交换左右两部分，即得到最终结果
// 123456789 -> 向左移动 3 步 得到 456789123
// 1. 对称交换： 987654321
// 2.左边右边分别对称交换：987654 -> 456789, 321 -> 123, 
// 向右循环移动可以转化为： 向左移动 len - right 步
// 

ListNode* createListNode(vector<int>& n)
{
	ListNode* head = new ListNode(n[0]);
	ListNode* idx = head;
	for (int i = 1; i < n.size(); i++)
	{
		ListNode* node = new ListNode(n[i]);
		idx->next = node;
		idx = idx->next;
	}

	return head;

}

void deleteList(ListNode* head)
{
	ListNode* idx = NULL;
	while (head != NULL)
	{
		idx = head->next;
		delete head;
		head = idx;
	}
}

TreeNode** createTree(vector<int>& values)
{
	TreeNode** nodes = new TreeNode* [values.size()];
	for (int i = 0; i < values.size(); i++)
	{
		if (values[i] == INT_MIN)
		{
			nodes[i] = NULL;
			continue;
		}
		nodes[i] = new TreeNode(values[i]);
	}

	for (int i = 0; i < values.size(); i++)
	{
		if (values[i] == INT_MIN)
			continue;
		
		if (i * 2 + 1 < values.size() && values[i*2+1] != INT_MIN)
			nodes[i]->left = nodes[i * 2 + 1];

		if (i * 2 + 2 < values.size() && values[i * 2 + 2] != INT_MIN)
			nodes[i]->right = nodes[i * 2 + 2];
	}

	return nodes;
}

void deleteTree(TreeNode** nodes, int size)
{
	for (int i = 0; i < size; i++)
		delete nodes[i];

	delete[] nodes;
}

int testbs()
{
	vector<int> v({ 2, 4, 6, 8, 10, 12, 14, 16 });
	int i = 2;
	int l = 0, r = v.size() - 1;
	int m = r / 2;
	while (l <= r)
	{
		if (v[m] == i)
			return m;

		if (v[m] < i)
		{
			l = m + 1;
		}
		else
		{
			r = m - 1;
		}
		m = l + (r - l) / 2;
	}

	return m;
}

// 1st ele that < target
int testbs2()
{
	vector<int> v({ 2, 4, 6, 8, 8, 8, 10, 10, 10, 12, 14, 16 });
	int i = 10;
	int l = 0, r = v.size() - 1;
	int m = r / 2;
	int result = -1;
	while (l <= r)
	{
		if (v[m] < i) {
			result = m;
			if (v[m + 1] != v[m] && v[m+1] < i)
				l = m + 1; 
			else
				r = m - 1;
		}
		else {
			r = m - 1;
		}
		m = l + (r - l) / 2;
	}

	return result;
}

// https://leetcode.com/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstringOK(string s)
{
	int longestsubstr = 0, norepeat = 0;
	int char_pos_arr[256];
	int cursubstart = 0;
	//dfdefabcdef
	memset(char_pos_arr, -1, sizeof(char_pos_arr));

	for (size_t i = 0; i < s.size(); ++i)
	{
		char c = s[i];
		if (char_pos_arr[s[i]] >= cursubstart)
		{
			int cursublong = i - cursubstart;
			if (cursublong > longestsubstr)
				longestsubstr = cursublong;

			cursubstart = char_pos_arr[s[i]] + 1;
		}

		char_pos_arr[s[i]] = i;
	}

	if (s.size() - cursubstart > longestsubstr)
		longestsubstr = s.size() - cursubstart;

	return longestsubstr;

}

/*
"abcabcbb"
"bbbbb"
"pwwkew"
aab
*/
int lengthOfLongestSubstring(string s)
{
	int mask[256];
	int max_unique_len = 0, cur_uni_len = 0, cur_uni_idx = 0;

	memset(mask, -1, sizeof(mask));
	int len = s.size(), i = 0;
	while (i < len)
	{
		char c = s[i];
		if (mask[c] >= cur_uni_idx)
		{
			if (max_unique_len < i - cur_uni_idx)
			{
				max_unique_len = i - cur_uni_idx;
			}
			cur_uni_idx = mask[c] + 1;			
		}
		mask[c] = i;
		i++;
	}

	if (max_unique_len < len - cur_uni_idx)
	{
		max_unique_len = len - cur_uni_idx;
		cur_uni_len = 0;
	}

	return max_unique_len;
}

//https://leetcode.com/problems/compare-version-numbers/



bool IsHereNumber(string& str)
{
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] >= '1' && str[i] <= '9')
			return true;

	return false;
}

int compareVersion(string version1, string version2) 
{
	string subv1, subv2;
	size_t dot_pos1 = 0;
	size_t dot_pos2 = 0;

	size_t idx1 = 0, idx2 = 0;
	int a = 0, b = 0;

	size_t ver1idx = 0, ver2idx = 0;
	while (ver1idx < version1.length() && ver2idx < version2.length())
	{
		dot_pos1 = version1.find(".", ver1idx);
		dot_pos2 = version2.find(".", ver2idx);
		if (dot_pos1 != string::npos && dot_pos2 != string::npos)
		{
			subv1 = version1.substr(ver1idx, dot_pos1 - ver1idx);
			subv2 = version2.substr(ver2idx, dot_pos2 - ver2idx);

			ver1idx = dot_pos1 + 1;
			ver2idx = dot_pos2 + 1;
		}
		else if (dot_pos1 == string::npos && dot_pos2 != string::npos)
		{
			subv1 = version1.substr(ver1idx, version1.length());
			subv2 = version2.substr(ver2idx, dot_pos2 - ver2idx);

			ver1idx = version1.length();
			ver2idx = dot_pos2 + 1;			
		}
		else if (dot_pos1 != string::npos && dot_pos2 == string::npos)
		{
			subv1 = version1.substr(ver1idx, dot_pos1 - ver1idx);
			subv2 = version2.substr(ver2idx, version2.length());

			ver1idx = dot_pos1 + 1;
			ver2idx = version2.length();			
		}
		else
		{
			subv1 = version1.substr(ver1idx, version1.length());
			subv2 = version2.substr(ver2idx, version2.length());

			ver1idx = version1.length();
			ver2idx = version2.length();			
		}

		if (subv1.length() == 0 && subv2.length() == 0)
			return 0;

		a = std::stoi(subv1, &idx1, 10);
		b = std::stoi(subv2, &idx2, 10);

		if (a < b)
			return -1;
		else if (a > b)
			return 1;
	}

	if (ver1idx < version1.length())
	{
		subv1 = version1.substr(ver1idx, version1.length());
		if (IsHereNumber(subv1))
			return 1;

		return 0;
	}

	if (ver2idx < version2.length())
	{
		subv2 = version2.substr(ver2idx, version2.length());
		if (IsHereNumber(subv2))
			return -1;
	}

	return 0;
}

int compareVersionTest()
{
	string s1("7.5.2.4"), s2("7.5.3");
	int v = compareVersion(s1, s2);
	return v;
}

///////////////////////////////////////////////////////////////

int lengthOfLongestSubstringTest()
{
	string s[4] = { "0123.345.", "bbbbb", "pwwkew", "aaba" };
	string t = s[0].substr(0, 2);
	size_t idx;
	int a = std::stoi(s[0], &idx, 10);

	int j = 0;
	for (int i = 0; i < 4; i++)
		j = lengthOfLongestSubstring(s[i]);

	return j;
}

//https://leetcode.com/problems/slowest-key/
char slowestKey(vector<int>& releaseTimes, string keysPressed) 
{
	int maxDur = releaseTimes[0];
	char maxKey = keysPressed[0];

	for (size_t i = 1; i < releaseTimes.size(); i++)
	{
		int dur = releaseTimes[i] - releaseTimes[i - 1];
		if (dur > maxDur || (dur == maxDur && maxKey < keysPressed[i]))
		{
			maxDur = dur;
			maxKey = keysPressed[i];
		}
	}

	return maxKey;
}

void slowestKeyTest()
{
	vector<int> releaseTimes = { 9, 29, 49, 50 };
	string keyPressed("cbcd");
	slowestKey(releaseTimes, keyPressed);
}


// https://leetcode.com/problems/score-after-flipping-matrix/
int matrixScore(vector<vector<int>>& grid) 
{
	size_t rows = grid.size(), cols = grid[0].size();
	vector<int> numOnRow(rows, 0), numOnCol(cols, 0);
	vector<int> numOnMovedGridRow(rows, 0), numOnMovedGridCol(cols, 0);
	vector<vector<int> > movedGrid(grid);
	
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			numOnMovedGridRow[i] = (numOnMovedGridRow[i] << 1);
			numOnMovedGridCol[j] = (numOnMovedGridCol[j] << 1);

			if (grid[i][j] == 0)
			{
				movedGrid[i][j] = 1;
			}
			else
			{
				movedGrid[i][j] = 0;
			}
			numOnRow[i] |= grid[i][j];
			numOnCol[j] |= grid[i][j];
			
			numOnMovedGridRow[i] |= movedGrid[i][j];
			numOnMovedGridCol[j] |= movedGrid[i][j];
		}
	}
	return 0;
}
// 0 0 1 1 
// 1 0 1 0 
// 1 1 0 0 
// 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
int  matrixScoreTest()
{
	vector<vector<int> > maxOnRow({ { 1,1,1,1 }, { 0, 0, 1, 1 }, {1,0,1,0} });
	int a = 0;
	int b = ~a;
	matrixScore(maxOnRow);
	return b;
}

// https://leetcode.com/problems/linked-list-cycle/

bool hasCycle(ListNode *head) 
{
	ListNode *pIdx = head;
	ListNode *pIdx2 = head;
	if (pIdx != NULL && pIdx->next != NULL && pIdx->next->next != NULL)
		pIdx2 = pIdx->next->next;
	else
		return false;

	while (pIdx != pIdx2)
	{
		if (pIdx2->next != NULL)
		{
			if (pIdx2->next->next != NULL)
			{
				pIdx2 = pIdx2->next->next;
			}
			else
				return false;
			pIdx = pIdx->next;
		}
		else
			return false;

		if (pIdx == pIdx2)
			return true;
	}
	return true;
}

void testhasCycle()
{
	ListNode *p1 = new ListNode(1);
	ListNode *p2 = new ListNode(2);
	ListNode *p3 = new ListNode(3);
	p1->next = p2;
	p2->next = p3;
	p3->next = p2;

	hasCycle(p1);

	delete p1;
	delete p2;
	delete p3;

}

//https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
ListNode* getLastRepeat(ListNode *head)
{
	if (head == NULL)
		return NULL;

	ListNode *pIdx = head;
	while (pIdx->next != NULL && pIdx->next->val == head->val)
	{
		pIdx = pIdx->next;
	}

	return pIdx;
}

ListNode* deleteDuplicates2(ListNode* head)
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode *puni = getLastRepeat(head);
	while (puni != NULL && puni->val == head->val && puni != head)
	{
		head = puni->next;
		puni = getLastRepeat(puni->next);
	}

	if (head == NULL || head->next == NULL)
		return head;

	puni = head;
	ListNode *prepEnd = getLastRepeat(puni->next);
	while (prepEnd != NULL)
	{
		if (prepEnd != puni->next)
		{
			puni->next = prepEnd->next;
		}
		else
		{
			puni = puni->next;
		}

		prepEnd = getLastRepeat(puni->next);
	}

	return head;
}

void deleteDuplicatesTest()
{
	//int a[] = {1, 1, 2, 2,2,3}; // ok
	 //int a[] = { 1, 2, 2,2,3 }; // ok
	//int a[] = { 1, 1, 2, 2,2,3,3 };  // ok
	// int a[] = { 1, 2, 2,2,3,3 }; //ok
	int a[] = { 1, 2,3,3,4,5,5,6 };


	ListNode *p = NULL;
	ListNode *h = NULL;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		ListNode *ptmp = new ListNode(a[i]);
		if (p == NULL)
		{
			p = ptmp;
			h = ptmp;
		}
		else
		{
			p->next = ptmp;
			p = ptmp;
		}
	}

	deleteDuplicates2(h);

	while (h != NULL)
	{
		p = h->next;
		delete h;
		h = p;
	}
}


// https://leetcode.com/problems/partition-labels/

size_t getRepeatIdx(string& s, size_t curChar)
{
	for (size_t i = s.size() - 1; i > curChar; i--)
	{
		if (s[i] == s[curChar])
			return i;
	}

	return curChar;
}

vector<int> partitionLabels(string s) 
{
	vector<int> ret;

	size_t i = 0;

	while (i < s.size())
	{
		size_t curRep1 = getRepeatIdx(s, i);
		if (curRep1 == i)
		{
			ret.push_back(1);
			i++;
		}
		else
		{
			size_t endPartIdx = curRep1;
			for (size_t j = i + 1; j < endPartIdx; j++)
			{
				size_t curRep2 = getRepeatIdx(s, j);
				if (curRep2 > endPartIdx)
				{
					endPartIdx = curRep2;
				}
			}

			ret.push_back(endPartIdx - i + 1);
			i = endPartIdx + 1;
		}
	}
	

	return ret;
}

vector<int> partitionLabelsTest()
{
	//string s("qiejxqfnqceocmy");
	string s("ababcbacadefegdehijhklij");
	
	//[11,1,1,1,1]
	//[13,1,1]
	vector<int> ret = partitionLabels(s);
	return ret;
}

//https://leetcode.com/problems/broken-calculator/
int brokenCalc(int startValue, int target) 
{
	if (startValue > target)
		return startValue - target;

	int middle = startValue;
	int cnt = 0;
	while (target > startValue)
	{
		if (target % 2 == 0)
			target /= 2;
		else
			target++;

		cnt++;
	}

	if (target == startValue)
		return cnt;

	return cnt + startValue - target;
}

int brokenCalcTest()
{
	int ret = brokenCalc(1, 1000000000);
	return ret;
}

// https://leetcode.com/problems/two-sum/
vector<int> twoSum(vector<int>& nums, int target) 
{
	map<int, int> sum_map;
	vector<int> ret;
	for (size_t i = 0; i < nums.size(); i++)
	{
		int diff = target - nums[i];
		map<int, int>::iterator itor = sum_map.find(diff);
		if (itor != sum_map.end())
		{
			ret.push_back(i);
			ret.push_back(itor->second);

			return ret;
		}
		else
		{
			sum_map[nums[i]] = i;
		}
	}

	return ret;
}

void twoSumTest()
{
	vector<int> nums;
	nums.push_back(2);
	nums.push_back(7);
	twoSum(nums, 9);
}

// https://leetcode.com/problems/valid-palindrome-ii/
bool validPalindromeForward(string str) 
{
	size_t l = 0, r = str.size() - 1;
	bool hasSkipped = false;
	while (l < r)
	{
		if (str[l] != str[r])
		{
			if (hasSkipped)
				return false;

			if (str[l + 1] == str[r])
			{
				l += 2;
				r--;
				hasSkipped = true;
				continue;
			}

			return false;
		}

		l++;
		r--;
	}

	return true;
}


bool validPalindromeBackword(string str)
{
	size_t l = 0, r = str.size() - 1;
	bool hasSkipped = false;
	while (l < r)
	{
		if (str[l] != str[r])
		{
			if (hasSkipped)
				return false;

			if (str[l] == str[r - 1])
			{
				l++;
				r -= 2;
				hasSkipped = true;
				continue;
			}

			return false;
		}

		l++;
		r--;
	}

	return true;
}

bool validPalindrome(string str)
{
	if (validPalindromeForward(str))
		return true;

	return validPalindromeBackword(str);
}

void  validPalindromeTest()
{
	string s("aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga");
	validPalindrome(s);
}

// https://leetcode.com/problems/last-stone-weight/

void getTwoWeight(int& w1, int& w2, vector<int>& stones)
{
	if (stones.size() < 2)
		return;

	w1 = 0;
	w2 = 1;
	if (stones[w1] < stones[w2])
	{
		w1 = 1;
		w2 = 0;		
	}
	if (stones.size() == 2)
		return;

	for (size_t i = 2; i < stones.size(); i++)
	{
		if (stones[i] == 0)
			continue;

		if (stones[i] > stones[w1])
		{
			w2 = w1;
			w1 = i;
		}
		else if (stones[i] > stones[w2])
		{
			w2 = i;
		}
	}
}
int lastStoneWeight(vector<int>& stones)
{
	int w1 = 0, w2 = 0;
	size_t destoried = 0;
	while (destoried < stones.size() - 1)
	{
		getTwoWeight(w1, w2, stones);
		if (w1 != w2)
		{
			stones[w1] -= stones[w2];
			stones[w2] = 0;
			destoried++;
		}
	}

	for (size_t i = 0; i < stones.size(); i++)
	{
		if (stones[i] != 0)
			return stones[i];
	}

	return stones[0];
}
void lastStoneWeightTest()
{
	//vector<int> stones({ 2,7,4,1,8,1 });
	vector<int> stones({ 2,1, 1, 1 });
	lastStoneWeight(stones);

}

//https://leetcode.com/problems/game-of-life/
int deadOrLive(vector<vector<int>>& board, int r, int c)
{
	vector<int> rows, cols;
	if (r == 0)
	{
		rows.push_back(r);
		if (board.size() > 1)
		    rows.push_back(r+1);
	}
	else if (r == board.size() - 1)
	{
		rows.push_back(r - 1);
		rows.push_back(r);		
	}
	else
	{
		rows.push_back(r - 1);
		rows.push_back(r);
		rows.push_back(r+1);
		
	}

	if (c == 0)
	{
		cols.push_back(c);
		if (board[0].size() > 1)
		    cols.push_back(c+1);
	}
	else if (c == board[0].size()-1)
	{
		cols.push_back(c-1);
		cols.push_back(c);		
	}
	else
	{
		cols.push_back(c-1);
		cols.push_back(c);
		cols.push_back(c+1);
	}

	int liveCnt = 0;

	for (size_t rIdx = 0; rIdx < rows.size(); rIdx++)
	{
		for (size_t cIdx = 0; cIdx < cols.size(); cIdx++)
		{
			if (rows[rIdx] == r && cols[cIdx] == c)
				continue;

			if (board[rows[rIdx]][cols[cIdx]] == 1)
				liveCnt++;
		}
	}

	int live = 1;

	if (board[r][c] == 1)
	{
		if (liveCnt == 2 || liveCnt == 3)
			live = 1;
		else
			live = 0;
	}
	else
	{
		if (liveCnt == 3)
			live = 1;
		else
			live = 0;
	}

	return live;
}

void gameOfLife(vector<vector<int>>& board) 
{
	int live = 0;
	bool changed = true;
	//while (changed)
	{
		vector<vector<int>> nextGen(board);
		changed = false;
		for (size_t r = 0; r < board.size(); r++)
		{
			for (size_t c = 0; c < board[r].size(); c++)
			{
				live = deadOrLive(board, r, c);
				nextGen[r][c] = live;
				if (live != board[r][c])
					changed = true;
			}
		}
		board.assign(nextGen.begin(), nextGen.end());
	}

	return;
}

void gameOfLifeTest()
{
	//vector<vector<int>> board({ { 0,1,0 }, { 0,0,1 }, { 1,1,1 }, { 0,0,0 } });
	//vector<vector<int>> board({ { 1, 1, 1} });
	vector<vector<int>> board({ { 1}, {1},{1} });
	gameOfLife(board);
	return;
}


// https://leetcode.com/problems/trim-a-binary-search-tree/
TreeNode* getRightestAndParent(TreeNode* root, TreeNode *&pParentOfRightest)
{
	if (root == NULL)
		return root;

	TreeNode *pRightest = root;
	pParentOfRightest = root;
	while (pRightest != NULL && pRightest->right != NULL)
	{
		pParentOfRightest = pRightest;
		pRightest = pRightest->right;
	}

	return root;
}

TreeNode* getLeftestAndParent(TreeNode* root, TreeNode *&pParentOfLeftest)
{
	if (root == NULL)
		return root;

	TreeNode *pLeftest = root;
	pParentOfLeftest = root;
	while (pLeftest != NULL && pLeftest->right != NULL)
	{
		pParentOfLeftest = pLeftest;
		pLeftest = pLeftest->right;
	}

	return pLeftest;
}

void DoTrimBST(TreeNode* root, TreeNode* parent, int low, int high)
{
	if (root == NULL)
		return;

	if (root->val > low && root->val < high)
	{
		if (parent != NULL)
		{
			if (root == parent->left)
			{
				TreeNode *pParent = NULL;
				TreeNode *pRightest = getRightestAndParent(root->left, pParent);
				pRightest->right = root->right;
				pParent->right = pRightest->left;
				root = pRightest;
			}
			else
			{
				TreeNode *pParent = NULL;
				TreeNode *pLeftest = getLeftestAndParent(root->right, pParent);
				pLeftest->left = root->left;
				pParent->left = pLeftest->right;
				root = pLeftest;
			}
		}
	}

	DoTrimBST(root->left, root, low, high);
	DoTrimBST(root->right, root, low, high);
}

TreeNode* trimBST(TreeNode* root, int low, int high) 
{
	while (root->val > low && root->val < high)
	{
		if (root->left != NULL)
		{
			TreeNode *pParent = NULL;
			TreeNode *pRightest = getRightestAndParent(root->left, pParent);
			pRightest->right = root->right;
			pParent->right = pRightest->left;
			root = pRightest;
		}
		else if (root->right != NULL)
		{
			TreeNode *pParent = NULL;
			TreeNode *pLeftest = getLeftestAndParent(root->right, pParent);
			pLeftest->left = root->left;
			pParent->left = pLeftest->right;				
			root = pLeftest;
		}
		else
			return root;		
	}

	DoTrimBST(root->left, root, low, high);
	DoTrimBST(root->right, root, low, high);

	return root;
}

void trimBSTTest()
{
	TreeNode n5(5), n3(3), n7(7), n2(2), n4(4), n1(1), n0(0), n6(6), n8(8), n9(9), n10(10);
	n5.left = &n3;
	n5.right = &n7;

	n3.left = &n2;
	n3.right = &n4;

	n2.left = &n1;
	n1.left = &n0;

	n7.left = &n6;
	n7.right = &n9;

	n9.left = &n8;
	n9.right = &n10;

	trimBST(&n5, 4, 8);
}

//https://leetcode.com/problems/remove-nth-node-from-end-of-list/
ListNode* removeNthFromEnd(ListNode* head, int n) 
{
	int i = 0;
	if (head == NULL)
		return NULL;

	ListNode *pIdx1 = head, *pIdx2 = head;
	while (pIdx1->next != NULL)
	{
		pIdx1 = pIdx1->next;
		if (i < n)
		{
			i++;
		}
		else
		{
			pIdx2 = pIdx2->next;
		}		
	}

	if (i == n)
	{	
        pIdx2->next = pIdx2->next->next;	//delete the last and other nodes
	}
	else if (i == n - 1)
	{
		head = head->next;  // delete the 1st node
	}		
	
	return head;

}

void removeNthFromEndTest()
{
	ListNode *n = new ListNode(0);
	ListNode *r = n;
	for (int i = 1; i < 6; i++)
	{
		n->next = new ListNode(i);
		n = n->next;
	}

	removeNthFromEnd(r, 2);
}

// https://leetcode.com/problems/permutations-ii/
vector<vector<int>> permuteUnique(vector<int>& nums) 
{
	vector<vector<int>> ret;
	return ret;
}

void permuteUniqueTest()
{

}

// https://leetcode.com/problems/permutations/

bool isallmarkset(vector<bool>& marks)
{
	for (int i = 0; i < marks.size(); i++)
	{
		if (!marks[i])
			return false;
	}

	return true;
}

void mypermutation_helper(vector<int>& nums, vector<int> oneresult, vector<vector<int>>& results, vector<bool> marks)
{
	if (isallmarkset(marks))
	{
		results.push_back(oneresult);
		return;
	}

	for (int i = 0; i < nums.size(); i++)
	{
		if (marks[i])
		{
			continue;
		}
		oneresult.push_back(nums[i]);
		marks[i] = true;
		mypermutation_helper(nums, oneresult, results, marks);
		marks[i] = false;
		oneresult.pop_back();
	}
}

vector<vector<int>> mypermutation(vector<int>& nums)
{
	vector<bool> marks(nums.size(), false);
	vector<vector<int>> results;

	for (int i = 0; i < nums.size(); i++)
	{
		marks[i] = true;
		vector<int> oneresult;
		oneresult.push_back(nums[i]);
		mypermutation_helper(nums, oneresult, results, marks);
		marks[i] = false;
	}

	return results;
}

void testmypermutation()
{
	vector<int> nums({ 5,8,12,7 });
	mypermutation(nums);
}

void swapInt(vector<int>& nums, int i, int j)
{
	int tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp;
}

void doPermute(vector<int>& nums, int n, vector<vector<int>>& ret)
{
	if (n == nums.size() - 1)
	{
		ret.push_back(nums);
		return;
	}

	for (int i = n; i < nums.size(); i++)
	{
		swapInt(nums, i, n);
		doPermute(nums, n + 1, ret);
		swapInt(nums, n, i);
	}
}

vector<vector<int>> permute(vector<int>& nums) 
{
	vector<vector<int>> ret;
	doPermute(nums, 0, ret);

	return ret;
}

void  permuteTest()
{
	vector<int> nums({ 1,2,3 });
	permute(nums);
}

// https://leetcode.com/problems/min-cost-to-connect-all-points/

void getLightestEdge(vector<vector<int>>& points, edge& e)
{
	e.w = -1;
	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = i + 1; j < points.size(); j++)
		{
			unsigned int w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
			if (w < e.w)
			{
				e.from = i;
				e.to = j;
				e.w = w;
			}
		}
	}
}
void getLightestEdge(vector<vector<int>>& points, vector<bool> pointsFrom, vector<bool> pointsTo, edge& e)
{
	e.w = -1;
	for (size_t i = 0; i < pointsFrom.size(); i++)
	{
		if (!pointsFrom[i])
			continue;

		for (size_t j = 0; j < pointsTo.size(); j++)
		{
			if (!pointsTo[j])
				continue;

			unsigned int w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
			if (w < e.w)
			{
				e.from = i;
				e.to = j;
				e.w = w;
			}
		}
	}
}

void getAllEdges(vector<vector<int>>& points, std::priority_queue <edge>& pq)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = i + 1; j < points.size(); j++)
		{
			int w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
			edge e(i, j, w);
			pq.push(e);			
		}
	}
}

void getEdgesOfPointes(vector<vector<int>>& points, vector<bool> pointsFrom, vector<bool> pointsTo, std::priority_queue <edge>& pq)
{
	for (size_t i = 0; i < pointsFrom.size(); i++)
	{
		if (!pointsFrom[i])
			continue;

		for (size_t j = 0; j < pointsTo.size(); j++)
		{
			if (!pointsTo[j])
				continue;

			int w = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
			edge e(i, j, w);
			pq.push(e);
		}
	}
}

bool stillHavePoints(vector<bool> p)
{
	for (size_t i = 0; i < p.size(); i++)
	{
		if (p[i] != 0)
			return true;
	}

	return false;
}

int minCostConnectPoints(vector<vector<int>>& points)
{
	if (points.size() == 1)
		return 0;

	std::priority_queue <edge> pq;
	getAllEdges(points, pq);

	int w = 0;

	vector<bool> pointsFrom(points.size(), 0);
	vector<bool> pointsTo(points.size(), 1);
	edge e;

	getLightestEdge(points, e);
	w += e.w;
	pointsFrom[e.from] = 1;
	pointsFrom[e.to] = 1;

	pointsTo[e.from] = 0;
	pointsTo[e.to] = 0;

	while (stillHavePoints(pointsTo))
	{	
		getLightestEdge(points, pointsFrom, pointsTo, e);
		w += e.w;
		pointsFrom[e.from] = 1;
		pointsFrom[e.to] = 1;

		pointsTo[e.from] = 0;
		pointsTo[e.to] = 0;
	}

	return w;
}

void minCostConnectPointsTest()
{
	vector<vector<int>> points({ { 0, 0 }, { 2, 2 }, { 3, 10 }, { 5, 2 }, { 7, 0 } });
	minCostConnectPoints(points);
}


// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
void combineLetter(vector<string> &ret, string &digits, map<char, string> lettersMap, size_t index, string oneCombination)
{
	map<char, string>::iterator letters = lettersMap.find(digits[index]);
	if (letters == lettersMap.end())
		return;

	for (int i = 0; i < letters->second.size(); i++)
	{
		string tmp(oneCombination);
		tmp.push_back(letters->second[i]);
		if (index < digits.size() - 1)
		{
			combineLetter(ret, digits, lettersMap, index + 1, tmp);
		}
		else
		{
			ret.push_back(tmp);
		}
	}
}

vector<string> letterCombinations(string digits)
{
	vector<string> ret;

	if (digits.size() == 0)
		return ret;

	map<char, string> lettersMap = {
		{ '2', "abc" },
		{ '3', "def" },
		{'4', "ghi"} ,
		{'5', "jkl"} ,
		{'6', "mno"} ,
		{'7', "pqrs"} ,
		{'8', "tuv"} ,
		{'9', "wxyz"} ,
	};
	if (digits.size() == 1)
	{
		string letters = lettersMap[digits[0]];
		for (size_t i = 0; i < letters.size(); i++)
		{
			string tmp;
			tmp.push_back(letters[i]);
			ret.push_back(tmp);
		}
	}


	string letters = lettersMap[digits[0]];
	for (size_t i = 0; i < letters.size(); i++)
	{
		string tmp;
		tmp.push_back(letters[i]);

		combineLetter(ret, digits, lettersMap, 1, tmp);
	}

	return ret;
}

void letterCombinationsTest()
{
	string str("");
	letterCombinations(str);
}

//https://leetcode.com/problems/combination-sum-iii/
int getSumOfCombination(vector<int>& oneCombination)
{
	int sum = 0;
	for (size_t i = 0; i < oneCombination.size(); i++)
	{
		sum += oneCombination[i];
	}

	return sum;
}

void getCombinations(int k, int n, int num, vector<int> oneCombination, vector<vector<int>> ret)
{
	if (oneCombination.size() == n)
	{
		if (getSumOfCombination(oneCombination) == n)
		{
			ret.push_back(oneCombination);
			return;				
		}
	}

	if (k == 0 || num == 10)
		return;

	oneCombination.push_back(num);
	getCombinations(k - 1, n, num + 1, oneCombination, ret);
	oneCombination.pop_back();
	getCombinations(k, n, num + 1, oneCombination, ret);
}
vector<vector<int>> combinationSum3(int k, int n) 
{
	vector<vector<int>> ret;

	return ret;
}

// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
int getTreeDepth(Node *pNode, int curDepth)
{
	if (pNode == NULL)
		return curDepth;

	int leftDepth  = getTreeDepth(pNode->left, curDepth + 1);
	int rightDepth = getTreeDepth(pNode->right, curDepth + 1);

	if (leftDepth > rightDepth)
		return leftDepth;
	else
		return rightDepth;
}

void getTreeNodeNumber(Node *pNode, int& curNodeNum)
{
	if (pNode == NULL)
		return;

	curNodeNum++;
	
	getTreeNodeNumber(pNode->left, curNodeNum);
	getTreeNodeNumber(pNode->right, curNodeNum);
}

void setTreeNodeNext(list<Node *> *nodeList)
{
	list<Node *>::iterator itor = nodeList->begin();
	Node *pNode = *itor;
	itor++;
	while (itor != nodeList->end())
	{
		pNode->next = (*itor);
		pNode = *itor;
		itor++;
	}
}

void flatTree2(Node *pNode)
{
	if (pNode == NULL)
		return;

	list<Node *> nodeList, nodeList2;
	list<Node *> *treeInFlat = &nodeList, *treeInFlat2 = &nodeList2;

	if (pNode->left)
	    nodeList.push_back(pNode->left);

	if (pNode->right)
	    nodeList.push_back(pNode->right);

	list<Node *>::iterator itor;
	
	while (!treeInFlat->empty())
	{
		setTreeNodeNext(treeInFlat);
		list<Node *>::iterator itor = treeInFlat->begin();
		while (itor != treeInFlat->end())
		{
			Node *pNode = *itor;
			if (pNode->left != NULL)
				treeInFlat2->push_back(pNode->left);

			if (pNode->right != NULL)
				treeInFlat2->push_back(pNode->right);	

			itor++;
		}

		treeInFlat->clear();
		list<Node *> *tmp = treeInFlat;		
		treeInFlat = treeInFlat2;
		treeInFlat2 = tmp;
	}

	return;
}

Node* connect2(Node* root) 
{
	if (root == NULL)
		return NULL;

	flatTree2(root);

	return root;
}

void connecttest()
{
	Node n0(0), n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7), n8(8), n9(9), n10(10), n12(12), n14(14);	

	n0.left = &n1;
	n0.right = &n2;
	n1.left = &n3;
	n1.right = &n4;
	n2.left = &n5;
	n2.right = &n6;
	n3.left = &n7;
	n3.right = &n8;
	n4.left = &n9;
	n4.right = &n10;
	n5.right = &n12;
	n6.right = &n14;

//	connect(&n0);
	int treeNode = 0;
	getTreeNodeNumber(&n0, treeNode);

	flatTree2(&n0);
}

// https://leetcode.com/problems/intersection-of-two-linked-lists/

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
{
	ListNode *pidx1 = headA, *pidx2 = headB;
	ListNode *pInterNode = NULL;
	map<ListNode *, bool> nodeMap;
	while (pidx1 != NULL)
	{
		if (nodeMap.find(pidx1) != nodeMap.end())
			return pidx1;
		else
			nodeMap[pidx1] = true;

		pidx1 = pidx1->next;
	}

	while (pidx2 != NULL)
	{
		if (nodeMap.find(pidx2) != nodeMap.end())
			return pidx2;
		else
			nodeMap[pidx2] = true;

		pidx2 = pidx2->next;
	}

	return NULL;
}

// https://leetcode.com/problems/merge-sorted-array/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
{
	int left1 = m, left2 = n;
	vector<int> ret, ret2(n, 0);
	while (left1 > 0 && left2 > 0)
	{
		if (nums1[m - left1] < nums2[n - left2])
		{
			ret.push_back(nums1[m - left1]);
			left1--;
		}
		else if (nums1[m - left1] > nums2[n - left2])
		{
			ret.push_back(nums2[n - left2]);
			left2--;
		}
		else
		{
			ret.push_back(nums1[m - left1]);
			ret.push_back(nums1[m - left1]);
			left1--;
			left2--;
		}
	}
	if (left1 > 0)
	{
		ret.insert(ret.end(), nums1.begin() + (m - left1), nums1.begin() + m);
	}
	else
	{
		ret.insert(ret.end(), nums2.begin() + (n - left2), nums2.begin() + n);
	}

	nums1.clear();
	nums1.insert(nums1.end(), ret.begin(), ret.end());
}

void mergeTest()
{
//	vector<int> n1({ 1,3,5,7,9,11,13,15,16 }), n2({2,4,6,8,10,12,14,15,16,18});
	vector<int> n1({ 2, 0 }), n2({ 1 });
	merge(n1, 1, n2, 1);
	return;
}


// https://leetcode.com/problems/rotate-image/

void rotate(vector<vector<int>>& matrix)
{
	int n = matrix.size();

	//对角线交换
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int tmp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = tmp;
		}
	}

	// 左右镜像交换
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n/2; j++)
		{
			int tmp = matrix[i][j];
			matrix[i][j] = matrix[i][n - j - 1];
			matrix[i][n - j - 1] = tmp;
		}
	}

	return;
}
void rotateTest()
{
	vector<vector<int>> matrix({ {1,2,3, 4}, {5,6,7,8}, {9,10,11,12},{13,14,15,16} });
//	vector<vector<int>> matrix({ {1,2,},{3, 4 } });


	rotate(matrix);
}

// https://leetcode.com/problems/search-in-rotated-sorted-array/
int search(vector<int>& nums, int target) 
{
	if (nums.size() == 0 || (nums.size() == 1 && nums[0] != target))
	{
		return -1;
	}

	if (nums.size() == 2)
	{
		if (nums[0] == target)
			return 0;

		if (nums[1] == target)
			return 1;

		return -1;
	}
	int size = nums.size();

	int i = 0, j = size - 1, m = (i + j) / 2;

	while (i <= j)
	{
		if (target == nums[m])
			return m;

		if (target >= nums[0]) // target 在左半部
		{
			if (nums[m] >= nums[0])  // m 也在左半部
			{
				if (target > nums[m]) // 根据 target 与 m 之间的位置调整 i 和 j
					i = m + 1;
				else
					j = m - 1;
			}
			else
			{
				// target 在左半部， 但是 m 在右半部, 则需调整右侧的索引
				j = m - 1;
			}
		}
		else // target 在右半部
		{
			if (nums[m] >= nums[0]) // 但 m 在左半部
			{
				i = m + 1;
			}
			else // m 也在右半部
			{
				if (target > nums[m]) // 根据 target 与 m 之间的位置调整 i 和 j
					i = m + 1;
				else
					j = m - 1;
			}
		}

		m = (i + j) / 2;
	}
	return -1;
}



// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
bool search2(vector<int>& nums, int target) 
{
	if (nums.size() == 0 || (nums.size() == 1 && nums[0] != target))
	{
		return false;
	}

	if (nums.size() == 2)
	{
		if (nums[0] == target)
			return true;

		if (nums[1] == target)
			return true;

		return false;
	}
	int size = nums.size();

	int i = 0, j = size - 1, m = (i + j) / 2;

	while (i <= j)
	{
		if (target == nums[m])
			return true;

		if (nums[i] == nums[m] && nums[m] == nums[j])
		{
			i++;
			j--;
		}
		else if (nums[i] <= nums[m])
		{
			if (nums[i] <= target && target < nums[m])
			{
				j = m - 1; 
			}
	    	else
			{
				i = m + 1;
			}
		}
		else
		{
			if (nums[m] < target && target <= nums[j])
			{
				i = m + 1;
			}
			else
			{
				j = m - 1;
			}
		}

		m = (i + j) / 2;
	}
	return false;
}
/*
bool search2(vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size() - 1;

	while(l <= r)
	{
		int mid = l + (r-l) / 2;
		if (nums[mid] == target)
			return true;
		// with duplicates we can have this contdition, just update left & right
		if((nums[l] == nums[mid]) && (nums[r] == nums[mid]))
		{
			l++;
			r--;
		}
		// first half
		// first half is in order
		else if(nums[l] <= nums[mid])
		{
			// target is in first  half
			if((nums[l] <= target) && (nums[mid] > target))
				r = mid - 1;
			else
				l = mid + 1;
		}
		// second half
		// second half is order
		// target is in second half
		else
		{
			if((nums[mid] < target) && (nums[r]>= target))
				l = mid + 1;
			else
				r = mid - 1;
		}
	}
	return false;
}
*/


void testsearch()
{
	//vector<int> nums({7,8,9,10,1,2,3,4,5,6});
	//vector<int> nums({ 4,5,6,7,0,1,2 });
	vector<int> nums({ 1,0,1,1,1 });
	int target = 0;
//	search(nums, target);
	search2(nums, target);
}


// https://leetcode.com/problems/combination-sum-iv/
/*
void combinationSum4Helper(vector<int>& nums, int target, int idxInTmp, int curIdx, vector<vector<int>> &rets, vector<int>& result, int& ret)
{
	if (target == 0)
	{
		//rets.push_back(result);
		ret++;
		return;
	}

	if (target < 0)
		return;

	for (size_t i = 0; i < nums.size(); i++)
	{

		if (idxInTmp <= result.size())
		{
			result.push_back(nums[i]);
			idxInTmp++;
		}
		else
		{
			result[idxInTmp] = nums[i];
		}

		//result.push_back(nums[i]);
		combinationSum4Helper(nums, target - nums[i], idxInTmp, i, rets, result, ret);
	}
}

int combinationSum4(vector<int>& nums, int target) 
{
	vector<vector<int>> rets;
	int ret = 0;

	vector<int> tmp;
	int idxInTmp = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		if (idxInTmp <= tmp.size())
			tmp.push_back(nums[i]);
		else
			tmp[idxInTmp] = nums[i];

		combinationSum4Helper(nums, target - nums[i], idxInTmp, i, rets, tmp, ret);
	}

	return ret;

	return rets.size();
}
*/

int solve(vector<int>& nums, int target, vector<int> &dp) {
	if (target == 0) 
		return 1;

	if (dp[target] != -1) 
		return dp[target];

	dp[target] = 0;
	for (int num : nums)
		if (num <= target)
			dp[target] += solve(nums, target - num, dp);

	return dp[target];
}
int combinationSum4(vector<int>& nums, int target) {
	vector<int> dp(target + 1, -1);
	int i = solve(nums, target, dp);
	return i;
}

void testcombinationSum4()
{
	//vector<int> nums({ 4,2,1});
	vector<int> nums({ 1, 2, 3,4});
	combinationSum4(nums, 32);	//32
}


// https://leetcode.com/problems/where-will-the-ball-fall/
// ret: -1: no, 
//       
//     

int CanGoDown(vector<vector<int>>& grid, int row, int col)
{
	int ret = 0;

	if (grid[row][col] == 1)
	{
		if ((col == grid[0].size() - 1) || 
			(col < grid[0].size() - 1 && grid[row][col + 1] == -1))
			return -1;

		return col + 1;
	}
	else
	{
		if (col == 0 || 
			(col > 0 && grid[row][col - 1] == 1))
			return -1;

		return col-1;
	}
}

vector<int> findBall(vector<vector<int>>& grid) 
{
	vector<int> ret(grid[0].size(), 0);
	for (int i = 0; i < ret.size(); i++)
		ret[i] = i;

	bool oneDown = true;
	for (int row= 0; row < grid.size() && oneDown; row++)
	{
		oneDown = false;
		for (int col = 0; col < ret.size(); col++)
		{
			if (ret[col] == -1)
				continue;

			ret[col] = CanGoDown(grid, row, ret[col]);
			if (ret[col] != -1)
				oneDown = true;			
		}
	}

	return ret;
}

void testfindBall()
{
	vector<vector<int>> grid({ { 1,  1,  1, -1, -1}, 
							   { 1,  1,  1, -1, -1},
		                       {-1, -1, -1,  1,  1},
		                       { 1,  1,  1,  1, -1},
		                       {-1, -1, -1, -1, -1} });
	findBall(grid);
}


// https://leetcode.com/problems/path-with-maximum-probability/description/

void getNextCandidate(vector<vector<int>>& edges, int start, vector<int> &nextNodeCandidate, map<int, bool> &nodeInPath)
{
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i][0] != start || nodeInPath.find(edges[i][1]) != nodeInPath.end())
			continue;

		nextNodeCandidate.push_back(edges[i][1]);
		nodeInPath[edges[i][1]] = true;
	}
}


void getPath(vector<vector<int>>& edges, int start, int end, vector<int> path, vector<vector<int>> pathes, map<int, bool> &nodeOnPath)
{
	if (start == end)
	{
		pathes.push_back(path);
		return;
	}

	if (nodeOnPath.size() == edges.size())
		return;

	nodeOnPath[start] = true;

	vector<int> nextNodeCandidate;

	getNextCandidate(edges, start, nextNodeCandidate, nodeOnPath);
	for (int i = 0; i < nextNodeCandidate.size(); i++)
	{
		getPath(edges, nextNodeCandidate[i], end, path, pathes, nodeOnPath);
	}

}

void getAEdge(vector<vector<int>>& edges, vector<double>& succProb, int start, int end, double curProb, double maxProb, vector<int> &path, map<int, bool> nodeOnPath)
{
	vector<int> nextNodeCandidate;
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i][0] != start)
			continue;

		if (edges[i][1] == end)
		{
			curProb *= succProb[i];

			if (curProb > maxProb)
				maxProb = curProb;

			return;
		}

		if (nodeOnPath.find(edges[i][1]) != nodeOnPath.end())
		{
			nodeOnPath[edges[i][1]] = true;
			continue;
		}

		getNextCandidate(edges, start, nextNodeCandidate, nodeOnPath);

		curProb *= succProb[i];

		path.push_back(edges[i][1]);

		getAEdge(edges, succProb, edges[i][1], end, curProb, maxProb, path, nodeOnPath);
	}
}

void testmaxProbability()
{
	vector<vector<int>> edges({ {0, 1}, {1, 2},{0, 2} });
	vector<double> succProb({ 0.5,0.5,0.2 });
	int start = 0;
	int end = 2;

	double curProb = 1, maxProb = 1;

	vector<int> path;
	map<int, bool> nodeOnPath;
	nodeOnPath[start] = 1;

	getAEdge(edges, succProb, start, end, curProb, maxProb, path, nodeOnPath);
}

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) 
{
	double ret = 1;

	return 0;
}

// https://leetcode.com/problems/longest-common-prefix/
string longestCommonPrefix(vector<string>& strs) 
{
	size_t curCommonIdx = 0;
	bool bHasCommon = true;

	if (strs.size() == 0 || strs[0].size() == 0)
		return "";

	if (strs.size() == 1)
		return strs[0];

	string ret;

	int curIdx = 0;

	while (true)
	{
		char c = strs[0].c_str()[curIdx];
		for (size_t i = 0; i < strs.size(); i++)
		{
			if (strs[i].size() == 0)
				return "";

			if (strs[i].size() == curIdx)
				return ret;

			if (strs[i].c_str()[curIdx] != c)
				return ret;
		}

		ret.push_back(c);
		curIdx++;
		if (strs[0].size() == curIdx)
			return ret;
	}

	return ret;
}

void testlongestCommonPrefix()
{
	vector<string> strs({ "" });
	string r = longestCommonPrefix(strs);
}

//https://leetcode.com/problems/all-paths-from-source-to-target/

void findOnePath(vector<vector<int>>& graph, int start, vector<vector<int>>& allPathes, vector<int> onePath)
{
	if (start >= graph.size())
		return;

	onePath.push_back(start);
	if (start == graph.size() - 1)
	{
		allPathes.push_back(onePath);
		return;
	}

	for (int idx = 0; idx < graph[start].size(); idx++)
	{
		findOnePath(graph, graph[start][idx], allPathes, onePath);
	}
}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) 
{
	vector<vector<int>> allPathes;

	for (int idx = 0; idx < graph[0].size(); idx++)
	{
		vector<int> onePath;
		onePath.push_back(0);
		findOnePath(graph, graph[0][idx], allPathes, onePath);
	}

	return allPathes;
}

void testallPathsSourceTarget()
{
	vector<vector<int>> graph({ {4, 3, 1}, {3, 2, 4},{3},{4},{} });
	allPathsSourceTarget(graph);
}

// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/
void convertEdgesToMap(vector<vector<int>>& edges, map<int, vector<int> *> &edgeMap)
{
	for (int i = 0; i < edges.size(); i++)
	{
		int victFrom = edges[i][0];
		int victTo = edges[i][1];
		if (edgeMap.find(victFrom) == edgeMap.end())
		{
			edgeMap[victFrom] = new vector<int>();
			if (victFrom == 0)
				edgeMap[victFrom]->push_back(-1);
		}
		edgeMap[victFrom]->push_back(victTo);

		if (edgeMap.find(victTo) == edgeMap.end())
		{
			edgeMap[victTo] = new vector<int>();
		}

		edgeMap[victTo]->push_back(victFrom);
	}
}

void ReleaseEdgeMap(map<int, vector<int>* > edgeMap)
{
	for (map<int, vector<int>* >::iterator itor = edgeMap.begin(); itor != edgeMap.end(); itor++)
	{
		delete itor->second;
	}
}

int DoChildrenHaveApple(map<int, vector<int>* > &edgeMap, vector<bool>& hasApple, int node, int parent)
{
	// this is a leaf node
	if (edgeMap[node]->size() == 1)
	{
		if (hasApple[node])
			return 2;
		else
			return 0;
	}

	int path = 0;
	for (int i = 0; i < edgeMap[node]->size(); i++)
	{		
		int cur = (*(edgeMap[node]))[i];
		if (cur != parent)
			path += DoChildrenHaveApple(edgeMap, hasApple, cur, node);
	}

	if (node == 0)
		return path;
	else if (path || hasApple[node])
		return path + 2;
	else
		return 0;
}

int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) 
{
	map<int, vector<int>* > edgeMap;

	if (n == 1)
	{
		return 0;
	}
	
	convertEdgesToMap(edges, edgeMap);
	int path = DoChildrenHaveApple(edgeMap, hasApple, 0, -1);

	ReleaseEdgeMap(edgeMap);
	return path;
}


void testminTime()
{
//	vector<vector<int>> edges({ {0, 1}, {0, 2},{1, 4},{1, 5},{2, 3},{2, 6} });
//	vector<bool> hasApple({ false, false, true, false, true, true, false });

	vector<vector<int>> edges({ {1, 2}, {0,2},{0,3} });
	vector<bool> hasApple({ false,true,false,false });

//	Solution s;
//	s.minTime(4, edges, hasApple);
	minTime(4, edges, hasApple);
}

//https://leetcode.com/problems/greatest-common-divisor-of-strings/
bool IsCommonDivisor(string &str1, string &str2, int divisorLen)
{
	string strDivisor(str1.c_str(), divisorLen);

	int i = 0;

	for (i = 0; i < str1.size(); i += divisorLen)
	{
		if (str1.compare(i, divisorLen, strDivisor.c_str()) != 0)
			return false;
	}

	for (i = 0; i < str2.size(); i += divisorLen)
	{
		if (str2.compare(i, divisorLen, strDivisor.c_str()) != 0)
			return false;
	}
	
	return true;
}

string gcdOfStrings(string str1, string str2) 
{
	string ret;
	size_t largestDivisorLen = min(str1.size(), str2.size());
	for (size_t i = largestDivisorLen; i >= 1; i--)
	{
		if (str1.size() % i != 0 || str2.size() % i != 0)
			continue;

		if (IsCommonDivisor(str1, str2, i))
			return str1.substr(0, i);
	}
	return ret;

}

void testgcdOfStrings()
{
	string str1("ABABAB"), str2("ABAB");

	string ret = gcdOfStrings(str1, str2);
}


// https://leetcode.com/problems/verifying-an-alien-dictionary/
bool isAlienSorted(vector<string>& words, string order) 
{
	
	map<char, int> lexioDict;
	int i = 0;

	int len0cnt = 0;
	int lastLen0 = 0;
	for (i = 0; i < words.size(); i++)
	{
		if (words[i].size() == 0)
		{
			len0cnt++;
			lastLen0 = i;
		}
	}

	if (len0cnt == words.size())
		return true;

	if (lastLen0 != 0)
		return false;

	for (i = 0; i < order.size(); i++)
	{
		lexioDict[order[i]] = i;
	}

	for (i = 0; i < words.size() - 1; i++)
	{
		int len = min(words[i].size(), words[i + 1].size());		
		int inorder = 0;

		for (int j = 0; j < len; j++)
		{
			if (lexioDict[words[i][j]] < lexioDict[words[i + 1][j]])
			{
				inorder = -1;
				break;
			}
			else if (lexioDict[words[i][j]] == lexioDict[words[i + 1][j]])
			{
				inorder = 0;
			}
			else
			{
				inorder = 1;
				break;
			}
		}

		if (inorder == 1 || (inorder == 0 && words[i].size() > words[i+1].size()))
		{
			return false;
		}
	}

	return true;
}

void testisAlienSorted()
{
	vector<string> words({ "zezwvpdhkhc","nldmzkh","qvjpbis","gxntgh","knkdjzzxkv","qyymcxdjut","htjghmlc","qxgxzmgbodnj","hkmhfenu","tlbjlaw" });
	string order("pojvhubakxzqtlesmcwydinrfg");

	bool b = isAlienSorted(words, order);
}

//https://leetcode.com/problems/jump-game/
bool canjump_helper(vector<int>& nums, int pos, vector<bool>& nums_passed)
{
	if (pos == nums.size() - 1 || pos + nums[pos] >= nums.size())
		return true;

	for (int i = 1; i <= nums[pos]; i++)
	{
		if ((nums_passed[pos + i]))
			continue;

		if (canjump_helper(nums, pos + i, nums_passed))
			return true;
	}

	nums_passed[pos] = true;

	return false;
}
bool canJump(vector<int>& nums)
{
	vector<bool> nums_passed(nums.size(), 0);

	return canjump_helper(nums, 0, nums_passed);
}
void testcanjump()
{
	vector<int> nums({ 3,2, 1, 0, 4 });

	canJump(nums);
}


// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
// post: 2315764
// in:   1234567
// https://blog.csdn.net/qq_39445165/article/details/93971171
int getRootPosFromIn(vector<int>& inorder, int root)
{
	for (int i = 0; i < inorder.size(); i++)
		if (root == inorder[i])
			return i;

	return -1;
}

//	vector<int> inorder({ 1,2,3,4, });
// vector<int> postorder({ 4,3,2,1 });
void buildTree_helper(vector<int>& inorder, vector<int>& postorder, int inL, int inR, int postL, int postR, TreeNode *& pNode)
{
	if (inL > inR)
		return;

	int root = postorder[postR];
	int rootPos = getRootPosFromIn(inorder, root);
	pNode = new TreeNode;
	pNode->val = root;
	int childLenL = rootPos - inL;
	int childLenR = inR - rootPos;

	if (childLenL == 1)
	{
		pNode->left = new TreeNode;
		pNode->left->val = inorder[inL];
		pNode->left->left = NULL;
		pNode->left->right = NULL;
	}
	else
		buildTree_helper(inorder, postorder, inL, inL + childLenL - 1, postL, postL + childLenL - 1, pNode->left);


	if (childLenR == 1)
	{
		pNode->right = new TreeNode;
		pNode->right->val = inorder[inR];
		pNode->right->left = NULL;
		pNode->right->right = NULL;
	}
	else
	{
		//buildTree_helper(inorder, postorder, rootPos + 1, rootPos + childLenR, rootPos, rootPos + childLenR - 1, pNode->right);
		buildTree_helper(inorder, postorder, rootPos + 1, rootPos + childLenR, postR - childLenR, postR - 1, pNode->right);
	}
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {

	TreeNode *pTree = NULL;
	buildTree_helper(inorder, postorder, 0, inorder.size() - 1, 0, inorder.size() - 1, pTree);

	return pTree;
}

void testbuildTree()
{
//	vector<int> inorder({1,2,3,4,5,6,7});
	//vector<int> postorder({ 2,3,1,5,7,6,4 });

	vector<int> inorder({ 1,2,3,4, });
	vector<int> postorder({ 4,3,2,1 });

	buildTree(inorder, postorder);
}

// https://leetcode.com/problems/3sum/
vector<vector<int>> threeSum(vector<int>& nums) 
{
	vector<vector<int>> ret;
	if (nums.size() < 3)
		return ret;

	if (nums.size() == 3)
	{
		if (nums[0] + nums[1] + nums[2] == 0)
			ret.push_back(nums);

		return ret;
	}

	std::sort(nums.begin(), nums.end());

	unordered_map<int, int> numsLeft;
	int i = 0, j = 0;
	for (i = 0; i < nums.size(); i++)
	{
		numsLeft[nums[i]] = i;
	}

	i = 0;
	while (i < nums.size() - 2)
	{
		if (nums[i] > 0)
			break;
		int j = i + 1;
		while (j < nums.size() - 1)
		{
			int curSum = nums[i] + nums[j];

			int lastNum = 0 - curSum;
			int count = numsLeft.count(lastNum);
			if (count && numsLeft[lastNum] > j)
			{
				ret.push_back({ nums[i], nums[j], lastNum });
				j = numsLeft[nums[j]];
			}
			
			j++;
		}
		i = numsLeft[nums[i]];
		i++;
	}

	return ret;
}

void testthreeSum()
{
	vector<int> nums({ -1,0,1,2,-1,-4 });
//	vector<int> nums({ 0,0,0,0});

	threeSum(nums);
}

// https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/
int solve(TreeNode* root, int length, bool shouldGoLeft) 
{
	if (!root)
		return length;

	int left = 0;
	int right = 0;
	int tmp = 0;

	if (shouldGoLeft && !root->left) {
		tmp = length;
		length = 0;
	}
	else if (!shouldGoLeft && !root->right) {
		tmp = length;
		length = 0;
	}

	right = solve(root->right, shouldGoLeft ? 1 : length + 1, true);
	left = solve(root->left, shouldGoLeft ? length + 1 : 1, false);

	return std::max({ left, right, tmp });
}

int iterateTree(TreeNode* root, int steps, bool leftChildOfParent, map<TreeNode *, int> &nodeSteps)
{
	if (root == NULL)
		return steps;

	if ((leftChildOfParent  && root->right == NULL) ||
		(!leftChildOfParent && root->left == NULL))
	{
		nodeSteps[root] = 3;
		return 1;
	}

	int stepFromCurNode = 0;

	if (leftChildOfParent)
	{
		stepFromCurNode = iterateTree(root->right, steps + 1, false, nodeSteps);
		if (nodeSteps.find(root) != nodeSteps.end())
			nodeSteps[root] |= 2;
		else
			nodeSteps[root] = 2;

		if (root->left == NULL)
			nodeSteps[root] |= 1;
	}
	else
	{
		stepFromCurNode = iterateTree(root->left, steps + 1, true, nodeSteps);
		if (nodeSteps.find(root) != nodeSteps.end())
			nodeSteps[root] |= 1;
		else
			nodeSteps[root] = 1;

		if (root->right == NULL)
			nodeSteps[root] |= 2;
	}

	return stepFromCurNode + 1;
}

int longestZigZagHelper(TreeNode* root, map<TreeNode *, int> &nodeSteps)
{

	//if (nodeSteps.find(root) != nodeSteps.end())
	//{
	//	return nodeSteps[root];
	//}

	int stepsLeft = 0, stepsRight = 0;

	stepsLeft = iterateTree(root->left, 1, true, nodeSteps);
	stepsRight = iterateTree(root->right, 1, false, nodeSteps);

	return max(stepsLeft, stepsRight);
}

int longestZigZag(TreeNode* root)
{
//	return solve(root, 0, false);

	int maxSteps = 0;
	map<TreeNode *, int> nodeSteps;
	list<TreeNode *> treeNodesList;
	treeNodesList.push_back(root);

	while (!treeNodesList.empty())
	{
		TreeNode *pNode = treeNodesList.front();
		int steps = longestZigZagHelper(pNode, nodeSteps);
		if (maxSteps < steps)
			maxSteps = steps;

		treeNodesList.pop_front();

		if (pNode->left && (pNode->left->left || pNode->left->right) && nodeSteps[pNode] != 3)
			treeNodesList.push_back(pNode->left);

		if (pNode->right && (pNode->right->left || pNode->right->right) && nodeSteps[pNode] != 3)
			treeNodesList.push_back(pNode->right);
	}

	return maxSteps;
}

void testlongestZigZag()
{	
	TreeNode n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7), n8(8), n9(9), n10(10);

	n1.left = &n2;
	n1.right = &n3;
	n2.right = &n4;
	n3.right = &n5;

	//n1.right = &n2;
	//n2.left = &n3;
	//n2.right = &n4;
	//n4.left = &n5;
	//n4.right = &n6;
	//n5.right = &n7;
	//n7.right = &n8;

	longestZigZag(&n1);
}

//https://leetcode.com/problems/kth-largest-element-in-a-stream/
class KthLargest {
public:
	// 得到第 k 大的数。 先创建一个最小堆，在堆顶的就是最小的数，当堆的size > k 的时候就 pop，表示把最小的数 pop 出去
	// 则剩下的就是较大的数，遍历完整个 vec 后，则堆中保存的就是最大的前 k 个数。由于是最小堆，在堆顶的就是最小的数，
	// 则堆顶则是整个 vec 中第 k 大的数
	// greater<int> 创建最小堆。 less<int> 创建最大堆
	// 默认 priority_queue<int> pq 为最大堆
	priority_queue<int, vector<int>, greater<int>> pq;
	int sz;
	KthLargest(int k, vector<int>& nums) {
		sz = k;
		for (int n : nums) {
			pq.push(n);
			if (pq.size() > sz) 
				pq.pop();
		}
	}

	int add(int val) {
		pq.push(val);
		if (pq.size() > sz) 
			pq.pop();
		return pq.top();
	}
};

void testKthLargest()
{
	vector<int> nums({4,5,8,2,3,9,7,10,6});
	KthLargest kth(3, nums);
	int i = kth.add(3);
	i = kth.add(5);
	i = kth.add(10);
	i = kth.add(9);
	i = kth.add(4);
}

// https://leetcode.com/problems/check-if-it-is-a-straight-line/
// Ax + By + C = 0
// A = y2 - y1
// B = x1 - x2
// C = x2*y1 - x1*y2
void getParam(vector<int>& p1, vector<int>& p2, int& a, int& b, int& c)
{
	int x1 = p1[0], y1 = p1[1];
	int x2 = p2[0], y2 = p2[1];

	a = y2 - y1;
	b = x1 - x2;
	c = x2 * y1 - x1 * y2;
}

bool checkStraightLine(vector<vector<int>>& coordinates) 
{
	int a = 0, b = 0, c = 0;
	if (coordinates.size() == 2)
		return true;

	getParam(coordinates[0], coordinates[1], a, b, c);

	for (int i = 2; i < coordinates.size(); i++)
	{
		int y = coordinates[i][1];
		int x = coordinates[i][0];
		if (a *x + b*y + c != 0)
			return false;
	}

	return true;
}

void testcheckStraightLine()
{
	vector<vector<int>> coordinates({ {0,0},{0,5},{5,5},{5,0} });
	checkStraightLine(coordinates);
}

//https://leetcode.com/problems/add-two-numbers/description/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
	ListNode *l1Idx = l1, *l2Idx = l2, *listIdx = NULL;
	ListNode *ret = new ListNode(0);
	ListNode *retIdx = ret;

	int carry = 0;
	ListNode *retTmp = NULL;

	while (l1Idx != NULL || l2Idx != NULL)
	{
		if (l1Idx != NULL)
		{
			carry += l1Idx->val;
			l1Idx = l1Idx->next;
		}

		if (l2Idx != NULL)
		{
			carry += l2Idx->val;
			l2Idx = l2Idx->next;
		}

		if (carry >= 10)
		{
			retIdx->val = carry - 10;
			carry /= 10;
		}
		else
		{
			retIdx->val = carry;
			carry = 0;
		}

		if (l1Idx != NULL || l2Idx != NULL)
		{
			retIdx->next = new ListNode(0);
			retIdx = retIdx->next;
		}
	}

	if (carry)
	{
		retIdx->next = new ListNode(1);
		retIdx = retIdx->next;
	}

	return ret;
}

void testaddTwoNumbers()
{
	ListNode n1(2), n2(4), n3(3), n4(9), n5(9), n6(9), n7(9);

	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	//n4.next = &n5;
	//n5.next = &n6;
	//n6.next = &n7;

	ListNode k1(5), k2(6), k3(4), k4(9);
	k1.next = &k2;
	k2.next = &k3;
	//k3.next = &k4;

	addTwoNumbers(&n1, &k1);
}

// https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
struct TreeNodeLevel
{
	TreeNode* pNode;
	int level;
};


int maxLevelSum(TreeNode* root) 
{
	TreeNode *pidx = root;
	list<TreeNode *> nodeLevList1, nodeLevList2;
	nodeLevList1.push_back(root);

	list<TreeNode *> *pNodeLevListIdx = &nodeLevList1;

	int curlev = 1;
	int maxSum = root->val;
	int maxlev = 1;
	while (nodeLevList1.size() > 0)
	{
		int curSum = 0;
		size_t nodes = nodeLevList1.size();
		while (nodes > 0)
		{
			TreeNode *pNode = nodeLevList1.front();			
			curSum += pNode->val;
			nodeLevList1.pop_front();

			if (pNode->left != NULL)
				nodeLevList1.push_back(pNode->left);

			if (pNode->right!= NULL)
				nodeLevList1.push_back(pNode->right);

			nodes--;
		}

		if (curSum > maxSum)
		{
			maxSum = curSum;
			maxlev = curlev;
		}

		curlev++;
	}

	return maxlev;
}

// 1,7,0,7,-8,null,null
void testmaxSum()
{
	TreeNode n5(5), n3(3), n7(7), n2(2), n4(4), n1(1), n0(0), n6(6), n8(8), n9(9), n10(10);
	n5.left = &n3;
	n5.right = &n7;

	n3.left = &n2;
	n3.right = &n4;

	n2.left = &n1;
	n1.left = &n0;

	n7.left = &n6;
	n7.right = &n9;

	n9.left = &n8;
	n9.right = &n10;

	maxLevelSum(&n5);
}

//https://leetcode.com/problems/find-the-highest-altitude/description/
int largestAltitude(vector<int>& gain) 
{
	vector<int> altitude(gain.size() + 1);
	altitude[0] = 0;
	int maxAlt = 0;

	for (int i = 0; i < gain.size(); i++)
	{
		altitude[i + 1] = altitude[i] + gain[i];
		if (maxAlt < altitude[i + 1])
			maxAlt = altitude[i + 1];
	}

	return maxAlt;
}

void testlargestAltitude()
{
	vector<int> gain({ -4, -3, -2, -1, 4, 3, 2 });

	largestAltitude(gain);
}

//https://leetcode.com/problems/buddy-strings/
bool buddyStrings(string s, string goal) 
{
	if (s.size() != goal.size())
		return false;

	vector<int> diffVec;
	map<char, bool> dupChar;
	bool hasDupChar = false;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != goal[i])
			diffVec.push_back(i);

		if (diffVec.size() > 2)
			return false;

		if (hasDupChar == false)
		{
			if (dupChar.find(s[i]) == dupChar.end())
				dupChar[s[i]] = true;
			else
				hasDupChar = true;
		}		
	}

	if (diffVec.size() == 0)
	{
		return hasDupChar;
	}

	if (diffVec.size() == 1)
		return false;

	return (s[diffVec[0]] == goal[diffVec[1]] && s[diffVec[1]] == goal[diffVec[0]]);
}

void testbuddyStrings()
{
	string s("aa"), goal("aa");
	bool b = buddyStrings(s, goal);
}



//https://leetcode.com/problems/longest-consecutive-sequence/
int longestConsecutive(vector<int>& nums) 
{
	map<int, int> nums_map;
	size_t i = 0;

	for (; i < nums.size(); i++)
	{
		if (nums_map.find(nums[i]) != nums_map.end())
		{
			nums_map[nums[i]] += 1;
		}
		else
		{
			nums_map[nums[i]] = 1;
		}
	}

	int best = 0, max_best = 0;
	map<int, int>::iterator itor = nums_map.begin();
	while (itor!= nums_map.end())
	{
		int tmp = itor->first - 1;
		if (nums_map.find(tmp) == nums_map.end())
		{
			tmp++;			
			best = 0;			
			while (nums_map.find(tmp) != nums_map.end())
			{				
				best++;
				tmp++;
			}
		}

		if (max_best < best)
		{
			max_best = best;
			best = 0;
		}
		itor++;
	}

	return max_best;
}

void testlongestConsecutive()
{
	vector<int> nums({ 0,3,7,2,5,8,4,6,0,1 });

	int best = longestConsecutive(nums);
}

//https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/
class PairDiff
{
public:
	int i;
	int j;
	int diff;

	bool operator < (const PairDiff &a)
	{
		return this->diff < a.diff;
	}

	bool operator > (const PairDiff &a)
	{
		return this->diff > a.diff;
	}

	bool operator== (const PairDiff &a)
	{
		return (this->i == a.i || this->j == a.j);
	}

	PairDiff& operator = (const PairDiff& a)
	{
		this->i = a.i;
		this->j = a.j;
		this->diff = a.diff;

		return *this;
	}

	PairDiff(int i, int j, int diff)
	{
		this->i = i;
		this->j = j;
		this->diff = diff;
	}
};

int minimizeMax(vector<int>& nums, int p) 
{
	if (nums.size() < p * 2)
		return 0;

	int max = 0;

	vector<PairDiff> diffList;

	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = i + 1; j < nums.size(); j++)
		{
			PairDiff diff(i, j, abs(nums[i] - nums[j]));
			
			diffList.push_back(diff);
		}
	}

	sort(diffList.begin(), diffList.end());
	bool hasDupPair = true;
	int dedupedPairs = 0;

	vector<PairDiff>::iterator itor = diffList.begin();
	while (itor != diffList.end() && dedupedPairs < p)
	{
		vector<PairDiff>::iterator itor2 = std::next(itor);
		while (itor2 != diffList.end())
		{
			if (itor->i == itor2->i || itor->j == itor2->j)
			{
				itor2 = diffList.erase(itor2);
			}
			else
				itor2++;
		}
		itor++;
		dedupedPairs++;
	}

	if (diffList.size() < p)
		return 0;

	itor = diffList.begin();
	max = itor->diff;
	itor++;
	int i = 0;
	while (itor != diffList.end() && i < p)
	{
		if (max < itor->diff)
			max = itor->diff;
	}

	return max;
}


void testminimizeMax()
{
	vector<int> nums({ 10,1,2,7,1,3 });

	minimizeMax(nums, 2);
}

// https://leetcode.com/problems/01-matrix/
int findZeroDist(map<int, vector<int>>& zeroPosMapRow, map<int, vector<int>>& zeroPosMapCol, int row, int col)
{
	int minDist = INT32_MAX;
	static int lastMinRow = 0, lastMinCol = 0;

	map<int, vector<int>>::iterator rowItor = zeroPosMapRow.begin();
	while (rowItor != zeroPosMapRow.end())
	{
		int rowIdx = rowItor->first;
		int rowDist = std::abs(row - rowIdx);		

		if (rowDist >= minDist)
		{	
			break;
		}

		for (int colIdx = 0; colIdx < rowItor->second.size(); colIdx++)
		{
			int colDist = std::abs(col - rowItor->second[colIdx]);

			if (colDist >= minDist)
				continue;

			int dist = rowDist + colDist;
			if (minDist > dist)
				minDist = dist;

			if (minDist == 1)
				return minDist;
		}
		rowItor++;
	}

	return minDist;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) 
{	
	vector<vector<int>> ret(mat.size(), vector<int>(mat[0].size(), 0));

	map<int, vector<int>> zeroPosMapRow, zeroPosMapCol;

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
		{
			if (mat[i][j] == 0)
			{
				if (zeroPosMapRow.find(i) == zeroPosMapRow.end())
				{
					zeroPosMapRow[i] = vector<int>();
				}
				zeroPosMapRow[i].push_back(j);

				if (zeroPosMapCol.find(j) == zeroPosMapCol.end())
				{
					zeroPosMapCol[j] = vector<int>();
				}
				zeroPosMapCol[j].push_back(i);
			}
		}
	}

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
		{
			if (mat[i][j] != 0)
			{
				ret[i][j] = findZeroDist(zeroPosMapRow, zeroPosMapCol, i, j);
			}
		}
	}

	return ret;
}


vector<vector<int>> updateMatrix_2(vector<vector<int>>& mat)
{
	vector<vector<int>> ret(mat.size(), vector<int>(mat[0].size(), 0));
	
	int minDist = INT32_MAX, lastMinRow = 0, lastMinCol = 0;

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
		{
			if (mat[i][j] != 0)
			{
				minDist = INT32_MAX;
				for (int rowIdx = lastMinRow; rowIdx < mat.size(); rowIdx++)
				{
					int rowDist = std::abs(i - rowIdx);
					if (rowDist >= minDist)
						continue;

					for (int colIdx = lastMinCol; colIdx < mat[0].size() && mat[rowIdx][colIdx] == 0; colIdx++)
					{
						int colDist = std::abs(j - colIdx);
						if (colDist >= minDist)
							continue;

						int dist = rowDist + colDist;
						if (minDist > dist)
						{
							minDist = dist;
							lastMinRow = rowIdx;
							lastMinCol = colIdx;
						}
					}
				}
				ret[i][j] = minDist;
			}
		}
	}

	return ret;
}
void testupdateMatrix()
{
	vector<vector<int>> mat({ {0,0,0}, {0,1,0}, {1,1,1} });

	updateMatrix(mat);
}

//https://leetcode.com/problems/excel-sheet-column-title/
string convertToTitle(int columnNumber) 
{
	string ret;
	char titleMap[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y', 'Z'};

	while (columnNumber > 0)
	{
		columnNumber--;		
		ret.insert(ret.begin(), titleMap[columnNumber % 26]);
		columnNumber /= 26;
	}

	return ret;
}

void testconvertToTitle()
{
	string ret;
	ret = convertToTitle(28);
}

//https://leetcode.com/problems/reverse-linked-list/
ListNode* reverseList(ListNode* head) 
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode *pTmp = NULL, *pTmp2 = NULL, *pTmp3 = NULL;

	if (head->next->next == NULL)
	{
		pTmp = head->next;
		head->next = NULL;
		pTmp->next = head;
		head = pTmp;
		return head;
	}

	pTmp = head;
	pTmp2 = head->next;
	head->next = NULL;
	while (pTmp2 != NULL)
	{
		pTmp3 = pTmp2->next;
		pTmp2->next = pTmp;
		pTmp = pTmp2;
		pTmp2 = pTmp3;
	}
	head = pTmp;

	return head;
}

//https://leetcode.com/problems/generate-parentheses/
void solve(string op, int open, int close, vector<string> &ans) {
	if (open == 0 && close == 0) {
		ans.push_back(op);
		return;
	}
	//when count of open and close brackets are same then 
	//we have only one choice to put open bracket 
	if (open == close) {
		string op1 = op;
		op1.push_back('(');
		solve(op1, open - 1, close, ans);
	}
	else if (open == 0) {
		//only choice is to put close brackets 
		string op1 = op;
		op1.push_back(')');
		solve(op1, open, close - 1, ans);
	}
	else if (close == 0) {
		//only choise is to use open bracket 
		string op1 = op;
		op1.push_back('(');
		solve(op1, open - 1, close, ans);
	}
	else {
		string op1 = op;
		string op2 = op;
		op1.push_back('(');
		op2.push_back(')');
		solve(op1, open - 1, close, ans);
		solve(op2, open, close - 1, ans);
	}
}
vector<string> generateParenthesis(int n) {
	int open = n;
	int close = n;
	vector<string> ans;
	string op = "";
	solve(op, open, close, ans);
	return ans;
}

//https://leetcode.com/problems/reverse-integer/
// [-2^31, 2^31 - 1]
// 964632435 
//INT_MAX  INT_MIN

int reverse(int x)
{
	if (x == 0)
		return x;

	int ret = 0;
	int ten_pow = 0;
	while (x != 0)
	{
		int mod = x % 10;
		if (x > 0)
		{
			if (ret > INT_MAX / 10)
				return 0;
		}
		else
		{
			if (ret < INT_MIN / 10)
				return 0;
		}
		ret = ret * 10 + x % 10;
		x /= 10;
	}
	
	return ret;
}

void reverseTest()
{
	reverse(1463847412);
}

//https://leetcode.com/problems/string-to-integer-atoi/
int DoMyAtoi(string s, size_t idx, int sign)
{
	long long ret = 0;
	for (size_t i = idx; i < s.length(); i++)
	{
		char c = s[i];
		if (c >= '0' && c <= '9')
		{
			ret = ret * 10 + (c - '0')*sign;		
			
			if (ret >= INT_MAX)
				return INT_MAX;
			else if (ret < INT_MIN)
				return INT_MIN;			
		}
		else
		    break;
	}

	return (int)ret;
}

int myAtoi(string s) 
{
	int ret = 0;
	int sign = 1;
	for (size_t i = 0; i < s.size(); ++i)
	{
		char c = s[i];
		if (c == ' ')
			continue;
		if (c == '+' || c == '-' || (c >= '0' && c <= '9'))
		{
			if (c == '+')
			{
				sign = 1;
				i++;
			}
			else if (c == '-')
			{
				sign = -1;
				i++;
			}

			return DoMyAtoi(s, i, sign);
		}
		else
			break;
	}
	return ret;
}

void testmyAtoi()
{
	string s("  -042");
	myAtoi(s);
}

//https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/
int countTriplets(vector<int>& arr)
{
	int ret = 0;
	int a = 0, b = 0;	
	size_t i = 0, j = 0, k = 0;
	for (i = 0; i < arr.size() - 1; i++)
	{
		a = 0;		
		for (j = i + 1; j < arr.size(); j++)
		{			
			a ^= arr[j - 1];

			b = 0;
			for (k = j; k < arr.size(); k++)
			{
				b ^= arr[k];
				if (a == b)
					ret++;
			}
		}
	}
	return ret;
}

void testcountTriplets()
{
//	vector<int> arr({ 2,3,1,6,7 });
	vector<int> arr({ 1,1,1,1,1 });

	countTriplets(arr);

	return;
}


//https://leetcode.com/problems/hand-of-straights/description/
bool isNStraightHand(vector<int>& hand, int groupSize)
{
	if (hand.size() % groupSize != 0)
		return false;

	if (hand.size() == 1 && groupSize == 1)
		return true;

	vector<bool> handUsed(hand.size(), false);

	sort(hand.begin(), hand.end());

	size_t i = 1;
	handUsed[0] = true;
	int preGroupVal = hand[0];
	while (i < hand.size())
	{
		int oneGroupSize = 1;
		size_t groupIdx = i;		
		while (oneGroupSize < groupSize && groupIdx < hand.size())
		{
			if (hand[groupIdx] - 1 == preGroupVal && handUsed[groupIdx] == false)
			{
				oneGroupSize++;
				handUsed[groupIdx] = true;
				preGroupVal = hand[groupIdx];				
			}

			groupIdx++;
		}

		if (oneGroupSize != groupSize)
			return false;

		if (groupIdx == hand.size())
			break;

		while (i < hand.size() && handUsed[i] == true)
			i++;

		if (i >= hand.size())
			break;

		preGroupVal = hand[i];
		handUsed[i] = true;
	}

	for (; i < hand.size(); i++)
	{
		if (handUsed[i] == false)
		    return false;
	}

	return true;
}

bool testisNStraightHand()
{
	//vector<int> hand({ 1,2,3,6,2,3,4,7,8});
	vector<int> hand({ 2,1,2,4,1,3,3,3 });
	bool b = isNStraightHand(hand, 2);
	return b;
}

//https://leetcode.com/problems/container-with-most-water/description/
int maxArea(vector<int>& height) 
{
	int i = 0, j = height.size() - 1;
	int area = (j - i) * std::min(height[i], height[j]);
	while (i < j)
	{
		area = std::max(area, (j - i) * std::min(height[i], height[j]));
		if (height[i] < height[j])
			i++;
		else
			j--;
	}

	return area;
}

void testmaxArea()
{
	//vector<int> height({ 1,8,6,2,5,4,8,3,7 });
	vector<int> height({ 1,1 });
	maxArea(height);
}

// https://leetcode.com/problems/most-profit-assigning-work/description/
/*
class Solution {
	public int maxProfitAssignment(int[] difficulty, int[] profit, int[] worker) {
		int maxDifficulty = 0;
		for (int d : difficulty) {
			maxDifficulty = Math.max(maxDifficulty, d);
		}

		int[] maxProfitUpToDifficulty = new int[maxDifficulty + 1];
		for (int i = 0; i < difficulty.length; i++) {
			maxProfitUpToDifficulty[difficulty[i]] = Math.max(maxProfitUpToDifficulty[difficulty[i]], profit[i]);
		}

		for (int i = 1; i <= maxDifficulty; i++) {
			maxProfitUpToDifficulty[i] = Math.max(maxProfitUpToDifficulty[i], maxProfitUpToDifficulty[i - 1]);
		}

		int totalProfit = 0;
		for (int ability : worker) {
			if (ability > maxDifficulty) {
				totalProfit += maxProfitUpToDifficulty[maxDifficulty];
			}
			else {
				totalProfit += maxProfitUpToDifficulty[ability];
			}
		}

		return totalProfit;
	}
*/

struct diff_pro_struct {
	int diff;
	int profit;

	bool operator<(diff_pro_struct& b) const {
		return diff < b.diff;
	}
};

int maxProfitAssignment_slow(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) 
{
	if (difficulty.size() != profit.size())
		return 0;

	int maxprofit = 0;
	size_t w = 0;
	vector<diff_pro_struct> diff_pro(difficulty.size());
	for (size_t d = 0; d < difficulty.size(); d++)
	{
		diff_pro[d].diff = difficulty[d];
		diff_pro[d].profit = profit[d];
	}

	sort(diff_pro.begin(), diff_pro.end());

	vector<vector<int> > w_cap_vec;
	for (; w < worker.size(); w++)
	{
		int max_p = 0;
		for (size_t d = 0; d < difficulty.size() && diff_pro[d].diff <= worker[w]; d++)
		{
			if (max_p < diff_pro[d].profit)
			{
				max_p = diff_pro[d].profit;
			}
		}

		maxprofit += max_p;
	}

	return maxprofit;
}


int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker)
{
	if (difficulty.size() != profit.size())
		return 0;

	int maxprofit = 0;

	int max_diff = 0;
	size_t i = 0;
	for (; i < difficulty.size(); i++)
	{
		if (max_diff < difficulty[i])
			max_diff = difficulty[i];
	}

	vector<int> maxProToDiff(max_diff + 1);
	for (i = 0; i < difficulty.size(); i++)
	{
		maxProToDiff[difficulty[i]] = std::max(maxProToDiff[difficulty[i]], profit[i]);
	}

	for (i = 1; i <= max_diff; i++)
	{
		maxProToDiff[i] = std::max(maxProToDiff[i - 1], maxProToDiff[i]);
	}

	for (i = 0; i < worker.size(); i++)
	{
		if (worker[i] > max_diff)
			maxprofit += maxProToDiff[max_diff];
		else
			maxprofit += maxProToDiff[worker[i]];
	}

	return maxprofit;
}

void testmaxProfitAssignment()
{
	vector<int> difficulty({  2, 4, 6, 8, 10 }), profit({10, 20, 30, 40, 50 }), worker({ 4, 5, 6, 7 });	

	maxProfitAssignment(difficulty, profit, worker);
}

//https://leetcode.com/problems/successful-pairs-of-spells-and-potions/description/
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {

	vector<int> ret(spells.size(), 0);

	sort(potions.begin(), potions.end());
	int total = potions.size();
	for (size_t s = 0; s < spells.size(); s++)
	{
		long long least_p = success / spells[s];
		if (success % spells[s] != 0)
			least_p++;

		// 二分查找时， right = size - 1， 循环时判断 left 小于等于 right
		// 循环结束时，left 指向第一个大于等于 target 的位置
		// 注意: left, right 应该用 int，不要用 u_int，因为如果：
		// m = (0 + 1)/2 = 0, 此时 u_int r = m -1 就会溢出
		// 还可以直接用 lower_bound() 进行查找

		int l = 0, r = potions.size() - 1;
		int m = r / 2;
		
		int idx = total;
		while (l <= r)
		{
			m = (l + r) / 2;
			if (potions[m] >= least_p)
			{
				r = m - 1;
				idx = m;
			}
			else
			{
				l = m + 1;
			}			
		}

		ret[s] = max(total - idx, 0);
	}
	return ret;
}

vector<int> successfulPairs_slow(vector<int>& spells, vector<int>& potions, long long success) {

	vector<int> ret(spells.size(), 0);

	map<int, int> sepll_success, postions_pos;
	std::sort(potions.begin(), potions.end(), greater<int>());

	for (size_t p = 0; p < potions.size(); p++)
		postions_pos[potions[p]] = p;
	
	for (size_t s = 0; s < spells.size(); s++)
	{
		if (sepll_success.find(spells[s]) != sepll_success.end())
		{
			ret[s] = sepll_success[spells[s]];
			continue;
		}

		long long least_postion = success / spells[s];
		if (success % spells[s] != 0)
			least_postion++;

		if (least_postion > potions[0])
		{
			ret[s] = 0;
			sepll_success[spells[s]] = 0;
			continue;
		}

		while (postions_pos.find(least_postion) == postions_pos.end())
			least_postion++;

		ret[s] = postions_pos[least_postion] + 1;
		sepll_success[spells[s]] = postions_pos[least_postion] + 1;
	}
	return ret;
}

void testsuccessfulPairs()
{
	vector<int> spells({ 5,1,3 });
	vector<int> potions({ 1,2,3,4,5 });

	successfulPairs(spells, potions, 1000000000);
}

//https://leetcode.com/problems/maximum-matching-of-players-with-trainers/description/
int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) 
{
	if (players.size() == 0 || trainers.size() == 0)
		return 0;

	if (players.size() == 1)
	{
		for (size_t t = 0; t < trainers.size(); t++)
		{
			if (trainers[t] >= players[0])
				return 1;
		}

		return 0;
	}

	if (trainers.size() == 1)
	{
		for (size_t p = 0; p < players.size(); p++)
		{
			if (players[p] <= trainers[0])
				return 1;
		}

		return 0;
	}

	int match = 0;
	std::sort(players.begin(), players.end());
	std::sort(trainers.begin(), trainers.end());

	size_t s = 0;
	int l = s, r = trainers.size() - 1;
	bool found = false;
	for (size_t p = 0; p < players.size(); p++)
	{
		found = false;
		
		while (l <= r)
		{
			size_t m = (l + r) / 2;
			if (trainers[m] >= players[p])
			{
				s = m;
				r = m - 1;
				found = true;
			}
			else
			{
				l = m + 1;
			}
		}
		if (found)
			match++;

		if (s + 1 >= trainers.size())
			break;

		l = s + 1;
		r = trainers.size() - 1;
	}

	return match;
}

void testmatchPlayersAndTrainers()
{
	vector<int> players({ 1,1000000000 });
	vector<int> trainers({ 1000000000,1 });
	matchPlayersAndTrainers(players, trainers);
}

//https://leetcode.com/problems/largest-merge-of-two-strings/description/
bool mergeChar(string& word1, size_t &i1, string& word2, size_t &i2, string& ret)
{
	if (i1 >= word1.size() || i2 >= word2.size() || word1[i1] == word2[i2])
		return false;

	if (word1[i1] > word2[i2])
	{
		ret.push_back(word1[i1]);
		i1++;
	}
	else if (word1[i1] < word2[i2])
	{
		ret.push_back(word2[i2]);
		i2++;
	}

	return true;
}

//cabaa
//bcaaa
//cbcabaaaaa
string largestMerge_1(string s1, string s2) {
	if (s1.size() == 0 || s2.size() == 0)
		return s1 + s2;
	if (s1 > s2)
		return s1[0] + largestMerge_1(s1.substr(1), s2);

	return s2[0] + largestMerge_1(s1, s2.substr(1));
}

string largestMerge_2(string w1, string w2) {
	string res;
	int i = 0, j = 0;
	while (i < w1.size() && j < w2.size()) {
		if (w1.compare(i, w1.size() - i, w2, j, w2.size() - j) > 0)
			res += w1[i++];
		else
			res += w2[j++];
	}
	res = res + w1.substr(i) + w2.substr(j);

	return res;
}

string largestMerge(string word1, string word2) 
{
	string ret;
	size_t i1 = 0, i2 = 0;
	size_t tmp_i1 = i1, tmp_i2 = i2;
	while (i1 < word1.size() && i2 < word2.size())
	{
		if (!mergeChar(word1, i1, word2, i2, ret))		
		{
			tmp_i1 = i1, tmp_i2 = i2;
			while (word1[tmp_i1] == word2[tmp_i2] && tmp_i1 < word1.size() && tmp_i2 < word2.size())
			{
				tmp_i1++;
				tmp_i2++;
			}

			if (tmp_i1 >= word1.size())
			{
				ret.append(word1.substr(i1));
				ret.append(word2.substr(i2));
				return ret;
			}

			if (tmp_i2 >= word2.size())
			{
				ret.append(word2.substr(i2));
				ret.append(word1.substr(i1));
				return ret;
			}

			if (word1[tmp_i1] > word2[tmp_i2])
			{
				ret.append(word1.substr(i1, tmp_i1 - i1 + 1));
				i1 = tmp_i1 + 1;
			}
			else
			{
				ret.append(word2.substr(i2, tmp_i2 - i2 + 1));
				i2 = tmp_i2 + 1;
			}
		}
	}

	if (i1 >= word1.size() && i1 < word2.size())
	{
		ret.append(word2.substr(i2));
	}
	if (i2 >= word2.size() && i1 < word1.size())
	{
		ret.append(word1.substr(i1));
	}
	return ret;
}

void testlargestMerge()
{
	string word1("guguuuuuuuuuuuuuuguguuuuguug");
	string word2("gguggggggguuggguugggggg");
	largestMerge(word1, word2);
}

// https://leetcode.com/problems/lucky-numbers-in-a-matrix/description/
vector<int> luckyNumbers(vector<vector<int>>& matrix)
{
	vector<int> ret;
	map<int, int> rowminMap;
	map<int, int> colmaxMap;

	for (size_t r = 0; r < matrix.size(); r++)
	{
		rowminMap[r] = 0;
		
		for (size_t c = 0; c < matrix[0].size(); c++)
		{
			if (colmaxMap.find(c) == colmaxMap.end())
			{
				colmaxMap[c] = 0;
			}

			if (matrix[r][c] < matrix[r][rowminMap[r]])
			{
				rowminMap[r] = c;
			}

			if (matrix[r][c] > matrix[colmaxMap[c]][c])
				colmaxMap[c] = r;
		}
	}

	map<int, int>::iterator itor(rowminMap.begin());
	for (; itor != rowminMap.end(); itor++)
	{
		int r = itor->first;
		int c = itor->second;

		if (colmaxMap.find(c) != colmaxMap.end() && colmaxMap[c] == r)
			ret.push_back(matrix[r][c]);
	}

	return ret;
}

void testluckyNumbers()
{
//	vector<vector<int>> matrix({ {1, 10, 4, 2},{9, 3, 8, 7},{15, 16, 17, 12} });
	vector<vector<int>> matrix({ {3, 7, 8} ,{9, 11, 13},{15, 16, 17} });

	luckyNumbers(matrix);
}

//https://leetcode.com/problems/sort-array-by-increasing-frequency/description/
vector<int> frequencySort(vector<int>& nums) 
{
	vector<int> ret;
	map<int, int> freqMap;
	vector<int> distinctNum;

	for (int i = 0; i < nums.size(); i++)
	{
		if (freqMap.find(nums[i]) == freqMap.end())
		{
			freqMap[nums[i]] = 1;
			distinctNum.push_back(nums[i]);
		}
		else
		{
			freqMap[nums[i]] += 1;
		}
	}

	// 使用匿名函数进行排序， distinctNum 为待排序的数组
	// freqMap 为 distinctNum 中每个数字出现的次数，根据出现的次数对 distinctNum 进行降序排序，出现次数少的排前面，
	// 如果出现的次数相等，则根据数字的大小进行排序
	sort(distinctNum.begin(), distinctNum.end(), 
		[&](int a, int b)
		{
			if (freqMap[a] == freqMap[b])
				return a > b;

			return freqMap[a] < freqMap[b];
		});

	for (int i = 0; i < distinctNum.size(); i++)
	{
		ret.insert(ret.end(), freqMap[distinctNum[i]], distinctNum[i]);
	}

	return ret;
}


void testfrequencySort()
{
	vector<int> nums({ -1,1,-6,4,5,-6,1,4,1 });
	
	frequencySort(nums);
}

//https://leetcode.com/problems/sort-the-jumbled-numbers/description/
vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) 
{
	vector<int> ret;
	vector<int> mappedNums;
	std::vector<size_t> indices(nums.size());
	std::iota(indices.begin(), indices.end(), 0);

	for (int i = 0; i < nums.size(); i++)
	{
		int num = nums[i];
		int mappedNum = 0;
		int pow_10 = 0;
		if (num < 10)
		{
			mappedNums.push_back(mapping[num]);
		}
		else
		{
			while (num > 0)
			{
				mappedNum = mapping[num % 10] * pow(10, pow_10) + mappedNum;
				num /= 10;
				pow_10++;
			}
			mappedNums.push_back(mappedNum);
		}		
	}

	std::sort(indices.begin(), indices.end(), 
		[&](int i, int j)
		{
			return mappedNums[i] < mappedNums[j];

		});

	for (int i = 0; i < indices.size(); i++)
		ret.push_back(nums[indices[i]]);

	return ret;
}

void testsortJumbled()
{
	vector<int>  mapping({ 9,8,7,6,5,4,3,2,1,0 }), nums({ 0,1,2,3,4,5,6,7,8,9 });
	sortJumbled(mapping, nums);
}

//https://leetcode.com/problems/map-sum-pairs/description/
class MapSum 
{
public:
	map<string, int> keyVal;
	MapSum()
	{
	}

	void insert(string key, int val) 
	{
		keyVal[key] = val;
	}

	int sum(string prefix)
	{
		map<string, int>::iterator itor;
		int ret = 0;
		for (itor = keyVal.begin(); itor != keyVal.end(); itor++)
		{
			string key = itor->first.substr(0, prefix.size());
			if (key.compare(prefix) == 0)
				ret += itor->second;
		}
		return ret;
	}
};

void testMapSum()
{
	string key("apple");
	int val = 3;
	string prefix("ap");

	MapSum* obj = new MapSum();
	obj->insert(key, val);
	int param_2 = obj->sum(prefix);
}

//https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/description/
int minimumDeletions(string s) {
	int ret = 0;

	return ret;
}
/*
def minimumDeletions(self, s: str) -> int:
	b_count = del_a_count = i = res = 0
	while i < len(s) :
		if s[i] == 'b' :
			b_count += 1
			if i + 1 < len(s) and s[i + 1] == 'a' :
				a_count = 0
				j = i + 1
				while j < len(s) and s[j] == 'a' :
					a_count += 1
					j += 1
				if a_count < b_count - del_a_count :
					res += a_count
					del_a_count += a_count
				else:
					res += b_count
					res -= del_a_count # correct the internal a's
					b_count = del_a_count = 0
				i = j  # can directly jump to j
			else:
				i += 1
		else:
			i += 1

	return res
*/
void testminimumDeletions()
{
	string s("aababbab");
	minimumDeletions(s);
}

//https://leetcode.com/problems/kth-distinct-string-in-an-array/description/
string kthDistinct(vector<string>& arr, int k) 
{
	string ret;
	map<string, int> dictStr;
	vector<int> strCnt(arr.size(), 0);
	int kth = 0;	
	for (int i = 0; i < arr.size(); i++)
	{
		if (dictStr.find(arr[i]) == dictStr.end())
		{
			dictStr[arr[i]] = true;
		}
		else
		{
			dictStr[arr[i]] = false;
		}
	}

	for (int i = 0; i < arr.size(); i++)
	{
		if (dictStr[arr[i]])
		{
			kth++;
			if (kth == k)
				return arr[i];
		}
	}

	return ret;
}

void testkthDistinct()
{
	vector<string> arr({ "d", "b", "c", "b", "c", "a" });
	int k = 2;

	kthDistinct(arr, k);
}

//https://leetcode.com/problems/spiral-matrix/description/
vector<int> spiralOrder(vector<vector<int>>& matrix) 
{
	vector<int> ret;

	const int left = 1, right = 2, up = 3, down = 4;
	int dir = right;
	int row = 0, col = matrix[0].size() - 1;

	int start_r = 0, end_r = matrix.size() - 1;
	int start_c = 0, end_c = matrix[0].size() - 1;
	int i = 0;
	while (start_r <= end_r && start_c <= end_c)
	{
		switch (dir) 
		{
		case right:
			for (i = start_c; i <= end_c; i++)
				ret.push_back(matrix[row][i]);

			start_r++;
			col = end_c;

			dir = down;
			break;

		case down:
			for (i = start_r; i <= end_r; i++)
				ret.push_back(matrix[i][col]);
			end_c--;			
			row = end_r;

			dir = left;
			break;

		case left:
			for (i = end_c; i >= start_c; i--)
				ret.push_back(matrix[row][i]);

			end_r--;
			col = start_c;

			dir = up;
		    break;

		case up:
			for (i = end_r; i >= start_r; i--)
				ret.push_back(matrix[i][col]);

			start_c++;
			row = start_r;

			dir = right;
			break;
		default:
			break;
		}
	}

	
	return ret;
}

void testspiralOrder()
{

	vector<vector<int>> matrix2({ {1,  2,  3,  4 }, 
								 {5,  6,  7,  8 }, 
								 {9, 10, 11, 12} });

	vector<vector<int>> matrix({ {1,  2,  3,  },
								 {5,  6,  7,  },
								 {9, 10, 11, } });

	vector<vector<int>> matrix3({ {1,   2,  3,  },
								  {5,   6,  7,  },
								  {9,  10,  11, },
								  {12, 13, 14},
								  {15, 16, 17} });

	spiralOrder(matrix3);
}

//https://leetcode.com/problems/spiral-matrix-ii/description/
vector<vector<int>> generateMatrix(int n) 
{
	vector<vector<int>> ret(n);
	int i = 0;
	for (; i < n; i++)
		ret[i].resize(n);

	const int left = 1, right = 2, up = 3, down = 4;
	int dir = right;
	int row = 0, col = n - 1;

	int start_r = 0, end_r = n - 1;
	int start_c = 0, end_c = n - 1;
	
	int cur_num = 1;
	while (start_r <= end_r && start_c <= end_c)
	{
		switch (dir)
		{
		case right:	
			for (i = start_c; i <= end_c; i++)
			{
				ret[row][i] = cur_num;
				cur_num++;
			}
			start_r++;
			col = end_c;

			dir = down;
			break;

		case down:
			for (i = start_r; i <= end_r; i++)
			{
				ret[i][col] = cur_num;
				cur_num++;
			}
			end_c--;
			row = end_r;

			dir = left;
			break;

		case left:
			for (i = end_c; i >= start_c; i--)
			{
				ret[row][i] = cur_num;
				cur_num++;
			}
			end_r--;
			col = start_c;

			dir = up;
			break;

		case up:
			for (i = end_r; i >= start_r; i--)
			{
				ret[i][col] = cur_num;
				cur_num++;
			}
			start_c++;
			row = start_r;

			dir = right;
			break;
		default:
			break;
		}
	}

	return ret;
}

void testgenerateMatrix()
{
	generateMatrix(5);
}

//https://leetcode.com/problems/magic-squares-in-grid/
bool IsMagicSquare(vector<vector<int>>& grid, int start_r, int start_c)
{
	if (start_r >= grid.size() || start_r + 2 > grid.size() - 1 ||
		start_c >= grid[0].size() || start_c + 2 > grid[0].size() - 1)
		return false;

	vector<int> dict(10, 0);

	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {			
			int num = grid[start_r + x][start_c + y];
			if (num < 1 || num > 9 || dict[num] > 0)
				return false;
			dict[num] = 1;
		}
	}

	int diagonals1 = grid[start_r][start_c]    +  grid[start_r+1][start_c+1] + grid[start_r + 2][start_c + 2];
	int diagonals2 = grid[start_r][start_c + 2] + grid[start_r+1][start_c+1]     +  grid[start_r + 2][start_c];
	
	int row1 = grid[start_r][start_c] + grid[start_r][start_c + 1] + grid[start_r][start_c + 2];
	int row2 = grid[start_r + 1][start_c] + grid[start_r + 1][start_c + 1] + grid[start_r + 1][start_c + 2];
	int row3 = grid[start_r + 2][start_c] + grid[start_r + 2][start_c + 1] + grid[start_r + 2][start_c + 2];

	int col1 = grid[start_r][start_c] + grid[start_r + 1][start_c] + grid[start_r + 2][start_c];
	int col2 = grid[start_r][start_c + 1] + grid[start_r + 1][start_c + 1] + grid[start_r + 2][start_c + 1];
	int col3 = grid[start_r][start_c + 2] + grid[start_r + 1][start_c + 2] + grid[start_r + 2][start_c + 2];

	return  (diagonals1 == diagonals2 && 
		     row1 == row2 && row2 == row3 &&
		     col1 == col2 && col2 == col3);
}

int numMagicSquaresInside(vector<vector<int>>& grid) {
	if (grid.size() < 3 || grid[0].size() < 3)
		return 0;

	int ret = 0;
	for (int i = 0; i <= grid.size() - 3; i++)
	{
		for (int j = 0; j <= grid[0].size() - 3; j++)
		{
			if (IsMagicSquare(grid, i, j))
				ret++;
		}
	}

	return ret;

}

void testnumMagicSquaresInside()
{
//	vector<vector<int>> grid({{ 4, 3, 8, 4 }, { 9, 5, 1, 9 }, { 2, 7, 6, 2 }});
//	vector<vector<int>> grid({ {4, 7, 8} , {9, 5, 1}, {2, 3, 6 }});
	vector<vector<int>> grid({ { 5, 5, 5},{5, 5, 5},{5, 5, 5} });

	numMagicSquaresInside(grid);
}

//https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/
int getcount(vector<int>& nums, int maxdict)
{
	int count = 0;
	int i = 0, j = 0;
	for (i = 0; i < nums.size(); i++)
	{
		for (; j < nums.size() && nums[j] - nums[i] <= maxdict; j++);
		count += j - i - 1;
	}

	return count;
}

int smallestDistancePair(vector<int>& nums, int k) 
{
	int ret = 0;
	sort(nums.begin(), nums.end());

	int l = 0; 
	int r = nums[nums.size() - 1] - nums[0];	
	int m = 0;
	while (l < r)
	{
		m = (l + r) / 2;
		ret = getcount(nums, m);
		if (ret < k)
			l = m + 1; 
		else
			r = m;
	}

	return l;
}

void testsmallestDistancePair()
{
	vector<int> nums({ 1,2,0,2,1,0,1,1,0,2,2,0,2,0,1,1,1,0,1,0,1,1,2,2,2,2,0,0,2,1,2,1,2,0,0,0,1,0,0,1,0,2,1,1,1,1,0,2,2,1,0,2,0,2,2,2,1,0,2,2,2,2,0,0,1,0,1,1,2,1,2,2,1,1,0,2,0,1,0,1,1,2,0,1,1,1,1,2,0,2,2,0,0,1,1,1,1,2,1,2,2,1,2,0,1,2,2,1,1,2,1,0,1,1,1 });

	int k = smallestDistancePair(nums, 2204);
}

// https://leetcode.com/problems/median-of-two-sorted-arrays/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
{
	if (nums1.size() == 0)
	{
		if (nums2.size() % 2 == 0)
		{
			return (double(nums2[nums2.size() / 2]) + double(nums2[nums2.size() / 2 - 1]))/2;
		}
		else
		{
			return double(nums2[nums2.size() / 2]);
		}
	}

	if (nums2.size() == 0)
	{
		if (nums1.size() % 2 == 0)
		{
			return (double(nums1[nums1.size() / 2]) + double(nums1[nums1.size() / 2 - 1]))/2;
		}
		else
		{
			return double(nums1[nums1.size() / 2]);
		}
	}

	double ret = 0.0;
	int i = 0, j = 0, k = 0;
	vector<int> merge;
	while (i < nums1.size() && j < nums2.size())
	{
		if (nums1[i] <= nums2[j])
		{
			merge.push_back(nums1[i++]);
		}
		else
		{
			merge.push_back(nums2[j++]);
		}
	}
	if (i < nums1.size())
	{
		merge.insert(merge.end(), nums1.begin() + i, nums1.end());
	}
	else if (j < nums2.size())
	{
		merge.insert(merge.end(), nums2.begin() + j, nums2.end());
	}

	int n = nums1.size() + nums2.size();

	if (n % 2 == 0)
		ret = (double(merge[n / 2]) + double(merge[n / 2 - 1])) / 2;
	else
		ret = double(merge[n / 2]);

	return ret;
}

void testfindMedianSortedArrays()
{
	vector<int> i({-2,-1}), j({3 });
	findMedianSortedArrays(i, j);
}

//https://leetcode.com/problems/merge-k-sorted-lists/
static bool greaterlistnode(const ListNode* a, const ListNode* b)
{
	return a->val > b->val;
}
ListNode* mergeKLists(vector<ListNode*>& lists) 
{
	if (lists.size() == 0)
		return nullptr;

	if (lists.size() == 1)
		return lists[0];

	ListNode* pRet = nullptr, *pRetTail = nullptr;	

	// 给堆排序传一个自定义比较函数, 最小堆
	priority_queue<ListNode*, vector<ListNode*>, bool(*)(const ListNode* a, const ListNode* b)> curValpq(greaterlistnode);

	for (int i = 0; i < lists.size(); i++)
	{
		if (lists[i])
			curValpq.push(lists[i]);
	}

	if (curValpq.size() == 0)
		return nullptr;

	if (curValpq.size() == 1)
		return curValpq.top();

	while (curValpq.size() > 1)
	{
		if (pRet != nullptr)
		{
			pRetTail->next = curValpq.top();
			pRetTail = pRetTail->next;
		}
		else
		{
			pRet = curValpq.top();
			pRetTail = pRet;
		}

		curValpq.pop();
		if (pRetTail->next != nullptr)
			curValpq.push(pRetTail->next);
	}

	if (curValpq.top())
	{
		pRetTail->next = curValpq.top();
	}

	return pRet;
}

void testmergeKLists()
{
	ListNode l1(1), l2(2), l3(3), l4(4), l5(5), l6(6), l7(7), l8(8), l9(9), l10(10);
	l1.next = &l3;
	l3.next = &l5;

	l2.next = &l4;
	l4.next = &l6;

	l7.next = &l10;
	l8.next = &l9;	

	vector<ListNode*> lists({&l1, &l2, &l7, &l8});
	mergeKLists(lists);	
}

//https://leetcode.com/problems/reverse-nodes-in-k-group/
ListNode* getKthNode(ListNode* head, int k, ListNode *&preOfK)
{
	if (head == NULL || head->next == NULL || k == 1)
	{
		preOfK = NULL;
		return head;
	}

	ListNode *p2 = head;
	int i = 1;
	preOfK = NULL;
	while (i < k && p2 != NULL)
	{
		p2 = p2->next;
		i++;
		if (preOfK == NULL)
			preOfK = head;
		else
			preOfK = preOfK->next;
	}

	if (i < k)
		return NULL;

	return p2;
}

ListNode* reverseNodes(ListNode* head, int k)
{
	ListNode* p1 = head, * p2 = head->next;
	int i = 1;

	ListNode* ptmp = NULL;
	while (p2 != NULL && i < k)
	{
		ptmp = p2->next;
		p2->next = p1;

		p1 = p2;
		p2 = ptmp;
		i++;
	}

	head->next = ptmp;

	return p1;
}

ListNode* reverseKGroup(ListNode* head, int k) 
{
	if (head == NULL || head->next == NULL || k == 1)
		return head;

	ListNode* preOfK;
	ListNode* kNode = getKthNode(head, k, preOfK);
	if (kNode == NULL)
		return head;

	ListNode *pre = NULL, *newHead = NULL, *nHead = head;
	while (kNode != NULL)
	{
		ListNode *nTail = reverseNodes(nHead, k);
		if (nTail == NULL)
			break;

		if (newHead == NULL)
		{
			newHead = nTail;
		}
		kNode = getKthNode(nHead->next, k, preOfK);
		if (kNode != NULL)
		{
			ListNode* ptmp = nHead->next;
			nHead->next = kNode;
			nHead = ptmp;
		}
	}

	return newHead;
}

void testreverseKGroup()
{
	ListNode l1(1), l2(2), l3(3), l4(4), l5(5), l6(6), l7(7), l8(8), l9(9), l10(10);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l5;
	l5.next = &l6;

	reverseKGroup(&l1, 3);
}

//https://leetcode.com/problems/reverse-nodes-in-even-length-groups/description/
ListNode* reverseEvenLengthGroups(ListNode* head) 
{
	// TODO
	return NULL;
}


//https://leetcode.com/problems/swapping-nodes-in-a-linked-list/description/
ListNode* getKthNodeFromEnd(ListNode* head, int k, ListNode *&preOfEndK)
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode* p1 = head, * p2 = head;
	int i = 1;
	while (i < k && p2 != NULL)
	{
		p2 = p2->next;
		i++;
	}

	if (p2 == NULL)
		return NULL;

	if (p2->next == NULL)
	{
		preOfEndK = NULL;
		return head;
	}

	preOfEndK = head;
	p1 = p1->next;
	p2 = p2->next;

	while (p2->next != NULL)
	{
		p1 = p1->next;
		p2 = p2->next;
		preOfEndK = preOfEndK->next;
	}

	return p1;
}

ListNode* swapNodes(ListNode* head, int k) 
{
	ListNode* newHead = head;
	ListNode* preOfK = NULL;
	ListNode *kthNode = getKthNode(head, k, preOfK);
	if (kthNode == NULL)
		return head;

	ListNode* preOfEndK = NULL;
	ListNode* kthFromend = getKthNodeFromEnd(head, k, preOfEndK);

	if (kthNode == kthFromend)
		return head;

	if (preOfK == NULL)
	{
		preOfEndK->next = kthNode;		
		kthFromend->next = kthNode->next;
		kthNode->next = NULL;
		newHead = kthFromend;
	}
	else if (preOfEndK == NULL)
	{
		preOfK->next = kthFromend;
		kthNode->next = kthFromend->next;
		kthFromend->next = NULL;
		newHead = kthNode;
	}
	else if (kthNode->next == kthFromend)
	{
		preOfK->next = kthFromend;
		kthNode->next = kthFromend->next;
		kthFromend->next = kthNode;
	}
	else if (kthFromend->next == kthNode)
	{
		preOfEndK->next = kthNode;
		kthFromend->next = kthNode->next;
		kthNode->next = kthFromend;
	}
	else
	{
		preOfK->next = kthFromend;
		ListNode* tmp = kthNode->next;
		kthNode->next = kthFromend->next;
		kthFromend->next = tmp;
		preOfEndK->next = kthNode;
	}

	return newHead;
}

void testswapNodes()
{
	ListNode l1(1), l2(2), l3(3), l4(4), l5(5), l6(6), l7(7), l8(8), l9(9), l10(10);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l5;
	l5.next = &l6;

	ListNode* preOfEndK = NULL;

	swapNodes(&l1, 4);
}

//https://leetcode.com/problems/insertion-sort-list/description/
ListNode* insertNodeHelper(ListNode* head, ListNode* node)
{
	if (node->val <= head->val)
	{
		node->next = head;
		return node;
	}
	ListNode* idx = head->next, *preOfIdx = head;
	while (idx != NULL)
	{
		if (node->val <= idx->val)
		{
			preOfIdx->next = node;
			node->next = idx;
			break;
		}
		preOfIdx = idx;
		idx = idx->next;
	}

	return head;
}

ListNode* insertionSortList(ListNode* head) 
{
	if (head == NULL || head->next == NULL)
		return head;
	
	ListNode* maxNode = head;
	ListNode* idx = head->next, * preOfIdx = head;
	while (idx != NULL)
	{
		if (maxNode->val > idx->val)
		{
			preOfIdx->next = idx->next;
			head = insertNodeHelper(head, idx);
			idx = preOfIdx->next;
		}
		else
		{
			maxNode = idx;
			preOfIdx = idx;
			idx = idx->next;
		}		
	}

	return head;
}

void testinsertionSortList()
{
	ListNode l1(1), l2(2), l3(3), l4(4), l5(5), l6(6), l7(7), l8(8), l9(9), l10(10);
	l10.next = &l9;
	l9.next = &l7;
	l7.next = &l8;
	l8.next = &l6;
	l6.next = &l5;

	l4.next = &l2;
	l2.next = &l1;
	l1.next = &l3;

	insertionSortList(&l4);
}

//https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
bool isSubstring(string s, int offset, vector<string>& words, map<int, bool> beingSerchedWords, vector<int> &ret)
{
	if (beingSerchedWords.size() == 0)
	{
		ret.push_back(offset - words.size() * words[0].size());
		return true;
	}
	map<int, bool>::iterator itor(beingSerchedWords.begin());
	while(itor != beingSerchedWords.end())
	{
		if (s.compare(offset, words[itor->first].size(), words[itor->first].c_str()) == 0)
		{
			beingSerchedWords.erase(itor);

			return isSubstring(s, offset + words[0].size(), words, beingSerchedWords, ret);			
		}	
		itor++;
	}

	return false;
}
bool isSubstring2(string s, int offset, vector<string>& words, unordered_map<int, bool> beingSerchedWords, vector<int>& ret)
{
	bool keepfinding = true;
	int offset_inner = offset;
	while (beingSerchedWords.size() > 0 && keepfinding)
	{
		unordered_map<int, bool>::iterator itor(beingSerchedWords.begin());
		bool foundOneWord = false;
		while (itor != beingSerchedWords.end())
		{
			if (s.compare(offset_inner, words[itor->first].size(), words[itor->first].c_str()) == 0)
			{
				beingSerchedWords.erase(itor);

				offset_inner += words[0].size();
				foundOneWord = true;
				break;
			}
			itor++;
		}
		if (!foundOneWord)
		{
			keepfinding = false;
		}
	}

	if (beingSerchedWords.size() == 0)
	{
		ret.push_back(offset);
		return true;
	}

	return false;
}

vector<int> findSubstring(string s, vector<string>& words)
{
	vector<int> ret;
	if (words.size() == 0)
		return ret;

	unordered_map<int, bool> beingSerchedWords;
	int i = 0;
	for (i = 0; i < words.size(); i++)
	{
		beingSerchedWords[i] = true;
	}

	int offset = 0, substrLen = words.size() * words[0].size();
	while (offset + substrLen <= s.length())
	{
		bool found = false;
		for (i = 0; i < words.size(); i++)
		{
			if (s.compare(offset, words[0].size(), words[i].c_str()) == 0)
			{
				found = isSubstring2(s, offset, words, beingSerchedWords, ret);
				break;
			}
		}

		offset += 1;
	}

	return ret;
}


vector<int> findSubstring_ok(string s, vector<string>& words) {
	std::vector<int> result;
	unsigned int length = words[0].size();
	std::unordered_map<std::string, unsigned int> map;

	map.clear();
	for (const std::string& word : words)
		map[word]++;

	for (unsigned int offset = 0; offset < length; ++offset) {
		unsigned int size = 0;
		std::unordered_map<std::string, unsigned int> seen;
		for (unsigned int i = offset; i + length <= s.size(); i += length) {
			std::string sub = s.substr(i, length);

			auto itr = map.find(sub);
			if (itr == map.end()) {
				seen.clear();
				size = 0;
				continue;
			}

			++seen[sub];
			++size;
			while (seen[sub] > itr->second) {
				std::string first = s.substr(i - (size - 1) * length, length);
				--seen[first];
				--size;
			}

			if (size == words.size())
				result.push_back(i - (size - 1) * length);
		}
	}

	return result;
}


void testfindSubstring()
{
	/*
	string s("barfoothefoobarman");
	vector<string> words({ "foo", "bar" });
	
	string s("wordgoodgoodgoodbestword");
	vector<string> words({ "word","good","best","good" });	

	string s("aaaaaaaaaaaaaa");
	vector<string> words({ "aa","aa"});

	string s("mississippi");
	vector<string> words({ "is"});
	
	string s("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	vector<string> words({ "a","a","a","a","a","a","a","a","a","a","a","a" });
	*/	
	string s("abccbac");
	vector<string> words({ "a","b","c"});

	clock_t start, end;

	start = clock();

	for (int i = 0; i < 1; i++)
		findSubstring_ok(s, words);

	end = clock();

	double t = double(end - start) / CLOCKS_PER_SEC;

	return;
}

//https://leetcode.com/problems/find-missing-observations
bool findDiceCombination(int n, int sum_n, vector<int>& combine)
{
	if (n == 0 && sum_n == 0)
		return true;

	if (sum_n < n || sum_n > n * 6)
		return false;

	for (int i = 1; i <= 6; i++)
	{
		combine.push_back(i);
		
		if (findDiceCombination(n - 1, sum_n - i, combine))
		{			
			return true;
		}
		combine.pop_back();
	}
	return false;
}

vector<int> missingRolls(vector<int>& rolls, int mean, int n) 
{
	vector<int> ret;
	int sum_m = 0;
	int i = 0;
	for (i = 0; i < rolls.size(); i++)
		sum_m += rolls[i];

	int sum_n = mean * (rolls.size() + n) - sum_m;
	if (sum_n < n || sum_n > n*6)
		return ret;

	for (int i = 1; i <= 6; i++)
	{
		ret.clear();
		ret.push_back(i);
		if (findDiceCombination(n - 1, sum_n - i, ret))
			return ret;
	}

	return ret;
}

vector<int> missingRolls_ok(vector<int>& rolls, int mean, int n) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int nNumsSum = 0;
	for (int i : rolls) nNumsSum += i;

	int m = rolls.size();
	int totalLength = n + m;

	int mNumsSum = mean * totalLength - nNumsSum;     
	

	if (n * 6 < mNumsSum || mNumsSum < n) return {}; 

	int rem = mNumsSum % n;
	int q = mNumsSum / n;

	vector<int> res(n, q);
	for (int i = 1; i <= rem; i++)
		res[i]++;

	return res;
}

void testmissingRolls()
{
	vector<int> m({ 5,1,3,3,6,5,3,4,2,5,1,6,5,1,4,2,2,1,1,4,3,6,3,4,5,3,1,2,1,5,5,2,6,3,4,6,3,5,1,2,1,1,4,3,6,3,4,5,2,6,2,3,1,1,5,6,1,1,5,4,4,4,5,1,5,5,5,1,2,5,4,4,5,5,4,6,3,1,2,4,1,6,3,4,1,3,6,1,1,1,5,2,3,2,6,6,3,5,4,4,4,3,5,1,1,1,3,4,1,3,5,6,1,5,3,1,3,5,5,3,1,6,5,3,1,5,5,5,3,1,3,6,5,5,3,4,2,4,4,6,5,1,3,4,1,4,2,4,1,4,3,3,2,3,6,5,2,6,3,4,1,1,4,3,4,6,4,4,5,4,6,4,3,6,2,1,4,5,1,3,2,6,2,4,3,2,3,2,3,1,6,3,1,3,1,4,3,5,5,5,3,3,1,4,4,4,2,3,5,1,4,2,3,5,4,2,1,6,5,1 });
	int mean = 2;
	int n = 77603;
	missingRolls(m, mean, n);
}

//https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array
ListNode* modifiedList(vector<int>& nums, ListNode* head) 
{
	ListNode* newHead = head;

	unordered_map<int, bool> numsMap;
	int i = 0;
	for (i = 0; i < nums.size(); i++)
		numsMap[nums[i]] = true;

	while (newHead != NULL && numsMap.find(newHead->val) != numsMap.end())
	{
		newHead = newHead->next;
	}
	if (newHead == NULL)
		return NULL;

	ListNode* nodeIdx = newHead->next, *preNode = newHead;
	while (nodeIdx != NULL)
	{
		while (nodeIdx != NULL && numsMap.find(nodeIdx->val) != numsMap.end())
		{
			preNode->next = nodeIdx->next;
			nodeIdx = nodeIdx->next;
		}

		if (nodeIdx != NULL)
		{
			preNode = nodeIdx;
			nodeIdx = nodeIdx->next;
		}
	}

	return newHead;
}

void testmodifiedList()
{
	ListNode l1(3), l2(7), l3(1), l4(8), l5(1), l6(2), l7(7), l8(8), l9(9), l10(10);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l5;
	//l5.next = &l6;

	vector<int> nums({ 1,7,6,2,4 });

	modifiedList(nums, &l1);
}

//https://leetcode.com/problems/spiral-matrix-iv
vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) 
{
	vector<vector<int>> ret(m);
	int i = 0;
	for (i = 0; i < m; i++)
	{
		ret[i].resize(n, -1);
	}

	if (head == NULL)
		return ret;

	const int left = 1, right = 2, up = 3, down = 4;
	int dir = right;
	ListNode* idx = head;
	int r = 0, c = 0;
	int start_r = 0, end_r = m-1;
	int start_c = 0, end_c = n-1;

	while (idx != NULL)
	{
		switch (dir)
		{
		case right:
			for (c = start_c; c <= end_c && idx != NULL; c++)
			{
				ret[start_r][c] = idx->val;
				idx = idx->next;
			}
			start_r++;
			dir = down;
			break;

		case down:
			for (r = start_r; r <= end_r && idx != NULL; r++)
			{
				ret[r][end_c] = idx->val;
				idx = idx->next;
			}
			end_c--;

			dir = left;
			break;

		case left:
			for (c = end_c; c >= start_c && idx != NULL; c--)
			{
				ret[end_r][c] = idx->val;
				idx = idx->next;
			}
			end_r--;
			dir = up;
			break;

		case up:
			for (r = end_r; r >= start_r && idx != NULL; r--)
			{
				ret[r][start_c] = idx->val;
				idx = idx->next;
			}
			start_c++;
			dir = right;
			break;
		default:
			break;
		}
	}

	return ret;
}

void testspiralMatrix()
{
	vector<int> n({ 3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0 });
	ListNode* l = createListNode(n);
	
	
	/*
	* 30268
	* 50  1
	* 52497
	*/
	spiralMatrix(3, 5, l);
}

//https://leetcode.com/problems/minimum-bit-flips-to-convert-number/
int minBitFlips(int start, int goal) 
{
	int ret = 0;
	if (start == goal)
		return 0;
	
	int tmp = 0;
	for (int i = 0; i < 32; i++)
	{
		tmp = 1 << i;
		if (tmp > start && tmp > goal)
			break;

		if ((start & tmp) != (goal & tmp))
			ret++;
	}

	return ret;
}

void testminBitFlips()
{
	minBitFlips(10, 7);
}

//https://leetcode.com/problems/maximum-subarray/description/
int maxSubArray(vector<int>& nums) 
{
	int ret = 0;
	//TODO

	return ret;
}

void testmaxSubArray()
{
	vector<int> nums({ -2,1,-3,4,-1,2,1,-5,4 });
	maxSubArray(nums);
}

// https://leetcode.com/problems/merge-intervals/description/
vector<vector<int>> merge(vector<vector<int>>& intervals) 
{
	vector<vector<int>> ret;	
	int i = 0; 
	vector<int> distinctNum(intervals.size());
	std::iota(distinctNum.begin(), distinctNum.end(), 0);		

	//note: stick weak ordering
	sort(distinctNum.begin(), distinctNum.end(),
		[&](int a, int b)
		{
			if (intervals[a][0] == intervals[b][0])
				return (intervals[a][1] < intervals[b][1]);
			else
				return intervals[a][0] < intervals[b][0];
		});

	while( i < intervals.size() - 1)
	{
		int j = i + 1;
		if (intervals[distinctNum[i]][1] >= intervals[distinctNum[j]][0])
		{
			int pair_s = intervals[distinctNum[i]][0];
			int pair_e = std::max(intervals[distinctNum[i]][1], intervals[distinctNum[j]][1]);
			while (j < intervals.size() && pair_e >= intervals[distinctNum[j]][0])
			{
				pair_e = std::max(pair_e, intervals[distinctNum[j]][1]);
				j++;
			}
			vector<int > tmp({ pair_s, pair_e});
			ret.push_back(tmp);
			i = j;
		}
		else
		{
			ret.push_back(intervals[distinctNum[i]]);
			i++;
		}
	}
	
	if (i == intervals.size() -1)	    
		ret.push_back(intervals[distinctNum[i]]);

	return ret;
}

void testmerge()
{
//	vector<vector<int>> intervals({ {1, 3},{2, 6},{8, 10},{9, 18} });
	vector<vector<int>> intervals({ {74,78},{61,63},{46,50},{51,54},{50,50},{60,64},{39,42},{25,27},{91,95},{14,16},{85,85},{5,7},{45,46},{45,49},{66,66},{73,73},{25,26},{25,26},{45,48},{67,67},{63,65},{82,84},{90,92},{47,49},{3,4},{1,5},{64,66},{73,77},{90,94},{20,21},{84,87},{48,49},{80,80},{85,85},{53,55},{21,23},{31,34},{71,75},{62,65},{8,9},{32,33},{7,8},{20,22},{57,57},{51,53},{18,21},{71,75},{49,50},{44,45} });
	
	merge(intervals);

}

//https://leetcode.com/problems/insert-interval/description/
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
{

	int i = 0;
	vector<vector<int>> ret;

	if (intervals.size() == 0)
	{
		ret.push_back(newInterval);

		return ret;
	}

	while (i < intervals.size() && newInterval[0] > intervals[i][1])
	{
		ret.push_back(intervals[i]);
		i++;
	}

	if (i == intervals.size())
	{
		ret.push_back(newInterval);
		return ret;
	}

	int pair_s = intervals[i][0], pair_e = newInterval[1];

	if (newInterval[0] < intervals[i][0])
	{
		pair_s = newInterval[0];
	}

	while (i < intervals.size() && intervals[i][1] <= pair_e)
	{
		i++;
	}
	
	if (i < intervals.size() && pair_e >= intervals[i][0])
	{
		pair_e = intervals[i][1];
		i++;
	}

	vector<int> tmp({ pair_s, pair_e });
	ret.push_back(tmp);
	ret.insert(ret.end(), intervals.begin() + i, intervals.end());
	

	return ret;
}

void testinsert()
{
	vector<vector<int>> intervals({ {1,5}});
	vector<int> newInterval({6,8});

	insert(intervals, newInterval);
}

//https://leetcode.com/problems/largest-number/
int getLargestDigital(vector<string>& numsInStr, vector<int>& strUsedIdx)
{
	char maxDigit = 0;
	vector<int> sameDigIdx;

	int i = 0, j = 0;
	for (; i < numsInStr.size(); i++)
	{
		if (strUsedIdx[i] == -1)
			continue;

		if (numsInStr[i][strUsedIdx[i]] > maxDigit)
		{
			maxDigit = numsInStr[i][strUsedIdx[i]];
			sameDigIdx.clear();
			sameDigIdx.push_back(i);
		}
		else if (numsInStr[i][strUsedIdx[i]] == maxDigit)
		{
			sameDigIdx.push_back(i);
		}
	}

	if (sameDigIdx.size() == 0)
	{	
		return -1;
	}

	if (sameDigIdx.size() == 1)
	{
		strUsedIdx[sameDigIdx[0]] = -1;

		return sameDigIdx[0];
	}
	else
	{
		int strIdx = sameDigIdx[0];
		int allSameDigs = 0;
		bool keepFinding = true;
		while (keepFinding)
		{			
			for (i = 1; i < sameDigIdx.size(); i++)
			{
				if (numsInStr[sameDigIdx[i]][allSameDigs] != numsInStr[sameDigIdx[0]][allSameDigs])				
				{
					strIdx = sameDigIdx[i];
					keepFinding = false;
					break;
				}
			}
			if (i == sameDigIdx.size())
				allSameDigs++;
		}
		string curMaxDigs(numsInStr[sameDigIdx[0]].substr(0, allSameDigs));

		vector<int> strDigIdx(sameDigIdx.size(), 0);
		char curMaxDig(numsInStr[sameDigIdx[0]][0]);
		
		for (i = 0; i < sameDigIdx.size(); i++)
		{
			if (allSameDigs < numsInStr[sameDigIdx[i]].size())
			{
				string tmp(numsInStr[sameDigIdx[i]].substr(allSameDigs, numsInStr[sameDigIdx[i]].size() - allSameDigs));
				if (tmp.compare(curMaxDigs.c_str()) > 0)
				{
					strIdx = sameDigIdx[i];
					curMaxDigs = tmp;
				}
			}
		}

		strUsedIdx[strIdx] = -1;

		return strIdx;
	}
}

string largestNumber(vector<int>& nums)
{
	string ret;
	vector<string> numsInStr(nums.size());
	vector<int> strUsedIdx(nums.size(), 0);

	for (int i = 0; i < nums.size(); i++)
	{
		numsInStr[i] = std::to_string(nums[i]);
	}

	int largestDig = getLargestDigital(numsInStr, strUsedIdx);
	while (largestDig >= 0)
	{
		ret.append(numsInStr[largestDig]);
		largestDig = getLargestDigital(numsInStr, strUsedIdx);
	}

	return ret;
}

string largestNumber_ok(vector<int>& nums)
{
	// Convert integers to strings
	vector<string> array;
	for (int num : nums) {
		array.push_back(to_string(num));
	}

	// Custom comparator for sorting
	sort(array.begin(), array.end(), [](const string& a, const string& b) {
		return (b + a) < (a + b);
		});

	// Handle the case where the largest number is "0"
	if (array[0] == "0") {
		return "0";
	}

	// Build the largest number from the sorted array
	string largest;
	for (const string& num : array) {
		largest += num;
	}

	return largest;
}

void testlargestNumber()
{
	//vector<int> nums({ 432,43243 });

	//vector<int> nums({ 3, 30, 34, 5, 9 });
	vector<int> nums({ 8, 807, 89 });

	largestNumber_ok(nums);
}

//https://leetcode.com/problems/rotate-list/description/
int getListLength(ListNode* head)
{
	if (head == NULL)
		return 0;

	if (head->next == NULL)
		return 1;

	int len = 0;
	ListNode* idx = head;
	while (idx != NULL)
	{
		len++;
		idx = idx->next;
	}

	return len;
}

ListNode* rotateRight(ListNode* head, int k) 
{
	if (head == NULL)
		return head;

	int len = getListLength(head);
	k = k % len;
	if (k == 0)
		return head;

	ListNode* reverse_k = head, *node_idx = head;
	ListNode* pre_reverse_k = head;
	int i = 1;
	while (node_idx->next != NULL)
	{
		node_idx = node_idx->next;
		i++;
		if (i > k)
		{
			pre_reverse_k = reverse_k;
			reverse_k = reverse_k->next;
		}		
	}

	node_idx->next = head;
	pre_reverse_k->next = NULL;
	head = reverse_k;

	return head;
}

void testrotateRight()
{
	ListNode l1(1), l2(2), l3(3), l4(4), l5(5), l6(6), l7(7), l8(8), l9(9), l10(10);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l5;
	l5.next = &l6;

	rotateRight(&l1, 2);
}

//https://leetcode.com/problems/first-missing-positive/description/
int firstMissingPositive(vector<int>& nums) {
	int ret = 0;
	int i = 0;
	int min = INT_MAX, sec_min = INT_MAX;
	for (i = 0; i < nums.size(); i++)
	{
		if (nums[i] > 0)
		{
			if (nums[i] < min)
			{
				sec_min = min;
				min = nums[i];
			}
			else if (nums[i] < sec_min)
			{
				sec_min = nums[i];
			}
		}
	}

	if (min == sec_min)
	{
		if (min == INT_MAX)
			return 1;
		else if (min > 1)
			return 1;
		else if (min == 1)
			return 2;
		else
			return min - 1;
	}

	if (min > 1)
	{
		return 1;
	}

	if (min + 1 < sec_min)
	{
		return min + 1;
	}
	else if (min + 1 == sec_min)
	{

	}
	
	return sec_min + 1;
}

int firstMissingPositive_ok(vector<int>& nums) {
	int n = size(nums);

	for (int i = 0; i < n; i++) {
		int x = nums[i]; // x = current element

		// x>=1 && x<=n : to check if x is in range[1, n]
		// x != i+1 : skip if at index i correct element is present.
		// nums[x-1]!=x: skip if at index x-1 correct element is present
		while (x >= 1 && x <= n && x != i + 1 && nums[x - 1] != x) {
			swap(nums[x - 1], nums[i]);
			x = nums[i];
		}
	}

	for (int i = 0; i < n; i++) {
		if (nums[i] == i + 1)
			continue;
		return i + 1;
	}

	return n + 1;
}
void testfirstMissingPositive()
{
	vector<int> nums({ 100000, 11, 4000, 10, 2, 9, -1});
	firstMissingPositive_ok(nums);
}

//https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/description/
int minGroups(vector<vector<int>>& intervals) 
{
	int ret = 0;

	sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
		return a[0] < b[0];
		});

	vector<int> idx1(intervals.size(), 0), idx2;
	int i = 0, j = 0;
	for (i = 0; i < intervals.size(); i++)
		idx1[i] = i;

	vector<int> *idx_ref1 = &idx1, *idx_ref2 = &idx2;

	while (idx_ref1->size() > 0)
	{
		int link_end = intervals[(*idx_ref1)[0]][1];

		for (int j = 1; j < idx_ref1->size(); j++)
		{
			if (intervals[(*idx_ref1)[j]][0] > link_end)
			{
				link_end = intervals[(*idx_ref1)[j]][1];
			}
			else
			{
				idx_ref2->push_back((*idx_ref1)[j]);
			}
		}

		ret++;

		idx_ref1->clear();
		vector<int> *tmp = idx_ref1;
		idx_ref1 = idx_ref2;
		idx_ref2 = tmp;
	}

	return ret;
}

int minGroups_ok(vector<vector<int>>& intervals) {
	vector<int> start_times, end_times;

	// Extract start and end times
	for (const auto& interval : intervals) {
		start_times.push_back(interval[0]);
		end_times.push_back(interval[1]);
	}

	// Sort start and end times
	sort(start_times.begin(), start_times.end());
	sort(end_times.begin(), end_times.end());

	int end_ptr = 0, group_count = 0;

	// Traverse through the start times
	for (int start : start_times) {
		if (start > end_times[end_ptr]) {
			end_ptr++;
		}
		else {
			group_count++;
		}
	}

	return group_count;
}
void testminGroups()
{
	//vector<vector<int>> intervals({{5, 10},{6, 8},{1, 5},{2, 3},{1, 10 } });
	// 1 1 2 5  6
	// 3 5 8 10 10 

	vector<vector<int>> intervals({ {1, 3},{5, 6},{8, 10},{11, 13} });
	// 1 5 8  11
	// 3 6 10 13

	minGroups(intervals);
}

//01020304
//00120304
//00102304
//00102034
//00012034
//00010234
//00001234

//0123456789
// 
//1023456789
//1032456789
//1032546789
//1032547689
//1032547698
// 
//1302547698
//1305247698
//1305274698
//1305274968

//1350274968
//1350724968
//1350729468

//1357029468
//1357092468
//1357902468

//https://leetcode.com/problems/trapping-rain-water/description/
int getSpaceBetweenNeighbors(vector<int>& height, int pos, int &endpos)
{
	if (pos >= height.size()-1)
	{
		endpos = pos;
		return 0;
	}
	if (height[pos] <= height[pos + 1])
	{
		endpos = pos + 1;
		return 0;
	}

	int idx = pos + 1;
	int space = 0;
	endpos = idx;
	for (; idx < height.size(); idx++)
	{
		if (height[idx] >= height[pos])
		{
			endpos = idx;
			break;
		}
	}

	if (idx == pos + 1)
	{
		return 0;
	}

	if (idx == height.size())
	{
		int nextmaxlevel = pos + 1;
		for (idx = pos + 1; idx < height.size(); idx++)
		{
			if (height[idx] > height[nextmaxlevel])
				nextmaxlevel = idx;
		}
		if (nextmaxlevel == pos+1)
			return 0;
		else
			endpos = nextmaxlevel;
	}

	int bankheight = min(height[pos], height[endpos]);
	for (idx = pos + 1; idx < endpos; idx++)
	{
		space += bankheight - height[idx];
	}	

	return space;
}

int trap_slow(vector<int>& height) 
{
	if (height.size() < 3)
		return 0;

	int pos = 0;
	int endpos = 0;
	int space = 0;
	while (pos < height.size()-2)
	{
		space += getSpaceBetweenNeighbors(height, pos, endpos);
		pos = endpos;
	}
	return space;
}

int trap(vector<int>& height) {
	if (height.size() <= 2) return 0;
	int n = height.size(), maxLeft = height[0], maxRight = height[n - 1];
	int left = 1, right = n - 2, ans = 0;
	while (left <= right) {
		if (maxLeft < maxRight) {
			if (height[left] > maxLeft)
				maxLeft = height[left];
			else
				ans += maxLeft - height[left];
			left += 1;
		}
		else {
			if (height[right] > maxRight)
				maxRight = height[right];
			else
				ans += maxRight - height[right];
			right -= 1;
		}
	}
	return ans;
}

void testtrap()
{
	//vector<int> height({ 0,1,0,2,1,0,1,3,2,1,2,1 });
	vector<int> height({ 1,3,5,7,0,2,9,4,6,8 });

	trap(height);
}

//https://leetcode.com/problems/separate-black-and-white-balls
long long minimumSteps(string s) 
{
	long long swaptimes = 0;

	int last_pos_1 = s.size() - 1;
	while (last_pos_1 >= 0)
	{
		if (s[last_pos_1] == '1')
			last_pos_1--;
		else
			break;
	}

	if (last_pos_1 == 0)
		return swaptimes;

	int idx = last_pos_1 - 1;
	while (idx >= 0)
	{
		if (s[idx] == '1')
		{
			swaptimes += last_pos_1 - idx;
			last_pos_1--;
		}
		idx--;
	}
	
	return swaptimes;
}

void testminimumSteps()
{
	string s("10101010101");
	minimumSteps(s);
}

//https://leetcode.com/problems/maximum-swap
int maximumSwap(int num) 
{
	string strnum(std::to_string(num));
	for (int i = 0; i < strnum.size() - 1; i++)
	{
		if (strnum[i] == '9')
			continue;

		int swap_idx = i;		
		for (int j = i + 1; j < strnum.size(); j++)		
		{
			if (strnum[j] > strnum[i] && strnum[j] >= strnum[swap_idx])
			{
				swap_idx = j;
			}
		}
		if (swap_idx != i)
		{
			swap(strnum[i], strnum[swap_idx]);
			int ret = std::atoi(strnum.c_str());
			return ret;
		}
	}
	
	return num;
}

void testmaximumSwap()
{
	maximumSwap(1993);
}

//https://leetcode.com/problems/unique-paths/description/
int uniquePaths(int m, int n) {
	std::vector<int> aboveRow(n, 1);
		
	for (int row = 1; row < m; row++) {
		std::vector<int> currentRow(n, 1);
		for (int col = 1; col < n; col++) {
			// (0,1), (1,0) 唯一路径数都是 1. 从 1 行 1 列开始，走到当前格子的可能的唯一路径数，就是它的上边格子和左边格子的唯一路径数之和
			currentRow[col] = currentRow[col - 1] + aboveRow[col]; 
		}
		aboveRow = currentRow;
	}

	return aboveRow[n - 1];
}

void testuniquePaths()
{
	uniquePaths(3, 4);
}



//https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/description/
long long kthLargestLevelSum(TreeNode* root, int k) 
{
	if (root == NULL)
		return -1;

	list<TreeNode*> nodesAtLevel1, nodesAtLevel2, * nodeListIdx;
	if (root->left)
		nodesAtLevel1.push_back(root->left);

	if (root->right)
		nodesAtLevel1.push_back(root->right);

	priority_queue<long long, vector<long long>, greater<long long>> pq;
	pq.push(root->val);

	nodeListIdx = &nodesAtLevel1;
	
	while (nodeListIdx != NULL && nodeListIdx->size() > 0)
	{
		long long cursum = 0;
		list<TreeNode*>::iterator itor = nodeListIdx->begin();
		while (itor != nodeListIdx->end())
		{
			cursum += (*itor)->val;
			if ((*itor)->left)
			{
				if (nodeListIdx == &nodesAtLevel1)
					nodesAtLevel2.push_back((*itor)->left);
				else
					nodesAtLevel1.push_back((*itor)->left);
			}

			if ((*itor)->right)
			{
				if (nodeListIdx == &nodesAtLevel1)
					nodesAtLevel2.push_back((*itor)->right);
				else
					nodesAtLevel1.push_back((*itor)->right);
			}

			itor++;
		}

		pq.push(cursum);
		if (pq.size() > k)
		{
			pq.pop();
		}

		nodeListIdx->clear();
		if (nodeListIdx == &nodesAtLevel1)
		{
			nodeListIdx = &nodesAtLevel2;
		}
		else
		{
			nodeListIdx = &nodesAtLevel1;
		}
	}
	if (k > pq.size())
		return -1;

	long long ret = pq.top();
	return ret;
}

void testkthLargestLevelSum()
{
	TreeNode t1(1), t2(2), t3(3), t4(4), t5(5), t6(6), t7(7), t8(8), t9(9), t10(10);
	t1.left = &t2;
	t1.right = &t3;
	t2.left = &t4;
	t2.right = &t5;
	t3.left = &t6;
	t3.right = &t7;
	t7.right = &t8;
	t5.left = &t9;
	t8.right = &t10;

	kthLargestLevelSum(&t1, 2);
}

//https://leetcode.com/problems/cousins-in-binary-tree-ii/description/
TreeNode* replaceValueInTree(TreeNode* root) 
{
	if (root == NULL)
		return NULL;

	list<TreeNode*> siblingNodes1, siblingNodes2;
	root->val = 0;
	if (root->left)
	{
		siblingNodes1.push_back(root->left);
		root->left->val = 0;
	}

	if (root->right)
	{
		siblingNodes1.push_back(root->right);
		root->right->val = 0;
	}

	list<TreeNode*>* nodeListIdx = &siblingNodes1;
	while (nodeListIdx->size() > 0)
	{
		int sumOfCursion = 0;
		list<TreeNode*>::iterator itor = nodeListIdx->begin();
		while (itor != nodeListIdx->end())
		{
			if ((*itor)->left)
				sumOfCursion += (*itor)->left->val;

			if ((*itor)->right)
				sumOfCursion += (*itor)->right->val;

			itor++;
		}

		itor = nodeListIdx->begin();
		while (itor != nodeListIdx->end())
		{
			int siblingSum = 0;
			if ((*itor)->left)
			{
				siblingSum += (*itor)->left->val;
				if (nodeListIdx == &siblingNodes1)
					siblingNodes2.push_back((*itor)->left);
				else
					siblingNodes1.push_back((*itor)->left);
			}

			if ((*itor)->right)
			{
				siblingSum += (*itor)->right->val;
				if (nodeListIdx == &siblingNodes1)
					siblingNodes2.push_back((*itor)->right);
				else
					siblingNodes1.push_back((*itor)->right);
			}

			if ((*itor)->left)
				(*itor)->left->val = sumOfCursion - siblingSum;

			if ((*itor)->right)
				(*itor)->right->val = sumOfCursion - siblingSum;

			itor++;
		}

		nodeListIdx->clear();
		if (nodeListIdx == &siblingNodes1)
			nodeListIdx = &siblingNodes2;
		else
			nodeListIdx = &siblingNodes1;
	}

	return root;
}

void testreplaceValueInTree()
{
	TreeNode t1(1), t2(2), t3(3), t4(4), t5(5), t6(6), t7(7), t8(8), t9(9), t10(10);
	t1.left = &t2;
	t1.right = &t3;
	t2.left = &t4;
	t2.right = &t5;
	t3.left = &t6;
	t3.right = &t7;
	t7.right = &t8;
	t5.left = &t9;
	t8.right = &t10;
	replaceValueInTree(&t1);
}
//https://leetcode.com/problems/cousins-in-binary-tree/description/
bool isCousins(TreeNode* root, int x, int y) 
{
	if (root == NULL || root->left == NULL || root->right == NULL)
		return false;

	list<TreeNode*> siblingNodes1, siblingNodes2;
	siblingNodes1.push_back(root);
	int depth = 1;

	list<TreeNode*>* nodeListIdx = &siblingNodes1;
	while (nodeListIdx->size() > 0)
	{
		list<TreeNode*>::iterator itor = nodeListIdx->begin();
		bool isX = false, isY = false;
		while (itor != nodeListIdx->end())
		{
			TreeNode* node = (*itor);
			if ( (node->left && node->right) &&
				 ( (node->left->val == x && node->right->val == y) || 
				   (node->left->val == y && node->right->val == x) ))
				return false;

			if ((*itor)->val == x)
				isX = true;

			if ((*itor)->val == y)
				isY = true;

			if (isX && isY && depth > 2)
				return true;

			if ((*itor)->left)
			{
				if (nodeListIdx == &siblingNodes1)
					siblingNodes2.push_back((*itor)->left);
				else
					siblingNodes1.push_back((*itor)->left);
			}

			if ((*itor)->right)
			{
				if (nodeListIdx == &siblingNodes1)
					siblingNodes2.push_back((*itor)->right);
				else
					siblingNodes1.push_back((*itor)->right);
			}

			itor++;
		}
		depth++;

		nodeListIdx->clear();
		if (nodeListIdx == &siblingNodes1)
			nodeListIdx = &siblingNodes2;
		else
			nodeListIdx = &siblingNodes1;		
	}

	return false;
}

void testisCousins()
{
	TreeNode t1(1), t2(2), t3(3), t4(4), t5(5), t6(6), t7(7), t8(8), t9(9), t10(10);
	t1.left = &t2;
	t1.right = &t3;
//	t2.left = &t4;
	//t2.right = &t5;
	t3.left = &t4;
	t3.right = &t5;
//	t7.right = &t8;
//	t5.left = &t9;
//	t8.right = &t10;
	isCousins(&t1, 5, 4);
}

//https://leetcode.com/problems/remove-sub-folders-from-the-filesystem
void splitpath(const std::string& text, char delimiter, std::vector<std::string>& tokens)
{
	std::istringstream tokenStream(text);
	std::string token;
	while (std::getline(tokenStream, token, delimiter)) {
		if (token.size() > 0)
			tokens.push_back(token);
	}
}

struct FolderNode
{
	string folder;
	bool isPathEnd;
	unordered_map<string, FolderNode*> folderDict;

	FolderNode(string f, bool b) :folder(f), isPathEnd(b) {};
};

bool shouleKeepPath(unordered_map<string, FolderNode*> &folderDict, vector<string> &foldersOnPath, int index)
{
	unordered_map<string, FolderNode*>::iterator itor = folderDict.find(foldersOnPath[index]);
	if (itor == folderDict.end())
	{
		folderDict[foldersOnPath[index]] = new FolderNode(foldersOnPath[index], index == foldersOnPath.size() - 1 ? true : false);
		if (index == foldersOnPath.size() - 1)
			return true;

		return shouleKeepPath(folderDict[foldersOnPath[index]]->folderDict, foldersOnPath, index + 1);
	}
	else
	{
		if (itor->second->isPathEnd)
			return false;

		return shouleKeepPath(folderDict[foldersOnPath[index]]->folderDict, foldersOnPath, index + 1);
	}
}

vector<string> removeSubfolders(vector<string>& folder) 
{
	vector<string> ret;

	sort(folder.begin(), folder.end());

	unordered_map<string, FolderNode*> folderDict;

	for (int i = 0; i < folder.size(); i++)
	{
		vector<string> foldersOnPath;
		splitpath(folder[i], '/', foldersOnPath);
		if (shouleKeepPath(folderDict, foldersOnPath, 0))
			ret.push_back(folder[i]);		
	}

	return ret;
}

void testremoveSubfolders()
{
	//	vector<string> folder({  "/c/d/e", "/a", "/a/b", "/c/d", "/c/f" });	
	vector<string> folder({ "/a/b/c", "/a/b/ca", "/a/b/d" });
	removeSubfolders(folder);
}

//https://leetcode.com/problems/longest-square-streak-in-an-array/description/
int longestSquareStreak(vector<int>& nums) 
{
	sort(nums.begin(), nums.end());

	unordered_map<unsigned long, bool> numMap;
	int i = 0;
	for (i = 0; i < nums.size(); i++)
		numMap[nums[i]] = false;

	int longest = 1;
	for (i = 0; i < nums.size(); i++)
	{
		if (nums[i] == 1 || numMap[nums[i]] == true)
			continue;

		int curLen = 1;
		unsigned long square = (unsigned long)nums[i] * nums[i];
		unordered_map<unsigned long, bool>::iterator itor = numMap.find(square);
		while (itor != numMap.end() && itor->second == false)
		{
			curLen++;
			square *= square;
			itor->second = true;
			itor = numMap.find(square);
		}

		if (curLen > longest)
			longest = curLen;
	}

	if (longest == 1)
		return  -1;

	return longest;
}

void testlongestSquareStreak()
{
//	vector<int> nums({ 4, 3, 6, 16, 8, 2 });
//	vector<int> nums({ 2, 3, 5, 6, 7 });
	vector<int> nums({ 4, 16, 256, 65536 });

	longestSquareStreak(nums);
}

//https://leetcode.com/problems/simplify-path/description/
string simplifyPath(string path) 
{
	string ret;
	vector<string> foldersOnPath;

	splitpath(path, '/', foldersOnPath);

	vector<string> validToken(foldersOnPath.size() + 1, "");
	int validIdx = 1;
	validToken[0] = "/";
	for (int i = 0; i < foldersOnPath.size(); i++)
	{
		if (foldersOnPath[i].compare("..") == 0)
		{
			validIdx--;
			if (validIdx == 0)
				validIdx = 1;

			continue;
		}

		if (foldersOnPath[i].compare(".") == 0)
			continue;

		validToken[validIdx] = foldersOnPath[i];
		validIdx++;
	}

	for (int i = 0; i < validIdx; i++)
	{
		ret.append(validToken[i].c_str());
		if (i > 0 && i < validIdx - 1)
			ret.append("/");
	}

	return ret;
}

void testsimplifyPath()
{
	string path("/../.../a///../b/c/../d/./");
	simplifyPath(path);

}

//https://leetcode.com/problems/search-a-2d-matrix/
bool IsInRow(vector<vector<int>>& matrix, int target, int row)
{
	int i = 0, j = matrix[0].size() - 1;
	
	while(i <= j)
	{
		int mid = (i + j) / 2;
		if (matrix[row][mid] == target)
			return true;

		if (matrix[row][mid] < target)
			i = mid + 1;
		else
			j = mid - 1;
	}
	return false;
}

bool IsInCol(vector<vector<int>>& matrix, int target, int col)
{
	int i = 0, j = matrix.size() - 1;
	while (i <= j)
	{
		int mid = (i + j) / 2;
		if (matrix[mid][col] == target)
			return true;

		if (matrix[mid][col] < target)
			i = mid + 1; 
		else
			j = mid - 1;
	}

	return false;
}


bool searchMatrix(vector<vector<int>>& matrix, int target) 
{
	bool bFound = false;
	int i = 0, j = 0;
	int cols = matrix[0].size();

	if (matrix.size() == 1 || matrix[0].size() == 1)
	{
		if (matrix.size() == 1 && matrix[0].size() == 1)
			return matrix[0][0] == target;

		if (matrix.size() == 1)
			return IsInRow(matrix, target, 0);

		if (matrix[0].size() == 1)
			return IsInCol(matrix, target, 0);
	}

	for (i = 0; i < matrix.size(); i++)
	{
		if (target >= matrix[i][0] && target <= matrix[i][cols - 1])
		{
			bFound = true;
			return IsInRow(matrix, target, i);
		}
	}

	return bFound;
}

void testsearchMatrix()
{
//	vector<vector<int>> matrix({ { 1, 3, 5, 7 }, { 10, 11, 16, 20 }, { 23, 30, 34, 60 } });
	vector<vector<int>> matrix({ { 1},{3} });
	searchMatrix(matrix, 3);
}

//https://leetcode.com/problems/set-matrix-zeroes/description/
void zeroRowCol(int r, int c, vector<vector<int>>& matrix, vector<bool>& zeroedR, vector<bool> &zeroedC)
{
	int i = 0;
	if (zeroedR[r] == false)
	{
		for (i = 0; i < matrix[0].size() && zeroedR[r] == false; i++)
		{
			matrix[r][i] = 0;
		}
		zeroedR[r] = true;
	}

	if (zeroedC[c] == false)
	{
		for (i = 0; i < matrix.size(); i++)
		{
			matrix[i][c] = 0;
		}

		zeroedC[c] = true;
	}
}

void setZeroes(vector<vector<int>>& matrix) 
{
	vector<pair<int, int>> zeros;
	vector<bool> zeroedR(matrix.size(), 0), zeroedC(matrix[0].size(), 0);

	for (int r = 0; r < matrix.size(); r++)
	{
		for (int c = 0; c < matrix[0].size(); c++)
		{

			if (matrix[r][c] == 0)
			{
				pair<int, int> z(r, c);
				zeros.push_back(z);
			}
		}
	}

	for (int i = 0; i < zeros.size(); i++)
	{
		zeroRowCol(zeros[i].first, zeros[i].second, matrix, zeroedR, zeroedC);
	}

	return;
}

void testsetZeroes()
{
	vector<vector<int>> matrix({ {0, 1, 2, 0},{3, 4, 5, 2},{1, 3, 1, 5} });
	setZeroes(matrix);
}

//https://leetcode.com/problems/remove-duplicates-from-sorted-list/
ListNode* deleteDuplicates(ListNode* head) 
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode* ptmp = head, * ptmp2 = head->next;
	while (ptmp2 != NULL)
	{
		if (ptmp->val == ptmp2->val)
		{
			ptmp->next = ptmp2->next;
		}
		else
		{
			ptmp = ptmp2;			
		}
		ptmp2 = ptmp2->next;
	}

	return head;
}

void testdeleteDuplicates()
{
	ListNode l1(1), l2(1), l3(1), l4(4), l5(5), l6(6), l7(7), l8(8), l9(9), l10(10);
	l1.next = &l2;
	l2.next = &l3;
	deleteDuplicates(&l1);
}

//https://leetcode.com/problems/partition-list/
//143252 ->122435
ListNode* partition(ListNode* head, int x) 
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode* pidx = head, * preIdx = head, * lastMovable = NULL;

	while (pidx != NULL && pidx->val >= x)
	{
		preIdx = pidx;
		pidx = pidx->next;
	}

	if (pidx == NULL)
		return head;

	if (head != pidx)
	{
		preIdx->next = pidx->next;
		pidx->next = head;
		head = pidx;

		pidx = preIdx->next;
	}
	else
	{
		preIdx = head;
		pidx = head->next;
	}

	lastMovable = head;

	while (pidx != NULL)
	{
		if (pidx->val < x && preIdx->val >= x)
		{
			preIdx->next = pidx->next;
			pidx->next = lastMovable->next;
			lastMovable->next = pidx;
			lastMovable = pidx;

			pidx = preIdx->next;
		}
		else 
		{
			preIdx = pidx;
			pidx = pidx->next;
			if (preIdx->val < x)
				lastMovable = preIdx;
		}
	}

	return head;
}

void testpartition()
{
	//vector<int> values({ 2,0,4,1,3,1,4,0,3 });
	vector<int> values({ 2,1});
	ListNode *head = createListNode(values);

	partition(head, 2);

	deleteList(head);
}


//https://leetcode.com/problems/partition-array-according-to-given-pivot/description/
vector<int> pivotArray(vector<int>& nums, int pivot) 
{
	vector<int> ret(nums.size(), 0);
	int i = 0;
	int less = 0, larger = 0, equal = 0;
	for (i = 0; i < nums.size(); i++)
	{
		if (nums[i] < pivot)
			less++;
		else if (nums[i] == pivot)
			equal++;
		else
			larger++;
	}
	int lessidx = 0, equalidx = less, largeridx = less + equal;

	for (i = 0; i < nums.size(); i++)
	{
		if (nums[i] < pivot)
		{
			ret[lessidx] = nums[i];
			lessidx++;
		}
		else if (nums[i] == pivot)
		{
			ret[equalidx] = nums[i];
			equalidx++;
		}
		else
		{
			ret[largeridx] = nums[i];
			largeridx++;
		}
	}

	return ret;
}

void testpivotArray()
{
	vector<int> nums({ 9,12,5,10,14,3,10 });
	pivotArray(nums, 10);
}


//https://leetcode.com/problems/reverse-linked-list-ii/?envType=daily-question&envId=2023-09-07
ListNode* getNthNodeOfList(ListNode* head, int n)
{
	ListNode* pidx = head;
	int i = 0;
	while (pidx != NULL)
	{
		i++;
		if (i == n)
			return pidx;

		pidx = pidx->next;
	}

	return pidx;
}

ListNode* reverseBetween(ListNode* head, int left, int right)
{
	if (head == NULL || head->next == NULL || left == right)
		return head;

	ListNode* pleft = getNthNodeOfList(head, left);
	ListNode* pright = getNthNodeOfList(head, right);
	ListNode* pidx = pleft->next, * preidx = pleft, * prightnext = pright->next, * ptmp = NULL;

	while (pidx != NULL && pidx != prightnext)
	{
		ptmp = pidx->next;
		pidx->next = preidx;
		preidx = pidx;
		pidx = ptmp;
	}
	pleft->next = prightnext;
	if (pleft == head)
	{
		head = pright;
	}
	else
	{
		ptmp = getNthNodeOfList(head, left - 1);
		ptmp->next = pright;
	}

	return head;
}

void testreverseBetween()
{

	vector<int> n({1,2,3,4,5,6 });
	ListNode* l = createListNode(n);

	reverseBetween(l, 1, 2);

	deleteList(l);
}

//https://leetcode.com/problems/binary-tree-inorder-traversal/description/
void itorTreeInorder(TreeNode* root, vector<int> &inorder)
{
	if (root == NULL)
		return;

	itorTreeInorder(root->left, inorder);
	inorder.push_back(root->val);	
	itorTreeInorder(root->right, inorder);
}

vector<int> inorderTraversal(TreeNode* root) 
{
	vector<int> ret;

	itorTreeInorder(root, ret);

	return ret;
}

//https://leetcode.com/problems/validate-binary-search-tree/description/

bool getandValidAllChildVals(TreeNode* curnode, vector<int> &childValsFromParent)
{
	vector<int> myleftVals, myRightVals;
	if (curnode->left != NULL)
	{
		myleftVals.push_back(curnode->left->val);
		if (!getandValidAllChildVals(curnode->left, myleftVals))
			return false;

		if (myleftVals.size() > 0)
		{
			for (int i = 0; i < myleftVals.size(); i++)
			{
				if (myleftVals[i] >= curnode->val)
					return false;
			}
			childValsFromParent.insert(childValsFromParent.end(), myleftVals.begin(), myleftVals.end());
		}
	}

	if (curnode->right != NULL)
	{
		myRightVals.push_back(curnode->right->val);

		if (!getandValidAllChildVals(curnode->right, myRightVals))
			return false;

		if (myRightVals.size() > 0)
		{
			for (int i = 0; i < myRightVals.size(); i++)
			{

				if (myRightVals[i] <= curnode->val)
					return false;
			}
			childValsFromParent.insert(childValsFromParent.end(), myRightVals.begin(), myRightVals.end());
		}
	}

	return true;
}

bool isValidBST(TreeNode* root) 
{
	vector<int> myleftVals, myRightVals;
	if (root->left != NULL)
		myleftVals.push_back(root->left->val);

	if (root->right != NULL)
		myRightVals.push_back(root->right->val);

	bool leftvalid = true, rightvalid = true;
	if (root->left != NULL)
	{
		if (root->left->val >= root->val)
			return false;

		leftvalid = getandValidAllChildVals(root->left, myleftVals);
	}

	if (root->right != NULL)
	{
		if (root->right->val <= root->val)
			return false;

		rightvalid = getandValidAllChildVals(root->right, myRightVals);
	}

	if (leftvalid && rightvalid)
	{
		if (myleftVals.size() > 0)
		{
			for (int i = 0; i < myleftVals.size(); i++)
			{
				if (myleftVals[i] >= root->val)
					return false;
			}
		}

		if (myRightVals.size() > 0)
		{
			for (int i = 0; i < myRightVals.size(); i++)
			{
				if (myRightVals[i] <= root->val)
					return false;
			}
		}

		return true;
	}	
	
	return false;
}

bool isPossible(TreeNode* root, long long l, long long r) 
{
	if (root == nullptr)  
		return true;
	if (root->val > l && root->val < r)
		return isPossible(root->left, l, root->val) && isPossible(root->right, root->val, r);
	else 
		return false;
}

void testisValidBST()
{
	//TreeNode n3(3), n1(1), n5(5), n0(0), n2(2), n4(4), n6(6), n3_2(3);
	//n3.left = &n1;
	//n3.right = &n5;
	//n1.left = &n0;
	//n1.right = &n2;
	//n2.right = &n3_2;
	//n5.left = &n4;
	//n5.right = &n6;
	//isValidBST(&n3);

	TreeNode n1(1), n1_2(1);
	n1.right = &n1_2;
	isValidBST(&n1);	
	isPossible(&n1, INT_MAX, INT_MIN);
	long long int min = -1000000000000, max = 1000000000000;
	isPossible(&n1, min, max);
}

// https://leetcode.com/problems/same-tree/description/
bool verifyTree(TreeNode* p, TreeNode* q)
{
	if (p == NULL && q == NULL)
		return true;

	if ((p == NULL && q != NULL) || (p != NULL && q == NULL) || (p->val != q->val))
		return false;

	bool l = verifyTree(p->left, q->left);
	if (l)
		return verifyTree(p->right, q->right);

	return false;
}

bool isSameTree(TreeNode* p, TreeNode* q)
{
	return verifyTree(p, q);
}

void testisSameTree()
{
	vector<int> v1({ 0,1,2,INT_MIN, INT_MIN, 5,6 });
	vector<int> v2({ 0,1,2,INT_MIN, 4, INT_MIN,6 });
	TreeNode **t1 = createTree(v1);
	TreeNode **t2 = createTree(v2);
	isSameTree(*t1, *t2);
}

//https://leetcode.com/problems/n-ary-tree-postorder-traversal/description/
void postorderNArrTree(Node* root, vector<int> &ret)
{
	if (root == NULL)
		return;
	if (root->children.size() == 0)
	{
		ret.push_back(root->val);		
	}
	else
	{
		for (int i = 0; i < root->children.size(); i++)
		{
			postorderNArrTree(root->children[i], ret);
		}
		ret.push_back(root->val);
	}
}

vector<int> postorder(Node* root) 
{
	vector<int> ret;
	if (root == NULL)
		return ret;

	if (root->children.size() == 0)
	{
		ret.push_back(root->val);
	}
	else
	{
		for (int i = 0; i < root->children.size(); i++)
		{
			postorderNArrTree(root->children[i], ret);
		}

		ret.push_back(root->val);
	}
	return ret;
}

//https://leetcode.com/problems/binary-tree-level-order-traversal/description/
vector<vector<int>> levelOrder(TreeNode* root) 
{
	vector<vector<int>> ret;
	if (root == NULL)
		return ret;

	list<TreeNode*> nodeList1, nodeList2;
	nodeList1.push_back(root);
	vector<int> onelevel;
	list<TreeNode*>* nodeListIdx = &nodeList1;

	while (nodeListIdx->size() > 0)
	{
		list<TreeNode*>::iterator itor = nodeListIdx->begin();
		while (itor != nodeListIdx->end())
		{
			onelevel.push_back((*itor)->val);
			if ((*itor)->left != NULL)
			{
				if (nodeListIdx == &nodeList1)
					nodeList2.push_back((*itor)->left);
				else
					nodeList1.push_back((*itor)->left);
			}
			if ((*itor)->right != NULL)
			{
				if (nodeListIdx == &nodeList1)
					nodeList2.push_back((*itor)->right);
				else
					nodeList1.push_back((*itor)->right);
			}

			itor++;
		}
		ret.push_back(onelevel);
		onelevel.clear();
		nodeListIdx->clear();
		if (nodeListIdx == &nodeList1)
			nodeListIdx = &nodeList2;
		else
			nodeListIdx = &nodeList1;
	}

	return ret;
}
void testlevelOrder()
{
	vector<int> values({ 3,9,20,INT_MIN,INT_MIN,15,7 });
	TreeNode** root = createTree(values);

	levelOrder(*root);

	deleteTree(root, values.size());
}

//https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/
vector<vector<int>> levelOrderBottom(TreeNode* root) 
{	
	stack<vector<int> > reverseLevel;
	vector<vector<int>> ret;
	if (root == NULL)
		return ret;

	list<TreeNode *> nodelist1, nodelist2, * nodeIdx;
	nodeIdx = &nodelist1;
	nodeIdx->push_back(root);
	vector<int> onelevel;
	while (nodeIdx->size() > 0)
	{		
		list<TreeNode *>::iterator itor = nodeIdx->begin();
		while (itor != nodeIdx->end())
		{
			onelevel.push_back((*itor)->val);
			if ((*itor)->left)
			{
				if (nodeIdx == &nodelist1)
					nodelist2.push_back((*itor)->left);
				else
					nodelist1.push_back((*itor)->left);
			}

			if ((*itor)->right)
			{
				if (nodeIdx == &nodelist1)
					nodelist2.push_back((*itor)->right);
				else
					nodelist1.push_back((*itor)->right);
			}
			itor++;
		}

		reverseLevel.push(onelevel);
		onelevel.clear();
		nodeIdx->clear();
		if (nodeIdx == &nodelist1)
			nodeIdx = &nodelist2;
		else
			nodeIdx = &nodelist1;
	}

	while (reverseLevel.size() > 0)
	{
		ret.push_back(reverseLevel.top());
		reverseLevel.pop();
	}

	return ret;
}

void testlevelOrderBottom()
{
	vector<int> values({ 3,9,20,INT_MIN,INT_MIN,15,7 });
	TreeNode** root = createTree(values);

	levelOrderBottom(*root);

	deleteTree(root, values.size());
}
//https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/
void insertNodeToTree(TreeNode*& root, vector<int>& nums, int l, int r)
{
	if (l <= r)
	{
		int m = (l + r) / 2;
		root = new TreeNode(nums[m]);
		insertNodeToTree(root->left, nums, l, m-1);
		insertNodeToTree(root->right, nums, m+1, r);
	}
}

TreeNode* sortedArrayToBST(vector<int>& nums)
{
	if (nums.size() == 0)
		return NULL;
	TreeNode* root = NULL;
	insertNodeToTree(root, nums, 0, nums.size() - 1);
	return root;
}

void testsortedArrayToBST()
{
	vector<int> nums({ -10, -3, 0, 5, 9 });
	sortedArrayToBST(nums);
}

//https://leetcode.com/problems/balanced-binary-tree/
int checkTreeBalanced(TreeNode* root)
{
	if (root == NULL)
		return 0;

	int l = 0, r = 0;

	l = checkTreeBalanced(root->left);
	if (l == -1)
		return -1;
	r = checkTreeBalanced(root->right);
	if (r == -1)
		return -1;
	if (std::abs(l - r) > 1)
		return -1;

	return std::max(l, r) + 1;
}

bool isBalanced(TreeNode* root) 
{
	if (root == NULL)
		return true;
	
	return checkTreeBalanced(root) != -1;
}

void testisBalanced()
{
	//vector<int> values({ 3,9,20,5,INT_MIN,15,7, 6, 7,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,13 });
	vector<int> values({ 1,2,2,3,3,INT_MIN,INT_MIN,4,4 });
	//vector<int> values({ 1, 2, 2, 3, INT_MIN, INT_MIN, 3, 4, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 4 });
	TreeNode** root = createTree(values);
	isBalanced(*root);
	deleteTree(root, values.size());
}


//https://leetcode.com/problems/minimum-depth-of-binary-tree/description/
int getTreeHeight(TreeNode* root)
{
	if (root == NULL)
		return 0;

	int l = getTreeHeight(root->left);
	int r = getTreeHeight(root->right);

	return std::max(l, r) + 1;
}

int getLeafMinSteps(TreeNode* root)
{
	if (root->left == NULL && root->right == NULL)
		return 1;

	int l = INT_MAX, r = INT_MAX;
	if (root->left)
	{
		l = getLeafMinSteps(root->left);
	}

	if (root->right)
		r = getLeafMinSteps(root->right);

	return std::min(l, r) + 1;
}

int minDepth(TreeNode* root) 
{
	if (root == NULL)
		return 0;

	return getLeafMinSteps(root);
}

void testminDepth()
{
	vector<int> values({ -9,-3,2,INT_MIN,4,4,0,INT_MIN , INT_MIN ,-6,INT_MIN,-5 });
	TreeNode** root = createTree(values);
	minDepth(*root);
	deleteTree(root, values.size());
}

//https://leetcode.com/problems/path-sum/description/
bool checkTheSum(TreeNode* root, int targetSum)
{
	if (root->val == targetSum && root->left == NULL && root->right == NULL)
		return true;

	bool b = false;
	if (root->left)
		b = checkTheSum(root->left, targetSum - root->val);
	if (b)
		return b;

	if (root->right)
		b = checkTheSum(root->right, targetSum - root->val);
	return b;
}

bool hasPathSum(TreeNode* root, int targetSum) 
{
	if (root == NULL)
		return false;

	if (root->val == targetSum && root->left == NULL && root->right == NULL)
		return true;

	return checkTheSum(root, targetSum);
}

void testhasPathSum()
{
	vector<int> values({ 5,4,8,11,INT_MIN,13,4,7,2,INT_MIN,INT_MIN,INT_MIN,1 });
	TreeNode** root = createTree(values);
	hasPathSum(*root, 22);
	deleteTree(root, values.size());
}


//https://leetcode.com/problems/path-sum-ii/description/
void getNodesOnSumPath(TreeNode* root, int targetSum, vector<int> nodesOnPath, vector<vector<int>> &result)
{
	if (targetSum == root->val && root->left == NULL && root->right == NULL)
	{
		nodesOnPath.push_back(root->val);
		result.push_back(nodesOnPath);
		nodesOnPath.pop_back();
		return;
	}

	if (root->left == NULL && root->right == NULL)
		return;

	nodesOnPath.push_back(root->val);
	if (root->left)
	{
		getNodesOnSumPath(root->left, targetSum - root->val, nodesOnPath, result);
	}

	if (root->right)
	{
		getNodesOnSumPath(root->right, targetSum - root->val, nodesOnPath, result);
	}

	nodesOnPath.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) 
{
	vector<vector<int>> ret;
	vector<int> nodesOnPath;
	if (root == NULL)
		return ret;

	getNodesOnSumPath(root, targetSum, nodesOnPath, ret);

	return ret;
}

void testpathSum()
{	
//	vector<int> values({ 5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 5, 1 });
	vector<int> values({ 1,2});
	TreeNode** root = createTree(values);
	pathSum(*root, 1);
	deleteTree(root, values.size());
}

//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
void flatten(TreeNode* root) 
{
	if (root == NULL)
		return;

	if (root->left)
		flatten(root->left);

	if (root->right)
		flatten(root->right);

	if (root->left)
	{
		if (root->right)
		{
			TreeNode* tmp = root->right;
			root->right = root->left;			
			TreeNode* idx = root->right;
			while (idx->right != NULL)
				idx = idx->right;

			idx->right = tmp;
		}
		else
			root->right = root->left;

		root->left = NULL;
	}

	return;
}

void testflatten()
{
//	vector<int> values({ 1,2,5,3,4,INT_MIN,6 });
	vector<int> values({ 1,INT_MIN, 2,INT_MIN,INT_MIN,3, INT_MIN });
	TreeNode** root = createTree(values);
	flatten(*root);
	deleteTree(root, values.size());
}

//https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
Node* connect(Node* root) 
{
	if (root == NULL)
		return root;

	list<Node*> listNode1, listNode2;
	list<Node*>* listIdx = &listNode1;
	if (root->left)
		listNode1.push_back(root->left);
	if (root->right)
		listNode1.push_back(root->right);
	while (listIdx->size() > 0)
	{
		list<Node*>::iterator itor = listIdx->begin();
		Node* pNode = *itor;
		itor++;
		pNode->next = (*itor);
		if (pNode->left)
		{
			if (listIdx == &listNode1)
				listNode2.push_back(pNode->left);
			else
				listNode1.push_back(pNode->left);
		}

		if (pNode->right)
		{
			if (listIdx == &listNode1)
				listNode2.push_back(pNode->right);
			else
				listNode1.push_back(pNode->right);
		}
		
		while (itor != listIdx->end())
		{
			pNode->next = *itor;
			pNode = (*itor);
			if (pNode->left)
			{
				if (listIdx == &listNode1)
					listNode2.push_back(pNode->left);
				else
					listNode1.push_back(pNode->left);
			}

			if (pNode->right)
			{
				if (listIdx == &listNode1)
					listNode2.push_back(pNode->right);
				else
					listNode1.push_back(pNode->right);
			}
			itor++;			
		}

		listIdx->clear();
		if (listIdx == &listNode1)
			listIdx = &listNode2;
		else
			listIdx = &listNode1;

	}
	return root;
}

//https://leetcode.com/problems/sum-root-to-leaf-numbers/description/
void sumNumbers(TreeNode* root, int curSum, vector<int>& allSums)
{
	if (root == NULL)
		return;

	if (root->left == NULL && root->right == NULL)
	{
		allSums.push_back(curSum *10 + root->val);
	}

	if (root->left)
		sumNumbers(root->left, curSum * 10 + root->val, allSums);

	if (root->right)
		sumNumbers(root->right, curSum * 10 + root->val, allSums);
}

int sumNumbers(TreeNode* root) 
{
	vector<int> allSums;
	int ret = 0;
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
	{
		return root->val;
	}

	sumNumbers(root, 0, allSums);
	for (int i = 0; i < allSums.size(); i++)
		ret += allSums[i];


	return ret;
}

void testsumNumbers()
{
	vector<int> values({ 1,2,2,INT_MIN,3,INT_MIN,3 });

	TreeNode** root = createTree(values);

	sumNumbers(*root);

	deleteTree(root, values.size());
}

//https://leetcode.com/problems/clone-graph/
void cloneNode(Node* node, Node* clone, unordered_map<int, bool>& srcNodeMap, unordered_map<int, Node*>& destNodeMap)
{
	if (node == NULL)
		return;

	int i = 0;
	clone->neighbors.resize(node->neighbors.size());
	for (i = 0; i < node->neighbors.size(); i++)
	{
		if (destNodeMap.find(node->neighbors[i]->val) == destNodeMap.end())
		{
			clone->neighbors[i] = new Node();
			clone->neighbors[i]->val = node->neighbors[i]->val;
			destNodeMap[node->neighbors[i]->val] = clone->neighbors[i];
		}
		else
		{
			clone->neighbors[i] = destNodeMap[node->neighbors[i]->val];
		}
	}

	srcNodeMap[node->val] = true;
	for (i = 0; i < node->neighbors.size(); i++)
	{
		if (srcNodeMap.find(node->neighbors[i]->val) != srcNodeMap.end())
			continue;

		cloneNode(node->neighbors[i], clone->neighbors[i], srcNodeMap, destNodeMap);
	}
}

Node* cloneGraph(Node* node)
{
	if (node == NULL)
		return NULL;

	unordered_map<int, Node*> destNodeMap;
	unordered_map<int, bool> srcNodeMap;
	Node* clone = new Node();
	clone->val = node->val;
	destNodeMap[clone->val] = clone;
	cloneNode(node, clone, srcNodeMap, destNodeMap);

	return clone;
}

//https://leetcode.com/problems/gas-station/
void compressEqualCost(vector<int>& gas, vector<int>& cost, vector<int>& compressedGas, vector<int>& compressedCost, unordered_map<int, int>& indexMap)
{
	for (int i = 0; i < gas.size(); i++)
	{
		if (gas[i] != cost[i])
		{
			compressedGas.push_back(gas[i]);
			compressedCost.push_back(cost[i]);
			indexMap[compressedGas.size() - 1] = i;
		}
	}
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
{
	if (gas.size() != cost.size())
		return -1;

	if (gas.size() == 1)
	{
		if (gas[0] >= cost[0])
			return 0;
		else
			return -1;
	}

	vector<int> compressedGas;
	vector<int> compressedCost;
	unordered_map<int, int> indexMap;

	compressEqualCost(gas, cost, compressedGas, compressedCost, indexMap);

	vector<int> startCandidates;
	int i = 0;
	uint32_t totalGas = 0, totalCost = 0;
	for (i = 0; i < compressedGas.size(); i++)
	{
		if (compressedGas[i] >= compressedCost[i])
			startCandidates.push_back(i);

		totalGas += compressedGas[i];
		totalCost += compressedCost[i];
	}
	
	if (startCandidates.size() == 0 || totalGas < totalCost)
		return -1;

	if (totalCost == 0)
		return 0;

	for (i = 0; i < startCandidates.size(); i++)
	{
		int start = startCandidates[i];
		int idx = start + 1;
		if (idx == compressedGas.size())
			idx = 0;

		int gasleft = compressedGas[start] - compressedCost[start];
		while (idx != start && gasleft >= 0)
		{
			gasleft += compressedGas[idx] - compressedCost[idx];

			if (idx + 1 == compressedGas.size())
				idx = 0;
			else
				idx++;
		}

		if (idx == start && gasleft >= 0)
			return indexMap[start];
	}

	return -1;
}

void testcanCompleteCircuit()
{
	vector<int>  gas({ 3, });
	vector<int> cost({ 3,});

	canCompleteCircuit(gas, cost);
}

//https://leetcode.com/problems/single-number/
//https://leetcode.com/problems/single-number-ii/description/
int singleNumber1(vector<int>& nums) 
{
	int ret = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		ret ^= nums[i];
	}

	return ret;
}

int singleNumber(vector<int>& nums) {

	int ones = 0, twos = 0;
	for (int num : nums) 
	{
		ones = (ones ^ num) & ~twos;
		twos = (twos ^ num) & ~ones;
	}
	return ones;
}

void testsingleNumber()
{
	vector<int> nums({ 1,2,3,4,5,4,3,2,1,1,2,3,4 });
	singleNumber(nums);
}

//https://leetcode.com/problems/copy-list-with-random-pointer/
Node* copyRandomList(Node* head) 
{
	if (head == NULL)
		return NULL;

	unordered_map<Node*, Node*> nodeMap;

	Node* srcidx = head->next;
	Node* ret = new Node(head->val);
	nodeMap[head] = ret;

	Node* copyidx1 = ret, * copyidx2 = NULL;
	while (srcidx != NULL)
	{
		copyidx2 = new Node(srcidx->val);
		nodeMap[srcidx] = copyidx2;
		srcidx = srcidx->next;
	}

	srcidx = head;
	while (srcidx != NULL)
	{
		if (srcidx->random)
		{
			nodeMap[srcidx]->random = nodeMap[srcidx->random];
		}
		nodeMap[srcidx]->next = nodeMap[srcidx->next];
		srcidx = srcidx->next;
	}
	
	return nodeMap[head];
}

//https://leetcode.com/problems/linked-list-cycle-ii/description/
ListNode* detectCycle_slow(ListNode* head) 
{
	if (head == NULL || head->next == NULL || head->next->next == NULL)
		return NULL;

	ListNode* idx1 = head->next, * idx2 = head->next->next;
	while (idx1 != idx2)
	{
		if (idx1 != NULL)
			idx1 = idx1->next;
		else
			return NULL;

		if (idx2 != NULL && idx2->next != NULL && idx2->next->next != NULL)
			idx2 = idx2->next->next;
	}

	return idx1->next;
	/*
	if (head == NULL || head->next == NULL || head->next->next == NULL)
		return NULL;

	ListNode* idx = head;
	unordered_map<ListNode *, bool> nodeMap;
	
	while (idx != NULL)
	{
		if (nodeMap.find(idx) != nodeMap.end())
			return idx;

		nodeMap[idx] = true;
		idx = idx->next;
	}

	return NULL;
	*/
}

ListNode* detectCycle(ListNode* head) 
{
	ListNode* slow = head, * fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) 
			break;
	}
	if (!(fast && fast->next)) 
		return NULL;
	while (head != slow) {
		head = head->next;
		slow = slow->next;
	}
	return head;
}

void testdetectCycle()
{
	ListNode l1(1), l2(2), l3(3), l4(4), l5(5), l6(6);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l5;
	l5.next = &l6;
	l6.next = &l3;
	detectCycle(&l1);
	detectCycle_slow(&l1);
}

//https://leetcode.com/problems/reorder-list/description/
void reorderList(ListNode* head) 
{
	if (head == NULL || head->next == NULL)
		return;

	int nodes = 0;
	ListNode* idx = head;
	while (idx != NULL)
	{
		nodes++;
		idx = idx->next;
	}
	
	int lastHalfNodes = nodes / 2;
	int firstHalfNodes = nodes / 2;
	if (nodes % 2 != 0)
		firstHalfNodes++;

	int i = 1;
	ListNode* lastHalfList = head;
	while (i < firstHalfNodes)
	{
		lastHalfList = lastHalfList->next;
		i++;
	}
	ListNode* tmp = lastHalfList->next;
	lastHalfList->next = NULL;
	lastHalfList = tmp;

	ListNode* lastHalfIdx1 = lastHalfList, * lastHalfIdx2 = lastHalfList->next;
	lastHalfIdx1->next = NULL;
	while (lastHalfIdx2 != NULL)
	{
		ListNode* tmp = lastHalfIdx2->next;
		lastHalfIdx2->next = lastHalfIdx1;
		lastHalfIdx1 = lastHalfIdx2;
		lastHalfIdx2 = tmp;
	}
	lastHalfList = lastHalfIdx1;
	idx = head;
	ListNode* idx2 = lastHalfList;
	while (idx != NULL && idx2 != NULL)
	{
		ListNode* tmp = idx->next, *tmp2 = idx2->next;
		idx->next = idx2;
		idx2->next = tmp;
		idx = tmp;
		idx2 = tmp2;
	}
}

void testreorderList()
{
	vector<int> values({1,2,3,4,5 });
	ListNode* head = createListNode(values);

	reorderList(head);
	deleteList(head);
}

//https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/description/
ListNode* deleteMiddle(ListNode* head) 
{
	if (head == NULL || head->next == NULL)
		return NULL;

	int nodes = 0;
	ListNode* idx = head;
	while (idx != NULL)
	{
		nodes++;
		idx = idx->next;
	}

	int midnode = nodes / 2, mididx = 0;
	idx = head;
	ListNode* idx2 = head->next;
	while (mididx < midnode -1)
	{
		idx = idx2;
		idx2 = idx2->next;
		mididx++;
	}
	idx->next = idx2->next;

	return head;
}

//https://leetcode.com/problems/lru-cache/description/
class LRUCache {
private :
	int capacity;
	unordered_map<int, list<pair<int, int> >::iterator> kv;
	list<pair<int, int> > keylist;

public:
	LRUCache(int cap) {
		capacity = cap;		
	}

	int get(int key) {
		if (kv.find(key) == kv.end())
			return -1;

		list<pair<int, int> >::iterator itor = kv[key];
		int v = itor->second;
		keylist.erase(itor);
		keylist.push_back(pair<int, int>(key, v));
		itor = keylist.end();
		itor--;
		kv[key] = itor;

		return v;
	}

	void put(int key, int value) {
		if (kv.find(key) != kv.end())
		{
			keylist.erase(kv[key]);
			kv.erase(key);
		}
		else if (kv.size() == capacity)
		{
			list<pair<int, int> >::iterator itor = keylist.begin();
			kv.erase(itor->first);
			keylist.erase(itor);
		}

		keylist.push_back(pair<int, int>(key, value));
		list<pair<int, int> >::iterator itor = keylist.end();
		itor--;
		kv[key] = itor;
	}
};

void testLRUCache()
{
	//[[2],[2],[2,6],[1],[1,5],[1,2],[1],[2]]
	LRUCache lru(2);	
	lru.put(2, 6);
	lru.put(1,5);
	lru.put(1, 2);
	
	lru.get(2);
}

//https://leetcode.com/problems/reverse-words-in-a-string/
int getNextChar(string& s, int idx)
{
	while (idx < s.size())
	{
		if (s[idx] != ' ')
			break;
		idx++;
	}

	return idx;
}

int getNextSpace(string& s, int idx)
{
	while (idx < s.size())
	{
		if (s[idx] == ' ')
			break;
		idx++;
	}

	return idx;
}

string reverseWords(string s) 
{
	int i = 0;
	string ret;
	stack<string> words;
	while (i < s.size())
	{
		if (s[i] == ' ')
		{
			i = getNextChar(s, i);			
		}
		else
		{
			int j = getNextSpace(s, i);
			string tmp(s.substr(i, j - i));
			words.push(tmp);
			i = j;
		}
	}

	while (words.size() > 0)
	{
		ret.append(words.top().c_str());		
		words.pop();
		if (words.size() > 0)
			ret.push_back(' ');
	}

	return ret;
}

void testreverseWords()
{
	string s("   the sky is    blue   ");
	reverseWords(s);

}

int kadaneAlgo(vector<int> &array) 
{
	//nums = [-2,1,-3,4,-1,2,1,-5,4]

	int max_ending_here = 0;
	int max_so_far = INT_MIN;
	for (int i = 0; i < array.size(); i++) {
		if (array[i] + max_ending_here > array[i]) {
			max_ending_here = array[i] + max_ending_here;
		}
		else {
			max_ending_here = array[i];
		}
		if (max_ending_here > max_so_far) {
			max_so_far = max_ending_here;
		}
	}
	return max_so_far;
}

//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
// 查找循环右移有序数组的最小值
// 时间复杂度：O(log n)
int findMin(vector<int>& nums) {
	int numsSize = nums.size();

	if (numsSize == 0) return -1;

	int left = 0;
	int right = numsSize - 1;

	// 如果数组没有被旋转（或旋转了n次），直接返回第一个元素
	if (nums[left] < nums[right]) {
		return nums[left];
	}

	while (left < right) {
		int mid = left + (right - left) / 2;

		if (nums[mid] > nums[right]) {
			// 最小值在右半部分
			left = mid + 1;
		}
		else if (nums[mid] < nums[right]) {
			// 最小值在左半部分（包括mid）
			right = mid;
		}
		else {
			// nums[mid] == nums[right]，无法确定，缩小范围
			right--;
		}
	}

	return nums[left];
}

void testfindMin()
{
	//vector<int> nums({ 11,13,15,17});
	//vector<int> nums({ 3,4,5,1,2});
	vector<int> nums({ 3,1,2 });
	findMin(nums);
}

//https://leetcode.com/problems/binary-tree-right-side-view/description/
vector<int> rightSideView(TreeNode* root) 
{
	vector<int> ret;
	if (root == NULL)
		return ret;

	vector<TreeNode*> nodeOnLevel1, nodeOnLevel2;	
	nodeOnLevel1.push_back(root);
	vector<TreeNode*>* nodeOnLevelIdx = &nodeOnLevel1;
	while (nodeOnLevelIdx->size() > 0)
	{
		ret.push_back((*nodeOnLevelIdx)[nodeOnLevelIdx->size() - 1]->val);
		for (int i = 0; i < nodeOnLevelIdx->size(); i++)
		{
			if (nodeOnLevelIdx == &nodeOnLevel1)
			{
				if ((*nodeOnLevelIdx)[i]->left != NULL)
					nodeOnLevel2.push_back((*nodeOnLevelIdx)[i]->left);

				if ((*nodeOnLevelIdx)[i]->right != NULL)
					nodeOnLevel2.push_back((*nodeOnLevelIdx)[i]->right);
			}
			else
			{
				if ((*nodeOnLevelIdx)[i]->left != NULL)
					nodeOnLevel1.push_back((*nodeOnLevelIdx)[i]->left);

				if ((*nodeOnLevelIdx)[i]->right != NULL)
					nodeOnLevel1.push_back((*nodeOnLevelIdx)[i]->right);
			}
		}
		
		nodeOnLevelIdx->clear();
		if (nodeOnLevelIdx == &nodeOnLevel1)
			nodeOnLevelIdx = &nodeOnLevel2;
		else
			nodeOnLevelIdx = &nodeOnLevel1;
	}

	return ret;
}

void testrightSideView()
{
	vector<int> values({ 1,2,3,INT_MIN,5,INT_MIN,4 });
	TreeNode** root = createTree(values);
	rightSideView(*root);
	deleteTree(root, values.size());
}
//https://leetcode.com/problems/number-of-islands/description/
void markAdjecentedIslands(vector<vector<char>>& grid, int row, int col, vector<vector<char>>& markedIslands, int &curIslands)
{
	list<pair<int, int> > pointlist;
	pointlist.push_back(pair<int, int>(row, col));

	while (pointlist.size() > 0)
	{
		int r = pointlist.front().first;
		int c = pointlist.front().second;

		if (c + 1 < grid[0].size() && grid[r][c + 1] == '1' && markedIslands[r][c + 1] == 0)
		{
			pointlist.push_back(pair<int, int>(r, c + 1));
			markedIslands[r][c + 1] = 1;
		}
		if (c - 1 >= 0 && grid[r][c - 1] == '1' && markedIslands[r][c - 1] == 0)
		{
			pointlist.push_back(pair<int, int>(r, c - 1));
			markedIslands[r][c - 1] = 1;
		}

		if (r + 1 < grid.size() && grid[r + 1][c] == '1' && markedIslands[r + 1][c] == 0)
		{
			pointlist.push_back(pair<int, int>(r + 1, c));
			markedIslands[r + 1][c] = 1;
		}
		if (r - 1 >= 0 && grid[r - 1][c] == '1' && markedIslands[r - 1][c] == 0)
		{
			pointlist.push_back(pair<int, int>(r - 1, c));
			markedIslands[r -1][c] = 1;
		}

		pointlist.pop_front();
	}
}

int numIslands(vector<vector<char>>& grid) 
{
	int curIslands = 0;
	vector<vector<char>> markedIslands;
	markedIslands.resize(grid.size());
	int row, col;
	for (row = 0; row < grid.size(); row++)
		markedIslands[row].resize(grid[0].size());

	row = 0;
	while (row < grid.size())
	{
		col = 0;
		while (col < grid[0].size())
		{
			if (markedIslands[row][col] || grid[row][col] == '0')
			{
				col++;
				continue;
			}

			curIslands++;
			markedIslands[row][col] = 1;
			markAdjecentedIslands(grid, row, col, markedIslands, curIslands);
			col++;
		}
		row++;
	}

	return curIslands;
}

void testnumIslands()
{
	//vector<vector<char>> grid({ {'1','1','1','1','0'},
	//							{'1','1','0','1','0'},
	//							{'1','1','0','0','0'},
	//							{'0','0','0','0','0'} });
	vector<vector<char>> grid({ {'1','1','1'},
								{'0','1','0'},
								{'1','1','0'},
								{'1','1','1'}});
	numIslands(grid);
}

//https://leetcode.com/problems/rotate-array/
void rotate(vector<int>& nums, int k) 
{
	k = k % nums.size();

	if (k == 0)
		return;

	std::reverse(nums.begin(), nums.end());
	std::reverse(nums.begin(), nums.begin() + k);
	std::reverse(nums.begin() + k, nums.end());

	/*
	int newidx = k - 1;
	int curidx = nums.size() - 1;
	int oriNumAtNewIdx = nums[newidx];
	int movednums = 0;
	for (curidx = 0; curidx < nums.size() -k; curidx++)
	{
		newidx = curidx + k;
		if (newidx >= nums.size())
			newidx -= nums.size();

		int tmp = nums[newidx];
		nums[newidx] = nums[curidx];
		nums[curidx] = tmp;
	}
	int kidx = k;
	while (kidx >  0)
	{
		int tmp = nums[curidx];
		nums[curidx] = nums[curidx + kidx];
		nums[curidx + kidx] = tmp;
		kidx--;
	}
	*/
}

void testrotate()
{
	vector<int> nums({ 0,1,2,3,4,5,6,7,8});
	// 876543210
	// 678012345
	// 
	// 345678012
	// 
	//

	rotate(nums, 3);
}

//https://leetcode.com/problems/number-of-1-bits/
int hammingWeight(int n) {
	if (n == 0)
		return 0;
	
	int ret = 0;
	for (int i = 0; i < 32; i++)
	{
		if (((1 << i) & n) != 0)
			ret++;
	}

	return ret;
}


//https://leetcode.com/problems/isomorphic-strings/description/

void getLetterPos(string& s, string& t, int i, set<int> sset, set<int> tset)
{	
	char sc = s[i], tc = t[i];
	while (i < s.size())
	{
		if (sc == s[i])
		i++;
	}
}

bool isIsomorphic(string s, string t) 
{
	// badc, baba
	if (s.size() != t.size())
		return false;

	int i = 0;
	set<char> charChecked;
	while (i < s.size())
	{
		if (charChecked.find(s[i]) != charChecked.end())
		{
			i++;
			continue;
		}

		int j = i + 1;
		charChecked.insert(s[i]);
		while (j < s.size())
		{
			if ((s[j] == s[i] && t[j] != t[i]) || 
				(s[j] != s[i] && t[j] == t[i]))
				return false;
			j++;
		}		
	}

	return true;
}
//https://leetcode.com/problems/excel-sheet-column-number/description/
int titleToNumber(string columnTitle) 
{
	int num = 0;	
	for (int i = 0; i < columnTitle.size(); i++)
	{
		num = num * 26 + columnTitle[i] - 'A' + 1;
	}

	return num;
}

void testtitleToNumber()
{
	string s("a");
	titleToNumber(s);
}

//https://leetcode.com/problems/course-schedule/description/
bool canGotoParentCouse(int course, vector<list<int>> &courseDep, vector<bool> couseOnPath, vector<bool> &courseItored)
{
	if (courseItored[course])
		return true;

	list<int>::iterator itor(courseDep[course].begin());
	while (itor != courseDep[course].end())
	{
		int parentCourse = *itor;
		if (couseOnPath[parentCourse])
			return false;

		vector<bool> tmp_couseOnPath(couseOnPath);

		tmp_couseOnPath[parentCourse] = true;
		if (!canGotoParentCouse(parentCourse, courseDep, tmp_couseOnPath, courseItored))
			return false;
		
		itor++;
	}

	courseItored[course] = true;

	return true;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
{
	if (prerequisites.size() == 0)
		return true;

	numCourses++;
	vector<bool> courseItored(numCourses, 0);
	vector<list<int>> courseDep(numCourses);
	int i = 0;
	for (i = 0; i < prerequisites.size(); i++)
	{
		courseDep[prerequisites[i][0]].push_back(prerequisites[i][1]);
	}

	for (i = 0; i < courseDep.size(); i++)
	{
		if (courseItored[i])
			continue;

		list<int>::iterator itor(courseDep[i].begin());
		while (itor != courseDep[i].end())
		{	
			vector<bool> courseOnPath(numCourses, 0);

			int parentCourse = *itor;
			courseOnPath[i] = true;
			courseOnPath[parentCourse] = true;
			if (!canGotoParentCouse(parentCourse, courseDep, courseOnPath, courseItored))
				return false;
			itor++;
		}
		courseItored[i] = true;
	}
	return true;
}

void testcanFinish()
{
	// 1 0
	// 2 6
	// 1 7
	// 6 4
	// 7 0
	// 0 5
	// 5 6
	// 
	//[1,0],[0,3],[0,2],[3,2],[2,5],[4,5],[5,6],[2,4]
	vector<vector<int>> prerequisites({ {1,0},{2,6},{1,7},{6,4},{7,0},{0,5}, {5,6} });
	canFinish(8, prerequisites);
}

//https://leetcode.com/problems/implement-trie-prefix-tree/description/
class Trie 
{
public:
	unordered_map<char, Trie*> mTree;
	bool isLastChar;
	string word;
	void insertToTrie(string &word, int i)
	{
		if (i == word.size())
		{
			isLastChar = true;
			this->word = word;
			return;
		}

		char c = word[i];

		if (mTree.find(c) == mTree.end())
		{
			mTree[c] = new Trie();
		}
		mTree[c]->insertToTrie(word, i + 1);
	}

	bool searchTrie(string& word, int i)
	{
		if (i == word.size())
		{
			return isLastChar;
		}

		char c = word[i];
		if (mTree.find(c) == mTree.end())
			return false;

		return mTree[c]->searchTrie(word, i + 1);
	}

	bool startsWith(string& word, int i)
	{
		if (i == word.size())
			return true;

		char c = word[i];
		if (mTree.find(c) == mTree.end())
			return false;

		return mTree[c]->startsWith(word, i + 1);
	}

public:
	Trie() 
	{
		isLastChar = false;
	}

	void insert(string word) 
	{
		insertToTrie(word, 0);
	}

	bool search(string word) {
		return searchTrie(word, 0);
	}

	bool startsWith(string prefix) {
		return startsWith(prefix, 0);
	}

	Trie* getTrie(char c)
	{
		if (mTree.find(c) == mTree.end())
			return NULL;

		return mTree[c];
	}

	string getWord()
	{
		return word;
	}
};

void testTrie()
{
	Trie t;
	t.insert("ab");
	t.insert("ac");
	t.search("a");
	t.startsWith("a");
}

//https://leetcode.com/problems/minimum-size-subarray-sum/
int minSubArrayLen(int target, vector<int>& nums) 
{
	int sum = nums[0];
	int i = 0, j = 1;
	int ret = INT_MAX;
	while (i < nums.size())
	{
		while (sum < target && j < nums.size())
		{
			sum += nums[j];
			j++;
		}

		if (sum >= target && j - i < ret)
			ret = j - i;

		if (ret == 1)
			return ret;

		if (sum - nums[i] >= target)
		{
			 while (sum - nums[i] >= target && i < j)
			 {
				 sum -= nums[i];
				 ret--;
				 i++;
			 }
		}
		else
		{
			sum -= nums[i];
			i++;
		}
	}

	if (ret == INT_MAX)
		return 0;

	return ret;
}

void testminSubArrayLen()
{
	vector<int> nums({ 2,3,1,2,4,3 });
	minSubArrayLen(7, nums);
}

//https://leetcode.com/problems/contains-duplicate/description/
bool containsDuplicate(vector<int>& nums) 
{
	unordered_map<int, bool> numMap;
	for (int i = 0; i < nums.size(); i++)
	{
		if (numMap.find(nums[i]) != numMap.end())
			return true;

		numMap[nums[i]] = true;
	}

	return false;
}

//https://leetcode.com/problems/contains-duplicate-ii/
bool containsNearbyDuplicate(vector<int>& nums, int k) 
{
	unordered_map<int, int> numMap;
	for (int i = 0; i < nums.size(); i++)
	{
		if (numMap.find(nums[i]) != numMap.end() && 
			abs(i - numMap[nums[i]]) <= k)
		{
			return true;
		}
		
		numMap[nums[i]] = i;
	}

	return false;
}

void testcontainsDuplicate()
{

}

//https://leetcode.com/problems/design-add-and-search-words-data-structure/
class WordDictionary {
private:
	unordered_map<char, WordDictionary*> mTree;
	bool isLastChar;

	void addWordToDict(string &word, int i)
	{
		if (i == word.size())
			return;

		if (mTree.find(word[i]) == mTree.end())
		{
			mTree[word[i]] = new WordDictionary();
		}
		else if (word.size() == i - 1)
		{
			mTree[word[i]]->isLastChar = true;
		}

		mTree[word[i]]->addWordToDict(word, i + 1);
	}

	bool searchDict(string& word, int i)
	{
		if (i == word.size())
			return true;

		if (mTree.find(word[i]) != mTree.end() )
			return mTree[word[i]]->searchDict(word, i + 1);

		if (word[i] == '.')
		{
			unordered_map<char, WordDictionary*>::iterator itor = mTree.begin();
			while (itor != mTree.end())
			{
				bool bFind = itor->second->searchDict(word, i + 1);
				if (bFind)
					return true;

				itor++;
			}
		}

		return false;
	}

public:
	WordDictionary():isLastChar(false)
	{
	}

	void addWord(string word) {
		addWordToDict(word, 0);

	}

	bool search(string word) {
		if (word.size() == 0)
			return false;

		return searchDict(word, 0);
	}
};

void testWorkDict()
{
	vector<string> words({ "WordDictionary","addWord","addWord","addWord","search","search","search","search" });
	vector<string> search({ "" ,"bad", "dad", "mad","pad", "bad", ".ad", "b.."});

	WordDictionary dict;
	for (int i = 0; i < words.size(); i++)
		dict.addWord(words[i]);

	for (int i = 0; i < search.size(); i++)
		dict.search(search[i]);
}


//https://leetcode.com/problems/remove-linked-list-elements/
ListNode* removeElements(ListNode* head, int val) 
{
	while (head != NULL && head->val == val)
		head = head->next;

	if (head == NULL)
		return head;

	ListNode* ptmp1 = head, *ptmp2 = head->next;
	while (ptmp1 != NULL)
	{
		while (ptmp2 != NULL && ptmp2->val == val)
		{
			ptmp2 = ptmp2->next;
		}

		ptmp1->next = ptmp2;
		if (ptmp2 == NULL)
			break;

		ptmp1 = ptmp2;
		ptmp2 = ptmp2->next;
	}

	return head;
}

//https://leetcode.com/problems/word-search-ii/description/
void findWordStartPos(vector<vector<char>>& board, char c, list<pair<int, int>> &start_r_c)
{
	int row = 0, col = 0;
	for (row = 0; row < board.size(); row++)
	{
		for (col = 0; col < board[0].size() ; col++)
		{
			if (board[row][col] == c)
			{
				start_r_c.push_back(pair<int, int>(row, col));
			}
		}
	}
}

bool IsPosonPath(int r, int c, vector<vector<char>>& board)
{
	return board[r][c] == '#';
}
void findNextAdjancent(vector<vector<char>>& board, int r, int c, Trie* M_Tree, vector<string> &ret)
{
	if (M_Tree->isLastChar)
	{
		M_Tree->isLastChar = false;
		ret.push_back(M_Tree->word);
		M_Tree->word.clear();		
	}

	unordered_map<char, Trie*>::iterator itor(M_Tree->mTree.begin());
	while (itor != M_Tree->mTree.end())
	{
		char tmp_c = itor->first;
		if(r - 1 >= 0 && board[r - 1][c] == tmp_c && !IsPosonPath(r - 1, c, board))
		{
			board[r - 1][c] = '#';
			findNextAdjancent(board, r - 1, c, itor->second, ret);
			board[r - 1][c] = tmp_c;
		}

		if (r + 1 < board.size() && board[r + 1][c] == tmp_c && !IsPosonPath(r + 1, c, board))
		{
			board[r + 1][c] = '#';
			findNextAdjancent(board, r + 1, c, itor->second, ret);
			board[r + 1][c] = tmp_c;
		}

		if (c - 1 >= 0 && board[r][c - 1] == tmp_c && !IsPosonPath(r, c - 1, board))
		{
			board[r][c - 1] = '#';
			findNextAdjancent(board, r, c - 1, itor->second, ret);
			board[r][c - 1] = tmp_c;
		}

		if (c + 1 < board[0].size() && board[r][c + 1] == tmp_c && !IsPosonPath(r, c + 1, board))
		{
			board[r][c + 1] = '#';
			findNextAdjancent(board, r, c + 1, itor->second, ret);
			board[r][c + 1] = tmp_c;
		}

		itor++;
	}

	return;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
{
	vector<string> ret;
	unordered_map<int, set<int>> posOnPath;
	list<pair<int, int>>start_r_c;

	Trie m_Tree;

	int w = 0;
	int r, c;

	for (w = 0; w < words.size(); w++)
	{
		if (words[w].size() > board[0].size() * board.size())
			continue;
		m_Tree.insert(words[w]);
	}

	unordered_map<char, Trie*>::iterator MTree_itor(m_Tree.mTree.begin());
	while (MTree_itor != m_Tree.mTree.end())
	{
		start_r_c.clear();
		char tmp_c = MTree_itor->first;
		findWordStartPos(board, tmp_c, start_r_c);
		if (start_r_c.size() == 0)
		{
			MTree_itor++;
			continue;
		}

		list<pair<int, int>>::iterator itor(start_r_c.begin());
		while (itor != start_r_c.end())
		{
			r = itor->first;
			c = itor->second;			
			board[r][c] = '#';
			Trie* sub_MTree = m_Tree.getTrie(tmp_c);
			findNextAdjancent(board, r, c, sub_MTree, ret);
			board[r][c] = tmp_c;
			itor++;
		}

		MTree_itor++;
	}

	return ret;
}

// pre-processing words into a M-Tree, so when we find aaaaaB, we don't have to search whole word of aaaaaC
void testfindWords()
{
	//vector<vector<char>> board({ { 'o', 'a', 'a', 'n' }, { 'e','t','a','e' }, { 'i','h','k','r' }, { 'i','f','l','v' } });
	//vector<string> words({ "oath", "pea", "eat", "rain" });

	//vector<vector<char>> board({ {'a','b','c'},
	//							 {'a','e','d'},
	//							 {'a','f','g'}
	//						    });
	//vector<string> words({ "eaafgdcba","eaabcdgfa",});

	//vector<vector<char>> board({ {'a', 'a'}, {'a', 'a'} });
	//vector<string> words({ "aaaa", });

	vector<vector<char>> board({ { 'o', 'a', 'b', 'n' }, { 'o','t','a','e' }, { 'a','h','k','r' }, { 'a','f','l','v' } });
	vector<string> words({ "oa", "oaa" });

	findWords(board, words);
}

//https://leetcode.com/problems/kth-largest-element-in-an-array/
int findKthLargest(vector<int>& nums, int k) 
{
	priority_queue<int, vector<int>, greater<int>> pq;
	int i = 0;
	for (; i < k; i++)
	{
		pq.push(nums[i]);
	}

	for (; i < nums.size(); i++)
	{
		pq.push(nums[i]);
		if (pq.size() > k)
			pq.pop();
	}

	int kth = pq.top();

	return kth;
}
void testfindKthLargest()
{
	vector<int> nums({ 3,2,3,1,2,4,5,5,6 });
	findKthLargest(nums, 4);
}

//https://leetcode.com/problems/invert-binary-tree/description/
TreeNode* invertTree(TreeNode* root) 
{
	if (root == NULL)
		return root;

	TreeNode* ptmp = root->left;
	root->left = root->right;
	root->right = ptmp;
	
	if (root->left)
		invertTree(root->left);

	if (root->right)
		invertTree(root->right);
	return root;
}
void testinvertTree()
{
	vector<int> v1({ 4,2,7,1,3,6,9 });
	TreeNode** t1 = createTree(v1);
	invertTree(*t1);
}

//https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/
bool kthSmallest_helper(TreeNode* root, int k, int &current, int &val) 
{
	if (root == NULL)
		return false;

	bool bFound = false;
	if (root->left)
		bFound = kthSmallest_helper(root->left, k, current, val);

	if (bFound)
		return bFound;

	current++;
	if (current == k)
	{
		val = root->val;
		return true;
	}

	if (root->right)
		bFound = kthSmallest_helper(root->right, k, current, val);

	return bFound;
}

int kthSmallest(TreeNode* root, int k) {
	int val = 0;

	int current = 0;
	kthSmallest_helper(root, k, current, val);

	return val;
}

void testkthSmallest()
{
	vector<int> v1({ 5,3,6,2,4,INT_MIN,INT_MIN,1 });
	TreeNode** t1 = createTree(v1);
	kthSmallest(*t1, 3);
}

//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
bool getPathToNode(TreeNode* root, TreeNode* node, list<TreeNode *>& pathToNode)
{
	if (root == NULL)
		return false;

	pathToNode.push_back(root);
	if (root->val == node->val)
		return true;

	bool bFound = false;
	if (root->left)
		bFound = getPathToNode(root->left, node, pathToNode);

	if (!bFound && root->right)
		bFound = getPathToNode(root->right, node, pathToNode);

	if (!bFound)
		pathToNode.pop_back();

	return bFound;
}

TreeNode* lowestCommonAncestor_slow(TreeNode* root, TreeNode* p, TreeNode* q) 
{
	if (root == NULL || p == NULL || q == NULL)
		return NULL;

	list<TreeNode*> pathToP, pathToQ;

	if (!getPathToNode(root, p, pathToP))
		return NULL;

	if (!getPathToNode(root, q, pathToQ))
		return NULL;

	list<TreeNode*>::reverse_iterator itor_q(pathToQ.rbegin()), itor_p(pathToP.rbegin());
	if (pathToQ.size() > pathToP.size())
	{
		int steps = pathToQ.size() - pathToP.size();
		for (int i = 0; i < steps; i++, itor_q++);
	}
	else
	{
		int steps = pathToP.size() - pathToQ.size();
		for (int i = 0; i < steps; i++, itor_p++);
	}

	while (itor_p != pathToP.rend() && itor_q != pathToQ.rend())
	{
		if (*itor_p == *itor_q)
			return *itor_p;

		itor_p++;
		itor_q++;
	}

	return NULL;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
	if (!root) {
		return nullptr;
	}

	if (root->val > p->val && root->val > q->val) {
		TreeNode* leftTree = lowestCommonAncestor(root->left, p, q);
		if (leftTree) {
			return leftTree;
		}
	}
	if (root->val < p->val && root->val < q->val) {
		TreeNode* rightTree = lowestCommonAncestor(root->right, p, q);
		if (rightTree) {
			return rightTree;
		}
	}
	return root;
}

TreeNode* lowestCommonAncestor_level(TreeNode* root, TreeNode* p, TreeNode* q)
{
	int small = min(p->val, q->val);
	int large = max(p->val, q->val);
	while (root != nullptr) {
		if (root->val > large) // p, q belong to the left subtree
			root = root->left;
		else if (root->val < small) // p, q belong to the right subtree
			root = root->right;
		else // Now, small <= root.val <= large -> This root is the LCA between p and q
			return root;
	}
	return nullptr;
}

void testlowestCommonAncestor()
{
	vector<int> v1({ 6, 2, 8, 0, 4, 7, 9, INT_MIN, INT_MIN, 3, 5 });
	TreeNode** t1 = createTree(v1);

	TreeNode p(2), q(4);

	lowestCommonAncestor(*t1, &p, &q);
}

//https://leetcode.com/problems/product-of-array-except-self/
vector<int> productExceptSelf_ok(vector<int>& nums)
{	
	int zeroPos = -1;
	int i = 0;
	vector<int> ret(nums.size(), 0);
	
	for (; i < nums.size(); i++)
	{
		if (nums[i] == 0)
		{
			if (zeroPos == -1)
				zeroPos = i;
			else
				return ret;
		}
	}

	int product = 0;
	for (i = 0; i < nums.size(); i++)
	{
		if (nums[i] == 0)
			continue;

		if (product == 0)
			product = nums[i];
		else
			product *= nums[i];
	}

	for (; i < nums.size(); i++)
	{
	}

	return ret;

}

vector<int> productExceptSelf(vector<int>& nums) {
	vector<int> output(nums.size(), 1);

	int left = 1;
	for (int i = 0; i < nums.size(); i++) {
		output[i] *= left;
		left *= nums[i];
	}

	int right = 1;
	for (int i = nums.size() - 1; i >= 0; i--) {
		output[i] *= right;
		right *= nums[i];
	}

	return output;
}

void testproductExceptSelf()
{
	vector<int> nums({ 1,2,3,4 });

	productExceptSelf(nums);
}

//https://leetcode.com/problems/sliding-window-maximum/description/
int getMaxIdxFromK(vector<int>& nums, int i, int k)
{
	int maxIdx = i;
	for (int j = i+1; j < i + k; j++)
	{
		if (nums[maxIdx] <= nums[j])
			maxIdx = j;
	}

	return maxIdx;
}
vector<int> maxSlidingWindow_slow(vector<int>& nums, int k) 
{
	vector<int> ret(nums.size()-k+1);
	int maxIdx = getMaxIdxFromK(nums, 0, k);
	ret[0] = nums[maxIdx];
	int i = 1;
	while (i <= nums.size()-k)
	{
		if (maxIdx >= i && maxIdx < i + k)
		{
			if (nums[maxIdx] <= nums[i + k - 1])
			{
				maxIdx = i + k - 1;				
			}
		}
		else
		{
			maxIdx = getMaxIdxFromK(nums, i, k);
		}
		ret[i] = nums[maxIdx];
		i++;
	}

	return ret;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k) 
{
	deque<int> dq;
	vector<int> ans;
	for (int i = 0; i < nums.size(); i++) 
	{
		if (!dq.empty() && dq.front() == i - k) 
			dq.pop_front();

		while (!dq.empty() && nums[dq.back()] < nums[i])
			dq.pop_back();

		dq.push_back(i);
		if (i >= k - 1) 
			ans.push_back(nums[dq.front()]);
	}
	return ans;
}

void testmaxSlidingWindow()
{
	vector<int> nums({ 1,3,-1,-3,5,3,6,7 });
	int k = 3;

	maxSlidingWindow(nums, k);
}

//https://leetcode.com/problems/find-the-duplicate-number/description/

int findDuplicate(std::vector<int>& nums) 
{
	int bits = nums.size() - 1;
	int totalBytes = bits / 32 + 1;
	int *totalBytesArr = new int[totalBytes];
	memset(totalBytesArr, 0, totalBytes * sizeof(int));
	for (int i = 0; i < nums.size(); i++)
	{
		int byteIdx = nums[i] / 32;
		int bitIdx = nums[i] % 32;
		if ((totalBytesArr[byteIdx] & (1 << bitIdx)) != 0)
		{
			delete[] totalBytesArr;
			return nums[i];
		}

		totalBytesArr[byteIdx] |= 1 << bitIdx;
	}

	delete[] totalBytesArr;

	return 0;
}

void testfindDuplicate()
{
	vector<int> nums({ 3,3,3,3,4 });
	findDuplicate(nums);
}

//https://leetcode.com/problems/word-pattern/description/
bool wordPattern(string& pattern, string& s) 
{
	bool ret = false;
	vector<string> words;
	std::stringstream ss(s);
	std::string token;

	while (ss >> token) {
		words.push_back(token);
	}

	if (words.size() != pattern.size())
		return false;

	unordered_map<char, string> p_s;
	unordered_map<string, char> s_p;
	for (int i = 0; i < words.size(); i++)
	{
		if (p_s.find(pattern[i]) == p_s.end())
		{
			if (s_p.find(words[i]) == s_p.end())
			{
				p_s[pattern[i]] = words[i];
				s_p[words[i]] = pattern[i];
			}
			else
				return false;
		}
		else
		{
			if (p_s[pattern[i]].compare(words[i]) != 0)
				return false;			
		}
	}

	return true;
}

void testwordPattern()
{
	string p("abba"), s("dog dog dog dog");
	wordPattern(p, s);
}

//https://leetcode.com/problems/longest-increasing-subsequence/description/
int lengthOfLIS_slow(vector<int>& nums) 
{
	int ret = 0;
	int i = 0, j = 0, k = 0;
	
	vector<vector<int> > seqs;
	seqs.push_back(vector<int>());
	seqs[0].push_back(nums[0]);
	
	for (i = 1; i < nums.size(); i++)
	{
		bool bNeedNewSeq = true;
		
		for (j = 0; j < seqs.size(); j++)
		{
			if (seqs[j].back() < nums[i])
			{
				seqs[j].push_back(nums[i]);
				bNeedNewSeq = false;
			}
		}

		if (!bNeedNewSeq)
			continue;

		bNeedNewSeq = true;
		int seqsSize = seqs.size();
		for (j = 0; j < seqsSize; j++)
		{
			if (nums[i] <= seqs[j][0])
				continue;

			int l = 0, r = seqs[j].size() - 1;
			int m = 0;

			// 2 4 6 8 10 11
			while (l <= r)
			{
				m = (l + r) / 2;
				if (seqs[j][m] == nums[i])
				{
					break;
				}

				if (seqs[j][m] > nums[i])
					r = m - 1;
				else
					l = m + 1;
			}

			if (seqs[j][m] != nums[i])
			{
				int copyLen = m;
				if (seqs[j][m] < nums[i])
					copyLen++;
				vector<int> newSeq(seqs[j].begin(), seqs[j].begin() + copyLen);
				newSeq.push_back(nums[i]);
				seqs.push_back(newSeq);
				bNeedNewSeq = false;
			}
		}

		if (bNeedNewSeq)
		{
			vector<int> newSeq({nums[i]});			
			seqs.push_back(newSeq);
		}
	}

	int maxLen = seqs[0].size();
	for (k = 1; k < seqs.size(); k++)
	{
		if (maxLen < seqs[k].size())
			maxLen = seqs[k].size();
	}

	return maxLen;
}

int lengthOfLIS(vector<int>& nums)
{
	int ret = 0;
	int i = 0, j = 0, k = 0;

	vector<int> seq;	
	seq.push_back(nums[0]);
	for (i = 1; i < nums.size(); i++)
	{
		if (nums[i] > seq.back())
		{
			seq.push_back(nums[i]);
		}
		else //if (nums[i] < seq.back())
		{
			// lower_bound, 返回第一个 >= val 的索引。 
			// upper_bound, 返回第一个 大于 (>) 指定值的元素的迭代器
			//https://www.cnblogs.com/fnlingnzb-learner/p/5845438.html
			auto it = lower_bound(seq.begin(), seq.end(), nums[i]);			
//			*it = nums[i];
			
			// 2 4 6 8 10 11
			int l = 0, len = seq.size();
			int half = 0;
			int m = 0;
			while (len > 0)
			{
				half = len / 2;
				m = l + half;
				if (seq[m] < nums[i])
				{
					l = m + 1;
					len = len - half - 1;
				}
				else
				{
					len = half;
				}
			}

			seq[l] = nums[i];
			
		}
	}
	return seq.size();
}

void testlengthOfLIS()
{
//	vector<int> nums({ -813,82,-728,-82,-432,887,-551,324,-315,306,-164,-499,-873,-613,932,177,61,52,1000,-710,372,-306,-584,-332,-500,407,399,-648,290,-866,222,562,993,-338,-590,303,-16,-134,226,-648,909,582,177,899,-343,55,629,248,333,1,-921,143,629,981,-435,681,844,349,613,457,797,695,485,15,710,-450,-775,961,-445,-905,466,942,995,-289,-397,434,-14,34,-903,314,862,-441,507,-966,525,624,-706,39,152,536,874,-364,747,-35,446,-608,-554,-411,987,-354,-700,-34,395,-977,544,-330,596,335,-612,28,586,228,-664,-841,-999,-100,-620,718,489,346,450,772,941,952,-560,58,999,-879,396,-101,897,-1000,-566,-296,-555,938,941,475,-260,-52,193,379,866,226,-611,-177,507,910,-594,-856,156,71,-946,-660,-716,-295,-927,148,620,201,706,570,-659,174,637,-293,736,-735,377,-687,-962,768,430,576,160,577,-329,175,51,699,-113,950,-364,383,5,748,-250,-644,-576,-227,603,832,-483,-237,235,893,-336,452,-526,372,-418,356,325,-180,134,-698 });
	//vector<int> nums({ 10, 9, 2, 5, 3, 7, 101, 18 });
	
	vector<int> nums({ 3,5,6,2,5,4,19,5,6,7,12 });
	// 356  256  246  246 19  245 19 2456 2456712
	// 256
	// 456
	// 456 19 
	// 

	lengthOfLIS(nums);
}

// https://leetcode.com/problems/remove-duplicate-letters/
string removeDuplicateLetters(string s) {
	std::unordered_map<char, int> lastOccurrence;
	for (int i = 0; i < s.length(); i++) {
		lastOccurrence[s[i]] = i;
	}

	std::stack<char> stack;
	std::unordered_set<char> visited;

	for (int i = 0; i < s.length(); i++) {
		if (visited.find(s[i]) != visited.end()) {
			continue;
		}

		while (!stack.empty() && s[i] < stack.top() && i < lastOccurrence[stack.top()]) {
			visited.erase(stack.top());
			stack.pop();
		}

		visited.insert(s[i]);
		stack.push(s[i]);
	}

	std::string result;
	while (!stack.empty()) {
		result = stack.top() + result;
		stack.pop();
	}
	return result;
}

void removeDuplicateLettersTest()
{
	string s("cbacdcbc");

	removeDuplicateLetters(s);
}
//https://leetcode.com/problems/range-sum-query-mutable/description/
//https://blog.csdn.net/yuzhiqiang666/article/details/80643017 segment tree
class NumArray {
private:
	vector<int> nums;
	unordered_map<int, unordered_map<int, int>> numSum;
	vector<int> totalSum;
	
	int minUpdateIdx;
public:
	NumArray(vector<int>& nums) {
		this->nums.assign(nums.begin(), nums.end());
		totalSum.resize(nums.size());
		
		totalSum[0] = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			totalSum[i] = nums[i] + totalSum[i - 1];
		}
	}
	void update(int index, int val) 
	{
		minUpdateIdx = INT_MAX;
		nums[index] = val;
		if (index < minUpdateIdx)
			minUpdateIdx = index;
	}

	int sumRange(int left, int right)
	{
		if (left >= minUpdateIdx || (left < minUpdateIdx && right >= minUpdateIdx))
		{
			if (minUpdateIdx == 0)
			{
				totalSum[0] = nums[0];
				minUpdateIdx = 1;
			}
			for (int i = minUpdateIdx; i < nums.size(); i++)
			{
				totalSum[i] = totalSum[i - 1] + nums[i];
			}

			minUpdateIdx = INT_MAX;
		}

		if (left == 0)
			return totalSum[right];

		return totalSum[right] - totalSum[left - 1];
	}
	/*
	void update(int index, int val) {
		// 1 2 3 4 5
		// 1 3 6 10 15
		// 1 1 3 4 5
		nums[index] = val;
		updateIdx[index] = true;
	}

	int sumRange(int left, int right) {
		bool bupdate = false;
		int i = left;
		for (int i = left; i <= right; i++)
		{
			if (updateIdx[i])
			{
				bupdate = true;
				break;				
			}
		}
		if (bupdate)
		{
			if (i == 0)
			{
				totalSum[0] = nums[0];
				i = 1;
				updateIdx[0] = false;
			}

			for (int j = i; j <= right; j++)
			{
				totalSum[j] = totalSum[j - 1] + nums[j];
				updateIdx[j] = false;
			}
		}

		if (left == 0)
			return totalSum[right];

		return totalSum[right] - totalSum[left - 1];
	}
	*/
};
void testNumArray()
{
	vector<int> nums({ 1,3,5 });
	NumArray n(nums);
	n.update(1, 2);
	n.sumRange(0, 2);
}

//https://leetcode.com/problems/rectangle-area/description/
int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) 
{
	int area = (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1);
	if (ax2 <= bx1 || ax1 >= bx2 || ay1 >= by2 || ay2 <= by1) // no overlap
		return area;

	int overlap = (min(ax2, bx2) - max(ax1, bx1)) * (min(ay2, by2) - max(ay1, by1));	

	return area -overlap;
}

void testcomputeArea()
{
	//int ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2;
	int ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = 3, by1 = 3, bx2 = 4, by2 = 4;
	computeArea(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);
}

//https://leetcode.com/problems/odd-even-linked-list/description/
ListNode* oddEvenList(ListNode* head)
{
	if (head == NULL || head->next == NULL || head->next->next == NULL)
		return head;

	ListNode* oddhead = head, * evenhead = head->next;
	ListNode* oddtmp = head, *eventmp = head->next;
	while (eventmp != NULL && eventmp->next != NULL)
	{
		oddtmp->next   = eventmp->next;
		oddtmp = eventmp->next;

		eventmp->next = oddtmp->next;
		eventmp = oddtmp->next;
	}

	oddtmp->next = evenhead;

	return oddhead;
}
void testoddEvenList()
{
	vector<int> nums({ 1,2,3,4, 5 });

	ListNode* head = createListNode(nums);
	oddEvenList(head);
}

//https://leetcode.com/problems/flatten-nested-list-iterator/description/

  // This is the interface that allows for creating nested lists.
  // You should not implement it, or speculate about its implementation
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const { return true; };
 
    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
	int getInteger() const { return 0; };
 
    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
	const vector<NestedInteger>& getList() const
	{
		vector<NestedInteger>  a;
		return a;
	}
};

class NestedIterator {
public:
	vector<int> flattenedInt;
	int mCurIdx;

	NestedIterator(vector<NestedInteger>& nestedList) 
	{
		mCurIdx = 0;
		spreadNestdInt(nestedList);
	}

	void spreadNestdInt(const vector<NestedInteger>& nestedList)
	{
		for (int i = 0; i < nestedList.size(); i++)
		{
			if (nestedList[i].isInteger())
			{
				flattenedInt.push_back(nestedList[i].getInteger());
			}
			else
			{
				spreadNestdInt(nestedList[i].getList());
			}
		}
	}

	int next() {
		int tmp = flattenedInt[mCurIdx];
		mCurIdx++;
		return tmp;
	}

	bool hasNext() {
		return mCurIdx < flattenedInt.size();
	}
};
//https://leetcode.com/problems/increasing-triplet-subsequence/description/
bool findLarger(vector<int>& nums, int anchor, int start, int &larger)
{
	for (int i = start; i < nums.size(); i++)
	{
		if (nums[i] > nums[anchor])
		{
			larger = i;
			return true;
		}
	}

	return false;
}

bool increasingTriplet_slow(vector<int>& nums) 
{
	if (nums.size() < 3)
		return false;

	int i = 0;
	int next_i = 0;
	while (i < nums.size() - 2)
	{
		int j = i + 1;
		int next_j = 0;
		while (j < nums.size() -1)
		{
			if (nums[j] > nums[i])
			{
				for (int k = j + 1; k < nums.size(); k++)
				{
					if (nums[k] > nums[j])
						return true;
					
					if (nums[k] > nums[i])
						next_j = k;
				}
			}

			if (next_i == nums.size() - 1)
				break;
			if (next_j != 0)
			{
				j = next_j;
				next_j = 0;
			}
			else
			{
				j++;
			}
		}
		i++;

		//if (next_i != 0)
		//{
		//	i = next_i;
		//	next_i = 0;
		//	printf("next_i %d\n", next_i);
		//}
		//else
		//{
		//	i++;
		//}
	}

	return false;
}

bool increasingTriplet(vector<int>& nums) 
{
	int first = INT_MAX, second = INT_MAX;
	for (int n : nums) {
		if (n <= first) 
			first = n;
		else if (n <= second) 
			second = n;
		else
			return true;
	}
	return false;
}

void tesstincreasingTriplet()
{
	//vector<int> nums({ 20,100,10,12,5,13 });
	vector<int> nums({ 5, 6, 3, 8, 2, 7, 8 });
	
	increasingTriplet(nums);
}

//https://leetcode.com/problems/power-of-four/description/
bool isPowerOfFour(int n) 
{
	vector<unsigned int> mask;
	for (int i = 0; i < 32; i += 2)
		mask.push_back(1 << i);

	for (int i = 0; i < mask.size(); i++)
	{
		if ((n & mask[i]) == mask[i] && (n& (~mask[i])) == 0)
			return true;
	}

	return false;
}

void testisPowerOfFour()
{
	isPowerOfFour(5);
}

//https://leetcode.com/problems/integer-break/description/
int sMaxProd = 1;
unordered_map<int, int> sKnownMaxProd;
int getProd(int n, int maxProd)
{
	if (sKnownMaxProd.find(n) != sKnownMaxProd.end())
	{
		if (maxProd * sKnownMaxProd[n] > sMaxProd)		
			sMaxProd = maxProd * sKnownMaxProd[n];

		if (maxProd * n > sMaxProd)
			sMaxProd = maxProd * n;

		return sMaxProd;
	}

	int maxProdOfN = 0;

	if (maxProd > sMaxProd)
		sMaxProd = maxProd;
	
	for (int i = 2; i <= n; i++)
	{
		int tmp = getProd(n - i, maxProd * i);
		if (tmp > maxProdOfN)
			maxProdOfN = tmp;
	}

	sKnownMaxProd[n] = maxProdOfN;

	return maxProdOfN;
}

int integerBreak(int n) 
{
	sKnownMaxProd[2] = 1;
	sKnownMaxProd[3] = 2;
	sKnownMaxProd[4] = 4;
	sKnownMaxProd[5] = 6;
	sKnownMaxProd[6] = 9;
	if (sKnownMaxProd.find(n) != sKnownMaxProd.end())
		return sKnownMaxProd[n];

	int prod = 1;
	for (int i = 7; i <= n; i++)
		getProd(i, prod);

	return sMaxProd;
}

void testintegerBreak()
{
	integerBreak(8);
}

//https://leetcode.com/problems/reverse-vowels-of-a-string/description/
bool isVowles(char c)
{
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

string reverseVowels(string s) {
	if (s.size() == 0)
		return s;

	vector<int> vowleIdx;
	int i = 0;
	for (i = 0; i < s.size(); i++)
	{
		if (isVowles(s[i]))
			vowleIdx.push_back(i);
	}
	if (vowleIdx.size() < 2)
		return s;

	for (i = 0; i < vowleIdx.size()/2; i++)
	{
		std::swap(s[vowleIdx[i]], s[vowleIdx[vowleIdx.size()-1-i]]);
	}

	return s;
}

void testreverseVowels()
{
	string s("IceCreAm");
	reverseVowels(s);
}

//https://leetcode.com/problems/largest-divisible-subset/description/
vector<int> largestDivisibleSubset(vector<int>& nums) 
{
	if (nums.size() == 1)
		return nums;

	std::sort(nums.begin(), nums.end());
	unordered_map<int, vector<int>> candidates;	
	vector<int> ret;
	int i = 0, j = 0;

	candidates[nums[nums.size() - 1]] = vector<int>({ nums[nums.size() - 1] });
	for (i = nums.size() - 2; i >= 0; i--)
	{
		bool found = false;
		vector<int> newcandidate({ nums[i] });
		unordered_map<int, vector<int>>::iterator itor(candidates.begin());

		while (itor != candidates.end())
		{
			if (itor->first % nums[i] == 0 && itor->second.size() + 1 > newcandidate.size())
			{
				vector<int> tmp({ nums[i]});
				tmp.insert(tmp.end(), itor->second.begin(), itor->second.end());
				newcandidate.assign(tmp.begin(), tmp.end());
			}
			itor++;
		}
		candidates[nums[i]] = newcandidate;
		if (ret.size() < newcandidate.size())
			ret.assign(newcandidate.begin(), newcandidate.end());
	}

	return ret;
}

void testlargestDivisibleSubset()
{
	// 5 9 18 54 90 108 180 360 540 720 1080
	// 1080
	// 720
	// 540
	// 360 1080
	// 180 360 1080
	// 108 540
	// 90 180 360 1080
	// 54 540
	// 54 108 540
	// 18 720
	// 18 540
	// 18 360 720
	// 18 180 360 720
	// 18 180 540
	// ...
	// 18 90 180 360 720
	// 
	// 
	//

	vector<int> nums({ 5,9,18,54,108,540,90,180,360,720 }); //9,18,90,180,360,720
	largestDivisibleSubset(nums);
}

//https://leetcode.com/problems/count-numbers-with-unique-digits/description/
int getUniqueDigits(int n, set<int> digitsUsed)
{
	int digits = 0;
	for (int i = 0; i <= 9; i++)
	{
		if (digitsUsed.find(i) == digitsUsed.end())
		{
			if (n == 1)
			{
				digits++;
			}
			else
			{
				set<int> digitsUsed_tmp(digitsUsed);
				digitsUsed_tmp.insert(i);
				digits += getUniqueDigits(n - 1, digitsUsed_tmp);
			}
		}
	}

	return digits;
}

int countNumbersWithUniqueDigits(int n) 
{
	int ret = 0;
	if (n == 0)
		return 1;

	if (n == 1)
		return 10;

	for (int i = 1; i <= 9; i++)
	{
		set<int> digitsUsed;
		digitsUsed.insert(i);
		ret += getUniqueDigits(n - 1, digitsUsed);
	}

	return ret + 10; // 10 means 0 to 9
}

void testcountNumbersWithUniqueDigits()
{
	countNumbersWithUniqueDigits(3);
}

//https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
static bool largersum(const vector<int>& a, const vector<int>& b)
{
	return a[0] > b[0];
}


//vector<int> n1({ -10,-4, 0, 0, 6 });
//vector<int> n2({ 3,  5,  6, 7, 8,100 });
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,int k)
{
	priority_queue<vector<int>, vector<vector<int>>, bool(*)(const vector<int>& a, const vector<int>& b)> lesssumvectors(largersum);
	vector<vector<int>> ret;
	for (int i = 0; i < nums1.size(); i++)
	{
		lesssumvectors.push({ nums1[i] + nums2[0], 0 });
	}

	while (k > 0 && !lesssumvectors.empty())
	{
		vector<int> tmp(lesssumvectors.top());
		int sum = tmp[0];
		int pos = tmp[1];
		lesssumvectors.pop();
		ret.push_back({sum - nums2[pos], nums2[pos]});
		if (pos + 1 < nums2.size())
		{
			lesssumvectors.push({ sum - nums2[pos] + nums2[pos + 1], pos + 1 });
		}

		k--;
	}

	return ret;
}


void testkSmallestPairs()
{
	vector<int> n1({1,7,11});
	vector<int> n2({ 2,4,6 });
	kSmallestPairs(n1, n2, 10);
}

//https://leetcode.com/problems/build-array-from-permutation
vector<int> buildArray(vector<int>& nums) 
{
	vector<int> ret(nums.size(), 0);
	for (int i = 0; i < nums.size(); i++)
	{
		ret[i] = nums[nums[i]];
	}

	return ret;
}

void testbuildArray()
{
	vector<int> nums({ 0,2,1,5,3,4 });

	buildArray(nums);
}

//https://leetcode.com/problems/first-unique-character-in-a-string/description/
int firstUniqChar(string& s) 
{
	int bUnique[26] = { -1 };
	memset(bUnique, -1, sizeof(bUnique));
	int i = 0;
	for (i = 0; i < s.size(); i++)
	{
		bUnique[s[i] - 'a']++;
	}

	for (i = 0; i < s.size(); i++)
	{
		if (bUnique[s[i] - 'a'] == 0)
			return i;
	}

	return -1;
}

void testfirstUniqChar()
{
	string s("leetcode");
	firstUniqChar(s);
}

//https://leetcode.com/problems/longest-absolute-file-path/description/
class PathTreeNode
{
public:
	PathTreeNode* parent;
	vector<PathTreeNode*> child;
	vector<string> files;
	string foldername;
	int curLevel;
};

int getCurLevel(string& input, int idx)
{
	int i = idx;
	int curLevel = 0;
	while (i < input.size() && input[i] == '\t')
	{
		i++;
		curLevel++;
	}

	return curLevel;
}

int getSplitPos(string& input, int idx)
{
	int i = idx;
	while (i < input.size())
	{
		if (input[i] == '\n')
		{
			break;
		}
		i++;
	}

	return i;
}

void splitPath(string& input, int idx, PathTreeNode *root)
{
	int curLevel = getCurLevel(input, idx+1);
	if (curLevel == root->curLevel + 1)
	{
		int i = curLevel + idx + 1;
		int namestart = i;

		i = getSplitPos(input, i);
		if (i > input.size())
			return;

		string filename(input.substr(namestart, i - namestart));
		if (filename.find('.') != string::npos)
		{
			root->files.push_back(filename);
			splitPath(input, i, root);
		}
		else
		{
			PathTreeNode* treeNode = new PathTreeNode();
			treeNode->parent = root;
			treeNode->foldername = filename;
			treeNode->curLevel = curLevel;
			root->child.push_back(treeNode);
			splitPath(input, i, treeNode);
		}
	}
	else
	{
		int i = curLevel + idx + 1;
		int namestart = i;
		i = getSplitPos(input, i);
		if (i > input.size())
			return;

		while (root != NULL && root->curLevel >= curLevel)
		{
			root = root->parent;
		}

		if (root != NULL)
		{
			string filename(input.substr(namestart, i - namestart));
			if (filename.find('.') != string::npos)
			{
				root->files.push_back(filename);
				splitPath(input, i, root);
			}
			else
			{
				PathTreeNode* treeNode = new PathTreeNode();
				treeNode->parent = root;
				treeNode->foldername = filename;
				treeNode->curLevel = curLevel;
				root->child.push_back(treeNode);
				splitPath(input, i, treeNode);
			}
		}
	}
}

int getLongestPath(PathTreeNode *rootfolder, int curLen)
{
	if (rootfolder == NULL)
		return 0;

	int maxfilenamelen = 0, i = 0;
	for (i = 0; i < rootfolder->files.size(); i++)
	{
		if (rootfolder->files[i].size() > maxfilenamelen)
			maxfilenamelen = rootfolder->files[i].size();
	}

	int maxfilenamelenonsub = 0;
	for (i = 0; i < rootfolder->child.size(); i++)
	{
		int tmp = 0;
		tmp = getLongestPath(rootfolder->child[i], curLen + 1 + rootfolder->foldername.size());

		if (tmp > maxfilenamelenonsub)
			maxfilenamelenonsub = tmp;
	}
	if (maxfilenamelen == 0)
		return maxfilenamelenonsub;

	if (curLen + rootfolder->foldername.size() + 1 + maxfilenamelen > maxfilenamelenonsub)
		return curLen + rootfolder->foldername.size() + 1 + maxfilenamelen;
	else
		return maxfilenamelenonsub;
}

int lengthLongestPath(string& input) 
{
	string curPath;
	int maxLen = 0;
	PathTreeNode rootfolder;

	int i = getSplitPos(input, 0);
	if (i >= input.size())
	{
		if (input.find('.') == std::string::npos)
			return 0;
		else
			return input.size();
	}

	string curname(input.substr(0, i));
	rootfolder.curLevel = -1;
	rootfolder.foldername = "/";
	if (curname.find('.') == std::string::npos)
	{
		PathTreeNode* childnode = new PathTreeNode();
		childnode->parent = &rootfolder;
		childnode->foldername = curname;
		childnode->curLevel = 0;

		rootfolder.child.push_back(childnode);
		splitPath(input, i, childnode);
	}
	else
	{
		rootfolder.files.push_back(curname);
		splitPath(input, i, &rootfolder);
	}

	for (i = 0; i < rootfolder.files.size(); i++)
	{
		if (maxLen < rootfolder.files[i].size())
			maxLen = rootfolder.files[i].size();
	}

	for (int i = 0; i < rootfolder.child.size(); i++)
	{
		int tmp = getLongestPath(rootfolder.child[i], 0);
		if (maxLen < tmp)
			maxLen = tmp;
	}

	return maxLen;
}

void testlengthLongestPath()
{
	//string s("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
	//string s("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");
	string s("skd\n\talskjv\n\t\tlskjf\n\t\t\tklsj.slkj\n\t\tsdlfkj.sdlkjf\n\t\tslkdjf.sdfkj\n\tsldkjf\n\t\tlskdjf\n\t\t\tslkdjf.sldkjf\n\t\t\tslkjf\n\t\t\tsfdklj\n\t\t\tlskjdflk.sdkflj\n\t\t\tsdlkjfl\n\t\t\t\tlskdjf\n\t\t\t\t\tlskdjf.sdlkfj\n\t\t\t\t\tlsdkjf\n\t\t\t\t\t\tsldkfjl.sdlfkj\n\t\t\t\tsldfjlkjd\n\t\t\tsdlfjlk\n\t\t\tlsdkjf\n\t\tlsdkjfl\n\tskdjfl\n\t\tsladkfjlj\n\t\tlskjdflkjsdlfjsldjfljslkjlkjslkjslfjlskjgldfjlkfdjbljdbkjdlkjkasljfklasjdfkljaklwejrkljewkljfslkjflksjfvsafjlgjfljgklsdf.a");
	//string s("file1.txt");
	//string s("a\n\tb\n\t\tc\n\t\t\td\n\t\t\t\te.txt\n\t\t\t\talsdkjf.txt\n\t\tskdjfl.txtlsdkjflsdjflsajdflkjasklfjkasljfklas\n\tlskdjflkajsflj.txt");
	lengthLongestPath(s);
}

//https://leetcode.com/problems/guess-number-higher-or-lower/description/
int guess(int n)
{
	int pick = 9;

	if (n == pick)
		return 0;
	if (n > pick)
		return -1;

	return 1;
}

int guessNumber(int n) 
{
	int l = 1, r = n;
	int m = l + (r - l) / 2;
	
	int ret = guess(m);
	while (ret != 0)
	{
		if (ret == -1)
		{
			r = m-1;
		}			
		else if (ret == 1)
		{
			l = m + 1;
		}
		m = l + (r - l) / 2;
		ret = guess(m);
	}

	return m;		
}

void testguessNumber()
{
	guessNumber(100);
}

//https://leetcode.com/problems/wiggle-subsequence/
int findnext(vector<int>& nums, int idx, bool pos)
{
	for (int i = idx; i < nums.size(); i++)
	{
		if (pos)
		{
			if (nums[i] > 0)
				return i;
		}
		else
		{
			if (nums[i] < 0)
				return i;
		}
	}
	return -1;
}

int find1st(vector<int>& nums, bool pos)
{
	return findnext(nums, 0, pos);
}

int getmaxlen(vector<int>& wiggleseq, bool frompositive)
{
	int position = find1st(wiggleseq, frompositive);
	if (position == -1)
		return 0;

	bool nextpositive = !frompositive;
	int maxlen = 1;

	while (position != -1 && position < wiggleseq.size())
	{
		position = findnext(wiggleseq, position + 1, nextpositive);
		nextpositive = !nextpositive;
		if (position != -1)
			maxlen++;
	}

	if (maxlen > 1)
		return maxlen;

	return maxlen;
}

int allzerosinwiggle(vector<int>& wiggleseq)
{
	for (int i = 0; i < wiggleseq.size(); i++)
	{
		if (wiggleseq[i] != 0)
			return false;
	}

	return true;
}

int wiggleMaxLength(vector<int>& nums) 
{
	if (nums.size() <= 1)
		return nums.size();

	vector<int> wiggleseq(nums.size() - 1, 0);
	int ret = 0;
	int i = 0;
	bool positive = true;
	int wigglestart = -1, wiggleend = -1;
	int maxlen = 0;
	for (i = 1; i < nums.size(); i++)
	{
		wiggleseq[i-1] = nums[i] - nums[i - 1];
	}

	if (allzerosinwiggle(wiggleseq))
		return 1;

	int maxlenfrompos = getmaxlen(wiggleseq, true);
	int maxlenfromnag = getmaxlen(wiggleseq, false);

	if (maxlenfrompos != 0 || maxlenfromnag != 0)
		return max(maxlenfrompos, maxlenfromnag) + 1;

	return 0;
}

void testwiggleMaxLength()
{
	vector<int> nums({ 1,1,1 });
	wiggleMaxLength(nums);
}

//https://leetcode.com/problems/elimination-game/description/
// // 1 2 3 4 5 6 7 8 9 10 11 
// 
// 1 2 3 4 5 6 7 8 9 10 11 12
// 2 4 6 8 10 12
// 2 6 10
// 6
//
// 1 2 3 4 5 6 7 8 9 10 11 12 13 
// 2 4 6 8 10 12
// 2 6 10
// 6
//
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14
// 2 4 6 8 10 12 14
// 4 8 12
// 8
// 
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
// 2 4 6 8 10 12 14
// 8
//
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
// 2 4 6 8 10 12 14 16
// 2 6 10 14
// 6 14
// 6
// 
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
// 2 4 6 8 10 12 14 16 18
// 4 8 12 16
// 8 16
// 8
// 
int lastRemaining(int n)
{
	if (n == 1)
		return 1;

	int nextstart = 2;
	int nextend = n;
	if (n % 2 != 0)
		nextend = n - 1;
	int hop = 2;
	int nums = n / 2;
	bool ltor = false;
	while (nums != 1)
	{
		if (ltor)
		{
			nextstart += hop;
			if (nums % 2 != 0)
			{
				nextend -= hop;
			}
		}
		else
		{
			nextend -= hop;
			if (nums % 2 != 0)
			{
				nextstart += hop;
			}
		}
		ltor = (!ltor);
		hop *= 2;
		nums /= 2;
	}

	return nextstart;
}

int lastRemaining_oom(int n) 
{
	if (n == 1)
		return 1;

	vector<int> rem1(n/2, 0), rem2;
	int i = 0;
	for (i = 2; i <= n; i+=2)
	{
		rem1[(i>>1) -1] = i;
	}

	bool l2r = false;
	int hop = 2;
	vector<int> *premref = &rem1;
	while (premref->size() > 1)
	{
		if (l2r)
		{
			i = 1;
		}
		else
		{
			if (premref->size() % 2 == 0)
				i = 0;
			else
				i = 1;
		}

		for (; i < premref->size(); i += 2)
		{
			if (premref == &rem1)
			{
				rem2.push_back((*premref)[i]);
			}
			else
			{
				rem1.push_back((*premref)[i]);
			}
		}
		premref->clear();
		if (premref == &rem1)
		{	
			premref = &rem2;
		}
		else
		{
			premref = &rem1;
		}

		if (l2r)
			l2r = false;
		else
			l2r = true;
	}

	return (*premref)[0];
}

void testlastRemaining()
{
	lastRemaining(9);
}

//https://leetcode.com/problems/decode-string/description/

// 3[a3[a]]2[c]
int decompressString(string& str, int idx, string& ret);

void getrepeatstr(string& str, int& idx, string& ret)
{
	int i = idx;

	while (i >= 0 && i < str.size())
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			string repeatstr;
			i = decompressString(str, i, repeatstr);
			ret.append(repeatstr);
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			ret.push_back(str[i]);
			i++;
		}
		else
			break;
	}

	idx = i;
}
int findEndOfNum(string& str, int idx)
{
	if (!(str[idx] >= '1' && str[idx] <= '9'))
		return -1;

	int end = idx + 1;
	while (end < str.size() && str[end] >= '0' && str[end] <= '9')
	{
		end++;
	}

	return end;
}


int decompressString(string& str, int idx, string &ret)
{
	int numends = findEndOfNum(str, idx);
	string strnum(str.substr(idx, numends - idx));
	int repeatnum = atoi(strnum.c_str());

	string repeatstr;
	int repeatend = numends + 1;
	getrepeatstr(str, repeatend, repeatstr);

	for (int i = 0; i < repeatnum; i++)
		ret.append(repeatstr);

	return repeatend + 1;
}

string decodeString(string str) 
{
	string ret;
	int idx = 0;
	while (idx >= 0 && idx < str.size())
	{
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			idx = decompressString(str, idx, ret);
		}
		else if (str[idx] >= 'a' && str[idx] <= 'z')
		{
			ret.push_back(str[idx]);
			idx++;
		}
		else
			idx++;
	}

	return ret;
}

void testdecodeString()
{
	string s(" 3[a3[b]]2[c]ef");
	decodeString(s);
}

//https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
void getCharFreq(string& str, int *charFreq)
{
	int i = 0;	
	for (i = 0; i < str.size(); i++)
		charFreq[str[i] - 'a']++;
}

bool meetKChar(int *charFreq, int k)
{
	for (int i = 0; i < 26; i++)
		if (charFreq[i] > 0 && charFreq[i] < k)
			return false;

	return true;
}

int getLastSameIdx(string& str, int idx)
{
	int i = idx + 1;
	while (i < str.size())
	{
		if (str[i] != str[idx])
			return i - 1;

		i++;
	}
	
	return i - 1;
}

int longestSubstring(string& s, int k)
{
	if (s.size() < k)
		return 0;

	int charFreq[26] = { 0 };
	getCharFreq(s, charFreq);
	if (meetKChar(charFreq, k))
		return s.size();

	int ret = 0;
	int i = 0;
	for (i = 0; i <= s.size() - k; i++)
	{
		int j = i+k;
		int sublen = k;
		memset(charFreq, 0, sizeof(int) * 26);
		string substr(s.substr(i, j - i));
		getCharFreq(substr, charFreq);

		while (j < s.size())
		{
			if (meetKChar(charFreq, k))
			{
				if (ret < substr.size())
					ret = substr.size();
			}

			int next_j = getLastSameIdx(s, j);
			if (next_j == j)
			{
				substr.push_back(s[j]);
				charFreq[substr[substr.size() - 1] - 'a']++;
				j = next_j + 1;
			}
			else
			{	
				substr = s.substr(i, next_j - i + 1);
				charFreq[substr[substr.size() - 1] - 'a'] += next_j - j + 1;				
				j = next_j + 1;
			}
		}

		if (meetKChar(charFreq, k))
		{
			if (ret < substr.size())
				ret = substr.size();
		}
	}

	return ret;
}

int longestSubstring2(string &s, int k) 
{
	int charFreq[26] = { 0 };
	getCharFreq(s, charFreq);
	if (meetKChar(charFreq, k))
		return s.size();

	int ret = 0;
	int ks = 0, ke = k;
	int i = 0;
	for (i = 0; i < s.size() - k; i++)
	{
		memset(charFreq, 0, sizeof(int) * 26);
		string substr(s.substr(ks, ke - ks));
		getCharFreq(substr, charFreq);
		if (meetKChar(charFreq, k))
		{
			ke++;
			substr = s.substr(ks, ke - ks);
		}
	}

	return ret;
}

void testlongestSubstring()
{
	//string str("aaabb");
	string str("aaabbbcdefcdefcde");
	int k = 3;
	longestSubstring(str, k);
}

//https://leetcode.com/problems/rotate-function/description/
int maxRotateFunction(vector<int>& nums) 
{
	vector<int> rotateGains(nums.size(), 0);
	int sum = 0;	
	int ret = 0;
	int i = 0, rotate = 0;
	for (i = 0; i < nums.size(); i++)
		sum += nums[i];

	for (i = 1; i < nums.size(); i++)
		rotateGains[i] = sum - nums[nums.size() - i] * nums.size();

	for (i = 1; i < nums.size(); i++)
		ret += nums[i] * i;

	int rotateSum = ret;
	for (i = 1; i < nums.size(); i++)
	{
		rotateSum += rotateGains[i];
		if (rotateSum > ret)
			ret = rotateSum;
	}

	return ret;
}

/*
F(0) =  25
F(1) = 16
F(2) = 23
F(3) = 26
4 3 2 6
6 4 3 2
*/
void testmaxRotateFunction()
{
	vector<int> nums({4,3,2,6});
	maxRotateFunction(nums);
}

//https://leetcode.com/problems/nth-digit/description/
// 1: 9
// 2: 90*2
// 3: 900*3
// 4: 9000*4
//

// 100101102

int findNthDigit(int n) 
{
	if (n < 10)
		return n;

	int digitOfNum = 2;
	uint64_t digitsOfpowerOf10 = 9;
	uint64_t next_digitsOfpowerOf10 = 9 * pow(10, digitOfNum - 1) * digitOfNum;
	while (digitsOfpowerOf10 + next_digitsOfpowerOf10 <= n)
	{
		digitsOfpowerOf10 += next_digitsOfpowerOf10;
		digitOfNum++;
		next_digitsOfpowerOf10 = 9 * pow(10, digitOfNum - 1) * digitOfNum;
	}

	if (digitsOfpowerOf10 == n)
		return 0;

	uint64_t finalNum = pow(10, digitOfNum - 1) -1;
	while (digitsOfpowerOf10 + digitOfNum < n)
	{
		digitsOfpowerOf10 += digitOfNum;
		finalNum++;
	}
	
	finalNum++;
	
	int theleftdig = n - digitsOfpowerOf10;
	int finalDig = (finalNum / int(pow(10, digitOfNum - theleftdig))) % 10;

	return finalDig;
}

void testfindNthDigit()
{
	findNthDigit(1000000000);
}

//https://leetcode.com/problems/sum-of-left-leaves/
void getsumOfLeftLeaves(TreeNode* root, int &sum, bool leftleaf)
{
	if (root == NULL)
		return;

	if (root->left == NULL && root->right == NULL && leftleaf)
	{
		sum += root->val;
		return;
	}

	if (root->left)
	{
		getsumOfLeftLeaves(root->left, sum, true);
	}

	if (root->right)
	{
		getsumOfLeftLeaves(root->right, sum, false);
	}
}

int sumOfLeftLeaves(TreeNode* root) 
{
	if (root == NULL)
		return 0;

	int sum = 0;
	if (root->left != NULL)
		getsumOfLeftLeaves(root->left, sum, true);
	
	if (root->right)
		getsumOfLeftLeaves(root->right, sum, false);

	return sum;
}

void testsumOfLeftLeaves()
{
	vector<int> v1({1,2,3,4,5 });
	TreeNode** t1 = createTree(v1);

	sumOfLeftLeaves(*t1);

	deleteTree(t1, v1.size());
}


//https://leetcode.com/problems/longest-palindromic-substring/
int countPalindrome(string& s, int left, int right)
{
	while (left >= 0 && right < s.size() && s[left] == s[right])
	{
		left--;
		right++;
	}

	return (right-1) - (left+1) + 1;
}

string longestPalindrome(string& s)
{
	if (s.size() == 1)
		return s;

	int i = 0, j = 0;
	int maxs = 0, maxe = 0, maxlen = 0;
	for (i = 0; i <= s.size(); i++)
	{
		int oddlen = countPalindrome(s, i, i);
		int evenlen = countPalindrome(s, i, i+1);
		int tmps = 0, tmpe = 0;
		if (oddlen >= evenlen)
		{
			tmps = i - (oddlen / 2);
			tmpe = i + (oddlen / 2);
		}
		else
		{
			tmps = i - evenlen / 2 + 1;
			tmpe = (i + 1) + evenlen / 2 - 1;
		}

		if (tmpe - tmps +1 > maxlen)
		{
			maxlen = tmpe - tmps + 1;
			maxe = tmpe;
			maxs = tmps;
		}
		// 0 1 2 3 4 5
	}

	return s.substr(maxs, maxe - maxs + 1);
}

void longestPalindromeTest()
{
	string s("cbbd");
	longestPalindrome(s);
}

//https://leetcode.com/problems/longest-palindrome/description/
int longestPalindrome2(string& s) 
{
	int uppercount[26] = { 0 }, lowercount[26] = { 0 };
	int i = 0;
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			lowercount[s[i] - 'a']++;

		if (s[i] >= 'A' && s[i] <= 'Z')
			uppercount[s[i] - 'A']++;
	}

	int parlindromelen = 0;
	for (i = 0; i < 26; i++)
	{
		if (lowercount[i] >= 2)
		{
			if (lowercount[i] % 2 == 0)
				parlindromelen += lowercount[i];
			else
				parlindromelen += lowercount[i] - 1;
		}

		if (uppercount[i] >= 2)
		{
			if (uppercount[i] % 2 == 0)
				parlindromelen += uppercount[i];
			else
				parlindromelen += uppercount[i] - 1;
		}
	}

	if (parlindromelen < s.size())
		parlindromelen++;

	return parlindromelen;
}

void testlongestPalindrome2()
{
	string s("a");
	longestPalindrome2(s);
}

//https://leetcode.com/problems/arithmetic-slices/description/
int getArthSlice(vector<int>& nums, int start)
{
	if (start + 1 >= nums.size())
		return start;

	int end = start + 1;
	int diff = nums[end] - nums[start];
	while (end < nums.size() && nums[end] - nums[end - 1] == diff)
		end++;

	end--;

	return end;
}

int numberOfArithmeticSlices(vector<int>& nums) 
{
	if (nums.size() < 3)
		return 0;

	vector<pair<int, int>> arthvec;
	int ret = 0;
	
	int curdiff = nums[1] - nums[0];
	int start = 0, end = 0;
	int i = 0;
	while (i <= nums.size()-2)
	{
		int end = getArthSlice(nums, i);
		if (end < nums.size() && end >= i + 2)
		{
			arthvec.push_back(pair<int, int>(i, end));
		}
		i = end;
	}

	int arthlen = 3;
	for (i = 0; i < arthvec.size(); i++)
	{
		int arthlen = arthvec[i].second - arthvec[i].first + 1;
		ret += (arthlen - 2) * (arthlen - 1) / 2;
	}

	return ret;
}

void testnumberOfArithmeticSlices()
{	
	vector<int> nums({ 1,2,3,5,7,9 });
	numberOfArithmeticSlices(nums);
}

//https://leetcode.com/problems/battleships-in-a-board/
void markship(vector<vector<char>>& board, int r, int c, vector<vector<bool>>& counted)
{
	int deltar = 0, deltac = 0;
	int endr = board.size(), endc = board[0].size();

	if (r - 1 >= 0 && board[r - 1][c] == 'X')
	{
		while (r >= 0 && board[r][c] == 'X')
		{
			counted[r][c] = true;
			r--;
		}
	}
	else if (r + 1 < board.size() && board[r + 1][c] == 'X')
	{
		while (r < board.size() && board[r][c] == 'X')
		{
			counted[r][c] = true;
			r++;
		}
	}
	else if (c - 1 >= 0 && board[r][c - 1] == 'X')
	{
		while (c >= 0 && board[r][c] == 'X')
		{
			counted[r][c] = true;
			c--;
		}
	}
	else if (c + 1 < board[0].size() && board[r][c + 1] == 'X')
	{
		while (c < board[0].size() && board[r][c] == 'X')
		{
			counted[r][c] = true;
			c++;
		}
	}
	else
		counted[r][c] = true;
}

int countBattleships(vector<vector<char>>& board) 
{
	int ret = 0;
	vector<vector<bool>> counted(board.size(), vector<bool>(board[0].size(), false));
	int r, c;
	for (r = 0; r < board.size(); r++)
	{
		for (c = 0; c < board[0].size(); c++)
		{
			if (counted[r][c] == false && board[r][c] == 'X')
			{
				markship(board, r, c, counted);
				ret++;
			}
		}
	}

	return ret;
}

void testcountBattleships()
{
	vector<vector<char>> board({ {'.','X','.','.','X'},
								 {'.','X','.','.','X'},
								 {'.','.','.','.','X'},
								 {'X','.','X','X','.'},
								 {'X','.','.','.','X'} });
	countBattleships(board);
}

//https://leetcode.com/problems/range-sum-query-2d-immutable/description/
class NumMatrix 
{
public:
	NumMatrix(vector<vector<int>>& matrix) 
	{
		if (matrix.size() == 0 || matrix[0].size() == 0)
			return;

		matrixsum.resize(matrix.size());
		int i = 0, j = 0;
		for (i = 0; i < matrixsum.size(); i++)
			matrixsum[i].resize(matrix[0].size());

		matrixsum[0][0] = matrix[0][0];
		// 1st row
		for (i = 1; i < matrixsum[0].size(); i++)
		{
			matrixsum[0][i] = matrixsum[0][i - 1] + matrix[0][i];
		}

		// 1st colume
		for (i = 1; i < matrixsum.size(); i++)
		{
			matrixsum[i][0] = matrixsum[i-1][0] + matrix[i][0];
		}

		for (i = 1; i < matrix.size(); i++)
		{
			for (j = 1; j < matrix[0].size(); j++)
			{
				matrixsum[i][j] = matrix[i][j] + matrixsum[i - 1][j] + matrixsum[i][j - 1]  - matrixsum[i - 1][j - 1];
			}
		}

	}

	int sumRegion(int row1, int col1, int row2, int col2) 
	{
		int sum = matrixsum[row2][col2];

		if (row1 >= 1)
			sum -= matrixsum[row1 - 1][col2];

		if (col1 >= 1)
			sum -= matrixsum[row2][col1 - 1];

		if (row1 >= 1 && col1 >= 1)
			sum += matrixsum[row1 - 1][col1 - 1];

		return sum;
	}

	vector<vector<int>> matrixsum;
};



void testNumMatrix()
{
	vector<vector<int>> matrix({ { 3, 0, 1, 4, 2 },
								   { 5,6,3,2,1 },
								   { 1,2,0,1,5 },
								   { 4,1,0,1,7 },
								   { 1,0,3,0,5 } ,
								    });
	NumMatrix n(matrix);
}
//https://leetcode.com/problems/unique-binary-search-trees-ii/description/

vector<TreeNode*> buildTree(int start, int end) {
	vector<TreeNode*> ans;

	// If start > end, then subtree will be empty so add NULL in the ans and return it.
	if (start > end) {
		ans.push_back(NULL);
		return ans;
	}

	// Iterate through all values from start to end to construct left and right subtree recursively
	for (int i = start; i <= end; ++i) {
		vector<TreeNode*> leftSubTree = buildTree(start, i - 1);    // Construct left subtree
		vector<TreeNode*> rightSubTree = buildTree(i + 1, end);     // Construct right subtree

		// loop through all left and right subtrees and connect them to ith root  
		for (int j = 0; j < leftSubTree.size(); j++) {
			for (int k = 0; k < rightSubTree.size(); k++) {
				TreeNode* root = new TreeNode(i);   // Create root with value i
				root->left = leftSubTree[j];   // Connect left subtree rooted at leftSubTree[j]
				root->right = rightSubTree[k];   // Connect right subtree rooted at rightSubTree[k]
				ans.push_back(root);    // Add this tree(rooted at i) to ans data-structure
			}
		}
	}

	return ans;
}
vector<TreeNode*> generateTrees(int n) {
	return buildTree(1, n);
}

void testgenerateTrees()
{
	generateTrees(2);
}

//https://leetcode.com/problems/minimum-genetic-mutation
//BFS
int minMutation(string startGene, string endGene, vector<string>& bank) 
{
	int steps = 0;
	unordered_set<string> bankset(bank.begin(), bank.end());
	queue<pair<string, int>> Q;
	Q.push(pair<string, int>(startGene, 0));
	string genes("ACGT");
	while (!Q.empty())
	{
		pair<string, int> midgene(Q.front());
		Q.pop();
		if (midgene.first.compare(endGene.c_str()) == 0)
			return midgene.second;

		//ACGT
		for (int i = 0; i < midgene.first.size(); i++)
		{
			char gene = midgene.first[i];
			for (char gene : genes)
			{
				midgene.first[i] = gene;
				if (bankset.find(midgene.first) != bankset.end())
				{
					Q.push(pair<string, int>(midgene.first, midgene.second + 1));
					bankset.erase(midgene.first);
				}
			}
			midgene.first[i] = gene;
		}
	}

	return -1;
}

//https://leetcode.com/problems/non-overlapping-intervals/description/
bool isoverlap(vector<int>& a, vector<int>& b)
{
	if (a[0] == b[0] || a[1] > b[0])
		return true;

	return false;
}

int eraseOverlapIntervals(vector<vector<int>>& intervals) 
{
	int ret = 0;

	sort(intervals.begin(), intervals.end(),
		[&](vector<int> a, vector<int> b)
		{
			// 这里根据 a[1] 进行降序排序。如果要升序，则是:
			// if (a[1] > b[1]) 
			//     return true
			// 如果是：
			// if (a[1] > b[1]) 
			//     return false  <---- 则会导致 crash
			if (a[1] < b[1])
				return true;

			return false;
		});


	int prev = 0;
	int count = 1;
	int n = intervals.size();

	for (int i = 1; i < n; i++) {
		if (intervals[i][0] >= intervals[prev][1]) {
			prev = i;
			count++;
		}
	}
	return n - count;
}

void testeraseOverlapIntervals()
{
	vector<vector<int>> intervals({ {1,3} ,{1,2},{2,3},{3,4}, });

	eraseOverlapIntervals(intervals);
}

//https://leetcode.com/problems/binary-watch/description/
vector<string> readBinaryWatch(int turnedOn) 
{
	vector<string> ret;
	if (turnedOn > 8)
		return ret;

	for (int h = 0; h < 12; h++)
	{
		for (int m = 0; m < 60; m++)
		{
			int hbit = bitset<4>(h).count();
			int mbit = bitset<6>(m).count();
			if (hbit + mbit == turnedOn)
			{
				string timestr(to_string(h) + ":");
				if (m < 10)
					timestr.append("0" + to_string(m));
				else
					timestr.append(to_string(m));

				ret.emplace_back(timestr);
			}

			
		}
	}

	return ret;
}

//https://leetcode.com/problems/remove-k-digits/description/
string removeKdigits(string num, int k) 
{
	if (num.size() <= k)
		return "0";
		
	string ret;
	stack<char> s;
	s.push(num[0]);
	int i = 1;
	while (i < num.size())
	{
		while (k > 0 && !s.empty() && num[i] < s.top())
		{
			k--;
			s.pop();
		}

		s.push(num[i]);
		if (s.size() == 1 && num[i] == '0')
			s.pop();

		i++;
	}

	while (k > 0 && !s.empty())
	{
		s.pop();
		k--;
	}

	while (!s.empty())
	{
		ret.push_back(s.top());
		s.pop();
	}

	reverse(ret.begin(), ret.end());
	if (ret.size() == 0)
		return "0";

	return ret;
}


void testremoveKdigits()
{
	removeKdigits("10200", 1);
}

//https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
class XORTreeNode
{
public:
	XORTreeNode* children[2];

	XORTreeNode()
	{
		children[0] = NULL;
		children[1] = NULL;
	}
};

class XORTree
{
public:
	XORTreeNode root;
	int bits;

	XORTree(int bits)
	{
		this->bits = bits;
	}

	void insert(int num)
	{
		XORTreeNode* node = &root;
		for (int i = bits; i >= 0; i--)
		{
			int abit = (num >> i) & 1;
			if (node->children[abit] == NULL)
				node->children[abit] = new XORTreeNode();

			node = node->children[abit];
		}
	}

	int findmax(int num)
	{
		int max = 0;
		XORTreeNode* node = &root;
		for (int i = bits; i >= 0; i--)
		{
			int abit = (num >> i) & 1;
			// toggled_bit 时检查在 nums 中有没有某个数跟当前数在第 i 位上是相反的，而不是 xor 后的结果
			int toggled_bit = abit == 1 ? 0 : 1;
			if (node->children[toggled_bit] != NULL)
			{
				max += (1 << i);
				node = node->children[toggled_bit];
			}
			else
			{
				node = node->children[abit];
			}
		}

		return max;
	}
};


int findMaximumXOR(vector<int>& nums) 
{
	int max = 0;
	if (nums.size() == 0)
		return 0;

	int maxnum = *max_element(nums.begin(), nums.end());
	int bits = 0;
	while (maxnum > 0)
	{
		bits++;
		maxnum >>= 1;
	}

	XORTree xortree(bits);
	for (int num : nums)
	{
		xortree.insert(num);
		int tmp = xortree.findmax(num);
		if (tmp > max)
			max = tmp;
	}
	
	return max;
}

void testfindMaximumXOR()
{
	vector<int> nums({ 14,70,53,83,49,91,36,80,92,51,66,70 });
	findMaximumXOR(nums);
}


//https://leetcode.com/problems/longest-repeating-character-replacement/description/
int characterReplacement(string &s, int k) {
	int freq[26] = { 0 };
	int maxFreq = 0;
	int maxLength = 0;
	int left = 0;

	for (int right = 0; right < s.length(); ++right) {
		freq[s[right] - 'A']++;
		maxFreq = max(maxFreq, freq[s[right] - 'A']);

		if ((right - left + 1) - maxFreq > k) {
			freq[s[left] - 'A']--;
			left++;
		}

		maxLength = max(maxLength, right - left + 1);
	}

	return maxLength; 
}


void testcharacterReplacement()
{
	string s("AABABBA");
	int k = 1;
	characterReplacement(s, k);
}

//https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/
Node* flattenchild(Node* node)
{
	if (node == NULL)
		return NULL;

	Node* nodeidx = node;
	while (nodeidx->next != NULL)
	{
		if (nodeidx->child != NULL)
		{
			Node* tmp = nodeidx->next;
			Node *flattenednode = flattenchild(nodeidx->child);
			nodeidx->next = nodeidx->child;
			nodeidx->child->prev = nodeidx;
			flattenednode->next = tmp;
			tmp->prev = flattenednode;
			if (flattenednode->prev == NULL)
			{
				flattenednode->prev = nodeidx;
			}
			nodeidx->child = NULL;
			nodeidx = tmp;
		}
		else
		{
			nodeidx = nodeidx->next;
		}
	}

	if (nodeidx->child != NULL)
	{
		Node* flattenednode = flattenchild(nodeidx->child);
		nodeidx->next = nodeidx->child;
		nodeidx->child->prev = nodeidx;
		nodeidx->child = NULL;
		while (flattenednode->next != NULL)
			flattenednode = flattenednode->next;

		return flattenednode;
	}

	return nodeidx;
}

Node* flatten(Node* head) 
{
	if (head == NULL)
		return NULL;

	flattenchild(head);
	return head;
}

void testflatten2()
{
	Node n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7), n8(8), n9(9), n10(10), n11(11), n12(12);
	
	n1.next = &n2;	n2.prev = &n1;
	n2.next = &n3;	n3.prev = &n2;
	n3.next = &n7; n7.prev = &n3;

	n3.child = &n4;
	n4.child = &n5;
	n5.child = &n6;

	flatten(&n1);
}

//https://leetcode.com/problems/find-right-interval/description/
int findstartj(int endi, vector<vector<int>>& intervals, vector<int> &order_in_start)
{
	int l = 0, r = order_in_start.size()-1;
	int m = l + (r - l) / 2;
	int startjidx = -1;
	while (l <= r)
	{
		if (endi == intervals[order_in_start[m]][0])
		{
			int m_left = m;
			while (m_left - 1 >= 0 && intervals[order_in_start[m_left - 1]][0] == endi)
			{
				m_left--;
			}
			if (m_left == m)
				return order_in_start[m];

			return order_in_start[m_left+1];
		}

		if (endi > intervals[order_in_start[m]][0])
		{
			l = m + 1;
		}
		else
		{
			startjidx = m;
			r = m - 1;
		}

		m = l + (r - l) / 2;
	}

	if (startjidx == -1)
		return startjidx;

	return order_in_start[startjidx];
}

vector<int> findRightInterval(vector<vector<int>>& intervals) 
{
	vector<int> ret;	
	if (intervals.size() == 1)
	{
		if (intervals[0][0] >= intervals[0][1])
			ret.push_back(0);
		else
			ret.push_back(-1);

		return ret;
	}

	vector<int> order_in_start(intervals.size(), 0);
	std::iota(order_in_start.begin(), order_in_start.end(), 0);
	// 根据 intervals[i][0] 进行降序排序，排序后的索引放到 order_in_start 中
	sort(order_in_start.begin(), order_in_start.end(),
		[&](int i, int j)
		{
			return intervals[i][0] < intervals[j][0];
		});

	for (int i = 0; i < intervals.size(); i++)
	{
		int endi = intervals[i][1];
		ret.push_back(findstartj(endi, intervals, order_in_start));
	}

	return ret;
}

void testfindRightInterval()
{
	vector<vector<int>> intervals({ {1,4},{2,3},{3,4} });
	findRightInterval(intervals);
}

//https://leetcode.com/problems/path-sum-iii/
// therestsum has deducted root->val
void sumOnPath(vector<TreeNode*> &nodeOnPath, TreeNode * root, long long therestsum, int &path)
{
	if (therestsum == 0)
	{
		path++;
	}

	if (root == NULL)
		return;

	int leftsum = 0, rightsum = 0;
	if (root->left != NULL)
	{
		//vector<TreeNode*> tmpNodeOnPath(nodeOnPath);
		//tmpNodeOnPath.push_back(root->left);
		//sumOnPath(tmpNodeOnPath, root->left, therestsum - root->left->val, path);
		sumOnPath(nodeOnPath, root->left, therestsum - root->left->val, path);
	}

	if (root->right!= NULL)
	{
		//vector<TreeNode*> tmpNodeOnPath(nodeOnPath);
		//tmpNodeOnPath.push_back(root->right);
		//sumOnPath(tmpNodeOnPath, root->right, therestsum - root->right->val, path);
		sumOnPath(nodeOnPath, root->right, therestsum - root->right->val, path);
	}
}

int getSumOnPath(TreeNode* root, int targetSum)
{	
	if (root == NULL)
		return 0;

	int totalpath = 0;
	queue<TreeNode*> nodeq;
	nodeq.push(root);
	while (nodeq.size() > 0)
	{
		vector<TreeNode*> nodeOnPath;		
		TreeNode* node = nodeq.front();
		sumOnPath(nodeOnPath, node, targetSum - node->val, totalpath);
		nodeq.pop();
		if (node->left)
			nodeq.push(node->left);

		if (node->right)
			nodeq.push(node->right);
	}
	
	return totalpath;
}

int pathSum3(TreeNode* root, int targetSum) 
{
	if (root == NULL)
		return 0;

	return getSumOnPath(root, targetSum);
}

void testpathSum3()
{
	vector<int> v1({ 1,-2,-3,1,3,-2,INT_MIN,-1 });
	TreeNode** t1 = createTree(v1);
	getSumOnPath(*t1, -1);
}

//https://leetcode.com/problems/find-all-anagrams-in-a-string/description/
bool isAnagrams(string& s, int idx, string& p, int *charidx, bool * charexistence, int &nextidx)
{
	if (idx + p.size() > s.size())
		return false;	

	for (int i = 0; i < p.size(); i++)
	{
		if (charidx[s[i+idx] - 'a'] > 0)
		{
			charidx[s[i + idx] - 'a']--;
		}
		else
		{
			if (charexistence[s[i + idx] - 'a'] == true)
			{
				nextidx = idx+1;
			}
			else
			{
				nextidx = i + idx;
			}

			return false;
		}
	}

	return true;
}
vector<int> findAnagrams(string s, string p) {

	vector<int> ret;
	if (s.length() < p.length())
		return ret;

	int charidx[26] = { 0 };
	bool charexistence[26] = { 0 };
	int i = 0;
	for (i = 0; i < p.size(); i++)
	{
		charidx[p[i] - 'a']++;
		charexistence[p[i] - 'a'] = true;
	}

	i = 0;
	while (i <= s.size() - p.size())
	{
		if (charidx[s[i] - 'a'] > 0)
		{
			int charidx_tmp[26] = { 0 };
			memcpy(charidx_tmp, charidx, sizeof(charidx));
			if (isAnagrams(s, i, p, charidx_tmp, charexistence, i) == true)
			{
				ret.push_back(i);
				i++;
			}
		}
		else
		{
			i++;
		}
	}

	return ret;
}

void testfindAnagrams()
{
	string s("abacbabc");
	string p("abc");

	findAnagrams(s, p);
}

//https://leetcode.com/problems/find-all-duplicates-in-an-array/
vector<int> findDuplicates(vector<int>& nums) 
{
	vector<int> ret;
	if (nums.size() == 1)
		return ret;

	if (nums.size() == 2)
	{
		if (nums[0] == nums[1])
		{
			ret.push_back(nums[0]);
		}

		return ret;
	}

	int sizeof_int = sizeof(int);
	int* numsbits = new int[nums.size()/ 4 + 1];
	memset(numsbits, 0, (nums.size() / 4 + 1) * 4);

	int bitmask[32] = { 0 };
	int i = 0;
	for (i = 0; i < 32; i++)
	{
		bitmask[i] = 1 << i;
	}

	for (int i = 0; i < nums.size(); i++)
	{
		int n = nums[i];
		int numidx = n / 32;
		int bitidx = n % 32;

		if ((numsbits[numidx] & bitmask[bitidx]) == 0)
		{
			numsbits[numidx] |= bitmask[bitidx];
		}
		else
		{
			ret.push_back(n);
		}
	}

	delete[] numsbits;

	return ret;
}

void testfindDuplicates()
{
	vector<int> nums({ 4,3,2,7,8,2,3,1 });
	//vector<int> nums({ 1,1,2 });
	findDuplicates(nums);
}

//https://leetcode.com/problems/string-compression/description/
int findduplicateCharCnt(vector<char>& chars, int idx, int charslen)
{
	int i = idx+1;
	char cur_c = chars[idx];
	for (; i < charslen; i++)
	{
		if (chars[i] != cur_c)
		{
			break;
		}
	}
	return i - idx;
}

void moveforwardchars(vector<char>& chars, int src, int dest, int charslen)
{
	if (dest >= src || dest >= charslen || src >= charslen)
		return;

	int src_idx = src, dest_idx = dest;
	for (; src_idx < charslen; src_idx++, dest_idx++)
	{
		chars[dest_idx] = chars[src_idx];
	}	
}

int compress(vector<char>& chars) 
{
	int compressidx = 0, replaceidx = 1;
	int charslen = chars.size();
	while (compressidx < charslen)
	{
		int dupchars = findduplicateCharCnt(chars, compressidx, charslen);
		if (dupchars == 1)
		{
			compressidx++;
			replaceidx++;
		}
		else if (dupchars < 10)
		{
			chars[replaceidx] = '0' + dupchars;
			if (dupchars == 2)
			{
				replaceidx += 2;
				compressidx += 2;
			}
			else
			{
				replaceidx++;
				compressidx += dupchars;
				moveforwardchars(chars, compressidx, replaceidx, charslen);
				compressidx = replaceidx;
				replaceidx++;
				charslen = charslen - dupchars + 2;
			}
		}
		else
		{
			string strdupchars = std::to_string(dupchars);
			for (int j = 0; j < strdupchars.size(); j++, replaceidx++)
			{
				chars[replaceidx] = strdupchars[j];
			}			
			compressidx += dupchars;
			moveforwardchars(chars, compressidx, replaceidx, charslen);
			compressidx = replaceidx;
			replaceidx++;
			charslen = charslen - dupchars + strdupchars.size() + 1;
		}
	}

	return charslen;
}

void testcompress()
{
	vector<char> chars({ 'a','a','a','b','b','a','a','a','a' ,'a','a' ,'a','a' ,'a','a' ,'a','a' ,'a','a', 'b','a','a' });
	//vector<char> chars({ 'a','a','a','a','a','a','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','c','c','c','c','c','c','c','c','c','c','c','c','c','c' });
	compress(chars);
}

//https://leetcode.com/problems/number-of-boomerangs/description/
double getdist(vector<vector<int>>& points, int i, int j)
{
	if (i >= points.size() || j >= points.size())
		return -1;

	return sqrt(pow(points[i][0] - points[j][0], 2) + pow(points[i][1] - points[j][1], 2));
}

int getBoomerangs(vector<vector<double>>& distances, int idxi)
{
	int idxj = 0, idxk = 0;
	int numbers = 0;
	
	for (idxj = 0; idxj < distances.size(); idxj++)
	{
		if (idxj == idxi)
			continue;

		for (idxk = 0; idxk < distances.size(); idxk++)
		{
			if (idxk == idxj || idxk == idxi)
				continue;

			if (distances[idxi][idxj] == distances[idxi][idxk])
			{
				numbers++;
			}
		}
	}

	return numbers;
}

int numberOfBoomerangs_slow(vector<vector<int>>& points) 
{
	if (points.size() < 3)
		return 0;

	vector<vector<double>> distances;
	distances.resize(points.size());
	int i = 0, j = 0;
	for (i = 0; i < points.size(); i++)
	{
		distances[i].resize(points.size());
	}

	for (i = 0; i < points.size(); i++)
	{
		distances[i].resize(points.size());
		for (j = 0; j < points.size(); j++)
		{
			if (i != j)
			{
				if (distances[i][j] != 0)
					continue;

				distances[i][j] = getdist(points, i, j);
				distances[j][i] = distances[i][j];
			}
			else
			{
				distances[i][j] = 0;
			}
		}
	}

	int numbers = 0;
	for (i = 0; i < points.size(); i++)
	{
		numbers += getBoomerangs(distances, i);
	}

	return numbers;
}


int numberOfBoomerangs(vector<vector<int>>& points)
{
	if (points.size() < 3)
		return 0;

	int numbers = 0;
	map<unsigned int, unsigned int> distmap;
	int i = 0, j = 0;

	for (i = 0; i < points.size(); i++)
	{
		for (j = 0; j < points.size(); j++)
		{
			if (i == j)
				continue;

			unsigned int dist = pow(points[i][0] - points[j][0], 2) + pow(points[i][1] - points[j][1], 2);
			if (distmap.find(dist) == distmap.end())
				distmap[dist] = 1;
			else
				distmap[dist]++;
		}

		map<unsigned int, unsigned int>::iterator itor(distmap.begin());
		while (itor != distmap.end())
		{
			numbers += itor->second * (itor->second - 1);
			if (itor->second != 1)
			{
				int x = 0;
				x++;
			}

			itor++;
		}

		distmap.clear();
	}	

	return numbers;
}
void testnumberOfBoomerangs()
{
	vector<vector<int>> points({ {1,2}, {3,5}, {5,6} });
	
	numberOfBoomerangs(points);
}

//https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
vector<int> findDisappearedNumbers(vector<int>& nums) 
{
	vector<int> ret;
	int n = nums.size();
	int i = 0;
	for (i = 0; i < n; i++)
	{
		while (nums[nums[i] - 1] != nums[i])
			swap(nums[i], nums[nums[i] -1]);
	}

	for (i = 0; i < n; i++)
	{
		if (nums[i] != i + 1)
			ret.push_back(i+1);
	}

	return ret;
}

void testfindDisappearedNumbers()
{
	// 73248231
	// 33248271
	// 23348271
	// 32348271
	// 
	// 
//	vector<int> nums({ 4, 3, 2, 7, 8, 2, 3, 1 });
//	vector<int> nums({ 1,1 });
	vector<int> nums({ 1, 1, 2, 2 });

	findDisappearedNumbers(nums);
}

//https://leetcode.com/problems/serialize-and-deserialize-bst/description/

class Codec {
public:
	// 序列化二叉树（前序遍历）
	string serialize(TreeNode* root) {
		if (root == nullptr) {
			return "#";
		}
		return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
	}

	// 反序列化二叉树
	TreeNode* deserialize(string data) {
		queue<string> nodes;
		stringstream ss(data);
		string item;

		while (getline(ss, item, ',')) {
			nodes.push(item);
		}

		return deserializeHelper(nodes);
	}

	// 层次遍历序列化
	string serializeBFS(TreeNode* root) {
		if (!root) return "";

		queue<TreeNode*> q;
		q.push(root);
		string result;

		while (!q.empty()) {
			TreeNode* node = q.front();
			q.pop();

			if (node) {
				result += to_string(node->val) + ",";
				q.push(node->left);
				q.push(node->right);
			}
			else {
				result += "#,";
			}
		}

		return result;
	}

	TreeNode* deserializeBFS(string data) {
		if (data.empty()) return nullptr;

		vector<string> nodes;
		stringstream ss(data);
		string item;

		while (getline(ss, item, ',')) {
			nodes.push_back(item);
		}

		if (nodes.empty() || nodes[0] == "#") {
			return nullptr;
		}

		TreeNode* root = new TreeNode(stoi(nodes[0]));
		queue<TreeNode*> q;
		q.push(root);

		int index = 1;
		while (!q.empty() && index < nodes.size()) {
			TreeNode* current = q.front();
			q.pop();

			// 处理左子节点
			if (index < nodes.size() && nodes[index] != "#") {
				current->left = new TreeNode(stoi(nodes[index]));
				q.push(current->left);
			}
			index++;

			// 处理右子节点
			if (index < nodes.size() && nodes[index] != "#") {
				current->right = new TreeNode(stoi(nodes[index]));
				q.push(current->right);
			}
			index++;
		}

		return root;
	}

private:
	TreeNode* deserializeHelper(queue<string>& nodes) {
		if (nodes.empty()) {
			return nullptr;
		}

		string front = nodes.front();
		nodes.pop();

		if (front == "#") {
			return nullptr;
		}

		TreeNode* root = new TreeNode(stoi(front));
		root->left = deserializeHelper(nodes);
		root->right = deserializeHelper(nodes);

		return root;
	}
};

void testserialize()
{
	// 012##56###7##
	vector<int> v1({ 0,1,2,INT_MIN, INT_MIN, 5,6,INT_MIN, INT_MIN,INT_MIN, INT_MIN,INT_MIN, INT_MIN,INT_MIN, 7 });
	TreeNode** t1 = createTree(v1);

	Codec c;
	string spre = c.serialize(*t1);
	TreeNode* tpre = c.deserialize(spre);

	string stier = c.serializeBFS(*t1);	
	TreeNode* tbfs = c.deserializeBFS(stier);
}

//https://leetcode.com/problems/delete-node-in-a-bst/description/
TreeNode* findTreeNode(int key, TreeNode *node, TreeNode *& parentnode)
{
	if (node->val == key)
		return node;

	TreeNode* target = NULL;
	
	if (node->left != NULL)
	{
		parentnode = node;
		target = findTreeNode(key, node->left, parentnode);
	}

	if (target == NULL && node->right != NULL)
	{
		parentnode = node;
		target = findTreeNode(key, node->right, parentnode);
	}

	return target;
}

TreeNode* getrightestOfLeft(TreeNode* node, TreeNode*& parentofrightest)
{
	if (node == NULL)
		return NULL;

	parentofrightest = node;
	TreeNode* tmp = node->left;
	while (tmp != NULL && tmp->right != NULL)
	{
		parentofrightest = tmp;
		tmp = tmp->right;
	}

	return tmp;
}

TreeNode* getleftmostOfRight(TreeNode* node, TreeNode*& parentofleftmost)
{
	if (node == NULL)
		return NULL;

	parentofleftmost = node;
	TreeNode* tmp = node->right;
	while (tmp != NULL && tmp->left != NULL)
	{
		parentofleftmost = tmp;
		tmp = tmp->left;
	}

	return tmp;
}


TreeNode* deleteNode(TreeNode* root, int key)
{
	if (root == NULL)
		return root;

	TreeNode* ret = NULL;
	TreeNode* parentnode = NULL;
	TreeNode* delednode = findTreeNode(key, root, parentnode);
	if (delednode == NULL)
		return root;

	TreeNode* parentofleftmost = NULL;
	TreeNode* leftmost = getleftmostOfRight(delednode, parentofleftmost);
	if (delednode == root)
	{
		if (leftmost == NULL)
		{
			root = root->left;
		}
		else
		{			
			leftmost->left = root->left;
			if (parentofleftmost != root)
			{
				parentofleftmost->left = leftmost->right;
				leftmost->right = root->right;
			}
			root = leftmost;
		}
	}
	else
	{
		if (leftmost == NULL)
		{
			if (parentnode->left == delednode)
			{
				parentnode->left = delednode->left;
			}
			else
			{
				parentnode->right = delednode->left;
			}
		}
		else
		{
			if (parentnode->left == delednode)
			{
				parentnode->left = leftmost;
			}
			else
			{
				parentnode->right = leftmost;
			}

			leftmost->left = delednode->left;			
			if (parentofleftmost != delednode)
			{
				parentofleftmost->left = leftmost->right;
				leftmost->right = delednode->right;
			}
			
		}
	}

	return root;
}

TreeNode* deleteNode2(TreeNode* root, int key) 
{
	if (root == NULL)
		return root;

	TreeNode *ret = NULL;
	TreeNode *parentnode = NULL;
	TreeNode *delednode = findTreeNode(key, root, parentnode);
	if (delednode == NULL)
		return root;

	TreeNode* parentofrightest = NULL;
	TreeNode* rightest = getrightestOfLeft(delednode, parentofrightest);
	
	if (delednode == root)
	{
		if (rightest == NULL)
		{
			root = root->right;
		}
		else
		{	
			rightest->right = root->right;
			if (parentofrightest != root)
			{
				parentofrightest->right = rightest->left;
				rightest->left = root->left;
			}
			root = rightest;
		}		
	}
	else
	{
		if (rightest == NULL)
		{	
			if (parentnode->left == delednode)
			{
				parentnode->left = delednode->right;
			}
			else
			{
				parentnode->right = delednode->right;
			}			
		}
		else
		{
			if (parentnode->left == delednode)
			{
				parentnode->left = rightest;
			}
			else
			{
				parentnode->right = rightest;
			}

			rightest->right = delednode->right;

			if (parentofrightest != delednode)
			{
				parentofrightest->right = rightest->left;
			}
		}
	}

	return root;
}

void testdeleteNode()
{
	//vector<int> v1({ 5,3,6,1,4,INT_MIN,INT_MIN,INT_MIN,2});
	vector<int> v1({ 5, 3, 6, 2, 4, INT_MIN, 7 });
	//vector<int> v1({ 3, 2, 5, INT_MIN, INT_MIN, 4, 10, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 8, 15, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 7 });
	TreeNode** t1 = createTree(v1);

	deleteNode(*t1, 3);
}


//https://leetcode.com/problems/sort-characters-by-frequency/description/
string frequencySort2(string s) 
{
	unordered_map<char, int> snum;
	vector<char> uniquechar;
	for (int i = 0; i < s.size(); i++)
	{
		if (snum.find(s[i]) == snum.end())
		{
			snum[s[i]] = 1;
			uniquechar.push_back(s[i]);
		}
		else
		{
			snum[s[i]]++;
		}
	}

	sort(uniquechar.begin(), uniquechar.end(),
		[&](char a, char b)
		{
			return snum[a] > snum[b];
		});

	s.clear();
	for (int i = 0; i < uniquechar.size(); i++)
	{
		s.insert(s.end(), snum[uniquechar[i]], uniquechar[i]);
	}

	return s;
}

void testfrequencySort2()
{
	string s("loveleetcode");
	frequencySort2(s);
}

//https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
int findMinArrowShots_slow(vector<vector<int>>& points) 
{
	sort(points.begin(), points.end(),
		[&](vector<int> a, vector<int> b)
		{
			return a[0] < b[0];
		});

	int ret = 0;
	int i = 0;
	while (i < points.size())
	{
		int j = i + 1;
		int overlap_s = points[i][0], overlap_e = points[i][1];
		while (j < points.size() && points[j][0] <= overlap_e)
		{
			overlap_s = points[j][0];
			overlap_e = min(overlap_e, points[j][1]);
			j++;
		}
		ret++;
		i = j;
	}

	return ret;
}

int findMinArrowShots(vector<vector<int>>& points) 
{
	std::sort(points.begin(), points.end(), [](const auto& a, const auto& b) {
		return a[0] < b[0];
		});

	int arrows = 1;
	int end = points[0][1];

	for (size_t i = 1; i < points.size(); ++i) {
		if (points[i][0] > end) {
			arrows++;
			end = points[i][1];
		}
		else {
			end = std::min(end, points[i][1]);
		}
	}

	return arrows;
}

void testfindMinArrowShots()
{
	vector<vector<int>> points({ {3,9},{7,12},{3,8},{6,8},{9,10},{2,9},{0,9},{3,9},{0,6},{2,8} });

	findMinArrowShots(points);
}

//https://leetcode.com/problems/minimum-moves-to-equal-array-elements/
bool areallelesequal(vector<int>& nums)
{
	int i = nums[0];
	for (int j = 1; j < nums.size(); j++)
	{
		if (nums[j] != i)
		{
			return false;
		}
	}

	return true;
}

int minMoves(vector<int>& nums) 
{
	if (nums.size() < 2)
		return 0;

	int moves = 0;
	int min = nums[0];
	int i = 0;
	for (i = 1; i < nums.size(); i++)
		if (nums[i] < min)
			min = nums[i];

	for (i = 0; i < nums.size(); i++)
		moves += nums[i] - min;
	
	return moves;
}

void testminMoves()
{
	vector<int> nums({ -9, -7, -5, -3, 0, 2, 4, 5, 7, 9 });

	minMoves(nums);
}

//https://leetcode.com/problems/4sum-ii/
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) 
{
	int ret = 0;
	int i, j, k, l;
	unordered_map<int, int> sum34;
	for (k = 0; k < nums3.size(); k++)
	{
		for (l = 0; l < nums4.size(); l++)
		{
			sum34[nums3[k] + nums4[l]]++;
		}
	}

	for (i = 0; i < nums1.size(); i++)
	{
		for (j = 0; j < nums2.size(); j++)
		{	
			ret += sum34[-(nums1[i] + nums2[j])];
		}
	}

	return ret;
}

void testfourSumCount()
{
	vector<int> n1({ -1,-1 });
	vector<int> n2({ -1, 1 });
	vector<int> n3({ -1, 1 });
	vector<int> n4({ 1, -1 });

	fourSumCount(n1, n2, n3, n4);
}

//https://leetcode.com/problems/assign-cookies/description/
int findContentChildren(vector<int>& g, vector<int>& s) 
{
	sort(g.begin(), g.end());
	sort(s.begin(), s.end());
	int i = 0, j = 0;

	while (i < g.size() && j < s.size())
	{
		if (s[j] < g[i])
		{
			j++;
		}
		else
		{
			i++;
			j++;
		}
	}

	return i;
}

void testfindContentChildren()
{
	vector<int> g({ 250,490,328,149,495,325,314,360,333,418,430,458 });
	vector<int> s({ 376,71,228,110,215,410,363,135,508,268,494,288,24,362,20,5,247,118,152,393,458,354,201,188,425,167,220,114,148,43,403,385,512,459,71,425,142,102,361,102,232,203,25,461,298,437,252,364,171,240,233,257,305,346,307,408,163,216,243,261,137,319,33,91,116,390,139,283,174,409,191,338,123,231,101,458,497,306,400,513,175,454,273,88,169,250,196,109,505,413,371,448,12,193,396,321,466,526,276,276,198,260,131,322,65,381,204,32,83,431,81,108,366,188,443,331,102,72,496,521,502,165,439,161,257,324,348,176,272,341,230,323,124,13,51,241,186,329,70,387,93,126,159,370,292,16,211,327,431,26,70,239,379,368,215,501,382,299,481,163,100,488,259,524,481,87,118,112,110,425,295,352,62,162,19,404,301,163,389,13,383,43,397,165,385,274,59,499,136,309,301,345,381,124,394,492,96,243,4,297,153,9,210,291,33,450,202,313,138,214,308,239,129,154,354,289,484,388,351,339,337,161,97,185,190,498,348,242,38,217,343,170,269,465,514,89,366,447,166,52,33,436,268,3,74,505,403,302,513,69,439,68,72,403,33,130,466,417,186,339,328,237,138,427,392,496,430,442,260,229,372,217,399,203,170,246,153,137,358,138,22,19,110,304,399,458,165,372,254,358,364,345,52,150,121,226,156,231,83,377,237,342,184,27,73,392,238,366,258,434,498,184,309,394,110,246,430,437,33,488,520,69,24,18,221,146,19,147,283,407,437,185,399,238,471,117,110,266,507,263,293,94,314,31,217,224,36,515,147,432,270,327,521,113,153,14,160,435,396,501,13,461,103,441,461,68,55,510,380,291,305,365,511,218,515,148,324,136,291,519,201,192,97,183,448,294,242,379,52,154,224,183,344,452,240,380,338,337,437,92,206,490,405,396,274,41,305,170,423,437,92,480,477,260,224,176,239,466,525,458,226,189,251,516,479,305,463,116,126,88,490,93,389,246,480,139,193,303,205,270,83,89,461,492,209,311,368,457,478,188,484,4,501,513,18,2,90,39,205,500,391,191,229,32,147,438,123,493,71,363,143,163,110,199,305,476,430,86,378,416,444,325,207,519,380,81,116,503,13,211,290,327,510,141,37,242,370,117,208,58,336,432,19,474,488,74,472,63,287,11,470,221,349,211,191,497,50,442,315,376,355,302,206,291,376,499,405,498,202,40,115,178,66,438,446,498,443,292,123,493,505,205,490,368,349,341,107,290,428,141,271,117,54,410,172,92,450,524,427,371,69,77,35,234,25,152,365,509,154,61,143,111,188,101,327,21,378,186,57,241,351,136,213,143,86,325,83,358,79,427,406,491,192,248,360,428,478,385,252,270,106,524,343,92,483,9,15,54,511,296,238,392,106,198,64,394,122,187,14,481,50,221,226,63,50,449,504,357,499,120,448,275,363,465,451,68,25,233,124,520,415,90,302,246,19,63,335,308,235,297,410,349,78,324,210,327,199,202,455,387,159,148,344,375,127,368,305,347,307,451,412,323,188,16,139,143,362,228,493,334,341,406,113,368,234,439,193,211,500,231,311,204,99,82,52,66,286,142,27,445,12,410,370,118,104,358,330,96,351,93,469,63,450,14,455,309,84,101,58,166,224,34,158,322,388,345,328,329,509,168,292,367,5,309,477,75,306,524,416,35,417,229,448,513,99,179,526,147,390,260,459,394,503,414,221,429,469,160,415,417,435,139,277,195,340,526,7,369,177,324,132,505,36,239,354,414,144,221,378,441,13,93,70,104,449,387,288,492,329,257,489,501,308,376,289,421,320,226,407,294,463,209,322,34,72,310,2,293,11,196,411,136,455,106,432,193,475,518,243,306,410,14,273,145,492,290,33,345,108,75,271,115,517,456,326,108,319,470,40,429,408,380,271,423,475,100,402,408,379,428,512,340,8,172,43,383,72,422,35,57,281,185,304,442,224,376,163,478,210,146,266,139,309,263,210,400,131,400,56,371,458,365,215,173,148,349,369,300,144,225,162,335,221,311,276,248,261,90,270,12,450,80,420,227,126,16,263,326,139,104,454,137,295,68,400,277,463,88,355,32,242,116,205,396,397,448,217,505,224,376,280,252,455,46,49,455,60,228,30,70,157,346,190,455,222,426,377,447,299,305,484,282,135,147,262,339,139,446,272,215,89,304,194,495,466,509,2,329,57,264,230,121,273,237,498,179,216,54,317,473,198,331,117,479,503,438,514,58,72,259,224,424,381,35,53,40,393,274,180,174,435,131,426,401,195,472,59,157,178,73,217,262,253,387,487,430,342,487,122,352,496,116,214,159,403,513,434,348,72,321,72,174,113,335,31,84,353,8,111,11,284,378,406,2,156,409,69,8,332,15,467,206,57,408,272,446,10,345,457,194,146,459,222,371,22,159,73,90,440,144,87,244,506,129,526,237,27,83,249,281,259,171,243,524,385,490,383,151,337,488,312,117,313,357,231,251,263,396,277,355,350,82,75,382,73,124,126,49,33,160,118,180,166,357,143,254,417,410,280,526,217,358,2,469,328,148,350,99,465,423,179,72,496,150,46,154,57,65,332,489,59,101,138,276,290,411,35,85,166,350,338,320,167,11,395,159,49,75,379,33,123,90,118,133,485,484,370,224,421,16,39,340,70,311,448,93,53,100,230,345,287,57,318,420,194,291,146,384,262,388,313,453,53,461,266,208,152,15,276,459,523,17,309,187,171,16,482,149,184,54,372,177,43,240,213,67,168,194,296,475,344,152,478,244,122,48,360,426,492,223,189,291,259,475,237,263,518,460,279,261,487,81,337,470,301,175,343,113,111,524,104,127,428,403,449,481,404,297,332,215,517,92,101,353,199,456,475,44,399,67,270,394,90,421,93,66,162,396,352,397,26,461,140,211,458,375,82,177,108,71,30,175,443,471,34,6,423,385,78,422,254,480,469,236,96,394,48,175,300,170,366,49,168,28,154,315,84,52,255,110,309,320,295,123,337,202,186,38,54,309,501,119,99,448,163,110,138,119,244,306,384,141,441,419,410,168,370,440,483,398,328,419,522,322,398,365,149,523,453,351,347,408,209,422,341,44,270,3,135,342,51,270,115,181,474,487,195,266,56,149,22,11,194,293,238,206,220,398,9,169,431,248,514,22,186,135,348,319,206,513,289,455,21,421,8,258,176,408,327,470,379,27,204,339,344,192,127,466,347,414,429,399,212,244,350,103,434,332,414,235,70,517,45,370,212,300,400,241,128,111,93,217,287,140,72,188,208,33,227,124,401,306,517,416,324,485,191,79,194,342,183,344,206,355,195,40,117,112,313,520,126,38,211,151,124,447,28,68,284,214,187,411,340,513,87,465,263,511,465,87,205,179,320,485,169,153,34,403,417,226,246,447,219,420,268,495,351,269,214,311,188,28,60,167,93,62,173,469,423,58,358,161,83,297,461,53,357,227,20,191,96,182,212,52,113,242,442,420,243,314,426,524,115,56,172,173,477,189,188,414,122,451,453,465,262,17,398,425,519,243,437,251,105,94,503,213,405,362,470,148,96,343,470,30,344,114,285,37,49,323,424,513,119,194,280,179,332,198,389,412,273,34,209,72,314,203,389,471,339,173,280,82,219,90,523,36,187,453,439,418,381,324,146,430,456,394,461,345,449,129,150,241,512,411,78,26,273,275,424,217,188,172,391,223,489,35,420,300,322,518,2,117,122,290,318,518,147,470,75,308,368,12,510,206,157,138,355,487,446,217,121,443,505,294,218,339,523,21,125,249,185,520,453,189,454,146,9,259,198,399,121,436,511,397,525,313,489,144,52,372,156,59,316,231,89,241,207,325,117,415,4,208,116,321,166,223,463,29,260,360,408,124,464,188,194,245,401,491,389,145,414,120,375,422,423,153,489,220,42,374,179,402,367,434,471,203,303,83,428,123,49,487,127,251,213,64,116,470,192,436,489,428,61,302,273,219,495,172,354,17,163,30,105,487,303,224,260,59,121,199,251,166,437,232,494,422,88,435,185,411,162,296,327,186,140,450,323,289,38,187,499,490,78,259,156,275,234,369,328,511,280,17,303,431,48,229,513,72,42,98,515,110,363,446,202,79,328,485,118,434,487,310,401,112,472,258,462,84,72,378,337,413,395,32,230,145,289,504,167,158,128,356,435,26,294,130,277,276,78,133,519,467,208,89,89,418,107,429,31,86,387,172,193,343,390,303,61,452,10,161,254,48,492,292,114,240,158,241,291,383,345,429,358,227,224,340,63,279,203,205,382,461,203,496,498,6,453,89,24,507,143,63,408,165,402,336,333,205,153,180,288,399,83,122,504,178,24,60,471,283,378,2,210,33,315,253,124,134,141,363,410,267,40,310,159,391,33,345,496,298,380,190,202,294,149,67,4,427,381,163,332,300,389,176,254,222,378,345,486,259,111,285,249,482,295,26,313,282,121,115,406,32,242,134,476,80,131,459,334,186,112,419,488,460,81,120,452,191,490,29,31,289,104,442,172,457,256,154,1,365,124,472,388,374,365,300,474,229,147,447,314,399,230,187,397,105,399,65,516,296,4,14,351,407,331,238,278,376,325,149,336,85,458,281,467,253,411,494,49,177,26,119,471,342,114,5,340,36,481,417,516,123,168,177,111,506,242,313,162,478,126,255,426,246,420,236,222,517,479,71,146,148,509,299,60,341,345,228,97,222,71,127,421,395,476,295,521,523,44,68,156,424,251,362,356,111,282,400,401,465,341,512,217,275,232,375,70,480,136,263,235,513,110,335,257,167,117,342,488,176,396,18,15,110,225,313,214,173,418,214,160,358,43,278,225,342,415,464,521,341,395,163,420,136,461,35,469,157,268,284,30,101,156,67,149,91,139,84,298,419,123,345,186,140,418,453,46,423,494,4,338,521,227,131,109,48,341,419,164,81,250,391,10,356,130,264,311,513,146,495,395,211,227,182,169,242,459,207,307,519,349,4,194,99,220,292,18,335,178,283,412,224,304,214,258,402,236,235,470,289,269,341,18,210,151,361,157,317,181,129,219,320,140,180,267,311,346,243,156,510,433,125,148,307,338,191,398,173,87,94,56,296,75,100,513,504,99,267,105,428,258,515,437,44,464,319,128,184,464,102,328,505,291,20,396,252,437,77,94,493,462,327,315,178,13,318,447,510,91,411,44,270,398,79,519,438,367,141,382,501,521,341,194,516,397,441,439,21,501,345,268,390,234,378,428,247,133,454,273,88,289,330,45,101,264,478,28,338,185,171,235,514,442,353,243,352,202,268,4,322,300,71,126,277,473,70,453,256,487,500,304,128,206,63,58,289,452,359,12,286,513,264,467,96,444,509,500,205,402,404,89,86,136,189,180,478,165,508,320,437,341,60,431,113,365,359,150,269,217,313,247,315,250,223,385,381,167,499,503,13,243,100,102,446,126,485,205,400,89,313,211,64,50,262,121,472,236,14,465,158,502,493,162,121,199,242,410,31,258,34,107,42,175,324,101,224,293,224,397,112,314,251,2,482,331,210,484,324,297,291,255,101,146,355,443,310,416,8,292,505,87,496,370,5,7,264,348,77,102,478,245,156,114,452,427,518,506,342,181,52,397,203,17,152,101,181,416,221,43,176,461,374,13,469,49,226,212,406,205,388,29,20,447,107,462,258,358,428,192,182,323,277,463,159,430,140,406,432,305,91,41,504,103,402,141,176,15,31,89,364,109,92,355,155,2,468,307,418,250,49,384,399,134,219,416,59,473,409,505,122,166,410,289,278,328,493,180,94,341,491,5,160,465,214,141,79,40,327,362,442,521,365,385,96,480,337,269,315,341,399,381,87,174,128,313,429,259,434,244,495,5,238,416,192,225,275,14,416,446,418,123,469,468,112,253,504,221,502,244,175,92,520,453,234,362,219,220,138,303,430,247,125,447,392,2,27,40,92,127,450,511,438,397,398,46,246,222,212,195,283,329,487,423,378,58,428,168,428,405,358,302,324,153,243,87,336,438,342,327,389,282,165,129,82,454,145,236,456,378,297,127,23,522,133,279,386,85,343,514,301,169,279,251,123,243,74,309,46,29,198,341,373,386,130,282,144,211,69,223,124,194,173,59,141,414,431,406,81,134,298,46,115,188,329,66,337,61,9,330,153,355,524,465,68,41,134,33,460,33,14,187,469,217,256,239,458,523,410,263,45,391,65,337,426,232,86,65,201,249,243,262,352,238,177,54,57,359,230,314,327,410,268,4,90,431,158,253,89,18,176,393,244,362,156,134,28,444,115,325,331,181,338,49,262,361,213,412,66,36,283,216,297,371,53,380,142,2,66,370,34,233,436,255,214,157,423,220,339,516,278,196,259,361,143,63,346,241,465,116,193,55,368,24,246,353,205,28,210,87,236,85,463,349,460,463,379,335,341,405,10,309,168,429,205,177,35,284,310,95,401,362,428,33,320,513,20,293,481,19,396,425,418,272,22,487,502,331,511,361,471,488,282,411,85,213,401,373,444,241,337,375,470,506,140,67,335,56,149,312,433,54,29,417,235,285,15,351,112,366,91,168,86,458,151,304,64,92,87,11,421,393,24,31,189,357,451,377,50,338,233,153,292,423,182,165,72,275,329,191,6,361,477,359,172,69,445,275,82,458,482,353,222,505,326,27,127,237,347,5,60,496,324,106,226,195,414,354,368,76,47,353,506,399,120,202,237,309,472,446,487,471,315,16,87,267,369,28,172,283,372,323,355,149,182,70,501,58,344,324,132,70,525,457,283,183,415,368,63,57,360,334,183,289,285,179,184,464,150,307,431,405,178,221,346,355,80,169,404,46,218,16,161,369,41,71,500,105,373,462,274,151,457,28,55,517,319,252,159,425,514,441,466,349,484,351,313,508,508,345,63,197,342,21,359,360,391,317,117,108,504,18,237,379,267,313,356,322,90,518,456,125,48,300,199,465,320,3,497,303,113,405,228,130,135,401,421,174,451,326,30,27,320,346,400,317,86,114,488,426,507,141,458,181,116,109,60,289,389,435,41,228,358,84,489,100,325,45,426,158,225,293,409,447,267,413,478,210,32,344,237,186,236,295,511,87,105,408,117,321,391,407,333,203,241,498,194,96,23,427,518,487,271,333,454,357,166,149,322,351,463,455,508,466,322,445,267,492,45,75,463,162,181,152,164,122,382,288,25,152,178,52,301,115,461,155,33,54,34,318,175,1,123,405,454,478,259,149,35,461,14,29,469,389,261,285,245,514,283,468,397,381,434,140,138,393,367,64,481,514,518,43,34,464,345,363,153,504,100,479,308,303,356,392,474,506,214,119,332,499,313,244,473,275,247,487,9,472,89,397,75,246,472,297,341,166,223,93,503,289,164,423,39,211,270,4,3,97,141,406,279,411,386,519,524,107,494,46,381,85,186,141,447,279,444,179,153,350,14,127,219,102,457,476,499,303,358,142,56,62,377,9,143,266,59,219,185,98,210,329,161,154,419,311,308,409,286,170,79,511,482,494,124,331,523,274,133,57,381,425,357,501,197,107,415,441,118,515,197,195,170,520,462,228,82,416,365,115,32,339,68,510,78,478,221,128,193,241,163,258,150,182,499,96,109,126,404,236,471,48,517,109,453,276,291,209,525,307,239,159,363,168,237,192,58,71,420,111,301,421,180,70,191,346,125,228,254,210,317,25,236,86,504,226,187,104,461,139,145,412,291,354,79,519,430,197,3,233,65,403,464,162,410,5,81,240,58,156,257,503,124,4,254,123,526,520,266,43,5,55,359,280,497,380,320,69,307,64,437,288,6,486,49,337,177,358,517,393,458,81,282,352,364,233,1,212,401,360,143,289,191,225,467,173,207,475,203,50,109,424,517,243,372,358,322,92,481,165,399,376,202,440,380,70,434,310,414,334,440,376,273,451,379,193,199,424,66,330,433,465,48,137,510,329,491,90,32,242,425,52,24,408,149,524,373,261 });
	findContentChildren(g, s);
}

//https://leetcode.com/problems/132-pattern/
bool find132pattern_slow(vector<int>& nums) 
{
	if (nums.size() < 3)
		return false;
	int i = 0, j = 0, k = 0;
	for (i = 0; i < nums.size() - 2; i++)
	{
		for (j = i + 1; j < nums.size() - 1; j++)
		{
			if (nums[j] < nums[i])
				continue;

			for (k = j + 1; k < nums.size(); k++)
			{
				if (nums[k] < nums[j] && nums[k] > nums[i])
					return true;
			}
		}
	}

	return false;
}

bool find132pattern_ok(vector<int>& nums) {
	int length = nums.size();

	if (length < 3)
		return false;

	stack<int> decreasingStack;

	// Maximum value of the third element in the 132 pattern.
	int maxThirdElement = INT_MIN;

	for (int i = length - 1; i >= 0; i--) {
		int currentNumber = nums[i];

		if (currentNumber < maxThirdElement)
			return true;

		while (!decreasingStack.empty() && decreasingStack.top() < currentNumber) {
			maxThirdElement = decreasingStack.top();
			decreasingStack.pop();
		}

		decreasingStack.push(currentNumber);
	}

	return false; 
}
void testfind132pattern()
{
	vector<int> nums({ -1,3,2,0,1 });
	find132pattern_ok(nums);
}
//https://leetcode.com/problems/circular-array-loop/description/
int getnextpos(vector<int>& nums, int start)
{
	int curpos = nums[start];
	if (curpos < 0)
	{
		curpos = 0-(abs(curpos) % nums.size());
	}
	int next = curpos + start;

	// -2,-1,1,2,2 
	// start = 0, next = 0 + nums[0] = -2
	// next = -2% 5 = 3
	if (next < 0)
	{
		next = nums.size() + next;
	}
	else
	{
		next = next % nums.size();
	}

	return next;
}

bool iscircular(vector<int>& nums, int start)
{
	// 1 2 3 4 5 6 7 8 9 10
	int i = start;
	bool pos = nums[start] > 0 ? true : false;
	int next = getnextpos(nums, start);

	int steps = 1;
	while (steps < nums.size() && next != start)
	{
		if ((nums[next] > 0 && !pos) || (nums[next] < 0 && pos) ||
			(next == start && steps == 1))
			return false;

		next = getnextpos(nums, next);

		steps++;
	}

	return (next == start && steps > 1);
}

bool circularArrayLoop(vector<int>& nums) 
{
	bool ret;
	for (int i = 0; i < nums.size(); i++)
	{
		if (iscircular(nums, i))
			return true;
	}

	return false;
}
 
void testcircularArrayLoop()
{
	vector<int> nums({ -2,-3,-9 });
	circularArrayLoop(nums);
}


//https://leetcode.com/problems/repeated-substring-pattern/description/
bool repeatedSubstringPattern(string &s) 
{
	int sublen = 1;
	int maxsublen = s.size() / 2;
	bool found = false;
	while (sublen <= maxsublen)
	{
		int i = 0;
		string substr(s.substr(0, sublen));
		for (i = sublen; i + sublen <= s.size(); i += sublen)
		{
			if (substr.compare(s.substr(i, sublen)) != 0)
				break;
		}
		if (i >= s.size())
			return true;

		sublen++;
	}

	return false;
}

void testrepeatedSubstringPattern()
{
	string s("abcdabcdabcd");
	repeatedSubstringPattern(s);
}

//https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/description/
int minMoves2(vector<int>& nums) 
{
	if (nums.size() < 2)
		return 0;

	int ret = 0;
	sort(nums.begin(), nums.end());
	int diff = nums[nums.size() - 1] - nums[0];
	if (diff == 0)
		return 0;

	int media = nums[nums.size() / 2];
	int n = nums.size();
	for (int i = 0; i < n/2; i++)
	{
		//ret += abs(nums[i] - media);
		ret += nums[n - 1 - i] - nums[i];
	}
	
	return ret;
}

void testminMoves2()
{
	// 1 10 2 9
	vector<int> n({ 203125577,-349566234,230332704,48321315,66379082,386516853,50986744,-250908656,-425653504,-212123143 });
	minMoves2(n);
}

//https://leetcode.com/problems/island-perimeter/
int getnewPerimeter(vector<vector<int>>& grid, int i, int j)
{
	int perimeter = 4;
	if (i > 0 && grid[i - 1][j] == 1)
		perimeter--;

	if (i < grid.size() - 1 && grid[i + 1][j] == 1)
		perimeter--;

	if (j > 0 && grid[i][j - 1] == 1)
		perimeter--;

	if (j < grid[0].size() - 1 && grid[i][j + 1] == 1)
		perimeter--;

	return perimeter;
}

int islandPerimeter(vector<vector<int>>& grid) 
{
	int ret = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j] == 1)
			{
				ret += getnewPerimeter(grid, i, j);
			}
		}
	}

	return ret;
}

void testislandPerimeter()
{
	vector<vector<int>> grid({ {1,1,1,1},{1,1,1,1} });

	islandPerimeter(grid);
}

//https://leetcode.com/problems/unique-substrings-in-wraparound-string
int getconsecutivechars(string& s, int i)
{
	int consecutivechars = 1;
	char curchar = s[i];
	i++;
	while (i < s.size())
	{
		if ((s[i] == curchar + 1) || (curchar == 'z' && s[i] == 'a'))
		{
			curchar = s[i];
			consecutivechars++;
			i++;
		}
		else
			break;
	}

	return consecutivechars;
}

// abcdeabcdeabcde
// 4 + 3 + 2 + 1
int findSubstringInWraproundString(string &s)
{
	if (s.size() == 1)
		return 1;

	bool hasdup = false;
	set<char> uniques;
	string s2;
	for (auto c : s)
	{
		if (uniques.find(c) != uniques.end())
		{
			hasdup = true;
		}
		else
		{
			uniques.insert(c);
			s2.push_back(c);
		}
	}

	if (s2.size() == 1)
		return 1;

	int ret = s2.size();
	int substr = s2.size();
	int i = 0;
	map<int, list<int>> substrmap;
	while (i < s.size())
	{
		int consecutivechars = getconsecutivechars(s, i);
		
		if (consecutivechars == 1)
		{
			i++;
			continue;
		}

		bool uniquesubstr = true;
		printf("consecutivechars %d\r\n", consecutivechars);
		if (substrmap.find(consecutivechars) == substrmap.end())
		{
			substrmap[consecutivechars] = list<int>();
			substrmap[consecutivechars].push_back(i);
			uniquesubstr = true;
		}
		else
		{
			list<int>::iterator itor = substrmap[consecutivechars].begin();
			
			while (itor != substrmap[consecutivechars].end() && uniquesubstr)
			{
				int idx = *itor, idx2 = i;
				if (s.substr(idx, consecutivechars).compare(s.substr(i, consecutivechars)) == 0)
				{
					uniquesubstr = false;
					break;
				}

				itor++;
			}
		}
		i += consecutivechars;
		if (uniquesubstr)
			ret += consecutivechars * (consecutivechars + 1) / 2 - consecutivechars;
	}

	return ret;
}

void testfindSubstringInWraproundString()
{
	string s("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");

	findSubstringInWraproundString(s);
}

//https://leetcode.com/problems/validate-ip-address/description/
bool checkIpv4(vector<string> &items)
{
	if (items.size() != 4)
		return false;

	for (string item : items)
	{
		if (item.size() == 1)
		{
			if (!(item[0] >= '1' && item[0] <= '9'))
				return false;
		}

		if (item.size() == 2)
		{
			if (!(item[0] >= '1' && item[0] <= '9' && 
				  item[1] >= '0' && item[1] <= '9'))
				return false;
		}

		if (item.size() == 3)
		{
			if ( !((item[0] == '1' && item[1] >= '0' && item[1] <= '9' && item[2] >= '0' && item[2] <= '5') ||
				   (item[0] == '2' && item[1] >= '0' && item[1] <= '5' && item[2] >= '0' && item[2] <= '5')) )
		        return false;
		}
	}

	return true;
}

bool checkIpv6(vector<string>& items)
{
	if (items.size() != 8)
		return false;

	for (string item : items)
	{
		if (item.size() == 0 || item.size() > 4)
			return false;

		for (char c : item)
		{
			if (!( (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
				return false;
		}
	}

	return true;
}

string validIPAddress(string &ip) 
{
	if (ip.size() == 0)
		return "Neither";

	vector<string> items;
	stringstream ss(ip);
	string item;
	int N = ip.size();
	char c0 = ip[0], cn = ip[N - 1];

	if (ip.find(".") != string::npos)
	{
		if (!(c0 >= '1' && c0 <= '9') || 
			!(cn >= '0' && cn <= '9'))
			return "Neither";

		while (getline(ss, item, '.')) {
			items.push_back(item);
		}

		if (checkIpv4(items))
			return "IPv4";

		return "Neither";
	}
	else if (ip.find(":") != string::npos)
	{
		if (!((c0 >= '0' && c0 <= '9') || (c0 >= 'a' && c0 <= 'f') || (c0 >= 'A' && c0 <= 'F')) ||
			!((cn >= '0' && cn <= '9') || (cn >= 'a' && cn <= 'f') || (cn >= 'A' && cn <= 'F')))
			return "Neither";

		while (getline(ss, item, ':')) {
			items.push_back(item);
		}

		if (checkIpv6(items))
				return "IPv6";

		return "Neither";
	}

	return "Neither";
}

void testvalidIPAddress()
{
	string ip(":2001:0db8:85a3:0:0:8A2E:0370:7334:");
	validIPAddress(ip);
}

//https://leetcode.com/problems/implement-rand10-using-rand7/
int rand7()
{
	return 0;
}

int rand10() 
{
	int rand40 = (rand7() - 1) * 7 + rand7();
	return rand40 > 40 ? rand10() : rand40 % 10 + 1;
}

//https://leetcode.com/problems/matchsticks-to-square/description/
// 1 1 1 1 1 1 1 2 3
// 1 1 4 4 6 6 
// 1 4 2 3 2 3 5  -> 1 2 2 3 3 4 5 or 1 2 2 3 3 9
bool makesquaredfs(vector<int>& sidesLength, const vector<int>& matches, int index) {
	if (index == matches.size())
		return sidesLength[0] == sidesLength[1] && sidesLength[1] == sidesLength[2] && sidesLength[2] == sidesLength[3];
	for (int i = 0; i < 4; ++i) {
		sidesLength[i] += matches[index];
		if (makesquaredfs(sidesLength, matches, index + 1))
			return true;
		sidesLength[i] -= matches[index];
	}
	return false;
}
bool makesquare(vector<int>& nums) {
	if (nums.empty()) return false;
	vector<int> sidesLength(4, 0);
	return makesquaredfs(sidesLength, nums, 0);
}

void testmakesquare()
{
	vector<int> m({ 1,1,2,2,2 });
	makesquare(m);
}

//https://leetcode.com/problems/heaters/

int findRadius(vector<int>& houses, vector<int>& heaters)
{
	int radius = 0;
	sort(houses.begin(), houses.end());
	sort(heaters.begin(), heaters.end());

	vector<int> righttoheater(houses.size(), INT_MAX);
	vector<int> lefttoheater(houses.size(), INT_MAX);

	int i = 0, j = 0;
	while (i < houses.size() && j < heaters.size())
	{
		if (houses[i] <= heaters[j])
		{
			righttoheater[i] = heaters[j] - houses[i];
			i++;
		}
		else
		{
			j++;
		}
	}

	i = houses.size() - 1;
	j = heaters.size() - 1;
	while (i >= 0 && j >= 0)
	{
		if (houses[i] >= heaters[j])
		{
			lefttoheater[i] = houses[i] - heaters[j];
			i--;
		}
		else
		{
			j--;
		}
	}

	for (i = 0; i < houses.size(); i++)
	{
		int tmp = std::min(righttoheater[i], lefttoheater[i]);
		if (radius < tmp)
			radius = tmp;
	}

	return radius;
}
void testfindRadius()
{
	vector<int> houses({ 1,2,3,4 });
	vector<int> heaters({ 1,4 });
	findRadius(houses, heaters);
}

//https://leetcode.com/problems/total-hamming-distance/description/
int totalHammingDistance(vector<int>& nums) 
{
	int ret = 0;
	int n = nums.size();
	for (int i = 0; i < 32; i++)
	{
		int oneBits = 0;
		for (int j = 0; j < n; j++)
		{
			if ((nums[j] >> i) & 1)
				oneBits++;
		}

		ret += oneBits * (n - oneBits);
	}

	return ret;
}

void testtotalHammingDistance()
{
	vector<int> nums({ 4,14,2 });
	totalHammingDistance(nums);
}

//https://leetcode.com/problems/generate-random-point-in-a-circle/
class randPointSolution {
public:
	double radius;
	double x_center;
	double y_center;
	randPointSolution(double r, double x, double y) 
	{
		radius = r;
		x_center = x;
		y_center = y;
	}

	vector<double> randPoint()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_real_distribution<> dis(0.0, 1.0);
		double M_PI = 3.1415926;

		// 极坐标方法
		double angle = 2.0 * M_PI * dis(gen);  // 随机角度 [0, 2π]
		double r = radius * std::sqrt(dis(gen));  // 随机半径 [0, radius]

		vector<double>({
			x_center + r * std::cos(angle),
			y_center + r * std::sin(angle) });
	}	
};

void testrandPointSolution()
{
}

//https://leetcode.com/problems/sliding-window-median/description/
// 12 11 10 9 8 7 6 5 4 3 2 1
vector<double> medianSlidingWindow_slow(vector<int>& nums, int k) 
{
	vector<double> ret;
	vector<int> numsk(k, 0);
	numsk.assign(nums.begin(), nums.begin() +k);
	sort(numsk.begin(), numsk.end());

	int i = k;
	bool odd = k % 2 != 0;
	int mid = k / 2;
	if (odd)
	{
		ret.push_back((double)numsk[mid]);
	}
	else
	{
		double median = ((double)numsk[mid - 1] + numsk[mid]) / 2.0;
		ret.push_back(median);
	}

	for (i = k-1; i < nums.size(); i++)
	{
		numsk.assign(nums.begin() + (i - k+1), nums.begin()+(i+1));
		sort(numsk.begin(), numsk.end());
		if (odd)
		{
			ret.push_back((double)numsk[mid]);
		}
		else
		{
			double median = ((double)numsk[mid - 1] + numsk[mid]) / 2.0;
			ret.push_back(median);
		}
	}

	return ret;
}

vector<double> medianSlidingWindow(vector<int>& nums, int k) {
	multiset<int> window(nums.begin(), nums.begin() + k);
	auto mid = next(window.begin(), k / 2);
	vector<double> medians;
	for (int i = k; ; i++) {

		// Push the current median.
		medians.push_back((double(*mid) + *prev(mid, 1 - k % 2)) / 2);

		// If all done, return.
		if (i == nums.size())
			break;

		// Insert nums[i].
		window.insert(nums[i]);
		if (nums[i] < *mid)
			mid--;

		// Erase nums[i-k].
		if (nums[i - k] <= *mid)
			mid++;
		window.erase(window.lower_bound(nums[i - k]));
	}

	return medians;
}

void testmedianSlidingWindow()
{
	vector<int> nums({ 1,2,3,4,5,2,3,1,4,2 });
	int k = 4;

	multiset<int> window(nums.begin(), nums.begin() + k);
	auto mid = next(window.begin(), k / 2);

	medianSlidingWindow(nums, k);
}

//https://leetcode.com/problems/license-key-formatting/description/
string licenseKeyFormatting(string &s, int k) 
{
	string ret;
	int i = 0;
	string tmps;	
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] != '-')
		{
			if (s[i] >= 'a' && s[i] <= 'z')
				tmps.push_back((char)(s[i] - 32));
			else
				tmps.push_back(s[i]);
		}
	}

	if (tmps.size() == 0)
		return ret;

	if (tmps.size() <= k)
		return tmps;

	int firstpart = tmps.size() % k;
	if (firstpart == 0)
		firstpart = k;

	for (i = 0; i < firstpart; i++)
		ret.push_back(tmps[i]);

	ret.push_back('-');
	int tmpk = 0;
	while (i < tmps.size())
	{
		ret.push_back(tmps[i]);
		i++;
		tmpk++;
		if (tmpk == k && i < tmps.size())
		{
			ret.push_back('-');
			tmpk = 0;
		}
	}

	return ret;
}

void testlicenseKeyFormatting()
{
	string s("5F3Z-2e-9-w");
	int k = 4;

	licenseKeyFormatting(s, k);
}

//https://leetcode.com/problems/non-decreasing-subsequences/description/
vector<vector<int>> findSubsequences(vector<int>& nums) 
{
	vector<vector<int>> ret;

	if (nums.size() < 2)
		return ret;

	vector<vector<vector<int>>> sebsequence;
	sebsequence.resize(nums.size());

	int i = 0, j = 0, k = 0;
	for (i = nums.size() - 2; i >= 0; i--)
	{
		int j = i + 1;
		vector<int> samenumseq;
		samenumseq.push_back(nums[i]);
		if (nums[i] == nums[j])
		{
			while (j < nums.size() && nums[i] == nums[j])
			{
				samenumseq.push_back(nums[j]);
				j++;
			}
		}

		if (samenumseq.size() > 1)
		{
			sebsequence[i].push_back(samenumseq);
		}

		while (j < nums.size())
		{
			if (nums[i] <= nums[j])
			{
				if (nums[j - 1] != nums[j])
				{
					vector<int> tmp(samenumseq);
					tmp.push_back(nums[j]);
					sebsequence[i].push_back(tmp);
				}
				for (k = 0; k < sebsequence[j].size(); k++)
				{
					vector<int> tmp(samenumseq);
					tmp.insert(tmp.end(), sebsequence[j][k].begin(), sebsequence[j][k].end());
					sebsequence[i].push_back(tmp);
				}
			}

			j++;
		}
	}

	set<vector<int>>ans;

	for (i = 0; i < sebsequence.size(); i++)
	{
		for (j = 0; j < sebsequence[i].size(); j++)
			ans.insert(sebsequence[i][j]);	
	}

	set<vector<int>>::iterator itor(ans.begin());
	while (itor != ans.end())
	{
		ret.push_back(*itor);
		itor++;			
	}

	return ret;
}

void testfindSubsequences()
{
	// 1
	// 10
	// (9,10)
	// (8,9),/8 9 10/,/8,10/
	// 7,8/7 8 9/ 7 8 9 10/7 8 10/,7,9/7 9 10/7 10
	// 5,7/ 5,(7,8/7 8 9/ 7 8 9 10/7 8 10/,7,9/7 9 10/7 10)/5,(8,9,/8 9 10/,/8,10))/5,9,10/5,10/
	// 5 5/ 5 5 7/ 5 5 7 8 9
	//
	vector<int> nums({ 1,2,3,1,1,1 });
	findSubsequences(nums);
}


//https://leetcode.com/problems/reverse-pairs/description/

int reversePairs(vector<int>& nums)
{
	int ret = 0;
	vector<long long> doublenums(nums.size(), 0);
	int i = 0, j = 0; 
	for (i = 0; i < nums.size(); i++)
	{
		doublenums[i] = (long long)nums[i] * 2;
	}
	
	for (i = 0; i < nums.size()-1; i++)
	{
		for (j = i + 1; j < nums.size(); j++)
		{
			if (nums[i] > doublenums[j])
				ret++;
		}
	}

	return ret;
}

void testreversePairs()
{
	// 1 2 3 4 5
	// 4 8 6 10 2
	// 4 0 2 1 3
	vector<int> nums({ 2,4,3,5,1 });
	reversePairs(nums);
}

//https://leetcode.com/problems/count-and-say/description/
int getconsecutivecharsforRLE(string& ori, int idx)
{
	if (idx >= ori.size())
	{
		return 0;
	}

	char curchar = ori[idx];
	int dupchar = 1;
	idx++;
	while (idx < ori.size())
	{
		if (ori[idx] == curchar)
		{
			dupchar++;
			idx++;
		}
		else
			break;
	}

	return dupchar;
}
string getRLE(string &str)
{
	string ret;
	int idx = 0;
	while (idx < str.size())
	{
		int dupchar = getconsecutivecharsforRLE(str, idx);
		ret.append(std::to_string(dupchar));
		ret.push_back(str[idx]);
		idx += dupchar;
	}

	return ret;
}

string countAndSay(int n) 
{
	string ret("1");
	for (int i = 2; i <= n; i++)
	{
		ret = getRLE(ret);
	}

	return ret;
}

void testcountAndSay()
{
	countAndSay(4);
}

//https://leetcode.com/problems/sort-colors/description/
int sortcolors_helper(vector<int>& nums, int idx, int curcol)
{
	int i = idx, j = 0;
	int colors = 0;
	bool swaped = true;
	while (swaped && i < nums.size())
	{
		swaped = false;
		if (nums[i] == curcol)
		{
			i++;
			swaped = true;
			continue;
		}
		for (j = i + 1; j < nums.size(); j++)
		{
			if (nums[j] == curcol)
			{
				swap(nums[i], nums[j]);
				i++;
				swaped = true;
				break;
			}
		}
	}

	return i;
}

void sortColors(vector<int>& nums) 
{
	int idx = 0;
	for (int i = 0; i <= 2; i++)
	{
		idx = sortcolors_helper(nums, idx, i);
	}
}

void testsortColors()
{
	vector<int> nums({ 2,2,2,1,1,1});
	sortColors(nums);
}

void testsolveSudoku()
{	
	//vector<vector<char>> board({ { '5','3','.','.','7','.','.','.','.' },
	//							 { '6','.','.','1','9','5','.','.','.' },
	//							 { '.','9','8','.','.','.','.','6','.' },
	//							 { '8','.','.','.','6','.','.','.','3' },
	//							 { '4','.','.','8','.','3','.','.','1' },
	//							 { '7','.','.','.','2','.','.','.','6' },
	//							 { '.','6','.','.','.','.','2','8','.' },
	//							 { '.','.','.','4','1','9','.','.','5' },
	//							 { '.','.','.','.','8','.','.','7','9' } });

	//vector<vector<char>> board({ { '.','.','.','.','.','6','.','.','.' },
	//							 { '8','5','7','.','.','4','.','.','.' },
	//							 { '.','.','2','.','.','.','.','.','.' },
	//							 { '.','4','.','.','.','.','.','9','8' },
	//							 { '.','6','.','.','.','.','.','.','.' },
	//							 { '.','.','.','.','.','.','5','4','1' },
	//							 { '.','1','.','.','.','.','.','.','.' },
	//							 { '4','2','5','.','.','.','.','.','5' },
	//							 { '.','.','.','6','.','.','.','.','.' } });

	vector<vector<char>> board({ { '.', '.', '.', '.', '.', '.', '.', '.', '.' },
		{ '.','9','.','.','1','.','.','3','.' },
		{ '.','.','6','.','2','.','7','.','.' },
		{ '.','.','.','3','.','4','.','.','.' },
		{ '2','1','.','.','.','.','.','9','8' },
		{ '.','.','.','.','.','.','.','.','.' },
		{ '.','.','2','5','.','6','4','.','.' },
		{ '.','8','.','.','.','.','.','1','.' },
		{ '.','.','.','.','.','.','.','.','.' } });
	//
	solveSudoku(board);
}


//https://leetcode.com/problems/sort-list/
ListNode* sortList(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return head;

	vector<ListNode*> listvector;
	ListNode* nodeidx = head;
	while (nodeidx != nullptr)
	{
		listvector.push_back(nodeidx);
		nodeidx = nodeidx->next;
	}

	std::sort(listvector.begin(), listvector.end(),
		[&](ListNode* a, ListNode* b)
		{
			return a->val < b->val;
		});

	head = listvector[0];
	nodeidx = head;
	for (int i = 1; i < listvector.size(); i++)
	{
		nodeidx->next = listvector[i];
		nodeidx = nodeidx->next;
	}

	nodeidx->next = nullptr;

	return head;
}

void testsortlist()
{
	//vector<int> n({ 3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0 });
	vector<int> n({ 6,3, 0, 2, });
	ListNode* l = createListNode(n);
	sortList(l);
}

// https://leetcode.com/problems/jump-game-ii/
void jump_helper(vector<int>& nums, int pos, vector<int>& nums_passed, vector<int> nums_on_path, int& last_jump_at_pos, int total_jum, int& min_jump)
{
	if (total_jum >= min_jump && pos < nums.size() - 1)
	{
		for (int each = 0; each < nums_on_path.size(); each++)
		{
			nums_passed[nums_on_path[each]] = total_jum;
		}

		return;
	}

	if (total_jum + 1 == min_jump && nums[pos] + pos < nums.size() - 1)
	{
		for (int each = 0; each < nums_on_path.size(); each++)
		{
			nums_passed[nums_on_path[each]] = total_jum + 1;
		}
		return;
	}

	if (pos >= nums.size() - 1 || nums[pos] + pos >= nums.size() - 1)
	{
		if (pos < nums.size() - 1 && nums[pos] + pos >= nums.size() - 1)
		{
			total_jum++;
			nums_on_path.push_back(pos);
		}

		if (total_jum <= min_jump)
		{
			min_jump = total_jum;

			last_jump_at_pos = pos;
		}

		for (int each = 0; each < nums_on_path.size(); each++)
		{
			nums_passed[nums_on_path[each]] = min_jump;
		}

		return;
	}

	vector<int> nums_on_path_tmp(nums_on_path);
	nums_on_path_tmp.push_back(pos);

	for (int i = nums[pos]; i >= 1; i--)
	{
		if (nums_passed[pos] <= total_jum)
			continue;

		jump_helper(nums, pos + i, nums_passed, nums_on_path_tmp, last_jump_at_pos, total_jum + 1, min_jump);
	}
}

int jump_slow(vector<int>& nums)
{
	if (nums.size() == 1)
		return 0;

	if (nums[0] >= nums.size())
		return 1;

	vector<int> nums_passed(nums.size(), INT_MAX);

	int min_jump = INT_MAX;
	int last_jump_at_pos = INT_MAX;
	vector<int> nums_on_path;
	for (int i = 1; i <= nums[0]; i++)
	{
		nums_on_path.push_back(0);
		jump_helper(nums, i, nums_passed, nums_on_path, last_jump_at_pos, 1, min_jump);
		nums_on_path.clear();
	}

	return min_jump;
}

int jump(vector<int>& nums) {
	int n = nums.size(), i = 0, ans = 0;
	for (int i = 1; i < n; i++)
		nums[i] = max(i + nums[i], nums[i - 1]); //从 [1] 开始，nums[i] 保存的是从 i-1 与 i 两者中能够 jump 的最远距离

	while (i < n - 1) {
		ans++;
		i = nums[i];
	}
	return ans;
}

void testjump()
{
	vector<int> nums({ 5, 2, 1, 10, 1, 1, 1, 1 });
	jump(nums);

}


//https://leetcode.com/problems/length-of-last-word/description/
int lengthOfLastWord(string s) 
{
	int n = s.size();
	int len = 0;
	int sstart = 0, send = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (s[i] == ' ')
			continue;
		int j = i;

		for (; j >= 0 && s[j] != ' '; j--);

		return i - j;
	}

	return 0;
}

void testlengthOfLastWord()
{
	string s("  a   ");
	lengthOfLastWord(s);
}



//https://leetcode.com/problems/unique-paths-ii/description/
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
{
	int ret = 0;
	if (obstacleGrid[0][0] == 1)
		return 0;

	int i = 0;
	int blockrow = obstacleGrid[0].size(), blockcol = obstacleGrid.size();
	for (; i < obstacleGrid[0].size(); i++)
	{
		if (obstacleGrid[0][i] == 1)
		{
			blockrow = i;
			break;
		}
	}
	for (i = 0; i < obstacleGrid.size(); i++)
	{
		if (obstacleGrid[i][0] == 1)
		{
			blockcol = i;
			break;
		}
	}

	vector<int> aboveRow(obstacleGrid[0].size(), 1);
	if (blockrow < obstacleGrid[0].size())
	{
		for (i = blockrow; i < obstacleGrid[0].size(); i++)
			aboveRow[i] = 0;
	}

	for (i = 1; i < obstacleGrid.size(); i++)
	{
		vector<int> curRow(obstacleGrid[0].size(), 1);
		if (i >= blockcol)
			curRow[0] = 0;

		for (int j = 1; j < obstacleGrid[0].size(); j++)
		{
			if (obstacleGrid[i][j] == 1)
				curRow[j] = 0;
			else
				curRow[j] = curRow[j - 1] + aboveRow[j];
		}

		aboveRow = curRow;
	}

	return aboveRow[obstacleGrid[0].size() - 1];
}


void testuniquePathsWithObstacles()
{
	vector<vector<int>> obstacleGrid({ { 1,0 }, });
	uniquePathsWithObstacles(obstacleGrid);
}

//https://leetcode.com/problems/minimum-path-sum/description/
int minPathSum_helper(vector<vector<int>>& grid, int r, int c, int sumonpath, int & curminpath, vector<vector<int>> &minpath_grid)
{
	if (sumonpath >= curminpath)
	{
		minpath_grid[r][c] = sumonpath;
		return curminpath;
	}

	if (r == grid.size() - 1 && c == grid[0].size() - 1)
	{
		if (minpath_grid[grid.size() - 1][grid[0].size() - 1] > sumonpath)
			minpath_grid[grid.size() - 1][grid[0].size() - 1] = sumonpath;

		return sumonpath;
	}

	int minpath_r = INT_MAX, minpath_d = INT_MAX;
	if (c < grid[0].size()-1 && sumonpath + grid[r][c + 1] < curminpath)
		minpath_r = minPathSum_helper(grid, r, c + 1, sumonpath + grid[r][c+1], curminpath, minpath_grid);

	if (r < grid.size()-1 && sumonpath + grid[r + 1][c] < curminpath)
		minpath_d = minPathSum_helper(grid, r + 1, c, sumonpath + grid[r+1][c], curminpath, minpath_grid);

	curminpath = min(min(minpath_r, minpath_d), curminpath);
	minpath_grid[r][c] = curminpath;
	return curminpath;
}

int minPathSum(vector<vector<int>>& grid) 
{
	int curminpath = INT_MAX;
	vector<vector<int>> minpath_grid;
	int rows = grid.size(), columns = grid[0].size();
	for (int i = 0; i < rows; i++)
		minpath_grid.push_back(vector<int>(columns, INT_MAX));
	
	minpath_grid[rows - 1][columns - 1] = grid[rows - 1][columns - 1];
	for (int r = rows - 1; r >= 0; r--)
	{
		for (int c = columns - 1; c >= 0; c--)
		{
			if (r < rows - 1 && c < columns - 1)
			{
				minpath_grid[r][c] = grid[r][c] + min(minpath_grid[r + 1][c], minpath_grid[r][c + 1]);
			}
			else if (r < rows - 1)
			{
				minpath_grid[r][c] = grid[r][c] + minpath_grid[r + 1][c];
			}
			else if (c < columns -1)
			{
				minpath_grid[r][c] = grid[r][c] + minpath_grid[r ][c+1];
			}
			else
			{
				minpath_grid[r][c] = grid[r][c];
			}

		}
	}
	
	return minpath_grid[0][0];
}

void testminPathSum()
{
	vector<vector<int>> grid({ { 1, 3, 1 }, 
							   { 1, 5, 1 }, 
							   { 4, 2, 1  }
							});
	minPathSum(grid);
}

//https://leetcode.com/problems/combinations/description/
void combine_helper(int n, int currentN, int k, int currentK, vector<int> curcombine, vector<vector<int>> &totalcombines)
{
	if (currentK == k)
	{
		totalcombines.push_back(curcombine);
		return;
	}

	int i = currentN + 1;
	for (; i <= n-(k-currentK)+1; i++)
	{
		vector<int> tmp_curcombine(curcombine);
		tmp_curcombine.push_back(i);
		combine_helper(n, i, k, currentK + 1, tmp_curcombine, totalcombines);
	}
}
//1 2 3 4 5 6 7
// 1234 1235 1236 1237 
// 1245 1246 1247
// 1256 1257

vector<vector<int>> combine(int n, int k) 
{
	vector<vector<int>> totalcombines;
	for (int i = 1; i <= n - k+1; i++)
	{
		vector<int> curcombine;
		curcombine.push_back(i);
		combine_helper(n, i, k, 1, curcombine, totalcombines);
	}

	return totalcombines;
}

void testcombine()
{
	combine(7, 4);
}

//https://leetcode.com/problems/plus-one/description/
vector<int> plusOne(vector<int>& digits) 
{
	int i = 0;
	bool carry = true;	
	for (i = 0; i < digits.size(); i++)
	{
		if (digits[i] != 9)
			carry = false;
	}
	if (carry)
	{
		vector<int> ret(digits.size() + 1, 0);
		ret[0] = 1;
		return ret;
	}

	for (int i = digits.size() - 1; i >= 0; i--)
	{
		if (digits[i] == 9)
		{
			digits[i] = 0;
			carry = true;
		}
		else
		{
			digits[i]++;
			carry = false;
		}

		if (!carry)
			break;
	}

	return digits;
}

void testplusOne()
{
	vector<int> d({ 2,9,9, 9,9,});
	plusOne(d);
}


//https://leetcode.com/problems/word-search/description/
// 'A','B','C','E' 
// 'S','F','E','S' 
// 'A','D','E','E' 
// ABCESEEEFS

//{ 'A','A','A','A','A','A' },
//{ 'A','A','A','A','A','A' },
//{ 'A','A','A','A','A','A' },
//{ 'A','A','A','A','A','A' },
//{ 'A','A','A','A','A','A' },
//{ 'A','A','A','A','A','A' }
//AAAAAAAAAAAAAAB
bool exist_helper(vector<vector<char>>& board, string &word, int r, int c, int wordidx, set<pair<int, int>> &pointsonpath)
{
	if (wordidx == word.size())
		return true;

	pair<int, int> curpoint(r, c);

	if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != word[wordidx])
		return false;

	bool doesexist = false;	
	char tmp = board[r][c];
	board[r][c] = '0';
	
	//if (r > 0 && board[r - 1][c] == word[wordidx + 1])
	{
		doesexist = exist_helper(board, word, r - 1, c, wordidx + 1, pointsonpath);
		if (doesexist)
			return true;
	}
	
	//if (r < board.size()-1 && board[r + 1][c] == word[wordidx + 1])
	{
		doesexist = exist_helper(board, word, r + 1, c, wordidx + 1, pointsonpath);
		if (doesexist)
			return true;
	}

	//if (c > 0 && board[r][c - 1] == word[wordidx + 1])
	{
		doesexist = exist_helper(board, word, r, c - 1, wordidx + 1, pointsonpath);
		if (doesexist)
			return true;
	}

	//if (c < board[0].size()-1 && board[r][c + 1] == word[wordidx + 1])
	{
		doesexist = exist_helper(board, word, r, c + 1, wordidx + 1, pointsonpath);		
	}

	board[r][c] = tmp;

	return doesexist;
}

bool exist(vector<vector<char>>& board, string word) 
{
	vector<pair<int, int>> startpoints;
	int i = 0, j = 0;
	for (i = 0; i < board.size(); i++)
	{
		for (j = 0; j < board[0].size(); j++)
		{
			if (board[i][j] == word[0])
				startpoints.push_back(pair<int, int>(i, j));
		}
	}

	for (i = 0; i < startpoints.size(); i++)
	{
		int r = startpoints[i].first;
		int c = startpoints[i].second;

		set<pair<int, int>> pointsonpath;		
		if (exist_helper(board, word, r, c, 0, pointsonpath))
			return true;
	}

	return false;
}

bool exist_ok(vector<vector<char>>& board, string word) {
	int m = board.size();
	int n = board[0].size();

	auto backtrack = [&](int i, int j, int k, auto& backtrack) -> bool {
		if (k == word.length()) {
			return true;
		}
		if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[k]) {
			return false;
		}

		char temp = board[i][j];
		board[i][j] = '\0';

		if (backtrack(i + 1, j, k + 1, backtrack) || backtrack(i - 1, j, k + 1, backtrack) ||
			backtrack(i, j + 1, k + 1, backtrack) || backtrack(i, j - 1, k + 1, backtrack)) {
			return true;
		}

		board[i][j] = temp;
		return false;
		};

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == 1 && j == 3)
			{
				int k = 0;
				k++;
			}
			if (backtrack(i, j, 0, backtrack)) {
				return true;
			}
		}
	}
	return false;
}



void testexist()
{
	//vector<vector<char>> board({ {'A','B','C','E'},
	//							 {'S','F','E','S'},
	//							 {'A','D','E','E'} });	
	//string s("ABCESEEEFS");

	vector<vector<char>> board({ {'A','B','C','E'},
								 {'S','F','C','S'},
								 {'A','D','E','E'} });	
	string s("SEE");	


	//vector<vector<char>> board({ 
	//					       { 'A','A','A','A','A','A' },
	//						   { 'A','A','A','A','A','A' },
	//						   { 'A','A','A','A','A','A' },
	//						   { 'A','A','A','A','A','A' },
	//						   { 'A','A','A','A','A','A' },
	//						   { 'A','A','A','A','A','A' } });
	//string s("AAAAAAAAAAAAAAB");

	exist(board, s);
}
	
//https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

int getDuplicates(vector<int>& nums, int idx)
{
	int dup = 1;
	for (int i = idx + 1; i < nums.size(); i++)
	{
		if (nums[i] == nums[idx])
			dup++;
		else
			break;
	}

	return dup;
}

int removeDuplicates(vector<int>& nums) 
{
	typedef struct dupinfo
	{
		int num;
		int idx;
		int dups;
    } dupinfo_s;

	int i = 0;
	vector<dupinfo_s> dupinfolist;
	int actualsize = 0;
	while (i < nums.size())
	{
		dupinfo_s dupinfo;
		dupinfo.num = nums[i];
		dupinfo.idx = i;
		dupinfo.dups = getDuplicates(nums, i);
		if (dupinfo.dups >= 2)
			actualsize += 2;
		else
			actualsize += dupinfo.dups;

		i += dupinfo.dups;

		dupinfolist.push_back(dupinfo);		
	}

	int idx = 0;
	for (i = 0; i < dupinfolist.size(); i++)
	{
		nums[idx++] = dupinfolist[i].num;
		if (dupinfolist[i].dups >= 2)
		{
			nums[idx++] = dupinfolist[i].num;
		}
	}

	return actualsize;
}

void testremoveDuplicates()
{
	vector<int> nums({ 0,0,1,1,1,1,2,3,3});

	removeDuplicates(nums);
}

//https://leetcode.com/problems/edit-distance/description/
//https://blog.csdn.net/Sxiaocai/article/details/141192289
//https://cloud.tencent.com/developer/article/1810724
int minDistance(string word1, string word2) 
{
	const int m = word1.length();//first word length
	const int n = word2.length();//second word length
	// dp[i][j] := min # of operations to convert word1[0..i) to word2[0..j)
	vector<vector<int>> dp(m + 1, vector<int>(n + 1));

	//初始化第 [0]列，dp[i][0] 表示将一个空字符串转换成 word1 的[0, i] 个字符所需的操作数，即字符串的长度
	for (int i = 1; i <= m; ++i)
		dp[i][0] = i;
	//初始化第 [0] 行, dp[0][j] 表示将一个空字符串转换成 word2 的[0, j] 个字符所需的操作数，即字符串的长度
	for (int j = 1; j <= n; ++j)
		dp[0][j] = j;

	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
			if (word1[i - 1] == word2[j - 1])//same characters
				dp[i][j] = dp[i - 1][j - 1];//no operation
			else
								 //replace       //delete        //insert
				dp[i][j] = min({ dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1] }) + 1;
	
	return dp[m][n];
}
void testminDistance()
{
	string w1("minDistance"), w2("distance");
	minDistance(w1, w2);
}

//https://leetcode.com/problems/subsets-ii/description/
bool issubsetdup(vector<int>& onesubset, vector<vector<int>>& subsets)
{
	for (int i = 0; i < subsets.size(); i++)
	{
		int checkinglen = min(onesubset.size(), subsets[i].size());
		bool isdup = true;
		for (int j = 0; j < checkinglen; j++)
		{
			if (onesubset[j] != subsets[i][j])
			{
				isdup = false;
				break;
			}
		}

		if (isdup)
			return true;
	}

	return false;
}

void subsetsWithDup_helper(vector<int>& nums, int startidx, int leftlen, vector<int> onesubset, vector<vector<int>> & subsets)
{
	if (leftlen == 0)
	{
		if (!issubsetdup(onesubset, subsets))
		{
			subsets.push_back(onesubset);
		}
		return;
	}

	for (int i = startidx; i <= nums.size() - leftlen; i++)
	{
		vector<int> tmp_onesubset(onesubset);
		tmp_onesubset.push_back(nums[i]);
		subsetsWithDup_helper(nums, i + 1, leftlen - 1, tmp_onesubset, subsets);
	}
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) 
{
	vector<vector<int>> ret;
	ret.push_back(vector<int>());
	if (nums.size() == 0)
		return ret;

	int subsetlen = 1;
	sort(nums.begin(), nums.end());

	while (subsetlen <= nums.size())
	{
		vector<vector<int>> subsets;
		for (int i = 0; i <= nums.size()- subsetlen; i++)
		{
			if (i > 0 && nums[i - 1] == nums[i])
				continue;

			vector<int> onesubset;
			onesubset.push_back(nums[i]);
			subsetsWithDup_helper(nums, i+1, subsetlen-1, onesubset, subsets);
		}

		ret.insert(ret.end(), subsets.begin(), subsets.end());
		subsetlen++;
	}

	return ret;
}

void testsubsetsWithDup()
{
	vector<int> nums({ 1,2,2,});
	subsetsWithDup(nums);
}

//https://leetcode.com/problems/largest-rectangle-in-histogram/description/

int getarea(vector<int>& heights, int startidx, int & areaheight, int &areaidx, int &mostrightidx)
{
	int maxarearightidx = startidx;
	int maxarea = heights[startidx];
	int maxareeheight = heights[startidx];
	
	int curareaheight = heights[startidx];
	int curarearightidx = startidx;
	int curarea = heights[startidx];

	int i = 0;
	for (i = startidx + 1; i < heights.size(); i++)
	{
		if (heights[i] == 0)
			break;

		if (curareaheight > heights[i])
		{
			curareaheight = heights[i];
			curarearightidx = i;
		}

		curarea = (i - startidx + 1) * curareaheight;
		if (curarea > maxarea)
		{
			maxarearightidx = i;
			maxarea = curarea;
			//int tmp = startidx+1;
			//while (tmp < i)
			//{
			//	if (heights[tmp] == curareaheight)
			//	{
			//		curarearightidx = tmp;
			//		break;
			//	}
			//	tmp++;
			//}
			maxareeheight = curareaheight;
		}
	}
	curarea = (i - startidx) * curareaheight;
	maxarea = (maxarearightidx - startidx + 1) * maxareeheight;
	mostrightidx = i;
	if (curarea >= maxarea)
	{
		areaidx = curarearightidx + 1;
		return curarea;
	}
	else
	{
		areaidx = maxarearightidx + 1;
		return maxarea;
	}
}

int largestRectangleArea_error(vector<int>& heights) 
{
	if (heights.size() == 1)
		return heights[0];

	int nextidx = 0, mostrightidx = 0, areaheight = 0;
	int area = getarea(heights, 0, areaheight, nextidx, mostrightidx);
	
	for (int i = nextidx; i < heights.size();)
	{
		if (heights[i] == 0)
		{
			i++;
			continue;
		}

		int curarea = getarea(heights, i, areaheight, nextidx, mostrightidx);
		if (curarea > area)
		{
			area = curarea;
		}
		i = nextidx;
	}

	return area;
}
// https://cloud.tencent.com/developer/article/2313946  
// 用单调栈来解决, 栈底 -> 栈顶 是递减的，则称为单调递减栈，反之则为单调递增栈。
// 单调栈的作用是可以在 O(1) 的时间内获取当前元素左边第一个比它小的元素和右边第一个比它小的元素。对于本题来说，我们需要获取每个柱子左右两边第一个比它小的柱子的位置，这样就可以计算出以该柱子为高的矩形的宽度，从而计算出面积。
// 1,4,2,3,5 -- 栈顶是待解决的元素
// 
// 4 5 3 5  
// 
//   2    
int largestRectangleArea(vector<int>& heights)
{
	vector<int> areas(heights.size() - 1);
	stack<int> st;
	st.push(0);

	for (int i = 1; i < heights.size(); i++)
	{
		if (!st.empty() && heights[i] > heights[st.top()])
		{
			while (!st.empty() && heights[st.top()] < heights[i])
			{
				areas[st.top()] = i;
				st.pop();
			}
			st.push(i);
		}
		else
		{
			st.push(i);
		}
	}

	return 0;
	
}

int largestRectangleArea_ok(vector<int>& heights) {
	int n = heights.size();
	vector<int> left(n), right(n);
	stack<int> st;

	// Nearest Smaller to Left
	for (int i = 0; i < n; i++) {
		while (!st.empty() && heights[st.top()] >= heights[i])
			st.pop();

		left[i] = st.empty() ? -1 : st.top();
		st.push(i);
	}

	while (!st.empty()) 
		st.pop();

	// Nearest Smaller to Right
	for (int i = n - 1; i >= 0; i--) {
		while (!st.empty() && heights[st.top()] >= heights[i]) st.pop();
		right[i] = st.empty() ? n : st.top();
		st.push(i);
	}

	int maxArea = 0;
	for (int i = 0; i < n; i++) {
		int width = right[i] - left[i] - 1;
		maxArea = max(maxArea, heights[i] * width);
	}
	return maxArea;
}

void testlargestRectangleArea()
{
	vector<int> heights({ 3,6,5, });//7,4,8,1,0 });
	largestRectangleArea_ok(heights);
}

//https://leetcode.com/problems/decode-ways/description/
void numDecodings_helper(string& s, int idx, int &result, vector<int> stepsonpath, bool onehop)
{
	if (idx > s.size() || s[idx] == '0')
		return;

	if (idx == s.size())
	{
		result += 1;
		return;
	}
	
	if (s[idx] == '1')
	{
		numDecodings_helper(s, idx + 1, result, stepsonpath, true);
		stepsonpath.push_back(1);
		if (idx + 1 < s.size())
		{
			stepsonpath.pop_back();
			stepsonpath.push_back(2);
			numDecodings_helper(s, idx + 2, result, stepsonpath, false);
		}
	}
	else if (s[idx] == '2')
	{
		stepsonpath.push_back(1);
		numDecodings_helper(s, idx + 1, result, stepsonpath, true);
		if (idx + 1 < s.size() && s[idx + 1] <= '6')
		{
			stepsonpath.pop_back();
			stepsonpath.push_back(2);
			numDecodings_helper(s, idx + 2, result, stepsonpath, false);
		}
	}
	else
	{
		stepsonpath.push_back(1);
		numDecodings_helper(s, idx + 1, result, stepsonpath, true);
	}
}

int numDecodings(string &s) 
{
	int i = 0;
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] < '1' || s[i] > '9')
			return 0;
	}

	int result = 0;
	vector<int> stepsonpath;
	
	numDecodings_helper(s, 0, result, stepsonpath, true);
	return result;
}

void testnumDecodings()
{
	string s("1111");
	numDecodings(s);
}
// 1 1 1 1 
// 1 1 2
// 1 2 1
// 2 1 1
// 2 2
// 

//https://leetcode.com/problems/unique-binary-search-trees-ii/description/
bool isAllNodeSet(int n, vector<bool>& nmarks)
{
	for (int i = 1; i <= n; i++)
	{
		if (nmarks[i] == 0)
			return false;
	}

	return true;
}

// 68453127
void generateTrees2_helper(int n, TreeNode* root, TreeNode* parent, bool isLeft, vector<bool> nmarks, vector<TreeNode*> &result)
{
	int start = 0, end = 0;

	if (isLeft)
	{
		start = 1;
		end = parent->val - 1;		
	}
	else
	{
		start = parent->val + 1;
		end = n;
	}

	for (int i = start; i <= end; i++)
	{
		if (nmarks[i])
			continue;

		TreeNode* node = new TreeNode(i);
		if (isLeft)
			parent->left = node;
		else
			parent->right = node;

		vector<bool> tmp_nmarks(nmarks);
		tmp_nmarks[i] = true;
		if (isAllNodeSet(n, nmarks))
		{
			result.push_back(root);
			return;
		}

		generateTrees2_helper(n, root, node, true, tmp_nmarks, result);
		generateTrees2_helper(n, root, node, false, tmp_nmarks, result);
	}
}

vector<TreeNode*> generateTrees2(int n) {
	vector<bool> nmarks(n+1, 0);
	vector<TreeNode*> result;
	for (int i = 1; i <= n; i++)
	{
		nmarks[i] = true;
		TreeNode* root = new TreeNode(i);

		generateTrees2_helper(n, root, root, true, nmarks, result);
		generateTrees2_helper(n, root, root, false, nmarks, result);
		nmarks.clear();
	}

	return result;
}

void testgenerateTrees2()
{
	generateTrees2(3);
}

//https://leetcode.com/problems/gray-code/description/
vector<int> grayCode(int n) 
{
	vector<int> ret;

	return ret;
}

void testgrayCode()
{
	grayCode(2);
}


//https://leetcode.com/problems/recover-binary-search-tree/description/
class recoverTreeFast {
public:
	TreeNode* prev = NULL;
	TreeNode* first = NULL;
	TreeNode* second = NULL;

	void inorder(TreeNode* root) {
		if (root == NULL) return;

		inorder(root->left);

		if (prev != NULL && prev->val > root->val) {
			if (first == NULL) {
				first = prev;
			}
			second = root;
		}
		prev = root;
		inorder(root->right);
	}

	void recoverTree(TreeNode* root) {
		inorder(root);

		int temp = first->val;
		first->val = second->val;
		second->val = temp;
	}
};

void recoverTree_helper(TreeNode* node)
{
	if (node == NULL || (node->left == NULL && node->right == NULL))
		return;

	bool isrecovered = false;
	if (node->left)
	{
		list<TreeNode*> nodeList;
		nodeList.push_back(node->left);
		TreeNode *maxvalvode = node;

		while (nodeList.size() > 0)
		{
			TreeNode *ptmpnode = nodeList.front();
			nodeList.pop_front();
			if (ptmpnode->val >= maxvalvode->val)
				maxvalvode = ptmpnode;

			if (ptmpnode->left)
				nodeList.push_back(ptmpnode->left);

			if (ptmpnode->right)
				nodeList.push_back(ptmpnode->right);
		}

		if (maxvalvode != node)
		{
			std::swap(node->val, maxvalvode->val);
			isrecovered = true;

		}
	}
	if (node->right)
	{
		list<TreeNode*> nodeList;
		nodeList.push_back(node->right);
		TreeNode* minvalnode = node;

		while (nodeList.size() > 0)
		{
			TreeNode* ptmpnode = nodeList.front();
			nodeList.pop_front();
			if (ptmpnode->val < minvalnode->val)
				minvalnode = ptmpnode;

			if (ptmpnode->left)
				nodeList.push_back(ptmpnode->left);

			if (ptmpnode->right)
				nodeList.push_back(ptmpnode->right);
		}

		if (minvalnode != node)
		{
			std::swap(node->val, minvalnode->val);
			isrecovered = true;

		}
	}
	if (isrecovered)
	{
		recoverTree_helper(node);
	}
	else
	{
		if (node->left)
			recoverTree_helper(node->left);

		if (node->right)
			recoverTree_helper(node->right);
	}
}

void recoverTree(TreeNode* root) 
{
	recoverTree_helper(root);
}

void testrecoverTree()
{
	//vector<int> v1({ 1,3,INT_MIN, INT_MIN, 2});
	vector<int> v1({2,3,1});
	TreeNode** t1 = createTree(v1);
	//recoverTree(*t1);
	recoverTreeFast s;
	s.recoverTree(*t1);
}

//https://leetcode.com/problems/find-peak-element/description/
int findPeakElement(vector<int>& nums) 
{
	if (nums.size() <= 1)
		return 0;

	if (nums[0] > nums[1])
		return 0;

	int n = nums.size();
	if (nums[n - 1] > nums[n - 2])
		return n - 1;

	int i = 0;
	for (i = 1; i < nums.size()-1; i++)
	{
		if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
			return i;
	}

	return 0;
}

void testfindPeakElement()
{
	vector<int> nums({ 1, 2, 1, 3, 5, 6, 4 });
	findPeakElement(nums);
}


//https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
int maxProfit(vector<int>& prices)
{
	vector<int> profits(prices.size() - 1);
	int maxprofit = INT_MIN, maxprices = INT_MIN;
	int minprices = prices[0];
	for (int i = 1; i < prices.size(); i++)
	{
		if (prices[i] < minprices)
		{
			minprices = prices[i];
		}
		else if (prices[i] - minprices > maxprofit)
		{
			maxprofit = prices[i] - minprices;
		}
	}

	if (maxprofit < 0)
		return 0;

	return maxprofit;
}


void testmaxprofit()
{
	vector<int> p({ 7,6,8,4,3,1,6 });
	maxProfit(p);
}

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
int maxProfit_cooldown_policty1(vector<int>& prices)
{
	int buy_prices = prices[0];
	int profit = 0;
	int i = 1;
	while (i < prices.size())
	{
		if (prices[i] > buy_prices)
		{
			profit += prices[i] - buy_prices;
			i += 2;
			if (i < prices.size())
				buy_prices = prices[i];
		}
		else
			i++;
	}

	return profit;
}

int findmaxprofit(vector<int>& prices, int idx, int& sellday)
{
	return 0;
}

int maxProfit_cooldown_policty2(vector<int>& prices)
{
	int buy_prices = prices[0];
	int profit = 0;
	int i = 1;
	while (i < prices.size())
	{
		if (prices[i] > buy_prices)
		{
			profit += prices[i] - buy_prices;
			i += 2;
			if (i < prices.size())
				buy_prices = prices[i];
		}
		else
			i++;
	}

	return profit;
}


int maxProfit_cooldown(vector<int>& prices) 
{
	if (prices.size() == 0)
		return 0;

	return maxProfit_cooldown_policty1(prices);	
}

void testmaxProfit_cooldown()
{
	vector<int> p({ 1,2,4 });
	maxProfit_cooldown(p);
}

//https://leetcode.com/problems/maximal-square/description/
int maximalSquare_helper(vector<vector<char>>& matrix, int r, int c)
{
	int squarelen = 1;
	
	while (r + squarelen <= matrix.size() && c + squarelen <= matrix[0].size())
	{
		int ridx = r, cidx = c;
		int currow = r + squarelen - 1;
		int curcol = c + squarelen - 1;

		while (ridx <= currow && ridx < matrix.size() &&
 			   cidx <= curcol && cidx < matrix[0].size())
		{
			if (matrix[ridx][curcol] == '0' || matrix[currow][cidx] == '0')
				return squarelen-1;
			ridx++;
			cidx++;
		}

		squarelen++;
	}

	return squarelen-1;
}
bool ifoverloap(vector<vector<char>>& matrix, int r, int c, int squarelen)
{
	return true;
}

int maximalSquare(vector<vector<char>>& matrix) 
{
	int r = 0;
	int maxsquarelen = 0;
	int Line = matrix.size(), Col = matrix[0].size();
	while (r < Line)
	{
		int c = 0;
		while (c < Col)
		{
			if (matrix[r][c] == '1')
			{
				if (r == 16)// && c == 8)
				{
					int i = 0;
					i++;
				}

				int squarelen = maximalSquare_helper(matrix, r, c);

				if (maxsquarelen < squarelen)
					maxsquarelen = squarelen;
				if (r + squarelen < Line && c + squarelen < Col && 
					matrix[r+squarelen][c+squarelen] == '1' && 
					matrix[r + squarelen-1][c + squarelen] == '1' && 
					matrix[r + squarelen][c + squarelen-1] == '1')
				{
					// row bakc off, line back off
					int rbk = r + squarelen, cbk = c + squarelen;
					while (rbk >= r && matrix[rbk][c + squarelen] == '1')
					{
						rbk--;
					}
					while (cbk >= c && matrix[r + squarelen][cbk] == '1')
					{
						cbk--;
					}
					r = rbk + 1;
					c = cbk + 1;
				}
				else
				{
					if (c + squarelen < Col && Col - (c + squarelen) >= squarelen)
					{
						c += squarelen;
					}
					else
					{
						c = 0;
						r += squarelen;

						if (r >= Line || (matrix.size() - r) <= squarelen)
							break;
					}
				}
			}
			else
			{
				c++;
			}
		}
		if (r + maxsquarelen >= Line)
			break;

		r++;
	}

	return maxsquarelen* maxsquarelen;
}


// 
//int maximalSquare_helper(vector<vector<char>>& matrix, int r, int c)
//{
//	int squarelen = 1;
//
//	while (r + squarelen <= matrix.size() && c + squarelen <= matrix[0].size())
//	{
//		int ridx = r, cidx = c;
//		int currow = r + squarelen - 1;
//		int curcol = c + squarelen - 1;
//
//		while (ridx <= currow && ridx < matrix.size() &&
//			cidx <= curcol && cidx < matrix[0].size())
//		{
//			if (matrix[ridx][curcol] == '0' || matrix[currow][cidx] == '0')
//				return squarelen - 1;
//			ridx++;
//			cidx++;
//		}
//
//		squarelen++;
//	}
//
//	return squarelen - 1;
//}
//
//int maximalSquare(vector<vector<char>>& matrix)
//{
//	int r = 0;
//	int maxsquarelen = 0;
//	while (r < matrix.size())
//	{
//		int c = 0;
//		while (c < matrix[0].size())
//		{
//			if (matrix[r][c] == '1')
//			{
//				int squarelen = maximalSquare_helper(matrix, r, c);
//
//				if (maxsquarelen < squarelen)
//					maxsquarelen = squarelen;
//			}
//			c++;
//		}
//		r++;
//	}
//
//	return maxsquarelen * maxsquarelen;
//}

void testmaximalSquare()
{
	vector<vector<char>> matrix( 
		{{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','0','0','1','1','1','1','1','1','1','1','0','0','1','1','1','0','1','1','1','1','1','1','1','1'},{'1','1','1','1','0','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1'},{'0','1','1','1','1','0','1','0','1','1','1','1','1','1','0','1','1','0','1','1','0','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},{'0','1','0','1','1','0','1','0','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','0','1','1','0','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0','1','1','0','0','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1','0','1','1','0','1','0','1','1','1','1','1','1','1','1','1','1','1','0','1','0','1','1','1','1','1','1','0','1','1','1','1'},{'0','1','1','0','1','1','0','1','0','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0','1','0','1'},{'0','1','1','1','1','1','1','1','1','1','1','1','1','1','0','0','1','1','1','1','1','1','1','0','0','1','1','0','0','1','1','0','1','1','0','1','0','1','0','1'},{'1','1','1','1','0','1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','0','1','1','1','1','0','1','0','1','1','0','1','0','1','1'},{'1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','0','1','1','1','0','1','1','1','1','0','1','1','1','1'},{'1','1','1','0','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},{'1','0','1','1','1','1','1','1','1','0','1','1','1','1','0','1','1','1','1','0','0','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},{'0','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','0','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','0','1','1'},{'1','1','1','1','1','0','0','1','1','1','1','1','1','1','1','0','1','0','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1'},{'1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1'},{'1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','0','1','1','1','1','1','1','0','0','1','1','1','1','1'},{'1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1'},{'1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','0','1','1','1','1','1','0','0','1','0','1','1','1','1','1','0','1','1','1','1','1','1'},{'1','1','1','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1'},{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1','0','1','1','0','1','1'},{'1','1','0','0','0','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','0','1','0','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','0','1','0','1','1','1','0','0','1','1','1','1','1','1','1','1'},{'1','1','1','0','0','1','0','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1','0','1','1','1','1','0','1','1','1','1','1','0','1'},{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','0','1','1','1','1','1','1','0','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1'},{'1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','0','1','1','1','0','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0','1','1','1'},{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','0','1','1','1','1','1','1','0','1','0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1'},{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','0','0','1','1','1','1','1','1','1','1','1','0','1','1','1','0','1'},{'1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','0','1','1','1','0','1','1','0','1','1'},{'1','1','1','1','0','1','1','0','1','1','1','1','1','1','0','1','1','0','1','1','0','1','1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1'},{'1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},{'1','1','0','0','0','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1'},{'1','1','1','1','1','0','1','1','1','1','1','1','1','1','0','1','1','1','1','0','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},{'0','1','1','1','1','1','1','1','1','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','0','1','0','1','0','1','1','0','1','1','1','1','1','1','1','1'},{'1','0','1','1','0','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','0','0','1','1'},{'1','0','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','0','1','1','1','1','1'},{'0','1','1','1','1','0','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1'},{'0','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','0','1','1','1','0','1','1','1','1','0','1','1','1','0','1','1','1','1','1','1','1','1','1','1'},{'0','1','1','1','1','1','1','1','1','1','1','1','0','1','0','1','1','1','1','0','1','1','1','1','1','1','0','1','0','1','1','0','0','1','1','1','1','0','1','1'},{'1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','0','1','1','1','0'},{'1','1','1','1','1','0','1','1','1','1','1','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','0','0','1','1','1','1'},{'1','1','0','1','1','0','1','1','1','1','1','1','0','1','0','1','1','1','1','1','0','1','1','1','1','1','1','1','1','0','0','1','1','1','0','1','0','1','0','0'},{'0','1','1','0','1','1','1','1','1','1','1','0','0','1','1','1','1','1','0','0','1','0','1','1','1','1','1','0','1','1','1','0','1','1','0','1','1','1','0','1'}}
 
								);
	maximalSquare(matrix);
}
//https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/description/
TreeNode* sortedListToBST(ListNode* head) 
{
	if (head == NULL)
		return NULL;

	vector<int> nodevector;
	ListNode* nodeidx = head;
	while (nodeidx != NULL)
	{
		nodevector.push_back(nodeidx->val);
		nodeidx = nodeidx->next;
	}

	return sortedArrayToBST(nodevector);
}

void testsortedListToBST()
{
}

//https://leetcode.com/problems/can-i-win/description/
class canIWinCalss {
	unordered_map<int, bool> m;
public:
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if ((1 + maxChoosableInteger) * maxChoosableInteger / 2 < desiredTotal)
			return false;//总和不够
		return win(maxChoosableInteger, desiredTotal, 0, 0);
	}
	bool win(int maxChoosableInteger, int desiredTotal, int point, int state)
	{
		if (m.find(state) != m.end())
			return m[state];//重复的状态，直接读取
		for (int i = 1; i <= maxChoosableInteger; i++)
		{
			if (((state >> i) & 1) == 0)
			{	// 该二进制位为0 表示没有拿过该数
				if (point + i >= desiredTotal)
					return true;
				int newstate = state | (1 << i);//新的状态，该位为1，用过了
				//表示 对手在我选择数字 i 后的状态 是否有必胜策略。
				// 如果返回 True → 对手必胜 → 我在这个选择下输
				// 如果返回 False → 对手输 → 我在这个选择下必胜
				if (!win(maxChoosableInteger, desiredTotal, point + i, newstate))
				{
					m[state] = true;
					return true;
				}

				//上一个人在 newstate 下不能赢，那我在 state 状态下能赢
			}
		}
		m[state] = false;
		return false;
	}
};

bool canIWin_helper(int maxChoosableInteger, int desiredTotal, bool isfirst, vector<int> numbersonpath)
{
	if (maxChoosableInteger >= desiredTotal)
		return isfirst;

	for (int i = 1; i <= maxChoosableInteger; i++)
	{
		numbersonpath.push_back(i);
		if (canIWin_helper(maxChoosableInteger, desiredTotal - i, !isfirst, numbersonpath))
			return true;

		numbersonpath.pop_back();
	}

	return false;
}

// 11 19
bool canIWin(int maxChoosableInteger, int desiredTotal)
{
	if (maxChoosableInteger >= desiredTotal)
		return true;

	bool isfirst = true;
	vector<int> numbersonpath;
	for (int i = 1; i <= maxChoosableInteger; i++)
	{
		numbersonpath.push_back(i);
		if (canIWin_helper(maxChoosableInteger, desiredTotal - i, !isfirst, numbersonpath))
			return true;

		numbersonpath.pop_back();
	}

	return false;
}

void testcanIWin()
{
	canIWin(10, 40);
}

//https://leetcode.com/problems/target-sum/description/
class findTargetSumWaysClass {
public:
	unordered_map<string, int> memo;

	int dfs(vector<int>& nums, int index, int current_sum, int target) {
		if (index == nums.size()) {
			return current_sum == target ? 1 : 0;
		}

		string key = to_string(index) + "," + to_string(current_sum);

		if (memo.count(key)) {
			return memo[key];
		}

		int add = dfs(nums, index + 1, current_sum + nums[index], target);
		int sub = dfs(nums, index + 1, current_sum - nums[index], target);

		// memo["4,2"] = 1 表示 idx = 4， sum = 2 时(sum 中不包含 num[4])，有多少中方法可以得到 target
		memo[key] = add + sub;
		return memo[key];
	}

	int findTargetSumWays(vector<int>& nums, int target) {
		return dfs(nums, 0, 0, target);
	}

	int findTargetSumWays_dp(vector<int>& nums, int target) {
/*
假设：

所有加号的数之和 = P
所有减号的数之和 = N

那么有：

P - N = target
P + N = sum(nums)

两式相加：

2P = target + sum(nums)

得到：

P = (target + sum(nums)) / 2

dp[j] = 和为 j 的方案数
*/
		int sum = accumulate(nums.begin(), nums.end(), 0);

		if ((target + sum) % 2 != 0 || abs(target) > sum) {
			return 0;
		}

		int P = (target + sum) / 2;

		vector<int> dp(P + 1, 0);
		dp[0] = 1;

		for (int num : nums) {
			for (int j = P; j >= num; j--) {
				dp[j] += dp[j - num];
			}
		}

		return dp[P];
	}
};

void testfindTargetSumWays()
{
	findTargetSumWaysClass f;
	//vector<int> nums({ 42,24,30,14,38,27,12,29,43,42,5,18,0,1,12,44,45,50,21,47 });
	//f.findTargetSumWays(nums, 38);
	vector<int> nums({ 1,1,1,1,1});
	f.findTargetSumWays_dp(nums, 3);
	
}

//https://leetcode.com/problems/teemo-attacking/description/
int findPoisonedDuration(vector<int>& timeSeries, int duration) 
{
	int total = 0;
	int i1 = 0, i2 = 1;
	while (i2 < timeSeries.size())
	{
		int timediff = timeSeries[i2] - timeSeries[i1];
		if (timediff >= duration)
			total += duration;
		else
			total += timediff;

		i2++;
		i1++;
	}

	return total+duration;
}

void testfindPoisonedDuration()
{
	vector<int> timeSeries({ 1,2 });
	findPoisonedDuration(timeSeries, 2);
}

//https://leetcode.com/problems/next-greater-element-i/description/
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) 
{
	vector<int> ret(nums1.size(), 0);
	vector<int> nums2idx(nums2.size(), 0);

	for (int i = 0; i < nums1.size(); i++)
	{
		int curnum = nums1[i];
		bool found = false;
		int j = 0;
		for (; j < nums2.size(); j++)
		{
			if (nums1[i] == nums2[j])
			{
				found = true;
			}
			if (found && nums2[j] > curnum)
				break;
		}
		if (j < nums2.size())
		{
			ret[i] = nums2[j];
		}
		else
			ret[i] = -1;
	}

	return ret;
}
void testnextGreaterElement()
{
	vector<int> nums1({ 2,4 });
	vector<int> nums2({ 1,2,3,4 });
	nextGreaterElement(nums1, nums2);
}

//https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/
class RandomGenerator {
public:
	explicit RandomGenerator()
		: gen_(std::random_device{}()) {}

	explicit RandomGenerator(unsigned int seed)
		: gen_(seed) {}

	// 生成 [min, max] 范围内的随机整数
	template <typename T = int>
	T randInt(T min, T max) {
		static_assert(std::is_integral<T>::value, "T must be integral");
		std::uniform_int_distribution<T> dist(min, max);
		return dist(gen_);
	}

	// 生成 [min, max) 范围内的随机浮点数
	template <typename T = double>
	T randReal(T min = 0.0, T max = 1.0) {
		static_assert(std::is_floating_point<T>::value, "T must be floating point");
		std::uniform_real_distribution<T> dist(min, max);
		return dist(gen_);
	}

	// 以概率 p 返回 true
	bool randBool(double p = 0.5) {
		std::bernoulli_distribution dist(p);
		return dist(gen_);
	}

	// 重新设定种子
	void seed(unsigned int s) { gen_.seed(s); }

private:
	std::mt19937 gen_;
};
class Randompoints {
public:
	int totalpoints = 0;
	vector<vector<int>> rects;
	vector<int> pointsrect;
	RandomGenerator randgen;
	Randompoints(vector<vector<int>>& rects) 
	{
		this->rects = rects;
		pointsrect.resize(rects.size());
		
		for (int i = 0; i < rects.size(); i++)
		{
			int pointsinrect = (rects[i][2] - rects[i][0] + 1) * (rects[i][3] - rects[i][1] + 1);
			totalpoints += pointsinrect;
			pointsrect[i] = totalpoints;			
		}

		
	}

	vector<int> pick() 
	{
		int randpoint = randgen.randInt(1, totalpoints);
		int m = lower_bound(pointsrect.begin(), pointsrect.end(), randpoint) - pointsrect.begin();
		/*
		int l = 0, r = rects.size() - 1;
		m = (l + r) / 2;
		while (l <= r)
		{
			m = (l + r) / 2;
			if (m == 0)
			{
				if (randpoint <= pointsrect[m])
					break;
				else
					l = m + 1;
			}
			else if (pointsrect[m - 1] + 1 <= randpoint && randpoint <= pointsrect[m])
				break;			
			else if (randpoint > pointsrect[m])
				l = m + 1;
			else
				r = m - 1;
		}
		*/

		std::uniform_int_distribution<int> pointerx(rects[m][0], rects[m][2]);
		std::uniform_int_distribution<int> pointery(rects[m][1], rects[m][3]);

		int randx = randgen.randInt(rects[m][0], rects[m][2]), randy = randgen.randInt(rects[m][1], rects[m][3]);
		return vector<int>({ randx, randy });
	}
};

void testRandompoints()
{
	/*
	vector<vector<int>> rects({
							{-2, -2, 1, 1},
							{2, 2, 4, 6},
							{ 10, 10, 15, 15 },
							{16,16,20,20},
							{23,23,25,25},
							});
	*/
	vector<vector<int>> rects({ { 1, 1, 5, 5 } });
	Randompoints r(rects);
	for (int i = 0; i < 10; i++)
		r.pick();
}

//https://leetcode.com/problems/diagonal-traverse/description/
//  1 2 3 4 5 6 7 8 
//  2 3 4 5 6 7 8 9
//  1 2 3 4 5 6 7 8
//  1 2 3 4 5 6 7 8
vector<int> findDiagonalOrder(vector<vector<int>>& mat) 
{
	vector<int> ret;

	int row = 0, col = 0;
	int rowdir = -1, coldir = 1;
	int ROW = mat.size() - 1, COL = mat[0].size() - 1;
	int rowidx = row, colidx = col;
	while (rowidx >= 0 && rowidx <= ROW &&
		colidx >= 0 && colidx <= COL)
	{
		while (rowidx >= 0 && rowidx <= ROW &&
			colidx >= 0 && colidx <= COL)
		{
			ret.push_back(mat[rowidx][colidx]);
			rowidx += rowdir;			
			colidx += coldir;
		}

		int rowboundary = rowidx - rowdir;
		int colboundary = colidx - coldir;

		if (rowboundary == 0 && colboundary >= 0) // top
		{
			if (colboundary < COL)
			{
				rowidx = 0;
				colidx = colboundary + 1;
			}
			else
			{
				rowidx = 1;
				colidx = COL;
			}
		} 
		else if (rowboundary > 0 && colboundary == 0) // left
		{
			if (rowboundary == ROW)
			{
				rowidx = ROW;
				colidx = 1;
			}
			else
			{
				rowidx = rowboundary + 1;
				colidx = 0;
			}
		}
		else if (rowboundary == ROW && colboundary > 0) // bottom
		{
			rowidx = ROW;
			colidx = colboundary + 1;
		}
		else if (rowboundary > 0 && rowboundary < ROW && colboundary == COL) // right
		{
			rowidx = rowboundary + 1;
			colidx = COL;
		}

		rowdir *= -1;
		coldir *= -1;
	}

	return ret;

}

void testfindDiagonalOrder()
{
	//vector<vector<int>> mat({{ 1, 2, 3, 4, 5, 6, 7, 8 },
	//						 { 2, 3, 4, 5, 6, 7, 8, 9 },
	//						 { 1, 2, 3, 4, 5, 6, 7, 8 },
	//						 { 1, 2, 3, 4, 5, 6, 7, 8 } });
	//vector<vector<int>> mat({ { 1,},
	//						 { 2},
	//						 { 1},
	//						 { 1} });
	vector<vector<int>> mat({ { 1,2,3,4},});
	findDiagonalOrder(mat);
}


//https://leetcode.com/problems/partition-equal-subset-sum/
bool canPartition2(vector<int>& nums)
{
	int totalsum = 0;
	int i = 0, j = 0;
	totalsum = accumulate(nums.begin(), nums.end(), 0);

	if (totalsum % 2 != 0)
		return false;

	int targetsum = totalsum / 2;
	for (i = 0; i < nums.size() - 1; i++)
	{
		for (j = i + 1; j < nums.size(); j++)
		{

		}
	}

	return false;
}

bool canPartition(vector<int>& nums) {
	int totalSum = 0;
	for (int num : nums)
		totalSum += num;

	if (totalSum % 2 != 0)
		return false;

	int targetSum = totalSum / 2;
	vector<bool> dp(targetSum + 1, false);
	dp[0] = true;
	for (int num : nums) {
		for (int currSum = targetSum; currSum >= num; --currSum) {
			dp[currSum] = dp[currSum] || dp[currSum - num];
			if (dp[targetSum])
				return true;
		}
	}
	return dp[targetSum];
}
void testcanPartition()
{
	vector<int> nums({ 1,5,6,10 });
	canPartition(nums);
}

//https://leetcode.com/problems/pacific-atlantic-water-flow/description/
// 1 1 1 1 
// 1 1 1 1 
// 1 1 1 1 
// 1 1 1 1 
bool ismarkset(int row, int col, vector<vector<int>>& pathmark, int mark)
{
	return pathmark[row][col] & mark;
}

void pacificAtlantic_helper(vector<vector<int>>& heights, int row, int col, vector<vector<int>>& pathmark,int mark)
{
	int curheight = heights[row][col];

	pathmark[row][col] |= mark;
	
	//up
	if (row - 1 >= 0 && heights[row - 1][col] >= curheight && !ismarkset(row - 1, col, pathmark, mark))
	{
			pacificAtlantic_helper(heights, row - 1, col, pathmark, mark);
	}

	//down
	if (row + 1 < heights.size() && heights[row + 1][col] >= curheight && !ismarkset(row + 1, col, pathmark, mark))
	{

		pacificAtlantic_helper(heights, row + 1, col, pathmark, mark);
	}

	//left
	if (col - 1 >= 0 && heights[row][col -1] >= curheight && !ismarkset(row, col - 1, pathmark, mark))
	{
		pacificAtlantic_helper(heights, row, col - 1, pathmark, mark);
	}
	
	//right
	if (col + 1 < heights[0].size() && heights[row][col+1] >= curheight && !ismarkset(row, col + 1, pathmark, mark))
	{
		pacificAtlantic_helper(heights, row, col + 1, pathmark, mark);
	}
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) 
{
	vector<vector<int>> ret;
	vector<vector<int>> pathmark;
	pathmark.resize(heights.size());
	int row = 0, col = 0;
	for (row = 0; row < heights.size(); row++)
		pathmark[row].resize(heights[0].size());

	// 1st and last row
	for (col = 0; col < heights[0].size(); col++)
	{
		pacificAtlantic_helper(heights, 0, col, pathmark, 1);

		pacificAtlantic_helper(heights, heights.size() - 1, col, pathmark, 2);
	}

	// 1st and last col
	for (row = 0; row < heights.size(); row++)
	{
		pacificAtlantic_helper(heights, row, 0, pathmark, 1);
		pacificAtlantic_helper(heights, row, heights[0].size() - 1, pathmark, 2);
	}

	for (row = 0; row < heights.size(); row++)
	{
		for (col = 0; col < heights[0].size(); col++)
		{
			if (pathmark[row][col] == 3)
				ret.push_back(vector<int>({ row, col}));
		}
	}
	return ret;
}

void testpacificAtlantic()
{
	vector<vector<int>> heights({
								{1,2,2,3,5},
								{3,2,3,4,4},
								{2,4,5,3,1},
								{6,7,1,4,5},
								{5,1,1,2,4} });

	//vector<vector<int>> heights({
	//							{ 10, 10, 10 },
	//							{ 10, 1,10 },
	//							{ 10,10,10 }
	//							});

	//vector<vector<int>> heights({								
	//	{8,7},
	//	{11,2},
	//	{1,13},
	//	{14,15},
	//	{0,10},
	//	{19,9},
	//	{17,14},
	//	{10,10},
	//	{5,5},
	//	{15,3},
	//	{6,10},
	//	{11,10},
	//	{4,3},
	//	{12,13},
	//	{11,7},
	//	{0,9},
	//	{13,5},
	//	{11,18},
	//	{9,19},
	//	{10,11}
	//	});
	pacificAtlantic(heights);
}

//https://leetcode.com/problems/reconstruct-original-digits-from-english/description/
bool doesnumberexist(string &s, string &number, vector<bool> &isused)
{
	vector<int> localused(number.size(), 0);
	for (int i = 0; i < number.size(); i++)
	{
		bool found = false;
		for (int j = 0; j < s.size(); j++)
		{
			if (!isused[j] && s[j] == number[i])
			{
				localused[i] = j;
				found = true;				
				break;
			}
		}
		if (!found)
			return false;
	}
	for (int i = 0; i < number.size(); i++)
	{
		isused[localused[i]] = true;		
	}
	return true;
}

bool doesnumberexist2(string& s, unordered_map<char, uint32_t> &numbercharcount, unordered_map<char, uint32_t>& charcount)
{
	bool exist = false;
	auto numbercharcountidx = numbercharcount.begin();
	while (numbercharcountidx != numbercharcount.end())
	{
		char curchar = numbercharcountidx->first;
		uint32_t curcount = numbercharcountidx->second;
		if (charcount[curchar] < curcount)
			return false;
		numbercharcountidx++;
	}

	numbercharcountidx = numbercharcount.begin();
	while (numbercharcountidx != numbercharcount.end())
	{
		char curchar = numbercharcountidx->first;
		uint32_t curcount = numbercharcountidx->second;
		numbercharcountidx++;

		charcount[curchar] -= curcount;
	}
	return true;
}

string originalDigits(string &s) 
{
	string ret;
	vector<string> numstrmap({
		 "zero",
		 "one",
		"two",
		 "three",
		 "four",
		 "five",
		 "six",
		 "seven",
		 "eight",
		 "nine",
	});

	vector<unordered_map<char, uint32_t>> numcharcountmap(numstrmap.size());
	for (int i = 0; i < numstrmap.size(); i++)
	{
		for (int j = 0; j < numstrmap[i].size(); j++)
			numcharcountmap[i][numstrmap[i][j]]++;
	}

	unordered_map<char, uint32_t> charcount;
	for (int i = 0; i < s.size(); i++)
		charcount[s[i]]++;

	bool found = true;
	int curint = 0, usedchars = 0;
	while (curint < 10 && usedchars < s.size())
	{
		if (!doesnumberexist2(s, numcharcountmap[curint], charcount))
		{
			curint++;
		}
		else
		{
			usedchars += numcharcountmap[curint].size();
			ret += to_string(curint);
		}
	}

	return ret;
}


void testoriginalDigits()
{
	string s("ertfsxvxttior");
	originalDigits(s);
}

//https://leetcode.com/problems/next-greater-element-ii/description/
vector<int> nextGreaterElements(vector<int>& nums) 
{
	vector<int> ret(nums.size(), -1);
	if (nums.size() == 1)
		return ret;

	for (int i = 0; i < nums.size(); i++)
	{
		int curnum = nums[i];
		int j = i + 1;
		while (i != j)
		{
			if (j == nums.size())
				j = 0;
			if (i == j || nums[j] > curnum)
				break;
			j++;
		}
		if (i != j)
			ret[i] = nums[j];
	}
	return ret;
}

// 用单调递减栈来解决（从栈底 -> 栈顶是递减的），则栈顶是当前数字右侧的所有数字中的最大值
//栈实际上维护了一个右侧元素的"有效候选集合"：
//
//只保留那些"有可能成为某个左侧元素答案"的值
//通过弹出操作，不断剔除无效候选
//栈顶永远是当前能找到的最小但大于当前元素的候选
vector<int> nextGreaterElements2(vector<int>& nums) {
	int n = nums.size();
	vector<int> result(n, -1);  
	stack<int> st;
	
	for (int i = 2 * n - 1; i >= 0; i--) {
		int index = i % n;
		
		while (!st.empty() && st.top() <= nums[index]) {
			st.pop();
		}
		
		if (!st.empty()) {
			result[index] = st.top();
		}		
		st.push(nums[index]);
	}

	return result;
}

//查找某个数左侧第一个比它小的数， 单调递减栈
vector<int> previousLessElements(vector<int>& nums)
{
	vector<int> ret(nums.size(), -1);
	stack<int> st; 
	int n = nums.size();
	for (int i = 0; i <= 2 * n - 1; i++)
	{
		int idx = i % n;
		while (!st.empty() && st.top() >= nums[idx])
			st.pop();

		if (!st.empty())
			ret[idx] = st.top();

		st.push(nums[idx]);
	}

	return ret;
}

void testnextGreaterElements()
{
	vector<int> nums({ 5,4,3,2,1 });
	//vector<int> nums({ 20, 3, 30, 1,9, 4, 77, 2, 1, 5, 7, 0});
	
	//previousLessElements(nums);
	nextGreaterElements2(nums);
}

//https://leetcode.com/problems/base-7/description/
string convertToBase7(int num) 
{
	if (num == 0)
		return "0";

	string ret;
	bool ispos = (num > 0);
	num = std::abs(num);
	while (num > 0)
	{
		int remainder = num % 7;
		ret.insert(ret.begin(), '0' + remainder);
		num /= 7;
	}

	if (!ispos)
		ret.insert(ret.begin(), '-');
	
	return ret;
}

void testconvertToBase7()
{
	int n = 344;
	convertToBase7(n);
}

//https://leetcode.com/problems/roman-to-integer/description/
int romanToInt(string &s) 
{
	unordered_map<char, int> romannum({
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000},
		});
	/*
	I can be placed before V(5) and X(10) to make 4 and 9.
	X can be placed before L(50) and C(100) to make 40 and 90.
	C can be placed before D(500) and M(1000) to make 400 and 900.
	*/
	int ret = 0;
	int i = 0;
	while (i < s.size())
	{
		switch (s[i])
		{
		case 'I':
			if (i + 1 < s.size())
			{
				if (s[i + 1] == 'V')
				{
					ret += 4;
					i++;
				}
				else if (s[i + 1] == 'X')
				{
					ret += 9;
					i++;
				}
				else
					ret += 1;				
			}
			else
				ret += 1;
		break;
		case 'X':
			if (i + 1 < s.size())
			{
				if (s[i + 1] == 'L')
				{
					ret += 40;
					i++;
				}
				else if (s[i + 1] == 'C')
				{
					ret += 90;
					i++;
				}
				else
					ret += 10;				
			}
			else
				ret += 10;
		break;
		case 'C':
			if (i + 1 < s.size())
			{
				if (s[i + 1] == 'D')
				{
					ret += 400;
					i++;
				}
				else if (s[i + 1] == 'M')
				{
					ret += 900;
					i++;
				}
				else
					ret += 100;
			}
			else
				ret += 100;
			break;
		case 'V':
			ret += 5;
		break;
		case 'L':
			ret += 50;
		break;
		case 'D':
			ret += 500;
		break;
		case 'M':
			ret += 1000;
		break;
		}
		i++;
	}

	return ret;
}

void testromanToInt()
{
	string s("MMMCC");
	romanToInt(s);
}

//https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
int strStr(string haystack, string needle)
{
	int pos = haystack.find(needle.c_str(), 0);
	if (pos != string::npos)
		return pos;

	return -1;
}

void teststrStr()
{
	string haystack("leet"), needle("need");
	strStr(haystack, needle);
}

//https://leetcode.com/problems/search-insert-position/description/
int searchInsert(vector<int>& nums, int target) 
{
	//if (target <= nums[0] || nums.size() == 0)
	//	return 0;
	//if (target >= nums[nums.size() - 1])
	//	return nums.size();

	int left = 0, right = nums.size() - 1;
	int mid = left + (right - left) / 2;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (nums[mid] < target)
			left = mid + 1;
		else if (nums[mid] > target)
			right = mid - 1;
		else
			return mid;
	}

	return left;
}

void testsearchInsert()
{
	vector<int> nums({ 1,3, });
	searchInsert(nums, 3);
}

//https://leetcode.com/problems/add-binary/description/
string addBinary(string &a, string &b) 
{
	bool carry = false;
	string ret;
	ret.resize(a.size() > b.size() ? a.size() + 1 : b.size() + 1);
	int ai = a.size() - 1, bi = b.size() - 1, ri = ret.size() - 1;
	while (ai >= 0 && bi >= 0)
	{
		int sum = (a[ai] - '0') + (b[bi] - '0') + carry;
		bool left = sum % 2;
		carry = sum / 2;
		ret[ri] = '0' + left;

		ai--;
		bi--;
		ri--;
	}

	while (ai >= 0)
	{
		int sum = a[ai] -'0' + carry;
		bool left = sum % 2;
		carry = sum / 2;
		ret[ri] = '0' + left;

		ai--;
		ri--;
	}

	while (bi >= 0)
	{
		int sum = b[bi] - '0' + carry;
		bool left = sum % 2;
		carry = sum / 2;
		ret[ri] = '0' + left;

		bi--;
		ri--;
	}
	if (carry)
	{
		ret[0] = '1';
		return ret;
	}
	else
	{
		string subret = ret.substr(1, ret.size() - 1);
		return subret;
	}
}

void testaddBinary()
{
	string a("11"), b("1001");

	addBinary(a, b);
}

//https://leetcode.com/problems/sqrtx/description/
int mySqrt(int x) 
{
	if (x == 1)
		return 1;

	int l = 1, r = x;
	int ret = 0;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		if (mid <= x / mid)
		{
			if (mid * mid == x)
				return mid;

			ret = mid;
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}

	return ret;
}

//https://leetcode.com/problems/valid-perfect-square/description/
bool isPerfectSquare(int num) 
{
	if (num == 1)
		return true;

	int l = 1, r = num;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		if (mid <= num / mid)
		{
			if (mid * mid == num)
				return true;
			l = mid + 1;
		}
		else
			r = mid - 1;
	}

	return false;
}

//https://leetcode.com/problems/climbing-stairs/description/
void climbStairs_helpers(int left, int& ways)
{
	if (left == 0)
	{
		ways++;
		return;
	}

	climbStairs_helpers(left - 1, ways);
	if (left > 1)
		climbStairs_helpers(left - 2, ways);
}

int climbStairs_slow(int n) 
{
	int ways= 0;
	if (n <= 2)
		return n;

	climbStairs_helpers(n, ways);

	return ways;		
}

int climbStairs(int n)
{
	if (n <= 2)
		return n;

	int pre_1step = 2;
	int pre_2steps = 1;
	int cur = 0;
	for (int i = 3; i <= n; i++)
	{ 
		cur = pre_1step + pre_2steps;
		pre_2steps = pre_1step;
		pre_1step = cur;
	}

	return cur;
}

void testclimbStairs()
{
	climbStairs(5);
}

//https://leetcode.com/problems/symmetric-tree/description/
bool Are2NodesSymmetric(const TreeNode* a, const TreeNode* b)
{
	if (a == NULL && b == NULL)
		return true;

	if (a != NULL && b != NULL)
	{
		return a->val == b->val;
	}

	return false;
}

bool isSymmetric(TreeNode* root)
{
	if (root == NULL)
		return false;

	list<pair<TreeNode*, TreeNode*>> nodelist;
	nodelist.emplace_back(root->left, root->right);
	while (nodelist.size() > 0)
	{
		auto itor(nodelist.begin());
		if (!Are2NodesSymmetric(itor->first, itor->second))
			return false;

		if (itor->first && itor->second)
		{
			nodelist.emplace_back(itor->first->left, itor->second->right);
			nodelist.emplace_back(itor->first->right, itor->second->left);
		}
		nodelist.erase(itor);
	}

	return true;
}

bool isSymmetric_ok(TreeNode* root)
{
	if (root == NULL || (root->left == NULL && root->right == NULL))
		return true;

	if ((root->left == NULL && root->right != NULL) ||
		(root->left != NULL && root->right == NULL) ||
		(root->left != NULL && root->right != NULL && root->left->val != root->right->val))
		return false;

	list<pair<TreeNode*, TreeNode*> > nodeList;
	nodeList.push_back(pair<TreeNode*, TreeNode*>(root->left->left, root->right->right));
	nodeList.push_back(pair<TreeNode*, TreeNode*>(root->left->right, root->right->left));
	list<pair<TreeNode*, TreeNode*> >::iterator itor = nodeList.begin();
	while (nodeList.size() > 0)
	{
		TreeNode* n1 = itor->first, * n2 = itor->second;
		if (n1 == NULL && n2 == NULL)
		{
			itor = nodeList.erase(itor);
			continue;
		}
		if ((n1 == NULL && n2 != NULL) ||
			(n1 != NULL && n2 == NULL) ||
			(n1->val != n2->val))
			return false;

		nodeList.push_back(pair<TreeNode*, TreeNode*>(n1->left, n2->right));
		nodeList.push_back(pair<TreeNode*, TreeNode*>(n1->right, n2->left));

		itor = nodeList.erase(itor);
	}

	return true;
}

//https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
int maxDepth_helper(TreeNode* root, int curdep)
{
	if (root == NULL)
		return curdep;

	int leftdep = curdep;
	if (root->left)
		leftdep = maxDepth_helper(root->left, curdep + 1);

	int rightdep = curdep;
	if (root->right)
		rightdep = maxDepth_helper(root->right, curdep + 1);

	return max(leftdep, rightdep);
}

int maxDepth(TreeNode* root) 
{
	if (root == NULL)
		return 0;

	int dep = maxDepth_helper(root, 1);
	return dep;
}

void testmaxDepth()
{
	vector<int> v1({ 0,1,2,INT_MIN, INT_MIN, 5,6 });	
	TreeNode** t1 = createTree(v1);
	maxDepth(*t1);
}

//https://leetcode.com/problems/pascals-triangle/description/
vector<vector<int>> generate(int numRows) 
{
	vector<vector<int>> ret;
	vector<int> firstrow({ 1 }), secondrow({ 1,1 });
	if (numRows == 1)
	{
		ret.push_back(firstrow);
		return ret;
	}
	ret.push_back(firstrow);
	if (numRows == 2)
	{
		ret.push_back(secondrow);
		return ret;
	}
	ret.push_back(secondrow);
	for (int i = 2; i < numRows; i++)
	{
		vector<int> nthrow(i+1);
		nthrow[0] = 1;
		nthrow[i] = 1;
		for (int j = 1; j < i; j++)
		{
			nthrow[j] = ret[i -1][j - 1] + ret[i - 1][j];
		}
		ret.push_back(nthrow);
	}

	return ret;
}


vector<int> getRow(int rowIndex)
{
	vector<vector<int>> ret;
	vector<int> firstrow({ 1 }), secondrow({ 1,1 });
	if (rowIndex == 0)
	{
		return firstrow;
	}
	ret.push_back(firstrow);
	if (rowIndex == 1)
	{	
		return secondrow;
	}
	ret.push_back(secondrow);
	for (int i = 2; i <= rowIndex; i++)
	{
		vector<int> nthrow(i + 1);
		nthrow[0] = 1;
		nthrow[i] = 1;
		for (int j = 1; j < i; j++)
		{
			nthrow[j] = ret[i - 1][j - 1] + ret[i - 1][j];
		}
		ret.push_back(nthrow);
	}

	return ret[rowIndex];
}
void testgenerate()
{
	getRow(5);
}

//https://leetcode.com/problems/valid-palindrome/description/
bool isPalindrome_slow(string s)
{
	string s2(s.size(), 0);
	int i = 0;
	for (char c : s)
	{
		if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		{
			s2[i] = c;
			i++;
		}
		else if (c >= 'A' && c <= 'Z')
		{
			s2[i] = c + 32;
			i++;
		}
	}
	
	int l = 0, r = i - 1;
	while (l < r)
	{
		if (s2[l] != s2[r])
			return false;
		l++;
		r--;
	}
	return true;
}

bool isLetterOrNum(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c>= 'A' && c<= 'Z');
}

char covertToLower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 32;

	return c;
}

bool isPalindrome(string s)
{
	int l = 0, r = s.size() - 1;
	while (l < r)
	{
		while (l < r && !isLetterOrNum(s[l]))
		{
			l++;
		}

		while (l < r && !isLetterOrNum(s[r]))
		{
			r--;
		}

		if (covertToLower(s[l]) != covertToLower(s[r]))
			return false;

		l++;
		r--;
	}

	return true;
}

void testisPalindrome()
{
	string s("A man, a plan, a canal: Panama");
	isPalindrome(s);
}

//https://leetcode.com/problems/surrounded-regions/description/
void findwholeregion(vector<vector<char>>& board, int row, int col)
{
	bool newnodeonpath = false;
	board[row][col] = 'N';

	set<pair<int, int>> curnodecandidates;
	// up
	if (row - 1 >= 0 && board[row - 1][col] == 'O')
	{
		findwholeregion(board, row - 1, col);
	}

	//dwon
	if (row + 1 <= board.size() - 1 && board[row + 1][col] == 'O')
	{
		findwholeregion(board, row + 1, col);
	}

	//left
	if (col - 1 >= 0 && board[row][col - 1] == 'O')
	{
		findwholeregion(board, row, col-1);
	}

	//right
	if (col + 1 <= board[0].size() - 1 && board[row][col + 1] == 'O')
	{
		findwholeregion(board, row, col+1);
	}
}


void solve(vector<vector<char>>& board)
{
	int row = 1, col = 1;
	int ROW = board.size() - 1, COL = board[0].size() - 1;

	for (row = 0; row <= ROW; row++)
	{
		if (board[row][0] == 'O')
		{
			
			findwholeregion(board, row, 0);
		}

		if (board[row][COL] == 'O')
		{
			
			findwholeregion(board, row, COL);
		}		
	}

	for (col = 0; col <= COL; col++)
	{
		if (board[0][col] == 'O')
		{
			findwholeregion(board, 0, col);
		}

		if (board[ROW][col] == 'O')
		{
			findwholeregion(board, ROW, col);
		}
	}

	for (row = 0; row <= ROW; row++)
	{
		for (col = 0; col <= COL; col++)
		{
			if (board[row][col] == 'O')
			{
				board[row][col] = 'X';
			}

			if (board[row][col] == 'N')
			{
				board[row][col] = 'O';
			}
		}
	}
}

void testsolve()
{
	vector<vector<char>> board({
		//	{'X','X','X','X'},
		//	{'X','O','O','X'},
		//	{'X','X','O','X'},
		//	{'X','O','X','X'} 
		
	 //{'X','O','X','O','X','O','O','O','X','O'},
	 //{'X','O','O','X','X','X','O','O','O','X'},
	 //{'O','O','O','O','O','O','O','O','X','X'},
	 //{'O','O','O','O','O','O','X','O','O','X'},
	 //{'O','O','X','X','O','X','X','O','O','O'},
	 //{'X','O','O','X','X','X','O','X','X','O'},
	 //{'X','O','X','O','O','X','X','O','X','O'},
	 //{'X','X','O','X','X','O','X','O','O','X'},
	 //{'O','O','O','O','X','O','X','O','X','O'},
	 //{'X','X','O','X','X','X','X','O','O','O'}

		{'O'}
		});

	solve(board);
}
//https://leetcode.com/problems/palindrome-partitioning/
bool partition_helper_checkpalindrome(string& s, int l, int r)
{
	if (s.size() == 1 || l == r)
		return true;

	while (l < r)
	{
		if (s[l] != s[r])
			return false;
	}

	return true;
}

vector<vector<string>> partition(string &s) 
{
	vector<vector<string>> ret;
	int pallen = 1;
	while (pallen <= s.size())
	{
		int i = 0; 
		vector<string> onepart;
		while (i + pallen < ret.size())
		{			
			if (partition_helper_checkpalindrome(s, i, i + pallen - 1))
			{
				onepart.push_back(s.substr(i, pallen));
				i += pallen;
			}
			else
			{
				onepart.push_back(s.substr(i, 1));
				i++;
			}
		}
		ret.push_back(onepart);
		pallen++;
	}

	return ret;
}

void testpartition131()
{
	string s("aab");
	partition(s);
}

int main()
{
	testpartition131();
	return 0;
}
