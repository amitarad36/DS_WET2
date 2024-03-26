// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
// 

#include "olympics24a2.h"
#include <string>
#include <iostream>


using namespace std;

//int main() {
//	// Create an instance of the olympics_t class
//	olympics_t olympics;
//
//	int choice = 0;
//	while (choice != 10) {
//		std::cout << "Choose the function to invoke:" << std::endl;
//		std::cout << "1. Add Team" << std::endl;
//		std::cout << "2. Remove Team" << std::endl;
//		std::cout << "3. Add Player" << std::endl;
//		std::cout << "4. Remove Newest Player" << std::endl;
//		std::cout << "5. Play Match" << std::endl;
//		std::cout << "6. Number of Wins for Team" << std::endl;
//		std::cout << "7. Get Highest Ranked Team" << std::endl;
//		std::cout << "8. Unite Teams" << std::endl;
//		std::cout << "9. Play Tournament" << std::endl;
//		std::cout << "10. Finish" << std::endl;
//		std::cout << "Enter your choice: ";
//		std::cin >> choice;
//
//		switch (choice) {
//		case 1: {
//			// Add Team
//			int team_id;
//			std::cout << "Enter team ID: ";
//			std::cin >> team_id;
//			StatusType add_team_status = olympics.add_team(team_id);
//			if (add_team_status == StatusType::SUCCESS) {
//				std::cout << "Team " << team_id << " added successfully." << std::endl;
//			}
//			else {
//				std::cout << "Failed to add team " << team_id << "." << std::endl;
//			}
//			break;
//		}
//		case 2: {
//			// Remove Team
//			int team_id;
//			std::cout << "Enter team ID to remove: ";
//			std::cin >> team_id;
//			StatusType remove_team_status = olympics.remove_team(team_id);
//			if (remove_team_status == StatusType::SUCCESS) {
//				std::cout << "Team " << team_id << " removed successfully." << std::endl;
//			}
//			else {
//				std::cout << "Failed to remove team " << team_id << "." << std::endl;
//			}
//			break;
//		}
//		case 3: {
//			// Add Player
//			int team_id, player_strength;
//			std::cout << "Enter team ID to add player to: ";
//			std::cin >> team_id;
//			std::cout << "Enter player strength: ";
//			std::cin >> player_strength;
//			StatusType add_player_status = olympics.add_player(team_id, player_strength);
//			if (add_player_status == StatusType::SUCCESS) {
//				std::cout << "Player added to team " << team_id << " successfully." << std::endl;
//			}
//			else {
//				std::cout << "Failed to add player to team " << team_id << "." << std::endl;
//			}
//			break;
//		}
//		case 4: {
//			// Remove Newest Player
//			int team_id;
//			std::cout << "Enter team ID to remove the newest player from: ";
//			std::cin >> team_id;
//			StatusType remove_player_status = olympics.remove_newest_player(team_id);
//			if (remove_player_status == StatusType::SUCCESS) {
//				std::cout << "Newest player removed from team " << team_id << " successfully." << std::endl;
//			}
//			else {
//				std::cout << "Failed to remove newest player from team " << team_id << "." << std::endl;
//			}
//			break;
//		}
//		case 5: {
//			// Play Match
//			int team_id1, team_id2;
//			std::cout << "Enter team ID 1: ";
//			std::cin >> team_id1;
//			std::cout << "Enter team ID 2: ";
//			std::cin >> team_id2;
//			output_t<int> match_result = olympics.play_match(team_id1, team_id2);
//			if (match_result.status() == StatusType::SUCCESS) {
//				std::cout << "Match played successfully:" << std::endl;
//			}
//			else {
//				std::cout << "Failed to play the match." << std::endl;
//			}
//			break;
//		}
//		case 6: {
//			// Number of Wins for Team
//			int team_id;
//			std::cout << "Enter team ID: ";
//			std::cin >> team_id;
//			output_t<int> num_wins = olympics.num_wins_for_team(team_id);
//			if (num_wins.status() == StatusType::SUCCESS) {
//				std::cout << "Number of wins for team " << team_id << ": " << num_wins.ans()
//					<< std::endl;
//			}
//			else {
//				std::cout << "Failed to get number of wins for team " << team_id << "." << std::endl;
//			}
//			break;
//		}
//		case 7: {
//			// Get Highest Ranked Team
//			output_t<int> highest_ranked_team = olympics.get_highest_ranked_team();
//			if (highest_ranked_team.status() == StatusType::SUCCESS) {
//				std::cout << "Highest ranked team: " << highest_ranked_team.ans() << std::endl;
//			}
//			else {
//				std::cout << "Failed to get highest ranked team." << std::endl;
//			}
//			break;
//		}
//		case 8: {
//			// Unite Teams
//			int team_id1, team_id2;
//			std::cout << "Enter team ID 1: ";
//			std::cin >> team_id1;
//			std::cout << "Enter team ID 2: ";
//			std::cin >> team_id2;
//			StatusType unite_status = olympics.unite_teams(team_id1, team_id2);
//			if (unite_status == StatusType::SUCCESS) {
//				std::cout << "Teams " << team_id1 << " and " << team_id2 << " united successfully." << std::endl;
//			}
//			else {
//				std::cout << "Failed to unite teams " << team_id1 << " and " << team_id2 << "." << std::endl;
//			}
//			break;
//		}
//		case 9: {
//			// Play Tournament
//			int low_power, high_power;
//			std::cout << "Enter low power: ";
//			std::cin >> low_power;
//			std::cout << "Enter high power: ";
//			std::cin >> high_power;
//			output_t<int> tournament_result = olympics.play_tournament(low_power, high_power);
//			if (tournament_result.status() == StatusType::SUCCESS) {
//				std::cout << "Tournament played successfully:" << std::endl;
//			}
//			else {
//				std::cout << "Failed to play the tournament." << std::endl;
//			}
//			break;
//		}
//		case 10: {
//			std::cout << "Exiting the program." << std::endl;
//			break;
//		}
//		default:
//			std::cout << "Invalid choice. Please try again." << std::endl;
//		}
//	}
//
//	return 0;
//}

