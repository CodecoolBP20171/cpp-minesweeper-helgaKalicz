//

#include "Mine.h"

//
// Created by kalicz on 2017.10.03..
Mine::Mine(bool isMine) {
    this->isMine = isMine;
    isTurnedUp = false;
    isEmpty = true;
    neighbours = 0;
}

bool Mine::getIsMine() {
    return isMine;
}

bool Mine::getIsEmpty() {
    return isEmpty;
}

void Mine::setIsEmpty(bool isEmpty) {
    this->isEmpty = isEmpty;
}

bool Mine::getIsTurnedUp() {
    return isTurnedUp;
}

void Mine::setIsTurnedUp(bool isTurnedUp) {
    this->isTurnedUp = isTurnedUp;
}

int Mine::getNeighbours() {
    return neighbours;
}

void Mine::addNeighbours() {
    ++neighbours;
}
