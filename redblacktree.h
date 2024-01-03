#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

enum Color {BLACK, RED};

struct Node {
	int key;
	Color color;
	Node* parent;
	Node* left;
	Node* right;
	Node(int k, Color color = RED, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : key(k), color(color), parent(p), left(l), right(r) {}
};

class RedBlackTree {
private:
	Node* NIL;
	Node* root;	

private:
	void leftRotate(Node*);
	void rightRotate(Node*);
	void insertFixtUp(Node*);
	void transplant(Node*, Node*);
	void deleteFixUp(Node*);
	

public:
	RedBlackTree();
	~RedBlackTree();
	void insert(int);
	void remove(int);
	void inorderTraverse(Node*);
	void print();
	void printLevel(Node*);
	void printWithLvl();
};
#endif //REDBLACKTREE_H
