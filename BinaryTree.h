#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define SPACE 10
#define MIN_RANK 0


#include "iostream"
#include "wet2util.h"
#include "BinaryTreeNode.h"

using namespace std;

template <typename T>
class BinaryTree {

private:

	int m_tree_size;
	BinaryTreeNode<T> * m_root;
	bool first_insertion = true;

public:

	BinaryTree() : m_root(nullptr), m_tree_size(0) {}

	virtual ~BinaryTree() {
		postorderDelete();
	}

	bool isEmpty() {
		return (m_root == nullptr);
	}

	BinaryTreeNode<T>* getRoot() {
		return m_root;
	}

	void setRoot(BinaryTreeNode<T>* new_root) {
		m_root = new_root;
	}

	BinaryTreeNode<T>* minNode(BinaryTreeNode<T>* node) {
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

	BinaryTreeNode<T>* rightRotation(BinaryTreeNode<T>* imbalanced_node) {
		BinaryTreeNode<T>* x = imbalanced_node->getLeft();
		BinaryTreeNode<T>* T2 = x->getRight();

		int A = imbalanced_node->getExtraWins();
		int B = x->getExtraWins();
		int E = 0;
		if (T2 != nullptr)
			E = T2->getExtraWins();

		imbalanced_node->setExtraWins(-B);
		x->setExtraWins(A + B);
		if (T2 != nullptr)
			T2->setExtraWins(B + E);


		// Perform rotation
		x->setRight(imbalanced_node);
		imbalanced_node->setLeft(T2);

		// Update heights
		imbalanced_node->setHeight(max(height(imbalanced_node->getLeft()), height(imbalanced_node->getRight())) + 1);
		x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);

		updateSubtreeSize(imbalanced_node);
		updateSubtreeSize(x);


		updateSubtreeMaxRankedTeam(imbalanced_node);
		updateSubtreeMaxRankedTeam(x);

		return x;
	}

	BinaryTreeNode<T>* leftRotation(BinaryTreeNode<T>* imbalanced_node)
	{
		BinaryTreeNode<T>* x = imbalanced_node->getRight();
		BinaryTreeNode<T>* T2 = x->getLeft();

		int A = imbalanced_node->getExtraWins();
		int B = x->getExtraWins();
		int E = 0;
		if (T2 != nullptr)
			E = T2->getExtraWins();

		imbalanced_node->setExtraWins(-B);
		x->setExtraWins(A + B);
		if (T2 != nullptr)
			T2->setExtraWins(B + E);


		// Perform rotation
		x->setLeft(imbalanced_node);
		imbalanced_node->setRight(T2);

		// Update heights
		imbalanced_node->setHeight(max(height(imbalanced_node->getLeft()), height(imbalanced_node->getRight())) + 1);
		x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);


		updateSubtreeSize(imbalanced_node);
		updateSubtreeSize(x);

		updateSubtreeMaxRankedTeam(imbalanced_node);
		updateSubtreeMaxRankedTeam(x);


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
			root->setSubtreeSize(1);
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
			else {
				// Node with two children
				BinaryTreeNode<T>* temp = minNode(root->getRight());
				root->setData(temp->getData());
				root->setRight(remove_aux(root->getRight(), temp->getData()));
			}
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

	StatusType insertByStrengthAndId(T* new_data) {
		BinaryTreeNode<T>* new_node = new BinaryTreeNode<T>(new_data);
		if (new_node == nullptr) {
			return StatusType::ALLOCATION_ERROR;
		}
		setRoot(insertByStrengthAndId_aux(m_root, new_node));
		m_tree_size++;
		return StatusType::SUCCESS;
	}

	BinaryTreeNode<T>* insertByStrengthAndId_aux(BinaryTreeNode<T>* root, BinaryTreeNode<T>* new_node) {
		if (root == nullptr) {
			root = new_node;
			root->setSubtreeSize(1);
			new_node->setExtraWins(-calculatePathExtraWins(new_node, m_root));
			root->setSubtreeMaxRankedTeam(new_node->getData()->getStrength() - new_node->getExtraWins());
			if (first_insertion) {
				setRoot(root);
				first_insertion = false;
			}
			return root;
		}

		if (new_node->getData()->lessThanByStrengthAndId(root->getData()) > 0) {
			root->setLeft(insertByStrengthAndId_aux(root->getLeft(), new_node));
		}
		else if (new_node->getData()->lessThanByStrengthAndId(root->getData()) < 0) {
			root->setRight(insertByStrengthAndId_aux(root->getRight(), new_node));
		}

		root->setHeight(1 + max(height(root->getLeft()), height(root->getRight())));

		updateSubtreeSize(root);
		updateSubtreeMaxRankedTeam(root->getRight());
		updateSubtreeMaxRankedTeam(root->getLeft());
		updateSubtreeMaxRankedTeam(root);

		int bf = getBalanceFactor(root);


		//LL imbalance
		if (bf > 1 && new_node->getData()->lessThanByStrengthAndId(root->getLeft()->getData()) > 0) {
			return rightRotation(root);
		}

		//RR imbalance
		if (bf < -1 && new_node->getData()->lessThanByStrengthAndId(root->getRight()->getData()) < 0) {
			return leftRotation(root);
		}

		//LR imbalance
		if (bf > 1 && new_node->getData()->lessThanByStrengthAndId(root->getLeft()->getData()) < 0)
		{
			root->setLeft(leftRotation(root->getLeft()));
			return rightRotation(root);
		}

		//RL imbalance
		if (bf < -1 && new_node->getData()->lessThanByStrengthAndId(root->getRight()->getData()) > 0)
		{
			root->setRight(rightRotation(root->getRight()));
			return leftRotation(root);
		}

		return root;
	}

