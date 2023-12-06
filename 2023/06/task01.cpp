#include <iostream>
#include <string>
#include <string.h>
#include <vector>

int main() {
    std::string time;
    std::string dist;
    
    std::getline(std::cin, time);
    std::getline(std::cin, dist);

    int tidx = 0;
    int didx = 0;

    long res = 1;

    while(tidx < time.length()) {
        bool found = false;

        int tval = 0;
        int dval = 0;
        for (; tidx < time.length(); tidx++) {
            int c = time.at(tidx);
            if (c >= '0' && c <= '9') {
                found = true;
                tval = tval * 10 + c - '0';
            } else if(found) {
                break;
            }
        }
        found = false;
        for (; didx < dist.length(); didx++) {
            int c = dist.at(didx);
            if (c >= '0' && c <= '9') {
                found = true;
                dval = dval * 10 + c - '0';
            } else if(found) {
                break;
            }
        }
        int wins = 0;
        for (int i = 0; i <= tval; i++) {
            int d = (tval - i) * i;
            if (d > dval) {
                wins ++;
            }
        }
        res = res * wins;
        // std::cout << tval << " " << dval << std::endl;
    }
    std::cout << res << std::endl;
    return 0;
}
