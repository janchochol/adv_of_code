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
    int x, y;

    y = 0;
    while (std::getline(std::cin, line)) {
        if (grid == NULL) {
            grid = new Grid(line.size());
        }
        for (x = 0; x < grid->size; x++) {
            grid->at(x, y) = line.at(x) - '0';
        }
        y++;
    }
    grid->dump();

    int max = 0;

    for (y = 1; y < grid->size - 1; y++) {
        for (x = 1; x < grid->size - 1; x++) {
            int l = 0, t = 0, r = 0, b = 0;
            int c = grid->at(x, y);

            for (int p = x - 1; p >= 0; p--) {
                l++;
                if (grid->at(p, y) >= c) {
                    break;
                }
            }
            for (int p = y - 1; p >= 0; p--) {
                t++;
                if (grid->at(x, p) >= c) {
                    break;
                }
            }
            for (int p = x + 1; p < grid->size; p++) {
                r++;
                if (grid->at(p, y) >= c) {
                    break;
                }
            }
            for (int p = y + 1; p < grid->size; p++) {
                b++;
                if (grid->at(x, p) >= c) {
                    break;
                }
            }
            c = l * t * r * b;
            std::cout << c << " ";
            if (c > max) {
                max = c;
            }
        }
        std::cout << std::endl;
    }
    std::cout << max << std::endl;

    delete grid;
    return 0;
}
