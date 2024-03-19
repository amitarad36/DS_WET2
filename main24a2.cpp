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

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);


#include <iostream>
#include "BinaryTree.h"

#include <iostream>

int main() {
    // Create an instance of the olympics_t class
    olympics_t olympics;

    // Insert 10 teams
    for (int i = 1; i <= 10; ++i) {
        StatusType add_status = olympics.add_team(i);
        if (add_status == StatusType::SUCCESS) {
            std::cout << "Team " << i << " added successfully." << std::endl;
        }
        else {
            std::cout << "Failed to add team " << i << "." << std::endl;
        }

        // Print hash table after insertion
        std::cout << "Hash Table After Insertion:" << std::endl;
        for (int j = 0; j < olympics.m_teams->getHashTableSize(); ++j) {
            std::cout << "Hash Table Index " << j << ":" << std::endl;
            olympics.m_teams->getData()[j]->printTree();
            std::cout << std::endl;
        }
    }

    // Remove 5 teams
    for (int i = 1; i <= 5; ++i) {
        StatusType remove_status = olympics.remove_team(i);
        if (remove_status == StatusType::SUCCESS) {
            std::cout << "Team " << i << " removed successfully." << std::endl;
        }
        else {
            std::cout << "Failed to remove team " << i << "." << std::endl;
        }

        // Print hash table after removal
        std::cout << "Hash Table After Removal:" << std::endl;
        for (int j = 0; j < olympics.m_teams->getHashTableSize(); ++j) {
            std::cout << "Hash Table Index " << j << ":" << std::endl;
            olympics.m_teams->getData()[j]->printTree();
            std::cout << std::endl;
        }
    }

    return 0;
}


//int main()
//{
//	
//    int d1, d2;
//
//    // Init
//    olympics_t *obj = new olympics_t();
//	
//    // Execute all commands in file
//	string op;
//	while (cin >> op)
//    {
//        if (!op.compare("add_team")) {
//            cin >> d1;
//            print(op, obj->add_team(d1));
//        } else if (!op.compare("remove_team")) {
//            cin >> d1;
//            print(op, obj->remove_team(d1));
//        } else if (!op.compare("add_player")) {
//            cin >> d1 >> d2;
//            print(op, obj->add_player(d1, d2));
//        } else if (!op.compare("remove_newest_player")) {
//            cin >> d1;
//            print(op, obj->remove_newest_player(d1));
//        } else if (!op.compare("play_match")) {
//            cin >> d1 >> d2;
//            print(op, obj->play_match(d1, d2));
//        } else if (!op.compare("num_wins_for_team")) {
//            cin >> d1;
//            print(op, obj->num_wins_for_team(d1));
//        } else if (!op.compare("get_highest_ranked_team")) {
//            print(op, obj->get_highest_ranked_team());
//        } else if (!op.compare("unite_teams")) {
//            cin >> d1 >> d2;
//            print(op, obj->unite_teams(d1, d2));
//        } else if (!op.compare("play_tournament")) {
//            cin >> d1 >> d2;
//            print(op, obj->play_tournament(d1, d2));
//        } else {
//            cout << "Unknown command: " << op << endl;
//            return -1;
//        }
//        // Verify no faults
//        if (cin.fail()){
//            cout << "Invalid input format" << endl;
//            return -1;
//        }
//    }
//
//    // Quit 
//	delete obj;
//	return 0;
//}

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
