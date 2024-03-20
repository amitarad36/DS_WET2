#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define SPACE 10

#include "iostream"
#include "wet2util.h"
#include "BinaryTreeNode.h"

using namespace std;

template <typename T>
class BinaryTree {

private:

	int m_tree_size;
	BinaryTreeNode<T>* m_root;
	bool first_insertion = true;

public:

	BinaryTree() : m_root(nullptr), m_tree_size(0) {}

	bool isEmpty() {
		return (m_root == nullptr);
	}

	BinaryTreeNode<T>* getRoot() {
		return m_root;
	}

	void setRoot(BinaryTreeNode<T>* new_root) {
		m_root = new_root;
	}

	BinaryTreeNode<T>* minNode(BinaryTreeNode<T>* node)
	{
		BinaryTreeNode<T>* current = node;
		while (current->getLeft() != nullptr)
			current = current->getLeft();
		return current;
	}

	int height(BinaryTreeNode<T>* node) {
		if (node == nullptr)
			return -1;
		return node->getHeight();
	}

	int getTreeSize() const {
		return m_tree_size;
	}

	void setTreeSize(int size) {
		m_tree_size = size;
	}

	int getBalanceFactor(BinaryTreeNode<T>* node) //added <T>
	{
		if (node == nullptr)
			return 0;
		return(height(node->getLeft()) - height(node->getRight()));
	}

	BinaryTreeNode<T>* rightRotation(BinaryTreeNode<T>* imbalanced_node)
	{
		BinaryTreeNode<T>* x = imbalanced_node->getLeft();
		BinaryTreeNode<T>* T2 = x->getRight();

		// Perform rotation
		x->setRight(imbalanced_node);
		imbalanced_node->setLeft(T2);

		// Update heights
		imbalanced_node->setHeight(max(height(imbalanced_node->getLeft()), height(imbalanced_node->getRight())) + 1);
		x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);

		updateSubtreeSize(imbalanced_node);
		updateSubtreeSize(x);

