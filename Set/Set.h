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

	Node* min() const;
	Node*& find(Node*& node, int& val);
	Node*& find(Node*& node, int& val, Node*& outParent);
	void remove_leaf(Node* node);
	void remove_1_child_node(Node* node);
	void remove_2_child_node(Node* node);
	static Node* inorder_next(Node* node);
	static Node* inorder_prev(Node* node);

public:

#pragma region Iterator

	class iterator
	{
	private:
		Node* _current;

	public:
		using value_type = int;
		using difference_type = std::ptrdiff_t;
		using pointer = int*;
		using reference = const int&;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator(Node* ptr = nullptr);

		iterator& operator=(const iterator& source);
		reference operator*() const;
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;

		friend class Set;
	};

#pragma endregion

	Set();
	Set(const Set& source);
	Set(std::initializer_list<int> initList);
	~Set();

	size_t size();
	bool empty();

	void insert(int val);
	bool contains(int val);
	void erase(int val);

	iterator find(int val);
	iterator begin();
	iterator end();

	Set& operator=(const Set& source);
	friend bool operator==(const Set& lhs, const Set& rhs);

};