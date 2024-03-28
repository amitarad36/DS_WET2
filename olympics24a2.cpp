#include "olympics24a2.h"

#define MAX_TEAMS 1000

static int last_wins = 0;
static int team_wins[MAX_TEAMS] = { 0 }; // Array to store wins for each team

static void assert(BinaryTree<Team>* m_teams_tree, HashObj<Team>* m_teams) {
	// Create an array to hold pointers to Team objects
	Team* teams[MAX_TEAMS];

	// Copy elements of the tree into the array using inorder traversal
	m_teams_tree->inorderToArray(teams);

	// Iterate through the array of teams
	for (int i = 0; i < m_teams_tree->getTreeSize(); ++i) {
		Team* current_team = teams[i];
		int current_wins = m_teams_tree->teamNumOfWins(current_team);

		// Check if wins for the current team have changed
		if (current_wins != team_wins[current_team->getTeamID()]) {			cout << "Team " << current_team->getTeamID() << ": " << team_wins[current_team->getTeamID()] << " -> " << current_wins << endl;
			team_wins[current_team->getTeamID()] = current_wins;
		}
	}
}



olympics_t::olympics_t() : m_num_of_teams(0),
m_teams_tree(new BinaryTree<Team>()), m_teams(new HashObj<Team>()) {}

olympics_t::~olympics_t()
{
	// TODO: Your code goes here
}

StatusType olympics_t::add_team(int teamId) {

	assert(m_teams_tree, m_teams);

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

	if (m_teams->resize(true) == StatusType::ALLOCATION_ERROR)
		return StatusType::ALLOCATION_ERROR;
	m_num_of_teams++;
	return return_val;
}

StatusType olympics_t::remove_team(int teamId) {

	assert(m_teams_tree, m_teams);
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
	Team* team_to_remove = team_to_remove_node->getData();
	m_teams_tree->removeByStrengthAndId(team_to_remove);
	StatusType return_val = m_teams->getData()[team_index]->remove(team_to_remove);
	if (return_val == StatusType::SUCCESS) {
		delete team_to_remove;
		m_teams->setNumOfElements(m_teams->getNumOfElements() - 1);
	}

	if (m_teams->resize(false) == StatusType::ALLOCATION_ERROR)
		return StatusType::ALLOCATION_ERROR;
	m_num_of_teams--;
	return return_val;
}

