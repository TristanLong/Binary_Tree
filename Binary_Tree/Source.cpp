#include "iostream"
using namespace std;

struct node {
	int data;
	node* left, * right;
};
typedef node* nodeptr;
typedef node* BST;

void init(BST& root) {
	root = NULL;
}

bool isEmpty(BST root) {
	return root == NULL;
}

nodeptr makeNode(int x) {
	nodeptr p = new node;
	if (p == NULL) return NULL;
	p->data = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void insert(BST& root, int x) {
	if (root == NULL)
		root = makeNode(x);
	else if (x == root->data)
		cout << "\nAlready here";
	else if (x < root->data)
		insert(root->left, x);
	else
		insert(root->right, x);
}

void input(BST& root) {
	int x;
	cout << "\nEnter tree (-99:exit): " << endl;
	while (true)
	{
		cin >> x;
		if (x == -99) break;
		insert(root, x);
	}
}
 
int totalNode(BST root) {
	if (root == NULL) return 0;
	return 1 + totalNode(root->left) + totalNode(root->right);
}

int totalLeafNode(BST root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	return totalLeafNode(root->left) + totalLeafNode(root->right);
}

int height(BST root) {
	if (root == NULL) return 0;
	int left = height(root->left);
	int right = height(root->right);
	return max(left, right) + 1;
}

// Node Left Right 
void NLR(BST root) {
	if (root) {
		cout << "\t" << root->data;
		NLR(root->left);
		NLR(root->right);
	}
}

// Left Node Right 
void LNR(BST root) {
	if (root) {
		LNR(root->left);
		cout << "\t" << root->data;
		LNR(root->right);
	}
}

// Left Right Node 
void LRN(BST root) {
	if (root) {
		LRN(root->left);
		LRN(root->right);
		cout << "\t" << root->data;
	}
}

BST search(BST root, int x) {
	if (root == NULL || root->data == x) return root;
	else if (x < root->data)
		return search(root->left, x);
	else
		return search(root->right, x);
}

BST findMin(BST root) {
	if (root == NULL) return NULL;
	nodeptr p = root;
	while (p->left)
		p = p->left;
	return p;
}

BST deleteNode(BST root, int key) {
	if (root == nullptr) return root;

	// Tìm node cần xóa
	if (key < root->data) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data) {
		root->right = deleteNode(root->right, key);
	}
	else {
		// Node có một hoặc không có con
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			return nullptr;
		}
		else if (root->left == nullptr) {
			BST temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == nullptr) {
			BST temp = root->left;
			delete root;
			return temp;
		}

		// Node có hai con
		BST leftMostNode = findMin(root->right);
		root->data = leftMostNode->data;
		root->right = deleteNode(root->right, leftMostNode->data);
	}
	return root;
}

void deleteNodeCStyle(nodeptr& root, int key) {
	if (root == NULL) return;
	if (root->data == key) {
		nodeptr temp;
		// Trường hợp có 1 cây con PHẢI hoặc không có cây con nào 
		if (root->left == NULL) {
			temp = root;
			root = root->right;
			delete temp;
		}
		// Trường hợp có 1 cây con TRÁI hoặc không có cây con nào 
		else if (root->right == NULL) {
			temp = root;
			root = root->left;
			delete temp;
		}
		// Trường hợp có 2 cây con 
		else {
			nodeptr minRightNode = root->left;
			while (minRightNode->right != NULL) {
				minRightNode = minRightNode->right;
			}
			root->data = minRightNode->data;
			deleteNodeCStyle(root->left, minRightNode->data);
		}
	}
	else if (key < root->data)
		deleteNodeCStyle(root->left, key);
	else
		deleteNodeCStyle(root->right, key);
}

int main() {
	BST Tree;
	init(Tree);
	input(Tree);
	insert(Tree, 999);
	deleteNode(Tree, 999);

	cout << "\n\n\n\n\n";
	cout << "\nSum of nodes: " << totalNode(Tree);
	cout << "\nNumber of leaf nodes: " << totalLeafNode(Tree);
	cout << "\nHeight of the tree: " << height(Tree);
	cout << "\nTree: ";
	cout << "\nNLR: ";
	NLR(Tree);
	cout << "\nLNR: ";
	LNR(Tree);
	cout << "\nLRN: ";
	LRN(Tree);
	int x;
	cout << "\nEnter x want to search: ";
	cin >> x;
	if (search(Tree, x) == NULL)
		cout << "\nNot found!";
	else
		cout << "\nPosition: " << search(Tree, x);
}