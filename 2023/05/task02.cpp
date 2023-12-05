#include <iostream>
#include <string>
#include <string.h>
#include <vector>

int main() {
    std::string line;
    int state = 0;
    std::vector<std::pair<long, long>> v1;
    std::vector<std::pair<long, long>> v2;
    std::vector<std::pair<long, long>> *a = &v1;
    std::vector<std::pair<long, long>> *b = &v2;

    while (std::getline(std::cin, line)) {
        if (line.length() == 0) {
            continue;
        }
        if (state == 0) {
            long num = 0;
            long numo = 0;
            long idx = 0;
            for (int i = 7; i < line.length() + 1; i++) {
                long c;
                if (i == line.length() || (c = line.at(i)) == ' ') {
                    if (idx & 1) {
                        a->emplace_back(std::make_pair(numo, numo + num - 1));
                    } else {
                        numo = num;
                    }
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
                    std::vector<std::pair<long, long>>::iterator iter = a->begin();
                    while(iter != a->end()) {
                        b->emplace_back(*iter);
                        iter = a->erase(iter);
                    }
                }
/*                std::cout << state << ":";
                for (std::pair<long, long> &x : v1) {
                    std::cout << x.first << ":" << x.second << " ";
                }
                std::cout << std::endl;
                std::cout << state << ":";
                for (std::pair<long, long> &x : v2) {
                    std::cout << x.first << ":" << x.second << " ";
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
                nums[0] = nums[0] - nums[1];
                nums[2] = nums[1] + nums[2] - 1;
                // shift start end
                std::vector<std::pair<long, long>>::iterator iter = a->begin();
                while(iter != a->end()) {
                    if (iter->first >= nums[1] && iter->second <= nums[2]) {
                        //      | f       | s
                        //   | 1             | 2
                        b->emplace_back(std::make_pair(iter->first + nums[0], iter->second + nums[0]));
                        iter = a->erase(iter);
                    } else if (iter->first >= nums[1] && iter->first <= nums[2]) {
                        //      | f       | s
                        //   | 1       | 2
                        b->emplace_back(std::make_pair(iter->first + nums[0], nums[2] + nums[0]));
                        iter->first = nums[2] + 1;
                        ++iter;
                    } else if (iter->second >= nums[1] && iter->second <= nums[2]) {
                        //      | f       | s
                        //         | 1      | 2
                        b->emplace_back(std::make_pair(nums[1] + nums[0], iter->second + nums[0]));
                        iter->second = nums[1] - 1;
                        ++iter;
                    } else if (iter->first < nums[1] && iter->second > nums[2]) {
                        //      | f          | s
                        //        | 1      | 2
                        b->emplace_back(std::make_pair(nums[1] + nums[0], nums[2] + nums[0]));
                        a->emplace_back(std::make_pair(nums[2] + 1, iter->second));
                        iter->second = nums[1] - 1;
                        ++iter;
                    } else {
                        ++iter;
                    }
                }
            }
        }
    }
    std::vector<std::pair<long, long>>::iterator iter = a->begin();
    while(iter != a->end()) {
        b->emplace_back(*iter);
        iter = a->erase(iter);
    }
    long min = -1;
    for (std::pair<long, long> &x : *b) {
        if (min == -1 || x.first < min) {
            min = x.first;
        }
    }
    std::cout << min << std::endl;
    return 0;
}