StatusType olympics_t::add_player(int teamId, int playerStrength) {
	assert(m_teams_tree, m_teams);

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
	Team * team = team_node->getData();
	Contestant * new_contestant = new Contestant(playerStrength);
	if (new_contestant == nullptr) {
		return StatusType::ALLOCATION_ERROR;
		delete team_dup;
	}
	int num_of_wins = m_teams_tree->teamNumOfWins(team);
	
	m_teams_tree->removeByStrengthAndId(team); // make sure the num of wins is correct

	if (team->getContestants()->insert(new_contestant) == StatusType::ALLOCATION_ERROR) {
		delete team_dup;
		return StatusType::ALLOCATION_ERROR;
	}
	team->getContestantsStack()->push(new_contestant->getStrength(), new_contestant->getTimeStamp());
	team->setStrength(team->getMeanStrength() * team->getContestants()->getTreeSize());
	m_teams_tree->insertByStrengthAndId(team);
	int rank = m_teams_tree->getRankByTeam(team);
	if (rank > 0 && num_of_wins > 0) {
		m_teams_tree->addWinToTeams(rank, num_of_wins);
		if(rank > 1) m_teams_tree->addWinToTeams(rank - 1, -num_of_wins);
	}

	team->setWasInTeamsTree(true);
	delete team_dup;
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_newest_player(int teamId) {	assert(m_teams_tree, m_teams);

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

	Team* team = team_node->getData();
	int num_of_wins = m_teams_tree->teamNumOfWins(team);
	m_teams_tree->removeByStrengthAndId(team); // make sure the num of wins is correct
	
	int contestant_strength = team->getContestantsStack()->top()->getContestantStrength();
	int contestant_time_stamp = team->getContestantsStack()->top()->getContestantTimeStamp();
	Contestant* contestant_to_remove_dup = new Contestant(contestant_strength, contestant_time_stamp);
	team->getContestantsStack()->pop();
	BinaryTreeNode<Contestant>* contestant_to_remove_node = team->getContestants()->search(contestant_to_remove_dup);
	Contestant* contestant = contestant_to_remove_node->getData();
	StatusType return_val = team->getContestants()->remove(contestant_to_remove_dup);
	if (return_val == StatusType::SUCCESS) {
		delete contestant;
	}
	team->setStrength(team->getMeanStrength() * team->getContestants()->getTreeSize());
	m_teams_tree->insertByStrengthAndId(team);
	int rank = m_teams_tree->getRankByTeam(team);
	team->setWasInTeamsTree(true);
	if (rank > 0 && num_of_wins > 0) {
		m_teams_tree->addWinToTeams(rank, num_of_wins);
		if (rank > 1) m_teams_tree->addWinToTeams(rank - 1, -num_of_wins);
	}
	delete contestant_to_remove_dup;
	delete team_dup;
	return return_val;
}

output_t<int> olympics_t::play_match(int teamId1, int teamId2) {
	assert(m_teams_tree, m_teams);

	if (teamId1 == teamId2 || teamId2 <= 0 || teamId1 <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}

	int team1_index = m_teams->getIndexOfKey(teamId1);
	Team* team1_dup = new Team(teamId1);
	if (team1_dup == nullptr) {
		return output_t<int>(StatusType::ALLOCATION_ERROR);
	}
	BinaryTreeNode<Team>* team1_node = m_teams->getData()[team1_index]->search(team1_dup);
	if (team1_node == nullptr || team1_node->getData()->getContestantsStack()->empty()) {
		delete team1_dup;
		return output_t<int>(StatusType::FAILURE);
	}

	int team2_index = m_teams->getIndexOfKey(teamId2);
	Team* team2_dup = new Team(teamId2);
	if (team2_dup == nullptr) {
		return output_t<int>(StatusType::ALLOCATION_ERROR);
	}
	BinaryTreeNode<Team>* team2_node = m_teams->getData()[team2_index]->search(team2_dup);
	if (team2_node == nullptr || team2_node->getData()->getContestantsStack()->empty()) {
		delete team2_dup;
		return output_t<int>(StatusType::FAILURE);
	}
	Team* team1 = team1_node->getData();
	Team* team2 = team2_node->getData();



	delete team1_dup;
	delete team2_dup;

	int team1_strength = team1->getStrength();
	int team2_strength = team2->getStrength();

	int rank_team1 = m_teams_tree->getRankByTeam(team1);
	int rank_team2 = m_teams_tree->getRankByTeam(team2);

	if (team1_strength > team2_strength) {
		m_teams_tree->addWinToTeamsInRange(rank_team1, rank_team1);
		return output_t<int>(teamId1);
	}
	else if (team1_strength < team2_strength) {
		m_teams_tree->addWinToTeamsInRange(rank_team2, rank_team2); // add win
		return output_t<int>(teamId2);

	}
	else {
		if (team1->getTeamID() < team2->getTeamID()) {
			m_teams_tree->addWinToTeamsInRange(rank_team1, rank_team1); // add win
			return output_t<int>(teamId1);

		}
		else {
			m_teams_tree->addWinToTeamsInRange(rank_team2, rank_team2); // add win
			return output_t<int>(teamId2);
		}
	}
}

output_t<int> olympics_t::num_wins_for_team(int teamId) {
	assert(m_teams_tree, m_teams);

	if (teamId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}

	int team_index = m_teams->getIndexOfKey(teamId);
	Team* team_dup = new Team(teamId);
	if (team_dup == nullptr) {
		return output_t<int>(StatusType::ALLOCATION_ERROR);
	}
	BinaryTreeNode<Team>* team_node = m_teams->getData()[team_index]->search(team_dup);
	if (team_node == nullptr) {
		delete team_dup;
		return output_t<int>(StatusType::FAILURE);
	}
	int wins = m_teams_tree->teamNumOfWins(team_node->getData()); //find wins
	delete team_dup;
	return output_t<int>(wins);
}

output_t<int> olympics_t::get_highest_ranked_team() {
	assert(m_teams_tree, m_teams);

	if (m_num_of_teams == 0) {
		return output_t<int>(-1);
	}
	if (m_teams_tree->getRoot() == nullptr) {
		return output_t<int>(0);
	}
	return output_t<int>(m_teams_tree->getRoot()->getSubtreeMaxRankedTeam());
}

StatusType olympics_t::unite_teams(int teamId1, int teamId2) {
	assert(m_teams_tree, m_teams);

	if (teamId1 == teamId2 || teamId2 <= 0 || teamId1 <= 0) {
		return StatusType::INVALID_INPUT;

	}
	int team1_index = m_teams->getIndexOfKey(teamId1);
	Team* team1_dup = new Team(teamId1);
	if (team1_dup == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
	BinaryTreeNode<Team>* team1_node = m_teams->getData()[team1_index]->search(team1_dup);
	if (team1_node == nullptr) {
		delete team1_dup;
		return StatusType::FAILURE;
	}

	int team2_index = m_teams->getIndexOfKey(teamId2);
	Team* team2_dup = new Team(teamId2);
	if (team2_dup == nullptr) {
		return StatusType::ALLOCATION_ERROR;
	}
	BinaryTreeNode<Team>* team2_node = m_teams->getData()[team2_index]->search(team2_dup);
	if (team2_node == nullptr) {
		delete team2_dup;
		return StatusType::FAILURE;
	}
	Team* team1 = team1_node->getData();
	Team* team2 = team2_node->getData();


	m_teams_tree->removeByStrengthAndId(team1);
	m_teams_tree->removeByStrengthAndId(team2);
	m_teams->getData()[team2_index]->remove(team2);

	int team1_size = team1->getContestants()->getTreeSize();
	int team2_size = team2->getContestants()->getTreeSize();
	Contestant** team1_contestants_arr = new Contestant * [team1_size];
	team1->getContestants()->inorderToArray(team1_contestants_arr);
	Contestant** team2_contestants_arr = new Contestant * [team2_size];
	team2->getContestants()->inorderToArray(team2_contestants_arr);
	Contestant** merged_contestants_arr = mergeSortedArrays(team1_contestants_arr, team1_size, team2_contestants_arr, team2_size);
	BinaryTree<Contestant>* team1_new_contestants_tree = buildTeamTreeFromArrayCont(merged_contestants_arr, team1_size + team2_size);

	delete team1->getContestants();

	team1->setContestants(team1_new_contestants_tree);

	Stack* flipped_contestants_stack = team2->getContestantsStack()->flipStack();
	while (!flipped_contestants_stack->empty()) {
		team1->getContestantsStack()->push(flipped_contestants_stack->top()->getContestantStrength(), flipped_contestants_stack->top()->getContestantTimeStamp());
		flipped_contestants_stack->pop();
	}



	delete flipped_contestants_stack;

	team1->setStrength(team1->getMeanStrength() * team1->getContestants()->getTreeSize());
	m_teams_tree->insertByStrengthAndId(team1);
	team1->setWasInTeamsTree(true);

	if (m_teams->resize(false) == StatusType::ALLOCATION_ERROR)
		return StatusType::ALLOCATION_ERROR;

	m_num_of_teams--;


	delete[] team1_contestants_arr;
	delete[] team2_contestants_arr;
	delete[] merged_contestants_arr;

	delete team1_dup;
	delete team2_dup;

	team2->getContestants()->postorderDelete();
	delete team2;



	return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower) {


	if (highPower <= 0 || lowPower <= 0 || highPower <= lowPower) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}

	// Find the minimal and maximal teams
	Team* minimal_team = findMinTeam(m_teams_tree->getRoot(), lowPower);
	Team* maximal_team = findMaxTeam(m_teams_tree->getRoot(), highPower);

	// Get the ranks of the minimal and maximal teams
	int min_rank = m_teams_tree->getRankByTeam(minimal_team);
	int max_rank = m_teams_tree->getRankByTeam(maximal_team);

	// Check if the difference between max and min rank is a power of 2
	int rank_difference = max_rank - min_rank + 1;
	while (rank_difference > 1) {
		if (rank_difference % 2 != 0) {
			return output_t<int>(StatusType::FAILURE);
		}
		rank_difference /= 2;
	}



	return output_t<int>(StatusType::SUCCESS);
}

static Contestant** mergeSortedArrays(Contestant** arr1, int size1, Contestant** arr2, int size2) {
	Contestant** merged_arr = new Contestant * [size1 + size2];

	int i = 0, j = 0, k = 0;

	while (i < size1 && j < size2) {
		if (*arr1[i] < *arr2[j]) {
			merged_arr[k++] = arr1[i++];
		}
		else {
			merged_arr[k++] = arr2[j++];
		}
	}

	while (i < size1) {
		merged_arr[k++] = arr1[i++];
	}

	while (j < size2) {
		merged_arr[k++] = arr2[j++];
	}

	return merged_arr;
}

static BinaryTree<Contestant>* buildTeamTreeFromArrayCont(Contestant** merged_arr, int size) {
	BinaryTree<Contestant>* tree = new BinaryTree<Contestant>();
	tree->setRoot(buildTeamTreeFromArrayCont_aux(merged_arr, 0, size - 1));
	tree->setTreeSize(size);
	return tree;
}

static BinaryTreeNode<Contestant>* buildTeamTreeFromArrayCont_aux(Contestant** merged_arr, int start, int end) {
	if (start > end) {
		return nullptr;
	}

	int mid = (start + end) / 2;
	BinaryTreeNode<Contestant>* root = new BinaryTreeNode<Contestant>(merged_arr[mid]);
	root->setLeft(buildTeamTreeFromArrayCont_aux(merged_arr, start, mid - 1));
	root->setRight(buildTeamTreeFromArrayCont_aux(merged_arr, mid + 1, end));

	// Update subtreeSize
	int left_subtree_size = root->getLeft() ? root->getLeft()->getSubtreeSize() : 0;
	int right_subtree_size = root->getRight() ? root->getRight()->getSubtreeSize() : 0;
	root->setSubtreeSize(1 + left_subtree_size + right_subtree_size);

	// Update height
	int left_height = root->getLeft() ? root->getLeft()->getHeight() : -1;
	int right_height = root->getRight() ? root->getRight()->getHeight() : -1;
	root->setHeight(1 + max(left_height, right_height));

	return root;
}

static Team* findMinTeam(BinaryTreeNode<Team>* root, int x) {
	return findMinTeam_aux(root, x, nullptr);
}

static Team* findMaxTeam(BinaryTreeNode<Team>* root, int x) {
	return findMaxTeam_aux(root, x, nullptr);
}

static Team* findMinTeam_aux(BinaryTreeNode<Team>* root, int x, Team* candidate = nullptr) {
	if (root == nullptr)
		return candidate;

	if (root->getData()->getStrength() >= x) {
		if (candidate == nullptr || root->getData()->lessThanByStrengthAndId(candidate)) {
			candidate = root->getData();
		}
		return findMinTeam_aux(root->getLeft(), x, candidate);
	}
	else {
		return findMinTeam_aux(root->getRight(), x, candidate);
	}
}

static Team* findMaxTeam_aux(BinaryTreeNode<Team>* root, int x, Team* candidate = nullptr) {
	if (root == nullptr)
		return candidate;

	if (root->getData()->getStrength() <= x) {
		if (candidate == nullptr || candidate->lessThanByStrengthAndId(root->getData())) {
			candidate = root->getData();
		}
		return findMaxTeam_aux(root->getRight(), x, candidate);
	}
	else {
		return findMaxTeam_aux(root->getLeft(), x, candidate);
	}
}

