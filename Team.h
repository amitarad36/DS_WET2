#ifndef TEAM_H
#define TEAM_H

#include "Stack.h"
#include "Contestant.h"
#include "BinaryTree.h"

class Team {
private:

	int m_id;
	int m_team_strength;
	int m_num_of_wins;
	BinaryTree<Contestant> * m_contestants_tree;
	Stack<Contestant*> * m_contestants_strength_stack;

public:

	Team(int teamId);

	virtual ~Team();

	int getTeamID() const;

	int getRank() const;

	void setNumOfWins(int wins);

	int getNumOfWins() const;

	void setTeamStrength(int strength);

	int getTeamStrength() const;

	int getMeanStrength() const {
		BinaryTreeNode<Contestant>* mean_contestant_node = m_contestants_tree->getElementByRank((m_contestants_tree->getTreeSize()/2) + 1);
		return mean_contestant_node != nullptr? mean_contestant_node->getData()->getStrength() : 0;
	}

	BinaryTree<Contestant>* getContestants() const;

	Stack<Contestant*>* getContestantsStack() const;

	int lessThanByStrengthAndId(Team* other);

	bool operator<(const Team& t) const;

	bool operator>(const Team& t) const;

	bool operator==(const Team& t) const;

	friend std::ostream& operator<<(std::ostream& os, const Team& obj);

};

#endif // TEAM_H