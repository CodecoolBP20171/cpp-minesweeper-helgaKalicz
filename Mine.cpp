#include "Mine.h"

Mine::Mine(bool isMine) {
    this->isMine = isMine;
    isTurnedUp = false;
    isEmpty = true;
    neighbours = 0;
}

bool Mine::getIsMine() { return isMine; }

bool Mine::getIsEmpty() { return this->isEmpty; }

void Mine::setIsEmpty() { this->isEmpty = false; }

bool Mine::getIsTurnedUp() { return this->isTurnedUp; }

void Mine::setIsTurnedUp() { this->isTurnedUp = true; }

int Mine::getNeighbours() { return this->neighbours; }

void Mine::addNeighbours() { ++neighbours; }
