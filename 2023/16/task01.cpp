#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <stack>

struct beam {
    beam(int _x, int _y, int _dir) {
        x = _x;
        y = _y;
        dir = _dir;
    }
    int x, y;
    int dir;
};

constexpr int L = 1;
constexpr int D = 2;
constexpr int R = 4;
constexpr int U = 8;

int main() {
    std::string line;
    std::vector<std::string> rows;
    std::stack<beam> beams;
    int dimx, dimy;
    int *lights;

    while (std::getline(std::cin, line)) {
        rows.emplace_back(std::move(line));
    }
    dimx = rows[0].size();
    dimy = rows.size();

    lights = new int[dimx * dimy];
    memset(lights, 0, dimx * dimy * sizeof(*lights));
    beams.emplace(-1, 0, L);

    while (!beams.empty()) {
        beam cur = beams.top();
        beams.pop();

        int x = cur.x;
        int y = cur.y;

        // std::cout << x << " " << y << " " << cur.dir << std::endl;
        switch (cur.dir) {
            case L:
                x++;
                break;
            case D:
                y++;
                break;
            case R:
                x--;
                break;
            case U:
                y--;
                break;
        }
        // std::cout << " -> " << x << " " << y << " " << (lights[y * dimx + x] & cur.dir) << std::endl;
        if (x >= 0 && x < dimx && y >= 0 && y < dimy && ((lights[y * dimx + x] & cur.dir) == 0)) {
            lights[y * dimx + x] |= cur.dir;
            switch (rows[y].at(x)) {
                case '.':
                    beams.emplace(x, y, cur.dir);
                    break;
                case '|':
                    if (cur.dir == U || cur.dir == D) {
                        beams.emplace(x, y, cur.dir);
                    } else {
                        beams.emplace(x, y, U);
                        beams.emplace(x, y, D);
                    }
                    break;
                case '-':
                    if (cur.dir == L || cur.dir == R) {
                        beams.emplace(x, y, cur.dir);
                    } else {
                        beams.emplace(x, y, L);
                        beams.emplace(x, y, R);
                    }
                    break;
                case '/':
                    if (cur.dir == L) {
                        beams.emplace(x, y, U);
                    } else if (cur.dir == R) {
                        beams.emplace(x, y, D);
                    } else if (cur.dir == U) {
                        beams.emplace(x, y, L);
                    } else if (cur.dir == D) {
                        beams.emplace(x, y, R);
                    }
                    break;
                case '\\':
                    if (cur.dir == L) {
                        beams.emplace(x, y, D);
                    } else if (cur.dir == R) {
                        beams.emplace(x, y, U);
                    } else if (cur.dir == U) {
                        beams.emplace(x, y, R);
                    } else if (cur.dir == D) {
                        beams.emplace(x, y, L);
                    }
                    break;
            }
        }
    }

    long sum = 0;

    for (int y = 0; y < dimy; y++) {
        for (int x = 0; x < dimx; x++) {
            if (lights[y * dimx + x] != 0) {
                // std::cout << '#';
                sum++;
            } else {
                // std::cout << '.';
            }
        }
        // std::cout << std::endl;
    }

    delete [] lights;
    
    std::cout << sum << std::endl;
    return 0;
}
