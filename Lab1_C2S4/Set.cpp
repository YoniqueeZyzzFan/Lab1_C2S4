#include <iostream>
#include <string>

class MyIterator;
template <typename T>
class AvlTree {
private:
	template <typename T>
	struct node {
		node* right;
		node* left;
		T data;
		int height;
		node(T value = 0 ) { height = 0; data = value; right = nullptr; left = nullptr;}
	};
	bool findr(node<T>* p, T value) const {
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
	node<T>* findmin(node<T>* p) {
		if (p->left != nullptr) { return findmin(p->left); }
		else return p;
	}
	node<T>* balance(node<T>* p) {
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
	int height(node<T>* p) {
		return p ? p->height : 0;
	}
	int BalanceFactor(node<T>* p) {
		return height(p->left) - height(p->right);
	}
	void FixHeight(node<T>* p) {
		int rl = p->left ? p->left->height : 0;
		int rh = p->right ? p->right->height : 0;
		p->height = (rl > rh ? rl : rh) + 1;
	}
	node<T>* TurnRight(node<T>* p) {
		node<T>* q = p->left;
		p->left = q->right;
		q->right = p;
		FixHeight(p);
		FixHeight(q);
		return q;
	}
	node<T>* TurnLeft(node<T>* p) {
		node<T>* q = p->right;
		p->right = q->left;
		q->left = p;
		FixHeight(p);
		FixHeight(q);
		return q;
	}
	node<T>* removemin(node<T>* p) {
		if (p->left == 0) {
			return p->right;
		}
		p->left = removemin(p->left);
		return balance(p);
	}
	node<T>* remove(node<T>* p, T value) {
		if (!p) return nullptr;
		if (value < p->data) p->left = remove(p->left, value);
		else if (value > p->data)  p->right = remove(p->right, value);
		else {
			node<T>* q = p->left;
			node<T>* r = p->right;
			delete p;
			if (!r) return q;
			node<T>* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}
	node<T>* insert(node<T>* root, T value) {
		if (!root) {
			root = new node<T>(value);
			root->height = 0;
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
	node<std::string>* insert(node<std::string>* root, std::string value) {
		if (!root) {
			root = new node<std::string>(value);
			root->height = 0;
			root->left = nullptr;
			root->right = nullptr;
		}
		else if (value.length() < root->data.length()) {
			root->left = insert(root->left, value);
		}
		else {
			root->right = insert(root->right, value);
		}
		return balance(root);
	}
	void print_Tree(node<T>* p, int level = 0) const
	{
		if (p)
		{
			print_Tree(p->right, level + 1);
			for (int i = 0; i < level; i++) std::cout << "   ";
			std::cout << p->data << std::endl;
			print_Tree(p->left, level + 1);
		}
	}
	void clear(node<T>* p) {
		while (p != nullptr) {
			p = remove(p, p->data);
		}
	}
	node<T>* copy(node<T>* p) {
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
	node<T>* root;
public:
	AvlTree() {
		root = nullptr;
	}
	void insert(T value) {
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
	bool find(T key) const {
		return findr(root, key);
	}
	void erase(T key) {
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
		AvlTree<T>	* tree;
		AvlTree::node<T>* root;
		AvlTree::node<T>* head;
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
		T& operator*() {
			return head->data;
		}
	};
	MyIterator begin() {
		return MyIterator(this);
	}
};
