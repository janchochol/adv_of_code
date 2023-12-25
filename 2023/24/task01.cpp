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

int main(int argc, char *argv[]) {
    std::string line;
    std::vector<std::array<std::array<long, 3>, 2>> hailstones;

    long min = 7;
    long max = 27;
    if (argc > 1) {
        min = 200000000000000;
        max = 400000000000000;
    }

    while (std::getline(std::cin, line)) {
        std::istringstream lines(line);
        std::string pos_vel;
        std::array<std::array<long, 3>, 2> hailstone;
        int pv = 0;

        while (std::getline(lines, pos_vel, '@')) {
            std::istringstream pos_vels(pos_vel);
            std::string xyz;
            int x = 0;
        
            while (std::getline(pos_vels, xyz, ',')) {
                long v = std::stol(xyz);
                hailstone[pv][x] = v;
                x++;
            }
            pv++;
        }
        hailstones.emplace_back(hailstone);
    }

    int sum = 0;
    for (int a = 0; a < hailstones.size(); a++) {
        for (int b = a + 1; b < hailstones.size(); b++) {
            double x1 = hailstones[a][0][0];
            double x2 = hailstones[a][0][0] + hailstones[a][1][0];
            double y1 = hailstones[a][0][1];
            double y2 = hailstones[a][0][1] + hailstones[a][1][1];

            double x3 = hailstones[b][0][0];
            double x4 = hailstones[b][0][0] + hailstones[b][1][0];
            double y3 = hailstones[b][0][1];
            double y4 = hailstones[b][0][1] + hailstones[b][1][1];

            double t = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
            t /= (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
            
            double u = (x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2);
            u /= (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

            double x = hailstones[a][0][0] + t * hailstones[a][1][0];
            double y = hailstones[a][0][1] + t * hailstones[a][1][1];
/*
            std::cout << x1 << " x " << y1 << std::endl;
            std::cout << x2 << " x " << y2 << std::endl;

            std::cout << x3 << " x " << y3 << std::endl;
            std::cout << x4 << " x " << y4 << std::endl;

            std::cout << a << " x " << b << " * " << t << " = " << x << " " << y << std::endl;
*/
            if (t >= 0 && u >= 0 && x >= min && x <= max && y >= min && y <= max) {
//                std::cout << "OK" << std::endl;
                sum++;
            }
        }
    }
    std::cout << sum;

    return 0;
}
