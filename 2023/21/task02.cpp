#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>

/*
 * There is some period, but I have no ideas what conditions make it periodic.
 * So I end up manually analyzing numerical series on bigger board and found geometric series.
 * I end up with this solution (and do not ask me why it is working):
 *
 * echo "821009 1054439 821009 - 202293 * + 202293 202293 1 - 2 / * 29168 * + p" | dc
 *
 */

std::vector<std::pair<int, int>> next;
int dimx, dimy;
int *history;

void do_step(int x, int y, int s) {
    if (x >= 0 && x <= dimx - 1 && y >= 0 && y <= dimy - 1 && history[y * dimx + x] != -1 && history[y * dimx + x] < s) {
        history[y * dimx + x] = s;
        next.emplace_back(x, y);
    }
/*    if (x == 0 || x == dimx - 1 || y == 0 || y == dimy - 1) {
        std::cout << "edge " << s << std::endl;
    } */
}

int main(int argc, char *argv[]) {
    std::string line;
    std::vector<std::string> map;
    std::vector<std::pair<int, int>> stack;

    if (argc < 2) {
        std::cerr << "Usage: ./a.out <6: example, 64: input>" << std::endl;
        return 1;
    }

    while (std::getline(std::cin, line)) {
        map.emplace_back(line);
    }

    dimx = map[0].size();
    dimy = map.size();

    int q = 100;
    history = new int[(2 * q + 1) * dimx * (2 * q + 1) * dimy];

    for (int x = 0; x < dimx; x++) {
        for (int y = 0; y < dimy; y++) {
            int v;
            switch(map[y].at(x)) {
                case 'S':
                    stack.emplace_back(std::make_pair(q * dimx + x,q * dimy + y));
                case '.':
                    v = 0;
                    break;
                case '#':
                    v = -1;
                    break;
            }
            for (int dy = 0; dy < 2 * q + 1; dy++) {
                for (int dx = 0; dx < 2 * q + 1; dx++) {
                    history[(dy * dimy + y) * (2 * q + 1) * dimx + (dx * dimx + x)] = v;
                }
            }
        }
    }

    int steps = std::stoi(argv[1]);
    int prev1 = 0;
    int prev2 = 0;

    dimx *= 2 * q + 1;
    dimy *= 2 * q + 1;

    for (int s = 1; s <= steps; s++) {
        // std::cout << "S:" << s << " " << stack.size() << std::endl;
        for (const std::pair<int, int>& pos: stack) {
            int x = pos.first;
            int y = pos.second;

            do_step(x - 1, y, s);
            do_step(x + 1, y, s);
            do_step(x, y - 1, s);
            do_step(x, y + 1, s);
        }

        stack = std::move(next);
/*
        for (int x = 0; x < dimx; x++) {
            for (int y = 0; y < dimy; y++) {
                if(history[y * dimx + x] == -1) {
                    std::cout << "#";
                } else if(history[y * dimx + x] == s) {
                    std::cout << "O";
                } else {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
         } */
        if (s >= 100) {
            std::cout << s << ": " << stack.size() << " " << (stack.size() - prev2) << " " << (stack.size() - prev2 - s) << std::endl;
        }
        if (prev1 == stack.size()) {
            std::cout << prev1 << " " << prev2 << " " << s << std::endl;
        }
        prev1 = prev2;
        prev2 = stack.size();
    }

    delete [] history;
    
    std::cout << stack.size() << std::endl;
    return 0;
}
