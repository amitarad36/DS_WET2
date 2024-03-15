#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H


template <typename T>
class BinaryTreeNode {

private:

	bool m_deletion_approval;
	int m_height;
	int m_subtree_size;
	T* m_data;
	BinaryTreeNode<T>* m_left;
	BinaryTreeNode<T>* m_right;

public:

	BinaryTreeNode(T* data) : m_data(data), m_height(0), m_left(nullptr), m_right(nullptr), m_deletion_approval(false) {}

	~BinaryTreeNode() {
		if (m_deletion_approval) {
			delete m_data;
		}
	}

	int getHeight() const {
		return m_height;
	}

	void setHeight(const int height) {
		m_height = height;
	}

	bool getDeletionApproval() const {
		return m_deletion_approval;
	}

	void setDeletionApproval(bool deletion_approval) {
		m_deletion_approval = deletion_approval;
	}

	T* getData() const {
		return m_data;
	}

	void setData(T* data) {
		m_data = data;
	}

	BinaryTreeNode<T>* getLeft() const {
		return m_left;
	}

	void setLeft(BinaryTreeNode<T>* left) {
		m_left = left;
	}

	BinaryTreeNode<T>* getRight() const {
		return m_right;
	}

	void setRight(BinaryTreeNode<T>* right) {
		m_right = right;
	}

};
#endif