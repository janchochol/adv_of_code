#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <cmath>

int main() {
    std::string time;
    std::string dist;

    std::getline(std::cin, time);
    std::getline(std::cin, dist);

    long tval = 0;
    long dval = 0;

    for (int tidx = 0; tidx < time.length(); tidx++) {
        int c = time.at(tidx);
        if (c >= '0' && c <= '9') {
            tval = tval * 10 + c - '0';
        }
    }
    for (int didx = 0; didx < dist.length(); didx++) {
        int c = dist.at(didx);
        if (c >= '0' && c <= '9') {
            dval = dval * 10 + c - '0';
        }
    }
    // std::cout << tval << " " << dval << std::endl;
    int wins = 0;
    // (tval - i) * i > dval
    // i * tval - i * i > dval
    // - 1 * i * i + tval * i - dval > 0
    //
    // (tval +- sqrt(tval * tval - 4 * dval)) / 2

    // Over-round a up and b down
    long a = (tval - std::sqrt(tval * tval - 4 * dval)) / 2 - 1;
    long b = (tval + std::sqrt(tval * tval - 4 * dval)) / 2 + 1;

    // Fix rounding
    while((tval - a) * a <= dval) {
        a++;
    }
    while((tval - b) * b <= dval) {
        b--;
    }

    // std::cout << a << " " << b << std::endl;

    std::cout << (b - a + 1) << std::endl;

    return 0;
}
