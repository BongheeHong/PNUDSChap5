﻿//Tree 5.13 Threaded binary tree
/*
* C++ Program to Implement Threaded Binary Tree\
* setup() 대신에 화면에서 입력받으면 tree를 생성하는 프로그램 작성
*/
#include <iostream>
#include <cstdlib>
#define MAX_VALUE 65536
using namespace std;


class ThreadedTree;

class ThreadedNode {
	friend class ThreadedTree;
	friend class ThreadedInorderIterator;
private:
	bool LeftThread;
	ThreadedNode *LeftChild;
	char data;
	ThreadedNode *RightChild;
	bool RightThread;
public:
	ThreadedNode() { LeftChild = RightChild = 0; };
	ThreadedNode(char ch) { data = ch; };
	ThreadedNode(char ch, ThreadedNode *lefty, ThreadedNode *righty,
		bool lthread, bool rthread)
	{
		data = ch; LeftChild = lefty; RightChild = righty;
		LeftThread = lthread;  RightThread = rthread;
	};
};

class ThreadedTree {
	friend class ThreadedInorderIterator;
private:
	ThreadedNode *root;
	void Inorder(ThreadedNode *, bool);
public:
	void setup();
	/* Constructor */
	ThreadedTree() {
		root = new ThreadedNode;
		root->RightChild = root->LeftChild = root;
		root->data = 'z';
		root->LeftThread = true; root->RightThread = false;
	};
	void InsertRight(ThreadedNode*, char);
	bool Insert(char data);
	void Delete(char data);
	void Setup();
	void Inorder();
	void PrintTree();
	bool Search(char data);
	ThreadedNode* InorderSucc(ThreadedNode*);
};


ThreadedNode* ThreadedTree::InorderSucc(ThreadedNode *current)
{
	ThreadedNode *temp = current->RightChild;
	if (!current->RightThread)
		while (!temp->LeftThread) temp = temp->LeftChild;
	return temp;
}


void ThreadedTree::InsertRight(ThreadedNode *s, char ch)
// Create node r; store ch in r; insert r as the right child of s
{
	ThreadedNode *r = new ThreadedNode(ch);
	r->RightChild = s->RightChild;
	r->RightThread = s->RightThread;
	r->LeftChild = s;
	r->LeftThread = true; // LeftChild is a thread
	s->RightChild = r; // attach r to s
	s->RightThread = false;
	if (!r->RightThread) {
		ThreadedNode *temp = InorderSucc(r); // returns the inorder successor of r
		temp->LeftChild = r;
	}
}

/* Fuction to delete an element */
void ThreadedTree::Delete(char data)
{
	ThreadedNode *dest = root->LeftChild, *p = root;
	for (;;)
	{
		if (dest->data < data)
		{
			/* not found */
			if (dest->RightThread)
				return;
			p = dest;
			dest = dest->RightChild;
		}
		else if (dest->data > data)
		{
			/* not found */
			if (dest->LeftThread)
				return;
			p = dest;
			dest = dest->LeftChild;
		}
		else
		{
			/* found */
			break;
		}
	}
	ThreadedNode *target = dest;
	if (!dest->RightThread && !dest->LeftThread)
	{
		/* dest has two children*/
		p = dest;
		/* find largest node at left child */
		target = dest->LeftChild;
		while (!target->RightThread)
		{
			p = target;
			target = target->RightChild;
		}
		/* using replace mode*/
		dest->data = target->data;
	}
	if (p->data >= target->data)
	{
		if (target->RightThread && target->LeftThread)
		{
			p->LeftChild = target->LeftChild;
			p->LeftThread = true;
		}
		else if (target->RightThread)
		{
			ThreadedNode *largest = target->LeftChild;
			while (!largest->RightThread)
			{
				largest = largest->RightChild;
			}
			largest->RightChild = p;
			p->LeftChild = target->LeftChild;
		}
		else
		{
			ThreadedNode *smallest = target->RightChild;
			while (!smallest->LeftThread)
			{
				smallest = smallest->LeftChild;
			}
			smallest->LeftChild = target->LeftChild;
			p->LeftChild = target->RightChild;
		}
	}
	else
	{
		if (target->RightThread && target->LeftThread)
		{
			p->RightChild = target->RightChild;
			p->RightThread = true;
		}
		else if (target->RightThread)
		{
			ThreadedNode *largest = target->LeftChild;
			while (!largest->RightThread)
			{
				largest = largest->RightChild;
			}
			largest->RightChild = target->RightChild;
			p->RightChild = target->LeftChild;
		}
		else
		{
			ThreadedNode *smallest = target->RightChild;
			while (!smallest->LeftThread)
			{
				smallest = smallest->LeftChild;
			}
			smallest->LeftChild = p;
			p->RightChild = target->RightChild;
		}
	}
}void ThreadedTree::Inorder()
{
	Inorder(root, root->LeftThread);
}

void ThreadedTree::Inorder(ThreadedNode *CurrentNode, bool b)
{
	if (!b) {
		Inorder(CurrentNode->LeftChild, CurrentNode->LeftThread);
		cout << " " << CurrentNode->data;
		cout << "Inorder:" << "rightthread=" << CurrentNode->RightThread;
		if (CurrentNode->RightChild != root) Inorder(CurrentNode->RightChild, CurrentNode->RightThread);
	}
}


