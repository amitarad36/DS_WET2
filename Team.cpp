#include "Team.h"

Team::Team(int team_id) : m_id(team_id), was_in_teams_tree(false), m_saved_wins(0), m_team_strength(0), m_contestants_tree(new BinaryTree<Contestant>()), m_contestants_strength_stack(new Stack()) {}

Team::~Team() {
	m_contestants_tree->postorderDelete(true);
	delete m_contestants_tree;
	delete m_contestants_strength_stack;
}

int Team::getTeamID() const {
	return m_id;
}

void Team::setWasInTeamsTree(bool was) {
	was_in_teams_tree = was;
}

bool Team::getWasInTeamsTree() const {
	return was_in_teams_tree;
}

void Team::setStrength(int strength) {
	m_team_strength = strength;
}

int Team::getStrength() const {
	return m_team_strength;
}

void Team::setSavedWins(int wins) {
	m_saved_wins = wins;
}

int Team::getSavedWins() const {
	return m_saved_wins;
}

void Team::setContestants(BinaryTree<Contestant>* contestants_tree) {
	m_contestants_tree = contestants_tree;
}

BinaryTree<Contestant>* Team::getContestants() const {
	return m_contestants_tree;
}

int Team::getMeanStrength() const {
	BinaryTreeNode<Contestant>* mean_contestant_node = m_contestants_tree->getElementByRank((m_contestants_tree->getTreeSize() / 2) + 1);
	return mean_contestant_node != nullptr ? mean_contestant_node->getData()->getStrength() : 0;
}

Stack* Team::getContestantsStack() const{
	return m_contestants_strength_stack;
}

int Team::lessThanByStrengthAndId(Team* other) {
	if (this->getStrength() == other->getStrength()) {
		return this->getTeamID() - other->getTeamID(); // Compare IDs
	}
	return other->getStrength() - this->getStrength(); // Compare strengths
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
	os << obj.getStrength() << "-" << obj.getTeamID();
	return os;
}