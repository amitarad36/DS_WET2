#ifndef TEAM_H
#define TEAM_H


#include "Contestant.h"
#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include "Stack.h"


class Team {
private:

	int m_id;
	int m_num_of_wins;
	BinaryTree<Contestant> * m_contestants_tree;
	Stack<Contestant*> * m_contestants_stregth_stack;

public:

	Team(int teamId);

	virtual ~Team();

	int getTeamID() const;

	void setNumOfWins(int wins);

	int getNumOfWins() const;

	int getMeanStrength() const {
		BinaryTreeNode<Contestant>* mean_contestant_node = m_contestants_tree->getElementByRank((m_contestants_tree->getTreeSize()/2) + 1);
		return mean_contestant_node->getData()->getStrength();
	}

	BinaryTree<Contestant>* getContestants() const;

	Stack<Contestant*>* getContestantsStack() const;

	bool operator<(const Team& t) const;

	bool operator>(const Team& t) const;

	bool operator==(const Team& t) const;

	friend std::ostream& operator<<(std::ostream& os, const Team& obj);

};
#endif // TEAM_H