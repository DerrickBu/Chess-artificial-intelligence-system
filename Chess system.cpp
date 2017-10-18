//·程序的输入与输出均为标准记步法表示的走法。
//·程序对人工输入的走法不做检查，请不要输入不符合规则的走法，以免产生错误。
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
#pragma once
#include <stdio.h>
#include <tchar.h>
#include "Single_linked_list.h"
#include "tree.h"
#include "targetver.h"
#include "Chessman.h"
#include "Chessboard.h"
#include "Player.h"
#pragma once
#include "stdafx.h"
#pragma once
// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。
// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// 将 _WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。
#include <SDKDDKVer.h>
#pragma once
#include "stdafx.h"
template <class T>
class NODE
{
public:
	T Data;
	NODE* Child;
    NODE* Brother;
};
template <class T>
class Tree
{
public:
	Tree(T board) :ROOT(Init(board)) {}
	int Add_Child(T board, NODE<T>* root);
	int Delete_All(NODE<T>* root);
	int Perorder(NODE<T>* root) const;
	int NorecPerorder(NODE<T>* root) const;
	int Postorder(NODE<T>* root) const;
	int NorecPostorder(NODE<T>* root) const;
	int Levelorder(NODE<T>* root) const;
    NODE<T>* Root() const
    {
        return ROOT;
    }
    NODE<T>* Init(T board);
    ~Tree()
    {
        Delete_All(Root());
    }
private:
    NODE* ROOT;
};
template <class T>
NODE<T>* Tree<T>::Init(T board)
{
	NODE<T>* root;
	root = new NODE;
	root->Data = board;
	root->Brother = NULL;
	root->Child = NULL;
	return root;
}
template <class T>
int Tree<T>::Add_Child(T board, NODE<T>* root)
{
	NODE<T>* p = root->Child;
	if (p != NULL)
	{
		while (p->Brother != NULL)
			p = p->Brother;
		p->Brother = new NODE;
		p->Brother->Data = board;
		p->Brother->Brother = NULL;
		p->Brother->Child = NULL;
	}
	else
	{
		p->Child = new NODE;
		p->Child->Data = board;
		p->Child->Brother = NULL;
		p->Child->Child = NULL;
	}
	return 0;
}
template <class T>
int Tree<T>::Delete_All(NODE<T>* root)
{
    if(root==NULL)
        return 0;
	Tree::Delete_All(root->Child);
	Tree::Delete_All(root->Brother);
	delete root;
	return 0;
}
template <class T>
int Tree<T>::Perorder(NODE<T>* root) const
{
	if (root == NULL)
		return 0;
	cout << root->Data << ' ';
	Tree<T>::Perorder(root->Child);
	Tree<T>::Perorder(root->Brother);
}
template<class T>
int Tree<T>::NorecPerorder(NODE<T>* root) const
{
	NODE<T>** Stack = new NODE<T>*[10];
	int top = -1;
	NODE<T>* p = root;
	top++;
	Stack[top] = p;
	while (top != -1)
	{
		p = Stack[top];
		top--;
		cout << p->Data << ' ';
		if (p->Brother != NULL)
		{
			top++;
			Stack[top] = p->Brother;
		}
		if (p->Child != NULL)
		{
			top++;
			Stack[top] = p->Child;
		}
	}
}
template<class T>
int Tree<T>::Postorder(NODE<T>* root) const
{
	if (root == NULL)
		return 0;
	Tree<T>::Postorder(root->Child);
	cout << root->Data << ' ';
	Tree<T>::Postorder(root->Brother);
}
template<class T>
int Tree<T>::NorecPostorder(NODE<T>* root) const
{
	NODE<T>** Stack = new NODE<T>*[10];
	int top = -1;
	NODE<T>* p = root;
	for (;;)
	{
		while (p != NULL)
		{
			top++;
			Stack[top] = p;
			p = p->Child;
		}
		if (top == -1)
			return 0;
		else
		{
			p = Stack[top];
			top--;
		}
		cout << p->Data << ' ';
		p = p->Brother;
	}
}
template<class T>
int Tree<T>::Levelorder(NODE<T>* root) const
{
	NODE<T>** Queue = new NODE<T>*[10];
	int top = 0;
	int rear = 0;
	NODE<T>* p = root;
	Queue[top] = p;
	rear++;
	while (top != rear)
	{
		p = Queue[top];
		top = (top + 1) % 10;
		while (p != NULL)
		{
			cout << p->Data << ' ';
			if (p->Child != NULL)
			{
				Queue[rear] = p->Child;
				rear = (rear + 1) % 10;
			}
			p = p->Brother;
		}
	}
}
#pragma once
#include "stdafx.h"
#define NODE_PRESENT 0
#define NODE_FIRST 1
#define NODE_LAST 2
template <class T>
class node
{
public:
    T Data;
    node* next;
};
template <class T>
class single_linked_list
{
public:
	single_linked_list() :length(0), head(new node), rear(head) {}
	int add_node(T x);
	int delete_node(node<T>* p);
	const long get_length()
    {
		return length;
    }
    node<T>* head;
    node<T>* rear;
    int length;
};
template <class T>
int single_linked_list<T>::add_node(T x)
{
	rear->next = new node;
	rear->next->Data = x;
	rear = rear->next;
	length++;
	return 0;
}
template <class T>
int single_linked_list<T>::delete_node(node<T>* p)
{
	node<T>* s = head;
	while (s != NULL)
	{
		if (s->next == p)
		{
			if (p == rear)
			{
				s->next == NULL;
				rear = s;
			}
			else
				s->next = p->next;
			delete p;
			length--;
			return 0;
		}
		s = s->next;
	}
	return 1;
}
/*
template <class T>
node* single_linked_list::search_node(T x)
{
    node* p=head;
	while (p != NULL)
	{
		p = p->next;
		if (p->Data == x)
			return p;
	}
    return NULL;
}
*/
#pragma once
#include "stdafx.h"
#include "Chessboard.h"
class player
{
public:
	int flag;
	single_linked_list<Chessman> chessman_left;
	Tree<Chessboard> tree;
	player(int Flag, Chessboard board) :flag(Flag), tree(board)
	{
		for (int i = 0; i < 8; i++)
		{
			pawn apawn(Flag, Flag*5+1, i);
			chessman_left.add_node(apawn);
		}
		for (int i = 0; i < 2; i++)
		{
			bishop abishop(Flag, Flag * 7, i * 3 + 2);
			chessman_left.add_node(abishop);
			rook arook(Flag, Flag * 7, i * 7);
			chessman_left.add_node(arook);
			knight aknight(Flag, Flag * 7, i * 5 + 1);
			chessman_left.add_node(aknight);
		}
		king aking(Flag, Flag * 7, Flag + 3);
		chessman_left.add_node(aking);
		queen aqueen(Flag, Flag * 7, 4 - Flag);
		chessman_left.add_node(aqueen);
	}
};
#pragma once
#include "stdafx.h"
#define QUEEN  900
#define KING   9999
#define KNIGHT 300
#define BISHOP 325
#define ROOK   500
#define PAWN   10
class Chessman
{
public:
	int side;
	int x;
	int y;
	int value;
	Chessman(int Side, int Value, int X, int Y) :side(Side), value(Value), x(X), y(Y) {}
	virtual int next_step() {};
};

