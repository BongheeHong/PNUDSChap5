#ifndef _IOSTREAM_H
#include <iostream>
#define _IOSTREAM_H
#endif

using namespace std;

enum TypesOfData {
	LogicalNot, LogicalAnd, LogicalOr,
	LogicalTrue, LogicalFalse
};

class SatTree;

class SatNode {
	friend class SatTree;
private:
	SatNode *LeftChild;
	TypesOfData data;
	bool value;
	SatNode *RightChild;
	SatNode() { LeftChild = RightChild = 0; };

	SatNode(TypesOfData tod) {
		data = tod;
	}

	SatNode(TypesOfData tod, SatNode *Lefty, SatNode *Righty)
	{
		data = tod;
		LeftChild = Lefty;
		RightChild = Righty;
	}
};

class SatTree {
private:
	SatNode *root;
	void PostOrderEval(SatNode *);
public:
	void PostOrderEval();
	SatTree() { root = 0; };
	void setup();
	void setup2();
	void rootvalue() { 
		cout << "result: ";
		if (root->value) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}
	};
};



void SatTree::PostOrderEval()
{
	PostOrderEval(root);
}

void SatTree::PostOrderEval(SatNode *s)
{
	if (s) {
		PostOrderEval(s->LeftChild);
		PostOrderEval(s->RightChild);
		switch (s->data) {
		case LogicalNot: 
			s->value = !s->RightChild->value;
			break;
		case LogicalAnd: 
			s->value = s->LeftChild->value && s->RightChild->value;
			break;
		case LogicalOr: 
			s->value = s->LeftChild->value || s->RightChild->value;
			break;
		case LogicalTrue: 
			s->value = true;
			break;
		case LogicalFalse: 
			s->value = false;
		}
	}
}

//(False|True)&(!False), result = True
void SatTree::setup()
{
	root = new SatNode(LogicalAnd);
	root->LeftChild = new SatNode(LogicalOr);
	root->LeftChild->LeftChild = new SatNode(LogicalFalse);
	root->LeftChild->RightChild = new SatNode(LogicalTrue);
	root->RightChild = new SatNode(LogicalNot);
	root->RightChild->RightChild = new SatNode(LogicalFalse);

	cout << "set up: (False|True)&(!False)" << endl;
}

//(False & True) | (False)
void SatTree::setup2() {
	root = nullptr;
	
	root = new SatNode(LogicalOr);
	root->LeftChild = new SatNode(LogicalAnd);
	root->LeftChild->LeftChild = new SatNode(LogicalFalse);
	root->LeftChild->RightChild = new SatNode(LogicalTrue);
	root->RightChild = new SatNode(LogicalFalse);

	cout << "set up: (False & True) | (False)" << endl;
}

void main()
{
	SatTree t;
	t.setup();
	t.PostOrderEval();
	t.rootvalue();

	t.setup2();
	t.PostOrderEval();
	t.rootvalue();
	cout << endl;
	system("pause");
}

