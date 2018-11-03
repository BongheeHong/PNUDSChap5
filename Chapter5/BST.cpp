//Binary Search Tree
//화면에서 입력받아 BST를 만든다
//입력후 left subtree의 노드 수 – right subtree의 노드 수 >= 5 이상이면 split 호출
// adjust하는 프로그램 작성
//12월 4일 오후 6시
#include <iostream>
using namespace std;

class Element {
public:
	int key;
	Element() {}
	Element(int key) :key(key) {}
};

class BstNode {
	friend class BST;
public:
	void display(int i);
	void treeprint(int i);
private:
	Element data;
	BstNode *LeftChild, *RightChild;
};


class BST {
public:
	BST(BstNode *init = 0) { root = init; };

	//   BST& operator=(const BST&);

	bool Insert(const Element& x);
	//   bool Delete(const Element&);
	BstNode* Search(BstNode*, const Element&);
	BstNode* Search(const Element&);
	BstNode* IterSearch(const Element&);

	void treeprint() { cout << "\n"; root->treeprint(1); }

	void display() {
		cout << "\n";
		if (root) root->display(1);
		else cout << "0\n";
	};
	Element* Split(int i, BST& B, BST& C, Element &x);
private:
	BstNode *root;
};


void BstNode::display(int i)
{
	cout << "Position " << i << ": data.key " << data.key << "\n";
	if (LeftChild) LeftChild->display(2 * i);
	if (RightChild) RightChild->display(2 * i + 1);
};


Element* BST::Split(int i, BST& B, BST& C, Element &x)
// Split the binary search tree with respect to key i
{
	if (!root) {// empty tree
		B.root = C.root = 0; 
		return 0; 
	} 

	BstNode *Y = new BstNode; 
	BstNode *L = Y;
	BstNode *Z = new BstNode;
	BstNode *R = Z;
	BstNode *t = root;
	while (t)
		if (i == t->data.key) {  // split at t
			L->RightChild = t->LeftChild;
			R->LeftChild = t->RightChild;
			x = t->data;
			B.root = Y->RightChild; delete Y;
			C.root = Z->LeftChild; delete Z;
			return &x;
		}
		else if (i < t->data.key) {
			R->LeftChild = t;
			R = t; 
			t = t->LeftChild;
		}
		else {
			L->RightChild = t;
			L = t;
			t = t->RightChild;
		}
	L->RightChild = R->LeftChild = 0;
	B.root = Y->RightChild; 
	delete Y;
	C.root = Z->LeftChild; 
	delete Z;
	return 0;
}


void BstNode::treeprint(int l)
{
	if (this) {
		(this->RightChild)->treeprint(l + 1);
		for (int i = 1; i <= l; i++) cout << "   ";
		cout << this->data.key << "\n";
		(this->LeftChild)->treeprint(l + 1);
	};
};


BstNode* BST::Search(BstNode* b, const Element &x)
{
	if (!b) return 0;
	if (x.key == b->data.key) return b;
	if (x.key < b->data.key) return Search(b->LeftChild, x);
	return Search(b->RightChild, x);
};


BstNode* BST::Search(const Element& x)
{
	return Search(root, x);
}


BstNode* BST::IterSearch(const Element& x)
{
	for (BstNode *t = root; t; )
	{
		if (x.key == t->data.key) return t;
		if (x.key < t->data.key) t = t->LeftChild;
		else t = t->RightChild;
	}
	return 0;
}


bool BST::Insert(const Element& x)
{
	BstNode *p = root;  
	BstNode *q = 0;
	while (p) {
		q = p;
		if (x.key == p->data.key) return false; //x.key is already in t
		if (x.key < p->data.key) p = p->LeftChild;
		else p = p->RightChild;
	};
	p = new BstNode;
	p->LeftChild = p->RightChild = 0; p->data = x;
	if (!root) root = p;
	else if (x.key < q->data.key) q->LeftChild = p;
	else q->RightChild = p;
	return true;
}


//void test(){
//	BST m;
//	Element a, b, c, d, e, f, g, h, i, j, k, l;
//	a.key = 5; b.key = 3; c.key = 11; d.key = 33; e.key = 15;
//	f.key = 2; g.key = 8; h.key = 22; i.key = 20; j.key = 9;
//	k.key = 99; l.key = 77;
//	cout << "\n" << "1: success of insert key:" << a.key << "::" << m.Insert(a);
//	cout << "\n" << "1: success of insert key:" << b.key << "::" << m.Insert(b);
//	//m.treeprint();
//	cout << "\n" << "1: success of insert key:" << c.key << "::" << m.Insert(c);
//	//   m.treeprint();
//	cout << "\n" << "1: success of insert key:" << d.key << "::" << m.Insert(d);
//	m.treeprint();
//
//	cout << "\n" << "1: success of insert key:" << e.key << "::" << m.Insert(e);
//	//   m.treeprint();
//	cout << "\n" << "1: success of insert key:" << f.key << "::" << m.Insert(f);
//	//   m.treeprint();
//	cout << "\n" << "1: success of insert key:" << g.key << "::" << m.Insert(g);
//	//   m.treeprint();
//	cout << "\n" << "1: success of insert key:" << h.key << "::" << m.Insert(h);
//	//   m.treeprint();
//	cout << "\n" << "1: success of insert key:" << i.key << "::" << m.Insert(i);
//	//   m.treeprint();
//	cout << "\n" << "1: success of insert key:" << j.key << "::" << m.Insert(j);
//	m.treeprint();
//	BST n, o;
//	Element el;
//	cout << endl << "After splitting BST: m" << endl;
//	cout << "splitting of BST m into two substrees: n and o, splitted value = ";
//	cout << (m.Split(22, n, o, el))->key << endl;
//	cout << "The splitted BST: n" << endl;
//	n.treeprint();
//	cout << "The splitted BST: o" << endl;
//	o.treeprint();
//
//	cout << "\n" << (m.Search(j) == m.IterSearch(j));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(i) == m.IterSearch(i));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(b) == m.IterSearch(b));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(a) == m.IterSearch(a));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(d) == m.IterSearch(d));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(c) == m.IterSearch(c));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(f) == m.IterSearch(f));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(e) == m.IterSearch(e));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(g) == m.IterSearch(g));
//	//   m.treeprint();
//	cout << "\n" << (m.Search(h) == m.IterSearch(h));
//	//   m.treeprint();
//}

int main() {
	int select = 0;
	int data = 0;
	BST tree;
	BST splitTree1;
	BST splitTree2;
	Element ele;

	Element *tempEle;

	do {
		cout << "binary search tree. Select: 1 insert, 2 display, 3 split, >=5 exit" << endl;
		cin >> select;
		switch (select) {
		case 1:
			cout << "input value: ";
			cin >> data;
			tree.Insert(Element(data));
			tree.treeprint();
			break;
		case 2:
			tree.display();
			break;
		case 3:
			cout << "intput splited tree note: ";
			cin >> data;
			tempEle = tree.Split(data, splitTree1, splitTree2, ele);
			if (tempEle != 0) {
				cout << "sub-tree1: " << endl;
				splitTree1.treeprint();
				cout << "sub-tree2: " << endl;
				splitTree2.treeprint();
			}
			break;
		case 5:
			exit(1);
			break;

		}
	} while (select < 5);

	return 0;
}
