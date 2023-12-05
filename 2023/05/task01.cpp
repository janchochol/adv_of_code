#include <iostream>
#include <string>
#include <string.h>
#include <vector>

int main() {
    std::string line;
    int state = 0;
    std::vector<long> v1;
    std::vector<long> v2;
    std::vector<long> *a = &v1;
    std::vector<long> *b = &v2;

    while (std::getline(std::cin, line)) {
        if (line.length() == 0) {
            continue;
        }
        if (state == 0) {
            long num = 0;
            long idx = 0;
            for (int i = 7; i < line.length() + 1; i++) {
                long c;
                if (i == line.length() || (c = line.at(i)) == ' ') {
                    a->emplace_back(num);
                    num = 0;
                    idx++;
                } else {
                    num = 10 * num + c - '0';
                }
            }
            state++;
        } else {
            long s = line.at(0);
            if (s < '0' || s > '9') {
                state++;
                if (state > 2) {
                    std::vector<long>::iterator iter = a->begin();
                    while(iter != a->end()) {
                        b->emplace_back(*iter);
                        iter = a->erase(iter);
                    }
                }
/*                std::cout << state << ":";
                for (long &x : v1) {
                    std::cout << x << " ";
                }
                std::cout << std::endl;
                std::cout << state << ":";
                for (long &x : v2) {
                    std::cout << x << " ";
                }
                std::cout << std::endl; */
                if (state & 1) {
                    b = &v1;
                    a = &v2;
                } else {
                    a = &v1;
                    b = &v2;
                }
            } else {
                long num = 0;
                long idx = 0;
                long nums[3]; // dest start len
                for (int i = 0; i < line.length() + 1; i++) {
                    long c;
                    if (i == line.length() || (c = line.at(i)) == ' ') {
                        nums[idx] = num;
                        num = 0;
                        idx++;
                    } else {
                        num = 10 * num + c - '0';
                    }
                }
                std::vector<long>::iterator iter = a->begin();
                while(iter != a->end()) {
                    if (*iter >= nums[1] && *iter < nums[1] + nums[2]) {
                        b->emplace_back(*iter - nums[1] + nums[0]);
                        iter = a->erase(iter);
                    } else {
                        ++iter;
                    }
                }
            }
        }
    }
    std::vector<long>::iterator iter = a->begin();
    while(iter != a->end()) {
        b->emplace_back(*iter);
        iter = a->erase(iter);
    }
    long min = -1;
    for (long &x : *b) {
        if (min == -1 || x < min) {
            min = x;
        }
    }
    std::cout << min << std::endl;
    return 0;
}
