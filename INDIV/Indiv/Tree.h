#pragma once

#include <iostream>
#include <string>
#include "MyException.h"

using namespace std;

template <class T>
class Tree {
private:
	struct node {
		T data;
		node* left;
		node* right;

		node(
			T data = 0,
			node* left = nullptr,
			node* right = nullptr
		) {
			this->data = data;
			this->left = left;
			this->right = right;
		}



	};

	node* root;

	//============служебные_функции============


	//tree->new_tree
	void copy(node*& new_tree, node* tree) {
		if (tree) {
			new_tree = new node(tree->data);
			copy(new_tree->left, tree->left);
			copy(new_tree->right, tree->right);
		}
		else {
			new_tree = nullptr;
		}
	}

	void delete_tree(node* tree) {
		if (tree) {
			delete_tree(tree->left);
			delete_tree(tree->right);
			delete tree;
		}
	}

	void add_element(node*& tree, const T& element) {
		if (tree) {
			if (element > tree->data) {
				add_element(tree->right, element);
			}
			else {
				add_element(tree->left, element);
			}
		}
		else {
			tree = new node(element);
		}
	}

	void printLKR(node* tree, ostream& os) const {
		if (tree) {
			printLKR(tree->left, os);
			os << tree->data << " ";
			printLKR(tree->right, os);
		}
	}


	bool find_element(node* tree, const T& element) {
		if (!tree) return false;
		else if (tree && (tree->data == element)) return true;
		else if (element > tree->data) find_element(tree->right, element);
		else if (element < tree->data) find_element(tree->left, element);
	}

	node*& get_node(node * &tree, const T& element) {
		if (!tree) {
			string message = "GET_NODE ERROR: Can't find the element";
			MyException error(message);
			throw error;
		}
		else if (tree->data == element) return tree;
		else if (element > tree->data) get_node(tree->right, element);
		else if (element < tree->data) get_node(tree->left, element);
	}

	node*& get_parent_node(node * &tree, const T& element) {
		if (!tree) {
			string message = "GET_PARENT_NODE ERROR: Can't find the element";
			MyException error(message);
			throw error;
		}
		else if ((tree->left && tree->left->data == element) || (tree->right && tree->right->data == element)) return tree;
		else if (element > tree->data) get_parent_node(tree->right, element);
		else if (element < tree->data) get_parent_node(tree->left, element);
	}

	node*& get_local_max(node * &tree) {
		if (!tree) {
			MyException error("aaaaaaaaa");
			throw error;
		}
		else if (!tree->right) return tree;
		else if (!tree->right->right) return tree;
		else get_local_max(tree->right);
	}

	void set_difference(Tree& minuend, node* subtrahend) {
		if (subtrahend) {

			set_difference(minuend, subtrahend->left);
			if (minuend.find_element(subtrahend->data)) minuend.erase(subtrahend->data);
			set_difference(minuend, subtrahend->right);
		}
	}

	void set_union(Tree& tree, node* addition) {
		if (addition) {

			set_union(tree, addition->left);
			if (!tree.find_element(addition->data)) tree.append(addition->data);
			set_union(tree, addition->right);
		}
	}

	bool are_equal(node* first, node* second) {
		if (first && second) {
			if (first->data == second->data) {
				if (first->left && second->left && first->right && second->right) return true * are_equal(first->left, second->left)* are_equal(first->right, second->right);
				if (first->left && second->left) return true * are_equal(first->left, second->left);
				if (first->right && second->right) return true * are_equal(first->right, second->right);
			}
			else return false;
		}
		else if ((!first && second) || (first && !second)) return false;
		else if (!first && !second) return true;
	}

public:

	void set_union(const Tree& other) {
		set_union(*this, other.root);
	}

	void difference(const Tree& other) {
		set_difference(*this, other.root);
	}

	Tree() {
		root = nullptr;
	}

	Tree(const Tree & other) {
		copy(root, other.root);
	}

	~Tree() {
		delete_tree(this->root);
	}

	void append(const T& element) {
		add_element(this->root, element);
	}

	bool find_element(const T& element) {
		return find_element(root, element);
	}

	int get_element(T& element) {
		try {
			node* wanted = get_node(root, element);
			return wanted->data;
		}
		catch (MyException error) {
			throw error;
		}
	}

	bool is_empty() {
		return root == nullptr;
	}

	void copy(const Tree & tree) {
		copy(this->root, tree.root);
	}

	Tree& operator = (const Tree & other) {
		copy(root, other.root);
		return *this;
	}

	bool operator == (const Tree& other) {
		bool result = are_equal(root, other.root);
		return result;
	}

	bool operator != (const Tree& other) {
		return !(*this == other);
	}

	void erase(const T& element) {
		try {
			node* wanted = get_node(root, element);

			if (wanted != root) { // ======удачение_не_корня======
				node* parent = get_parent_node(root, element);

				if (!wanted->left && !wanted->right) { // лист

					if (parent->left && parent->left->data == wanted->data) {
						parent->left = nullptr;
						delete wanted;
					}
					else {
						parent->right = nullptr;
						delete wanted;
					}

				}
				else if (wanted->left && !wanted->right) { // один дочерний эелемент(левый)

					if (parent->left && parent->left->data == wanted->data) {
						parent->left = wanted->left;
						delete wanted;

					}
					else {
						parent->right = wanted->left;
						delete wanted;

					}

				}
				else if (!wanted->left && wanted->right) { // один дочерний эелемент(правый)

					if (parent->left && parent->left->data == wanted->data) {
						parent->left = wanted->right;
						delete wanted;

					}
					else {
						parent->right = wanted->right;
						delete wanted;

					}
				}
				else { // два дочених элемента

					node* pre_local_max = get_local_max(wanted->left);

					if (pre_local_max->right) {
						node* local_max = pre_local_max->right;
						wanted->data = local_max->data;
						pre_local_max->right = nullptr;
						delete local_max;
					}
					else {
						wanted->data = pre_local_max->data;
						wanted->left = pre_local_max->left;
						delete pre_local_max;
					}
				}
			}
			else { // ======удаление_корня======
				if (!wanted->left && !wanted->right) { // лист
					node* temp = wanted;
					root = nullptr;
					delete temp;
				}
				else if (wanted->left && !wanted->right) { // один дочерний эелемент
					node* temp = wanted;
					root = wanted->left;
					delete temp;
					temp = nullptr;

				}
				else if (!wanted->left && wanted->right) { // один дочерний эелемент
					node* temp = wanted;
					root = wanted->right;
					delete temp;
					temp = nullptr;
				}
				else { // два дочених элемента
					node* pre_local_max = get_local_max(wanted->left);

					if (pre_local_max->right) {
						node* local_max = pre_local_max->right;
						wanted->data = local_max->data;
						pre_local_max->right = nullptr;
						delete local_max;
					}
					else {
						root->data = pre_local_max->data;
						root->left = pre_local_max->left;
						delete pre_local_max;
					}



				}
			}
		}
		catch (MyException error) {
			throw error;
		}
	}



	friend ostream& operator << (ostream & os, const Tree & tree) {
		tree.printLKR(tree.root, os);
		return os;
	}
};




