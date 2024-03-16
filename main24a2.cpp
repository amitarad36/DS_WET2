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

int main() {
	// Create a BinaryTree of integers
	BinaryTree<int> tree;

	// Insert some elements
	tree.insert(new int(10));
	tree.insert(new int(5));
	tree.insert(new int(4));
	tree.insert(new int(1));
	tree.insert(new int(15));
	tree.insert(new int(3));
	tree.insert(new int(7));
	tree.insert(new int(12));
	tree.insert(new int(17));
	tree.insert(new int(127));


	// Test the getElementByRank function
	for (int i = 1; i <= tree.getTreeSize(); ++i) {
		BinaryTreeNode<int>* node = tree.getElementByRank(i);
		if (node != nullptr) {
			std::cout << "Element at rank " << i << ": " << *(node->getData()) << std::endl;
		}
		else {
			std::cout << "No element found at rank " << i << std::endl;
		}
	}
	tree.printTree();

	for (int i = 0; i < 10; i++) {
		int* num = new int(); // Dynamically allocate memory for each input integer
		std::cin >> *num;     // Read input integer from std::cin

		tree.remove(num);     // Pass the pointer 'num' to the remove function
		delete num;           // Deallocate memory allocated for 'num'

		// Print the elements in the tree after removal
		for (int j = 1; j <= tree.getTreeSize(); ++j) {
			BinaryTreeNode<int>* node = tree.getElementByRank(j);
			if (node != nullptr) {
				std::cout << "Element at rank " << j << ": " << *(node->getData()) << std::endl;
			}
			else {
				std::cout << "No element found at rank " << j << std::endl;
			}
		}

		tree.printTree();
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
