#include <iostream>
#include <algorithm>
#include "Mine.h"

namespace {
    class Minesweeper {
    public:
        Minesweeper(const size_t width, const size_t height)
                : width(width), height(height),
                  table(new char[width * height]) {
            fillTable();
        }

        /* In a real implementation there would also be a
         * - copy constructor
         * - assignment operator
         * - move constructor
         * - move assignment operator
         * We will learn about them later
         */

        virtual ~Minesweeper() {
            delete[] table;
        }

        void countNeighbours() {
            // step 2 goes here
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (mineField[i][j].getIsMine()) {
                        for (int k = -1; k <= 1; ++k) {
                            for (int l = -1; l <= 1; ++l) {
                                if (!(k == 0 && l == 0)) {
                                    if (!(i+k < 0 || i+k >= height || j+l < 0 || j+l >= width)) {
                                        mineField[i+k][j+l].addNeighbours();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        void setEmptiness() {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (mineField[i][j].getNeighbours() > 0) mineField[i][j].setIsEmpty();
                }
            }
        }

        void printTable() const {
            // step 3 goes here
            for (std::vector<Mine> fieldRow : mineField) {
                for (int i = 0; i < width*4+1; ++i) std::cout << '-';
                std::cout << std::endl;
                for (Mine fieldCell : fieldRow) fieldCell.getIsTurnedUp() ? std::cout << "| " << fieldCell.getNeighbours() << " " : std::cout<< "|   ";
                std::cout << "|" << std::endl;
            }
            for (int i = 0; i < width*4+1; ++i) std::cout << '-';
            std::cout << std::endl;

        }

        void printTable2() const {
            // Print out the table just for help.
            for (std::vector<Mine> fieldRow : mineField) {
                for (int i = 0; i < width*4+1; ++i) std::cout << '-';
                std::cout << std::endl;
                for (Mine fieldCell : fieldRow) fieldCell.getIsMine() ? std::cout << "| * " : std::cout<< "| " << fieldCell.getNeighbours() << " ";
                std::cout << "|" << std::endl;
            }
            for (int i = 0; i < width*4+1; ++i) std::cout << '-';
            std::cout << std::endl;
        }

        void turnUpField(int x, int y) {
            mineField[x][y].setIsTurnedUp();
            if (mineField[x][y].getIsEmpty()) {
                int counter = 0;
                for (int i = x-1; i <= x+1; ++i) {
                    for (int j = y-1; j <= y+1; ++j) {
                        ++counter;
                        if (counter % 2 == 0 && i >= 0 && j >=0 && i < height && j < width) {
                            if (!mineField[i][j].getIsMine() && !mineField[i][j].getIsEmpty()) {
                                mineField[i][j].setIsTurnedUp();
                            }
                            else if (mineField[i][j].getIsEmpty() && !mineField[i][j].getIsTurnedUp()) {
                                mineField[i][j].setIsTurnedUp();
                                turnUpField(i, j);
                            }
                        }
                    }
                }
            }
        }

        bool gameEnd() {
            for (std::vector<Mine> fieldRow : mineField) {
                for (Mine fieldCell : fieldRow) {
                    if (fieldCell.getIsMine() && fieldCell.getIsTurnedUp()) { return false; }
                    else if (!fieldCell.getIsMine() && !fieldCell.getIsTurnedUp()) { return false; }
                }
            }
            return true;
        }

    private:

        void fillTable() {
            // step 1 goes here
            for (int i = 0; i < height; ++i) {
                std::vector<Mine> character;
                for (int j = 0; j < width; ++j) rand() % 100 > 90 ? character.emplace_back(Mine(true)) : character.emplace_back(Mine(false));
                mineField.push_back(character);
            }
        }

        const size_t width, height;
        char *table;
        std::vector<std::vector<Mine>> mineField;
    };
}


int main() {
    srand(time(0));
    try {
        Minesweeper ms(10, 10);
        ms.countNeighbours();
        ms.setEmptiness();
        ms.printTable2();
        ms.printTable();
        while (!ms.gameEnd()) {
            int x;
            int y;
            std::cin >> x;
            std::cin >> y;
            ms.turnUpField(x, y);
            ms.printTable();
        }
        std::cout << "Game end!";
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}