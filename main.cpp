#include "Mine.h"
#include <iostream>
#include <algorithm>

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
                    if (mineField[i][j].getNeighbours() == -1) {
                        for (int k = -1; k <= 1; ++k) {
                            for (int l = -1; l <= 1; ++l) {
                                if (!(k == 0 && l == 0)) {
                                    if (!(i+k < 0 || i+k >= height || j+l < 0 || j+l >= width)) {
                                        if (mineField[i + k][j + l].getNeighbours() != -1) {
                                            mineField[i + k][j + l].addNeighbours();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }


        void turnUpField(int x, int y) {
            mineField[x][y].turnUp();
            if (mineField[x][y].getNeighbours() == 0) {
                for (int i = x-1; i <= x+1; ++i) {
                    for (int j = y-1; j <= y+1; ++j) {
                        if (i >= 0 && j >=0 && i < height && j < width) {
                            if (mineField[i][j].getNeighbours() > 0) {
                                mineField[i][j].turnUp();
                            }
                            else if (mineField[i][j].getNeighbours() == 0 && !mineField[i][j].getIsTurnedUp()) {
                                turnUpField(i, j);
                            }
                        }
                    }
                }
            }
        }


        void printTable() const {
            // step 3 goes here
            for (std::vector<Mine> fieldRow : mineField) {
                for (int i = 0; i < width*4+1; ++i) std::cout << '-';
                std::cout << std::endl;
                for (Mine fieldCell : fieldRow) {
                    if (fieldCell.getIsTurnedUp()) {
                        if (fieldCell.getNeighbours() == -1) { std::cout<< "| * "; }
                        else { std::cout << "| " << fieldCell.getNeighbours() << " "; }
                    }
                    else { std::cout<< "|   "; }
                }
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
                for (Mine fieldCell : fieldRow) fieldCell.getNeighbours() == -1 ? std::cout << "| * " : std::cout<< "| " << fieldCell.getNeighbours() << " ";
                std::cout << "|" << std::endl;
            }
            for (int i = 0; i < width*4+1; ++i) std::cout << '-';
            std::cout << std::endl;
        }


        bool isStepOnMine() {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if ((mineField[i][j].getNeighbours() == -1) && mineField[i][j].getIsTurnedUp()) {
                        return true; }
                }
            }
            return false;
        }


        bool isUnknownField() {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (mineField[i][j].getNeighbours() != -1 && !mineField[i][j].getIsTurnedUp()) {
                        return true;
                    }
                }
            }
            return false;
        }


        bool gameEnd() {
            if (isStepOnMine())         { std::cout << "You lose!\nGame Over!"; return true; }
            else if (!isUnknownField()) { std::cout << "You win!";              return true; }
            return false;
        }


        int getHeight() { return this->height; }


        int getWidth()  { return this->width;}


    private:

        void fillTable() {
            // step 1 goes here
            for (int i = 0; i < height; ++i) {
                std::vector<Mine> character;
                for (int j = 0; j < width; ++j) rand() % 100 > 85 ? character.emplace_back(Mine(-1)) : character.emplace_back(Mine(0));
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
        Minesweeper ms(20, 20);
        ms.countNeighbours();
//        ms.printTable2();
        ms.printTable();
        while (!ms.gameEnd()) {
            int x;
            int y;
            while (true) {
                std::cout << "\nGive me the row: ";
                std::cin >> x;
                std::cin.clear();
                std::cin.ignore(255, '\n');
                if (x > 0 && x <= ms.getHeight()) { break; }
            }
            while (true) {
                std::cout << "\nGive me the cell: ";
                std::cin >> y;
                std::cin.clear();
                std::cin.ignore(255, '\n');
                if (y > 0 && y <= ms.getWidth()) break;
            }
            ms.turnUpField(x-1, y-1);
//            ms.printTable2();
            ms.printTable();
        }
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}