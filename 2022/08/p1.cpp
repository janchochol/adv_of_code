#include <iostream>
#include <string>

class Grid {
public:
    Grid(int size) : size(size) {
        arr = new int[size * size];
    };

    int& at(int x, int y) {
        return arr[x + size * y];
    };

    ~Grid() {
        delete []arr;
    };

    void dump() {
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                std::cout << at(x, y);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    int size;
private:
    int *arr;
};

#define LEFT 0
#define TOP 1
#define RIGHT 2
#define BOTTOM 3

int main() {
    std::string line;
    Grid *grid = NULL;
    Grid *mgrid[4] = { NULL };
    int x, y;
    int count;

    y = 0;
    while (std::getline(std::cin, line)) {
        if (grid == NULL) {
            grid = new Grid(line.size());
            mgrid[LEFT] = new Grid(line.size());
            mgrid[TOP] = new Grid(line.size());
            mgrid[RIGHT] = new Grid(line.size());
            mgrid[BOTTOM] = new Grid(line.size());
        }
        for (x = 0; x < grid->size; x++) {
            grid->at(x, y) = line.at(x) - '0';
        }
        y++;
    }
    grid->dump();

    for (int j = 0; j < grid->size; j++) {
        mgrid[LEFT]->at(0, j) = grid->at(0, j);
        mgrid[TOP]->at(j, 0) = grid->at(j, 0);
        mgrid[RIGHT]->at(grid->size - 1, j) = grid->at(grid->size - 1, j);
        mgrid[BOTTOM]->at(j, grid->size - 1) = grid->at(j, grid->size - 1);
    }

    for (int i = 1; i < grid->size; i++) {
        for (int j = 0; j < grid->size; j++) {
            mgrid[LEFT]->at(i, j) = std::max(mgrid[LEFT]->at(i - 1, j), grid->at(i, j));
            mgrid[TOP]->at(j, i) = std::max(mgrid[TOP]->at(j, i - 1), grid->at(j, i));
            mgrid[RIGHT]->at(grid->size - 1 - i, j) = std::max(mgrid[RIGHT]->at(grid->size - i, j), grid->at(grid->size - 1 - i, j));
            mgrid[BOTTOM]->at(j, grid->size - 1 - i) = std::max(mgrid[BOTTOM]->at(j, grid->size - i), grid->at(j, grid->size - 1 - i));
        }
    }

    for (int g = 0; g < 4; g++) {
        mgrid[g]->dump();
    }

    count = (grid->size - 1) * 4;
    for (x = 1; x < grid->size - 1; x++) {
        for (y = 1; y < grid->size - 1; y++) {
            int c = grid->at(x, y);

            if(
               c > mgrid[LEFT]->at(x - 1, y) ||
               c > mgrid[TOP]->at(x, y - 1) ||
               c > mgrid[RIGHT]->at(x + 1, y) ||
               c > mgrid[BOTTOM]->at(x, y + 1)
              ) {
                count++;
            }
        }
    }
    std::cout << count << std::endl;

    for (int g = 0; g < 4; g++) {
        delete mgrid[g];
    }
    delete grid;
    return 0;
}
