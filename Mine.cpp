#include "Mine.h"

Mine::Mine(int value) {
    this->isTurnedUp = false;
    this->value = value;
}

bool Mine::getIsTurnedUp() { return this->isTurnedUp; }

void Mine::turnUp() { this->isTurnedUp = true; }

int Mine::getNeighbours() { return this->value; }

void Mine::addNeighbours() { this->value++; }
