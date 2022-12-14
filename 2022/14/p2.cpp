#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>


class Path {
public:
    Path() {}

    std::vector<int> x;
    std::vector<int> y;
};

int main() {
    std::string line;
    std::vector<Path> paths;

    while (std::getline(std::cin, line)) {
        paths.push_back(Path());

        Path &current = paths.at(paths.size() - 1);
        int pos = 0;
        while(pos < line.size()) {
            int comma = line.find(',', pos);
            int space = line.find(' ', comma);

            if (space == std::string::npos) {
                space = line.size();
            }

            int x = stoi(line.substr(pos, comma - pos));
            int y = stoi(line.substr(comma + 1, space - comma - 1));

            current.x.push_back(x);
            current.y.push_back(y);

            pos = space + 4;
        }
    }

    int max_y = 0;
    int min_x = 500;
    int max_x = 500;

    for (const Path& path : paths) {
        for (int i = 0; i < path.x.size(); i++) {
            if (path.y.at(i) > max_y) {
                max_y = path.y.at(i);
            }
            if (path.x.at(i) > max_x) {
                max_x = path.x.at(i);
            }
            if (path.x.at(i) < min_x) {
                min_x = path.x.at(i);
            }
        }
    }

    min_x -= max_y + 1;
    max_x += max_y + 1;
    max_y += 2;

    std::cout << std::endl;

    int size_x = max_x - min_x + 1;
    int *map = new int[(max_y + 1) * size_x];

    std::fill_n(map, (max_y + 1) * size_x, 0);

    for (int x = min_x; x <= max_x; x++) {
        map[x - min_x + max_y * size_x] = 1;
    }

    for (const Path& path : paths) {
        for (int i = 0; i < path.x.size() - 1; i++) {
            int x = path.x.at(i);
            int y = path.y.at(i);

            int fx = path.x.at(i + 1);
            int fy = path.y.at(i + 1);

            int dx = 0;
            int dy = 0;

            if (fx > x) {
                dx = 1;
            } else if (fx < x) {
                dx = -1;
            }

            if (fy > y) {
                dy = 1;
            } else if (fy < y) {
                dy = -1;
            }

            while (x != fx || y != fy) {
                map[x - min_x + y * size_x] = 1;

                x += dx;
                y += dy;
            }
            map[x - min_x + y * size_x] = 1;
        }
    }

    for (int y = 0; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            if (map[x - min_x + y * size_x] == 1) {
                std::cout << "#";
            } else if (map[x - min_x + y * size_x] == 2) {
                std::cout << "%";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::queue<int> qx;
    std::queue<int> qy;

    qx.push(500);
    qy.push(0);

    int sands = 1;
    map[500 - min_x + 0 * size_x] = 2;

    while(!qx.empty()) {
        int sx = qx.front();
        int sy = qy.front();

        qx.pop();
        qy.pop();

        if (map[sx - min_x + (sy + 1) * size_x] == 0) {
            map[sx - min_x + (sy + 1) * size_x] = 2;
            sands ++;

            qx.push(sx);
            qy.push(sy + 1);
        }

        if(map[(sx - 1) - min_x + (sy + 1) * size_x] == 0) {
            map[(sx - 1) - min_x + (sy + 1) * size_x] = 2;
            sands ++;

            qx.push(sx - 1);
            qy.push(sy + 1);
        }

        if(map[(sx + 1) - min_x + (sy + 1) * size_x] == 0) {
            map[(sx + 1) - min_x + (sy + 1) * size_x] = 2;
            sands ++;

            qx.push(sx + 1);
            qy.push(sy + 1);
        }
    }
    for (int y = 0; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            if (map[x - min_x + y * size_x] == 1) {
                std::cout << "#";
            } else if (map[x - min_x + y * size_x] == 2) {
                std::cout << "%";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << sands << std::endl;


    return 0;
}
