//make a binary tree 
/*
1. preorder, postorder, copy, == (equal)를 test한다.
2. 두개의 binary tree를 만들어 equal 테스트한다.
3. NonrecInorder()를 구현한다
4. class InorderIterator를 구현한다.
5. class Queue를 사용하여 LevelOrder()를 구현한다.

expression = A + B * C –D를 TREE로 만드는 코딩
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Queue.h"

using namespace std;

class Tree;

class TreeNode {
	friend class Tree;
	friend class InorderIterator;
	friend int equal(TreeNode*, TreeNode*);
private:
	TreeNode * LeftChild;
	int data;
	TreeNode *RightChild;

	TreeNode() { 
		LeftChild = RightChild = 0; 
	};

	TreeNode(int ch, TreeNode *Lefty, TreeNode *Righty){
		data = ch;
		LeftChild = Lefty;
		RightChild = Righty;
	}
};

class Tree {
	friend int operator==(const Tree&, const Tree&);
	friend class InorderIterator;
private:
	TreeNode * root;
	void inorder(TreeNode *);
	void preorder(TreeNode *);
	void postorder(TreeNode *);
	TreeNode* copy(TreeNode *);
public:
	Tree(const Tree&);
	Tree() { root = 0; };

	bool Insert(int);
	void inorder();
	void preorder();
	void postorder();
	void NoStackInorder();
	void NonrecInorder();
	void LevelOrder();
};

class InorderIterator {
public:
	int * Next();
	InorderIterator(Tree tree) : t(tree) {
		CurrentNode = t.root; 
	};

private:
	Tree t;
	Stack<TreeNode *> s;
	TreeNode *CurrentNode;
};


int *InorderIterator::Next()
{
	while (CurrentNode) {
		s.Add(CurrentNode);
		CurrentNode = CurrentNode->LeftChild;
	}
	if (!s.IsEmpty()) {
		CurrentNode = *s.Delete(CurrentNode);
		int& temp = CurrentNode->data;
		CurrentNode = CurrentNode->RightChild;
		return &temp;
	}
	else return 0;
}

void Tree::inorder()
{
	inorder(root);
}

void Tree::preorder()
{
	preorder(root);
}

void Tree::postorder()
{
	postorder(root);
}

void Tree::inorder(TreeNode *CurrentNode)
{
	if (CurrentNode) {
		inorder(CurrentNode->LeftChild);
		cout << " " << CurrentNode->data;
		inorder(CurrentNode->RightChild);
	}
}

void Tree::preorder(TreeNode *CurrentNode)
{
	if (CurrentNode) {
		cout << CurrentNode->data << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}

void Tree::postorder(TreeNode *CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
}

Tree::Tree(const Tree& s)
{
	root = copy(s.root);
}

TreeNode* Tree::copy(TreeNode *orignode)
{
	if (orignode) {
		TreeNode *temp = new TreeNode;
		temp->data = orignode->data;
		temp->LeftChild = copy(orignode->LeftChild);
		temp->RightChild = copy(orignode->RightChild);
		return temp;
	}
	else return 0;
}

// Driver
int operator==(const Tree& s, const Tree& t)
{
	return equal(s.root, t.root);
}

// Workhorse
int equal(TreeNode *a, TreeNode *b)
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */
{
	if ((!a) && (!b)) return 1;  // both a and b are 0
	if (a && b &&                // both a and b are non-0
		(a->data == b->data)      // data is the same
		&& equal(a->LeftChild, b->LeftChild) // left subtrees are the same
		&& equal(a->RightChild, b->RightChild)) // right subtrees are the same
		return 1;
	return 0;
}

bool Tree::Insert(int x) {
	TreeNode *p = root;
	TreeNode *q = 0;
	while (p) {
		q = p;
		if (x == p->data) return false;
		if (x < p->data) p = p->LeftChild;
		else p = p->RightChild;
	}
	p = new TreeNode;
	p->LeftChild = p->RightChild = 0;
	p->data = x;
	if (!root) root = p;
	else if (x < q->data) q->LeftChild = p;
	else q->RightChild = p;
	return true;
}

void Tree::NonrecInorder()
{
	Stack<TreeNode *> s;
	TreeNode *CurrentNode = root;
	while (1) {
		while (CurrentNode) {
			s.Add(CurrentNode);
			CurrentNode = CurrentNode->LeftChild;
		}
		if (!s.IsEmpty()) {
			CurrentNode = *s.Delete(CurrentNode);
			cout << CurrentNode->data << endl;
			CurrentNode = CurrentNode->RightChild;
		}
		else break;
	}
}
void Tree::LevelOrder()
{
	Queue <TreeNode *> q;
	TreeNode *CurrentNode = root;
	while (CurrentNode) {
		cout << CurrentNode->data << endl;
		if (CurrentNode->LeftChild) 
			q.Add(CurrentNode->LeftChild);
		if (CurrentNode->RightChild) 
			q.Add(CurrentNode->RightChild);
		CurrentNode = *q.Delete(CurrentNode);
	}
}
void Tree::NoStackInorder()
{
	if (!root) return;
	TreeNode *top = 0, *LastRight = 0, *p, *q, *r, *r1;
	p = q = root;
	while (1) {
		while (1) {
			if ((!p->LeftChild) && (!p->RightChild)) {
				cout << p->data; break;
			}
			if (!p->LeftChild) {
				cout << p->data;
				r = p->RightChild; p->RightChild = q;
				q = p; p = r;
			}
			else {
				r = p->LeftChild; p->LeftChild = q;
				q = p; p = r;
			}
		}
		TreeNode *av = p;
		while (1) {
			if (p == root) return;
			if (!q->LeftChild) {
				r = q->RightChild; q->RightChild = p;
				p = q; q = r;
			}
			else if (!q->RightChild) {
				r = q->LeftChild; q->LeftChild = p;
				p = q; q = r; cout << p->data;
			}
			else
				if (q == LastRight) {
					r = top; LastRight = r->LeftChild;
					top = r->RightChild;
					r->LeftChild = r->RightChild = 0;
					r = q->RightChild; q->RightChild = p;
					p = q; q = r;
				}
				else {
					cout << q->data;
					av->LeftChild = LastRight; av->RightChild = top;
					top = av; LastRight = q;
					r = q->LeftChild; q->LeftChild = p;
					r1 = q->RightChild; q->RightChild = r;
					p = r1;
					break;
				}
		}
	}
}


int main(void)
{
	Tree t;
	int eq = -1;
	char select = 'i';
	int max = 0, x = 0;
	while (select != 'q')
	{
		cout << "BinarySearchTree. Select i:Insert, d:Display, e:NonrecInorder, f:preorder, g:postorder, h:copy and compare, q : Quit =>";
		cin >> select;
		switch (select)
		{
		case 'i':
			cout << "The number of items = ";
			cin >> max;
			for (int i = 0; i < max; i++){
				cout << "value= ";
				cin >> x;
				if (!t.Insert(x)) cout << "Insert Duplicated data" << endl;
			}
			break;
		case 'd':
			t.inorder();
			cout << endl;
			break;
		case 'e':
			t.NonrecInorder();
			break;
		case 'f':
			t.preorder();
			break;
		case 'g':
			t.postorder();
			break;
		case 'h':
			eq = (t == Tree(t));
			if (eq) {
				cout << "compare result: true" << endl;
			}else 
				cout << "compare result: false" << endl;
			break;
		case 'q':
			cout << "Quit" << endl;
			break;

		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}

	system("pause");
	return 0;
}
