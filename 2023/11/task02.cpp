#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>

int main() {
    int dimx;
    int dimy;
    std::string line;
    std::map<int, bool> galx;
    std::map<int, bool> galy;
    std::vector<std::pair<int, int>> gals;

    int x = 0;
    int y = 0;
    while (std::getline(std::cin, line)) {
        for (x = 0; x < line.size(); x++) {
            if (line.at(x) == '#') {
                galx[x] = true;
                galy[y] = true;
                gals.emplace_back(x, y);
            }
        }
        y++;
    }

    int dx = x;
    int dy = y;
    int *mapx = new int[dx];
    int *mapy = new int[dy];

    int in;
    int out;

    in = -1;
    out = -1;
    for (const std::pair<const int, bool> gal : galx) {
        out += 1000000 * (gal.first - in - 1) + 1;
        // std::cout << gal.first << " -> " << out << std::endl;
        mapx[gal.first] = out;
        in = gal.first;
    }

    in = -1;
    out = -1;
    for (const std::pair<const int, bool> gal : galy) {
        out += 1000000 * (gal.first - in - 1) + 1;
        // std::cout << gal.first << " -> " << out << std::endl;
        mapy[gal.first] = out;
        in = gal.first;
    }

    long sum = 0;
    for (int i = 0; i < gals.size(); i++) {
        for (int j = i; j < gals.size(); j++) {
            sum += abs(mapx[gals[j].first] - mapx[gals[i].first]) + abs(mapy[gals[j].second] - mapy[gals[i].second]);
        }
    }
        
    std::cout << sum << std::endl;

    delete [] mapy;
    delete [] mapx;

    return 0;
}
