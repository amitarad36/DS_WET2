#ifndef CONTESTANT_H
#define CONTESTANT_H

#define MAX_TEAMS_PER_CONTESTANT 3

#include <iostream>
#include "BinaryTreeNode.h"

class Contestant {
private:
	int m_strength;

public:

	Contestant(int strength);

	virtual ~Contestant();

	int getStrength() const;

	void setStrength(int strength);

	bool operator<(const Contestant& c) const;

	bool operator>(const Contestant& c) const;

	bool operator==(const Contestant& c) const;

	friend std::ostream& operator<<(std::ostream& os, const Contestant& obj);
};
#endif // CONTESTANT_H
