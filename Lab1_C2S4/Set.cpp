#include <iostream>
#include <string>

class MyIterator;
template <typename T>
class AvlTree {
private:
	template <typename T>
	struct node {
		node* next;
		node* prev;
		node* right;
		node* left;
		T data;
		int height;
		node(T value = 0) { height = 0; data = value; right = nullptr; left = nullptr; next = nullptr; prev = nullptr; }
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
	node<T>* insert(node<T>* root, node<T>* parent, T value) {
		if (!root) {
			root = new node<T>(value);
			if (_tail == nullptr) _tail = root;
			if (_begin == nullptr) _begin = root;
			if (parent!=nullptr && parent->data > root->data) {
				node<T>* tmp = parent->prev;
				parent->prev = root;
				root->next = parent;
				root->prev = tmp;
				if (tmp != nullptr) tmp->next = root;
				if(_begin->data > value) _begin = root;
			}
			if (parent!=nullptr && parent->data < root->data) {
				node<T>* tmp = parent->next;
				parent->next = root;
				root->prev = parent;
				root->next = tmp;
				if (tmp != nullptr) tmp->prev = root;
				if(_tail->data < value) _tail = root;
			}
		}
		else if (value < root->data) {
			root->left = insert(root->left,root, value);
		}
		else {
			root->right = insert(root->right,root, value);
		}
		return balance(root);
	}
	node<std::string>* insert(node<std::string>* root, node<std::string>* parent, std::string value) {
		if (!root) {
			root = new node<std::string>(value);
			if (parent!=nullptr && parent->data.length() > root->data.length()) {
				node<std::string>* tmp = parent->prev;
				parent->prev = root;
				root->next = parent;
				root->prev = tmp;
				if (tmp != nullptr) tmp->next = root;
			}
			if(parent!=nullptr && parent->data.length() < root->data.length()){
				node<std::string>* tmp = parent->next;
				parent->next = root;
				root->prev = parent;
				root->next = tmp;
				if (tmp != nullptr) tmp->prev = root;
			}
		}
		else if (value.length() < root->data.length()) {
			root->left = insert(root->left, root, value);
		}
		else {
			root->right = insert(root->right, root, value);
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
	node<T>* _begin;
	node<T>* _tail;
public:
	AvlTree() {
		root = nullptr;
		_begin = nullptr;
		_tail = nullptr;
	}
	void insert(T value) {
		if (findr(root, value) != true) {
			root = insert(root,root, value);
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
		AvlTree<T>* owner;
		AvlTree::node<T>* root;
	public:
		MyIterator() = delete;
		MyIterator(AvlTree::node<T>* rhs, AvlTree<T>* own) :root(rhs), owner(own) {}
		MyIterator operator++() {
			if (root == nullptr) return *this;
			root = root->next;
			return *this;
		}
		MyIterator operator--() {
			if (root == nullptr) return *this;
			root = root->prev;
			return *this;
		}
		bool operator == (const MyIterator & rhs){
			return root == rhs.root;
		}
		bool operator !=(const MyIterator& rhs) {
			return !(root==rhs.root);
		}
		T& operator*() {
			if (root != nullptr) return root->data;
			else throw "Nullptr";
		}
	};
	MyIterator begin() {
		return MyIterator(this->_begin, this);
	}
	MyIterator end() {
		return MyIterator(this->_tail->next, this);
	}

	class rMyIterator {
		AvlTree<T>* owner;
		AvlTree::node<T>* root;
	public:
		rMyIterator() = delete;
		rMyIterator(AvlTree::node<T>* rhs, AvlTree<T>* own) :root(rhs), owner(own) {}
		rMyIterator operator++() {
			if (root == nullptr) return *this;
			root = root->prev;
			return *this;
		}
		rMyIterator operator--() {
			if (root == nullptr) return *this;
			root = root->next;
			return *this;
		}
		bool operator == (const rMyIterator& rhs) {
			return root == rhs.root;
		}
		bool operator !=(const rMyIterator& rhs) {
			return !(root==rhs.root);
		}
		T& operator*() {
			if (root != nullptr) return root->data;
			else throw "Nullptr";
		}
	};
	rMyIterator rbegin() {
		return rMyIterator(this->_tail, this);
	}
	rMyIterator rend() {
		return rMyIterator(this->_begin->prev, this);
	}
};
