#include <cassert>
#include "Set.h"

Set::Set() : _size(0), _root(nullptr) { }

Set::Set(std::initializer_list<int> initList) : _size(0), _root(nullptr)
{
	for (auto& i : initList)
		insert(i);
}

Set::Node::Node(int val = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) : _val(val), _parent(parent), _left(left), _right(right) {}


size_t Set::size()
{
	return _size;
}

bool Set::empty()
{
	return _size == 0;
}

Set::Node*& Set::find(Node*& node, int& val)
{
	if (node == nullptr || node->_val == val)
		return node;

	if (val < node->_val)
		return find(node->_left, val);

	return find(node->_right, val);
}

Set::Node*& Set::find(Node*& node, int& val, Node*& outParent)
{
	if (node == nullptr || node->_val == val)
		return node;

	outParent = node;
	if (val < node->_val)
		return find(node->_left, val, outParent);

	return find(node->_right, val, outParent);
}

void Set::insert(int val)
{
	Node* parent = nullptr;
	Node*& res = find(_root, val, parent);
	if (res == nullptr)
	{
		res = new Node(val, parent);
		++_size;
	}
}

bool Set::contains(int val)
{
	return find(_root, val) != nullptr;
}

void Set::remove_leaf(Node* node)
{
	assert(node->_left == nullptr && node->_right == nullptr);

	if (node->_parent != nullptr)
	{
		if (node == node->_parent->_left)
			node->_parent->_left = nullptr;
		else
			node->_parent->_right = nullptr;
	}

	delete node;
}

void Set::remove_1_child_node(Node* node)
{
	assert((node->_left != nullptr) ^ (node->_right != nullptr));

	const bool has_right = (node->_right != nullptr);
	Node* c = (has_right ? node->_right : node->_left);

	if (node->_parent != nullptr)
	{
		if (node == node->_parent->_left)
			node->_parent->_left = c;
		else
			node->_parent->_right = c;
	}

	c->_parent = node->_parent;
	delete node;
}

void Set::remove_2_child_node(Node* node)
{
	assert((node->_left != nullptr) & (node->_right != nullptr));

	Node* curr;
	if (node->_parent != nullptr)
	{
		if (node == node->_parent->_left)
		{
			curr = node->_right;
			while (curr->_left != nullptr)
				curr = curr->_left;

			node->_val = curr->_val;
		}
		else
		{
			curr = node->_left;
			while (curr->_right != nullptr)
				curr = curr->_right;

			node->_val = curr->_val;
		}
	}
	else
	{
		curr = node->_right;
		while (curr->_left != nullptr)
			curr = curr->_left;

		node->_val = curr->_val;
	}

	if (curr->_right == nullptr)
		remove_leaf(curr);
	else
		remove_1_child_node(curr);
}

void Set::erase(int val)
{
	Node* node = find(_root, val);

	if (node == nullptr)
		return;

	if (node->_left == nullptr && node->_right == nullptr)
		remove_leaf(node);
	else if (node->_left == nullptr || node->_right == nullptr)
		remove_1_child_node(node);
	else
		remove_2_child_node(node);

	--_size;
}


