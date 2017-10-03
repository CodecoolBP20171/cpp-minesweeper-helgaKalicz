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

        void printTable() const {
            // step 3 goes here
            int fieldWidthSize = 0;
            for (std::vector<Mine> fieldRow : mineField) {
                fieldWidthSize = fieldRow.size();
                // Print a line above the rows
                for (int i = 0; i < fieldWidthSize*4+1; ++i) {
                    std::cout << '-';
                }
                std::cout << std::endl;
                for (Mine fieldCell : fieldRow) {
                    std::cout << "| ";
                    fieldCell.getIsMine() ? std::cout << '*' : std::cout << fieldCell.getNeighbours();
                    std::cout << " ";
                }
                std::cout << "|" << std::endl;
            }
            // Print a line under the last row
            for (int i = 0; i < fieldWidthSize*4+1; ++i) {
                std::cout << '-';
            }
        }

    private:

        void generateRandomMines() {
            while (true) {
                int randomMine = rand() % (height * width);
                if (!(find(mineIndex.begin(), mineIndex.end(), randomMine) != mineIndex.end())) mineIndex.push_back(randomMine);
                if (mineIndex.size() == mineNumber) break;
            }
            std::sort(mineIndex.begin(), mineIndex.end());
        }

        // step 2 goes here
        void countNeighbours() {
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

        // step 1 goes here
        void fillTable() {
            generateRandomMines();
            int counter = 0;
            for (int i = 0; i < height; ++i) {
                std::vector<Mine> cellCharacter;
                for (int j = 0; j < width; ++j) {
                    if (mineIndex[0] == counter) {
                        mineIndex.erase(mineIndex.begin());
                        cellCharacter.push_back(Mine(true));
                    } else {
                        cellCharacter.push_back(Mine(false));
                    }
                    ++counter;
                }
                mineField.push_back(cellCharacter);
            }
            countNeighbours();
        }

        const size_t width, height;
        char *table;
        std::vector<std::vector<Mine>> mineField;
        std::vector<int> mineIndex;
        const int mineNumber = 10;
    };
}

int main() {
    srand(time(0));
    try {
        Minesweeper ms(5, 5);
        ms.printTable();
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}