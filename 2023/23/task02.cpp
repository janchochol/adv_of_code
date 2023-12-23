#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <sstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <set>

int search(std::vector<std::string> &map, int x, int y, int *state);

void step(std::vector<std::string> &map, int x, int y, int *state, int &steps) {
    int n;
    if (x >= 0 && x <= map[0].size() && y >= 0 && y <= map.size() - 1) {
        if (map[y].at(x) != '#' && state[y * map[0].size() + x] == 0) {
            state[y * map[0].size() + x] = 1;
            n = search(map, x, y, state);
            if (steps == -1 || n > steps) {
                steps = n;
            }
            state[y * map[0].size() + x] = 0;
        }
    }
}

int search(std::vector<std::string> &map, int x, int y, int *state) {
    if (x == map[0].size() - 2 && y == map.size() - 1) {
        return 1;
    }
    int steps = -1;

    step(map, x - 1, y, state, steps);
    step(map, x + 1, y, state, steps);
    step(map, x, y - 1, state, steps);
    step(map, x, y + 1, state, steps);

    if (steps != -1) {
        steps++;
    }
    return steps;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> map;
    std::string line;

    while (std::getline(std::cin, line)) {
        map.emplace_back(line);
    }
    
    int *state = new int[map[0].size() * map.size()];

    state[1] = 1;
    std::cout << (search(map, 1, 0, state) - 1)  << std::endl;

    delete [] state;

    return 0;
}