class queen :public Chessman
{
public:
	queen(int Side, int X, int Y) :Chessman(Side, QUEEN, X, Y) {}
	int next_step()
	{
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 1:

				break;
			}
		}
		return 0;
	}
};
class king :public Chessman
{
public:
	king(int Side, int X, int Y) :Chessman(Side, KING, X, Y) {}
	int next_step()
	{
		return 0;
	}#pragma once
#include "stdafx.h"
#define QUEEN  900
#define KING   9999
#define KNIGHT 300
#define BISHOP 325
#define ROOK   500
#define PAWN   100
class Chessman
{
public:
	int side;
	int x;
	int y;
	int value;
	Chessman(int Side, int Value, int X, int Y) :side(Side), value(Value), x(X), y(Y) {}
	virtual int next_step() {};
};
class queen :public Chessman
{
public:
	queen(int Side, int X, int Y) :Chessman(Side, QUEEN, X, Y) {}
	int next_step()
	{
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 1:
				break;
			}
		}
		return 0;
	}
};
class king :public Chessman
{
public:
	king(int Side, int X, int Y) :Chessman(Side, KING, X, Y) {}
	int next_step()
	{
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 1:
				break;
			}
		}
		return 0;
	}
};
class bishop :public Chessman
{
public:
	bishop(int Side, int X, int Y) :Chessman(Side, BISHOP, X, Y) {}
	int next_step()
	{
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 1:
				break;
			}
		}
		return 0;
	}
};

