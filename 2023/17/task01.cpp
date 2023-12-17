#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>

constexpr int N = 1;
constexpr int S = 2;
constexpr int W = 4;
constexpr int E = 8;

struct node {
    node(int _dir, int _straight) {
        dir = _dir;
        straight = _straight;
    }
    int dir;
    int straight;
};

struct node_hash
{
    std::size_t operator()(const node& k) const
    {
        return
                std::hash<int>()(k.dir) ^
                (std::hash<int>()(k.straight) << 1);
    }
};
 
struct node_equal
{
    bool operator()(const node& lhs, const node& rhs) const
    {
        return lhs.dir == rhs.dir && lhs.straight == rhs.straight;
    }
};

std::vector<std::string> rows;
int dimx, dimy;
std::unordered_map<node, int, node_hash, node_equal> *prev;

bool possible(const node &p, int dir) {
    if (p.dir == N && dir == S) {
        return false;
    }
    if (p.dir == S && dir == N) {
        return false;
    }
    if (p.dir == W && dir == E) {
        return false;
    }
    if (p.dir == E && dir == W) {
        return false;
    }
    if (p.dir == dir && p.straight == 3) {
        return false;
    }
    return true;
}

bool step(int x, int y, int dir) {
    int x2 = x;
    int y2 = y;
    bool changed = false;
    if (dir == N) {
        if (y == 0) {
            return changed;
        } else {
            y2--;
        }
    }
    if (dir == S) {
        if (y == dimy - 1) {
            return changed;
        } else {
            y2++;
        }
    }
    if (dir == E) {
        if (x == 0) {
            return changed;
        } else {
            x2--;
        }
    }
    if (dir == W) {
        if (x == dimx - 1) {
            return changed;
        } else {
            x2++;
        }
    }

    for (const auto& [p, value] : prev[y * dimx + x]) {
        if (possible(p, dir)) {
            int next_value = value + rows[y2].at(x2) - '0';
            int next_straight;
            if (p.dir == dir) {
                next_straight = p.straight + 1;
            } else {
                next_straight = 1;
            }
            // std::cout  << x << " x " << y << " : " << x2 << " x " << y2 << " -> " << dir << " (" << value << " + " << next_value << ")" <<std::endl;
            node next_node = node(dir, next_straight);
            auto f = prev[y2 * dimx + x2].find(next_node);
            if (f == prev[y2 * dimx + x2].end()) {
                prev[y2 * dimx + x2][next_node] = next_value;
                changed = true;
            } else if (next_value < f->second) {
                f->second = next_value;
                changed = true;
            }
        }
    }
    return changed;
}

int main() {
    std::string line;

    while (std::getline(std::cin, line)) {
        rows.emplace_back(std::move(line));
    }
    dimx = rows[0].size();
    dimy = rows.size();

    prev = new std::unordered_map<node, int, node_hash, node_equal>[dimx * dimy];
    prev[0][node(W, 0)] = 0;
    bool changed = true;
    while (changed) {
        changed = false;
        for (int x = 0; x < dimx; x++) {
            for (int y = 0; y < dimy; y++) {
                changed |= step(x, y, N);
                changed |= step(x, y, S);
                changed |= step(x, y, W);
                changed |= step(x, y, E);
            }
        }
    }
    int m = -1;
    for (const auto& [p, value]: prev[(dimy - 1) * dimx + dimx - 1]) {
        if (m == -1 || value < m) {
            m = value;
        }
    }
    std::cout << m << std::endl;

    delete [] prev;
    
    return 0;
}
