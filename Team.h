#ifndef TEAM_H
#define TEAM_H

#include "Stack.h"
#include "Contestant.h"
#include "BinaryTree.h"

class Team {
private:

	int m_id;
	int m_saved_wins;
	int m_team_strength;
	bool was_in_teams_tree;
	BinaryTree<Contestant> * m_contestants_tree;
	Stack * m_contestants_strength_stack;

public:

	Team(int teamId);

	virtual ~Team();

	int getTeamID() const;

	void setWasInTeamsTree(bool was);

	bool getWasInTeamsTree() const;

	void setStrength(int strength);

	int getStrength() const;

	void setSavedWins(int wins);

	int getSavedWins() const;

	void setContestants(BinaryTree<Contestant>* contestants_tree);

	BinaryTree<Contestant>* getContestants() const;
	
	int getMeanStrength() const;

	Stack* getContestantsStack() const;

	int lessThanByStrengthAndId(Team* other);

	bool operator<(const Team& t) const;

	bool operator>(const Team& t) const;

	bool operator==(const Team& t) const;

	friend std::ostream& operator<<(std::ostream& os, const Team& obj);

};

#endif // TEAM_H