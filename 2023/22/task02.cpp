#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <sstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <set>

struct {
    bool operator()(std::array<std::array<int, 3>, 2>& a, std::array<std::array<int, 3>, 2>& b) const {
        return a[0][2] < b[0][2];
    }
} lowest;
    
void number_of_crashed(std::set<int>* supports, std::set<int>* supported_by, std::set<int>& crash, int i) {
    crash.emplace(i);

    for (const int& s: supports[i]) {
        bool incl = true;
        for (const int& r: supported_by[s]) {
            if (crash.find(r) == crash.end()) {
                incl = false;
                break;
            }
        }
        if (incl) {
            number_of_crashed(supports, supported_by, crash, s);
        }
    }
}

int main(int argc, char *argv[]) {
    std::string line;
    std::vector<std::array<std::array<int, 3>, 2>> bricks;
    std::array<int, 3> max{0, 0, 0};

    while (std::getline(std::cin, line)) {
        std::istringstream lines(line);
        std::string cube;
        std::array<std::array<int, 3>, 2> corners;
        int cr = 0;

        while (std::getline(lines, cube, '~')) {
            std::istringstream cubes(cube);
            std::string coord;
            int c = 0;
        
            while (std::getline(cubes, coord, ',')) {
                int v = std::stoi(coord);
                corners[cr][c] = v;
                if (v > max[c]) {
                    max[c] = v;
                }
                c++;
            }
            cr++;
        }
        if (corners[1][2] < corners[0][2]) {
            std::cout << "xxx" << std::endl;
        }
        bricks.emplace_back(corners);
    }

    std::sort(bricks.begin(), bricks.end(), lowest);

    max[0]++;
    max[1]++;
    max[2]++;

    int *used = new int[max[0] * max[1] * max[2]];
    std::set<int> *supports = new std::set<int>[bricks.size()];
    std::set<int> *supported_by = new std::set<int>[bricks.size()];
    int *fall = new int[bricks.size()];

    for (int x = 0; x < max[0]; x++) {
        for (int y = 0; y < max[1]; y++) {
            for (int z = 0; z < max[2]; z++) {
                used[z * max[0] * max[1] + y * max[0] + x] = -1;
            }
        }
    }
    
    int idx = 0;
    for (const auto& brick: bricks) {
        bool found = false;
        for (int z = brick[0][2] - 1; z > 0 && found == false; z--) {
            for (int x = brick[0][0]; x <= brick[1][0]; x++) {
                for (int y = brick[0][1]; y <= brick[1][1]; y++) {
                    int v = used[z * max[0] * max[1] + y * max[0] + x];
                    if (v != -1) {
                        // std::cout << "FF " << x << " " << y << " " << brick[0][2]  << " " << z << std::endl;
                        fall[idx] = brick[0][2] - 1 - z;
                        found = true;
                    }
                }
            }
        }
        if (!found) {
            fall[idx] = brick[0][2] - 1;
        }
//        std::cout << "F(" << idx << "): " << fall[idx] << std::endl;

        for (int x = brick[0][0]; x <= brick[1][0]; x++) {
            for (int y = brick[0][1]; y <= brick[1][1]; y++) {
                for (int z = brick[0][2] - fall[idx]; z <= brick[1][2] - fall[idx]; z++) {
                    // std::cout << idx << ": " << x << " " << y << " " << z << std::endl;
                    used[z * max[0] * max[1] + y * max[0] + x] = idx;
                }
            }
        }
        idx++;
    }
    
    idx = 0;
    for (const auto& brick: bricks) {
        int found = false;
        int z = brick[0][2] - 1 - fall[idx];
        for (int x = brick[0][0]; x <= brick[1][0]; x++) {
            for (int y = brick[0][1]; y <= brick[1][1]; y++) {
                int v = used[z * max[0] * max[1] + y * max[0] + x];
                if (v != -1) {
                    found = true;
                    supports[v].emplace(idx);
                    supported_by[idx].emplace(v);
                    // std::cout << "S: " << " " << v << " " << idx << std::endl;
                }
            }
        }
        idx++;
    }

    int sum = 0;
    for (int i = 0; i < bricks.size(); i++) {
        std::set<int> crash;

        number_of_crashed(supports, supported_by, crash, i);

        sum += crash.size() - 1;
    }

    delete [] fall;
    delete [] supported_by;
    delete [] supports;
    delete [] used;

    std::cout << sum << std::endl;

    return 0;
}
