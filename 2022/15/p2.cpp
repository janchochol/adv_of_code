#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    std::string line;

    const int target = 4000001;
//    const int target = 21;
    std::vector<std::pair<int, int>> *intervals;

    intervals = new std::vector<std::pair<int, int>>[target];

    while (std::getline(std::cin, line)) {
        int comma1 = line.find(',');
        int double1 = line.find(':');
        int comma2 = line.find(',', comma1 + 1);

        int sx = stoi(line.substr(12, comma1 - 12));
        int sy = stoi(line.substr(comma1 + 4, double1 - comma1 - 4));
        int bx = stoi(line.substr(double1 + 25, comma2 - double1 - 25));
        int by = stoi(line.substr(comma2 + 4, line.size() - comma2 - 4));

        int size = std::abs(bx - sx) + std::abs(by - sy);

        for (int y = 0; y < target; y++) {
            if (y == sy) {
                intervals[y].push_back(std::make_pair(sx - size, sx + size));
            } else if (y < sy && y >= (sy - size)) {
                intervals[y].push_back(std::make_pair(sx - size + (sy - y), sx + size - (sy - y)));
            } else if (y > sy && y <= (sy + size)) {
                intervals[y].push_back(std::make_pair(sx - size + (y - sy),  sx + size - (y - sy)));
            }
        }
    }
    for (int y = 0; y < target; y++) {
        int sum = 0;
        int cur_min = -1;
        int cur_max = -1;

        sort(intervals[y].begin(), intervals[y].end());
        for (std::pair<int, int> interval : intervals[y]) {
            if (cur_min == -1 && cur_max == -1) {
                cur_min = interval.first;
                cur_max = interval.second;
            } else if (interval.first <= cur_max) {
                cur_max = std::max(cur_max, interval.second);
            } else {
                std::cout << (cur_max + 1) << "," << y << ": " << ((4000000 * ((long)cur_max + 1)) + y) << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