bool ThreadedTree::Insert(char d)
{
	ThreadedNode *p = root;
	ThreadedNode *q = p;
	bool temp = p->LeftThread;
	while (!temp) {
		q = p;
		if (d == p->data) return false;
		if (d < p->data) { temp = p->LeftThread; p = p->LeftChild; }
		else { temp = p->RightThread; p = p->RightChild; }
		cout << "Insert:: while" << endl;
	}
	p = new ThreadedNode;
	p->data = d;
	//	if (q->LeftChild == q){ q->LeftChild = p;q->LeftThread = false;}
	//	else
	if (d < q->data)
	{
		p->RightChild = q; p->RightThread = true;
		p->LeftChild = q->LeftChild; p->LeftThread = q->LeftThread;
		q->LeftChild = p; q->LeftThread = false;
		cout << "Insert:: go left";
	}
	else
	{
		p->RightChild = q->RightChild; p->RightThread = q->RightThread;
		p->LeftChild = q; p->LeftThread = true;
		q->RightChild = p; q->RightThread = false;
	}
	return true;
}


void ThreadedTree::Setup()
{
	ThreadedNode *A, *B, *C, *D, *E, *F, *G, *H, *I;

	root->LeftChild = A = new ThreadedNode('A', 0, 0, false, false);
	root->LeftThread = false;

	A->LeftChild = B = new ThreadedNode('B', 0, 0, false, false);
	A->RightChild = C = new ThreadedNode('C', 0, 0, false, false);

	B->LeftChild = D = new ThreadedNode('D', 0, 0, false, false);
	B->RightChild = E = new ThreadedNode('E', 0, 0, true, true);

	D->LeftChild = H = new ThreadedNode('H', 0, 0, true, true);
	D->RightChild = I = new ThreadedNode('I', 0, 0, true, true);

	C->LeftChild = F = new ThreadedNode('F', 0, 0, true, true);
	C->RightChild = G = new ThreadedNode('G', 0, 0, true, true);

	H->LeftChild = root; H->RightChild = D;
	I->LeftChild = D; I->RightChild = B;
	E->LeftChild = B; E->RightChild = A;
	F->LeftChild = A; F->RightChild = C;
	G->LeftChild = C; G->RightChild = root;

	InsertRight(A, 'X');
	InsertRight(E, 'Y');
}

/* Function to print tree */
void ThreadedTree::PrintTree()
{
	ThreadedNode *tmp = root, *p;
	for (;;)
	{
		p = tmp;
		tmp = tmp->RightChild;
		if (!p->RightThread)
		{
			while (!tmp->LeftThread)
			{
				tmp = tmp->LeftChild;
			}
		}
		if (tmp == root)
			break;
		cout << tmp->data << "   ";
	}
	cout << endl;
}

class ThreadedInorderIterator {
public:
	void Inorder();
	char *Next();
	ThreadedInorderIterator(ThreadedTree tree) : t(tree) {
		CurrentNode = t.root;
	};
private:
	ThreadedTree t;
	ThreadedNode *CurrentNode;
};

char* ThreadedInorderIterator::Next()
// Find the inorder successor of \fICurrentNode\fR in a threaded binary tree
{
	ThreadedNode *temp = CurrentNode->RightChild;
	if (!CurrentNode->RightThread)
		while (!temp->LeftThread) temp = temp->LeftChild;
	CurrentNode = temp;
	if (CurrentNode == t.root) return 0; // all tree nodes have been traversed
	else return &CurrentNode->data;
}

void ThreadedInorderIterator::Inorder()
{
	for (char *ch = Next(); ch; ch = Next()) 
		cout << *ch << endl;
}



/* Main Contains Menu */

int main()
{
	ThreadedTree t;
	ThreadedInorderIterator ti(t);
	cout << "ThreadedTree Test\n";
	char ch;
	int choice;
	/*  Perform tree operations  */
	do
	{
		cout << "\nThreadedTree Operations\n";
		cout << "1. Insert list " << endl;
		cout << "2. Delete" << endl;
		cout << "3. recursive Inorder" << endl;
		cout << "4. iteratorInorder" << endl;
		cout << "5. Setup" << endl;
		cout << "6. PrintTree" << endl;
		cout << "7. exit" << endl;
		cout << "Enter Your Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter character to insert: ";
			int m;
			cout << "The number of data = ";
			cin >> m;
			for (int i = 0; i < m; i++)
			{
				cout << endl << "The next element = ";
				cin >> ch;
				if (!t.Insert(ch)) cout << "Duplicate data already" << endl;
			}
			break;
		case 2:
			cout << "Enter integer element to delete: ";
			cin >> ch;
			t.Delete(ch);
			break;
		case 3:
			cout << "Recursive Inorder" << endl;
			t.Inorder();
			break;
		case 4:
			cout << "IteratorInorder" << endl;
			ti.Inorder();
			break;
		case 5:
			cout << "Setup" << endl;
			t.Setup();
			break;
		case 6:
			cout << "PrintTree " << endl;
			t.PrintTree();
			break;
		case 7:
			exit(0);
			break;
		default:
			cout << "Wrong Entry" << endl;
			break;
		}
		/*  Display tree  */
		cout << "Tree = ";
		t.PrintTree();
	} while (choice != 7 );

	system("pause");
	return 0;
}
