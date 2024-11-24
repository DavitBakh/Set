#pragma once

#include <initializer_list>

class Set
{
#pragma region Node

	struct Node
	{
		int _val;
		Node* _left;
		Node* _right;
		Node* _parent;

		Node(int val, Node* parent, Node* left, Node* right);
		~Node();

	};

#pragma endregion

	size_t _size;
	Node* _root;

	Node*& find(Node*& node, int& val);
	Node*& find(Node*& node, int& val, Node*& outParent);
	void remove_leaf(Node* node);
	void remove_1_child_node(Node* node);
	void remove_2_child_node(Node* node);
	static Node* inorder_next(Node* node);
	static Node* inorder_prev(Node* node);

public:

	Set();
	Set(const Set& source);
	Set(std::initializer_list<int> initList);
	~Set();

	size_t size();
	bool empty();


	void insert(int val);
	bool contains(int val);
	void erase(int val);

	Set& operator=(const Set& source);
	friend bool operator==(const Set& lhs, const Set& rhs);

};