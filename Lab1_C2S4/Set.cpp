#include <iostream>
class MyIterator;

class AvlTree {
private:
	struct node {
		node* right;
		node* left;
		int data;
		int height;
		node(int value = 0) { height = 0; data = value; right = nullptr; left = nullptr; }
	};
	bool findr(node* p, int value) const {
		while (p != nullptr) {
			if (p->data < value) {
				p = p->right;
			}
			else if (p->data > value) {
				p = p->left;
			}
			else return true;
		}
		return false;
	}
	node* findmin(node* p) {
		if (p->left != nullptr) { return findmin(p->left); }
		else return p;
	}
	node* balance(node* p) {
		FixHeight(p);
		int dh = BalanceFactor(p);
		if (dh == 2) {
			if (height(p->left->right) > height(p->left->left)) {
				p->left = TurnLeft(p->left);
			}
			p = TurnRight(p);
		}
		else if (dh == -2) {
			if (height(p->right->left) > height(p->right->right)) {
				p->right = TurnRight(p->right);
			}
			p = TurnLeft(p);

		}
		return p;
	}
	int height(node* p) {
		return p ? p->height : 0;
	}
	int BalanceFactor(node* p) {
		return height(p->left) - height(p->right);
	}
	void FixHeight(node* p) {
		int rl = p->left ? p->left->height : 0;
		int rh = p->right ? p->right->height : 0;
		p->height = (rl > rh ? rl : rh) + 1;
	}
	node* TurnRight(node* p) {
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		FixHeight(p);
		FixHeight(q);
		return q;
	}
	node* TurnLeft(node* p) {
		node* q = p->right;
		p->right = q->left;
		q->left = p;
		FixHeight(p);
		FixHeight(q);
		return q;
	}
	node* removemin(node* p) {
		if (p->left == 0) {
			return p->right;
		}
		p->left = removemin(p->left);
		return balance(p);
	}
	node* remove(node* p, int value) {
		if (!p) return nullptr;
		if (value < p->data) p->left = remove(p->left, value);
		else if (value > p->data)  p->right = remove(p->right, value);
		else {
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}
	node* insert(node* root, int value) {
		if (!root) {
			root = new node;
			root->height = 0;
			root->data = value;
			root->left = nullptr;
			root->right = nullptr;
		}
		else if (value < root->data) {
			root->left = insert(root->left, value);
		}
		else {
			root->right = insert(root->right, value);
		}
		return balance(root);
	}
	void print_Tree(node* p, int level = 0) const
	{
		if (p)
		{
			print_Tree(p->right, level + 1);
			for (int i = 0; i < level; i++) std::cout << "   ";
			std::cout << p->data << std::endl;
			print_Tree(p->left, level + 1);
		}
	}
	void clear(node* p) {
		while (p != nullptr) {
			p = remove(p, p->data);
		}
	}
	node* copy(node* p) {
		if (p) {
			node* nr = new node;
			nr->data = p->data;
			nr->height = p->height;
			nr->right = copy(p->right);
			nr->left = copy(p->left);
			return nr;
		}
		return p;
	}
	node* root;
public:
	AvlTree() {
		root = nullptr;
	}
	void insert(int value) {
		if (findr(root, value) != true) {
			root = insert(root, value);
		}
	}
	void treeprint() const {
		if (root == nullptr) {
			std::cout << "Clear" << std::endl;
			return;
		}
		print_Tree(root);
	}
	bool find(int key) const {
		return findr(root, key);
	}
	void erase(int key) {
		root = remove(root, key);
	}
	~AvlTree() {
		clear(root);
		root = nullptr;
	}
	AvlTree(const AvlTree& at) {
		root = copy(at.root);
	}
	AvlTree& operator=(const AvlTree& rhs) {
		if (this == &rhs) return *this;
		clear(root);
		root = copy(rhs.root);
	}
	class MyIterator {
		AvlTree* tree;
		AvlTree::node* root;
		AvlTree::node* head;
	public:
		MyIterator() = delete;
		MyIterator(AvlTree* rhs) : tree(rhs) {
			root = rhs->root;
			head = rhs->root;
			while (root != nullptr && head->left != nullptr) {
				head = head->left;
				while (root->left != head) {
					root = root->left;
				}
			}
		}
		MyIterator& operator++() {

		}
		int& operator*() {
			return head->data;
		}
	};
	MyIterator begin() {
		return MyIterator(this);
	}
};



