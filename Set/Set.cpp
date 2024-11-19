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