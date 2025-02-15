#include "Contestant.h"
#include <iostream>

int Contestant::numContestants = 0;

Contestant::Contestant(int strength) : m_strength(strength) {
	m_contestant_time_stamp = numContestants;
	numContestants++;
}

Contestant::Contestant(int strength, int contestant_time_stamp) : m_strength(strength), m_contestant_time_stamp(contestant_time_stamp) {}

Contestant::~Contestant() {}

int Contestant::getStrength() const {
	return m_strength;
}

int Contestant::getTimeStamp() const {
	return m_contestant_time_stamp;
}

bool Contestant::getWasInTeamsTree() {
	return true;
}

void Contestant::setStrength(int strength) {
	m_strength = strength;
}

int Contestant::lessThanByStrengthAndId(Contestant* other) {
	return 0;
}

bool Contestant::operator<(const Contestant& c) const {
	if (getStrength() < c.getStrength())
		return true;
	else if (getStrength() == c.getStrength()) {
		return (getTimeStamp() < c.getTimeStamp());
	}
	return false;
}

bool Contestant::operator>(const Contestant& c) const {
	return (c < *this);
}

bool Contestant::operator==(const Contestant& c) const {
	return (getStrength() == c.getStrength());
}

std::ostream& operator<<(std::ostream& os, const Contestant& obj)
{
	os << obj.getStrength();
	return os;
}