int main() {
    // Create a binary tree of teams
    BinaryTree<Team> teamTree;

    // Insert some teams
    Team team1(1);
    Team team2(2);
    Team team3(3);
    Team team4(4);
    Team team5(5);
    Team team6(6);


    teamTree.insertByStrengthAndId(&team1);
    teamTree.insertByStrengthAndId(&team2);
    teamTree.insertByStrengthAndId(&team3);
    teamTree.insertByStrengthAndId(&team4);
    teamTree.insertByStrengthAndId(&team5);
    teamTree.insertByStrengthAndId(&team6);

    
    team1.setWasInTeamsTree(true);
    team2.setWasInTeamsTree(true);
    team3.setWasInTeamsTree(true);
    team4.setWasInTeamsTree(true);
    team5.setWasInTeamsTree(true);
    team6.setWasInTeamsTree(true);

    teamTree.printTree();

    // Add wins to teams within a rank range
    teamTree.addWinToTeamsInRange(1, 2);
    teamTree.addWinToTeamsInRange(3, 4);



    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;


    // Print number of wins for each team
    cout << "Number of wins for Team 1: " << teamTree.teamNumOfWins(&team1) << endl;
    cout << "Number of wins for Team 2: " << teamTree.teamNumOfWins(&team2) << endl;
    cout << "Number of wins for Team 3: " << teamTree.teamNumOfWins(&team3) << endl;
    cout << "Number of wins for Team 4: " << teamTree.teamNumOfWins(&team4) << endl;
    cout << "Number of wins for Team 5: " << teamTree.teamNumOfWins(&team5) << endl;
    cout << "Number of wins for Team 6: " << teamTree.teamNumOfWins(&team6) << endl;

 

    Team team11(11);

    team11.setWasInTeamsTree(true);
    teamTree.insertByStrengthAndId(&team11);
    teamTree.printTree();
    cout << "Number of wins for Team 11: " << teamTree.teamNumOfWins(&team11) << endl;


    return 0;
}


// Helpers
static const char* StatusTypeStr[] =
{
	"SUCCESS",
	"ALLOCATION_ERROR",
	"INVALID_INPUT",
	"FAILURE"
};

void print(string cmd, StatusType res)
{
	cout << cmd << ": " << StatusTypeStr[(int)res] << endl;
}

void print(string cmd, output_t<int> res)
{
	if (res.status() == StatusType::SUCCESS) {
		cout << cmd << ": " << StatusTypeStr[(int)res.status()] << ", " << res.ans() << endl;
	}
	else {
		cout << cmd << ": " << StatusTypeStr[(int)res.status()] << endl;
	}
}

//int main()
//{
//    int d1, d2;
//
//    // Init
//    olympics_t* obj = new olympics_t();
//
//    // Execute all commands in file
//    string op;
//    while (cin >> op)
//    {
//        if (!op.compare("add_team")) {
//            cin >> d1;
//            print(op, obj->add_team(d1));
//        }
//        else if (!op.compare("remove_team")) {
//            cin >> d1;
//            print(op, obj->remove_team(d1));
//        }
//        else if (!op.compare("add_player")) {
//            cin >> d1 >> d2;
//            print(op, obj->add_player(d1, d2));
//        }
//        else if (!op.compare("remove_newest_player")) {
//            cin >> d1;
//            print(op, obj->remove_newest_player(d1));
//        }
//        else if (!op.compare("play_match")) {
//            cin >> d1 >> d2;
//            print(op, obj->play_match(d1, d2));
//        }
//        else if (!op.compare("num_wins_for_team")) {
//            cin >> d1;
//            print(op, obj->num_wins_for_team(d1));
//        }
//        else if (!op.compare("get_highest_ranked_team")) {
//            print(op, obj->get_highest_ranked_team());
//        }
//        else if (!op.compare("unite_teams")) {
//            cin >> d1 >> d2;
//            print(op, obj->unite_teams(d1, d2));
//        }
//        else if (!op.compare("play_tournament")) {
//            cin >> d1 >> d2;
//            print(op, obj->play_tournament(d1, d2));
//        }
//        else {
//            cout << "Unknown command: " << op << endl;
//            return -1;
//        }
//        // Verify no faults
//        if (cin.fail()) {
//            cout << "Invalid input format" << endl;
//            return -1;
//        }
//    }
//
//    // Quit 
//    delete obj;
//    return 0;
//}
