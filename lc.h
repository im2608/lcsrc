#pragma once
#ifndef LC_H
#define LC_H
#include "Header.h"
#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode* random;
	ListNode(int x) : val(x), next(NULL) {}	
};


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}	
};


class edge
{
public:
	edge(int f, int t, int w): from(f), to(t), w(w)
	{
	}
	edge() :from(0), to(0), w(-1)
	{
	}

	int from, to;
	unsigned int w;

	bool operator <(const edge e) const 
	{
		return e.w < this->w;
	}

};

class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;
	Node* random;
	vector<Node*> children;
	vector<Node*> neighbors;

	Node* prev;	
	Node* child;

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
		neighbors = _children;
	}
	Node() : val(0), left(NULL), right(NULL), next(NULL), random(NULL) { neighbors = vector<Node*>(); }

	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL), random(NULL) {}

	Node(int _val, Node* _left, Node* _right, Node* _next, Node *_rand)
		: val(_val), left(_left), right(_right), next(_next), random(_rand) {}

};


ListNode* createListNode(std::vector<int>& n);
void deleteList(ListNode* head);

class CBASE
{
public:
	int ibase;
	virtual int printvalue() { printf("cbase\n"); }
};

class CDeriveA : public CBASE
{
public:
	int ia;
	int printvalue() { printf("CDeriveA\n"); }
};

class CDeriveB : public CBASE
{
public:
	int ib;
	int ib2;
	int printvalue() { printf("CDeriveB\n"); }
};


#endif LC_H