class knight :public Chessman
{
public:
	knight(int Side, int X, int Y) :Chessman(Side, KNIGHT, X, Y) {}
	int next_step()
	{
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 1:
				break;
			}
		}
		return 0;
	}
};
class pawn :public Chessman
{
public:
	pawn(int Side, int X, int Y) :Chessman(Side, PAWN, X, Y) {}
	int next_step()
	{
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 1:
				break;
			}
		}
		return 0;
	}
};
class rook :public Chessman
{
public:
	rook(int Side, int X, int Y) :Chessman(Side, ROOK, X, Y) {}
	int next_step()
	{
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 1:
				break;
			}
		}
		return 0;
	}
};#pragma once
#include "stdafx.h"
#include "Player.h"
#define BLACK 0
#define WHITE 1
class Chessboard
{
public:
	int who_win = -1;
	int chessboard[8][8][2] = {
		{ { 0,ROOK },{ 0,KNIGHT },{ 0,BISHOP },{ 0,KING },{ 0,QUEEN },{ 0,BISHOP },{ 0,KNIGHT },{ 0,ROOK } },
		{ { 0,PAWN },{ 0,PAWN },{ 0,PAWN },{ 0,PAWN },{ 0,PAWN },{ 0,PAWN },{ 0,PAWN },{ 0,PAWN } },
		{ { -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 } },
		{ { -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 } },
		{ { -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 } },
		{ { -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 },{ -1,0 } },
		{ { 1,PAWN },{ 1,PAWN },{ 1,PAWN },{ 1,PAWN },{ 1,PAWN },{ 1,PAWN },{ 1,PAWN },{ 1,PAWN } },
		{ { 1,ROOK },{ 1,KNIGHT },{ 1,BISHOP },{ 1,QUEEN },{ 1,KING },{ 1,BISHOP },{ 1,KNIGHT },{ 1,ROOK } }
	};
	int judge(int side);
	int ifgo(Chessman man, int x, int  y);
	int get_step(int step);
	player* black;
	player* white;
};
int Chessboard::get_step(int step)
{
	chessboard[(step % 100) / 10][step % 10][0] = chessboard[step / 1000][(step % 1000) / 100][0];
	chessboard[(step % 100) / 10][step % 10][1] = chessboard[step / 1000][(step % 1000) / 100][1];
	chessboard[step / 1000][(step % 1000) / 100][0] = -1;
	chessboard[step / 1000][(step % 1000) / 100][1] = 0;
}
int Chessboard::ifgo(Chessman man, int x, int y)
{
	if (x > 7 || x < 0 || y > 7 || y < 0)
		return 1;
	if (chessboard[x][y][0] == man.side)
		return 1;
	return 0;
}
int Chessboard::judge(int side)
{
	int power = 0;
	int p_power = 0;
	node<Chessman>* p;
	p = black->chessman_left.head;
	while (p->next != NULL)
	{
		power += p->next->Data.value;
		if (p->next->Data.x == 3 || p->next->Data.x == 4)
			if (p->next->Data.y == 3 || p->next->Data.y == 4)
				p_power += p->next->Data.value;
		p = p->next;
	}
	p = white->chessman_left.head;
	while (p != NULL)
	{
		power -= p->next->Data.value;
		p = p->next;
	}
	if (side == WHITE)
		power = -power;
	if (power <= -3950 || power > 3950)
	{
		if (power*(side - 1) == -power)
			who_win = BLACK;
		else
			who_win = WHITE;
		return 65535;
	}
	return power + p_power;
}
