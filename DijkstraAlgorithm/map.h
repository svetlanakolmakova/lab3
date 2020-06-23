#pragma once
#define RED true
#define BLACK false

#include"list.h"
#include<string>

using namespace std;
template<typename T, typename T1>
class Map {
public:
	class Node
	{
	public:
		Node(bool color = RED, T key = T(), Node* parent = NULL, Node* left = NULL, Node* right = NULL, T1 value = T1()) :color(color), key(key), parent(parent), left(left), right(right), value(value) {}
		T key;
		T1 value;
		bool color;
		Node* parent;
		Node* left;
		Node* right;
	};

	~Map() {
		if (this->Top != NULL)
			this->clear();
		Top = NULL;
		delete Leaf;
		Leaf = NULL;
	}

	Map(Node* Top = NULL, Node* Leaf = new Node(0)) :Top(Top), Leaf(Leaf) {}

	void  insert(T key, T1 value) {

		if (this->Top != NULL) {
			Node* node = NULL;
			Node* parent = NULL;
			for (node = this->Top; node != Leaf; )// Search leaf for new element 
			{
				parent = node;
				if (key < node->key)
					node = node->left;
				else if (key > node->key)
					node = node->right;
				else if (key == node->key)
					throw std::out_of_range("key is repeated");
			}
			node = new Node(RED, key, Leaf, Leaf, Leaf, value);
			node->parent = parent;
			if (parent != Leaf) {
				if (key < parent->key)
					parent->left = node;
				else
					parent->right = node;
			}
			BalanceTree(node);
		}
		else {
			this->Top = new Node(BLACK, key, Leaf, Leaf, Leaf, value);
		}
	}
	List<T>* get_keys() {
		List<T>* list = new List<T>();
		this->ListKeyOrValue(1, list);
		return list;
	}
	List<T1>* get_values() {
		List<T1>* list = new List<T1>();
		this->ListKeyOrValue(2, list);
		return list;
	}
	T1 find(T key) {
		Node* node = Top;
		while (node != Leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != Leaf)
			return node->value;
		else
			throw std::out_of_range("Key is missing");
	}
	void clear() {
		this->clear_tree(this->Top);
		this->Top = NULL;
	}
	bool is_in_map(T key) {
		Node* node = Top;
		while (node != nullptr && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != nullptr)
			return true;
		else
			return false;
	}
	void add_entry(T key) {
		Node* current = this->get_node(key);
		current->value++;
	}
	void Delete(T key) {
		Node* needed = Top;
		// находим узел с ключом key
		while (needed->key != key) {
			if (needed->key < key)
				needed = needed->right;
			else
				needed = needed->left;
		}
		deleteNode(needed);
	}

private:
	Node* Top;
	Node* Leaf;
	Node* get_node(T key) {
		Node* node = Top;

		while (node != Leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != Leaf)
			return node;

	}
	void deleteNode(Node* current) {
		Node* fixed, *changed;


		// delete node current from tree  

		if (!current || current == Leaf) return;


		if (current->left == Leaf || current->right == Leaf) {
			/* changed has a Leaf node as a child */
			changed = current;
		}
		else {
			/* find tree successor with a Leaf node as a child */
			changed = current->right;
			while (changed->left != Leaf) changed = changed->left;
		}

		/* fixed is changed's only child */
		if (changed->left != Leaf)
			fixed = changed->left;
		else
			fixed = changed->right;

		/* remove changed from the parent chain */
		fixed->parent = changed->parent;
		if (changed->parent)
			if (changed == changed->parent->left)
				changed->parent->left = fixed;
			else
				changed->parent->right = fixed;
		else
			Top = fixed;

		if (changed != current) {
			current->key = changed->key;
			current->value = changed->value;
		}

		if (changed->color == BLACK)
			BalanceTree(fixed);
	}
	void clear_tree(Node* tree) {
		if (tree != Leaf) {
			clear_tree(tree->left);
			clear_tree(tree->right);
			delete tree;
		}
	}

