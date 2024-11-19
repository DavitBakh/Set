#pragma once

/*
  Your task here is to define a set of integers. Since this is not a template class
  you must declare your functions in the header file and define them in .cpp file.
*/

class Set
{
#pragma region Node

	struct Node
	{
		int _val;
		Node* _left;
		Node* _right;

		Node(int val, Node* left, Node* right);
		//~Node(); ???


	};

#pragma endregion

	size_t _size = 0;
	Node* _root = nullptr;

	Node*& find(Node*& node, int& val);

public:


	size_t size();
	bool empty();


	void insert(int val);
	bool contains(int val);
};