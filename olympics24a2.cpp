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
	if (new_team == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
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
	if (team_to_remove_dup == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
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

StatusType olympics_t::add_player(int teamId, int playerStrength) {
	if (playerStrength <= 0 || teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}

	int team_index = m_teams->getIndexOfKey(teamId);
	Team* team_dup = new Team(teamId);
	if (team_dup == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
	BinaryTreeNode<Team>* team_node = m_teams->getData()[team_index]->search(team_dup);
	if (team_node == nullptr) {
		delete team_dup;
		return StatusType::FAILURE;
	}

	Contestant* new_contestant = new Contestant(playerStrength);
	if (new_contestant == nullptr) {
		return StatusType::ALLOCATION_ERROR;
		delete team_dup;
	}

	if (team_node->getData()->getContestants()->insert(new_contestant) == StatusType::ALLOCATION_ERROR) {
		delete team_dup;
		return StatusType::ALLOCATION_ERROR;
	}

	team_node->getData()->getContestantsStack()->push(new_contestant);

	delete team_dup;
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_newest_player(int teamId) {
	if (teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}

	int team_index = m_teams->getIndexOfKey(teamId);
	Team* team_dup = new Team(teamId);
	if (team_dup == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}

	BinaryTreeNode<Team>* team_node = m_teams->getData()[team_index]->search(team_dup);
	if (team_node == nullptr || team_node->getData()->getContestantsStack()->empty()) {
		delete team_dup;
		return StatusType::FAILURE;
	}

	Contestant* contestant_to_remove = team_node->getData()->getContestantsStack()->top();
	team_node->getData()->getContestantsStack()->pop();
	StatusType return_val = team_node->getData()->getContestants()->remove(contestant_to_remove);

	delete team_dup;
	return return_val;
}

output_t<int> olympics_t::play_match(int teamId1, int teamId2) {
	if (teamId1 == teamId2 || teamId2 <= 0 || teamId1 <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	int team1_index = m_teams->getIndexOfKey(teamId1);
	Team* team1_dup = new Team(teamId1);
	if (team1_dup == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
	BinaryTreeNode<Team>* team1_node = m_teams->getData()[team1_index]->search(team1_dup);
	if (team1_node == nullptr || team1_node->getData()->getContestantsStack()->empty()) {
		delete team1_dup;
		return StatusType::FAILURE;
	}

	int team2_index = m_teams->getIndexOfKey(teamId2);
	Team* team2_dup = new Team(teamId2);
	if (team2_dup == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
	BinaryTreeNode<Team>* team2_node = m_teams->getData()[team2_index]->search(team2_dup);
	if (team2_node == nullptr || team2_node->getData()->getContestantsStack()->empty()) {
		delete team2_dup;
		return StatusType::FAILURE;
	}
	Team* team1 = team1_node->getData();
	Team* team2 = team2_node->getData();

	int team1_strength = team1->getContestants()->getTreeSize() * team1->getMeanStrength();
	int team2_strength = team2->getContestants()->getTreeSize() * team2->getMeanStrength();
	if (team1_strength > team2_strength) {
		team1->setNumOfWins(team1->getNumOfWins() + 1);
	}
	else if (team1_strength < team2_strength) {
		team2->setNumOfWins(team2->getNumOfWins() + 1);
	}
	else {
		if (team1->getTeamID() < team2->getTeamID()) {
			team1->setNumOfWins(team1->getNumOfWins() + 1);
		}
		else {
			team2->setNumOfWins(team2->getNumOfWins() + 1);
		}
	}

	delete team1_dup;
	delete team2_dup;
	return  output_t<int>(StatusType::SUCCESS);
}

output_t<int> olympics_t::num_wins_for_team(int teamId) {
	return 1;
}

output_t<int> olympics_t::get_highest_ranked_team() {
	return 1;
}

StatusType olympics_t::unite_teams(int teamId1, int teamId2) {
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower) {
	// TODO: Your code goes here
	return 1;
}