	void ListKeyOrValue(int mode, List<T>* list) {
		if (this->Top != Leaf)
			this->KeyOrValue(Top, list, mode);
		else
			throw std::out_of_range("Tree empty!");
	}
	void KeyOrValue(Node* tree, List<T>* list, int mode) {

		if (tree != Leaf) {
			KeyOrValue(tree->left, list, mode);
			if (mode == 1)
				list->push_back(tree->key);
			else
				list->push_back(tree->value);
			KeyOrValue(tree->right, list, mode);
		}
	}
	Node* minimum(Node* node) {
		while (node->left != Leaf)
		{
			node = node->left;
		}
		return node;
	}
	
	Node* maximum(Node* node) {
		while (node->right != Leaf)
		{
			node = node->right;
		}
		return node;
	}

	Node* grandparent(Node* cur) {
		if ((cur != Leaf) && (cur->parent != Leaf))
			return cur->parent->parent;
		else
			return Leaf;
	}

	Node* uncle(Node* cur) {
		Node* cur1 = grandparent(cur); //assisting node
		if (cur1 == Leaf)
			return Leaf; // No grandparent means no uncle
		if (cur->parent == cur1->left)
			return cur1->right;
		else
			return cur1->left;
	}

	Node* sibling(Node* cur) {
		if (cur == cur->parent->left)
			return cur->parent->right;
		else
			return cur->parent->left;
	}

	Node* find_key(T key) {
		Node* node = this->Top;
		while (node != Leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != Leaf)
			return node;
		else
			throw std::out_of_range("Key is missing");
	}

	//balance tree
	void BalanceTree(Node* node) {
		Node* uncle;
		/* Current node is RED */
		while (node != this->Top && node->parent->color == RED)//
		{
			/* node in left tree of grandfather */
			if (node->parent == this->grandparent(node)->left)//
			{
				/* node in left tree of grandfather */
				uncle = this->uncle(node);
				if (uncle->color == RED) {
					/* Case 1 - uncle is RED */
					node->parent->color = BLACK;
					uncle->color = BLACK;
					this->grandparent(node)->color = RED;
					node = this->grandparent(node);
				}
				else {
					/* Cases 2 & 3 - uncle is BLACK */
					if (node == node->parent->right) {
						/*Reduce case 2 to case 3 */
						node = node->parent;
						this->left_rotate(node);
					}
					/* Case 3 */
					node->parent->color = BLACK;
					this->grandparent(node)->color = RED;
					this->right_rotate(this->grandparent(node));
				}
			}
			else {
				/* Node in right tree of grandfather */
				uncle = this->uncle(node);
				if (uncle->color == RED) {
					/* Uncle is RED */
					node->parent->color = BLACK;
					uncle->color = BLACK;
					this->grandparent(node)->color = RED;
					node = this->grandparent(node);
				}
				else {
					/* Uncle is BLACK */
					if (node == node->parent->left) {
						node = node->parent;
						this->right_rotate(node);
					}
					node->parent->color = BLACK;
					this->grandparent(node)->color = RED;
					this->left_rotate(this->grandparent(node));
				}
			}
		}
		this->Top->color = BLACK;
	}


	//Rotation
	void left_rotate(Node* node) {
		Node* right = node->right;
		/* Create node->right link */
		node->right = right->left;
		if (right->left != Leaf)
			right->left->parent = node;
		/* Create right->parent link */
		if (right != Leaf)
			right->parent = node->parent;
		if (node->parent != Leaf) {
			if (node == node->parent->left)
				node->parent->left = right;
			else
				node->parent->right = right;
		}
		else {
			this->Top = right;
		}
		right->left = node;
		if (node != Leaf)
			node->parent = right;
	}
	void right_rotate(Node* node) {
		Node* left = node->left;
		/* Create node->left link */
		node->left = left->right;
		if (left->right != Leaf)
			left->right->parent = node;
		/* Create left->parent link */
		if (left != Leaf)
			left->parent = node->parent;
		if (node->parent != Leaf) {
			if (node == node->parent->right)
				node->parent->right = left;
			else
				node->parent->left = left;
		}
		else {
			this->Top = left;
		}
		left->right = node;
		if (node != Leaf)
			node->parent = left;
	}
};
