#include "Contestant.h"
#include <iostream>

Contestant::Contestant(int strength) : m_strength(strength) {}

Contestant::~Contestant() {}

int Contestant::getStrength() const {
	return m_strength;
}

void Contestant::setStrength(int strength) {
	m_strength = strength;
}

bool Contestant::operator<(const Contestant& c) const {
	return getStrength() < c.getStrength();
}

bool Contestant::operator>(const Contestant& c) const {
	return (c < *this);
}

bool Contestant::operator==(const Contestant& c) const {
	return (getStrength() == c.getStrength());
}

std::ostream& operator<<(std::ostream& os, const Contestant& obj) {
	os << obj.getStrength();
	return os;
}
