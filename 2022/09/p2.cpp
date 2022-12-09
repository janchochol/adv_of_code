#include <iostream>
#include <string>
#include <unordered_set>

class Position {
public:
    Position(): x(0), y(0) { }
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

    Position knot[10];

    visited.insert(Position(0, 0));

    while (std::getline(std::cin, line)) {
        char move = line.at(0);
        int count = stoi(line.substr(2));

        while(count > 0) {
            switch(move) {
            case 'R':
                knot[0].x++;
                break;
            case 'L':
                knot[0].x--;
                break;
            case 'U':
                knot[0].y--;
                break;
            case 'D':
                knot[0].y++;
                break;
            }

            for (int k = 0; k < 9; k++) {
                if (knot[k].x == knot[k + 1].x) {
                    if (knot[k].y > knot[k + 1].y + 1) {
                        knot[k + 1].y++;
                    } else if(knot[k].y < knot[k + 1].y - 1) {
                        knot[k + 1].y--;
                    }
                } else if(knot[k].y == knot[k + 1].y) {
                    if (knot[k].x > knot[k + 1].x + 1) {
                        knot[k + 1].x++;
                    } else if(knot[k].x < knot[k + 1].x - 1) {
                        knot[k + 1].x--;
                    }
                } else {
                    if ((std::abs(knot[k].y - knot[k + 1].y) + std::abs(knot[k].x - knot[k + 1].x)) > 2) {
                        knot[k + 1].x += (knot[k].x - knot[k + 1].x) / std::abs(knot[k].x - knot[k + 1].x);
                        knot[k + 1].y += (knot[k].y - knot[k + 1].y) / std::abs(knot[k].y - knot[k + 1].y);
                    }
                }
            }

            for (int k = 0; k < 10; k++) {
                std::cout << knot[k].x << ":" <<  knot[k].y << " -> ";
            }
            std::cout << std::endl;
            visited.insert(knot[9]);

            count--;
        }
    }

    std::cout << visited.size() << std::endl;

    return 0;
}
