#ifndef CONTESTANT_H
#define CONTESTANT_H

#define MAX_TEAMS_PER_CONTESTANT 3

#include <iostream>
#include "BinaryTreeNode.h"

class Contestant {
private:
	int m_strength;
	int m_contestant_time_stamp;
	static int numContestants;
public:

	Contestant(int strength);

	Contestant(int strength, int contestant_time_stamp);

	virtual ~Contestant();

	int getStrength() const;

	int getTimeStamp() const;

	bool getWasInTeamsTree();

	void setStrength(int strength);

	int lessThanByStrengthAndId(Contestant* other);

	bool operator<(const Contestant& c) const;

	bool operator>(const Contestant& c) const;

	bool operator==(const Contestant& c) const;

	friend std::ostream& operator<<(std::ostream& os, const Contestant& obj);
};
#endif // CONTESTANT_H
