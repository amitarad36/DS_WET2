#include "Team.h"

Team::Team(int team_id) : m_id(team_id), m_num_of_wins(0), m_team_strength(0), m_contestants_tree(new BinaryTree<Contestant>()), m_contestants_strength_stack(new Stack<Contestant*>()) {}

Team::~Team() {
	m_contestants_tree->postorderDelete(true);
	delete m_contestants_strength_stack;
}

int Team::getTeamID() const {
	return m_id;
}

int Team::getRank() const {
	return m_team_strength + m_num_of_wins;
}


void Team::setNumOfWins(int wins) {
	m_num_of_wins = wins;
}

int Team::getNumOfWins() const {
	return m_num_of_wins;
}

void Team::setTeamStrength(int strength) {
	m_team_strength = strength;
}

int Team::getTeamStrength() const {
	return m_team_strength;
}

BinaryTree<Contestant>* Team::getContestants() const {
	return m_contestants_tree;
}

Stack<Contestant*>* Team::getContestantsStack() const{
	return m_contestants_strength_stack;
}

bool Team::operator<(const Team& c) const {
	return (getTeamID() < c.getTeamID());
}

bool Team::operator>(const Team& c) const {
	return (getTeamID() > c.getTeamID());
}

bool Team::operator==(const Team& c) const {
	return (getTeamID() == c.getTeamID());
}


std::ostream& operator<<(std::ostream& os, const Team& obj) {
	os << obj.getTeamID();
	return os;
}