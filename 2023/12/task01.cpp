#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>


int try_valid(int *vals, int *groups, int vcount, int gcount, bool in) {
    if (vcount == 0) {
        if (gcount == 0) {
            return 1;
        }
        if (in && gcount == 1 && groups[0] == 0) {
            return 1;
        }
        return 0;
    }

    int valid = 0;
    if(vals[0] == '.' || vals[0] == '?') {
        if (in) {
            if (groups[0] == 0) {
                valid += try_valid(vals + 1, groups + 1, vcount - 1, gcount - 1, false);
            }
        } else {
            valid += try_valid(vals + 1, groups, vcount - 1, gcount, false);
        }
    }

    if(vals[0] == '#' || vals[0] == '?') {
        if (in) {
            if (groups[0] > 0) {
                groups[0]--;
                valid += try_valid(vals + 1, groups, vcount - 1, gcount, true);
                groups[0]++;
            }
        } else {
            if (gcount > 0) {
                groups[0]--;
                valid += try_valid(vals + 1, groups, vcount - 1, gcount, true);
                groups[0]++;
            }
        }
    }
    return valid;
}

int main() {
    std::string line;
    int sum = 0;

    while (std::getline(std::cin, line)) {
        int i = 0;
        int *vals = new int[line.size()];
        int *groups = new int[line.size()];
        int vcount;
        int gcount;
        int group = 0;
        int idx = 0;

        for (; line.at(i) != ' '; i++) {
            vals[i] = line.at(i);
        }
        vcount = i;
        for (++i; i < line.size(); i++) {
            int c = line.at(i);
            if (c >= '0' && c <= '9') {
                group = group * 10 + c - '0';
            } else {
                groups[idx++] = group;
                group = 0;
            }
        }
        groups[idx++] = group;
        gcount = idx;

        int valid = try_valid(vals, groups, vcount, gcount, false);
        // std::cout << valid << std::endl;
        sum += valid;

        delete [] groups;
        delete [] vals;
    }

    std::cout << sum << std::endl;
    return 0;
}