		return x;
	}

	BinaryTreeNode<T>* leftRotation(BinaryTreeNode<T>* imbalanced_node)
	{
		BinaryTreeNode<T>* x = imbalanced_node->getRight();
		BinaryTreeNode<T>* T2 = x->getLeft();

		// Perform rotation
		x->setLeft(imbalanced_node);
		imbalanced_node->setRight(T2);

		// Update heights
		imbalanced_node->setHeight(max(height(imbalanced_node->getLeft()), height(imbalanced_node->getRight())) + 1);
		x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);

		updateSubtreeSize(imbalanced_node);
		updateSubtreeSize(x);

		return x;
	}

	StatusType insert(T* new_data) {
		BinaryTreeNode<T>* new_node = new BinaryTreeNode<T>(new_data);
		if (new_node == nullptr) {
			return StatusType::ALLOCATION_ERROR;
		}
		setRoot(insert_aux(m_root, new_node));
		m_tree_size++;
		return StatusType::SUCCESS;
	}

	BinaryTreeNode<T>* insert_aux(BinaryTreeNode<T>* root, BinaryTreeNode<T>* new_node) {
		if (root == nullptr) {
			root = new_node;
			root->setSubtreeSize(1); // Update subtree size for the new node
			if (first_insertion) {
				setRoot(root);
				first_insertion = false;
			}
			return root;
		}

		if (*(new_node->getData()) < *(root->getData()))
		{
			root->setLeft(insert_aux(root->getLeft(), new_node));
		}
		else if (*(new_node->getData()) > *(root->getData()))
		{
			root->setRight(insert_aux(root->getRight(), new_node));
		}

		root->setHeight(1 + max(height(root->getLeft()), height(root->getRight())));

		updateSubtreeSize(root);

		int bf = getBalanceFactor(root);

		//LL imbalance
		if (bf > 1 && *(new_node->getData()) < *(root->getLeft()->getData())) {
			return rightRotation(root);
		}

		//RR imbalance
		if (bf < -1 && *(new_node->getData()) > *(root->getRight()->getData()))
		{
			return leftRotation(root);
		}

		//LR imbalance
		if (bf > 1 && *(new_node->getData()) > *(root->getLeft()->getData()))
		{
			root->setLeft(leftRotation(root->getLeft()));
			return rightRotation(root);
		}

		//RL imbalance
		if (bf < -1 && *(new_node->getData()) < *(root->getRight()->getData()))
		{
			root->setRight(rightRotation(root->getRight()));
			return leftRotation(root);
		}

		return root;
	}
	
	StatusType remove(T* data) {
		if (search(data) == nullptr)
			return StatusType::FAILURE;
		setRoot(remove_aux(m_root, data));
		m_tree_size--;
		return StatusType::SUCCESS;
	}

	BinaryTreeNode<T>* remove_aux(BinaryTreeNode<T>* root, T* data) {
		if (root == nullptr)
			return nullptr;

		if (*data < *root->getData()) //search left
			root->setLeft(remove_aux(root->getLeft(), data));
		else if (*data > *root->getData()) //search right
			root->setRight(remove_aux(root->getRight(), data));
		else // found the node with the id
		{
			if (root->getLeft() == nullptr) // no children or only right child
			{
				BinaryTreeNode<T>* temp = root->getRight();
				try {
					delete root;
				}
				catch (const std::bad_alloc& e) {
					throw;
				}
				return temp;
			}
			else if (root->getRight() == nullptr)
			{
				BinaryTreeNode<T>* temp = root->getLeft();
				try {
					delete root;
				}
				catch (const std::bad_alloc& e) {
					throw;
				}
				return temp;
			}
			// Node with two children
			BinaryTreeNode<T>* temp = minNode(root->getRight());
			root->setData(temp->getData());
			root->setRight(remove_aux(root->getRight(), temp->getData()));
		}

		root->setHeight(1 + max(height(root->getLeft()), height(root->getRight())));

		updateSubtreeSize(root);


		int bf = getBalanceFactor(root);
		if (bf > 1 && getBalanceFactor(root->getLeft()) >= 0)
			return rightRotation(root);
		if (bf < -1 && getBalanceFactor(root->getRight()) <= 0)
			return leftRotation(root);
		if (bf > 1 && getBalanceFactor(root->getLeft()) < 0)
		{
			root->setLeft(leftRotation(root->getLeft()));
			return rightRotation(root);
		}
		if (bf < -1 && getBalanceFactor(root->getRight()) > 0)
		{
			root->setRight(rightRotation(root->getRight()));
			return leftRotation(root);
		}

		return root;
	}

	BinaryTreeNode<T>* search(T* data) {
		if (this == nullptr)
			return nullptr;
		return search_aux(m_root, data);
	}

	BinaryTreeNode<T>* search_aux(BinaryTreeNode<T>* root, T* data) {
		if (root == nullptr || *(root->getData()) == *data)
			return root;

		if (*data < *(root->getData()))
			return search_aux(root->getLeft(), data);
		else
			return search_aux(root->getRight(), data);
	}

	BinaryTreeNode<T>* getElementByRank(int rank) {
		return getElementByRank_aux(m_root, rank);
	}

	BinaryTreeNode<T>* getElementByRank_aux(BinaryTreeNode<T>* root, int rank) {
		if (root == nullptr || rank <= 0 || rank > root->getSubtreeSize()) {
			return nullptr;
		}

		int leftSubtreeSize = (root->getLeft() != nullptr) ? root->getLeft()->getSubtreeSize() : 0;

		if (rank == leftSubtreeSize + 1) {
			return root;
		}
		else if (rank <= leftSubtreeSize) {
			return getElementByRank_aux(root->getLeft(), rank);
		}
		else {
			return getElementByRank_aux(root->getRight(), rank - leftSubtreeSize - 1);
		}
	}

	BinaryTreeNode<T>* getMaxNode() {
		if (m_root == nullptr)
			return nullptr;
		return getMaxNode_aux(m_root);
	}

	BinaryTreeNode<T>* getMaxNode_aux(BinaryTreeNode<T>* root) {
		if (root->getRight() == nullptr)
			return root;
		return getMaxNode_aux(root->getRight());
	}

	BinaryTreeNode<T>* getMinNode() {
		if (m_root == nullptr)
			return nullptr;
		return getMinNode_aux(m_root);
	}

	BinaryTreeNode<T>* getMinNode_aux(BinaryTreeNode<T>* root) {
		if (root->getLeft() == nullptr)
			return root;
		return getMinNode_aux(root->getLeft());
	}

	void updateSubtreeSize(BinaryTreeNode<T>* node) {
		if (node == nullptr) return;
		node->setSubtreeSize(1 + (node->getLeft() != nullptr ? node->getLeft()->getSubtreeSize() : 0) +
			(node->getRight() != nullptr ? node->getRight()->getSubtreeSize() : 0));
	}

	void postorderDelete(bool delete_data = false) {
		postorderDelete_aux(m_root, delete_data);
		setRoot(nullptr);
	}
	
	void postorderDelete_aux(BinaryTreeNode<T>* root, bool delete_data) {
		if (root == nullptr) {
			return;
		}
		postorderDelete_aux(root->getLeft(), delete_data);
		postorderDelete_aux(root->getRight(), delete_data);
		root->setDeletionApproval(delete_data);
		delete root;
	}
		
	void printTree() {
		printTree_aux(this->getRoot(), 3);
	}

	void printTree_aux(BinaryTreeNode<T>* n, int space)
	{
		if (n == nullptr)
		{
			return;
		}
		space += SPACE;
		printTree_aux(n->getRight(), space);
		cout << endl;
		for (int i = SPACE; i < space; i++)
		{
			cout << " ";
		}
		cout << *(n->getData()) << "\n";
		printTree_aux(n->getLeft(), space);
	}

	template <typename T>
	void inorderToArray(T* arr[]) {
		int i = 0;
		inorderToArray_aux(getRoot(), arr, i);
	}

	template <typename T>
	void inorderToArray_aux(BinaryTreeNode<T>* root, T* arr[], int& i) {
		if (root == nullptr)
			return;
		inorderToArray_aux(root->getLeft(), arr, i);
		arr[i++] = dynamic_cast<T*>(root->getData());
		inorderToArray_aux(root->getRight(), arr, i);
	}
};

#endif