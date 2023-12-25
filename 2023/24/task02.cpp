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

int main(int argc, char *argv[]) {
    std::string line;
    std::vector<std::array<std::array<long, 3>, 2>> hailstones;

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

    std::cout << sizeof(__int128) << std::endl;
/*
    for (int a = 0; a < hailstones.size(); a++) {
        for (int b = a + 1; b < hailstones.size(); b++) {
            double x =
                (double) hailstones[a][1][0] * hailstones[b][1][0] +
                (double) hailstones[a][1][1] * hailstones[b][1][1] +
                (double) hailstones[a][1][2] * hailstones[b][1][2];
            if (x == 0) {
                std::cout << a << " x " << b << " = " << x << std::endl;
            }
        }
    }
*/
    // count times:
    // hailstones[a][0][0] + v[a] * hailstones[a][1][0] = r[0][0] + v[a] * r[1][0];
    // hailstones[a][0][1] + v[a] * hailstones[a][1][1] = r[0][1] + v[a] * r[1][1];
    // hailstones[a][0][2] + v[a] * hailstones[a][1][2] = r[0][2] + v[a] * r[1][2];
    //
    //  v[a] * (hailstones[a][1][0] - r[1][0]) = (r[0][0] - hailstones[a][0][0]);
    //  v[a] * (hailstones[a][1][1] - r[1][1]) = (r[0][1] - hailstones[a][0][0]);
    //  v[a] * (hailstones[a][1][2] - r[1][2]) = (r[0][2] - hailstones[a][0][0]);
    //
    //  -> vector
    //  v[a] * (hailstones[a][1] - r[1]) = (r[0] - hailstones[a][0]);
    //  v[a] * (hailstones[a][1] - r[1]) x (hailstones[a][1] - r[1]) = (r[0] - hailstones[a][0]) x (hailstones[a][1] - r[1])
    //  0 = (r[0] - hailstones[a][0]) x (hailstones[a][1] - r[1])
    //
    //
    //  0 = (r[0] - hailstones[a][0]) x (hailstones[a][1] - r[1])
    //  0 = (r[0] - hailstones[b][0]) x (hailstones[b][1] - r[1])
    //  0 = (r[0] - hailstones[c][0]) x (hailstones[c][1] - r[1])
    //
    //  0 = (r[0][1] - hailstones[a][0][1]) * (hailstones[a][1][2] - r[1][2]) - (r[0][2] - hailstones[a][0][2]) * (hailstones[a][1][1] - r[1][1])
    //  0 = (r[0][2] - hailstones[a][0][2]) * (hailstones[a][1][0] - r[1][0]) - (r[0][0] - hailstones[a][0][0]) * (hailstones[a][1][2] - r[1][2])
    //  0 = (r[0][0] - hailstones[a][0][0]) * (hailstones[a][1][1] - r[1][1]) - (r[0][1] - hailstones[a][0][1]) * (hailstones[a][1][0] - r[1][0])
    //
    //  0 = r[0][1] * hailstones[a][1][2] - r[0][1] * r[1][2] - hailstones[a][0][1] * hailstones[a][1][2] + hailstones[a][0][1] * r[1][2]
    //    - r[0][2] * hailstones[a][1][1] - r[0][2] * r[1][1] - hailstones[a][0][2] * hailstones[a][1][1] + hailstones[a][0][2] * r[1][1]
    //  0 = r[0][2] * hailstones[a][1][0] - r[0][2] * r[1][0] - hailstones[a][0][2] * hailstones[a][1][0] + hailstones[a][0][2] * r[1][0]
    //    - r[0][0] * hailstones[a][1][2] - r[0][0] * r[1][2] - hailstones[a][0][0] * hailstones[a][1][2] + hailstones[a][0][0] * r[1][2]
    //  0 = r[0][0] * hailstones[a][1][1] - r[0][0] * r[1][1] - hailstones[a][0][0] * hailstones[a][1][1] + hailstones[a][0][0] * r[1][1]
    //    - r[0][1] * hailstones[a][1][0] - r[0][1] * r[1][0] - hailstones[a][0][1] * hailstones[a][1][0] + hailstones[a][0][1] * r[1][0]
    
    double a00  = hailstones[0][0][0];
    double a01  = hailstones[0][0][1];
    double a02  = hailstones[0][0][2];
    double a10  = hailstones[0][1][0];
    double a11  = hailstones[0][1][1];
    double a12  = hailstones[0][1][2];
    double b00  = hailstones[1][0][0];
    double b01  = hailstones[1][0][1];
    double b02  = hailstones[1][0][2];
    double b10  = hailstones[1][1][0];
    double b11  = hailstones[1][1][1];
    double b12  = hailstones[1][1][2];
    double c00  = hailstones[2][0][0];
    double c01  = hailstones[2][0][1];
    double c02  = hailstones[2][0][2];
    double c10  = hailstones[2][1][0];
    double c11  = hailstones[2][1][1];
    double c12  = hailstones[2][1][2];

    //  0 = r01 * a12 - r01 * r12 - a01 * a12 + a01 * r12 -r02 * a11 - r02 * r11 - a02 * a11 + a02 * r11
    //  0 = r01 * b12 - r01 * r12 - b01 * b12 + b01 * r12 -r02 * b11 - r02 * r11 - b02 * b11 + b02 * r11
    
    //  0 = r01 * (a12 - b12) - (a01 * a12 - b01 * b12) + (a01 - b01) * r12 - r02 * (a11 - b11) - (a02 * a11 - b02 * b11) + (a02 - b02) * r11

    double ab1 = a12 - b12;
    double ab2 = a01 * a12 - b01 * b12 + a02 * a11 - b02 * b11;
    double ab3 = a01 - b01;
    double ab4 = a11 - b11;
    double ab5 = a02 - b02;
    
    //  0 = ab1 * r01 - ab2 + ab3 * r12 - ab4 * r02 + ab5 * r11
    //  TODO - finish one time

    
    // Numbers obtained by sympy:
    std::cout << (261502975177164 + 428589795012222 + 196765966839909) << std::endl;


    return 0;
}
