#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stack>

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

bool valid(int *map, int x, int y, int dim, int dimy, int move, int *visited) {
    bool valid = false;
    int n;

    switch(move) {
        case 0: // top -> down
            if (y < dimy - 1) {
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
    int dimy;
    int *map;
    int *visited;
    std::string line;
    int y = 0;

    int sx, sy;
    std::vector<move> path;
    std::vector<std::string> lines;

    while (std::getline(std::cin, line)) {
        lines.emplace_back(line);
    }
    dimy = lines.size();
    for (auto line : lines) {
        if (dim == -1) {
            dim = line.size();
            map = new int[dim * dimy];
            visited = new int[dim * dimy];
            memset(map, 0, sizeof(int) * dim * dimy);
            memset(visited, 0, sizeof(int) * dim * dimy);
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
        bool v = valid(map, x, y, dim, dimy, t, visited);
        // std::cout << "T: " << x << " x " << y << " -> " << t << " = " << v << std::endl;

        if (v) {
            path.emplace_back(x, y, t);
            advance(x, y, t, dim, visited);
            // std::cout << "A: " << x << " x " << y << std::endl;
        } else {
            memset(visited, 0, sizeof(int) * dim * dimy);
            path.clear();
            x = sx;
            y = sy;
        }
    }
    // std::cout << "B: " << x << " x " << y << std::endl;

    int *g2 = new int[2 * dim * 2 * dimy];
    memset(g2, 0, sizeof(int) * 2 * dim * 2 * dimy);

    for (move step: path) {
        int xx = step.x * 2;
        int yy = step.y * 2;
        g2[yy * dim * 2 + xx] = 1;
        switch (step.from) {
            case 0:
                yy++;
                break;
            case 1:
                yy--;
                break;
            case 2:
                xx++;
                break;
            case 3:
                xx--;
                break;
        }
        g2[yy * dim * 2 + xx] = 1;
    }

    std::stack<std::pair<int, int>> search;

    search.emplace(dim * 2 - 1, dimy * 2 - 1);
    g2[(dimy * 2 - 1) * dim * 2 + dim * 2 - 1] = 2;

    while(!search.empty()) {
        int x = search.top().first;
        int y = search.top().second;
        search.pop();

        if (y < 2 * dimy - 1 && g2[(y + 1) * dim * 2 + x] == 0) {
            g2[(y + 1) * dim * 2 + x] = 2;
            search.emplace(x, y + 1);
        }
        if (y > 0 && g2[(y - 1) * dim * 2 + x] == 0) {
            g2[(y - 1) * dim * 2 + x] = 2;
            search.emplace(x, y - 1);
        }
        if (x < 2 * dim - 1 && g2[y * dim * 2 + x + 1] == 0) {
            g2[y * dim * 2 + x + 1] = 2;
            search.emplace(x + 1, y);
        }
        if (x > 0 && g2[y * dim * 2 + x - 1] == 0) {
            g2[y * dim * 2 + x - 1] = 2;
            search.emplace(x - 1, y);
        }
    }

    int count = 0;
    for (y = 1; y < dimy - 1; y++) {
        for (x = 1; x < dim - 1; x++) {
            if(g2[y * 2 * dim * 2 + x * 2] == 0) {
                g2[y * 2 * dim * 2 + x * 2] = 3;
                count ++;
            }
        }
    }
/*    for (y = 0; y < dimy * 2; y++) {
        for (x = 0; x < dim * 2; x++) {
            char c = '.';
            if (g2[y * dim * 2 + x] == 1) {
                c = '*';
            } else if (g2[y * dim * 2 + x] == 2) {
                c = '+';
            } else if (g2[y * dim * 2 + x] == 3) {
                c = '#';
            }
            std::cout << c;
        }
        std::cout << std::endl;
    }
*/
    delete [] g2;
    delete [] visited;
    delete [] map;

    std::cout << count << std::endl;

    return 0;
}