	StatusType removeByStrengthAndId(T* data) {

		if (searchByStrengthAndId(data) == nullptr)
			return StatusType::FAILURE;
		setRoot(removeByStrengthAndId_aux(m_root, data));
		m_tree_size--;
		return StatusType::SUCCESS;
	}

	BinaryTreeNode<T>* removeByStrengthAndId_aux(BinaryTreeNode<T>* root, T* data) {
		if (root == nullptr)
			return nullptr;


		if (data->lessThanByStrengthAndId(root->getData()) > 0) //search left
			root->setLeft(removeByStrengthAndId_aux(root->getLeft(), data));
		else if (data->lessThanByStrengthAndId(root->getData()) < 0) //search right
			root->setRight(removeByStrengthAndId_aux(root->getRight(), data));
		else { // found the node with the id
			int A = root->getExtraWins();
			
			if (root->getLeft() == nullptr) { // no children or only right child 
				BinaryTreeNode<T>* temp = root->getRight();
				if (temp != nullptr)
					temp->setExtraWins(temp->getExtraWins() + A);
				try {
					delete root;
				}
				catch (const std::bad_alloc& e) {
					throw;
				}
				return temp;
			}
			else if (root->getRight() == nullptr) {  // only left child
				BinaryTreeNode<T>* temp = root->getLeft();
				if (temp != nullptr) {
					temp->setExtraWins(temp->getExtraWins() + A);
				}
				try {
					delete root;
				}
				catch (const std::bad_alloc& e) {
					throw;
				}
				return temp;
			}
			else {

				// Node with two children
				BinaryTreeNode<T>* temp = minNode(root->getRight());
				BinaryTreeNode<T>* temp_right = temp->getRight();



				int path_sum = calculatePathExtraWins(temp, root);
				int B = root->getRight()->getExtraWins();
				int C = root->getLeft()->getExtraWins();
				int D = temp->getExtraWins();
				int E = temp_right == nullptr ? 0 : temp_right->getExtraWins();



				root->setExtraWins(path_sum + D);
				if (root->getRight() != nullptr)
					root->getRight()->setExtraWins(A + B - path_sum - D);
				root->getLeft()->setExtraWins(A + C - path_sum - D);
				if (temp_right != nullptr) {
					temp_right->setExtraWins(path_sum + D + E - calculatePathExtraWins(temp_right, root));
				}

				root->setData(temp->getData());
				root->setRight(removeByStrengthAndId_aux(root->getRight(), temp->getData()));

			}
		}

		root->setHeight(1 + max(height(root->getLeft()), height(root->getRight())));
		updateSubtreeSize(root);	
		updateSubtreeMaxRankedTeam(root->getRight());
		updateSubtreeMaxRankedTeam(root->getLeft());
		updateSubtreeMaxRankedTeam(root);

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

	BinaryTreeNode<T>* searchByStrengthAndId(T* data) {
		if (this == nullptr)
			return nullptr;
		return searchByStrengthAndId_aux(m_root, data);
	}

	BinaryTreeNode<T>* searchByStrengthAndId_aux(BinaryTreeNode<T>* root, T* data) {
		if (root == nullptr || root->getData()->lessThanByStrengthAndId(data) == 0)
			return root;

		if (data->lessThanByStrengthAndId(root->getData()) > 0)
			return searchByStrengthAndId_aux(root->getLeft(), data);
		else
			return searchByStrengthAndId_aux(root->getRight(), data);
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

	void updateSubtreeMaxRankedTeam(BinaryTreeNode<T>* node) {
		if (node == nullptr) return;
		node->setSubtreeMaxRankedTeam(node->getExtraWins() + max(node->getData()->getStrength(),
			max((node->getLeft() != nullptr ? node->getLeft()->getSubtreeMaxRankedTeam() : MIN_RANK),
				(node->getRight() != nullptr ? node->getRight()->getSubtreeMaxRankedTeam() : MIN_RANK))));
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

	void printTree_aux(BinaryTreeNode<T>* n, int space) {
		if (n == nullptr) {
			return;
		}
		space += SPACE;
		printTree_aux(n->getRight(), space);
		cout << endl;
		for (int i = SPACE; i < space; i++) {
			cout << " ";
		}
		cout << *(n->getData()) << " - " << n->getExtraWins() << " - " << n->getSubtreeMaxRankedTeam() << endl;
		printTree_aux(n->getLeft(), space);
	}

	void inorderToArray(T* arr[]) {
		int i = 0;
		inorderToArray_aux(getRoot(), arr, i);
	}

	void inorderToArray_aux(BinaryTreeNode<T>* root, T* arr[], int& i) {
		if (root == nullptr)
			return;
		inorderToArray_aux(root->getLeft(), arr, i);
		arr[i++] = dynamic_cast<T*>(root->getData());
		inorderToArray_aux(root->getRight(), arr, i);
	}

	int getRankByTeam(T* target) {
		return getRankByTeam_aux(m_root, target) + 1;
	}

	int getRankByTeam_aux(BinaryTreeNode<T>* root, T* target) {
		if (root == nullptr)
			return 0;

		//search left
		if (target->lessThanByStrengthAndId(root->getData()) > 0)
			return getRankByTeam_aux(root->getLeft(), target);

		//search right
		if (target->lessThanByStrengthAndId(root->getData()) < 0) {
			int add = 1 + (root->getLeft() != nullptr ? root->getLeft()->getSubtreeSize() : 0);
			return getRankByTeam_aux(root->getRight(), target) + add;
		}

		return root->getLeft() != nullptr ? root->getLeft()->getSubtreeSize() : 0;
	}

	void addWinToTeamsInRange(int low_rank, int high_rank) {
		if (high_rank == 0) return;
		addWinToTeams(high_rank, 1);
		if (low_rank == 1) return;
		addWinToTeams(low_rank - 1, -1);
	}

	void addWinToTeams(int rank, int x) {
		BinaryTreeNode<T>* target = getElementByRank(rank);
		bool added = false;
		addWinToTeams_aux(target->getData(), &added, x, m_root);
		updateSubtreeMaxRankedTeam(target->getRight());
		updateSubtreeMaxRankedTeam(target->getLeft());
		updateSubtreeMaxRankedTeamAlongPath(target->getData());
	}

	void addWinToTeams_aux(T* team, bool* added, int x, BinaryTreeNode<T>* root) {
		if (root == nullptr) {
			return;
		}
		if (root->getData() == team) {
			if (!*added) {
				root->setExtraWins(root->getExtraWins() + x);
				if (root->getRight() != nullptr) {
					root->getRight()->setExtraWins(root->getRight()->getExtraWins() - x);
				}
			}
			else if (root->getRight() != nullptr) {
				root->getRight()->setExtraWins(root->getRight()->getExtraWins() - x);
			}
			return;
		}

		if (team->lessThanByStrengthAndId(root->getData()) < 0) {
			if (!*added) {
				root->setExtraWins(root->getExtraWins() + x);
				*added = true;
				addWinToTeams_aux(team, added, x, root->getRight());
			}
			else {
				addWinToTeams_aux(team, added, x, root->getRight());
			}
		}

		if (team->lessThanByStrengthAndId(root->getData()) > 0) {
			if (*added) {
				root->setExtraWins(root->getExtraWins() - x);
				*added = false;
			}
			addWinToTeams_aux(team, added, x, root->getLeft());
		}
	}

	int teamNumOfWins(T* target) {
		if (!target->getWasInTeamsTree()) {
			return 0;
		}
		int wins = 0;
		teamNumOfWins_aux(m_root, target, &wins);
		return wins;
	}

	void teamNumOfWins_aux(BinaryTreeNode<T>* root, T* target, int* sum_num_of_wins) {
		if (root == nullptr) {
			return;
		}

		if (root->getData() == target) {
			*sum_num_of_wins += root->getExtraWins();
			return;
		}

		if (target->lessThanByStrengthAndId(root->getData()) < 0) {
			*sum_num_of_wins += root->getExtraWins();
			teamNumOfWins_aux(root->getRight(), target, sum_num_of_wins);
		}
		else {
			*sum_num_of_wins += root->getExtraWins();
			teamNumOfWins_aux(root->getLeft(), target, sum_num_of_wins);
		}
	}

	int calculatePathExtraWins(BinaryTreeNode<T>* new_node, BinaryTreeNode<T>* root) {
		int sum = 0;

		if (root != nullptr) {
			if(root->getData() != new_node->getData())
				sum += root->getExtraWins();
			if (root->getData()->lessThanByStrengthAndId(new_node->getData()) > 0) {
				return sum + calculatePathExtraWins(new_node, root->getRight());
			}
			else {
				return sum + calculatePathExtraWins(new_node, root->getLeft());
			}
		}
		return sum;
	}

	void updateSubtreeMaxRankedTeamAlongPath(T* target_data) {
		updateSubtreeMaxRankedTeamAlongPath_aux(m_root, target_data);
	}

	void updateSubtreeMaxRankedTeamAlongPath_aux(BinaryTreeNode<T>* node, T* target_data) {
		if (node->getData() == target_data) {
			updateSubtreeMaxRankedTeam(node);
			return;
		}

		if (node->getData()->lessThanByStrengthAndId(target_data) > 0) {
			updateSubtreeMaxRankedTeamAlongPath_aux(node->getRight(), target_data);
		}
		else if (node->getData()->lessThanByStrengthAndId(target_data) < 0) {
			updateSubtreeMaxRankedTeamAlongPath_aux(node->getLeft(), target_data);
		}

		updateSubtreeMaxRankedTeam(node);
	}

};


#endif