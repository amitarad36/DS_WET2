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
	BinaryTree<Contestant> m_contestants_tree;
	Stack<int> m_contestants_stregth_stack;

public:

	Team(int teamId);

	virtual ~Team();

	int getTeamID() const;

	bool operator<(const Team& t) const;

	bool operator>(const Team& t) const;

	bool operator==(const Team& t) const;

	friend std::ostream& operator<<(std::ostream& os, const Team& obj);

};
#endif // TEAM_H