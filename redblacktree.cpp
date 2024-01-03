#include <iostream>
#include <queue>
#include "redblacktree.h"

RedBlackTree::RedBlackTree() {
	NIL = new Node(0, BLACK);
	root = NIL;
}

RedBlackTree::~RedBlackTree() {
	delete NIL;
}

void RedBlackTree::leftRotate(Node* x) {
	Node* y = x -> right;
	x -> right = y -> left;
	if(y -> left != NIL) {
		y -> left -> parent = x;
	}
	y -> parent = x -> parent;
	if(x -> parent == NIL) {
		root = y;
	} else if (x == x -> parent -> left) {
		x -> parent -> left = y;
	} else {
		x -> parent -> right = y;
	}
	y -> left = x;
	x -> parent = y;
}

void RedBlackTree::rightRotate(Node* y) {
	Node* x = y -> left;
	y -> left = x -> right;
	if(x -> right != NIL) {
		x -> right -> parent = y;
	}
	x -> parent = y -> parent;
	if(y -> parent == NIL) {
		root = x;
	} else if (y == y -> parent -> left) {
		y -> parent -> left = x;
	} else {
		y -> parent -> right = x;
	}
	x -> right = y;
	y -> parent = x;
}

void RedBlackTree::insert(int key) {
	Node* z = new Node(key);
	Node* y = NIL;
	Node* x = root;
	while(x != NIL) {
		y = x;
		if(z -> key < x -> key) {
			x = x -> left;
		} else {
			x = x -> right;
		}
	}
	z -> parent = y;
	if(y == NIL) {
		root = z;
	} else if (z -> key < y -> key) {
		y -> left = z;
	} else {
		y -> right = z;
	}
	z -> left = NIL;
	z -> right = NIL;
	z -> color = RED;
	insertFixtUp(z);//can be violated 2 and 4 properties
}
void RedBlackTree::insertFixtUp(Node* z) {
	while (z -> parent -> color == RED) {
		if(z -> parent == z -> parent -> parent -> left) {
			Node* uncle = z -> parent -> parent -> right;
			if(uncle -> color == RED) {
				//case 1
				z -> parent -> color = BLACK;
				uncle -> color = BLACK;
				z -> parent -> parent -> color = RED;
				z = z -> parent -> parent;
			} else {
				if(z == z -> parent -> right) {
					//case 2
					z = z -> parent;
					leftRotate(z);
				}
				//case 3
				z -> parent -> color = BLACK;
				z -> parent -> parent -> color = RED;
				rightRotate(z -> parent -> parent);
			}
		}
		else {//z -> parent == z -> parent -> parent -> right
				Node* uncle = z -> parent -> parent -> left;
				if(uncle -> color == RED) {
				//case 1
					z -> parent -> color = BLACK;
					uncle -> color = BLACK;
					z -> parent -> parent -> color = RED;
					z = z -> parent -> parent;
			} else {
				if(z == z -> parent -> left) {
					//case2
					z = z -> parent;
					rightRotate(z);
				} else {
					//case3
					z -> parent -> color = BLACK;
					z -> parent -> parent -> color = RED;
					leftRotate(z -> parent -> parent);
				}
			}
		}
	}
		root -> color = BLACK;
	
}
void RedBlackTree::inorderTraverse(Node* z) {
	if(z != NIL) {
		inorderTraverse(z -> left);
		std::cout << z -> key << (z -> color == BLACK ?  "B" :  "R") << " ";
		inorderTraverse(z -> right);
	}
}
void RedBlackTree::print() {
	inorderTraverse(root);
}
void RedBlackTree::transplant(Node* u, Node* v) {
	if(u -> parent == NIL) {
		root = v;
	}
	if(u  == u -> parent -> left) {
		u -> parent -> left = v;
	} else {
		u -> parent -> right = v;
	}
	v -> parent = u -> parent;
}
void RedBlackTree::remove(int key) {
	Node* z = root;
	while(z != NIL) {
		if (z -> key < key) {
			z = z -> right;
		} else if(key < z -> key){
			z = z -> left;
		} else {//z -> key == key
			Node* y = z;
			Color yOrigColor = y -> color;
			Node* x;
			if(z -> left == NIL) {
				x = z -> right;
				transplant(z, z -> right);
			} else if (z -> right == NIL) {
				x = z ->left;
				transplant(z, z-> left);
			} else {
				//it has 2 child
				y = z -> right;
				while(y -> left != NIL) {
					y = y -> left;//successor
				}		
				yOrigColor = y -> color;
				x = y -> right;
				if(y -> parent == z) {
					x -> parent = y;
				} else {
					transplant(y, y -> right);
					y -> right = z -> right;
					y -> right -> parent = y;
				}
				transplant(z, y);
				y -> left = z -> left;
				y -> left -> parent = y;
				y -> color = z -> color ;
			}
		if(yOrigColor == BLACK) {
				deleteFixUp(x);
			}
			delete z;
			return;
		}
	}
}
void RedBlackTree::deleteFixUp(Node* x) {
	//5th property violated
	while(x != root && x -> color == BLACK){
		if(x == x -> parent -> left) {
			Node* sibling = x -> parent -> right;
			if(sibling -> color == RED) {
				//case 1
				sibling -> color = BLACK;
				x -> parent -> color = RED;
				leftRotate(x -> parent);
				sibling = x -> parent -> right;
			}
			if(sibling -> left -> color == BLACK && sibling -> right -> color == BLACK) {
					//case 2
					sibling -> color = RED;
					x = x -> parent;
			} else {
				if(sibling -> right -> color == BLACK) {
					//case 3
					sibling -> left -> color = BLACK;
					sibling -> color = RED;
					rightRotate(sibling);
					sibling = x -> parent -> right;	
				}
				//case 4
					sibling -> color = x -> parent -> color;
					x -> parent -> color = BLACK;
					sibling -> right -> color = BLACK;
					leftRotate(x -> parent);
					x = root;
			}
		}		
		else {
			//x == x -> parent -> right
			Node* sibling = x -> parent -> left;
			if(sibling -> color == RED) {
				//case1
				sibling -> color = BLACK;
				x -> parent -> color = RED;
				rightRotate(x -> parent);
				sibling = x -> parent -> left;
			}
			if(sibling -> right -> color == BLACK && sibling -> left -> color == BLACK) {
			//case2
			sibling -> color = RED;
			x = x -> parent;		
			} else {
				if(sibling -> left -> color == BLACK) { //case3
					sibling -> right -> color = BLACK;
					sibling -> color = RED;
					leftRotate(sibling);
					sibling = x -> parent -> left;
				}
				//case4
				sibling -> color = x -> parent -> color;
				x -> parent -> color = BLACK;
				sibling -> left -> color = BLACK;
				rightRotate(x -> parent);
				x = root;
			}
		}
	}
	x -> color = BLACK;
}
void RedBlackTree::printLevel(Node *root) {
	if(root == NIL) {
		return;
	}
	std::queue<Node *>q;
	q.push(root);
	while(!q.empty()) {
		int lvlSize = q.size();
		for(int i = 0; i < lvlSize; ++i) {
			Node* curr = q.front();
			q.pop();

			std::cout << curr -> key;
			if(curr -> color == RED) {
				std::cout << "R" << " ";
			} else {
				std::cout << "B" << " ";
			}
			if(curr -> left != nullptr) {
				q.push(curr -> left);
			}
			if(curr -> right != nullptr) {
				q.push(curr -> right);
			}
		}
			std::cout << std::endl;
	}
}
void RedBlackTree::printWithLvl() {
	printLevel(root);
}
int main()
{
	RedBlackTree rb;
	rb.insert(10);
	rb.insert(20);
	rb.insert(5);
	rb.insert(6);
	rb.insert(12);

	std::cout << "Current tree - \n";
//	rb.print();
//	rb.remove(6);
//	std::cout << "\nAfter removing 6 - ";
//	rb.print();
	rb.printWithLvl();

	
}
