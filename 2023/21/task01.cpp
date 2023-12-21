#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>

int main(int argc, char *argv[]) {
    std::string line;
    std::vector<std::string> map;
    std::vector<std::pair<int, int>> stack;
    int dimx, dimy;
    int *history;

    if (argc < 2) {
        std::cerr << "Usage: ./a.out <6: example, 64: input>" << std::endl;
        return 1;
    }

    while (std::getline(std::cin, line)) {
        map.emplace_back(line);
    }

    dimx = map[0].size();
    dimy = map.size();

    history = new int[dimx * dimy];

    for (int x = 0; x < dimx; x++) {
        for (int y = 0; y < dimy; y++) {
            switch(map[y].at(x)) {
                case 'S':
                    stack.emplace_back(std::make_pair(x, y));
                    history[y * dimx + x] = 0;
                    break;
                case '.':
                    history[y * dimx + x] = 0;
                    break;
                case '#':
                    history[y * dimx + x] = -1;
                    break;
            }
        }
    }

    int steps = std::stoi(argv[1]);
    std::vector<std::pair<int, int>> next;

    for (int s = 1; s <= steps; s++) {
        // std::cout << "S:" << s << " " << stack.size() << std::endl;
        for (const std::pair<int, int>& pos: stack) {
            int x = pos.first;
            int y = pos.second;

            x--;
            if (x >= 0 && x <= dimx - 1 && y >= 0 && y <= dimy - 1 && history[y * dimx + x] != -1 && history[y * dimx + x] < s) {
                history[y * dimx + x] = s;
                next.emplace_back(x, y);
            }

            x += 2;
            if (x >= 0 && x <= dimx - 1 && y >= 0 && y <= dimy - 1 && history[y * dimx + x] != -1 && history[y * dimx + x] < s) {
                history[y * dimx + x] = s;
                next.emplace_back(x, y);
            }
            
            x--;
            y--;
            if (x >= 0 && x <= dimx - 1 && y >= 0 && y <= dimy - 1 && history[y * dimx + x] != -1 && history[y * dimx + x] < s) {
                history[y * dimx + x] = s;
                next.emplace_back(x, y);
            }

            y += 2;
            if (x >= 0 && x <= dimx - 1 && y >= 0 && y <= dimy - 1 && history[y * dimx + x] != -1 && history[y * dimx + x] < s) {
                history[y * dimx + x] = s;
                next.emplace_back(x, y);
            }
        }

        stack = std::move(next);
    }

    delete [] history;
    
    std::cout << stack.size() << std::endl;
    return 0;
}
