#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    std::string line;
    std::vector<std::pair<int, int>> intervals;
    std::set<int> beacons;

    int target_y = 2000000;
    int sum = 0;

    while (std::getline(std::cin, line)) {
        int comma1 = line.find(',');
        int double1 = line.find(':');
        int comma2 = line.find(',', comma1 + 1);

        int sx = stoi(line.substr(12, comma1 - 12));
        int sy = stoi(line.substr(comma1 + 4, double1 - comma1 - 4));
        int bx = stoi(line.substr(double1 + 25, comma2 - double1 - 25));
        int by = stoi(line.substr(comma2 + 4, line.size() - comma2 - 4));

        int size = std::abs(bx - sx) + std::abs(by - sy);

        std::cout << sx << "," << sy << " (" << size << ") x " << bx << "," << by << ": ";

        if (target_y == sy) {
            std::cout << (sx - size) << " - " << (sx + size) << std::endl;
            intervals.push_back(std::make_pair(sx - size, sx + size));
        } else if (target_y < sy && target_y >= (sy - size)) {
            std::cout << (sx - size + (sy - target_y)) << " - " << (sx + size - (sy - target_y)) << std::endl;
            intervals.push_back(std::make_pair(sx - size + (sy - target_y), sx + size - (sy - target_y)));
        } else if (target_y > sy && target_y <= (sy + size)) {
            std::cout << (sx - size + (target_y - sy)) << " - " << (sx + size - (target_y - sy)) << std::endl;
            intervals.push_back(std::make_pair(sx - size + (target_y - sy),  sx + size - (target_y - sy)));
        } else {
            std::cout << "none" << std::endl;
        }
        if (by == target_y) {
            if (beacons.find(by) == beacons.end()) {
                beacons.insert(by);
                sum --;
            }
        }
    }
    sort(intervals.begin(), intervals.end());

    int cur_min = -1;
    int cur_max = -1;

    for (std::pair<int, int> interval : intervals) {
        if (cur_min == -1 && cur_max == -1) {
            cur_min = interval.first;
            cur_max = interval.second;
        } else if (interval.first <= cur_max) {
            cur_max = std::max(cur_max, interval.second);
        } else {
            sum += cur_max - cur_min + 1;
            cur_min = interval.first;
            cur_max = interval.second;
        }
        std::cout << interval.first << "," << interval.second << " -> " << cur_min << " - " << cur_max << "(" << sum << ")" << std::endl;
    }
    sum += cur_max - cur_min + 1;

    std::cout << sum << std::endl;

    return 0;
}
