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
            for (int i = 0; i < height*width; ++i) {
                for (int j = 0; j < 8; ++j) {

                }
            }
        }

        void printTable() const {
            // step 3 goes here
            int counter = 0;
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width*4+1; ++j) std::cout << '-';
                std::cout << std::endl;
                for (int k = 0; k < width; ++k) {
                    std::cout << "| " << table[counter] << " ";
                    ++counter;
                }
                std::cout << "|" << std::endl;
            }
            for (int j = 0; j < width*4+1; ++j) std::cout << '-';
            std::cout << std::endl;
        }

    private:
        void fillTable() {
            // step 1 goes here
            for (int i = 0; i < height*width; ++i) {
                rand() % 10 > 7 ? table[i] = '*' : table[i] = '.';
            }
        }

        const size_t width, height;
        char *table;
    };
}

int main() {
    try {
        Minesweeper ms(5, 5);
        ms.printTable();
        ms.countNeighbours();
        ms.printTable();
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}