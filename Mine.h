//
// Created by kalicz on 2017.10.03..
//

#ifndef MINESWEEPER_MINE_H
#define MINESWEEPER_MINE_H


class Mine {
public:
    Mine(int value = 0);

    bool getIsTurnedUp();
    void turnUp();

    int getNeighbours();
    void addNeighbours();

private:
    bool isTurnedUp;
    int value;

};


#endif //MINESWEEPER_MINE_H
