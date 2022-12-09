#include <iostream>
#include <string>
#include <unordered_set>

class Position {
public:
    Position(int x, int y): x(x), y(y) { }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    };

    int x;
    int y;
};

template <>
struct std::hash<Position> {
    inline size_t operator()(const Position& p) const {
        size_t h1 = std::hash<int>{}(p.x);
        size_t h2 = std::hash<int>{}(p.y);
        return h1 ^ (h2 << 1);
    }
};


int main() {
    std::string line;
    std::unordered_set<Position> visited;

    int hx = 0, hy = 0, tx = 0, ty = 0;

    visited.insert(Position(tx, ty));

    while (std::getline(std::cin, line)) {
        char move = line.at(0);
        int count = stoi(line.substr(2));

        while(count > 0) {
            switch(move) {
            case 'R':
                hx++;
                break;
            case 'L':
                hx--;
                break;
            case 'U':
                hy--;
                break;
            case 'D':
                hy++;
                break;
            }

            if (hx == tx) {
                if (hy > ty + 1) {
                    ty++;
                } else if(hy < ty - 1) {
                    ty--;
                }
            } else if(hy == ty) {
                if (hx > tx + 1) {
                    tx++;
                } else if(hx < tx - 1) {
                    tx--;
                }
            } else {
                if ((std::abs(hy - ty) + std::abs(hx - tx)) > 2) {
                    tx += (hx - tx) / std::abs(hx - tx);
                    ty += (hy - ty) / std::abs(hy - ty);
                }
            }
            std::cout << hx << ":" << hy << " -> " << tx << ":" << ty << std::endl;

            visited.insert(Position(tx, ty));
            count--;
        }
    }

    std::cout << visited.size() << std::endl;

    return 0;
}
