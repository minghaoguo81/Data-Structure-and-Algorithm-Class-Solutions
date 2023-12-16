#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MY_INT64_MIN        (-9223372036854775807 - 1)
#define MY_INT64_MAX          9223372036854775807



struct Node 
{
	int key;
	int left;
	int right;

	Node() : key(0), left(-1), right(-1) {}
	Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};



bool BSTUtil(const vector<Node>& tree, const int& node_idx, long long min, long long max)
{
	if (node_idx == -1)
		return true;

	if (tree[node_idx].key < min || tree[node_idx].key >= max)
		return false;

	return
		BSTUtil(tree, tree[node_idx].left, min, (tree[node_idx].key)) &&
		BSTUtil(tree, tree[node_idx].right, (tree[node_idx].key), max);
}

bool BinarySearchTree(const vector<Node>& tree) 
{
	if (tree.size() == 0)
		return  true;

	return BSTUtil(tree, 0, MY_INT64_MIN, MY_INT64_MAX);
}

int main() 
{
	int nodes;
	cin >> nodes;
	vector<Node> tree;

	for (int i = 0; i < nodes; ++i) 
	{
		int key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}

	if (BinarySearchTree(tree)) 
	{
		cout << "CORRECT" << endl;
	}
	else 
	{
		cout << "INCORRECT" << endl;
	}

	return 0;
}