#include <cassert>
#include <queue>
#include <vector>
#include "Set.h"

Set::Set() : _size(0), _root(nullptr) {}

Set::Set(std::initializer_list<int> initList) : Set::Set()
{
	for (auto& i : initList)
		insert(i);
}

Set::Set(const Set& source) : Set::Set()
{
	std::queue<Node*> queue;
	queue.push(source._root);

	Node* curr;
	while (!queue.empty())
	{
		curr = queue.front();
		queue.pop();

		if (curr == nullptr)
			continue;

		queue.push(curr->_left);
		queue.push(curr->_right);

		insert(curr->_val);
	}
}

Set::Node::Node(int val = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) : _val(val), _parent(parent), _left(left), _right(right), _height(1) {}

Set::Node::~Node()
{
	delete _right;
	delete _left;
}

Set::~Set()
{
	delete _root;
}


size_t Set::size()
{
	return _size;
}

bool Set::empty()
{
	return _size == 0;
}

void Set::insert(int val)
{
	Node* parent = nullptr;
	insert(_root, val, parent);
}

bool Set::contains(int val)
{
	return find(_root, val) != nullptr;
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

void Set::erase(iterator it)
{
	Node* node = it._current;

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

Set& Set::operator=(const Set& source)
{
	if (&source != this)
	{
		this->~Set();

		std::queue<Node*> queue;
		queue.push(source._root);

		Node* curr;
		while (!queue.empty())
		{
			curr = queue.front();
			queue.pop();

			if (curr == nullptr)
				continue;

			queue.push(curr->_left);
			queue.push(curr->_right);

			insert(curr->_val);
		}
	}

	return *this;
}

bool operator==(const Set& lhs, const Set& rhs)
{
	if (lhs._size != rhs._size)
		return false;

	Set::Node* curr1 = lhs.min();
	Set::Node* curr2 = rhs.min();

	while (curr1 != nullptr)
	{
		if (curr1->_val != curr2->_val)
			return false;

		curr1 = Set::inorder_next(curr1);
		curr2 = Set::inorder_next(curr2);
	}

	return true;
}

bool operator!=(const Set& lhs, const Set& rhs)
{
	return !(lhs == rhs);
}

Set::iterator Set::find(int val)
{
	return iterator(find(_root, val));
}

Set::iterator Set::upper_bound(int val)
{
	Node* curr = _root;
	Node* upper = nullptr;

	while (curr != nullptr)
	{
		if (curr->_val <= val)
			curr = curr->_right;
		else
		{
			upper = curr;
			curr = curr->_left;
		}
	}

	return iterator(upper);
}

Set::iterator Set::lower_bound(int val)
{
	Node* curr = _root;
	Node* lower = nullptr;

	while (curr != nullptr)
	{
		if (curr->_val < val)
			curr = curr->_right;
		else
		{
			lower = curr;
			curr = curr->_left;
		}
	}

	return iterator(lower);
}

#pragma region Private Functions

Set::Node* Set::min() const
{
	if (_root == nullptr)
		return nullptr;

	Set::Node* curr = _root;

	while (curr->_left != nullptr)
		curr = curr->_left;

	return curr;
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
	else
		_root = nullptr;

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
	else
		_root = c;

	if (has_right)
		node->_right = nullptr;
	else
		node->_left = nullptr;

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

Set::Node* Set::inorder_next(Node* node)
{
	if (node->_right != nullptr) {
		node = node->_right;
		while (node->_left != nullptr)
			node = node->_left;
		return node;
	}
	else {
		while (node->_parent != nullptr && node == node->_parent->_right)
			node = node->_parent;
		return node->_parent;
	}
}

Set::Node* Set::inorder_prev(Node* node)
{
	if (node->_left != nullptr) {

		node = node->_left;
		while (node->_right != nullptr)
			node = node->_right;
		return node;
	}
	else {

		while (node->_parent != nullptr && node == node->_parent->_left)
			node = node->_parent;
		return node->_parent;
	}
	return nullptr;
}

void Set::insert(Node*& node, int& val, Node*& parent)
{
	if (node == nullptr)
	{
		node = new Node(val, parent);
		++_size;
		return;
	}

	if (node->_val == val)
		return;
	else if (val < node->_val)
		insert(node->_left, val, node);
	else
		insert(node->_right, val, node);


	int leftH = node->_left ? node->_left->_height : 0;
	int rightH = node->_right ? node->_right->_height : 0;

	if (std::abs(leftH - rightH) > 1)
	{
		bool isLeftChild = leftH > rightH;
		Node* child = isLeftChild ? node->_left : node->_right;

		int ChleftH = child->_left ? child->_left->_height : 0;
		int ChrightH = child->_right ? child->_right->_height : 0;

		bool isLeftGrChild = ChleftH > ChrightH;
		Node* grChild = isLeftGrChild ? child->_left : child->_right;

		if (isLeftChild && isLeftGrChild)
		{
			rightRotation(child);
			if (node == _root)
				_root = child;
		}

		if (isLeftChild && !isLeftGrChild)
		{
			leftRotation(grChild);
			rightRotation(grChild);

			if (node == _root)
				_root = grChild;
		}


		if (!isLeftChild && isLeftGrChild)
		{
			rightRotation(grChild);
			leftRotation(grChild);

			if (node == _root)
				_root = grChild;
		}


		if (!isLeftChild && !isLeftGrChild)
		{
			leftRotation(child);
			if (node == _root)
				_root = child;
		}

	}

	node->_height = std::max(node->_left ? node->_left->_height : 0, node->_right ? node->_right->_height : 0) + 1;
}

void Set::leftRotation(Node* node)
{
	Node* p = node->_parent;
	if (p == nullptr)
		return;

	if (node != p->_right)
		return;

	Node* left = node->_left;
	Node* pp = p->_parent;

	node->_left = p;
	p->_parent = node;

	p->_right = left;

	if (left)
		left->_parent = p;

	node->_parent = pp;
	if (pp) {
		if (pp->_left == p)
			pp->_left = node;
		else
			pp->_right = node;
	}
}

void Set::rightRotation(Node* node)
{
	Node* p = node->_parent;
	if (p == nullptr)
		return;

	if (node != p->_left)
		return;

	Node* right = node->_right;
	Node* pp = p->_parent;

	node->_right = p;
	p->_parent = node;

	p->_left = right;

	if (right)
		right->_parent = p;

	node->_parent = pp;
	if (pp) {
		if (pp->_right == p)
			pp->_right = node;
		else
			pp->_left = node;
	}
}
#pragma endregion


#pragma region Iterator


Set::iterator::iterator(Node* ptr) : _current(ptr) {}

Set::iterator Set::begin()
{
	return iterator(min());
}

Set::iterator Set::end()
{
	return iterator(nullptr);
}

Set::iterator::reference Set::iterator::operator*() const
{
	return _current->_val;
}

Set::iterator& Set::iterator::operator++()
{
	_current = inorder_next(_current);
	return *this;
}

Set::iterator Set::iterator::operator++(int)
{
	iterator result(*this);
	++(*this);
	return result;
}

Set::iterator& Set::iterator::operator--()
{
	_current = inorder_prev(_current);
	return *this;
}

Set::iterator Set::iterator::operator--(int)
{
	iterator result(*this);
	--(*this);
	return result;
}


bool Set::iterator::operator==(const Set::iterator& other) const
{
	return this->_current == other._current;
}


bool Set::iterator::operator!=(const Set::iterator& other) const
{
	return this->_current != other._current;
}


Set::iterator& Set::iterator::operator=(const iterator& source)
{
	this->_current = source._current;
	return *this;
}

#pragma endregion