#include "Set.h"

Set::Node::Node(int val = 0, Node* left = nullptr, Node* right = nullptr) : _val(val), _left(left), _right(right) { }

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

void Set::insert(int val)
{
	Node*& res = find(_root, val);
	if (res == nullptr)
	{
		res = new Node(val);
		++_size;
	}
}

bool Set::contains(int val)
{
	return find(_root, val) != nullptr;
}


