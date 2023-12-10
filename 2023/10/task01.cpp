#include <iostream>
#include <string>
#include <string.h>
#include <vector>

struct move {
    move (int xx, int yy, int ffrom) {
        x = xx;
        y = yy;
        from = ffrom;
    }

    int x;
    int y;
    // top (prev -y), bottom(prev +y), left(prev -x), right(prev +x)
    int from;
};

bool valid(int *map, int x, int y, int dim, int move, int *visited) {
    bool valid = false;
    int n;

    switch(move) {
        case 0: // top -> down
            if (y < dim - 1) {
                y++;
                n = map[y * dim + x];
                valid = n == '|' || n == 'L' || n == 'J' || n == 'S';
            }
            break;
        case 1: // bottom -> up
            if (y > 0) {
                y--;
                n = map[y * dim + x];
                valid = n == '|' || n == '7' || n == 'F' || n == 'S';
            }
            break;
        case 2: // left -> right
            if (x < dim - 1) {
                x++;
                n = map[y * dim + x];
                valid = n == '-' || n == 'J' || n == '7' || n == 'S';
            }
            break;
        case 3: // right -> left
            if (x > 0) {
                x--;
                n = map[y * dim + x];
                valid = n == '-' || n == 'L' || n == 'F' || n == 'S';
            }
            break;
    }
    // std::cout << "V: " << x << " x " << y << " " << dim << " " << move << " " << n << " " << valid << " " << visited[y * dim + x] << std::endl;
    return valid && (visited[y * dim + x] == 0);
}

void advance(int &x, int &y, int move, int dim, int *visited) {
    switch(move) {
        case 0:
            y++;
            break;
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            x--;
            break;
    }
    visited[y * dim + x] = 1;
}

int main() {
    int dim  = -1;
    int *map;
    int *visited;
    std::string line;
    int y = 0;

    int sx, sy;
    std::vector<move> path;

    while (std::getline(std::cin, line)) {
        if (dim == -1) {
            dim = line.size();
            map = new int[dim * dim];
            visited = new int[dim * dim];
            memset(map, 0, sizeof(int) * dim * dim);
            memset(visited, 0, sizeof(int) * dim * dim);
        }
        for (int x = 0; x < dim; x++) {
            map[y * dim + x] = line.at(x);
            if (line.at(x) == 'S') {
                sx = x;
                sy = y;
            }
        }
        y++;
    }

    int x = sx;
    y = sy;
    int stry = 0;
    while(path.size() == 0 || sx != x || sy != y) {
        int t;
        switch(map[y * dim + x]) {
            case 'S':
                t = stry++;
                if (t == 4) {
                    std::cout << "ERR" << std::endl;
                    return 1;
                }
                break;
            case '|': // 0 -> 0, 1 -> 1
                t = path.back().from;
                break;
            case '_': // 2 -> 2, 3 -> 3
                t = path.back().from;
                break;
            case 'L': // 0 -> 2, 3 -> 1
                t = (path.back().from + 2) % 4;
                break;
            case 'J': // 0 -> 3, 2 -> 1
                t = (path.back().from + 3) % 4;
                break;
            case '7': // 2 -> 0, 1 -> 3
                t = (path.back().from + 2) % 4;
                break;
            case 'F': // 3 -> 0, 1 -> 2
                t = (path.back().from + 1) % 4;
                break;
        }
        bool v = valid(map, x, y, dim, t, visited);
        // std::cout << "T: " << x << " x " << y << " -> " << t << " = " << v << std::endl;

        if (v) {
            path.emplace_back(x, y, t);
            advance(x, y, t, dim, visited);
            // std::cout << "A: " << x << " x " << y << std::endl;
        } else {
            memset(visited, 0, sizeof(int) * dim * dim);
            path.clear();
            x = sx;
            y = sy;
        }
    }
    // std::cout << "B: " << x << " x " << y << std::endl;

    delete [] visited;
    delete [] map;

    std::cout << (path.size() / 2) << std::endl;

    return 0;
}
