#include "olympics24a2.h"

olympics_t::olympics_t() : m_teams(new HashObj<Team>()) {
	
}

olympics_t::~olympics_t()
{
	// TODO: Your code goes here
}

StatusType olympics_t::add_team(int teamId) {
	if (teamId <= 0)
		return StatusType::INVALID_INPUT;

	int team_index = m_teams->getIndexOfKey(teamId);
	Team* new_team = new Team(teamId);
	if (m_teams->getData()[team_index]->search(new_team) != nullptr) {
		delete new_team;
		return StatusType::FAILURE;
	}

	StatusType return_val = m_teams->getData()[team_index]->insert(new_team); // inserting and verifying success
	if (return_val == StatusType::SUCCESS) {
		m_teams->setNumOfElements(m_teams->getNumOfElements() + 1);
	}
	else {
		if (m_teams->getData()[team_index]->getTreeSize() == 0) {
			delete new_team;
		}
	}

	// check if needed: resize hashObj and ditribute teams
	if (m_teams->resize(true) == StatusType::ALLOCATION_ERROR)
		return StatusType::ALLOCATION_ERROR;
	return return_val;
}

StatusType olympics_t::remove_team(int teamId) {
	if (teamId <= 0)
		return StatusType::INVALID_INPUT;

	// find cell
	int team_index = m_teams->getIndexOfKey(teamId);

	// find team
	Team* team_to_remove_dup = new Team(teamId);
	BinaryTreeNode<Team>* team_to_remove_node = m_teams->getData()[team_index]->search(team_to_remove_dup);
	if (team_to_remove_node == nullptr) {
		delete team_to_remove_dup;
		return StatusType::FAILURE;
	}

	// delete team
	delete team_to_remove_dup;
	team_to_remove_node->setDeletionApproval(true);
	StatusType return_val = m_teams->getData()[team_index]->remove(team_to_remove_node->getData());
	if (return_val == StatusType::SUCCESS) {
		m_teams->setNumOfElements(m_teams->getNumOfElements() - 1);
	}

	// check if needed: resize hashObj and ditribute teams
	if (m_teams->resize(false) == StatusType::ALLOCATION_ERROR)
		return StatusType::ALLOCATION_ERROR;
	return return_val;
}

StatusType olympics_t::add_player(int teamId, int playerStrength)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_newest_player(int teamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> olympics_t::num_wins_for_team(int teamId)
{
	// TODO: Your code goes here
	static int i = 0;
	return (i++ == 0) ? 11 : 2;
}

output_t<int> olympics_t::get_highest_ranked_team()
{
	// TODO: Your code goes here
	return 42;
}

StatusType olympics_t::unite_teams(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{
	// TODO: Your code goes here
	static int i = 0;
	return (i++ == 0) ? 11 : 2;
}
