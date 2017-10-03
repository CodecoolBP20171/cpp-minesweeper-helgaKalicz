//
// Created by kalicz on 2017.10.03..
//

#ifndef MINESWEEPER_MINE_H
#define MINESWEEPER_MINE_H


class Mine {
public:
    Mine(bool isMine);

    bool getIsMine();

    bool getIsEmpty();
    void setIsEmpty(bool isEmpty);

    bool getIsTurnedUp();
    void setIsTurnedUp(bool isTurnedUp);

    int getNeighbours();
    void addNeighbours();

private:
    bool isMine;
    bool isEmpty;
    bool isTurnedUp;
    int neighbours;

};


#endif //MINESWEEPER_MINE_H
