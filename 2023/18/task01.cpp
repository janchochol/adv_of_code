#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>

struct instr {
    instr(char dir_, int len_) {
        dir = dir_;
        len = len_;
    }
    char dir;
    int len;
};

int main() {
    std::string line;
    std::vector<instr> instrs;

    int x = 0;
    int y = 0;
    int maxx = 0;
    int maxy = 0;
    int minx = 0;
    int miny = 0;

    while (std::getline(std::cin, line)) {
        int v = 0;
        char dir = line.at(0);

        for (int i = 2; line.at(i) != ' '; i++) {
            v = v * 10 + line.at(i) - '0';
        }
        // std::cout << v << std::endl;
        instrs.emplace_back(dir, v);
        switch (dir) {
            case 'R':
                x += v;
                break;
            case 'L':
                x -= v;
                break;
            case 'U':
                y -= v;
                break;
            case 'D':
                y += v;
                break;

        }
        if (x < minx) {
            minx = x;
        }
        if (x > maxx) {
            maxx = x;
        }
        if (y < miny) {
            miny = y;
        }
        if (y > maxy) {
            maxy = y;
        }
    }
    
    int dimx = maxx - minx + 1;
    int dimy = maxy - miny + 1;
    
    // std::cout << "D: " << dimx << " " << dimy << std::endl;

    int *dmap = new int [dimx * 2 * dimy * 2];

    x = -2 * minx;
    y = -2 * miny;

    dmap[y * dimx * 2 + x] = 1;
    for (const instr& ins : instrs) {
        int dx = 0;
        int dy = 0;

        switch (ins.dir) {
            case 'R':
                dx = 1;
                break;
            case 'L':
                dx = -1;
                break;
            case 'U':
                dy = -1;
                break;
            case 'D':
                dy = 1;
                break;

        }
        for (int i = 0; i < 2 * ins.len; i++) {
            x += dx;
            y += dy;
            // std::cout << "X " << x << " " << y << std::endl;
            dmap[y * dimx * 2 + x] = 1;
        }
    }

    std::stack<std::pair<int, int>> stack;
    for (x = 0; x < 2 * dimx; x++) {
        y = 0;
        if (dmap[y * dimx * 2 + x] == 0) {
            stack.emplace(x, y);
            dmap[y * dimx * 2 + x] = 2;
        }
        y = 2 * dimy - 1;
        if (dmap[y * dimx * 2 + x] == 0) {
            stack.emplace(x, y);
            dmap[y * dimx * 2 + x] = 2;
        }
    }
    for (y = 0; y < 2 * dimy; y++) {
        x = 0;
        if (dmap[y * dimx * 2 + x] == 0) {
            stack.emplace(x, y);
            dmap[y * dimx * 2 + x] = 2;
        }
        x = 2 * dimx - 1;
        if (dmap[y * dimx * 2 + x] == 0) {
            stack.emplace(x, y);
            dmap[y * dimx * 2 + x] = 2;
        }
    }
    while(!stack.empty()) {
        x = stack.top().first;
        y = stack.top().second;
        stack.pop();

        x--;
        if (x >= 0 && x < dimx * 2 && dmap[y * dimx * 2 + x] == 0) {
            stack.emplace(x, y);
            dmap[y * dimx * 2 + x] = 2;
        }

        x += 2;
        if (x >= 0 && x < dimx * 2 && dmap[y * dimx * 2 + x] == 0) {
            stack.emplace(x, y);
            dmap[y * dimx * 2 + x] = 2;
        }

        x--;
        y--;
        if (y >= 0 && y < dimy * 2 && dmap[y * dimx * 2 + x] == 0) {
            stack.emplace(x, y);
            dmap[y * dimx * 2 + x] = 2;
        }

        y += 2;
        if (y >= 0 && y < dimy * 2 && dmap[y * dimx * 2 + x] == 0) {
            stack.emplace(x, y);
            dmap[y * dimx * 2 + x] = 2;
        }
    }

    int sum = 0;
    for (y = 0; y < dimy; y++) {
        for (x = 0; x < dimx; x++) {
            int v = dmap[2 * y * dimx * 2 + 2 * x];
/*            if (v == 0) {
                std::cout << "0";
            } else if (v == 1) {
                std::cout << "#";
            } else {
                std::cout << ".";
            } */
            if (v == 0 || v == 1) {
                sum++;
            }
        }
//        std::cout << std::endl;
    }

    delete [] dmap;
    std::cout << sum << std::endl;

    return 0;
}
