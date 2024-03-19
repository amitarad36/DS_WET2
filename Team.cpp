#include "Team.h"

Team::Team(int team_id) : m_id(team_id), m_num_of_wins(0), m_contestants_tree(new BinaryTree<Contestant>()), m_contestants_stregth_stack(new Stack<int>()) {}

Team::~Team() {
	m_contestants_tree->postorderDelete(true);
	delete m_contestants_stregth_stack;
}

int Team::getTeamID() const {
	return m_id;
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